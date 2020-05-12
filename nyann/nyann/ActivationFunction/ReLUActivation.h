#pragma once


// For all the framework configurations
#include "../_config.h"

#include "../ActivationFunction.h"


namespace nyann {

	template<typename _DT>
	class ReLUActivation : public ActivationFunction<_DT>
	{
		double m_k;

	public:
		ReLUActivation(double k = 0.0)
			: m_k(k)
		{}

		_DT operator()(const _DT& sum)
		{
			return (sum > 0 ? sum : m_k * sum);
		}

		_DT derivative(const _DT& y) override
		{
			return (y > 0 ? 1 : m_k);
		}
	};

} // namespace nyann