#pragma once

#include <math.h>

// For all the framework configurations
#include "../_config.h"

#include "..//ActivationFunction.h"


namespace nyann {

	template<typename _DT>
	class SigmoidActivation : public ActivationFunction<_DT>
	{
	public:
		_DT operator()(const _DT& sum) override
		{
			return 1.0 / (1 + exp(-sum));
		}
		_DT derivative(const _DT& y) override
		{
			return y * (1 - y);
		}

		/*DataSet<_DT> operator()(const DataSet<_DT>& sums) override
		{
			DataSet<_DT> results = DataSet<_DT>::ones_like(sums);
#ifdef DRAFT_DATASET_2_0_0_ALPHA_TEST
			for (auto it = sums.begin(-1); it != sums.end(-1); it++)
				results.push_to(it.location(), this->operator()(*it));
#endif
			return results;
		}
		DataSet<_DT> derivative(const DataSet<_DT>& Y) override
		{
			DataSet<_DT> results = DataSet<_DT>::ones_like(Y);
#ifdef DRAFT_DATASET_2_0_0_ALPHA_TEST
			for (auto it = Y.begin(-1); it != Y.end(-1); it++)
				results.push_to(it.location(), this->derivative(*it));
#endif
			return results;
		}*/
	};

} // namespace nyann