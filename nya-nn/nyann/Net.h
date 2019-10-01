#pragma once

#include <vector>
#include "Layer.h"
#include "Loss.h"
#include "Optimizer.h"
#include "ActivationFunction.h"


namespace nyann {

	template<typename _DT = double>
	class Net
	{
		std::vector<Layer<_DT>*> m_layers;
		Loss* m_loss;
		Optimizer* m_optimizer;

	public:
		Net() :
			m_loss(nullptr),
			m_optimizer(nullptr)
		{}

		void add_layer(Layer<_DT>* layer)
		{
			m_layers.push_back(layer);
		}

		void set_loss(Loss* loss)
		{
			m_loss = loss;
		}

		void set_optimizer(Optimizer* optimizer)
		{
			m_optimizer = optimizer;
		}

		void fit(const TrainDataSet<_DT>& dataset, int epochs, int batch_size = 1, double lr = 0.001)
		{
			DataSet<_DT> input = dataset.get_input();
			DataSet<_DT> output = dataset.get_output();
			while (epochs--)
			{
				double difference = DataSet<double>::abs_difference(output, predict(input));

				std::cout << "[INFO] Epoch " << epochs + 1 << "..." << std::endl;
				std::cout << "[INFO] Error: " << difference << std::endl;
				for (int i = 0; i < dataset.size() / batch_size; i++)
				{
					DataSet<_DT> X;
					DataSet<_DT> y;
					DataSet<_DT> y_pred;
					DataSet<_DT> errors;

					for (int j = i * batch_size; j < i * batch_size + batch_size; j++)
					{
						X.push_back(dataset[j][0]);
						y.push_back(dataset[j][1]);
					}

					y_pred = predict(X);
					errors = y_pred - y;

					for (auto it = m_layers.rbegin(); it != m_layers.rend(); it++)
					{
						errors = (*it)->back_propagation(
							errors,
							lr
						);
					}
				}
			}
		}

		nyann::DataSet<_DT> predict(const DataSet<_DT>& input)
		{
			nyann::DataSet<_DT> result = input;
			for (Layer<_DT>* layer : m_layers)
				result = (*layer)(result);
			return result;
		}

		void add_activation_function(ActivationFunction<_DT>* activation_function, int idx = -1)
		{
			if (idx == -1)
				m_layers.back()->add_activation_function(activation_function);
			else
				m_layers[idx]->add_activation_function(activation_function);
		}

		~Net()
		{
			for (auto layer : m_layers)
				delete layer;
		}
	};

} // namespace nyann