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

	TEST(Size, ShiftAt)
	{
		nyann::Size<> size{ 2, 5, 10 };
		size_t shift_at_minus_1 = size.shift_at(-1);
		size_t shift_at_0 = size.shift_at(0);
		size_t shift_at_1 = size.shift_at(1);
		size_t shift_at_2 = size.shift_at(2);

		ASSERT_EQ(shift_at_minus_1, 2 * 5 * 10);
		ASSERT_EQ(shift_at_0, 5 * 10);
		ASSERT_EQ(shift_at_1, 10);
		ASSERT_EQ(shift_at_2, 1);
	}

	TEST(Size, Join)
	{
		nyann::Size<> size_1{ 1, 2, 3 };
		nyann::Size<> size_2{ 4, 5, 6 };
		nyann::Size<> expected_joint_size{ 1, 2, 3, 4, 5, 6 };
		ASSERT_EQ(nyann::Size<>::join(size_1, size_2), expected_joint_size);
	}

} // namespace