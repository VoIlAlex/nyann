#include "pch.h"
#include "..//nya-nn//nyann.h"



TEST(DataSet, DataSet_construction)
{
	nyann::DataRow<float> row = { 1.0, 2.0, 3.0 };
	nyann::DataSet<float> dataset = {
		{1.0, 2.0},
		{3.0, 4.0}
	};
}

TEST(Size, Size_construction)
{
	nyann::Size size{ 2, 5, 10 };
}