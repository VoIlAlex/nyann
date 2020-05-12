#pragma once


// For all the framework configurations
#include "../_config.h"

#include "../Optimizer.h" // for Optimizer
#include "../utils/Index.h"
#include "../utils/conversion.h"


namespace nyann {

	template<typename _DT>
	class SGDOptimizer : public Optimizer<_DT>
	{
	public:
		SGDOptimizer(_DT lr)
			: Optimizer<_DT>(lr)
		{}

		void operator()(
			DataSet<_DT>& weights, 
			DataSet<_DT>& biases, 
			const DataSet<_DT>& derivatives, 
			const DataSet<_DT>& errors, 
			const DataSet<_DT>& input,
			const Size<>& size_in,
			const Size<>& size_out,
			int batch_size
		) const
		{
			Index<size_t> min_in_index(size_in.size());
			Index<size_t> min_out_index(size_out.size());
			Index<size_t> in_index(size_in.size());
			Index<size_t> out_index(size_out.size());
			Index<size_t> max_in_index = to_index(size_in);
			Index<size_t> max_out_index = to_index(size_out);
			for (out_index = min_out_index; out_index.all_lower(max_out_index); out_index.increment(min_out_index, max_out_index))
			{
				for (in_index = min_in_index; in_index.all_lower(max_in_index); in_index.increment(min_in_index, max_in_index))
				{
					double derivative_by_weight = 0;
					for (size_t batch = 0; batch < batch_size; batch++)
					{
						Index<size_t> batch_out_index = Index<size_t>::join({ batch }, out_index);
						Index<size_t> batch_in_index = Index<size_t>::join({ batch }, in_index);
						derivative_by_weight += errors.at_index(batch_out_index) * derivatives.at_index(batch_out_index) * input.at_index(batch_in_index);
					}
					Index<size_t> weight_index = Index<size_t>::join(in_index, out_index);
					weights.at_index(weight_index) -= this->m_lr * derivative_by_weight;

				}
				double derivative_by_bias = 0;
				for (size_t batch = 0; batch < batch_size; batch++)
				{
					Index<size_t> batch_out_index = Index<size_t>::join({ batch }, out_index);
					derivative_by_bias -= errors.at_index(batch_out_index) * derivatives.at_index(batch_out_index);
				}
				biases.at_index(out_index) -= this->m_lr * derivative_by_bias;
			}
		}
	};

} // namespace nyann