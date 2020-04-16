#pragma once
#include <utility>
#include "./DataSet_draft.h"

namespace nyann {

	template<typename _DT>
	class TrainDataSet_draft : public std::pair<DataSet_draft<_DT>, DataSet_draft<_DT>>
	{
	public:
		using std::pair<DataSet_draft<_DT>, DataSet_draft<_DT>>::pair;

		TrainDataSet_draft<_DT> operator[](int i) const
		{
			return TrainDataSet_draft<_DT>( 
				DataSet_draft<_DT>(this->first[i]),
				DataSet_draft<_DT>(this->second[i])
			);
		}

		Size<> input_size() const 
		{
			return DataSet_draft<_DT>(this->first[0]).size();
		}

		Size<> output_size() const
		{
			return DataSet_draft<_DT>(this->second[0]).size();
		}

		DataSet_draft<_DT>& get_input() 
		{
			return this->first;
		}

		const DataSet_draft<_DT>& get_input() const
		{
			return this->first;
		}

		DataSet_draft<_DT>& get_output() 
		{
			return this->second;
		}

		const DataSet_draft<_DT>& get_output() const
		{
			return this->second;
		}

		size_t samples_count() const
		{
			return DataSet_draft(this->first).size()[0];
		}
	
	};


} // namespace nyann
