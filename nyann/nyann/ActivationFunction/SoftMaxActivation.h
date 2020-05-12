#pragma once


// For all the framework configurations
#include "../_config.h"

#include "../ActivationFunction.h"


namespace nyann {

	template <typename _DT>
	class SoftMaxActivation : public ActivationFunction<_DT>
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

} // namespace nyann