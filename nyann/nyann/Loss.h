#pragma once


// For all the framework configurations
#include "_config.h"

#include "dataset.h"
#include "utils/Serializer.h"

namespace nyann {

	template<typename _DT>
	class Loss : public Serializable<std::string>
	{
	public:
		virtual DataSet<_DT> operator()(const DataSet<_DT>& output, const DataSet<_DT>& target) = 0;
		virtual DataSet<_DT> derivative(const DataSet<_DT>& loss) = 0;
		std::string serialize() const override
		{
			return "";
		}
		void deserialize(std::istringstream& stream) override
		{
			std::string empty_line;
			std::getline(stream, empty_line);
		}
	};

} // namespace nyann


// include subclasses of Loss
#include "Loss/MSELoss.h"