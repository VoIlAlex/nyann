#pragma once

namespace nyann {

	template<typename _DT>
	class ActivationFunction
	{
	public:
		virtual _DT operator()(const _DT& sum) = 0;
		virtual _DT derivative(const _DT& y) = 0;
	};

} // namespace nyann


// Subclasses of the ActivationFunction class
#include "ActivationFunction/BinaryActivation.h"
#include "ActivationFunction/ReLU.h"