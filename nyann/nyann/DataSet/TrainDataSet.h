#pragma once


// For all the framework configurations
#include "../_config.h"

#include "../dataset.h" // for DataSet

#include <initializer_list>
#include <vector>
#include <random>
#include <utility>


namespace nyann {

	template<typename _DT>
	class TrainDataSet : public std::pair<DataSet<_DT>, DataSet<_DT>>
	{
	public:
		using std::pair<DataSet<_DT>, DataSet<_DT>>::pair;

		TrainDataSet<_DT> operator[](int i) const
		{
			return TrainDataSet<_DT>(
				DataSet<_DT>(this->first[i]),
				DataSet<_DT>(this->second[i])
				);
		}

		Size<> input_size() const
		{
			return DataSet<_DT>(this->first[0]).size();
		}

		Size<> output_size() const
		{
			return DataSet<_DT>(this->second[0]).size();
		}

		DataSet<_DT>& get_input()
		{
			return this->first;
		}

		const DataSet<_DT>& get_input() const
		{
			return this->first;
		}

		DataSet<_DT>& get_output()
		{
			return this->second;
		}

		const DataSet<_DT>& get_output() const
		{
			return this->second;
		}

		size_t samples_count() const
		{
			return DataSet(this->first).size()[0];
		}

	};

} // namespace nyann