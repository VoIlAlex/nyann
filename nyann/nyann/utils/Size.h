#pragma once

#include <vector>
#include <stdexcept>

// For all the framework configurations
#include "../_config.h"

namespace nyann {

	template<typename _DT=int>
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