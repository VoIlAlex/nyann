#include "pch.h"
#include "..//nyann//nyann.h"
#include "..//nyann//nyann/drafts.h"

namespace {

	TEST(TrainDataSample_draft, Construction)
	{
		nyann::TrainDataSample_draft<double> data_sample = {
			{ {1, 2, 3}, {1, 2, 3} },
			{ {1, 2, 3}, {1, 2, 3} }
		};
	}

	TEST(TrainDataSample_draft, GetInput)
	{
		nyann::TrainDataSample_draft<double> data_sample = {
			{ {1, 2, 3}, {1, 2, 3} },
			{ {3, 2, 1}, {3, 2, 1} }
		};
		nyann::DataSet_draft<double> expected_input = { {1, 2, 3}, { 1, 2, 3 } };

		ASSERT_EQ(data_sample.get_input(), expected_input);
	}

	TEST(TrainDataSample_draft, GetOutput)
	{
		nyann::TrainDataSample_draft<double> data_sample = {
			{ {1, 2, 3}, {1, 2, 3} },
			{ {3, 2, 1}, {3, 2, 1} }
		};
		nyann::DataSet_draft<double> expected_output = { {3, 2, 1}, { 3, 2, 1 } };

		ASSERT_EQ(data_sample.get_output(), expected_output);
	}


	TEST(TrainDataSet_draft, Construction)
	{
		nyann::TrainDataSet_draft<double> train_data_set = {
			{ { {1}, {2}, {3} }, { {4}, {5}, {6} } },
			{ { {1}, {2}, {3} }, { {4}, {5}, {6} } }
		};
	}

	TEST(TrainDataSet_draft, GettingSample)
	{
		nyann::TrainDataSet_draft<double> train_data_set = {
			{ { {1}, {2}, {3} }, { {4}, {5}, {6} } },
			{ { {1}, {2}, {3} }, { {4}, {5}, {6} } }
		};

		nyann::TrainDataSample_draft<double> data_sample = train_data_set[0];
	}

	TEST(TrainDataSet_draft, SampleRightInput)
	{
		nyann::TrainDataSet_draft<double> train_data_set = {
			{ { {1}, {2}, {3} }, { {4}, {5}, {6} } },
			{ { {4}, {5}, {6} }, { {1}, {2}, {3} } }
		};

		nyann::TrainDataSample_draft<double> data_sample = train_data_set[0];
		nyann::DataSet_draft<double> input = data_sample.get_input();
		nyann::DataSet_draft<double> expected_input = { {1}, {2}, {3} };
		EXPECT_EQ(input, expected_input);
	}

	TEST(TrainDataSet_draft, SampleRightOutput)
	{
		nyann::TrainDataSet_draft<double> train_data_set = {
			{ { {1}, {2}, {3} }, { {4}, {5}, {6} } },
			{ { {4}, {5}, {6} }, { {1}, {2}, {3} } }
		};

		nyann::TrainDataSample_draft<double> data_sample = train_data_set[0];
		nyann::DataSet_draft<double> output = data_sample.get_output();
		nyann::DataSet_draft<double> expected_output = { {4}, {5}, {6} };
		EXPECT_EQ(output, expected_output);
	}

}