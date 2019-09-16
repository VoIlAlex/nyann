#pragma once

#include "dataset.h"

namespace nyann
{
	template<typename _DT_IN, typename _DT_OUT = _DT_IN>
	class Layer
	{
	public:
		Layer() = delete;
		virtual DataSet<_DT_OUT> operator() (const DataSet& <_DT_IN>);
	};

} // namespace nyann


// include subclasses of Layer
#include "Layer/FCLayer.h"
