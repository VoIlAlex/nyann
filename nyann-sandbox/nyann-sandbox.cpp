// nyann-sandbox.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "../nyann/nyann.h"

using namespace nyann;

TrainDataSet<double> get_dataset()
{
	TrainDataSet<double> dataset = {
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
			DataSet<double>{0.},
			DataSet<double>{1.}
		}
	};
	return dataset;
}

Net<double> get_net()
{
	// �������� �������� ����������� 
	// ��������� ����
	Layer<double>* layer_1 = new FCLayer<double>(Size<>{ 4, 2 }, Size<>{2});
	Layer<double>* layer_2 = new FCLayer<double>(Size<>{ 2, 1 });
	Loss<double>* loss = new MSELoss<double>();
	Optimizer<double>* optimizer = new SGDOptimizer<double>(0.1);

	// �������� ������� ��������� ����
	Net<double> net;
	net.set_loss(loss);
	net.set_optimizer(optimizer);
	net.add_layer(layer_1);
	net.add_layer(layer_2);
	return net;
}

void train_net()
{
	// ��������� ������ ������ ��� ��������
	// ��������� ����
	TrainDataSet<double> dataset = get_dataset();

	// ��������� ������� ��������� ����
	Net<double> net = get_net();

	// ���������� ��������� ����
	net.fit(dataset, RequiredErrorCondition<double>(0.1));

	// ���������� ��������� ����
	net.save("weights.txt");
}

void test_net()
{
	// ��������� ������ ������ ��� ��������
	// ��������� ����
	TrainDataSet<double> dataset = get_dataset();

	// ��������� ������� ��������� ����
	Net<double> net = get_net();

	// �������� ������������� ������ �� �����
	net.read("weights.txt");

	// �������� ��������� ����
	DataSet<double> input = dataset.get_input();
	DataSet<double> expected_output = dataset.get_output();
	DataSet<double> output = net.predict(input);

	const DataSetReducer<double>& abs_sum_reducer = ForEachReducer<double>([](const double& left, const double& right) {
		return abs(left) + abs(right);
	});

	double error = (expected_output - output).reduce(abs_sum_reducer);
	std::cout << "Final error: " << error;
}

int main()
{
	train_net();
	test_net();
}