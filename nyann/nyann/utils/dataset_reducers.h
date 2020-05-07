#pragma once


// For all the framework configurations
#include "../_config.h"

#include "Index.h"
#include "../dataset.h"
#include "../DataSet/DataSetReducer.h"

#include <functional>


namespace nyann {

	template<typename _DT>
	class LambdaReducer : public DataSetReducer<_DT>
	{
		std::function<_DT(const std::vector<_DT>&, const Size<size_t>&)> m_lambda;

	public:
		LambdaReducer(const std::function<_DT(const std::vector<_DT>&, const Size<size_t>&)>& lambda)
			: m_lambda(lambda)
		{}

		_DT operator()(const std::vector<_DT>& data, const Size<size_t>& size) const
		{
			return m_lambda(data, size);
		}
	};

	template<typename _DT>
	class ForEachReducer : public DataSetReducer<_DT>
	{
		std::function<_DT(const _DT& left, const _DT& right)> m_reducer;

	public:
		ForEachReducer(const std::function<_DT(const _DT& left, const _DT& right)>& reducer)
			: m_reducer(reducer)
		{}

		_DT operator()(const std::vector<_DT>& data, const Size<size_t>& size) const
		{
			_DT result = _DT();
			for (auto& val : data)
				result = m_reducer(result, val);
			return result;
		}
	};

	template<typename _DT>
	class AddReducer : public DataSetReducer<_DT>
	{
	public:
		_DT operator()(const std::vector<_DT>& data, const Size<size_t>& size) const
		{
			_DT result = _DT();
			for (auto& val : data)
				result += val;
			return result;
		}
	};

	template<typename _DT>
	class MultReducer : public DataSetReducer<_DT>
	{
	public:
		_DT operator()(const std::vector<_DT>& data, const Size<size_t>& size) const
		{
			_DT result = data[0];
			for (auto it = data.begin() + 1; it != data.end(); it++)
				result *= *it;
			return result;
		}
	};

	template<typename _DT>
	class AverageReducer : public DataSetReducer<_DT>
	{
	public:
		_DT operator()(const std::vector<_DT>& data, const Size<size_t>& size) const
		{
			_DT result = 0;
			for (int i = 0; i < data.size(); i++)
				result = (result * i + data[i]) / (i + 1);
			return result;
		}
	};
}