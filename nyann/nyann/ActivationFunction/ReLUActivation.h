#pragma once

// For all the framework configurations
#include "../_config.h"

#include "..//ActivationFunction.h"

namespace nyann {

	template<typename _DT>
	class ReLU : public ActivationFunction<_DT>
	{
		double m_k;
	public:
		ReLU(double k = 0.2)
			: m_k(k)
		{}
		_DT operator()(const _DT& sum)
		{
			return (sum > 0 ? sum : m_k * sum);
		}
		/*DataRow<_DT> operator()(const DataRow<_DT>& sums)
		{
			m_outputs.push_back(sums);

			DataRow<_DT> y;
			for (auto sum : sums)
			{
				y.push_back(sum > 0 ? sum : m_k * sum);
			}

			return y;
		}*/
		_DT derivative(const _DT& y) override
		{
			return (y > 0 ? 1 : m_k);
		}
		//DataSet<_DT> operator()(const DataSet<_DT>& sums) override
		//{
		//	// TODO: implementation
		//	return {};
		//}
		//virtual DataSet<_DT> derivative(const DataSet<_DT>& Y) override
		//{
		//	// TODO: implementation
		//	return {};
		//}
	};

} // namespace nyann