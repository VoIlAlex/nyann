#pragma once

#include <vector>

namespace nyann {

	class Size : public std::vector<int>
	{
	public:
		using std::vector<int>::vector;
	};

} // namespace nyann