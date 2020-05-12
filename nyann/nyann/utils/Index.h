#pragma once


// For all the framework configurations
#include "../_config.h"

#include <vector>


namespace nyann {

	template <typename _DT = unsigned int>
	class Index : public ::std::vector<_DT>
	{
		std::vector<_DT> m_initial_state;
	public:
		//using std::vector<int>::vector;
		Index() {}

		explicit Index(int count, _DT value = 0)
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
			::std::vector<_DT>::vector(std::move(index))
		{
			m_initial_state.resize(this->size());
			std::copy(this->begin(), this->end(), m_initial_state.begin());
		}

		Index(const std::vector<_DT>& ivec)
			:
			::std::vector<_DT>::vector(ivec),
			m_initial_state(ivec)
		{}

		Index(std::vector<_DT>&& ivec)
			:
			::std::vector<_DT>::vector(std::move(ivec))
		{
			m_initial_state.resize(this->size());
			std::copy(this->begin(), this->end(), m_initial_state.begin());
		}

		std::vector<_DT>& initial_state()
		{
			return m_initial_state;
		}

		const std::vector<_DT>& initial_state() const
		{
			return m_initial_state;
		}

		Index<_DT>& operator=(const Index<_DT>& index) 
		{
			for (int i = 0; i < index.size(); i++)
				this->at(i) = index.at(i);
			return *this;
		}

		Index<_DT>& operator=(Index<_DT>&& index)
		{
			for (int i = 0; i < index.size(); i++)
				this->at(i) = index.at(i);
			return *this;
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
			if (*this == other)
				return false;
			// find first difference
			for (int i = 0; i < this->size(); i++)
			{
				if (this->at(i) != other.at(i))
					return this->at(i) < other.at(i);
			}
		}
		bool operator>(const Index& other) const
		{
			return !(operator<(other)) && !(operator==(other));
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

		Index<_DT>& increment(Index<_DT> min = Index(), const Index<_DT>& max = Index(), std::vector<_DT> steps = std::vector<_DT>(), bool to_border = false)
		{
			// Invariant
			for (auto step : steps)
				if (step < 1)
					throw ::std::runtime_error("Wrong step");

			// Add missing
			for (int i = steps.size(); i < max.size(); i++)
				steps.push_back(1);

			for (int i = min.size(); i < this->size(); i++)
				min.push_back(_DT());

			if (max == Index<_DT>())
			{
				this->back()++;
				return *this;
			}

			
			int current_idx_item = max.size() - 1;
			int to_value;
			while (current_idx_item != 0)
			{
				to_value = (to_border ? max.at(current_idx_item) - 1 : max.at(current_idx_item));
				if (this->at(current_idx_item) == to_value || this->at(current_idx_item) + steps.at(current_idx_item) > to_value)
				{
					current_idx_item--;
				}
				else
				{
					this->at(current_idx_item) += steps.at(current_idx_item);
					for (int i = current_idx_item + 1; i < max.size(); i++)
						this->at(i) = min.at(i);
					break;
				}
			}
			if (current_idx_item == 0)
			{
				this->at(current_idx_item) += steps.at(current_idx_item);
				for (int i = current_idx_item + 1; i < max.size(); i++)
					this->at(i) = min.at(i);
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

		_DT plain(const Index& max_index) const
		{
			_DT index = _DT();
			int degree = 0;
			for (int i = 0, i_r = this->size() - 1; i < this->size(); i++, i_r--)
			{
				degree = 1;
				for (int j = i_r + 1; j < max_index.size(); j++)
					degree *= max_index[j];
				index += at(i_r) * degree;
			}
			return index;
		}

		bool all_lower(const Index& index)
		{
			if (this->size() != index.size())
				return false;
			for (int i = 0; i < this->size(); i++)
				if (this->at(i) >= index.at(i))
					return false;
			return true;
				
		}

		static Index<_DT> join(const Index<_DT>& size_1, const Index<_DT> size_2)
		{
			Index<_DT> size_result(size_1.size() + size_2.size());
			for (int i = 0; i < size_1.size(); i++)
				size_result[i] = size_1[i];
			for (int i = size_1.size(), j = 0; i < size_1.size() + size_2.size(); i++, j++)
				size_result[i] = size_2[j];
			return size_result;
		}
	};

} // namespace nyann