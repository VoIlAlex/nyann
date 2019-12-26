#pragma once
#include <vector>
#include <functional>
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
		DataSet<_DT_IN> m_input;
		DataSet<_DT_OUT> m_output;
	public:
		FCLayer(const Size<>& size_in, const Size<>& size_out)
			: m_weights(size_in), m_biases(size_out),
			m_size_in(size_in), m_size_out(size_out)
		{
			for (auto& w : m_weights)
				w.resize(m_size_out);
			fill_weights_random();
		}

		FCLayer(const Size<>& size_in_out)
			: m_weights(size_in_out[0]), m_biases(size_in_out[1]),
			m_size_in(size_in_out[0]), m_size_out(size_in_out[1])
		{
			for (auto& w : m_weights)
				w.resize(m_size_out);
			fill_weights_random();
		}

		virtual DataSet<_DT_OUT> operator() (const DataSet<_DT_IN>& input) override
		{

			// Save input to use
			// in backpropagation
			m_input = input;

			DataSet<_DT_OUT> outputs({ input.get_size()[0], m_size_out });

			for (int k = 0; k < outputs.get_size()[0]; k++)
			{
				//DataRow<_DT_OUT> output(m_size_out);
				for (int j = 0; j < m_size_out; j++)
				{
					for (int i = 0; i < m_size_in; i++)
						outputs[k][j] += m_weights[i][j] * input[k][i];
					outputs[k][j] -= m_biases[j];
					if (this->m_activation_function != nullptr)
						outputs[k][j] = this->m_activation_function->operator()(outputs[k][j]);
				}

				// save data 
				// for back propagation
				//return output;
			}

			// Save output to use
			// in backpropagation
			m_output = outputs;

			return outputs;
		}
		virtual DataSet<double> back_propagation(
			const DataSet<double>& errors,
			double lr = 0.01
		) override
		{
			auto& input = m_input;
			auto& output = m_output;
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
			std::normal_distribution distribution(0., sqrt(2. / (m_size_in + m_size_out)));
			auto generator = std::bind(distribution, random_engine);
			for (int j = 0; j < m_size_out; j++)
			{

				for (int i = 0; i < m_size_in; i++)
					m_weights[i][j] = generator();
				m_biases[j] = generator();
			}


		}
	};


} // namespace nyann 