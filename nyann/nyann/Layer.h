#pragma once


// For all the framework configurations
#include "_config.h"

#include "dataset.h"
#include "ActivationFunction.h"
#include "Optimizer.h"
#include "utils/Serializer.h"


namespace nyann {

	template<typename _DT_IN, typename _DT_OUT = _DT_IN>
	class Layer : public Serializable<_DT_IN>
	{
	protected:
		ActivationFunction<_DT_IN>* m_activation_function;

	public:
		Layer()
			: m_activation_function(new LinearActivation<_DT_OUT>()) {}
		virtual DataSet<_DT_OUT> operator() (const DataSet<_DT_IN>&) = 0;
#ifdef OPTIMIZER
		virtual DataSet<double> back_propagation(
			const DataSet<double>& errors,
			const Optimizer<double>& optimizer) = 0;
		virtual DataSet<double> back_propagation(
			const DataSet<double>& errors,
			double lr = 0.01)
		{
			throw DeprecationError("Currently used back_propagation iterface is deprecated.");
		}
#else
		virtual DataSet<double> back_propagation(
			const DataSet<double>& errors,
			double lr = 0.01) = 0;
#endif
		

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