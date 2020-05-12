#pragma once


// For all the framework configurations
#include "_config.h"

#include "utils/exceptions.h"
#include "utils/Size.h"
#include "utils/Index.h"
#include "utils/Slice.h"
#include "DataSet/DataSetOperation.h"
#include "DataSet/DataSetReducer.h"

#include <initializer_list>
#include <vector>
#include <math.h>
#include <functional>


namespace nyann {
	
	/*
		Dataset represents arbitrary
		shaped array. It might have
		a size of {2, 256, 256} as
		2 samples 256x256 each.
	*/
	template<typename _DT>
	class DataSet
	{
	protected:
		std::vector<_DT> m_data;
		Size<> m_size;

	public:
		class NestedDataSet;

		DataSet() {}

		DataSet(const Size<>& size)
			: m_size(size)
		{
			size_t flat_size = 1;
			for (int i = 0; i < size.size(); i++)
				flat_size *= size[i];
			m_data.resize(flat_size);
		}

		DataSet(const Size<>& size, const DataSet<_DT>& dataset)
		{
			// TODO: size correctess checking
			m_data = dataset.m_data;
			m_size = size;
		}

		DataSet(const Size<>& size, const std::vector<_DT>& data)
		{
			// TODO: size correctess checking
			m_data = data;
			m_size = size;
		}

		DataSet(const DataSet<_DT>& dataset)
		{
			m_data = dataset.m_data;
			m_size = dataset.m_size;
		}

		DataSet(DataSet<_DT>&& dataset)
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
		DataSet(std::initializer_list<_DT> il)
			: m_data(il)
		{
			m_size.push_back(il.size());
		}

		// ND dataset
		DataSet(std::initializer_list<DataSet<_DT>> il)
		{
			std::vector<_DT> merged_data;
			for (auto dataset : il)
				merged_data.insert(merged_data.end(), dataset.m_data.begin(), dataset.m_data.end());
			int datasets_count = il.end() - il.begin();
			Size<> datasets_sizes = il.begin()->m_size;
			datasets_sizes.insert(datasets_sizes.begin(), datasets_count);
			m_size = datasets_sizes;
			m_data = merged_data;
		}

		// Methods
		Size<> size() const
		{
			return m_size;
		}

		Size<> get_size() const
		{
			return m_size;
		}

		// TODO(feature): change shape of the 
		// data set when changing size()
		void resize(const Size<>& new_size)
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
				throw DifferentSizeError("");

			NestedDataSet value = operator[](idx[0]);
			for (auto it = idx.begin() + 1; it != idx.end(); it++)
				value = value[*it];

			return value.value_const();
		}

		template<typename _DT_IDX>
		_DT& at_index(const Index<_DT_IDX>& idx)
		{
			if (idx.size() != m_size.size())
				throw DifferentSizeError(""); // TODO: exception message 

			NestedDataSet value = operator[](idx[0]);
			for (auto it = idx.begin() + 1; it != idx.end(); it++)
				value = value[*it];

			return value.value();
		}

		template<typename _DT_IDX>
		const _DT& at_index(const Index<_DT_IDX>& idx) const
		{
			if (idx.size() != m_size.size())
				throw DifferentSizeError(""); // TODO: exception message 

			NestedDataSet value = operator[](idx[0]);
			for (auto it = idx.begin() + 1; it != idx.end(); it++)
				value = value[*it];
			return value.value_const();
		}

		// Operators
		NestedDataSet operator[](int idx)
		{
			std::vector<Slice<>> slices{ idx };
			NestedDataSet result(this, slices);
			return result;
		}

		NestedDataSet operator[](const Slice<>& idx)
		{
			return NestedDataSet(this, std::vector<Slice<>>{ idx });
		}
		NestedDataSet operator[](int idx) const
		{
			return NestedDataSet(this, std::vector<Slice<>>{ idx });
		}
		const ::std::vector<_DT>& data() const
		{
			return m_data;
		}

		::std::vector<_DT>& access_data()
		{
			return m_data;
		}

		NestedDataSet operator[](const Slice<>& idx) const
		{
			return NestedDataSet(this, { idx });
		}

		class NestedDataSet
		{
			DataSet<_DT>* m_parent;
			const DataSet<_DT>* m_parent_const;
			std::vector<Slice<>> m_slices;
			bool m_is_const;

		public:
			NestedDataSet()
				:
				m_parent(nullptr),
				m_parent_const(nullptr),
				m_slices(),
				m_is_const(false)
			{}

			NestedDataSet(DataSet<_DT>* parent, const std::vector<Slice<>>& idxs)
				:
				m_parent(parent),
				m_parent_const(nullptr),
				m_slices(idxs),
				m_is_const(false)
			{}

			NestedDataSet(const DataSet<_DT>* parent, const std::vector<Slice<>>& idxs)
				:
				m_parent(nullptr),
				m_parent_const(parent),
				m_slices(idxs),
				m_is_const(true)
			{}

			NestedDataSet(DataSet<_DT>* parent)
				:
				m_parent(parent),
				m_parent_const(nullptr),
				m_slices(),
				m_is_const(false)
			{}

			NestedDataSet(const DataSet<_DT>* parent)
				:
				m_parent(nullptr),
				m_parent_const(parent),
				m_slices(),
				m_is_const(true)
			{}

			NestedDataSet(const NestedDataSet& other)
				:
				m_parent(other.m_parent),
				m_parent_const(other.m_parent_const),
				m_slices(other.m_slices),
				m_is_const(other.m_is_const)
			{}

			NestedDataSet(NestedDataSet&& other)
				:
				m_parent(other.m_parent),
				m_parent_const(other.m_parent_const),
				m_slices(::std::move(other.m_slices)),
				m_is_const(other.m_is_const)
			{
				other.m_parent = nullptr;
				other.m_parent_const = nullptr;
				other.m_slices.clear();
				other.m_is_const = false;
			}

			NestedDataSet(DataSet<_DT>* parent, const Index<_DT>& index)
				:
				m_parent(parent),
				m_parent_const(nullptr),
				m_slices(index.size()),
				m_is_const(false)
			{
				for (int i = 0; i < index.size(); i++)
					m_slices[i] = Slice<>{ index[i] };
			}

			void set_parent(DataSet<_DT>* parent)
			{
				m_parent = parent;
			}

			NestedDataSet& operator=(const NestedDataSet& other)
			{
				m_parent = other.m_parent;
				m_parent_const = other.m_parent_const;
				m_slices = other.m_slices;
				m_is_const = other.m_is_const;

				return *this;
			}

			NestedDataSet& operator=(NestedDataSet&& other)
			{
				m_parent = other.m_parent;
				m_parent_const = other.m_parent_const;
				m_slices = other.m_slices;
				m_is_const = other.m_is_const;

				other.m_parent = nullptr;
				other.m_parent_const = nullptr;
				other.m_slices.clear();
				other.m_is_const = false;

				return *this;
			}

			_DT& value()
			{
				int flat_idx = get_flat_index();
				// bad size of the coordinate
				if (!m_is_const)
				{
					if (m_slices.size() != m_parent->size().size())
						throw ConversionError("");
					return m_parent->m_data[flat_idx];
				}
				else
				{
					throw ConstParentError("Cannot get reference to item of a const dataset.");
				}
			}

			const _DT& value() const
			{
				int flat_idx = get_flat_index();
				// bad size of the coordinate
				if (!m_is_const)
				{
					if (m_slices.size() != m_parent->size().size())
						throw ConversionError("");
					return m_parent->m_data[flat_idx];
				}
				else
				{
					if (m_slices.size() != m_parent_const->size().size())
						throw ConversionError("");
					return m_parent_const->m_data[flat_idx];
				}
			}

			operator _DT() const {
				int flat_idx = get_flat_index();
				// bad size of the coordinate
				if (!m_is_const)
				{
					if (m_slices.size() != m_parent->size().size())
						throw ConversionError("");
					return m_parent->m_data[flat_idx];
				}
				else
				{
					if (m_slices.size() != m_parent_const->size().size())
						throw ConversionError("");
					return m_parent_const->m_data[flat_idx];
				}
			}

			const _DT& value_const() const
			{
				int flat_idx = get_flat_index();
				// bad size of the coordinate
				if (!m_is_const)
				{
					if (m_slices.size() != m_parent->size().size())
						throw ConversionError("");
					return m_parent->m_data[flat_idx];
				}
				else
				{
					if (m_slices.size() != m_parent_const->size().size())
						throw ConversionError("");
					return m_parent_const->m_data[flat_idx];
				}
			}

			NestedDataSet& set_value(const _DT& value)
			{
				if (m_is_const)
					throw ConstParentError("Cannot set value to the item while dataset is const");
				else if (m_slices.size() != m_parent->size().size())
					throw ConversionError("");
				int flat_idx = get_flat_index();
				m_parent->m_data.at(flat_idx) = value;
				return *this;
			}

			NestedDataSet& set_value(const DataSet& value)
			{
				if (m_is_const)
					throw std::runtime_error("Parent dataset is constants.");

				DataSet* parent = m_parent;

				Index<> start_dataset_index(m_is_const ? m_parent_const->size().size() : m_parent->size().size());
				start_dataset_index.reserve(parent->size().size());

				Index<> max_dataset_index(m_is_const ? m_parent_const->size().size() : m_parent->size().size());
				max_dataset_index.reserve(parent->size().size());

				Index<> start_value_index(value.size().size(), 0);
				Index<> dataset_size(parent->size().size());
				for (int i = 0; i < parent->size().size(); i++)
					dataset_size[i] = parent->size()[i];

				Index<> max_value_index(value.size().size());
				for (int i = 0; i < value.size().size(); i++)
					max_value_index[i] = value.size()[i];

				for (int i = 0; i < m_slices.size(); i++)
				{
					start_dataset_index[i] = m_slices[i].from_value();
					max_dataset_index[i] = m_slices[i].to_value();
				}
				for (int i = m_slices.size(); i < parent->size().size(); i++)
				{
					start_dataset_index[i] = 0;
					max_dataset_index[i] = parent->size()[i];
				}

				Index<> current_dataset_index = start_dataset_index;
				Index<> current_value_index = start_value_index;
				for (size_t plain_dataset_index, plain_value_index;
					current_dataset_index.all_lower(max_dataset_index);
					)
				{
					plain_dataset_index = current_dataset_index.plain(dataset_size);
					plain_value_index = current_value_index.plain(max_value_index);
					parent->access_data()[plain_dataset_index] = value.data()[plain_value_index];
					current_dataset_index.increment(start_dataset_index, max_dataset_index, {}, true);
					current_value_index.increment(start_value_index, max_value_index, {}, true);
				}

				return *this;
			}

			operator DataSet<_DT>()
			{
				// Complete indexes
				if (m_is_const)
				{
					for (int i = m_slices.size(); i < m_parent_const->size().size(); i++)
						m_slices.push_back({ 0, static_cast<int>(m_parent_const->size()[i]) });
				}
				else
				{
					for (int i = m_slices.size(); i < m_parent->size().size(); i++)
						m_slices.push_back({ 0, static_cast<int>(m_parent->size()[i]) });
				}

				// Handle slices without right border
				if (m_is_const)
				{
					for (int i = 0; i < m_slices.size(); i++)
						if (m_slices[i].at(1) == -1)
							m_slices[i].at(1) = m_parent_const->size()[i];
				}
				else
				{
					for (int i = 0; i < m_slices.size(); i++)
						if (m_slices[i].at(1) == -1)
							m_slices[i].at(1) = m_parent->size()[i];
				}

				// Calculate the size 
				// of resultant dataset
				Size<> size;
				for (auto slice : m_slices)
					size.push_back(slice.width());

				// Size of the resulting 
				// array. Omit indexes. Keep
				// only slices.
				Size<> result_size;
				for (auto slice : m_slices)
					if (!slice.is_index())
						result_size.push_back(slice.width());

				/*
					TODO: Here size if not correct
					because indexes are not included
					in shape of final data. Like
					x = [[1, 2], [3, 4]]
					x[{0, 2}][0] = [1, 3], but not [[1], [3]]
					You task is correct this.
				*/

				DataSet<_DT> dataset(result_size);

				Index<unsigned int> max_idx(size.size());
				for (int i = 0; i < m_slices.size(); i++)
					max_idx[i] = m_slices[i].to_value() - 1;

				Index<unsigned int> min_idx(size.size());
				for (int i = 0; i < m_slices.size(); i++)
					min_idx[i] = m_slices[i].from_value();

				Index<unsigned int> max_result_idx(result_size.size());
				for (int i = 0; i < result_size.size(); i++)
					if (!m_slices[i].is_index())
						max_result_idx[i] = m_slices[i].width() - 1;

				Index<unsigned int> current_idx(size.size());
				for (int i = 0; i < m_slices.size(); i++)
					current_idx[i] = m_slices[i].from_value();

				std::vector<unsigned int> steps(size.size());
				for (int i = 0; i < size.size(); i++)
					steps[i] = m_slices[i].step_value();

				Index<unsigned int> current_result_idx(result_size.size());

				// Dataset creation
				while (current_idx <= max_idx)
				{
					if (m_is_const)
						dataset.at_index(current_result_idx) = m_parent_const->at_index(current_idx);
					else
						dataset.at_index(current_result_idx) = m_parent->at_index(current_idx);

					current_result_idx.increment(Index<>(), max_result_idx);
					current_idx.increment(min_idx, max_idx, steps);
				}

				return dataset;
			}

			NestedDataSet& operator=(const _DT& value) {
				int flat_idx = get_flat_index();
				// bad size of the coordinate
				if (!m_is_const)
				{
					if (m_slices.size() != m_parent->size().size())
						throw ConversionError("");
					m_parent->m_data[flat_idx] = value;
				}
				throw std::runtime_error("Parent dataset is constants.");
				return *this;
			}

			NestedDataSet& operator=(const DataSet<_DT>& dataset) {
				return this->set_value(dataset);
			}

			NestedDataSet operator[](const Slice<>& i) const
			{
				// if index size already 
				// reached its high border
				if (m_slices.size() == m_parent->m_size.size())
					throw IndexOverflowError("Bad size of indexing sequence");

				// create the complex
				// index
				std::vector<Slice<>> next_idxs = m_slices;
				next_idxs.push_back(i);

				return NestedDataSet(m_parent, next_idxs);
			}

			NestedDataSet operator[](int i) const
			{
				// if index size already 
				// reached its high border

				if (m_is_const)
				{
					if (m_slices.size() == m_parent_const->m_size.size())
						throw IndexOverflowError("Bad size of indexing sequence");
				}
				else
				{
					if (m_slices.size() == m_parent->m_size.size())
						throw IndexOverflowError("Bad size of indexing sequence");
				}

				// create the complex
				// index
				std::vector<Slice<>> next_idxs(m_slices);
				next_idxs.push_back(Slice<>(i));
				NestedDataSet result;
				if (m_is_const)
					result = NestedDataSet(m_parent_const, next_idxs);
				else
					result = NestedDataSet(m_parent, next_idxs);
				return result;
			}

			class iterator
			{
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

		class iterator
		{
			DataSet<_DT>* m_dataset;
			const DataSet<_DT>* m_dataset_const;
			int m_position;
			bool m_is_dataset_const;
			int m_axis;

		public:
			iterator(DataSet<_DT>* dataset, int position = 0, int axis = -1)
				:
				m_dataset(dataset),
				m_dataset_const(nullptr),
				m_position(position),
				m_is_dataset_const(false),
				m_axis(axis)
			{}

			iterator(const DataSet<_DT>* dataset, int position = 0, int axis = -1)
				:
				m_dataset(nullptr),
				m_dataset_const(dataset),
				m_position(position),
				m_is_dataset_const(true),
				m_axis(axis)
			{}

			iterator(const iterator& other)
				:
				m_dataset(other.m_dataset),
				m_dataset_const(other.m_dataset_const),
				m_position(other.m_position),
				m_is_dataset_const(other.m_is_dataset_const),
				m_axis(other.m_axis)
			{}

			iterator(const iterator* other)
				:
				m_dataset(other->m_dataset),
				m_dataset_const(other->m_dataset_const),
				m_position(other->m_position),
				m_is_dataset_const(other->m_is_dataset_const),
				m_axis(other->m_axis)
			{}

			_DT& operator->()
			{
				return m_dataset->access_data().at(m_position);
			}

			const _DT& operator->() const
			{
				if (m_is_dataset_const)
					return m_dataset_const->data().at(m_position);
				return m_dataset->data().at(m_position);
			}

			_DT& operator*()
			{
				return m_dataset->access_data().at(m_position);
			}

			const _DT& operator*() const
			{
				if (m_is_dataset_const)
					return m_dataset_const->data().at(m_position);
				return m_dataset->data().at(m_position);
			}

			_DT& value()
			{
				return m_dataset->access_data().at(m_position);
			}

			const _DT& value_const() const
			{
				if (m_is_dataset_const)
					return m_dataset_const->data().at(m_position);
				return m_dataset->data().at(m_position);
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
				iter.m_position = m_position + value;
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
			int max_index = 1;
			for (size_t dim_size : size())
				max_index *= dim_size;

			if (!size().empty())
				return iterator(this, max_index);
			return iterator(this);
		}

		const iterator begin() const
		{
			return iterator(this);
		}

		const iterator end() const
		{
			int max_index = 1;
			for (size_t dim_size : size())
				max_index *= dim_size;

			if (!size().empty())
				return iterator(this, max_index);
			return iterator(this);
		}


		//////////////////////
		// Generation tools //
		//////////////////////

		static DataSet<_DT> ones_like(const DataSet<_DT>& other)
		{
			DataSet<_DT> new_dataset;
			new_dataset.m_data = std::vector<_DT>(other.m_data.size(), _DT(1));
			new_dataset.m_size = other.m_size;
			return new_dataset;
		}

		static DataSet<_DT> zeros_like(const DataSet<_DT>& other)
		{
			DataSet<_DT> new_dataset;
			new_dataset.m_data = std::vector<_DT>(other.m_data.size(), _DT(0));
			new_dataset.m_size = other.m_size;
			return new_dataset;
		}

		static DataSet<_DT> empty_like(const DataSet<_DT>& other)
		{
			DataSet<_DT> new_dataset;
			new_dataset.m_data = std::vector<_DT>(other.m_data.size(), _DT());
			new_dataset.m_size = other.m_size;
			return new_dataset;
		}


		DataSet<_DT>& operator=(const DataSet<_DT>& dataset)
		{
			this->m_data = dataset.m_data;
			this->m_size = dataset.m_size;
			return *this;
		}


		DataSet<_DT> operator-(const DataSet<_DT>& right) const
		{
			if (this->size() != right.size())
				throw SizeError("Left dataset and right dataset have different sizes.");


			DataSet<_DT> result(this->size());
			for (int i = 0; i < this->m_data.size(); i++)
				result.m_data[i] = this->m_data[i] - right.m_data[i];
			return result;
		}

		bool operator==(const DataSet<_DT>& right) const
		{
			if (m_data.size() != right.m_data.size())
				return false;
			for (size_t i = 0; i < m_data.size(); i++)
			{
				if (m_data[i] != right.m_data[i])
					return false;
			}

			return true;
		}

		bool operator!=(const DataSet<_DT>& right) const
		{
			return !operator==(right);
		}

		static DataSet<_DT> abs(const DataSet<_DT>& dataset)
		{
			DataSet<_DT> result(dataset.size());

			for (int i = 0; i < dataset.m_data.size(); i++)
				result.m_data[i] = ::abs(dataset.m_data[i]);

			return result;
		}

		static _DT abs_difference(const DataSet<_DT>& left, const DataSet<_DT>& right)
		{
			_DT difference = _DT();
			DataSet<_DT> diff_dataset = DataSet<_DT>::abs(left - right);
			for (auto& value : diff_dataset.m_data)
				difference += value;
			return difference;
		}
	};
} // namespace nyann


// include subclasses etc. of DataSet
#include "DataSet/TrainDataSet.h"
#include "DataSet/DataSetSerializer.h"