#pragma once
#include <utility>
#include "./DataSet_draft.h"

namespace nyann {
	template<typename _DT>
	class TrainDataSample_draft : public std::pair<DataSet_draft<_DT>, DataSet_draft<_DT>>
	{
	public:
		using std::pair<DataSet_draft<_DT>, DataSet_draft<_DT>>::pair;

		DataSet_draft<_DT> get_input() const
		{
			return this->first;
		}

		DataSet_draft<_DT> get_output() const
		{
			return this->second;
		}
	};


	template<typename _DT>
	class TrainDataSet_draft : public std::pair<DataSet_draft<_DT>, DataSet_draft<_DT>>
	{
	public:
		using std::pair<DataSet_draft<_DT>, DataSet_draft<_DT>>::pair;

		TrainDataSample_draft<_DT> operator[](int i)
		{
			return TrainDataSample_draft<_DT>( 
				DataSet_draft<_DT>(this->first[i]),
				DataSet_draft<_DT>(this->second[i])
			);
		}
	};


} // namespace nyann
