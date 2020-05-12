#include "pch.h"
#include "..//nyann//nyann.h"

namespace {

	TEST(Index, Construction)
	{
		nyann::Index<unsigned int> empty_idx;
		nyann::Index<unsigned int> idx_1;
		nyann::Index<unsigned int> idx_2 = { 2, 1, 4, 2 };
		nyann::Index<unsigned int> idx_3 (idx_2);
		nyann::Index<unsigned int> idx_4 (std::move(idx_3));
		std::vector<unsigned int> vec_idx = { 1, 3, 4, 6 };
		nyann::Index<unsigned int> idx_5 (vec_idx);
		nyann::Index<unsigned int> idx_6 (std::move(vec_idx));
		ASSERT_EQ(idx_1, empty_idx);
		ASSERT_EQ(idx_3, empty_idx);
		ASSERT_EQ(idx_4, idx_2);
		ASSERT_EQ(idx_5, idx_6);
		ASSERT_TRUE(vec_idx.empty());
	}

	TEST(Index, Increment)
	{
		nyann::Index<unsigned int>  max_idx = { 2, 1, 4, 2 };
		nyann::Index<unsigned int>  idx = { 0, 0, 0, 0 };
		int count_of_increments = 0;
		while (idx <= max_idx && ++count_of_increments)
			idx.increment(nyann::Index(), max_idx);
		ASSERT_EQ(count_of_increments, 3 * 2 * 5 * 3);
	}

	TEST(Index, IncrementWithSteps)
	{
		nyann::Index<unsigned int>  max_idx = { 2, 1, 4, 2 };
		nyann::Index<unsigned int>  idx = { 0, 0, 0, 0 };
		nyann::Index<unsigned int>  steps = { 2, 1, 2, 2 };
		int count_of_increments = 0;
		while (idx <= max_idx && ++count_of_increments)
			idx.increment(nyann::Index(), max_idx, steps);
		ASSERT_EQ(count_of_increments, 2 * 2 * 3 * 2);
	}

	TEST(Index, IncrementWithStepsToBorder)
	{
		nyann::Index<unsigned int>  max_idx = { 2, 1, 4, 2 };
		nyann::Index<unsigned int>  min_index = { 0, 0, 0, 0 };
		nyann::Index<unsigned int>  idx = { 0, 0, 0, 0 };
		nyann::Index<unsigned int>  steps = { 1, 1, 1, 1 };
		int count_of_increments = 0;
		while (idx.all_lower(max_idx) && ++count_of_increments)
			idx.increment(min_index, max_idx, steps, true);
		ASSERT_EQ(count_of_increments, 2 * 1 * 4 * 2);
	}

	TEST(Index, Decrement)
	{
		nyann::Index<unsigned int>  idx = { 1, 2, 3, 4 };
		int count = 0;

		do
			count++;
		while (idx.decrement() > nyann::Index<>{ 0, 0, 0, 0 });

		EXPECT_EQ(count, 2 * 3 * 4 * 5 - 1);
	}

	TEST(Index, DecrementToMin)
	{
		nyann::Index<unsigned int>  idx = { 2, 2, 2, };
		nyann::Index<unsigned int>  min_idx = { 1, 1, 1 };
		try
		{
			while (true) idx.decrement(min_idx);
		}
		catch (std::out_of_range& e) {}
		ASSERT_EQ(idx, min_idx);
	}

	TEST(Index, ToBool)
	{
		nyann::Index<unsigned int>  idx_1 = { 0, 0, 1 };
		nyann::Index<unsigned int>  idx_2 = { 0, 1, 0 };
		nyann::Index<unsigned int>  idx_3 = { 1, 0, 0 };
		nyann::Index<unsigned int>  idx_4 = { 0, 0, 0 };

		ASSERT_TRUE(bool(idx_1));
		ASSERT_TRUE(bool(idx_2));
		ASSERT_TRUE(bool(idx_3));
		ASSERT_FALSE(bool(idx_4));
	}

	TEST(Index, BoolOperations)
	{
		nyann::Index<unsigned int>  idx_1 = { 0, 0, 1 };
		nyann::Index<unsigned int>  idx_2 = { 0, 0, 2 };

		nyann::Index<unsigned int>  idx_3 = { 0, 1, 0 };
		nyann::Index<unsigned int>  idx_4 = { 0, 2, 0 };

		nyann::Index<unsigned int>  idx_5 = { 1, 0, 0 };
		nyann::Index<unsigned int>  idx_6 = { 2, 0, 0 };


		ASSERT_EQ((idx_1 == nyann::Index<>{ 0, 0, 1 }), true);
		ASSERT_EQ(idx_1 == idx_2, false);

		ASSERT_EQ(idx_1 != idx_2, true);
		ASSERT_EQ(idx_1 != idx_1, false);

		ASSERT_EQ(idx_1 < idx_2, true);
		ASSERT_EQ(idx_2 < idx_3, true);

		ASSERT_EQ(idx_2 > idx_1, true);
		ASSERT_EQ(idx_3 > idx_2, true);

		ASSERT_EQ(idx_1 <= idx_1, true);
		ASSERT_EQ(idx_1 <= idx_2, true);
		ASSERT_EQ(idx_2 <= idx_2, true);
		ASSERT_EQ(idx_2 <= idx_3, true);
		ASSERT_EQ(idx_3 <= idx_3, true);

		ASSERT_EQ(idx_1 >= idx_1, true);
		ASSERT_EQ(idx_2 >= idx_1, true);
		ASSERT_EQ(idx_2 >= idx_2, true);
		ASSERT_EQ(idx_3 >= idx_2, true);
		ASSERT_EQ(idx_3 >= idx_3, true);
	}

	TEST(Index, InitialState)
	{
		nyann::Index<unsigned int>  idx_1 = { 2, 3, 1 };
		nyann::Index<unsigned int> initial_state = { 2, 3, 1 };
		ASSERT_TRUE(nyann::Index<unsigned int>(idx_1.initial_state()) == initial_state);
		idx_1.decrement();
		ASSERT_TRUE(nyann::Index<unsigned int>(idx_1.initial_state()) == initial_state);
		idx_1.increment().increment();
		ASSERT_TRUE(nyann::Index<unsigned int>(idx_1.initial_state()) == initial_state);
	}

} // namespace