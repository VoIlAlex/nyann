#pragma once

#include <vector>
#include <stdexcept>

namespace nyann {

	class Size : public std::vector<int>
	{
	public:
		using std::vector<int>::vector;
		// zero if not
		// presented
		int operator[](int i) const
		{
			try
			{
				return std::vector<int>::at(i);
			}
			catch (std::out_of_range&)
			{
				return 0;
			}
		}
		int& operator[](int i)
		{
			return std::vector<int>::at(i);
		}
	};

} // namespace nyann