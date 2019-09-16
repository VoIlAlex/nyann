#pragma once

#include <initializer_list>
#include <vector>

#include "utils/exceptions.h"

namespace nyann {
	template<typename _DT>
	class DataRow : public std::vector<_DT>
	{
	public:
		using std::vector<_DT>::vector;
	};


	template<typename _DT>
	class DataSet : public std::vector<DataRow<_DT>>
	{
	public:
		using std::vector<DataRow<_DT>>::vector;
	};

	////////////////////////////
	// Operators overloadings //
	////////////////////////////
	template<typename _DT>
	DataRow<_DT> operator+(const DataRow<_DT>& left, const DataRow<_DT>& right)
	{
		if (left.size() != right.size())
			throw DifferentSizeError();

		DataRow<_DT> result(left.size());
		for (int i = 0; i < right.size(); i++)
			result[i] = left[i] + right[i];
		return result;
	}

	template<typename _DT>
	DataRow<_DT> operator-(const DataRow<_DT>& left, const DataRow<_DT>& right)
	{
		if (left.size() != right.size())
			throw DifferentSizeError();

		DataRow<_DT> result(left.size());
		for (int i = 0; i < result.size(); i++)
			result[i] = left[i] - right[i];
		return result;
	}

	template<typename _DT>
	DataRow<_DT> operator-(const DataRow<_DT>& obj)
	{
		DataRow<_DT> result(obj);

		for (int i = 0; i < obj.size(); i++)
			result[i] = -result[i];

		return result;
	}

} // namespace nyann


// include subclasses of DataSet
#include "DataSet/TrainDataSet.h"