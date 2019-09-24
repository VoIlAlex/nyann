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
		DataSet<_DT> get_input() const
		{
			DataSet<_DT> input;
			for (auto it = this->begin(); it != this->end(); it++)
				input.push_back((*it)[0]);
			return input;
		}
		DataSet<_DT> get_output() const
		{
			DataSet<_DT> output;
			for (auto it = this->begin(); it != this->end(); it++)
				output.push_back((*it)[1]);
			return output;
		}
	};

} // namespace nyann