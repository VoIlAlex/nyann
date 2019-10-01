#pragma once

#include "dataset.h"

namespace nyann {

	template<typename _DT>
	class ActivationFunction
	{
	public:
		virtual _DT operator()(const _DT& sum) = 0;
		virtual _DT derivative(const _DT& y) = 0;
		virtual DataSet<_DT> operator()(const DataSet<_DT>& sums) = 0;
		virtual DataSet<_DT> derivative(const DataSet<_DT>& Y) = 0;
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
#include "ActivationFunction/ReLU.h"