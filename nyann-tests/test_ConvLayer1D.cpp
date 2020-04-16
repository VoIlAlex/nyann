#include "pch.h"
#include "..//nyann//nyann.h"
#include "../nyann/nyann/drafts.h"

namespace {
	TEST(ConvLayer1D, Construction)
	{
		nyann::ConvLayer1D<double> layer(
			1,		// filters in
			3,		// filters out
			2,		// kernel size
			1,		// stride
			0		// padding
		);
	}
#ifdef DRAFT_DATASET_2_0_0_ALPHA_TEST
	TEST(ConvLayer1D, BatchProcessing)
	{
		nyann::ConvLayer1D<double> layer(
			1,		// filters in
			3,		// filters out
			2,		// kernel size
			1,		// stride
			0		// padding
		);
		nyann::DataSet_draft<double> X = {
			{1.0, 2.0, 3.0},
			{4.0, 5.0, 6.0}
		};
		nyann::DataSet_draft<double> y = layer(X);
		ASSERT_NE(y, nyann::DataSet_draft<double>());
	}

	TEST(ConvLayer1D, BatchProcessingResultShape)
	{
		nyann::ConvLayer1D<double> layer(
			1,		// filters in
			3,		// filters out
			2,		// kernel size
			1,		// stride
			0		// padding
		);

		// Input shape: [2, 3, 1] (B, W, C)
		nyann::DataSet_draft<double> X = {
			{{1.0}, {2.0}, {3.0}},
			{{4.0}, {5.0}, {6.0}}
		};
		nyann::DataSet_draft<double> y = layer(X);

		nyann::Size<> output_shape;
		output_shape.push_back(2); // batch size
		output_shape.push_back(2); // width
		output_shape.push_back(3); // filters

		ASSERT_EQ(y.size(), output_shape);
	}
#elif defined(DRAFT_DATASET_2_0_0_PRERELEASE)
	TEST(ConvLayer1D, BatchProcessing)
	{
		nyann::ConvLayer1D<double> layer(
			1,		// filters in
			3,		// filters out
			2,		// kernel size
			1,		// stride
			0		// padding
		);
		nyann::DataSet<double> X = {
			{1.0, 2.0, 3.0},
			{4.0, 5.0, 6.0}
		};
		nyann::DataSet<double> y = layer(X);
		ASSERT_NE(y, nyann::DataSet<double>());
	}

	TEST(ConvLayer1D, BatchProcessingResultShape)
	{
		nyann::ConvLayer1D<double> layer(
			1,		// filters in
			3,		// filters out
			2,		// kernel size
			1,		// stride
			0		// padding
		);
		nyann::DataSet<double> X = {
			{{1.0}, {2.0}, {3.0}},
			{{4.0}, {5.0}, {6.0}}
		};
		nyann::DataSet<double> y = layer(X);

		nyann::Size output_shape;
		output_shape.push_back(2); // batch size
		output_shape.push_back(2); // width
		output_shape.push_back(3); // filters

		ASSERT_EQ(y.shape(), output_shape);
	}
#else
	TEST(ConvLayer1D, Forward)
	{
		nyann::ConvLayer1D<double> layer(
			2,		// filters in
			3,		// filters out
			2,		// kernel size
			1,		// stride
			0		// padding
		);

		nyann::ConvLayer1D<double>::input_t input = {
			{
				{1.0, 1.0, 1.0},
				{1.0, 1.0, 1.0}
			},
			{
				{1.0, 1.0, 1.0},
				{1.0, 1.0, 1.0}
			}
		};

		nyann::ConvLayer1D<double>::output_t output = layer(input);
	}

	TEST(ConvLayer1D, OutputShape)
	{
		nyann::ConvLayer1D<double> layer(
			2,		// filters in
			3,		// filters out
			2,		// kernel size
			1,		// stride
			0		// padding
		);

		nyann::ConvLayer1D<double>::input_t input = {
			{
				{1.0, 1.0, 1.0},
				{1.0, 1.0, 1.0}
			},
			{
				{1.0, 1.0, 1.0},
				{1.0, 1.0, 1.0}
			}
		};

		nyann::ConvLayer1D<double>::output_t output = layer(input);
		ASSERT_EQ(output.size(), input.size());
		ASSERT_EQ(output.at(0).size(), 3);
		ASSERT_EQ(output.at(0).at(0).size(), 2);
	}
#endif
} // namespace 