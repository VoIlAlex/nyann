#pragma once

#include "..//ActivationFunction.h"

namespace nyann {

	template<typename _DT>
	class ReLU : public ActivationFunction<_DT>
	{

		DataSet<_DT> m_outputs;
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
	};

} // namespace nyann