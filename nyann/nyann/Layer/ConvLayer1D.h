

// For all the framework configurations
#include "../_config.h"

#include "../Layer.h"
#include "../dataset.h"

namespace nyann {

	template<typename _DT>
	class ConvLayer1D : public Layer<_DT>
	{
		int m_filters_in;
		int m_filters_out;
		int m_kernel_size;
		int m_stride;
		int m_padding;
	public:
		ConvLayer1D(int filters_in, int filters_out, int kernel_size, int stride = 1, int padding=0)
			: 
			m_filters_in(filters_in),
			m_filters_out(filters_out),
			m_kernel_size(kernel_size),
			m_stride(stride),
			m_padding(padding)
		{

		}

		// It will receive squere matrices as input and generate 
		virtual DataSet<_DT> operator()(const DataSet<_DT>& dataset) override
		{
			
			return {};
		}
		virtual DataSet<_DT> back_propagation(
			const DataSet<_DT>& errors,
			double lr = 0.001
		)
		{
			// TODO
			return {};
		}

		std::string str() const
		{
			// TODO: implement
			return "";
		}
	};

} // namespace nyann