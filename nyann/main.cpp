/*
	^ 1  | 0
  1	|____|___
	|    |
	|__0_|_1__>
		 1

*/

#include <iostream>
#include "nyann.h"
//#include "nyann/drafts/io_draft.h"
//#include "examples/labs.h"
//#include "nyann/drafts.h"
//#include "nyann/drafts/DataSet_draft.h"

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

	//Lab1();
	//Lab2();
	//Lab3();

	nyann::TrainDataSet_draft<double> dataset {
		{
			nyann::DataSet_draft<double>{0, 0},
			nyann::DataSet_draft<double>{0, 1},
			nyann::DataSet_draft<double>{1, 0},
			nyann::DataSet_draft<double>{1, 1}
		},
		{
			nyann::DataSet_draft<double>{0},
			nyann::DataSet_draft<double>{1},
			nyann::DataSet_draft<double>{1},
			nyann::DataSet_draft<double>{0}
		}
	};

	nyann::Net<double> net;
	nyann::Layer<double> * layer_1 = new nyann::FCLayer<double>(nyann::Size<>{ 2 }, nyann::Size<>{ 1 });
	layer_1->add_activation_function(new nyann::SigmoidActivation<double>());
	net.add_layer(layer_1);

	net.fit(
		dataset,
		1000,
		1,
		0.01
	);

	//std::cout << dataset;
}
