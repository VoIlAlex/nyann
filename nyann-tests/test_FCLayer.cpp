#include "pch.h"
#include "..//nyann//nyann.h"

namespace {
	TEST(FCLayer, Construction)
	{
		nyann::FCLayer<double> layer({ 10, 10 });
	}
	TEST(FCLayer, BatchProcessing)
	{
		nyann::FCLayer<double> layer({ 2, 1 });
		nyann::TrainDataSet<double> dataset = {
			{{1.5, 1.5}, {0.}},
			{{1.5, 0.5}, {1.}},
			{{0.5, 1.5}, {1.}},
			{{0.5, 0.5}, {0.}}
		};
		nyann::DataSet<double> result = layer(dataset.get_input());
		ASSERT_NE(result, nyann::DataSet<double>());
	}

	TEST(FCLayer, BatchBackPropagation)
	{
		nyann::FCLayer<double> layer({ 2, 1 });
		nyann::TrainDataSet<double> dataset = {
			{{1.5, 1.5}, {0.}},
			{{1.5, 0.5}, {1.}},
			{{0.5, 1.5}, {1.}},
			{{0.5, 0.5}, {0.}}
		};
		auto input = dataset.get_input();
		auto output = dataset.get_output();
		auto result = layer(input);
		auto errors = result - output;
		auto initial_weights = layer.get_weights();
		layer.back_propagation(
			errors
		);
		ASSERT_TRUE(initial_weights != layer.get_weights());
	}
} // namespace