#pragma once
#include <vector>

// For all the framework configurations
#include "../_config.h"

namespace nyann {

	template <typename _DT = unsigned int>
	class Index : public ::std::vector<_DT>
	{
		std::vector<_DT> m_initial_state;
	public:
		//using std::vector<int>::vector;
		Index() {}

		Index(int count, _DT value = 0)
			:
			::std::vector<_DT>::vector(count, value),
			m_initial_state(count, value)
		{}

		Index(std::initializer_list<_DT> il)
			:
			::std::vector<_DT>::vector(il),
			m_initial_state(il)
		{
		}

		Index(const Index<_DT>& index)
			:
			::std::vector<_DT>::vector(index),
			m_initial_state(index.m_initial_state)
		{}

		Index(Index<_DT>&& index) noexcept
			:
			::std::vector<_DT>::vector(std::move(index)),
			m_initial_state(std::move(index))
		{}

		Index(const std::vector<_DT>& ivec)
			:
			::std::vector<_DT>::vector(ivec),
			m_initial_state(ivec)
		{}

		Index(std::vector<_DT>&& ivec)
			:
			m_initial_state(std::move(ivec)),
			::std::vector<_DT>::vector(m_initial_state)
		{}

		std::vector<_DT>& initial_state()
		{
			return m_initial_state;
		}

		const std::vector<_DT>& initial_state() const
		{
			return m_initial_state;
		}

		bool operator==(const Index<_DT>& other) const
		{
			if (this->size() != other.size())
				return false;
			for (int i = 0; i < this->size(); i++)
				if (this->at(i) != other.at(i))
					return false;
			return true;
		}
		bool operator!=(const Index<_DT>& other) const
		{
			return !operator==(other);
		}
		bool operator<(const Index<_DT>& other) const
		{
			if (this->size() != other.size())
			{
				// If the other index
				// has the size of lower
				// dimension then it's 
				// considered as highest
				return this->size() > other.size();
			}

			// find first difference
			for (int i = 0; i < this->size(); i++)
			{
				if (this->at(i) != other.at(i))
					return this->at(i) < other.at(i);
			}
		}
		bool operator>(const Index& other) const
		{
			return !(operator<(other));
		}

		bool operator<= (const Index& other) const
		{
			return operator<(other) || operator==(other);
		}

		bool operator>= (const Index& other) const
		{
			return operator>(other) || operator==(other);
		}

		//Index& increment(const Index& max = Index())
		//{
		//	if (max == Index())
		//	{
		//		back()++;
		//		return *this;
		//	}
		//	int current_idx_item = max.size() - 1;
		//	while(current_idx_item != 0)
		//		if (at(current_idx_item) == max.at(current_idx_item))
		//		{
		//			current_idx_item--;
		//		}
		//		else
		//		{
		//			at(current_idx_item)++;
		//			for (int i = current_idx_item + 1; i < max.size(); i++)
		//				at(i) = 0;
		//			break;
		//		}
		//	if (current_idx_item == 0)
		//	{
		//		front()++;
		//		for (int i = current_idx_item + 1; i < max.size(); i++)
		//			at(i) = 0;
		//	}
		//	return *this;
		//}


		Index<_DT>& increment(const Index<_DT>& max = Index(), std::vector<_DT> steps = std::vector<_DT>())
		{
			// Invariant
			for (auto step : steps)
				if (step < 1)
					throw ::std::runtime_error("Wrong step");

			// Add missing
			for (int i = steps.size(); i < max.size(); i++)
				steps.push_back(1);

			if (max == Index<_DT>())
			{
				this->back()++;
				return *this;
			}
			int current_idx_item = max.size() - 1;
			while (current_idx_item != 0)
				if (this->at(current_idx_item) == max.at(current_idx_item) || this->at(current_idx_item) + steps.at(current_idx_item) > max.at(current_idx_item))
				{
					current_idx_item--;
				}
				else
				{
					this->at(current_idx_item) += steps.at(current_idx_item);
					for (int i = current_idx_item + 1; i < max.size(); i++)
						this->at(i) = 0;
					break;
				}
			if (current_idx_item == 0)
			{
				this->at(current_idx_item) += steps.at(current_idx_item);
				for (int i = current_idx_item + 1; i < max.size(); i++)
					this->at(i) = 0;
			}
			return *this;
		}


		Index<_DT>& decrement(const Index<_DT>& min = Index<_DT>())
		{
			int decrease_idx = this->size() - 1;
			for (;; decrease_idx--)
			{

				if (decrease_idx == -1)
					throw std::out_of_range("Index has reached its min value");

				if ((min.empty() && this->at(decrease_idx) != 0) ||
					(!min.empty() && this->at(decrease_idx) > min[decrease_idx]))
				{
					this->at(decrease_idx)--;
					break;
				}

			}

			if (decrease_idx < this->size() - 1)
			{
				for (int i = decrease_idx + 1; i < this->size(); i++)
					this->at(i) = m_initial_state.at(i);
			}

			return *this;
		}

		// It's used for while loops
		operator bool() const
		{
			for (int i = 0; i < this->size(); i++)
				if (this->at(i) != 0)
					return true;
			return false;
		}
	};

} // namespace nyann