#pragma once

#include <initializer_list>
#include <vector>

#include "..//DataSet.h" // for DataSet

namespace nyann {

	template<typename _DT>
	class TrainDataSet : public std::vector<DataSet<_DT>>
	{
	public:
		using std::vector<DataSet<_DT>>::vector;
	};

} // namespace nyann