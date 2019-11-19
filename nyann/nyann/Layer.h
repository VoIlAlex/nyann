#pragma once

#include "dataset.h"
#include "ActivationFunction.h"

namespace nyann
{
	template<typename _DT_IN, typename _DT_OUT = _DT_IN>
	class Layer
	{
	protected:
		ActivationFunction<_DT_IN>* m_activation_function;
	public:
		Layer()
			: m_activation_function(nullptr) {}
		virtual DataSet<_DT_OUT> operator() (const DataSet<_DT_IN>&) = 0;
		virtual DataRow<_DT_OUT> operator() (const DataRow<_DT_IN>&, bool save = true) = 0;
		// 1-dimensional for now
		virtual std::vector<double> back_propagation(
			const std::vector<double>& errors,
			const std::vector<double>& derivitives, // d(yj) / d(Sj) - caused by activation function
			double lr = 0.01) = 0;
		virtual DataSet<double> back_propagation(
			const DataSet<double>& errors,
			double lr = 0.01) = 0;
		void add_activation_function(ActivationFunction<_DT_IN>* activation_function)
		{
			m_activation_function = activation_function;
		}
		~Layer()
		{
			if (m_activation_function != nullptr)
				delete m_activation_function;
		}
	};

} // namespace nyann


// include subclasses of Layer
#include "Layer/FCLayer.h"
#include "Layer/ConvLayer1D.h"