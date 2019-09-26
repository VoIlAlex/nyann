#include "pch.h"
#include "../nya-nn/nyann/drafts.h"
#include "..//nya-nn/nyann.h"

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
		DataSet_draft<double> dataset({ 3, 3, 3 });
		dataset[0][0][0];
		dataset[2][2][2];
		dataset[1][1];
	}

	TEST(DataSet_draft, Slicing)
	{
		DataSet_draft<double> dataset({ 3, 3, 3 });
		dataset[{1, 2}][{2, 3}][{0, 3}];
	}

} // namespace