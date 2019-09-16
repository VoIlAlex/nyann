#pragma once
#include <iostream>

#include "..//dataset.h"

template<typename _DT>
std::ostream& operator<<(std::ostream& stream, const nyann::DataSet<_DT>& dataset)
{
	std::cout << "[[";
	for (int i = 0; i < dataset.size(); i++)
	{
		if (i != 0)
			std::cout << "[";

		for (int j = 0; j < dataset[i].size(); j++)
		{
			if (j != 0)
				std::cout << ", ";
			std::cout << dataset[i][j];
		}
		std::cout << "]";
		if (i != dataset.size() - 1)
			std::cout << ", " << std::endl;
	}
	std::cout << "]";

	return stream;
}