/*
	^ 1  | 0
  1	|____|___
	|    |
	|__0_|_1__>
		 1

*/

#include "nyann.h"
#include "labs/labs.h"

int main()
{
	/*nyann::TrainDataSet<double> dataset = nyann::generate_linear_dataset<double>(1000, 5, 0.2);
	dataset.shuffle();
	nyann::TrainDataSet<double> dataset_train = { dataset.begin(), dataset.begin() + 800 };
	nyann::TrainDataSet<double> dataset_test = { dataset.begin() + 800, dataset.end() };

	nyann::Net net;

	nyann::Layer<double>* layer_1 = new nyann::FCLayer<double>(nyann::Size{ 5, 5 });
	nyann::Layer<double>* layer_2 = new nyann::FCLayer<double>(nyann::Size{ 5, 1 });
	net.add_layer(layer_1);
	net.add_layer(layer_2);

	net.fit(dataset_train, 100, 10, 0.001 / 10);

	nyann::DataSet<double> input = dataset_test.get_input();

	nyann::DataSet<double> expected_output = dataset_test.get_output();

	nyann::DataSet<double> output = net.predict(input);

	double error = nyann::DataSet<double>::abs_difference(output, expected_output);

	std::cout << "Error: " << error << std::endl;
	std::cin.get();*/

	Lab1();
	Lab2();
}
