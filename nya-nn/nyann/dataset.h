#pragma once

#include <initializer_list>
#include <vector>

// include subclasses of DataSet
#include "DataSet/TrainDataSet.h"

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
} // namespace nyann