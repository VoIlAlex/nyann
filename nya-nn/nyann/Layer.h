#pragma once

#include "dataset.h"

namespace nyann
{
	template<typename _DT_IN, typename _DT_OUT = _DT_IN>
	class Layer
	{
	public:
		virtual DataSet<_DT_OUT> operator() (const DataSet<_DT_IN>&) = 0;
		virtual DataRow<_DT_OUT> operator() (const DataRow<_DT_IN>&) = 0;
		// 1-dimensional for now
		virtual std::vector<double> back_propagation(
			const std::vector<double>& errors,
			const std::vector<double>& derivitives, // d(yj) / d(Sj) - caused by activation function
			double lr = 0.01) = 0;
	};

} // namespace nyann


// include subclasses of Layer
#include "Layer/FCLayer.h"
