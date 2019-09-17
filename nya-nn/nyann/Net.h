#pragma once

#include <vector>
#include "Layer.h"
#include "Loss.h"
#include "Optimizer.h"


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
			while (epochs--)
			{
				if (batch_size == 1)
				{
					DataRow<_DT> X;
					DataRow<_DT> y;
					DataRow<_DT> y_pred;
					for (DataSet<_DT> row : dataset)
					{
						X = row[0];
						y = row[1];
						y_pred = predict({ X })[0];
						std::vector<_DT> errors = y_pred - y;
						// TODO: derivatives based on activation function
						std::vector<double> derivatives;
						for (auto it = m_layers.rbegin(); it != m_layers.rend(); it++)
						{
							derivatives = std::vector<double>(errors.size(), 1.0);
							errors = (*it)->back_propagation(
								errors,
								derivatives,
								lr
							);
						}
					}
				}
				else
				{
					// TODO
				}
			}
		}

		nyann::DataSet<_DT> predict(const DataSet<_DT>& input)
		{
			if (input.size() == 1)
			{
				nyann::DataRow<_DT> result = input[0];
				for (Layer<_DT>* layer : m_layers)
					result = (*layer)(result);
				return { result };
			}
			// TODO
			else return {};
		}

		~Net()
		{
			for (auto layer : m_layers)
				delete layer;
		}
	};

} // namespace nyann