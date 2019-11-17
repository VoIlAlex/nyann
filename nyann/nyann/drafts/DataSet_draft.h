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

		// Methods
		Size size() const
		{
			return m_size;
		}

		// TODO(feature): change shape of the 
		// data set when changing size()
		void resize(const Size& new_size)
		{
			throw nyann::NotImplementedError("");
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
			const DataSet_draft<_DT>* m_parent_const;
			std::vector<Slice> m_slices;
			bool m_is_const;
		public:
			NestedDataSet(DataSet_draft<_DT>* parent, const std::vector<Slice>& idxs = {})
				:
				m_parent(parent),
				m_parent_const(nullptr),
				m_slices(idxs),
				m_is_const(false)
			{}

			NestedDataSet(const DataSet_draft<_DT>* parent, const std::vector<Slice>& idxs = {})
				:
				m_parent(nullptr),
				m_parent_const(parent),
				m_slices(idxs),
				m_is_const(true)
			{}

			// TODO: reconsider the condition of 
			// getting the result. It might appear 
			// that somewhere in m_slices is actual Slice
			// so you cannot convert a real slice into a number, can you?
			//operator _DT()
			//{
			//	// bad size of the coordinate
			//	if (!m_is_const)
			//	{
			//		if (m_slices.size() != m_parent->size().size())
			//		throw ConversionError("");
			//	}
			//	else if (m_is_const)
			//	{
			//		if (m_slices.size() != m_parent_const->size().size())
			//		throw ConversionError("");
			//	}

			//	int flat_idx = get_flat_index();

			//	return m_parent->m_data[flat_idx];
			//}

			_DT& value()
			{
				// bad size of the coordinate
				if (!m_is_const)
				{
					if (m_slices.size() != m_parent->size().size())
						throw ConversionError("");
				}
				else if (m_is_const)
				{
					if (m_slices.size() != m_parent_const->size().size())
						throw ConversionError("");
				}

				int flat_idx = get_flat_index();

				return m_parent->m_data[flat_idx];
			}

			const _DT& value() const
			{
				// bad size of the coordinate
				if (!m_is_const)
				{
					if (m_slices.size() != m_parent->size().size())
						throw ConversionError("");
				}
				else if (m_is_const)
				{
					if (m_slices.size() != m_parent_const->size().size())
						throw ConversionError("");
				}

				int flat_idx = get_flat_index();

				return m_parent->m_data[flat_idx];
			}

			const _DT& value_const() const
			{
				// bad size of the coordinate
				if (!m_is_const)
				{
					if (m_slices.size() != m_parent->size().size())
						throw ConversionError("");
				}
				else if (m_is_const)
				{
					if (m_slices.size() != m_parent_const->size().size())
						throw ConversionError("");
				}

				int flat_idx = get_flat_index();

				return m_parent_const->m_data[flat_idx];
			}

			operator DataSet_draft<_DT>()
			{
				// Complete indexes
				for (int i = m_slices.size(); i < m_parent->size().size(); i++)
					m_slices.push_back({ 0, m_parent->size()[i] });

				// Calculate the size 
				// of resultant dataset
				Size size;
				for (auto slice : m_slices)
				{
					if (!slice.is_index())
						size.push_back(slice.width());
				}

				DataSet_draft<_DT> dataset(size);

				std::vector<int> current_idx;
				std::vector<int> current_result_idx;
				/*for (int i = 0; i < m_slices.size(); i++)
				{
					if (m_slices[i].is_index())
					{
						current_idx.push_back(m_slices[i]);
						if (current_idx.size() == m_parent->m_size())
							dataset.at_index(current_result_idx) = m_parent->at_index(current_idx);
					}
					else
					{
						for (int j = m_slices[i][0], k = 0; j < m_slices[i][1]; j += m_slices[i][2], k++)
						{
							current_result_idx
						}
					}

				}*/

				// TODO: create the dataset

				return dataset;
			}

			NestedDataSet operator[](const Slice& i) const
			{
				// if index size already 
				// reached its high border
				if (m_slices.size() == m_parent->m_size.size())
					throw IndexOverflowError("Bad size of indexing sequence");

				// create the complex
				// index
				std::vector<Slice> next_idxs = m_slices;
				next_idxs.push_back(i);

				return NestedDataSet(m_parent, next_idxs);
			}

			NestedDataSet operator[](int i) const
			{
				// if index size already 
				// reached its high border

				if (m_is_const)
				{
					if(m_slices.size() == m_parent_const->m_size.size())
					throw IndexOverflowError("Bad size of indexing sequence");
				}
				else
				{
					if (m_slices.size() == m_parent->m_size.size())
						throw IndexOverflowError("Bad size of indexing sequence");
				}


				// create the complex
				// index
				std::vector<Slice> next_idxs = m_slices;
				next_idxs.push_back(i);

				if (m_is_const)
					return NestedDataSet(m_parent_const, next_idxs);
				return NestedDataSet(m_parent, next_idxs);
			}


			class iterator
			{
				/*NestedDataSet* m_dataset;
				int m_position;
			public:*/
				//iterator(NestedDataSet* dataset, int position = 0)
				//	: m_dataset(dataset), m_position(position)
				//{}

				//iterator(const iterator& other)
				//	: m_dataset(other.m_dataset), m_position(other.m_position)
				//{}

				//NestedDataSet& operator*()
				//{
				//	return m_dataset->operator[](m_position);
				//}

				//const NestedDataSet& operator*() const
				//{
				//	return m_dataset->operator[](m_position);
				//}
				//NestedDataSet* operator->()
				//{
				//	return *m_dataset->operator[](m_position);
				//}

				//iterator& operator++()
				//{
				//	m_position++;
				//	return *this;
				//}

				//iterator operator++(int)
				//{
				//	iterator temp(*this);
				//	operator++();
				//	return temp;
				//}

				//// Logic operations
				//bool operator<(const iterator& other) const
				//{
				//	return m_position < other.m_position;
				//}
				//bool operator>(const iterator& other) const
				//{
				//	return m_position > other.m_position;
				//}
				//bool operator==(const iterator& other) const
				//{
				//	return (m_dataset == other.m_dataset && m_position == other.m_position);
				//}
				//bool operator!=(const iterator& other) const
				//{
				//	return !(operator==(other));
				//}
				//bool operator<=(const iterator& other) const
				//{
				//	return (operator<(other) || operator==(other));
				//}
				//bool operator>=(const iterator& other) const
				//{
				//	return (operator>(other) || operator==(other));
				//}
				NestedDataSet* m_dataset;
				const NestedDataSet* m_dataset_const;
				int m_position;
				bool m_is_dataset_const;

				// It's for constructions in methods
				iterator() :
					m_dataset(nullptr),
					m_dataset_const(nullptr),
					m_position(0),
					m_is_dataset_const(false)
				{}

			public:

				
				iterator(NestedDataSet* dataset, int position = 0)
					:
					m_dataset(dataset),
					m_dataset_const(nullptr),
					m_position(position),
					m_is_dataset_const(false)
				{}

				iterator(const NestedDataSet* dataset, int position = 0)
					:
					m_dataset(nullptr),
					m_dataset_const(dataset),
					m_position(position),
					m_is_dataset_const(true)
				{}

				iterator(const iterator& other)
					:
					m_dataset(other.m_dataset),
					m_dataset_const(other.m_dataset_const),
					m_position(other.m_position),
					m_is_dataset_const(other.m_is_dataset_const)
				{}

				NestedDataSet operator*()
				{
					if (m_is_dataset_const)
						return m_dataset_const->operator[](m_position);
					return m_dataset->operator[](m_position);
				}

				/*const NestedDataSet& operator*() const
				{
					if (m_is_dataset_const)
						return m_dataset_const->operator[](m_position);
					return m_dataset->operator[](m_position);
				}*/

				NestedDataSet* operator->()
				{
					return *m_dataset->operator[](m_position);
				}

				NestedDataSet* operator->() const
				{
					if (m_is_dataset_const)
						return m_dataset_const->operator[](m_position);
					return m_dataset->operator[](m_position);
				}

				//iterator& operator++()
				//{
				//	m_position++;
				//	return *this;
				//}

				//iterator operator++(int)
				//{
				//	iterator temp(*this);
				//	operator++();
				//	return temp;
				//}

				// Logic operations
				bool operator<(const iterator& other) const
				{
					return m_position < other.m_position;
				}
				bool operator>(const iterator& other) const
				{
					return m_position > other.m_position;
				}
				bool operator==(const iterator& other) const
				{
					if (m_is_dataset_const)
					{
						if (other.m_is_dataset_const)
						{
							return (m_dataset_const == other.m_dataset_const && m_position == other.m_position);
						}
						else
						{
							return (m_dataset_const == other.m_dataset && m_position == other.m_position);
						}
					}
					else
					{
						if (other.m_is_dataset_const)
						{
							return (m_dataset == other.m_dataset_const && m_position == other.m_position);
						}
						else
						{
							return (m_dataset == other.m_dataset && m_position == other.m_position);
						}
					}

				}
				bool operator!=(const iterator& other) const
				{
					return !(operator==(other));
				}
				bool operator<=(const iterator& other) const
				{
					return (operator<(other) || operator==(other));
				}
				bool operator>=(const iterator& other) const
				{
					return (operator>(other) || operator==(other));
				}

				// Arithmetic operations
				iterator operator-(int value) const
				{
					if (m_position - value < 0)
						throw std::out_of_range("Iterator is out of range");
					iterator iter(this, m_position - value);
					return iter;
				}
				iterator operator+(int value) const
				{
					iterator iter(this, m_position + value);
					return iter;
				}
				iterator& operator++()
				{
					m_position++;
					return *this;
				}
				iterator operator++(int)
				{
					iterator temp (*this);
					m_position++;
					return temp;
				}
				iterator& operator--()
				{
					if(m_position - 1 < 0)
						throw std::out_of_range("Iterator is out of range");
					m_position--;
					return *this;
				}
				iterator operator--(int)
				{
					if (m_position - 1 < 0)
						throw std::out_of_range("Iterator is out of range");
					iterator temp(*this);
					m_position--;
					return temp;
				}

			};

			// Iteration tools
			iterator begin() const
			{
				return iterator(this);
			}

			iterator end() const
			{
				if (m_slices.empty())
					return iterator(this);
				if (m_is_const)
				{
					return iterator(this, m_parent_const->size()[m_slices.size()]);
				}
				else
				{
					return iterator(this, m_parent->size()[m_slices.size()]);
				}
			}

		private:
			int get_flat_index() const
			{
				int flat_idx = 0;
				for (int i = m_slices.size() - 1, offset_size = 1; i >= 0; i--)
				{
					flat_idx += offset_size * int(m_slices[i]);
					if (m_is_const)
						offset_size *= m_parent_const->m_size[i];
					else
						offset_size *= m_parent->m_size[i];
				}
				return flat_idx;
			}
		};

		bool operator==(const DataSet_draft<_DT>& left) const
		{
			return m_data == left.m_data && m_size == left.m_size;
		}

		class iterator
		{
			DataSet_draft<_DT>* m_dataset;
			const DataSet_draft<_DT>* m_dataset_const;
			int m_position;
			bool m_is_dataset_const;
		public:
			iterator(DataSet_draft<_DT>* dataset, int position = 0)
				: 
				m_dataset(dataset), 
				m_dataset_const(nullptr),
				m_position(position),
				m_is_dataset_const(false)
			{}

			iterator(const DataSet_draft<_DT>* dataset, int position = 0)
				:
				m_dataset(nullptr),
				m_dataset_const(dataset),
				m_position(position),
				m_is_dataset_const(true)
			{}

			iterator(const iterator& other)
				:
				m_dataset(other.m_dataset),
				m_dataset_const(other.m_dataset_const),
				m_position(other.m_position),
				m_is_dataset_const(other.m_is_dataset_const)
			{}

			iterator(const iterator* other)
				:
				m_dataset(other->m_dataset),
				m_dataset_const(other->m_dataset_const),
				m_position(other->m_position),
				m_is_dataset_const(other->m_is_dataset_const)
			{

			}

			NestedDataSet operator*() const
			{
				if (m_is_dataset_const)
					return m_dataset_const->operator[](m_position);
				return m_dataset->operator[](m_position);
			}

			NestedDataSet operator*()
			{
				if (m_is_dataset_const)
					return m_dataset_const->operator[](m_position);
				return m_dataset->operator[](m_position);
			}

			/*const NestedDataSet operator*() const
			{
				if (m_is_dataset_const)
					return m_dataset_const->operator[](m_position);
				return m_dataset->operator[](m_position);
			}*/

			NestedDataSet* operator->()
			{
				return *m_dataset->operator[](m_position);
			}

			NestedDataSet* operator->() const
			{
				if (m_is_dataset_const)
					return m_dataset_const->operator[](m_position);
				return m_dataset->operator[](m_position);
			}

			// Logic operations
			bool operator<(const iterator& other) const
			{
				return m_position < other.m_position;
			}
			bool operator>(const iterator& other) const
			{
				return m_position > other.m_position;
			}
			bool operator==(const iterator& other) const
			{
				if (m_is_dataset_const)
				{
					if (other.m_is_dataset_const)
					{
						return (m_dataset_const == other.m_dataset_const && m_position == other.m_position);
					}
					else
					{
						return (m_dataset_const == other.m_dataset && m_position == other.m_position);
					}
				}
				else
				{
					if (other.m_is_dataset_const)
					{
						return (m_dataset == other.m_dataset_const && m_position == other.m_position);
					}
					else
					{
						return (m_dataset == other.m_dataset && m_position == other.m_position);
					}
				}
				
			}
			bool operator!=(const iterator& other) const
			{
				return !(operator==(other));
			}
			bool operator<=(const iterator& other) const
			{
				return (operator<(other) || operator==(other));
			}
			bool operator>=(const iterator& other) const
			{
				return (operator>(other) || operator==(other));
			}


			// Arithmetic operations
			iterator operator-(int value) const
			{
				if (m_position - value < 0)
					throw std::out_of_range("Iterator is out of range");
				iterator iter(*this);
				iter.m_position = m_position - value;
				return iter;
			}
			iterator operator+(int value) const
			{
				iterator iter(*this);
				iter.m_position = m_position - value;
				return iter;
			}
			iterator& operator++()
			{
				m_position++;
				return *this;
			}
			iterator operator++(int)
			{
				iterator temp(*this);
				m_position++;
				return temp;
			}
			iterator& operator--()
			{
				if (m_position - 1 < 0)
					throw std::out_of_range("Iterator is out of range");
				m_position--;
				return *this;
			}
			iterator operator--(int)
			{
				if (m_position - 1 < 0)
					throw std::out_of_range("Iterator is out of range");
				iterator temp(*this);
				m_position--;
				return temp;
			}
		};

		// iteration tools

		iterator begin()
		{
			return iterator(this);
		}

		iterator end()
		{
			if (!size().empty())
				return iterator(this, size().front());
			return iterator(this);
		}

		const iterator begin() const
		{
			return iterator(this);
		}

		const iterator end() const
		{
			if (!size().empty())
				return iterator(this, size().front());
			return iterator(this);
		}



	};



} // namespace nyann