#pragma once


// For all the framework configurations
#include "../_config.h"

#include "../ActivationFunction.h"

#include <math.h>


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
	};

} // namespace nyann