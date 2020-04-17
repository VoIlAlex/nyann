#include "pch.h"
#include "..//nyann//nyann.h"

#ifdef DRAFT_DATASET_2_0_0_ALPHA_TEST
#include "../nyann/nyann/drafts/io_draft.h"
#include "../nyann/nyann/drafts/io_draft.cpp"
#endif

namespace {
#ifdef DRAFT_DATASET_2_0_0_ALPHA_TEST

	TEST(DataSet, Construction)
	{
		nyann::DataSet_draft<float> dataset = {
			{1.0, 2.0},
			{3.0, 4.0}
		};
	}
	/*TEST(DataSet, IO)
	{
		nyann::DataSet_draft<float> dataset = {
			{1.0, 2.0},
			{3.0, 4.0}
		};
		std::cout << dataset << std::endl;
	}
*/
	TEST(TrainDataSet, Construction)
	{
		nyann::TrainDataSet_draft<double> dataset = {
			{ {1.5, 1.5},
			{1.5, 0.5},
			{0.5, 1.5},
			{0.5, 0.5} },
			{ {0.},
			  {1.},
			  {1.},
			  {0.} }
		};
	}

	TEST(TrainDataSet, GetInput)
	{
		nyann::TrainDataSet_draft<double> dataset = {
			{ {1.5, 1.5},
			{1.5, 0.5},
			{0.5, 1.5},
			{0.5, 0.5} },
			{ {0.},
			  {1.},
			  {1.},
			  {0.} }
		};

		nyann::DataSet_draft<double> expected_input = {
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
		nyann::TrainDataSet_draft<double> dataset = {
			{ {1.5, 1.5},
			{1.5, 0.5},
			{0.5, 1.5},
			{0.5, 0.5} },
			{ {0.},
			  {1.},
			  {1.},
			  {0.}}
		};

		nyann::DataSet_draft<double> expected_output = {
			{0.},
			{1.},
			{1.},
			{0.}
		};

		auto output = dataset.get_output();
		bool equality = output == expected_output;

		ASSERT_TRUE(equality);
	}
#elif defined(DRAFT_DATASET_2_0_0_PRERELEASE)
	TEST(DataSet, Construction)
	{
		nyann::DataSet<float> dataset = {
			{1.0, 2.0},
			{3.0, 4.0}
		};
	}
	/*TEST(DataSet, IO)
	{
		nyann::DataSet<float> dataset = {
			{1.0, 2.0},
			{3.0, 4.0}
		};
		std::cout << dataset << std::endl;
	}
*/
	TEST(TrainDataSet, Construction)
	{
		nyann::TrainDataSet<double> dataset = {
			{ {1.5, 1.5},
			{1.5, 0.5},
			{0.5, 1.5},
			{0.5, 0.5} },
			{ {0.},
			  {1.},
			  {1.},
			  {0.} }
		};
	}

	TEST(TrainDataSet, GetInput)
	{
		nyann::TrainDataSet<double> dataset = {
			{ {1.5, 1.5},
			{1.5, 0.5},
			{0.5, 1.5},
			{0.5, 0.5} },
			{ {0.},
			  {1.},
			  {1.},
			  {0.} }
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
			{ {1.5, 1.5},
			{1.5, 0.5},
			{0.5, 1.5},
			{0.5, 0.5} },
			{ {0.},
			  {1.},
			  {1.},
			  {0.}}
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

#else
	TEST(DataSet, Construction)
	{
		nyann::DataSet<float> dataset = {
			{1.0, 2.0},
			{3.0, 4.0}
		};
	}
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


#endif 
} // namespace