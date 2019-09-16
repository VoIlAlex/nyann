#pragma once
#include <iostream>

#include "..//dataset.h"

template<typename _DT>
std::ostream& operator<<(std::ostream& stream, const nyann::DataSet<_DT>& dataset)
{
	stream << "[[";
	for (int i = 0; i < dataset.size(); i++)
	{
		if (i != 0)
			stream << "[";

		for (int j = 0; j < dataset[i].size(); j++)
		{
			if (j != 0)
				stream << ", ";
			stream << dataset[i][j];
		}
		stream << "]";
		if (i != dataset.size() - 1)
			stream << ", " << std::endl;
	}
	stream << "]";

	return stream;
}

	return stream;
}