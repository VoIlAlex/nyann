#include "./conversion.h"

namespace nyann {

	template<>
	double to_type<double>(const std::string& arg)
	{
		return atof(arg.c_str());
	}

	template<>
	float to_type<float>(const std::string& arg)
	{
		return atof(arg.c_str());
	}

	template<>
	size_t to_type<size_t>(const std::string& arg)
	{
		return atoi(arg.c_str());
	}

} // namespace nyann