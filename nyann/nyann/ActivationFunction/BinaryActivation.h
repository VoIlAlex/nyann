#pragma once

// For all the framework configurations
#include "../_config.h"

#include "..//ActivationFunction.h"

namespace nyann {
#ifndef DRAFT_DATASET_2_0_0_ALPHA_TEST
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

			for (int i = 0; i < sums.get_size()[0]; i++)
				for (int j = 0; j < sums.get_size()[1]; i++)
					results[i][j] = operator()(sums[i][j]);
			return results;

		};
		DataSet<_DT> derivative(const DataSet<_DT>& Y) override
		{
			DataSet<_DT> results = DataSet<_DT>::ones_like(Y);
			for (int i = 0; i < Y.get_size()[0]; i++)
				for (int j = 0; j < Y.get_size()[1]; i++)
					results[i][j] = derivative(Y[i][j]);
			return results;
		}
	};
#else

#include "../drafts.h"
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
		/*DataSet_draft<_DT> operator()(const DataSet_draft<_DT>& sums) override
		{

			DataSet_draft<_DT> results = DataSet_draft<_DT>::ones_like(sums);

			for (int i = 0; i < sums.get_size()[0]; i++)
				for (int j = 0; j < sums.get_size()[1]; i++)
					results[i][j] = operator()(sums[i][j]);
			return results;

		};
		DataSet_draft<_DT> derivative(const DataSet_draft<_DT>& Y) override
		{
			DataSet_draft<_DT> results = DataSet_draft<_DT>::ones_like(Y);
			for (int i = 0; i < Y.get_size()[0]; i++)
				for (int j = 0; j < Y.get_size()[1]; i++)
					results[i][j] = derivative(Y[i][j]);
			return results;
		}*/
	};
#endif
} // namespace nyann