#include "pch.h"
#include "..//nyann//nyann.h"

namespace {

#ifdef DRAFT_DATASET_2_0_0_ALPHA_TEST
#elif defined(DRAFT_DATASET_2_0_0_PRERELEASE)
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
		nyann::Net net;
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
#else
	TEST(Net, Construction)
	{
		nyann::Net net;
	}


	TEST(Net, LayersSetting)
	{
		nyann::Layer<double>* layer_1 = new nyann::FCLayer<double>(nyann::Size<>(2, 2));
		nyann::Layer<double>* layer_2 = new nyann::FCLayer<double>(nyann::Size<>(2, 1));
		nyann::Net net;
		net.add_layer(layer_1);
		net.add_layer(layer_2);
	}


	TEST(Net, Fitting)
	{
		nyann::Layer<double>* layer_1 = new nyann::FCLayer<double>(nyann::Size<>{ 2, 2 });
		nyann::Layer<double>* layer_2 = new nyann::FCLayer<double>(nyann::Size<>{ 2, 1 });
		nyann::Net net;
		net.add_layer(layer_1);
		net.add_layer(layer_2);

		nyann::TrainDataSet<double> dataset = {
			{{1.5, 1.5}, {0.}},
			{{1.5, 0.5}, {1.}},
			{{0.5, 1.5}, {1.}},
			{{0.5, 0.5}, {0.}}
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
			{{1.5, 1.5}, {0.}},
			{{1.5, 0.5}, {1.}},
			{{0.5, 1.5}, {1.}},
			{{0.5, 0.5}, {0.}}
		};

		std::vector<double> errors = net.fit(dataset, 10);
		ASSERT_EQ(errors.size(), 10);
	}
#endif
} // namespace