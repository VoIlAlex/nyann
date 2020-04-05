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

	TEST(Size, PlainSize)
	{
		nyann::Size<> size{ 2, 5, 10 };
		size_t plain_size = size.plain_size();
		size_t expected_plain_size = 100;
		ASSERT_EQ(plain_size, 100);
	}

} // namespace