#pragma once

#include "..//ActivationFunction.h"


namespace nyann {

	template<typename _DT>
	class BipolarActivation : public ActivationFunction<_DT>
	{
	public:
		_DT operator()(const _DT& sum) override
		{
			return (sum > 0 ? 1 : -1);
		}
		_DT derivative(const _DT& y) override
		{
			return 1.0;
		}
		DataSet<_DT> operator()(const DataSet<_DT>& sums) override
		{

			DataSet<_DT> results = DataSet<_DT>::ones_like(sums);
#ifdef DRAFT_DATASET_2_0_0_ALPHA_TEST
			for (auto it = sums.begin(-1); it != sums.end(-1); it++)
			{
				// TODO: update for the new style DataSet
			}
#else
			for (int i = 0; i < sums.get_size()[0]; i++)
				for (int j = 0; j < sums.get_size()[1]; i++)
					results[i][j] = operator()(sums[i][j]);
#endif
			return results;

		};
		DataSet<_DT> derivative(const DataSet<_DT>& Y) override
		{
			DataSet<_DT> results = DataSet<_DT>::ones_like(Y);
#ifdef DRAFT_DATASET_2_0_0_ALPHA_TEST
			for (auto it = sums.begin(-1); it != sums.end(-1); it++)
			{
				// TODO: update for the new style DataSet
			}
#else
			for (int i = 0; i < Y.get_size()[0]; i++)
				for (int j = 0; j < Y.get_size()[1]; i++)
					results[i][j] = derivative(Y[i][j]);
#endif
			return results;
		}
	};

} // namespace nyann