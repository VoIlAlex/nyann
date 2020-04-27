#pragma once


// For all the framework configurations
#include "../_config.h"

#include "../ActivationFunction.h"


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
	};

} // namespace nyann