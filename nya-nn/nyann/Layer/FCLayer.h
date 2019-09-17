#pragma once
#include <vector>
#include <functional>
#include <variant>
#include <random>

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
		std::vector<std::vector<double>> m_weights;
		std::vector<double> m_biases;
		std::variant<DataSet<_DT_IN>, DataRow<_DT_IN>> m_input; // cached data
	public:
		FCLayer(const Size& size_in, const Size& size_out);
		FCLayer(const Size& size_in_out);

		virtual DataSet<_DT_OUT> operator() (const DataSet<_DT_IN>& input) override
		{
			m_input = input;

			DataSet<_DT_OUT> results(input.get_size());

			// process row by row
			for (int k = 0; k < results.get_size()[0]; k++)
				results[k] = operator()(input[k], false);

			return results;
		}

		// for now on-line learning
		virtual DataRow<_DT_OUT> operator() (const DataRow<_DT_IN>& input, bool save = true) override
		{
			DataRow<_DT_OUT> output(m_size_out);
			for (int j = 0; j < m_size_out; j++)
			{
				for (int i = 0; i < m_size_in; i++)
					output[j] += m_weights[i][j] * input[i];
				output[j] -= m_biases[j];
			}

			// save data 
			// for back propagation
			if (save)
				m_input = input;
			return output;
		}

		virtual std::vector<double> back_propagation(
			const std::vector<double>& errors,
			const std::vector<double>& derivitives, // d(yj) / d(Sj) - caused by activation function
			double lr = 0.01
		) override
		{
			// output here is error on this layer
			auto& input = std::get<DataRow<_DT_IN>>(m_input);

			// updating parameters
			for (int j = 0; j < m_size_out; j++)
			{
				for (int i = 0; i < m_size_in; i++)
					m_weights[i][j] -= lr * errors[j] * derivitives[j] * input[i];
				m_biases[j] += lr * errors[j] * derivitives[j];
			}

			// clear cached data
			input.clear();

			// calculate the error on this layer
			std::vector<double> errors_here(m_size_in);
			for (int i = 0; i < m_size_in; i++)
				for (int j = 0; j < m_size_out; j++)
					errors_here[i] += errors[j] * derivitives[j] * m_weights[i][j];

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
			std::normal_distribution distribution(0.0, 1.0);
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
	FCLayer<_DT_IN, _DT_OUT>::FCLayer(const Size& size_in, const Size& size_out)
		: m_weights(size_in), m_biases(size_out),
		m_size_in(size_in), m_size_out(size_out)
	{
		for (auto& w : m_weights)
			w.resize(m_size_out);
		fill_weights_random();
	}

	template<typename _DT_IN, typename _DT_OUT>
	FCLayer<_DT_IN, _DT_OUT>::FCLayer(const Size& size_in_out)
		: m_weights(size_in_out[0]), m_biases(size_in_out[1]),
		m_size_in(size_in_out[0]), m_size_out(size_in_out[1])
	{
		for (auto& w : m_weights)
			w.resize(m_size_out);
		fill_weights_random();
	}


} // namespace nyann 