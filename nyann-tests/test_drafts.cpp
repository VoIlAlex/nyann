#include "pch.h"
#include "../nyann/nyann/drafts.h"
#include "..//nyann/nyann.h"
#include "../nyann/nyann/drafts/io_draft.cpp"

namespace {
	using namespace nyann;
	TEST(DataSet_draft, Construction)
	{
		DataSet_draft<double> dataset_0({ 3, 3, 3 });
		DataSet_draft<double> dataset_1 = { 1,2,3,4 };
		DataSet_draft<double> dataset_2 = {
			{1, 2, 3, 4},
			{1, 2, 3, 4},
			{1, 2, 3, 4},
			{1, 2, 3, 4}
		};
		DataSet_draft<double> dataset_3 = {
			{
				{
					{000},
					{001}
				},
				{
					{010},
					{011}
				}
			},
			{
				{
					{100},
					{101}
				},
				{
					{110},
					{111}
				}
			}
		};
	}

	TEST(DataSet_draft, Indexing)
	{
		DataSet_draft<double> dataset = {
			{
				{{000}, {001}},
				{{010}, {011}}
			},
			{
				{{100}, {101}},
				{{110}, {111}}
			}
		};

		ASSERT_EQ(dataset[0][0][0].value(), 000);
		ASSERT_EQ(dataset[1][1][1].value(), 111);
		try
		{
			dataset[1][1][1][1];
		}
		catch (std::out_of_range& err) {}
	}

	TEST(DataSet_draft, Slicing)
	{
		DataSet_draft<double> dataset_3 = {
			{
				{
					{000},
					{001}
				},
				{
					{010},
					{011}
				}
			},
			{
				{
					{100},
					{101}
				},
				{
					{110},
					{111}
				}
			}
		};

		DataSet_draft<double> dataset_slice = dataset_3[{0, 2}][0][0];
		DataSet_draft<double> expected_dataset_slice = {
			{000}, {100}
		};

		EXPECT_EQ(expected_dataset_slice, dataset_slice);
	}

	TEST(DataSet_draft, AtIndex)
	{
		DataSet_draft<double> dataset_3 = {
			{
				{
					{000},
					{001}
				},
				{
					{010},
					{011}
				}
			},
			{
				{
					{100},
					{101}
				},
				{
					{110},
					{111}
				}
			}
		};

		double value = dataset_3.at_index({ 1, 1, 1 });
		EXPECT_EQ(value, 111);
	}


	TEST(DataSet_draft, IO_formatting)
	{
		nyann::DataSet_draft<double> dataset = {
			{1.0, 2.0},
			{3.0, 4.0}
		};

		std::stringstream ss;
		ss << dataset << std::endl;

		EXPECT_EQ(ss.str(), "[[1, 2]\n[3, 4]]\n");
	}

	TEST(Index, Increment)
	{
		nyann::Index max_idx = { 2, 1, 4, 2 };
		nyann::Index idx = { 0, 0, 0, 0 };
		int count_of_increments = 0;
		while (idx <= max_idx && ++count_of_increments)
			idx.increment(max_idx);
		ASSERT_EQ(count_of_increments, 3 * 2 * 5 * 3);
	}

	TEST(Index, Decrement)
	{
		nyann::Index idx = { 1, 2, 3, 4 };
		int count = 0;

		while (idx.decrement() != nyann::Index{0, 0, 0, 0})
			count++;

		// minus 2 because
		// the initial value
		// is skipped as well as
		// the min value, i.e.
		// nyann::Index{0, 0, 0, 0}
		EXPECT_EQ(count, 2 * 3 * 4 * 5 - 2);
	}
} // namespace