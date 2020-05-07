#pragma once


// For all the framework configurations
#include "../_config.h"

#include "../DataSet.h"
#include "../utils/Serializer.h"
#include "../nyann/nyann/utils/conversion.h"

#include <string>
#include <sstream>
#include <iterator>


namespace nyann {

	template<typename _DT>
	class DataSetSerializer
	{
	public:
		std::string serialize(const DataSet<_DT>& dataset)
		{
			VectorSerializer<_DT> data_serializer;
			VectorSerializer<size_t> size_serializer;
			std::stringstream result;
			result << data_serializer.serialize(dataset.data()) << "\n";
			result << size_serializer.serialize(dataset.size());
			return result.str();
		}

		DataSet<_DT> deserialize(std::istringstream& input)
		{
			//std::istringstream input(serialized);
			std::string raw_size, raw_data;
			VectorSerializer<_DT> data_serializer;
			VectorSerializer<size_t> size_serializer;
			std::getline(input, raw_data);
			std::getline(input, raw_size);

			std::istringstream raw_size_stream(raw_size);
			std::istringstream raw_data_stream(raw_data);
			std::vector<_DT> data = data_serializer.deserialize(raw_data_stream);
			Size<> size = size_serializer.deserialize(raw_size_stream);
			DataSet<_DT> result(size, data);
			return result;

		}


	};

} // namespace nyann