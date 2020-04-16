#pragma once

#include <vector>
#include <stdexcept>

// For all the framework configurations
#include "../_config.h"

namespace nyann {

	template<typename _DT=size_t>
	class Size : public std::vector<_DT>
	{
	public:
		using std::vector<_DT>::vector;
		// zero if not
		// presented
		const _DT& operator[](int i) const
		{
			try
			{
				return { std::vector<_DT>::at(i) };
			}
			catch (std::out_of_range&)
			{
				return 0;
			}
		}
		_DT& operator[](int i)
		{
			return { std::vector<_DT>::at(i) };
		}

		size_t plain_size()
		{
			size_t size = this->front();
			for (auto it = this->begin() + 1; it != this->end(); it++)
				size *= *it;
			return size;
		}

		operator _DT() const
		{
			return this->at(0);
		}

		static Size<_DT> join(const Size<_DT>& size_1, const Size<_DT> size_2)
		{
			Size<_DT> size_result(size_1.size() + size_2.size());
			for (int i = 0; i < size_1.size(); i++)
				size_result[i] = size_1[i];
			for (int i = size_1.size(), j = 0; i < size_1.size() + size_2.size(); i++, j++)
				size_result[i] = size_2[j];
			return size_result;
		}
	};

	template<typename _DT>
	bool operator==(const Size<_DT>& left, const Size<_DT>& right)
	{
		if (left.size() != right.size())
			return false;
		for (int i = 0; i < left.size(); i++)
			if (left.at(i) != right.at(i))
				return false;
		return true;
	}

	template<typename _DT>
	bool operator!=(const Size<_DT>& left, const Size<_DT>& right)
	{
		if (left.size() != right.size())
			return true;
		for (int i = 0; i < left.size(); i++)
			if (left.at(i) != right.at(i))
				return true;
		return false;
	}

} // namespace nyann