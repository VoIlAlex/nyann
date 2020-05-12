#include "pch.h"
#include "../nyann/nyann.h"

namespace {
	using namespace nyann;
	TEST(DataSet, Construction)
	{
		DataSet<double> dataset_0({ 3, 3, 3 });
		DataSet<double> dataset_1 = { 1,2,3,4 };
		DataSet<double> dataset_2 = {
			{1, 2, 3, 4},
			{1, 2, 3, 4},
			{1, 2, 3, 4},
			{1, 2, 3, 4}
		};
		DataSet<double> dataset_3 = {
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

	TEST(DataSet, Indexing)
	{
		DataSet<double> dataset = {
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

	TEST(DataSet, Slicing_1)
	{
		DataSet<double> dataset_3 = {
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

		DataSet<double> dataset_slice = dataset_3[{0, 2}][0][0];
		DataSet<double> expected_dataset_slice = {
			{000}, {100}
		};

		EXPECT_EQ(expected_dataset_slice, dataset_slice);
	}

	TEST(DataSet, Slicing_2)
	{
		DataSet<double> dataset_3 = {
			{
				{
					{1010},
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

		DataSet<double> dataset_slice = dataset_3[{0, -1}][{0, -1}][0];
		DataSet<double> expected_dataset_slice = {
			{1010, 010}, {100, 110}
		};

		EXPECT_EQ(expected_dataset_slice, dataset_slice);
	}

	TEST(DataSet, Slicing_3)
	{
		DataSet<double> dataset_3 = {
			{
				{
					{1010},
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

		DataSet<double> dataset_slice = dataset_3[{0, 2}][0][0];
		DataSet<double> expected_dataset_slice = {
			1010, 100
		};

		EXPECT_EQ(expected_dataset_slice, dataset_slice);
	}

	TEST(DataSet, SliceSetting_1)
	{
		DataSet<double> dataset_3 = {
			{
				{1010, 001},
				{010, 011}
			},
			{
				{100, 101},
				{110, 111}
			}
		};

		dataset_3[{0, 2}][1][{0, 2}].set_value(DataSet<double>{
			{ 
				{0, 0} 
			},
			{ 
				{0, 0} 
			}
		});

		double first_zero = double(dataset_3[0][1][0]);
		double second_zero = double(dataset_3[0][1][1]);
		double third_zero = double(dataset_3[1][1][0]);
		double fourth_zero = double(dataset_3[1][1][1]);

		ASSERT_EQ(first_zero, 0);
		ASSERT_EQ(second_zero, 0);
		ASSERT_EQ(third_zero, 0);
		ASSERT_EQ(fourth_zero, 0);
	}

	TEST(DataSet, SliceSetting_2)
	{
		DataSet<double> dataset_3 = {
			{
				{
					{1, 1, 1, 1}, 
					{1, 1, 1, 1}, 
					{1, 1, 1, 1},
					{1, 1, 1, 1}
				},
				{
					{1, 1, 1, 1}, 
					{1, 1, 1, 1}, 
					{1, 1, 1, 1}, 
					{1, 1, 1, 1}
				}
			},
			{
				{
					{1, 1, 1, 1},
					{1, 1, 1, 1},
					{1, 1, 1, 1},
					{1, 1, 1, 1}
				},
				{
					{1, 1, 1, 1},
					{1, 1, 1, 1},
					{1, 1, 1, 1},
					{1, 1, 1, 1}
				}
			}
		};

		dataset_3[{0, 2}][1][0][{2, 4}].set_value(DataSet<double>{
			{
				{0, 0}
			},
			{
				{0, 0}
			}
		});

		double first_zero = double(dataset_3[0][1][0][2]);
		double second_zero = double(dataset_3[0][1][0][3]);
		double third_zero = double(dataset_3[1][1][0][2]);
		double fourth_zero = double(dataset_3[1][1][0][3]);

		ASSERT_EQ(first_zero, 0);
		ASSERT_EQ(second_zero, 0);
		ASSERT_EQ(third_zero, 0);
		ASSERT_EQ(fourth_zero, 0);
	}

	TEST(DataSet, SplitInputOutput)
	{
		typedef nyann::DataSet<double> dt;
		dt dataset = {
			{1.0, 1.0, 1.0, 3.0},
			{2.0, 2.0, 2.0, 6.0},
			{1.0, 2.0, 3.0, 6.0},
			{0.0, 0.0, 0.0, 0.0}
		};

		dt X = dataset[{0, -1}][{0, 3}];
		dt y = dataset[{0, -1}][{3, 4}];

		dt X_expected = {
			{1.0, 1.0, 1.0},
			{2.0, 2.0, 2.0},
			{1.0, 2.0, 3.0},
			{0.0, 0.0, 0.0}
		};

		dt y_expected = {
			dt{3.0},
			dt{6.0},
			dt{6.0},
			dt{0.0}
		};

		EXPECT_EQ(X, X_expected);
		EXPECT_EQ(y, y_expected);
	}

	TEST(DataSet, SizeGetting_1)
	{
		DataSet<double> dataset = {
			{1, 2, 3, 4},
			{1, 2, 3, 4},
			{1, 2, 3, 4},
			{1, 2, 3, 4}
		};
		nyann::Size<> size = dataset.size();
		nyann::Size<> expected_size = nyann::Size<>{ 4, 4 };
		ASSERT_EQ(size, expected_size);
	}

	TEST(DataSet, SizeGetting_2)
	{
		DataSet<double> dataset = {
			{1, 2, 3, 4},
			{1, 2, 3, 4},
			{1, 2, 3, 4},
			{1, 2, 3, 4}
		};
		nyann::Size<> size = dataset.get_size();
		nyann::Size<> expected_size = nyann::Size<>{ 4, 4 };
		ASSERT_EQ(size, expected_size);
	}

	TEST(DataSet, AtIndex)
	{
		DataSet<double> dataset_3 = {
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

	TEST(DataSet, Iteration_default)
	{
		DataSet<double> dataset = {
			{1, 2, 3, 4},
			{1, 2, 3, 4},
			{1, 2, 3, 4},
			{1, 2, 3, 4}
		};

		DataSet<double>::iterator it(&dataset, 0);
		ASSERT_EQ(*it, double(dataset[0][0]));
		ASSERT_EQ(*(it + 4), double(dataset[1][0]));
	}	
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
} // namespace