#include "..//nyann.h"
#include <functional>
#include <iostream>

std::pair<nyann::TrainDataSet<double>, nyann::TrainDataSet<double>> train_test_split(
	nyann::TrainDataSet<double> dataset,
	double test_size = 0.2);

class Lab1
{
public:
	Lab1()
	{
		nyann::Net net;
		nyann::Layer<double>* l_1 = new nyann::FCLayer<double>(nyann::Size{ 2, 1 });
		l_1->add_activation_function(new nyann::BinaryActivation<double>());

		net.add_layer(l_1);

		nyann::TrainDataSet<double> dataset = {
			{{1, 1}, {1}},
			{{-1, 1}, {1}},
			{{-1, -1}, {0}},
			{{1, -1}, {1}} };

		net.fit(dataset,
			-1,		// train until error become 0
			1,		// batch size
			0.3		// learning rate
		);

		nyann::DataSet<double> expected_output = dataset.get_output();
		nyann::DataSet<double> input = dataset.get_input();

		nyann::DataSet<double> output = net.predict(input);

		std::cout << "Final absolute error: "
			<< nyann::DataSet<double>::abs_difference(expected_output, output)
			<< std::endl;
		std::cout << net.str() << std::endl;
		std::cin.get();
	}
};

class Lab2
{
	nyann::TrainDataSet<double> generate_dataset(
		const std::function<double(double)>& func, int size, int input_size, double step = 0.1)
	{
		nyann::TrainDataSet<double> dataset;
		for (int i = 0; i < size; i++)
		{
			nyann::DataRow<double> X;
			nyann::DataRow<double> y;
			for (double x = i * step; x < (i + input_size) * step; x += step)
				X.push_back(x);

			y = { func((i + input_size) * step) };
			dataset.push_back({ X, y });
		}
		return dataset;
	}

public:
	Lab2()
	{
		nyann::TrainDataSet<double> dataset = generate_dataset(
			[](double x) {
				return 0.3 * cos(0.1 * x) + 0.06 * sin(0.1 * x);
			},
			100, 6);

		dataset.shuffle();
		auto [dataset_train, dataset_test] = train_test_split(dataset);

		nyann::Net net;

		nyann::Layer<double>* l_1 = new nyann::FCLayer<double>(nyann::Size{ 5, 2 });
		net.add_layer(l_1);
		nyann::Layer<double>* l_2 = new nyann::FCLayer<double>(nyann::Size{ 2, 1 });
		net.add_layer(l_2);

		net.fit(dataset_train, -1, 1, 0.01, 0.2);

		nyann::DataSet<double> input = dataset_test.get_input();
		nyann::DataSet<double> expected_output = dataset_test.get_output();
		nyann::DataSet<double> output = net.predict(input);

		std::cout << "Final absolute error: "
			<< nyann::DataSet<double>::abs_difference(expected_output, output)
			<< std::endl;
		std::cout << net.str() << std::endl;
		std::cin.get();
	}
};

//class Lab3
//{
//public:
//	Lab3()
//	{
//		// I will classify handwritten digits (0, 1, 2, 3, 4, 5, 6, 7, 8, 9)
//
//		// Getting a dataset
//		nyann::TrainDataSet<double> dataset = get_dataset();
//		auto [dataset_train, dataset_test] = train_test_split(dataset);
//
//		// Building an architecture
//
//		// TODO: correct architecture
//		int input_size = dataset_train.get_size()[0];
//		nyann::Layer<double>* l_1 = new nyann::FCLayer<double>(nyann::Size{ 28 * 28, 1000 });
//		l_1->add_activation_function(new nyann::ReLU<double>());
//		nyann::Layer<double>* l_2 = new nyann::FCLayer<double>(nyann::Size{ 1000, 1000 });
//		l_2->add_activation_function(new nyann::ReLU<double>());
//		nyann::Layer<double>* l_3 = new nyann::FCLayer<double>(nyann::Size{ 1000, 1000 });
//		l_3->add_activation_function(new nyann::ReLU<double>());
//		nyann::Layer<double>* l_4 = new nyann::FCLayer<double>(nyann::Size{ 1000, 10 });
//		l_4->add_activation_function(new nyann::Softmax<double>());
//
//		nyann::Net net;
//		net.add_layer(l_1);
//		net.add_layer(l_2);
//		net.add_layer(l_3);
//		net.add_layer(l_4);
//
//
//		// Train the network
//		net.fit(dataset_train, 50, 5, 0.001);
//
//
//		// Predict the output
//		nyann::DataSet<double> input = dataset_test.get_input();
//		nyann::DataSet<double> expected_output = dataset_test.get_output();
//		nyann::DataSet<double> output = net.predict(input);
//
//		std::cout << "Final absolute error: "
//			<< nyann::DataSet<double>::abs_difference(expeced_output, output)
//			<< std::endl;
//
//		std::cin.get();
//	}
//private:
//	nyann::TrainDataSet<double> get_dataset()
//	{
//		// TODO: get dataset from MNIST
//		return {};
//	}
//};

std::pair<nyann::TrainDataSet<double>, nyann::TrainDataSet<double>> train_test_split(nyann::TrainDataSet<double> dataset, double test_size)
{
	auto train_end = dataset.end() - int(dataset.size() * test_size);
	dataset.shuffle();
	nyann::TrainDataSet<double> dataset_test = {
		dataset.begin(),
		train_end };
	nyann::TrainDataSet<double> dataset_train = {
		train_end,
		dataset.end() };
	return { dataset_train, dataset_test };
}