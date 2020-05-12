#pragma once


// For all the framework configurations
#include "../_config.h"

#include "../Loss.h" // for Loss
#include "../utils/dataset_operations.h"


namespace nyann {

	template<typename _DT>
	class MSELoss : public Loss<_DT>
	{
	public:
		DataSet<_DT> operator()(const DataSet<_DT>& output, const DataSet<_DT>& target)
		{
			DataSet<_DT> diff = output - target;
			return diff;
		}

		DataSet<_DT> derivative(const DataSet<_DT>& loss)
		{
			DataSet<_DT> result = loss.execute(MultOperation<_DT>(2));
			result.execute_inplace(AbsOperation<_DT>());
			result.execute_inplace(PowerOperation<_DT>(0.5));
			return result;
		}

		
	};

} // namespace nyann