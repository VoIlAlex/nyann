#include "pch.h"
#include "..//nyann/nyann.h"

#ifdef GOAL

namespace {
	TEST(Goal, MNIST)
	{
		// second parameters is batch size
		nyann::DataSetLoader<double> loader(nyann::datasets::MNIST, 20);
		nyann::Net net;

		// create an architecture
		// ...

		double lr = 0.001;
		int epochs = 100;
		while (epochs--)
			for (auto batch : loader.train_subset(0.8))
				net.fit(batch, lr);

		auto test_subset = loader.test_subset(0.2);
		auto input = test_subset.get_input();
		auto expected_output = test_subset.get_output();
		auto output = net.predict(input);

		double difference = nyann::DataSet<double>::abs_difference(output, expected_output);
		// TODO: what next?
	}
} // namespace

#endif