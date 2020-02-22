#pragma once

#include <initializer_list>
#include <vector>
#include <random>

// For all the framework configurations
#include "../_config.h"

#include "../dataset.h" // for DataSet

namespace nyann {
#ifndef DRAFT_DATASET_2_0_0_ALPHA_TEST
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
#else
	template<typename _DT>
	class TrainDataSet : public std::pair<DataSet_draft<_DT>, DataSet_draft<_DT>>
	{
	public:
		using std::pair<DataSet<_DT>>::pair;
		DataSet_draft<_DT> get_input() const
		{
			return this->first;
		}
		DataSet_draft<_DT> get_output() const
		{
			return this->second;
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
				{
					swap(this->first[idx_1].value(), this->first[idx_2].value());
					swap(this->second[idx_1].value(), this->second[idx_2].value());
				}
					
			}
		}
	};
#endif
} // namespace nyann