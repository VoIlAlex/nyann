#include "pch.h"
#include "..//nyann//nyann.h"

namespace {

	TEST(Slice, Construction)
	{
		nyann::Slice<> slice_1 = { 1, 5, 2 };
		nyann::Slice<> slice_2(1, 5, 2);
		nyann::Slice<> slice_3(3);
	}

	TEST(Slice, ConvertToScalar)
	{
		nyann::Slice<> slice_1 = { 1, 5, 2 };
		ASSERT_EQ(slice_1, 1);
	}

	TEST(Slice, Getters)
	{
		nyann::Slice<> slice_1 = { 1, 5, 2 };
		ASSERT_EQ(slice_1[0], 1);
		ASSERT_EQ(slice_1[1], 5);
		ASSERT_EQ(slice_1[2], 2);

		slice_1.from_value() = 10;
		slice_1.to_value() = 20;
		slice_1.step_value() = 5;

		ASSERT_EQ(slice_1.from_value(), 10);
		ASSERT_EQ(slice_1.to_value(), 20);
		ASSERT_EQ(slice_1.step_value(), 5);
	}

} // namespace