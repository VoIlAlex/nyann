#include "pch.h"
#include "..//nya-nn//nyann.h"



TEST(DataSet, Construction)
{
	nyann::DataRow<float> row = { 1.0, 2.0, 3.0 };
	nyann::DataSet<float> dataset = {
		{1.0, 2.0},
		{3.0, 4.0}
	};
}

TEST(DataRow, Construction)
{
	nyann::DataRow<float> row = { 1.0, 2.0, 3.0 };
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

TEST(Size, Construction)
{
	nyann::Size size{ 2, 5, 10 };
}

TEST(FCLayer, Construction)
{
	nyann::FCLayer<double> layer({ 10, 10 });
}

TEST(FCLayer, ProcessingRow)
{
	nyann::FCLayer<double> layer({ 5, 1 });
	nyann::DataRow<double> input = { 1.0, 2.0, 3.0, 4.0, 5.0 };
	nyann::DataRow<double> output = layer(input);
}

TEST(FCLayer, BackPropagationRow)
{
	nyann::FCLayer<double> layer({ 5, 1 });
	nyann::DataRow<double> input = { 1.0, 2.0, 3.0, 4.0, 5.0 };
	nyann::DataRow<double> output = layer(input);
	std::vector<double> errors = layer.back_propagation(
		output - nyann::DataRow<double>{1.0},
		{ 1.0 }
	);
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


TEST(Net, Construction)
{
	nyann::Net net;
}


TEST(Net, LayersSetting)
{
	nyann::Layer<double>* layer_1 = new nyann::FCLayer<double>(nyann::Size(2, 2));
	nyann::Layer<double>* layer_2 = new nyann::FCLayer<double>(nyann::Size(2, 1));
	nyann::Net net;
	net.add_layer(layer_1);
	net.add_layer(layer_2);
}


TEST(Net, Fitting)
{
	nyann::Layer<double>* layer_1 = new nyann::FCLayer<double>(nyann::Size{ 2, 2 });
	nyann::Layer<double>* layer_2 = new nyann::FCLayer<double>(nyann::Size{ 2, 1 });
	nyann::Net net;
	net.add_layer(layer_1);
	net.add_layer(layer_2);

	nyann::TrainDataSet<double> dataset = {
		{{1.5, 1.5}, {0.}},
		{{1.5, 0.5}, {1.}},
		{{0.5, 1.5}, {1.}},
		{{0.5, 0.5}, {0.}}
	};

	net.fit(dataset, 10);
}


TEST(Net, Prediction)
{
	// Create a model

	nyann::Layer<double>* layer_1 = new nyann::FCLayer<double>(nyann::Size{ 2, 1 });

	nyann::Net net;

	net.add_layer(layer_1);

	// Train the model

	nyann::TrainDataSet<double> dataset = {
		{{1.5, 1.5}, {1.}},
		{{1.5, 0.5}, {0.}},
		{{0.5, 1.5}, {0.}},
		{{0.5, 0.5}, {-1.}}
	};

	net.fit(dataset, 10000, 1, 0.003);


	// Test the model

	double precision = 0.5;
	nyann::TrainDataSet<double> test_dataset = {
		{{1.5, 1.5}, {1.}},
		{{1.5, 0.5}, {0.}},
		{{0.5, 1.5}, {0.}},
		{{0.5, 0.5}, {0.}}
	};

	nyann::DataSet<double> input;
	double expected_value, predicted_value;
	for (auto data : test_dataset)
	{
		input = { data[0] };
		expected_value = data[1][0];
		predicted_value = net.predict(input)[0][0];
		if (abs(predicted_value - 0) < abs(predicted_value - 1))
			predicted_value = 0;
		else
			predicted_value = 1;
		ASSERT_NEAR(expected_value, predicted_value, precision);
	}
}