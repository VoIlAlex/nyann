#include "pch.h"
#include "../nyann/nyann.h"

namespace {

	TEST(ActivationFunction, BinaryActivation_execute) 
	{
		nyann::BinaryActivation<double> activation;
		ASSERT_EQ(activation(2.0), 1.0);
		ASSERT_EQ(activation(0.5), 1.0);
		ASSERT_EQ(activation(-0.5), 0.0);
		ASSERT_EQ(activation(-2.0), 0.0);
	}
	
	TEST(ActivationFunction, BinaryActivation_derivative) 
	{
		nyann::BinaryActivation<double> activation;
		ASSERT_EQ(activation.derivative(1.0), 1.0);
		ASSERT_EQ(activation.derivative(0.5), 1.0);
		ASSERT_EQ(activation.derivative(-0.5), 1.0);
		ASSERT_EQ(activation.derivative(-2.0), 1.0);
	}

	TEST(ActivationFunction, BipolarActivation_execute)
	{
		nyann::BipolarActivation<double> activation;
		ASSERT_EQ(activation(2.0), 1.0);
		ASSERT_EQ(activation(0.5), 1.0);
		ASSERT_EQ(activation(-0.5), -1.0);
		ASSERT_EQ(activation(-2.0), -1.0);
	}

	TEST(ActivationFunction, BipolarActivation_derivative)
	{
		nyann::BipolarActivation<double> activation;
		ASSERT_EQ(activation.derivative(1.0), 1.0);
		ASSERT_EQ(activation.derivative(0.5), 1.0);
		ASSERT_EQ(activation.derivative(-0.5), 1.0);
		ASSERT_EQ(activation.derivative(-2.0), 1.0);
	}

	TEST(ActivationFunction, LinearActivation_execute)
	{
		nyann::LinearActivation<double> activation;
		ASSERT_EQ(activation(2.0), 2.0);
		ASSERT_EQ(activation(0.5), 0.5);
		ASSERT_EQ(activation(-0.5), -0.5);
		ASSERT_EQ(activation(-2.0), -2.0);
	}

	TEST(ActivationFunction, LinearActivation_derivative)
	{
		nyann::LinearActivation<double> activation;
		ASSERT_EQ(activation.derivative(1.0), 1.0);
		ASSERT_EQ(activation.derivative(0.5), 1.0);
		ASSERT_EQ(activation.derivative(-0.5), 1.0);
		ASSERT_EQ(activation.derivative(-2.0), 1.0);
	}

	TEST(ActivationFunction, ReLUActivation_execute)
	{
		nyann::ReLUActivation<double> activation;
		ASSERT_EQ(activation(2.0), 2.0);
		ASSERT_EQ(activation(0.5), 0.5);
		ASSERT_EQ(activation(-0.5), 0.0);
		ASSERT_EQ(activation(-2.0), 0.0);
	}
	

	TEST(ActivationFunction, ReLUActivation_derivative)
	{
		nyann::ReLUActivation<double> activation(0.2);
		ASSERT_EQ(activation.derivative(1.0), 1.0);
		ASSERT_EQ(activation.derivative(0.5), 1.0);
		ASSERT_EQ(activation.derivative(-0.5), 0.2);
		ASSERT_EQ(activation.derivative(-2.0), 0.2);
	}

	TEST(ActivationFunction, SigmoidActivation_execute)
	{
		nyann::SigmoidActivation<double> activation;
		ASSERT_NEAR(activation(2.0), 0.88, 0.1);
		ASSERT_NEAR(activation(0.5), 0.622, 0.1);
		ASSERT_NEAR(activation(-0.5), 0.377, 0.1);
		ASSERT_NEAR(activation(-2.0), 0.119, 0.1);
	}

	TEST(ActivationFunction, SigmoidActivation_derivative)
	{
		nyann::SigmoidActivation<double> activation;
		ASSERT_NEAR(activation.derivative(1.0), 0.0, 0.1);
		ASSERT_NEAR(activation.derivative(0.7), 0.21, 0.1);
		ASSERT_NEAR(activation.derivative(0.3), 0.21, 0.1);
		ASSERT_NEAR(activation.derivative(0.0), 0.0, 0.1);
	}

	TEST(ActivationFunction, SoftMaxActivation_execute)
	{
		nyann::SoftMaxActivation<double> activation;
		nyann::DataSet<double> input{
			1.0, 5.0, 10.0, 3.0, 2.0
		};
		nyann::DataSet<double> expected_output {
			0.0001224, 0.00668375, 0.99195652, 0.0009045, 0.0003327
		};
		nyann::DataSet<double> output = activation(input);
		double diff = nyann::DataSet<double>::abs_difference(output, expected_output);
		ASSERT_LT(diff, 0.1);
	}

	TEST(ActivationFunction, SoftMaxActivation_derivative)
	{
		nyann::SoftMaxActivation<double> activation;
		ASSERT_NEAR(activation.derivative(1.0), 0.0, 0.1);
		ASSERT_NEAR(activation.derivative(0.7), 0.21, 0.1);
		ASSERT_NEAR(activation.derivative(0.3), 0.21, 0.1);
		ASSERT_NEAR(activation.derivative(0.0), 0.0, 0.1);
	}

} // namespace 