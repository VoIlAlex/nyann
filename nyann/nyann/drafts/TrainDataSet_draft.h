#pragma once
#include <utility>
#include "DataSet_draft.h"

namespace nyann {
	template<typename _DT>
	class TrainDataSample_draft : public std::pair<DataSet_draft<_DT>, DataSet_draft<_DT>>
	{
	public:
		using std::pair<DataSet_draft<_DT>, DataSet_draft<_DT>>::pair;

		DataSet_draft<_DT> get_input() const
		{
			return first;
		}

		DataSet_draft<_DT> get_output() const
		{
			return second;
		}
	};


	template<typename _DT>
	class TrainDataSet_draft : public std::pair<DataSet_draft<_DT>, DataSet_draft<_DT>>
	{
	public:
		using std::pair<DataSet_draft<_DT>, DataSet_draft<_DT>>::pair;

		TrainDataSample_draft<_DT> operator[](int i)
		{
			return { first[i], second[i] };
		}
	};


} // namespace nyann
