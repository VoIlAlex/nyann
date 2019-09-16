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

TEST(Size, Construction)
{
	nyann::Size size{ 2, 5, 10 };
}

TEST(FCLayer, Construction)
{
	nyann::FCLayer<double> layer({ 10, 10 });
}

TEST(FCLayer, Processing)
{
	nyann::FCLayer<double> layer({ 5, 1 });
	nyann::DataRow<double> input = { 1.0, 2.0, 3.0, 4.0, 5.0 };
	nyann::DataRow<double> output = layer(input);
}

TEST(FCLayer, BackPropagation)
{
	nyann::FCLayer<double> layer({ 5, 1 });
	nyann::DataRow<double> input = { 1.0, 2.0, 3.0, 4.0, 5.0 };
	nyann::DataRow<double> output = layer(input);
	std::vector<double> errors = layer.back_propagation(
		output - nyann::DataRow<double>{1.0},
		{ 1.0 }
	);
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
	nyann::Layer<double>* layer_1 = new nyann::FCLayer<double>(nyann::Size(2, 2));
	nyann::Layer<double>* layer_2 = new nyann::FCLayer<double>(nyann::Size(2, 1));
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


}