#include "pch.h"
#include "..//nyann//nyann.h"


namespace {
	TEST(DataSet, Construction)
	{
		nyann::DataRow<float> row = { 1.0, 2.0, 3.0 };
		nyann::DataSet<float> dataset = {
			{1.0, 2.0},
			{3.0, 4.0}
		};
	}
#ifndef DEPRECATED_LAYER_ROW_PROCESSING
	TEST(DataRow, Construction)
	{
		nyann::DataRow<float> row = { 1.0, 2.0, 3.0 };
	}
#endif
	TEST(DataSet, IO)
	{
		nyann::DataSet<float> dataset = {
			{1.0, 2.0},
			{3.0, 4.0}
		};
		std::cout << dataset << std::endl;
	}

	TEST(TrainDataSet, Construction)
	{
		nyann::TrainDataSet<float> dataset = {
			{{1.5, 1.5}, {0.}},
			{{1.5, 0.5}, {1.}},
			{{0.5, 1.5}, {1.}},
			{{0.5, 0.5}, {0.}}
		};
	}

	TEST(TrainDataSet, GetInput)
	{
		nyann::TrainDataSet<double> dataset = {
			{{1.5, 1.5}, {0.}},
			{{1.5, 0.5}, {1.}},
			{{0.5, 1.5}, {1.}},
			{{0.5, 0.5}, {0.}}
		};

		nyann::DataSet<double> expected_input = {
			{1.5, 1.5},
			{1.5, 0.5},
			{0.5, 1.5},
			{0.5, 0.5}
		};
		ASSERT_EQ(
			dataset.get_input(),
			expected_input
		);
	}

	TEST(TrainDataSet, GetOutput)
	{
		nyann::TrainDataSet<double> dataset = {
			{{1.5, 1.5}, {0.}},
			{{1.5, 0.5}, {1.}},
			{{0.5, 1.5}, {1.}},
			{{0.5, 0.5}, {0.}}
		};

		nyann::DataSet<double> expected_output = {
			{0.},
			{1.},
			{1.},
			{0.}
		};

		auto output = dataset.get_output();
		bool equality = output == expected_output;

		ASSERT_TRUE(equality);
	}
} // namespace