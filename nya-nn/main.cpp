/*
	^ 1  | 0
  1	|____|___
	|    |
	|__0_|_1__>
		 1

*/

#include "nyann.h"

int main()
{
	//// A dataset for the problem
	//// dataset_x -> dataset_y
	//nyann::TrainDataSet<double> dataset = {
	//	{{1.5, 1.5}, {0.}},
	//	{{1.5, 0.5}, {1.}},
	//	{{0.5, 1.5}, {1.}},
	//	{{0.5, 0.5}, {0.}}
	//};

	//// nn layers
	//nyann::Layer<double>* layer_1 = new nyann::FCLayer<double>(nyann::Size{ 2, 5 });
	//layer_1->add_activation_function(new nyann::ReLU<double>());
	//nyann::Layer<double>* layer_2 = new nyann::FCLayer<double>(nyann::Size{ 5, 5 });
	//layer_2->add_activation_function(new nyann::ReLU<double>());
	//nyann::Layer<double>* layer_3 = new nyann::FCLayer<double>(nyann::Size{ 5, 1 });
	//layer_3->add_activation_function(new nyann::ReLU<double>());

	//// creatinga  neural network
	//nyann::Net net;
	//net.add_layer(layer_1);
	//net.add_layer(layer_2);
	//net.add_layer(layer_3);

	////// setting an loss function
	////nyann::Loss* loss = new myann::MSELoss();
	////net.set_loss(loss);


	////// setting an optimizer
	////nyann::Optimizer* opt = new nyann::SGDOptimizer(0.01);
	////net.set_optimizer(opt);

	//// train the network
	//net.fit(
	//	dataset, // dataset
	//	20, // epoch number
	//	2, // batch size
	//	0.03
	//);

	//// Predict a value
	//nyann::DataSet<double> predicted_values = net.predict({
	//	{1.5, 1.5},
	//	{1.5, 0.5},
	//	{0.5, 1.5},
	//	{0.5, 0.5}
	//	});

	//// visualize the results
	//std::cout << predicted_values;


	nyann::TrainDataSet<double> dataset = nyann::generate_linear_dataset<double>(1000, 5, 0.2);
	dataset.shuffle();
	nyann::TrainDataSet<double> dataset_train = { dataset.begin(), dataset.begin() + 800 };
	nyann::TrainDataSet<double> dataset_test = { dataset.begin() + 800, dataset.end() };

	nyann::Net net;

	// TODO: add control under 
	// size of input/output of 
	// nearly located layers
	/*nyann::Layer<double>* layer_1 = new nyann::FCLayer<double>(nyann::Size{ 5, 1000 });
	layer_1->add_activation_function(new nyann::ReLU<double>(0.05));
	nyann::Layer<double>* layer_2 = new nyann::FCLayer<double>(nyann::Size{ 1000, 20 });
	layer_2->add_activation_function(new nyann::ReLU<double>(0.05));
	nyann::Layer<double>* layer_3 = new nyann::FCLayer<double>(nyann::Size{ 20, 1 });
	layer_3->add_activation_function(new nyann::ReLU<double>(0.05));*/

	/*net.add_layer(layer_1);
	net.add_layer(layer_2);
	net.add_layer(layer_3);*/

	// FIXIT: I CANNOT MAKE IT WORK!!!

	nyann::Layer<double>* layer_1 = new nyann::FCLayer<double>(nyann::Size{ 5, 5 });
	nyann::Layer<double>* layer_2 = new nyann::FCLayer<double>(nyann::Size{ 5, 1 });
	net.add_layer(layer_1);
	net.add_layer(layer_2);

	net.fit(dataset_train, 100, 10, 0.001 / 10);

	nyann::DataSet<double> input = dataset_test.get_input();

	nyann::DataSet<double> expected_output = dataset_test.get_output();

	nyann::DataSet<double> output = net.predict(input);

	double error = nyann::DataSet<double>::difference(output, expected_output);

	std::cout << "Error: " << error << std::endl;
	std::cin.get();
}