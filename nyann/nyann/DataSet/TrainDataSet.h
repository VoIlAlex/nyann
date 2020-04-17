#pragma once

#include <initializer_list>
#include <vector>
#include <random>
#include <utility>


// For all the framework configurations
#include "../_config.h"

#include "../dataset.h" // for DataSet

namespace nyann {

#ifdef DRAFT_DATASET_2_0_0_ALPHA_TEST

#include "../drafts/DataSet_draft.h"

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


#elif defined(DRAFT_DATASET_2_0_0_PRERELEASE)
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

#else
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
#endif
} // namespace nyann