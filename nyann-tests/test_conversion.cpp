#include "pch.h"
#include "../nyann/nyann.h"

namespace {

	TEST(Conversions, Size_to_Index)
	{
		nyann::Size<size_t> size{ 1, 2, 3, 4, 5 };
		nyann::Index<size_t> index = nyann::to_index(size);
		nyann::Index<> expected_index{ 1, 2, 3, 4, 5 };
		ASSERT_EQ(index, expected_index);
	}

} // namespace