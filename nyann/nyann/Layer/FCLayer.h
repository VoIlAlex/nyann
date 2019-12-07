#pragma once
#include <vector>
#include <functional>
#include <variant>
#include <random>

// For all the framework configurations
#include "../_config.h"


#include "..//Layer.h" // for Layer
#include "..//utils.h" // for Size
#include "..//dataset.h" // for DataSet

namespace nyann
{

	// 1-dimentional for now
	template<typename _DT_IN, typename _DT_OUT = _DT_IN>
	class FCLayer : public Layer<_DT_IN, _DT_OUT>
	{
		int m_size_in;
		int m_size_out;
#ifndef DEPRECATED_FCLAYER_WEIGHTS_VECTOR
		std::vector<std::vector<double>> m_weights;
		std::vector<double> m_biases;
#else
		DataSet<_DT_OUT> m_weights;
		DataSet<_DT_OUT> m_biases;
#endif

		// cached data
#ifndef DEPRECATED_LAYER_ROW_PROCESSING
		std::variant<DataSet<_DT_IN>, DataRow<_DT_IN>> m_input;
		std::variant<DataSet<_DT_OUT>, DataRow<_DT_OUT>> m_output;
#else
		DataSet<_DT_IN> m_input;
		DataSet<_DT_OUT> m_output;
#endif
	public:
		FCLayer(const Size<>& size_in, const Size<>& size_out);
		FCLayer(const Size<>& size_in_out);

		virtual DataSet<_DT_OUT> operator() (const DataSet<_DT_IN>& input) override
		{

			// Save input to use
			// in backpropagation
			m_input = input;

			DataSet<_DT_OUT> outputs(input.get_size());
#ifndef DEPRECATED_LAYER_ROW_PROCESSING
			// process row by row
			for (int k = 0; k < outputs.get_size()[0]; k++)
				outputs[k] = operator()(input[k], false);
#else
			for (int k = 0; k < outputs.get_size()[0]; k++)
			{
				DataRow<_DT_OUT> output(m_size_out);
				for (int j = 0; j < m_size_out; j++)
				{
					for (int i = 0; i < m_size_in; i++)
						output[j] += m_weights[i][j] * input[k][i];
					output[j] -= m_biases[j];
					if (this->m_activation_function != nullptr)
						output[j] = this->m_activation_function->operator()(output[j]);
				}

				// save data 
				// for back propagation
				return output;
			}
#endif

			// Save output to use
			// in backpropagation
			m_output = outputs;

			return outputs;
		}
#ifndef DEPRECATED_LAYER_ROW_PROCESSING
		// for now on-line learning
		virtual DataRow<_DT_OUT> operator() (const DataRow<_DT_IN>& input, bool save = true) override
		{
			DataRow<_DT_OUT> output(m_size_out);
			for (int j = 0; j < m_size_out; j++)
			{
				for (int i = 0; i < m_size_in; i++)
					output[j] += m_weights[i][j] * input[i];
				output[j] -= m_biases[j];
				if (this->m_activation_function != nullptr)
					output[j] = this->m_activation_function->operator()(output[j]);
			}

			// save data 
			// for back propagation
			if (save)
			{
				m_input = input;
				m_output = output;
			}
			return output;
		}
#endif
# ifndef DEPRECATED_LAYER_ROW_PROCESSING
		virtual std::vector<double> back_propagation(
			const std::vector<double>& errors,
			const std::vector<double>& derivatives, // d(yj) / d(Sj) - caused by activation function
			double lr = 0.01
		) override
		{
			// output here is error on this layer
			auto& input = std::get<DataRow<_DT_IN>>(m_input);

			// updating parameters
			for (int j = 0; j < m_size_out; j++)
			{
				for (int i = 0; i < m_size_in; i++)
					m_weights[i][j] -= lr * errors[j] * derivatives[j] * input[i];
				m_biases[j] += lr * errors[j] * derivatives[j];
			}

			// clear cached data
			input.clear();

			// calculate the error on this layer
			std::vector<double> errors_here(m_size_in);
			for (int i = 0; i < m_size_in; i++)
				for (int j = 0; j < m_size_out; j++)
					errors_here[i] += errors[j] * derivatives[j] * m_weights[i][j];

			return errors_here;
		}
#endif
		virtual DataSet<double> back_propagation(
			const DataSet<double>& errors,
			double lr = 0.01
		) override
		{
#ifndef DEPRECATED_LAYER_ROW_PROCESSING
			auto& input = std::get<DataSet<_DT_IN>>(m_input);
			auto& output = std::get<DataSet<_DT_OUT>>(m_output);
#else
			auto& input = m_input;
			auto& output = m_output;
#endif
			auto weights_copy = m_weights;


			// get derivatives
			// from activation 
			// function
			DataSet<double> derivatives = DataSet<double>::ones_like(errors);
			if (this->m_activation_function != nullptr)
				for (int i = 0; i < derivatives.size(); i++)
					for (int j = 0; j < derivatives[0].size(); j++)
					{
						derivatives[i][j] = this->m_activation_function->derivative(output[i][j]);
					}


			// update weights
			for (int j = 0; j < m_size_out; j++)
			{
				for (int i = 0; i < m_size_in; i++)
				{
					double derivative_by_weight = 0;
					for (int k = 0; k < derivatives.size(); k++)
						derivative_by_weight += errors[k][j] * derivatives[k][j] * input[k][i];

					m_weights[i][j] -= lr * derivative_by_weight;
				}

				double derivative_by_bias = 0;
				for (int k = 0; k < derivatives.size(); k++)
					derivative_by_bias -= errors[k][j] * derivatives[k][j];

				m_biases[j] -= lr * derivative_by_bias;
			}

			// Errors on this layer
			// (they are calculated by errors
			// from the next layer)
			DataSet<double> errors_here(errors.size());
			for (int k = 0; k < errors.size(); k++)
			{
				for (int i = 0; i < m_size_in; i++)
				{
					double error_k_i = 0;

					for (int j = 0; j < m_size_out; j++)
						error_k_i += errors[k][j] * derivatives[k][j] * weights_copy[i][j];

					errors_here[k].push_back(error_k_i);
				}
			}

			return errors_here;
		}

		std::vector<std::vector<double>> get_weights() const
		{
			return m_weights;
		}
		std::vector<std::vector<double>>& get_weights()
		{
			return m_weights;
		}

		std::vector<double> get_biases() const
		{
			return m_biases;
		}
		std::vector<double>& get_biases()
		{
			return m_biases;
		}


	private:
		void fill_weights_random()
		{
			std::default_random_engine random_engine;
			std::normal_distribution distribution(0., sqrt(2. / m_size_in));
			auto generator = std::bind(distribution, random_engine);
			for (int j = 0; j < m_size_out; j++)
			{

				for (int i = 0; i < m_size_in; i++)
					m_weights[i][j] = generator();
				m_biases[j] = generator();
			}


		}
	};

	template<typename _DT_IN, typename _DT_OUT>
	FCLayer<_DT_IN, _DT_OUT>::FCLayer(const Size<>& size_in, const Size<>& size_out)
		: m_weights(size_in), m_biases(size_out),
		m_size_in(size_in), m_size_out(size_out)
	{
		for (auto& w : m_weights)
			w.resize(m_size_out);
		fill_weights_random();
	}

	template<typename _DT_IN, typename _DT_OUT>
	FCLayer<_DT_IN, _DT_OUT>::FCLayer(const Size<>& size_in_out)
		: m_weights(size_in_out[0]), m_biases(size_in_out[1]),
		m_size_in(size_in_out[0]), m_size_out(size_in_out[1])
	{
		for (auto& w : m_weights)
			w.resize(m_size_out);
		fill_weights_random();
	}


} // namespace nyann 