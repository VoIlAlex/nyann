#pragma once


// For all the framework configurations
#include "_config.h"

#include "DataSet.h"

#include <sstream>


namespace nyann {

	template<typename _DT = double>
	class Optimizer : public Serializable<std::string>
	{
	protected:
		_DT m_lr;

	public:
		Optimizer(_DT lr)
			: m_lr(lr)
		{}

		virtual void operator()(
			DataSet<_DT>& weights,
			DataSet<_DT>& biases,
			const DataSet<_DT>& derivatives,
			const DataSet<_DT>& errors,
			const DataSet<_DT>& input,
			const Size<>& size_in,
			const Size<>& size_out,
			int batch_size) const = 0;

		std::string serialize() const override
		{
			std::ostringstream result;
			result << m_lr;
			return result.str();
		}

		void deserialize(std::istringstream& data) override
		{
			std::string raw_lr;
			std::getline(data, raw_lr);
			m_lr = to_type<_DT>(raw_lr);
		}

	};

	

} // namespace nyann


// include subclasses of Optimizer
#include "Optimizer/SGDOptimizer.h"