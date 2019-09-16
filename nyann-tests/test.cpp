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
	nyann::DataRow<double> ouput = layer(input);
}