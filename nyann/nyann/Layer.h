#pragma once


// For all the framework configurations
#include "_config.h"


#include "dataset.h"
#include "ActivationFunction.h"



namespace nyann
{
#ifndef DRAFT_DATASET_2_0_0_ALPHA_TEST
	template<typename _DT_IN, typename _DT_OUT = _DT_IN>
	class Layer
	{
	protected:
		ActivationFunction<_DT_IN>* m_activation_function;
	public:
		Layer()
			: m_activation_function(nullptr) {}
		virtual DataSet<_DT_OUT> operator() (const DataSet<_DT_IN>&) = 0;
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
#else

#include "drafts/DataSet_draft.h"
	template<typename _DT_IN, typename _DT_OUT = _DT_IN>
	class Layer
	{
	protected:
		ActivationFunction<_DT_IN>* m_activation_function;
	public:
		Layer()
			: m_activation_function(nullptr) {}
		virtual DataSet_draft<_DT_OUT> operator() (const DataSet_draft<_DT_IN>&) = 0;
		virtual DataSet_draft<double> back_propagation(
			const DataSet_draft<double>& errors,
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
#endif

} // namespace nyann


// include subclasses of Layer
#include "Layer/FCLayer.h"
#include "Layer/ConvLayer1D.h"