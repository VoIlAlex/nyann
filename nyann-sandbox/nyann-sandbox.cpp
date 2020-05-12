// nyann-sandbox.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "../nyann/nyann.h"

int main()
{
	nyann::TrainDataSet<double> dataset = {
		{
			{
				{1.5, 1.5},
				{1.5, 0.5},
				{0.5, 1.5},
				{0.5, 0.5}
			},
			{
				{0.5, 0.5},
				{0.5, 0.5},
				{0.5, 0.5},
				{0.5, 0.5}
			}
		},
		{
			nyann::DataSet<double>{0.},
			nyann::DataSet<double>{1.}
		}
	};

	nyann::Layer<double>* layer_1 = new nyann::FCLayer<double>(nyann::Size<>{ 4, 2 }, nyann::Size<>{2});
	nyann::Layer<double>* layer_2 = new nyann::FCLayer<double>(nyann::Size<>{ 2, 1 });
	nyann::Loss<double>* loss = new nyann::MSELoss<double>();
	nyann::Optimizer<double>* optimizer = new nyann::SGDOptimizer<double>(0.1);
	nyann::Net<> net;
	net.set_loss(loss);
	net.set_optimizer(optimizer);
	net.add_layer(layer_1);
	net.add_layer(layer_2);

	net.fit(dataset, nyann::RequiredErrorCondition<double>(0.5));
	nyann::DataSet<double> input = dataset.get_input();
	nyann::DataSet<double> expected_output = dataset.get_output();
	nyann::DataSet<double> output = net.predict(input);

	net.save("weights.txt");
	net.read("weights.txt");

	const nyann::DataSetReducer<double>& abs_sum_reducer = nyann::ForEachReducer<double>([](const double& left, const double& right) {
		return abs(left) + abs(right);
	});

	double error = (expected_output - output).reduce(abs_sum_reducer);
	std::cout << "Final error: " << error;
}