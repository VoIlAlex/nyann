#include "pch.h"
#include "../nyann/nyann.h"

namespace {

	TEST(DataSetOperations, LambdaOperation)
	{
		nyann::LambdaOperation<double> operation([](std::vector<double>& data, nyann::Size<>& size) {
			for (int i = 0; i < data.size(); i++)
				if (i % 2 == 0)
					data[i] *= 2;
				else
					data[i] *= 3;
		});

		nyann::DataSet<double> dataset = { 1, 2, 3, 4 };
		dataset.execute_inplace(operation);
		nyann::DataSet<double> expected_dataset = { 2, 6, 6, 12 };
		ASSERT_EQ(dataset, expected_dataset);
	}

	TEST(DataSetOperations, ForEachOperation)
	{
		nyann::ForEachOperation<double> operation([](double& item) {
			item /= 2;
		});

		nyann::DataSet<double> dataset = { 1, 2, 3, 4 };
		dataset.execute_inplace(operation);
		nyann::DataSet<double> expected_dataset = { 0.5, 1, 1.5, 2 };
		ASSERT_EQ(dataset, expected_dataset);
	}

	TEST(DataSetOperations, PowerOperation)
	{
		nyann::PowerOperation<double> operation(3);
		nyann::DataSet<double> dataset = { 1, 2, 3, 4 };
		dataset.execute_inplace(operation);
		nyann::DataSet<double> expected_dataset = { 1, 8, 27, 64 };
		ASSERT_EQ(dataset, expected_dataset);
	}

	TEST(DataSetOperations, MultOperation)
	{
		nyann::MultOperation<double> operation(3);
		nyann::DataSet<double> dataset = { 1, 2, 3, 4 };
		dataset.execute_inplace(operation);
		nyann::DataSet<double> expected_dataset = { 3, 6, 9, 12 };
		ASSERT_EQ(dataset, expected_dataset);
	}

	TEST(DataSetOperations, AbsOperation)
	{
		nyann::AbsOperation<double> operation;
		nyann::DataSet<double> dataset = { -1, -2, -3, -4 };
		dataset.execute_inplace(operation);
		nyann::DataSet<double> expected_dataset = { 1, 2, 3, 4 };
		ASSERT_EQ(dataset, expected_dataset);
	}

} // namespace