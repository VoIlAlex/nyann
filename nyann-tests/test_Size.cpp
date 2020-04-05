#include "pch.h"
#include "..//nyann//nyann.h"

namespace {

	TEST(Size, Construction)
	{
		nyann::Size<> size{ 2, 5, 10 };
	}

	TEST(Size, GettingSize)
	{
		nyann::Size<> size{ 2, 5, 10 };
		ASSERT_EQ(size[0], 2);
		ASSERT_EQ(size[1], 5);
		ASSERT_EQ(size[2], 10);
	}

} // namespace