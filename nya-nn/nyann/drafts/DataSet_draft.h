#pragma once

#include "..//utils/Size.h"
#include "..//utils/exceptions.h"

namespace nyann {
	/////////////////////
	// Classes summary //
	/////////////////////
	class Slice;

	template<typename _DT>
	class DataSet_draft;

	//////////////////////////
	// Function definitions //
	//////////////////////////



	/////////////
	// Classes //
	/////////////
	class Index : ::std::vector<int>
	{
		std::vector<int> m_initial_state;
	public:
		//using std::vector<int>::vector;
		Index() {}

		Index(int count, int value)
			: 
			::std::vector<int>::vector(count, value)
		{}

		Index(std::initializer_list<int> il)
			:
			::std::vector<int>::vector(il),
			m_initial_state(il)
		{
		}

		Index(const Index& index)
			:
			::std::vector<int>::vector(index),
			m_initial_state(index.m_initial_state)
		{}

		Index(Index&& index) noexcept
			:
			::std::vector<int>::vector(std::move(index)),
			m_initial_state(std::move(index))
		{}

		bool operator==(const Index& other) const 
		{
			if (size() != other.size())
				return false;
			for (int i = 0; i < size(); i++)
				if (at(i) != other[i])
					return false;
			return true;
		}
		bool operator!=(const Index& other) const 
		{
			return !operator==(other);
		}
		bool operator<(const Index& other) const 
		{
			if (size() != other.size())
			{
				// If the other index
				// has the size of lower
				// dimension then it's 
				// considered as highest
				return size() > other.size();
			}

			// find first difference
			for (int i = 0; i < size(); i++)
			{
				if (at(i) != other[i])
					return at(i) < other[i];
			}
		}
		bool operator>(const Index& other) const 
		{
			return !(operator>(other));
		}

		bool operator<= (const Index& other) const 
		{
			return operator<(other) || operator==(other);
		}

		bool operator>= (const Index& other) const 
		{
			return operator>(other) || operator==(other);
		}

		Index& increment(const Index& max = Index())
		{
			if (max == Index())
			{
				back()++;
				return *this;
			}
			for (int decrease_idx = size() - 1;; decrease_idx--)
			{
				if (decrease_idx == -1)
					throw std::out_of_range("Index has reached its max value");

				if (at(decrease_idx) < max.at(decrease_idx))
				{
					at(decrease_idx)++;
					break;
				}
			}
			return *this;
		}

		Index& decrement(const Index& min = Index())
		{
			int decrease_idx = size() - 1;
			for (;; decrease_idx--)
			{
				
				if (decrease_idx == -1)
					throw std::out_of_range("Index has reached its min value");

				if ((min.empty() && at(decrease_idx) != 0) ||
					(!min.empty() && at(decrease_idx) > min[decrease_idx]))
				{
					at(decrease_idx)--;
					break;
				}
				
			}

			if (decrease_idx < size() - 1)
			{
				for (int i = decrease_idx + 1; i < size(); i++)
					at(i) = m_initial_state.at(i);
			}

			return *this;
		}

		// It's used for while loops
		operator bool() const
		{
			for (int i = 0; i < size(); i++)
				if (at(i) != 0)
					return true;
			return false;
		}
	};


	class Slice : public std::vector<int>
	{
		// whether it's an index
		// not an slice
		bool m_is_index;
	public:
		// Constructors
		Slice(int start, int end, int step = 0)
			: std::vector<int>{ start, end, step }, m_is_index(false)
		{}
		Slice(int idx)
			: std::vector<int>{ idx, idx + 1, 1 }, m_is_index(true)
		{}

		int width() const
		{
			return (this->at(1) - this->at(0)) / this->at(2);
		}

		int is_index() const
		{
			return m_is_index;
		}

		// operators
		using std::vector<int>::operator[];

		/*int& operator[](int i)
		{
			return std::vector<int>::operator[](i);
		}

		const int& operator[](int i) const
		{
			return std::vector<int>::operator[](i);
		}*/

		operator int() const
		{
			return this->operator[](0);
		}
	};

	/*
		Dataset represents arbitrary
		shaped array. It might have
		a size of {2, 256, 256} as
		2 samples 256x256 each.
	*/
	template<typename _DT>
	class DataSet_draft
	{
		std::vector<_DT> m_data;
		Size m_size;
	public:
		class NestedDataSet;

		DataSet_draft() {}

		DataSet_draft(const Size& size)
			: m_size(size)
		{
			int flat_size = 1;
			for (int i = 0; i < size.size(); i++)
				flat_size *= size[i];
			m_data.resize(flat_size);
		}

		DataSet_draft(const Size& size, const DataSet_draft<_DT>& dataset)
		{
			// TODO: size correctess checking
			m_data = dataset.m_data;
			m_size = size;
		}

		DataSet_draft(const DataSet_draft<_DT>& dataset)
		{
			m_data = dataset.m_data;
			m_size = dataset.m_size;
		}

		DataSet_draft(DataSet_draft<_DT>&& dataset)
		{
			m_data = std::move(dataset.m_data);
			m_size = std::move(dataset.m_size);
		}


		///////////////////
		// constructors  //
		// for different //
		// dimensions    //
		///////////////////

		// 1D dataset
		DataSet_draft(std::initializer_list<_DT> il)
			: m_data(il)
		{
			m_size.push_back(il.size());
		}

		// ND dataset
		DataSet_draft(std::initializer_list<DataSet_draft<_DT>> il)
		{
			std::vector<_DT> merged_data;
			for (auto dataset : il)
				merged_data.insert(merged_data.end(), dataset.m_data.begin(), dataset.m_data.end());
			int datasets_count = il.end() - il.begin();
			Size datasets_sizes = il.begin()->m_size;
			datasets_sizes.insert(datasets_sizes.begin(), datasets_count);
			m_size = datasets_sizes;
			m_data = merged_data;
		}
		_DT& at_index(const std::vector<int>& idx)
		{
			if (idx.size() != m_size.size())
				throw DifferentSizeError(""); // TODO: exception message 

			NestedDataSet value = operator[](idx[0]);
			for (auto it = idx.begin() + 1; it != idx.end(); it++)
				value = value[*it];

			return value.value();
		}

		const _DT& at_index(const std::vector<int>& idx) const
		{
			if (idx.size() != m_size.size())
				throw DifferentSizeError();

			NestedDataSet value = operator[](idx[0]);
			for (auto it = idx.begin() + 1; it != idx.end(); it++)
				value = value[*it];

			return value.value();
		}

		// Operators
		NestedDataSet operator[](int idx)
		{
			return NestedDataSet(this, std::vector<Slice>{ idx });
		}

		NestedDataSet operator[](const Slice& idx)
		{
			return NestedDataSet(this, { idx });
		}
		NestedDataSet operator[](int idx) const
		{
			return NestedDataSet(this, std::vector<Slice>{ idx });
		}

		NestedDataSet operator[](const Slice& idx) const
		{
			return NestedDataSet(this, { idx });
		}

		class NestedDataSet
		{
			DataSet_draft<_DT>* m_parent;
			std::vector<Slice> m_idxs;
		public:
			NestedDataSet(DataSet_draft<_DT>* parent, const std::vector<Slice>& idxs = {})
				: m_parent(parent),
				m_idxs(idxs)
			{}

			// TODO: reconsider the condition of 
			// getting the result. It might appear 
			// that somewhere in m_idxs is actual Slice
			// so you cannot convert a real slice into a number, can you?
			operator _DT()
			{
				// bad size of the coordinate
				if (m_idxs.size() != m_parent->m_size.size())
					throw ConversionError();

				// flatten the index
				int flat_idx = 0;
				for (int i = 0, deg = m_idxs.size() - 1; i < m_idxs.size(); i++, deg--)
					flat_idx += pow(10, deg) * m_idxs[i];

				return m_parent->m_data[flat_idx];
			}

			operator std::vector<_DT>()
			{
				// bad size of the coordinate
				if (m_idxs.size() != m_parent->m_size.size())
					throw ConversionError();


			}

			NestedDataSet operator[](const Slice& i)
			{
				// if index size already 
				// reached its high border
				if (m_idxs.size() == m_parent->m_size.size())
					throw IndexOverflowError();

				// create the complex
				// index
				std::vector<Slice> next_idxs = m_idxs;
				next_idxs.push_back(i);

				return NestedDataSet(m_parent, next_idxs);
			}

			NestedDataSet operator[](int i)
			{
				// if index size already 
				// reached its high border
				if (m_idxs.size() == m_parent->m_size.size())
					throw IndexOverflowError();

				// create the complex
				// index
				std::vector<Slice> next_idxs = m_idxs;
				next_idxs.push_back(i);

				return NestedDataSet(m_parent, next_idxs);
			}


		};

		DataSet_draft() {}

		DataSet_draft(const Size& size)
			: m_size(size)
		{
			int flat_size = 1;
			for (int i = 0; i < size.size(); i++)
				flat_size *= size[i];
			m_data.resize(flat_size);
		}

		DataSet_draft(const Size& size, const DataSet_draft<_DT>& dataset)
		{
			// TODO: size correctess checking
			m_data = dataset.m_data;
			m_size = size;
		}

		///////////////////
		// constructors  //
		// for different //
		// dimensions    //
		///////////////////

		// 1D dataset
		DataSet_draft(std::initializer_list<_DT> il)
			: m_data(il)
		{}

		// ND dataset
		DataSet_draft(std::initializer_list<DataSet_draft<_DT>> il)
		{
			std::vector<_DT> merged_data;
			for (auto dataset : il)
				merged_data.insert(merged_data.end(), dataset.m_data.begin(), dataset.m_data.end());
			int datasets_count = il.end() - il.begin();
			Size datasets_sizes = il.begin()->m_size;
			datasets_sizes.insert(datasets_sizes.begin(), datasets_count);
			m_size.insert(m_size.begin(), datasets_sizes.begin(), datasets_sizes.end());
		}

		NestedDataSet operator[](int i)
		{
			return NestedDataSet(this, std::vector<Slice>{ i });
		}

		NestedDataSet operator[](const Slice& i)
		{
			return NestedDataSet(this, { i });
		}

	};

} // namespace nyann