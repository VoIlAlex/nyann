#pragma once


// For all the framework configurations
#include "_config.h"

#include "dataset.h"


namespace nyann {

	template<typename _DT>
	class ActivationFunction
	{
	public:
		virtual _DT operator()(const _DT& sum) = 0;
		virtual _DT derivative(const _DT& y) = 0;
		virtual DataSet<_DT> operator()(const DataSet<_DT>& sums)
		{
			DataSet<_DT> results = DataSet<_DT>::ones_like(sums);
			for (int i = 0; i < sums.data().size(); i++)
				results.access_data()[i] = operator()(sums.data()[i]);
			return results;
		}
		virtual DataSet<_DT> derivative(const DataSet<_DT>& Y)
		{
			DataSet<_DT> results = DataSet<_DT>::ones_like(Y);
			for (int i = 0; i < Y.data().size(); i++)
				results.access_data()[i] = derivative(Y.data()[i]);
			return results;
		}
		// TODO: save activation function 
		// identifier
		virtual void save(const std::string& filename) const
		{
			throw std::runtime_error("Not implemented error");
			return;
		}
	};
} // namespace nyann


// Subclasses of the ActivationFunction class
#include "ActivationFunction/BinaryActivation.h"
#include "ActivationFunction/BipolarActivation.h"
#include "ActivationFunction/ReLUActivation.h"
#include "ActivationFunction/SigmoidActivation.h"
#include "ActivationFunction/LinearActivation.h"