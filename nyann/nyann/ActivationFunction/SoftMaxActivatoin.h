#pragma once


// For all the framework configurations
#include "../_config.h"

#include "../ActivationFunction.h"

namespace nyann
{

#ifdef DRAFT_DATASET_2_0_0_ALPHA_TEST
// TODO: Test SoftMax
template <typename _DT>
class SoftMax : public ActivationFunction<_DT>
{
public:
	_DT operator()(const _DT &sum) override
	{
		throw NotImplementedError("Single processing isn't supported by SoftMax");
	}
	_DT derivative(const _DT &y) override
	{
		return y * (1 - y);
	}

	DataSet<_DT> operator()(const DataSet<_DT> &sums) override
	{
		DataSet<_DT> results = DataSet<_DT>::ones_like(sums);
		_DT sum_of_exponents;
		_DT result;
		for (int i = 0; i < sums.get_size()[0]; i++)
			for (int j = 0; j < sums.get_size()[1]; j++)
			{
				sum_of_exponents = 0;
				for (int k = 0; k < sums.get_size()[1]; k++)
					sum_of_exponents += exp(sums[i][k]);
				result = exp(sums[i][j]) / sum_of_exponents;
				results[i][j] = result;
			}
		return results;
	}
	DataSet<_DT> derivative(const DataSet<_DT> &Y) override
	{
		DataSet<_DT> results = DataSet<_DT>::ones_like(Y);

		for (int i = 0; i < Y.get_size()[0]; i++)
			for (int j = 0; j < Y.get_size()[1]; j++)
				results[i][j] = derivative(Y[i][j]);

		return results;
	}
};
#elif defined(DRAFT_DATASET_2_0_0_PRERELEASE)
	template <typename _DT>
	class SoftMax : public ActivationFunction<_DT>
	{
	public:
		_DT operator()(const _DT &sum) override
		{
			throw NotImplementedError("Single processing isn't supported by SoftMax");
		}
		_DT derivative(const _DT &y) override
		{
			return y * (1 - y);
		}

		DataSet<_DT> operator()(const DataSet<_DT> &sums) override
		{
			DataSet<_DT> results = DataSet<_DT>::ones_like(sums);
			_DT sum_of_exponents = _DT();
			_DT exponent;
			for (int i = 0; i < sums.data().size(); i++)
			{
				exponent = exp(sums.data()[i]);
				results.access_data()[i] = exponent;
				sum_of_exponents += exponent;
			}
			for (int i = 0; i < results.data().size(); i++)
				results.access_data()[i] /= sum_of_exponents;
			return results;
		}
	};
#endif

} // namespace nyann