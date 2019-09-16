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

	template<typename _DT>
	DataRow<_DT> abs(const DataRow<_DT>& datarow)
	{
		DataRow<_DT> result = datarow;
		for (int i = 0; i < result.size(); i++)
			result[i] = ::abs(result[i]);
		return result;
	}


	template<typename _DT>
	DataSet<_DT> abs(const DataSet<_DT>& dataset)
	{
		DataSet<_DT> result = dataset;
		for (auto& row : dataset)
			row = abs(row);
		return result;
	}
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

	// used in evaluation of results
	template<typename _DT>
	double operator-(const DataSet<_DT>& left, const DataSet<_DT>& right)
	{
		if (left.size() != right.size())
			throw DifferentSizeError();

		double error = 0;
		for (int i = 0; i < left.size(); i++)
			for (int j = 0; j < left.front().size(); j++)
				error += left[i][j] - right[i][j];
		return error;
	}

} // namespace nyann


// include subclasses of DataSet
#include "DataSet/TrainDataSet.h"