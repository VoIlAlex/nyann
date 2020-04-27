#pragma once


// For all the framework configurations
#include "_config.h"


namespace nyann {

	class Optimizer {};

} // namespace nyann


// include subclasses of Optimizer
#include "Optimizer/SGDOptimizer.h"