#pragma once
#include <iostream>
#include "DataSet_draft.h"

namespace nyann {

	template<typename _DT, typename T = typename DataSet_draft<_DT>::NestedDataSet>
	std::ostream& operator<<(std::ostream& stream, const T& dataset)
	{
		try
		{
			stream << dataset.value();
		}
		catch (ConversionError & e)
		{
			stream << "[";
			for (auto it = dataset.begin(); it != dataset.end(); it++)
			{
				if (it != dataset.begin())
					stream << ", ";
				stream << *it;
			}
			stream << "]";
			std::endl(stream);
		}
		return stream;
	}

	std::ostream& operator<<(std::ostream& stream, const DataSet_draft<double>::NestedDataSet& dataset);
	std::ostream& operator<<(std::ostream& stream, const DataSet_draft<float>::NestedDataSet& dataset);

	/*std::ostream& operator<<(std::ostream& stream, typename DataSet_draft<float>::NestedDataSet dataset)
	{
		try
		{
			stream << dataset.value();
		}
		catch (ConversionError & e)
		{
			stream << "[";
			for (auto it = dataset.begin(); it != dataset.end(); it++)
			{
				if (it != dataset.begin())
					stream << ", ";
				stream << *it;
			}
			stream << "]";
			std::endl(stream);
		}
		return stream;
	}*/

	template<typename _DT>
	std::ostream& operator<<(std::ostream& stream, const DataSet_draft<_DT>& dataset)
	{
		stream << "[";
		for (auto it = dataset.begin(); it != dataset.end(); it++)
		{
			stream << *it;
			if (it != dataset.end() - 1)
				std::endl(stream);
		}
		stream << "]";
		return stream;
	}

	

} // namespace nyann