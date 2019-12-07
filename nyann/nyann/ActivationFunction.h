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
#ifdef DRAFT_DATASET_2_0_0_ALPHA_TEST
			for (auto it = sums.begin(-1); it != sums.end(-1); it++)
			{
				// TODO: update for the new style DataSet
			}
#else
			for (int i = 0; i < sums.get_size()[0]; i++)
				for (int j = 0; j < sums.get_size()[1]; i++)
					results[i][j] = operator()(sums[i][j]);
#endif
			return results;
		}
		virtual DataSet<_DT> derivative(const DataSet<_DT>& Y)
		{
			DataSet<_DT> results = DataSet<_DT>::ones_like(Y);
#ifdef DRAFT_DATASET_2_0_0_ALPHA_TEST
			for (auto it = sums.begin(-1); it != sums.end(-1); it++)
			{
				// TODO: update for the new style DataSet
			}
#else
			for (int i = 0; i < Y.get_size()[0]; i++)
				for (int j = 0; j < Y.get_size()[1]; i++)
					results[i][j] = derivative(Y[i][j]);
#endif
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
#include "ActivationFunction/ReLU.h"
#include "ActivationFunction/SigmoidActivation.h"