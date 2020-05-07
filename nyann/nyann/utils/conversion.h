#pragma once


// For all the framework configurations
#include "../_config.h"

#include "./Size.h"
#include "./Index.h"

#include <string>


namespace nyann {

	template<typename _DT>
	Index<_DT> to_index(const Size<_DT>& size)
	{
		Index<_DT> result(size.size());
		for (int i = 0; i < size.size(); i++)
			result[i] = size[i];
		return result;
	}

	template<typename _DT>
	_DT to_type(const std::string& arg)
	{
		return _DT(arg);
	}

	template<>
	double to_type<double>(const std::string& arg);

	template<>
	float to_type<float>(const std::string& arg);

	template<>
	size_t to_type<size_t>(const std::string& arg);

} // namespace nyann