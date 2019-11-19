#pragma once

#include <vector>
#include <stdexcept>

namespace nyann {

	template<typename _DT=unsigned int>
	class Size : public std::vector<_DT>
	{
	public:
		using std::vector<_DT>::vector;
		// zero if not
		// presented
		_DT operator[](int i) const
		{
			try
			{
				return std::vector<_DT>::at(i);
			}
			catch (std::out_of_range&)
			{
				return 0;
			}
		}
		_DT& operator[](int i)
		{
			return std::vector<_DT>::at(i);
		}
	};

} // namespace nyann