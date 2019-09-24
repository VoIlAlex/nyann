#pragma once

#include <initializer_list>
#include <vector>
#include <random>

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
		void shuffle()
		{
			std::uniform_int_distribution<> distr(0, this->size() - 1);
			std::default_random_engine engine;
			for (int i = 0; i < this->size(); i++)
			{
				int idx_1 = distr(engine);
				int idx_2 = distr(engine);
				if (idx_1 != idx_2)
					swap(this->operator[](idx_1), this->operator[](idx_2));
			}
		}
	};

} // namespace nyann