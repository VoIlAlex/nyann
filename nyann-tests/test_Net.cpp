#include "pch.h"
#include "..//nyann//nyann.h"

namespace {
	TEST(Net, Construction)
	{
		nyann::Net net;
	}


	TEST(Net, LayersSetting)
	{
		nyann::Layer<double>* layer_1 = new nyann::FCLayer<double>(nyann::Size<>{2, 2});
		nyann::Layer<double>* layer_2 = new nyann::FCLayer<double>(nyann::Size<>{2, 1});
		nyann::Net net;
		net.add_layer(layer_1);
		net.add_layer(layer_2);
	}

	TEST(Net, Fitting)
	{
		nyann::Layer<double>* layer_1 = new nyann::FCLayer<double>(nyann::Size<>{ 2, 2 });
		nyann::Layer<double>* layer_2 = new nyann::FCLayer<double>(nyann::Size<>{ 2, 1 });
		nyann::Loss<double>* loss = new nyann::MSELoss<double>();
		nyann::Optimizer<double>* optimizer = new nyann::SGDOptimizer<double>(0.01);
		nyann::Net net;
		net.set_loss(loss);
		net.set_optimizer(optimizer);
		net.add_layer(layer_1);
		net.add_layer(layer_2);

		nyann::TrainDataSet<double> dataset = {
			{ {1.5, 1.5},
			{1.5, 0.5},
			{0.5, 1.5},
			{0.5, 0.5} },
			{
				nyann::DataSet<double>{0.},
				nyann::DataSet<double>{1.},
				nyann::DataSet<double>{1.},
				nyann::DataSet<double>{0.}
			}
		};

		net.fit(dataset, 10);
	}

	TEST(Net, OutputForPlot)
	{
		nyann::Layer<double>* layer_1 = new nyann::FCLayer<double>(nyann::Size<>{ 2, 2 });
		nyann::Layer<double>* layer_2 = new nyann::FCLayer<double>(nyann::Size<>{ 2, 1 });
		nyann::Net net;
		net.add_layer(layer_1);
		net.add_layer(layer_2);

		nyann::TrainDataSet<double> dataset = {
			{{1.5, 1.5},
			{1.5, 0.5},
			{0.5, 1.5},
			{0.5, 0.5}},
			{
				nyann::DataSet<double>{0.},
				nyann::DataSet<double>{1.},
				nyann::DataSet<double>{1.},
				nyann::DataSet<double>{0.}
			}
		};

		std::vector<double> errors = net.fit(dataset, 10);
		ASSERT_EQ(errors.size(), 10);
	}

	TEST(Net, RequiredErrorCondition)
	{
		nyann::Layer<double>* layer_1 = new nyann::FCLayer<double>(nyann::Size<>{ 2, 4 });
		nyann::Layer<double>* layer_2 = new nyann::FCLayer<double>(nyann::Size<>{ 4, 1 });
		layer_2->add_activation_function(new nyann::BinaryActivation<double>());
		nyann::Loss<double>* loss = new nyann::MSELoss<double>();
		nyann::Optimizer<double>* optimizer = new nyann::SGDOptimizer<double>(0.1);
		nyann::Net net;
		net.set_loss(loss);
		net.set_optimizer(optimizer);
		net.add_layer(layer_1);
		net.add_layer(layer_2);

		nyann::TrainDataSet<double> dataset = {
			{ {1.5, 1.5},
			{1.5, 0.5},
			{0.5, 1.5},
			{0.5, 0.5} },
			{
				nyann::DataSet<double>{0.},
				nyann::DataSet<double>{1.},
				nyann::DataSet<double>{1.},
				nyann::DataSet<double>{1.}
			}
		};

		net.fit(dataset, nyann::RequiredErrorCondition<double>(0));
		nyann::DataSet<double> input = dataset.get_input();
		nyann::DataSet<double> expected_output = dataset.get_output();
		nyann::DataSet<double> output = net.predict(input);

		const nyann::DataSetReducer<double>& abs_sum_reducer = nyann::ForEachReducer<double>([](const double& left, const double& right) {
			return abs(left) + abs(right);
		});

		double error = (expected_output - output).reduce(abs_sum_reducer);

		ASSERT_LE(error, 0.5);
	}

} // namespace