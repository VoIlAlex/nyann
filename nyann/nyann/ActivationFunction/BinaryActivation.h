#pragma once

#include "..//ActivationFunction.h"

namespace nyann {

	template<typename _DT>
	class BinaryActivation : public ActivationFunction<_DT>
	{
	public:
		_DT operator()(const _DT& sum) override
		{
			return (sum > 0 ? 1 : 0);
		}
		_DT derivative(const _DT& y) override
		{
			return 1.0;
		}
		DataSet<_DT> operator()(const DataSet<_DT>& sums) override
		{

			DataSet<_DT> results = DataSet<_DT>::ones_like(sums);
#ifdef DRAFT_DATASET
			for (auto it = sums.begin(-1); it != sums.end(-1); it++)
			{
				// TODO: update for the new style DataSet
			}
#endif
			return results;

		};
		DataSet<_DT> derivative(const DataSet<_DT>& Y) override
		{
			return{}; // TODO: implement
		}
	};

} // namespace nyann