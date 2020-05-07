#pragma once


// For all the framework configurations
#include "../_config.h"

#include "../utils/conversion.h"

#include <string>
#include <iterator>
#include <sstream>


namespace nyann {

	template<typename _DT>
	class Serializable
	{
	public:
		virtual std::string serialize() const = 0;
		virtual void deserialize(std::istringstream&) = 0;
	};


} // namespace nyann