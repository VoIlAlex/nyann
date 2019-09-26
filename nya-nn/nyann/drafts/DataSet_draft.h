#pragma once

#include "..//utils/Size.h"

namespace nyann {

	class Slice : std::vector<int>
	{
	public:
		// Constructors
		Slice(int start, int end, int step = 0)
			: std::vector<int>{ start, end, step }
		{}
		Slice(int idx)
			: std::vector<int>{ idx, idx + 1, 1 }
		{}

		// operators
		int& operator[](int i)
		{
			return this->operator[](i);
		}
		operator int()
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