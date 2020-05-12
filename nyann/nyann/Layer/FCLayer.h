#pragma once


// For all the framework configurations
#include "../_config.h"

#include "../Layer.h" // for Layer
#include "../utils.h" // for Size
#include "../dataset.h" // for DataSet

#include <vector>
#include <functional>
#include <random>
#include <fstream>
#include <sstream>
#include <iterator>
#include <string>


namespace nyann {
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
		FCLayer() {}
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
				for (out_index = Index<size_t>(m_size_out.size()); out_index.all_lower(max_out_index); out_index.increment({}, max_out_index))
				{
					Index<size_t> batch_out_index = Index<size_t>::join({ batch }, out_index);
					for (in_index = Index<size_t>(m_size_in.size()); in_index.all_lower(max_in_index); in_index.increment({}, max_in_index))
					{
						Index<size_t> in_out_index = Index<size_t>::join(in_index, out_index);
						Index<size_t> batch_in_index = Index<size_t>::join({ batch }, in_index);
						outputs.at_index(batch_out_index) += m_weights.at_index(in_out_index) * input.at_index(batch_in_index);
					}
					outputs.at_index(batch_out_index) -= m_biases.at_index(out_index);
				}
			}
			outputs = this->m_activation_function->operator()(outputs);
			m_output = outputs;

			return outputs;
		}
#ifdef OPTIMIZER
		virtual DataSet<_DT_IN> back_propagation(
			const DataSet<_DT_OUT>& errors,
			const Optimizer<_DT_OUT>& optimizer
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
			optimizer(m_weights, m_biases, derivatives, errors, input, m_size_in, m_size_out, batch_size);

			// Errors on this layer
			// (they are calculated by errors
			// from the next layer)
			DataSet<_DT_IN> errors_here(Size<size_t>::join({ batch_size }, m_size_in));


			Index<size_t> min_in_index(m_size_in.size());
			Index<size_t> min_out_index(m_size_out.size());
			Index<size_t> in_index(m_size_in.size());
			Index<size_t> out_index(m_size_out.size());
			Index<size_t> max_in_index = to_index(m_size_in);
			Index<size_t> max_out_index = to_index(m_size_out);

			for (size_t batch = 0; batch < errors.size()[0]; batch++)
			{
				for (in_index = min_in_index; in_index.all_lower(max_in_index); in_index.increment(min_in_index, max_in_index))
				{
					Index<size_t> batch_in_index = Index<size_t>::join({ batch }, in_index);
					double error_batch_in = 0;
					for (out_index = min_out_index; out_index.all_lower(max_out_index); out_index.increment(min_out_index, max_out_index))
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
#endif
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

		std::string serialize() const override
		{
			std::ostringstream result;
			DataSetSerializer<_DT_IN> data_serializer;
			VectorSerializer<size_t> size_serializer;
			result << data_serializer.serialize(m_weights) << "\n";
			result << data_serializer.serialize(m_biases) << "\n";
			result << data_serializer.serialize(m_input) << "\n";
			result << data_serializer.serialize(m_output) << "\n";
			result << size_serializer.serialize(m_size_in) << "\n";
			result << size_serializer.serialize(m_size_out);
			return result.str();
		}

		void deserialize(std::istringstream& input) override
		{
			//std::istringstream input(data);
			DataSetSerializer<_DT_IN> data_serializer;
			VectorSerializer<size_t> size_serializer;
			
			m_weights = data_serializer.deserialize(input);
			m_biases = data_serializer.deserialize(input);
			m_input = data_serializer.deserialize(input);
			m_output = data_serializer.deserialize(input);
			m_size_in = size_serializer.deserialize(input);
			m_size_out = size_serializer.deserialize(input);		
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
} // namespace nyann 