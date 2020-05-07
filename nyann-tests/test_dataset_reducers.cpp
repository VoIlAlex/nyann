#include "pch.h"
#include "../nyann/nyann.h"

namespace {

	TEST(DataSetReducers, LambdaReducer)
	{
		nyann::LambdaReducer<double> reducer([](const std::vector<double>& data, const nyann::Size<size_t>& size) {
			double result = 0;
			for (int i = 0; i < data.size(); i++)
				if (i % 2 == 0)
					result += data[i];
			return result;
		});

		nyann::DataSet<double> dataset = { 1, 2, 3, 4 };

		double result = dataset.reduce(reducer);

		ASSERT_EQ(result, 4);
	}

	TEST(DataSetReducers, ForEachReducer)
	{
		nyann::ForEachReducer<double> reducer([](const double& left, const double& right) {
			return left > right ? left : right;
		});

		nyann::DataSet<double> dataset = { 1, 2, 3, 4 };

		double result = dataset.reduce(reducer);

		ASSERT_EQ(result, 4);
	}

	TEST(DataSetReducers, AddReducer)
	{
		nyann::AddReducer<double> reducer;

		nyann::DataSet<double> dataset = { 1, 2, 3, 4 };

		double result = dataset.reduce(reducer);

		ASSERT_EQ(result, 10);
	}

	TEST(DataSetReducers, MultReducer)
	{
		nyann::MultReducer<double> reducer;

		nyann::DataSet<double> dataset = { 1, 2, 3, 4 };

		double result = dataset.reduce(reducer);

		ASSERT_EQ(result, 24);
	}

	TEST(DataSetReducers, AverageReducer)
	{
		nyann::AverageReducer<double> reducer;

		nyann::DataSet<double> dataset = { 1, 2, 3, 4 };

		double result = dataset.reduce(reducer);

		ASSERT_EQ(result, 2.5);
	}


} // namespace