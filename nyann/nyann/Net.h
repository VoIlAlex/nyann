#pragma once


// For all the framework configurations
#include "_config.h"

#include "Layer.h"
#include "Loss.h"
#include "Optimizer.h"
#include "ActivationFunction.h"
#include "DataSet.h"
#include "DataSet/TrainDataSet.h"
#include "utils/dataset_reducers.h"

#include <vector>
#include <sstream>
#include <string>


namespace nyann {

	template<typename _DT>
	struct TrainState
	{
		size_t epoch;
		_DT error;
	};

	template<typename _DT>
	class TrainStopCondition
	{
	public:
		TrainStopCondition()
		{}

		virtual bool is_true(const TrainState<_DT>& state) const = 0;

		virtual void act_before(TrainState<_DT>& state) const
		{}

		virtual void act_after(TrainState<_DT>& state) const
		{
			state.epoch++;
		}
	};

	template<typename _DT>
	class EpochsCondition : public TrainStopCondition<_DT>
	{
		int m_epochs;

	public:
		EpochsCondition(int epochs)
			: m_epochs(epochs)
		{}

		bool is_true(const TrainState<_DT>& state) const override
		{
			return state.epoch >= m_epochs;
		}
	};

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
			const ::nyann::TrainDataSet<_DT>& dataset,
			int epochs,
			size_t batch_size = 1,
			double lr = 0.001,
			double required_error = 0
		)
		{
			std::vector<_DT> error_dynamic;
			DataSet<_DT> input = dataset.get_input();
			DataSet<_DT> output = dataset.get_output();
			// TODO: here is a lot of duplicate code. Optimize it.
			if (epochs != -1)
				for (int ep = 0; ep < epochs; ep++)
				{
					_DT difference = DataSet<_DT>::abs_difference(output, predict(input)) / input.size();
					error_dynamic.push_back(difference);
					std::cout << "[INFO] Epoch " << ep + 1 << "..." << std::endl;
					std::cout << "[INFO] Error: " << difference << std::endl;
					for (int i = 0; i < dataset.samples_count() / batch_size; i++)
					{
						DataSet<_DT> X(Size<>::join({ batch_size }, dataset.input_size()));
						DataSet<_DT> y(Size<>::join({ batch_size }, dataset.output_size()));
						DataSet<_DT> errors;
						DataSet<_DT> y_pred;
						for (int j = i * batch_size; j < i * batch_size + batch_size; j++)
						{
							X[j] = dataset[j].get_input();
							y[j] = dataset[j].get_output();
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
					for (int i = 0; i < dataset.samples_count() / batch_size; i++)
					{
						DataSet<_DT> X(Size<>::join({ batch_size }, dataset.input_size()));
						DataSet<_DT> y(Size<>::join({ batch_size }, dataset.output_size()));
						DataSet<_DT> errors;
						DataSet<_DT> y_pred;

						for (int j = i * batch_size; j < i * batch_size + batch_size; j++)
						{
							X[j] = (dataset[j].get_input());
							y[j] = (dataset[j].get_output());
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

		DataSet<_DT> predict(const DataSet<_DT>& input)
		{
			DataSet<_DT> result = input;
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