#pragma once

#include <vector>


// For all the framework configurations
#include "_config.h"

#include "Layer.h"
#include "Loss.h"
#include "Optimizer.h"
#include "ActivationFunction.h"


namespace nyann {

#ifndef DRAFT_DATASET_2_0_0_ALPHA_TEST
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

		std::vector<_DT> fit(const TrainDataSet<_DT>& dataset, int epochs, int batch_size = 1, double lr = 0.001, double required_error = 0)
		{
			DataSet<_DT> input = dataset.get_input();
			DataSet<_DT> output = dataset.get_output();
			std::vector<_DT> error_dynamic;
			// TODO: here is a lot of duplicate code. Optimize it.
			if (epochs != -1)
				for (int ep = 0; ep < epochs; ep++)
				{
					_DT difference = DataSet<_DT>::abs_difference(output, predict(input)) / input.size();
					error_dynamic.push_back(difference);
					std::cout << "[INFO] Epoch " << ep + 1 << "..." << std::endl;
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
								lr);
						}
					}
				}
			else // number of epochs here is required error
			{
				_DT difference;
				do
				{
					epochs++;
					difference = DataSet<_DT>::abs_difference(output, predict(input)) / input.size();
					error_dynamic.push_back(difference);
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
								lr);
						}
					}
				} while (difference > required_error); // number of epochs here is required error
			}
			return error_dynamic;
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
#else 

#include "drafts.h"
#include "drafts/DataSet_draft.h"
#include "drafts/TrainDataSet_draft.h"

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
			this->m_layers.push_back(layer);
		}

		void set_loss(Loss* loss)
		{
			this->m_loss = loss;
		}

		void set_optimizer(Optimizer* optimizer)
		{
			this->m_optimizer = optimizer;
		}

		std::vector<_DT> fit(
			const ::nyann::TrainDataSet_draft<_DT>& dataset, 
			int epochs, 
			int batch_size = 1, 
			double lr = 0.001, 
			double required_error = 0
		)
		{
			DataSet_draft<_DT> input = dataset.get_input();
			DataSet_draft<_DT> output = dataset.get_output();
			std::vector<_DT> error_dynamic;
			// TODO: here is a lot of duplicate code. Optimize it.
			if (epochs != -1)
				for (int ep = 0; ep < epochs; ep++)
				{
					_DT difference = DataSet_draft<_DT>::abs_difference(output, predict(input)) / input.size();
					error_dynamic.push_back(difference);
					std::cout << "[INFO] Epoch " << ep + 1 << "..." << std::endl;
					std::cout << "[INFO] Error: " << difference << std::endl;
					for (int i = 0; i < dataset.size() / batch_size; i++)
					{
						DataSet_draft<_DT> X;
						DataSet_draft<_DT> y;
						DataSet_draft<_DT> y_pred;
						DataSet_draft<_DT> errors;

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
								lr);
						}
					}
				}
			else // number of epochs here is required error
			{
				_DT difference;
				do
				{
					epochs++;
					difference = DataSet_draft<_DT>::abs_difference(output, predict(input)) / input.size();
					error_dynamic.push_back(difference);
					std::cout << "[INFO] Epoch " << epochs + 1 << "..." << std::endl;
					std::cout << "[INFO] Error: " << difference << std::endl;
					for (int i = 0; i < dataset.size() / batch_size; i++)
					{
						DataSet_draft<_DT> X;
						DataSet_draft<_DT> y;
						DataSet_draft<_DT> y_pred;
						DataSet_draft<_DT> errors;

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
								lr);
						}
					}
				} while (difference > required_error); // number of epochs here is required error
			}
			return error_dynamic;
		}

		/*nyann::DataSet_draft<_DT> predict(const DataSet_draft<_DT>& input)
		{
			nyann::DataSet_draft<_DT> result = input;
			for (Layer<_DT>* layer : m_layers)
				result = (*layer)(result);
			return result;
		}*/

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
#endif 

} // namespace nyann