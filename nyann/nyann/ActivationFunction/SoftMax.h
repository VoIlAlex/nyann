#pragma once

#include "../ActivationFunction.h"

namespace nyann
{

// TODO: Test SoftMax
template <typename _DT>
class SoftMax : public ActivationFunction<_DT>
{
public:
	_DT operator()(const _DT &sum) override
	{
		throw NotImplementedError("Single processing isn't supported");
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

} // namespace nyann