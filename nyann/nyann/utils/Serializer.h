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

	template<typename _DT>
	class VectorSerializer
	{
	public:
		std::string serialize(const std::vector<_DT>& data) const
		{
			std::ostringstream result;
			for (int i = 0; i < data.size(); i++)
			{
				if (i != 0)
					result << " ";
				result << data[i];
			}
			return result.str();
		}

		std::vector<_DT> deserialize(std::istringstream& input) const
		{
			std::string line;
			std::getline(input, line);
			std::istringstream line_input(line);
			//std::istringstream input(data);
			std::vector<std::string> tokens{ std::istream_iterator<std::string>(line_input), std::istream_iterator<std::string>() };
			std::vector<_DT> result(tokens.size());
			for (int i = 0; i < tokens.size(); i++)
				result[i] = to_type<_DT>(tokens[i]);
			return result;
		}
	};

} // namespace nyann