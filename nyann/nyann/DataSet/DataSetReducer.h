#pragma once


// For all the framework configurations
#include "../_config.h"

#include "../utils/Size.h"

#include <vector>


namespace nyann {

	template<typename _DT>
	class DataSetReducer
	{
	public:
		virtual _DT operator()(const std::vector<_DT>& data, const Size<size_t>& size) const = 0;
	};

} // namespace nyann