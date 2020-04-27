#pragma once


// For all the framework configurations
#include "../_config.h"

#include "./Size.h"
#include "./Index.h"


namespace nyann {

	template<typename _DT>
	Index<_DT> to_index(const Size<_DT>& size)
	{
		Index<_DT> result(size.size());
		for (int i = 0; i < size.size(); i++)
			result[i] = size[i];
		return result;
	}

} // namespace nyann