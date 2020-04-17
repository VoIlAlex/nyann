#pragma once
#include <vector>
#include <functional>
#include <random>

// For all the framework configurations
#include "../_config.h"


#include "../Layer.h" // for Layer
#include "../utils.h" // for Size
#include "../dataset.h" // for DataSet

#ifdef DRAFT_DATASET_2_0_0_ALPHA_TEST
#include "../drafts/DataSet_draft.h"
#endif

namespace nyann
{
#ifdef DRAFT_DATASET_2_0_0_ALPHA_TEST
	// 1-dimentional for now
	template<typename _DT_IN, typename _DT_OUT = _DT_IN>
	class FCLayer : public Layer<_DT_IN, _DT_OUT>
	{
		Size<size_t> m_size_in;
		Size<size_t> m_size_out;
		DataSet_draft<_DT_OUT> m_weights;
		DataSet_draft<_DT_OUT> m_biases;

		// cached data
		DataSet_draft<_DT_IN> m_input;
		DataSet_draft<_DT_OUT> m_output;
	public:
		FCLayer(const Size<size_t>& size_in, const Size<size_t>& size_out)
			: m_weights(Size<>::join(size_in, size_out)), m_biases(size_out),
			m_size_in(size_in), m_size_out(size_out)
		{
			fill_weights_random();
		}

		FCLayer(const Size<size_t>& size_in_out)
			: m_weights(size_in_out), m_biases({ size_in_out[1] }),
			m_size_in(size_in_out[0]), m_size_out(size_in_out[1])
		{
			fill_weights_random();
		}

		virtual DataSet_draft<_DT_OUT> operator() (const DataSet_draft<_DT_IN>& input) override
		{

			// Save input to use
			// in backpropagation
			m_input = input;
			size_t batch_count = input.get_size()[0];

			Size<size_t> outputs_size = Size<size_t>::join({ batch_count }, m_size_out);
			DataSet_draft<_DT_OUT> outputs(outputs_size);

			Index<size_t> in_index(m_size_in.size());
			Index<size_t> out_index(m_size_out.size());
			Index<size_t> max_in_index = to_index(m_size_in);
			Index<size_t> max_out_index = to_index(m_size_out);
			for (size_t batch = 0; batch < batch_count; batch++)
			{
				for (; out_index < max_out_index; out_index.increment({}, max_out_index))
				{
					Index<size_t> batch_out_index = Index<size_t>::join({ batch }, out_index);
					for (; in_index < max_in_index; in_index.increment({}, max_in_index))
					{
						Index<size_t> in_out_index = Index<size_t>::join(in_index, out_index);
						Index<size_t> batch_in_index = Index<size_t>::join({ batch }, in_index);
						outputs.at_index(batch_out_index) += m_weights.at_index(in_out_index) * input.at_index(batch_in_index);
					}
					outputs.at_index(batch_out_index) -= m_biases.at_index(out_index);
				}
			}
			outputs = this->m_activation_function->operator()(outputs);

			//for (int k = 0; k < outputs.get_size()[0]; k++)
			//{
			//	//DataRow<_DT_OUT> output(m_size_out);
			//	for (int j = 0; j < m_size_out; j++)
			//	{
			//		for (int i = 0; i < m_size_in; i++)
			//			outputs[k][j] += m_weights[i][j] * input[k][i];
			//		outputs[k][j] -= m_biases[j];
			//		if (this->m_activation_function != nullptr)
			//			outputs[k][j] = this->m_activation_function->operator()(outputs[k][j]);
			//	}

			//	// save data 
			//	// for back propagation
			//	//return output;
			//}

			// Save output to use
			// in backpropagation
			m_output = outputs;

			return outputs;
		}
		virtual DataSet_draft<double> back_propagation(
			const DataSet_draft<double>& errors,
			double lr = 0.01
		) override
		{
			auto& input = m_input;
			auto& output = m_output;
			auto weights_copy = m_weights;


			// get derivatives
			// from activation 
			// function
			DataSet_draft<double> derivatives = this->m_activation_function->derivative(output);
			size_t batch_size = derivatives.size()[0];

			// update weights
			Index<size_t> in_index(m_size_in.size());
			Index<size_t> out_index(m_size_out.size());
			Index<size_t> max_in_index = to_index(m_size_in);
			Index<size_t> max_out_index = to_index(m_size_out);
			for (; out_index != max_out_index; out_index.increment({}, max_out_index))
			{
				for (; in_index != max_in_index; in_index.increment({}, max_in_index))
				{
					double derivative_by_weight = 0;
					for (size_t batch = 0; batch < batch_size; batch++)
					{
						Index<size_t> batch_out_index = Index<size_t>::join({ batch }, out_index);
						Index<size_t> batch_in_index = Index<size_t>::join({ batch }, in_index);
						derivative_by_weight += errors.at_index(batch_out_index) * derivatives.at_index(batch_out_index) * input.at_index(batch_in_index);
					}
					Index<size_t> weight_index = Index<size_t>::join(in_index, out_index);
					m_weights.at_index(weight_index) -= lr * derivative_by_weight;

				}
				double derivative_by_bias = 0;
				for (size_t batch = 0; batch < batch_size; batch++)
				{
					Index<size_t> batch_out_index = Index<size_t>::join({ batch }, out_index);
					derivative_by_bias -= errors.at_index(batch_out_index) * derivatives.at_index(batch_out_index);
				}
				m_biases.at_index(out_index) -= lr * derivative_by_bias;
			}

			/*for (int j = 0; j < m_size_out; j++)
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
			}*/

			// Errors on this layer
			// (they are calculated by errors
			// from the next layer)
			DataSet_draft<double> errors_here(Size<size_t>::join({ batch_size }, m_size_in));



			in_index = Index<size_t>(m_size_in.size());
			out_index = Index<size_t>(m_size_out.size());
			for (size_t batch = 0; batch < errors.size()[0]; batch++)
			{
				for (; in_index < max_in_index; in_index.increment({}, max_in_index))
				{
					Index<size_t> batch_in_index = Index<size_t>::join({ batch }, in_index);
					double error_batch_in = 0;

					for (; out_index < max_out_index; out_index.increment({}, max_out_index))
					{
						Index<size_t> batch_out_index = Index<size_t>::join({ batch }, out_index);
						Index<size_t> in_out_index = Index<size_t>::join(in_index, out_index);
						error_batch_in += errors.at_index(batch_out_index) * derivatives.at_index(batch_out_index) * weights_copy.at_index(in_out_index);
					}
					errors_here.at_index(batch_in_index) = error_batch_in;
				}
			}

			return errors_here;
		}

		const DataSet_draft<_DT_OUT>& get_weights() const
		{
			return m_weights;
		}
		DataSet_draft<_DT_OUT>& get_weights()
		{
			return m_weights;
		}

		const DataSet_draft<_DT_OUT>& get_biases() const
		{
			return m_biases;
		}
		DataSet_draft<_DT_OUT>& get_biases()
		{
			return m_biases;
		}


	private:
		void fill_weights_random()
		{
			std::default_random_engine random_engine;
			std::normal_distribution distribution(0., sqrt(2. / (m_size_in.plain_size() + m_size_out.plain_size())));
			auto generator = std::bind(distribution, random_engine);
			for (int i = 0; i < m_weights.access_data().size(); i++)
			{
				m_weights.access_data()[i] = generator();
				if (i < m_biases.access_data().size())
					m_biases.access_data()[i] = generator();
			}
		}
	};
#elif defined(DRAFT_DATASET_2_0_0_PRERELEASE)
	// 1-dimentional for now
	template<typename _DT_IN, typename _DT_OUT = _DT_IN>
	class FCLayer : public Layer<_DT_IN, _DT_OUT>
	{
		Size<size_t> m_size_in;
		Size<size_t> m_size_out;
		DataSet<_DT_OUT> m_weights;
		DataSet<_DT_OUT> m_biases;

		// cached data
		DataSet<_DT_IN> m_input;
		DataSet<_DT_OUT> m_output;
	public:
		FCLayer(const Size<size_t>& size_in, const Size<size_t>& size_out)
			: m_weights(Size<>::join(size_in, size_out)), m_biases(size_out),
			m_size_in(size_in), m_size_out(size_out)
		{
			fill_weights_random();
		}

		FCLayer(const Size<size_t>& size_in_out)
			: m_weights(size_in_out), m_biases(Size<size_t>{ size_in_out[1] }),
			m_size_in(Size<size_t>{ size_in_out[0] }), m_size_out(Size<size_t>{ size_in_out[1] })
		{
			fill_weights_random();
		}

		virtual DataSet<_DT_OUT> operator() (const DataSet<_DT_IN>& input) override
		{

			// Save input to use
			// in backpropagation
			m_input = input;
			size_t batch_count = input.get_size()[0];

			Size<size_t> outputs_size = Size<size_t>::join({ batch_count }, m_size_out);
			DataSet<_DT_OUT> outputs(outputs_size);

			Index<size_t> in_index(m_size_in.size());
			Index<size_t> out_index(m_size_out.size());
			Index<size_t> max_in_index = to_index(m_size_in);
			Index<size_t> max_out_index = to_index(m_size_out);
			for (size_t batch = 0; batch < batch_count; batch++)
			{
				for (; out_index < max_out_index; out_index.increment({}, max_out_index))
				{
					Index<size_t> batch_out_index = Index<size_t>::join({ batch }, out_index);
					for (; in_index < max_in_index; in_index.increment({}, max_in_index))
					{
						Index<size_t> in_out_index = Index<size_t>::join(in_index, out_index);
						Index<size_t> batch_in_index = Index<size_t>::join({ batch }, in_index);
						outputs.at_index(batch_out_index) += m_weights.at_index(in_out_index) * input.at_index(batch_in_index);
					}
					outputs.at_index(batch_out_index) -= m_biases.at_index(out_index);
				}
			}
			outputs = this->m_activation_function->operator()(outputs);

			//for (int k = 0; k < outputs.get_size()[0]; k++)
			//{
			//	//DataRow<_DT_OUT> output(m_size_out);
			//	for (int j = 0; j < m_size_out; j++)
			//	{
			//		for (int i = 0; i < m_size_in; i++)
			//			outputs[k][j] += m_weights[i][j] * input[k][i];
			//		outputs[k][j] -= m_biases[j];
			//		if (this->m_activation_function != nullptr)
			//			outputs[k][j] = this->m_activation_function->operator()(outputs[k][j]);
			//	}

			//	// save data 
			//	// for back propagation
			//	//return output;
			//}

			// Save output to use
			// in backpropagation
			m_output = outputs;

			return outputs;
		}
		virtual DataSet<_DT_IN> back_propagation(
			const DataSet<_DT_OUT>& errors,
			double lr = 0.01
		) override
		{
			auto& input = m_input;
			auto& output = m_output;
			auto weights_copy = m_weights;


			// get derivatives
			// from activation 
			// function
			DataSet<_DT_OUT> derivatives = this->m_activation_function->derivative(output);
			size_t batch_size = derivatives.size()[0];

			// update weights
			Index<size_t> in_index(m_size_in.size());
			Index<size_t> out_index(m_size_out.size());
			Index<size_t> max_in_index = to_index(m_size_in);
			Index<size_t> max_out_index = to_index(m_size_out);
			for (; out_index != max_out_index; out_index.increment({}, max_out_index))
			{
				for (; in_index != max_in_index; in_index.increment({}, max_in_index))
				{
					double derivative_by_weight = 0;
					for (size_t batch = 0; batch < batch_size; batch++)
					{
						Index<size_t> batch_out_index = Index<size_t>::join({ batch }, out_index);
						Index<size_t> batch_in_index = Index<size_t>::join({ batch }, in_index);
						derivative_by_weight += errors.at_index(batch_out_index) * derivatives.at_index(batch_out_index) * input.at_index(batch_in_index);
					}
					Index<size_t> weight_index = Index<size_t>::join(in_index, out_index);
					m_weights.at_index(weight_index) -= lr * derivative_by_weight;

				}
				double derivative_by_bias = 0;
				for (size_t batch = 0; batch < batch_size; batch++)
				{
					Index<size_t> batch_out_index = Index<size_t>::join({ batch }, out_index);
					derivative_by_bias -= errors.at_index(batch_out_index) * derivatives.at_index(batch_out_index);
				}
				m_biases.at_index(out_index) -= lr * derivative_by_bias;
			}

			/*for (int j = 0; j < m_size_out; j++)
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
			}*/

			// Errors on this layer
			// (they are calculated by errors
			// from the next layer)
			DataSet<_DT_IN> errors_here(Size<size_t>::join({ batch_size }, m_size_in));



			in_index = Index<size_t>(m_size_in.size());
			out_index = Index<size_t>(m_size_out.size());
			for (size_t batch = 0; batch < errors.size()[0]; batch++)
			{
				for (; in_index < max_in_index; in_index.increment({}, max_in_index))
				{
					Index<size_t> batch_in_index = Index<size_t>::join({ batch }, in_index);
					double error_batch_in = 0;

					for (; out_index < max_out_index; out_index.increment({}, max_out_index))
					{
						Index<size_t> batch_out_index = Index<size_t>::join({ batch }, out_index);
						Index<size_t> in_out_index = Index<size_t>::join(in_index, out_index);
						error_batch_in += errors.at_index(batch_out_index) * derivatives.at_index(batch_out_index) * weights_copy.at_index(in_out_index);
					}
					errors_here.at_index(batch_in_index) = error_batch_in;
				}
			}

			return errors_here;
			}

		const DataSet<_DT_OUT>& get_weights() const
		{
			return m_weights;
		}
		DataSet<_DT_OUT>& get_weights()
		{
			return m_weights;
		}

		const DataSet<_DT_OUT>& get_biases() const
		{
			return m_biases;
		}
		DataSet<_DT_OUT>& get_biases()
		{
			return m_biases;
		}


	private:
		void fill_weights_random()
		{
			std::default_random_engine random_engine;
			std::normal_distribution distribution(0., sqrt(2. / (m_size_in.plain_size() + m_size_out.plain_size())));
			auto generator = std::bind(distribution, random_engine);
			for (int i = 0; i < m_weights.access_data().size(); i++)
			{
				m_weights.access_data()[i] = generator();
				if (i < m_biases.access_data().size())
					m_biases.access_data()[i] = generator();
			}
		}
	};
#else
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



#endif 

} // namespace nyann 