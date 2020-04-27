#pragma once


// For all the framework configurations
#include "_config.h"


namespace nyann {

	class Loss {};

} // namespace nyann


// include subclasses of Loss
#include "Loss/MSELoss.h"