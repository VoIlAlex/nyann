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
	// A dataset for the problem
	// dataset_x -> dataset_y
	nyann::TrainDataSet<float> dataset = {
		{{1.5, 1.5}, {0}},
		{{1.5, 0.5}, {1}},
		{{0.5, 1.5}, {}},
		{{0.5, 0.5}, {}}
	};

	// nn layers
	nyann::Layer* layer_1 = new nyann::FCLayer(nyann::Size(2), nyann::Size(2));
	nyann::Layer* layer_2 = new nyann::FCLayer(nyann::Size(2), nyann::Size(1));


	// creatinga  neural network
	nyann::Net net;
	net.add_layer(layer_1);
	net.add_layer(layer_2);

	// setting an loss function
	nyann::Loss* loss = new myann::MSELoss();
	net.set_loss(loss);


	// setting an optimizer
	nyann::Optimizer* opt = new nyann::SGDOptimizer(0.01);
	net.set_optimizer(opt);

	// train the network
	net.fit(
		dataset, // dataset
		10, // epoch number
		4 // batch size
	);

	// Predict a value
	nyann::DataSet<float> predicted_values = net.predict({ {0.1, 1.1} });

	// visualize the results
	std::cout << predicted_values;
}