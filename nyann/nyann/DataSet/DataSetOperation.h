#pragma once


// For all the framework configurations
#include "../_config.h"

#include "../utils/Size.h"

#include <vector>


namespace nyann {

	template<typename _DT>
	class DataSetOperation
	{
	public:
		virtual void operator()(std::vector<_DT>& data, Size<size_t>& size) const = 0;
	};

} // namespace nyann