#include "pch.h"
#include "../nyann/nyann/drafts.h"

namespace {

	TEST(utils_draft, abs_DataSet_draft)
	{
		nyann::DataSet_draft<double> dataset = {
			{-1.0, -2.0},
			{-2.0, 1.0}
		};
		nyann::DataSet_draft<double> abs_dataset_expected = {
			{1.0, 2.0},
			{2.0, 1.0}
		};

		EXPECT_EQ(abs(dataset), abs_dataset_expected);
	}

} // namespace 