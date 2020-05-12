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
} // namespace