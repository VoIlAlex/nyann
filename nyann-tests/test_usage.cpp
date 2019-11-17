#include "pch.h"
#include "..//nyann//nyann.h"

namespace {
	TEST(Net, Prediction_1)
	{
		// Create a model

		nyann::Layer<double>* layer_1 = new nyann::FCLayer<double>(nyann::Size{ 2, 2 });
		layer_1->add_activation_function(new nyann::ReLU<double>());
		nyann::Layer<double>* layer_2 = new nyann::FCLayer<double>(nyann::Size{ 2, 1 });
		layer_2->add_activation_function(new nyann::ReLU<double>());

		nyann::Net net;

		net.add_layer(layer_1);
		net.add_layer(layer_2);

		// Train the model

		nyann::TrainDataSet<double> dataset = {
			{{1.5, 1.5}, {1.}},
			{{1.5, 0.5}, {0.}},
			{{0.5, 1.5}, {0.}},
			{{0.5, 0.5}, {0.}}
		};

		net.fit(dataset, 100, 2, 0.03);


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


	TEST(Net, PredictionWithActivation)
	{
		nyann::TrainDataSet<double> dataset = {
			{{1.5, 1.5}, {0.}},
			{{1.5, 0.5}, {1.}},
			{{0.5, 1.5}, {1.}},
			{{0.5, 0.5}, {0.}}
		};

		nyann::Net net;

		nyann::Layer<double>* layer_1 = new nyann::FCLayer<double>(nyann::Size{ 2, 20 });
		layer_1->add_activation_function(new nyann::ReLU<double>());
		nyann::Layer<double>* layer_2 = new nyann::FCLayer<double>(nyann::Size{ 20, 20 });
		layer_2->add_activation_function(new nyann::ReLU<double>());
		nyann::Layer<double>* layer_3 = new nyann::FCLayer<double>(nyann::Size{ 20, 1 });
		layer_3->add_activation_function(new nyann::ReLU<double>());

		net.add_layer(layer_1);
		net.add_layer(layer_2);
		net.add_layer(layer_3);

		net.fit(dataset, 1000, 1, 0.1);

		double precision = 0.5;
		nyann::TrainDataSet<double> test_dataset = {
			{{1.5, 1.5}, {0.}},
			{{1.5, 0.5}, {1.}},
			{{0.5, 1.5}, {1.}},
			{{0.5, 0.5}, {0.}}
		};

		nyann::DataSet<double> input;
		for (auto& row : test_dataset)
			input.push_back(row[0]);

		nyann::DataSet<double> expected_output;
		for (auto& row : test_dataset)
			expected_output.push_back(row[1]);

		nyann::DataSet<double> output = net.predict(input);

		double diff = nyann::DataSet<double>::abs_difference(output, expected_output);

		EXPECT_LT(diff, 1.0 * output.size());
	}
} // namespace