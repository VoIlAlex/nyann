

// For all the framework configurations
#include "../_config.h"

#include "../Layer.h"
#include "../dataset.h"

#include <functional>
#include <random>


namespace nyann {

#ifdef DRAFT_DATASET_2_0_0_ALPHA_TEST
	template<typename _DT>
	class ConvLayer1D : public Layer<_DT>
	{
	public:
		typedef _DT weight_t;
		typedef	_DT bias_t;
		typedef std::vector<std::vector<_DT>> weights_container_t;
		typedef std::vector<std::vector<_DT>> biases_container_t;
		typedef std::vector<std::vector<std::vector<_DT>>> input_t; // [feature map, feature]
		typedef std::vector<std::vector<std::vector<_DT>>> output_t; // [feature map, feature]
	private:
		int m_filters_in;
		int m_filters_out;
		int m_kernel_size;
		int m_stride;
		int m_padding;
		weights_container_t m_weights;
		biases_container_t m_biases;
	public:
		ConvLayer1D(int filters_in, int filters_out, int kernel_size, int stride = 1, int padding = 0)
			:
			m_filters_in(filters_in),
			m_filters_out(filters_out),
			m_kernel_size(kernel_size),
			m_stride(stride),
			m_padding(padding),
			m_weights(filters_out),
			m_biases(filters_out)
		{
			for (int i = 0; i < filters_out; i++)
			{
				m_weights[i].resize(kernel_size);
				m_biases[i].resize(1);
			}
			this->fill_weights_random();
		}


		// It will receive squere matrices as input and generate 
		output_t operator()(const input_t& input)
		{
			int batch_size = input.size();
			int input_size = input.at(0).at(0).size();
			int output_size = (m_padding * 2 + input_size - m_kernel_size) / m_stride + 1;

			// Add padding
			output_t input_with_padding = input;
			for (int i = 0; i < m_padding; i++)
			{
				for (int j = 0; j < batch_size; j++)
				{
					for (int k = 0; k < input_size; k++)
					{
						input_with_padding[j][k].insert(input_with_padding[j][k].begin(), input_with_padding[j][k].front());
						input_with_padding[j][k].insert(input_with_padding[j][k].end(), input_with_padding[j][k].back());

					}
				}
			}

			output_t output;

			// Initialize
			output.resize(batch_size);
			for (int i = 0; i < output.size(); i++)
			{
				output[i].resize(m_filters_out);
				for (int j = 0; j < m_filters_out; j++)
					output[i][j].resize(output_size);
			}

			// Process
			for (int feature_map = 0; feature_map < m_filters_out; feature_map++)
			{
				for (int item = 0; item < batch_size; item++)
				{
					for (int j = 0; j < output_size; j++)
					{
						for (int i = 0; i < m_kernel_size; i++)
						{
							for (int in_feature_map = 0; in_feature_map < m_filters_in; in_feature_map++)
								output[item][feature_map][j]
								+= input_with_padding[item][in_feature_map][j * m_stride + i]
								* m_weights[feature_map][i];
						}
						output[item][feature_map][j] -= m_biases[feature_map][0];
					}
				}
			}

			return output;
		}
		virtual DataSet_draft<_DT> back_propagation(
			const DataSet_draft<_DT>& errors,
			double lr = 0.001
		)override
		{
			// TODO
			return {};
		}

		virtual DataSet_draft<_DT> operator() (const DataSet_draft<_DT>&) override
		{
			return {};
		}

		std::string str() const
		{
			// TODO: implement
			return "";
		}
	private:
		void fill_weights_random()
		{
			std::default_random_engine random_engine;
			std::normal_distribution distribution(0., sqrt(2. / (m_kernel_size + 1)));
			auto generator = std::bind(distribution, random_engine);
			for (int i = 0; i < m_weights.size(); i++)
			{
				for (int j = 0; j < m_weights.at(i).size(); j++)
					m_weights[i][j] = generator();
				m_biases[i][0] = _DT();
			}
		}
	};
#else
	template<typename _DT>
	class ConvLayer1D : public Layer<_DT>
	{
	public:
		typedef _DT weight_t;
		typedef	_DT bias_t;
		typedef std::vector<std::vector<_DT>> weights_container_t;
		typedef std::vector<std::vector<_DT>> biases_container_t;
		typedef std::vector<std::vector<std::vector<_DT>>> input_t; // [feature map, feature]
		typedef std::vector<std::vector<std::vector<_DT>>> output_t; // [feature map, feature]
	private:
		int m_filters_in;
		int m_filters_out;
		int m_kernel_size;
		int m_stride;
		int m_padding;
		weights_container_t m_weights;
		biases_container_t m_biases;
	public:
		ConvLayer1D(int filters_in, int filters_out, int kernel_size, int stride = 1, int padding = 0)
			:
			m_filters_in(filters_in),
			m_filters_out(filters_out),
			m_kernel_size(kernel_size),
			m_stride(stride),
			m_padding(padding),
			m_weights(filters_out),
			m_biases(filters_out)
		{
			for (int i = 0; i < filters_out; i++)
			{
				m_weights[i].resize(kernel_size);
				m_biases[i].resize(1);
			}
			this->fill_weights_random();
		}


		// It will receive squere matrices as input and generate 
		output_t operator()(const input_t& input)
		{
			int batch_size = input.size();
			int input_size = input.at(0).at(0).size();
			int output_size = (m_padding * 2 + input_size - m_kernel_size) / m_stride + 1;

			// Add padding
			output_t input_with_padding = input;
			for (int i = 0; i < m_padding; i++)
			{
				for (int j = 0; j < batch_size; j++)
				{
					for (int k = 0; k < input_size; k++)
					{
						input_with_padding[j][k].insert(input_with_padding[j][k].begin(), input_with_padding[j][k].front());
						input_with_padding[j][k].insert(input_with_padding[j][k].end(), input_with_padding[j][k].back());

					}
				}
			}

			output_t output;

			// Initialize
			output.resize(batch_size);
			for (int i = 0; i < output.size(); i++)
			{
				output[i].resize(m_filters_out);
				for (int j = 0; j < m_filters_out; j++)
					output[i][j].resize(output_size);
			}

			// Process
			for (int feature_map = 0; feature_map < m_filters_out; feature_map++)
			{
				for (int item = 0; item < batch_size; item++)
				{
					for (int j = 0; j < output_size; j++)
					{
						for (int i = 0; i < m_kernel_size; i++)
						{
							for (int in_feature_map = 0; in_feature_map < m_filters_in; in_feature_map++)
								output[item][feature_map][j]
								+= input_with_padding[item][in_feature_map][j * m_stride + i]
								* m_weights[feature_map][i];
						}
						output[item][feature_map][j] -= m_biases[feature_map][0];
					}
				}
			}

			return output;
		}
		virtual DataSet<_DT> back_propagation(
			const DataSet<_DT>& errors,
			double lr = 0.001
		)override
		{
			// TODO
			return {};
		}

		virtual DataSet<_DT> operator() (const DataSet<_DT>&) override
		{
			return {};
		}

		std::string str() const
		{
			// TODO: implement
			return "";
		}
	private:
		void fill_weights_random()
		{
			std::default_random_engine random_engine;
			std::normal_distribution distribution(0., sqrt(2. / (m_kernel_size + 1)));
			auto generator = std::bind(distribution, random_engine);
			for (int i = 0; i < m_weights.size(); i++)
			{
				for (int j = 0; j < m_weights.at(i).size(); j++)
					m_weights[i][j] = generator();
				m_biases[i][0] = _DT();
			}
		}
	};
#endif


} // namespace nyann