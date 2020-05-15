#pragma once

// For all the framework configurations
#include "../_config.h"

#include "Index.h"
#include "../dataset.h"
#include "../DataSet/DataSetOperation.h"

#include <functional>


namespace nyann {

	template<typename _DT>
	class LambdaOperation : public DataSetOperation<_DT>
	{
		std::function<void(std::vector<_DT>&, Size<>&)> m_lambda;

	public:
		LambdaOperation(const std::function<void(std::vector<_DT>&, Size<>&)>& lambda)
			: m_lambda(lambda)
		{}

		void operator()(std::vector<_DT>& data, Size<size_t>& size) const override
		{
			m_lambda(data, size);
		}
	};

	template<typename _DT>
	class ForEachOperation : public DataSetOperation<_DT>
	{
		std::function<void(_DT&)> m_function;
	public:
		ForEachOperation(const std::function<void(_DT&)>& function)
			: m_function (function)
		{}

		void operator()(std::vector<_DT>& data, Size<size_t>& size) const override
		{
			for (_DT& item : data)
				m_function(item);
		}
	};

	template<typename _DT>
	class PowerOperation : public DataSetOperation<_DT>
	{
		_DT m_power;

	public:
		PowerOperation(const _DT &power)
			: m_power(power)
		{}

		void operator()(std::vector<_DT>& data, Size<size_t>& size) const override
		{
			for (_DT& item : data)
				item = pow(item, m_power);
		}
	};

	template<typename _DT>
	class MultOperation : public DataSetOperation<_DT>
	{
		_DT m_coefficient;

	public:
		MultOperation(const _DT& coefficient)
			: m_coefficient(coefficient)
		{}

		void operator()(std::vector<_DT>& data, Size<size_t>& size) const override
		{
			for (_DT& item : data)
				item *= m_coefficient;
		}

	};

	template<typename _DT>
	class AbsOperation : public DataSetOperation<_DT>
	{
	public:
		void operator()(std::vector<_DT>& data, Size<size_t>& size) const override
		{
			for (_DT& item : data)
				item = abs(item);
		}

	};

} // namespace nyann