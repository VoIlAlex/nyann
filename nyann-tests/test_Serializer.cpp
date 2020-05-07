#include "pch.h"
#include "../nyann/nyann.h"

namespace {

	TEST(Serializers, VectorSerializer)
	{
		nyann::VectorSerializer<double> serializer;
		std::vector<double> vec{ 1, 2, 3, 4 };
		std::string result = serializer.serialize(vec);
		std::istringstream input(result);
		std::vector<double> back_vec = serializer.deserialize(input);
		ASSERT_EQ(back_vec[0], 1);
		ASSERT_EQ(back_vec[1], 2);
		ASSERT_EQ(back_vec[2], 3);
		ASSERT_EQ(back_vec[3], 4);
		ASSERT_EQ(result, "1 2 3 4");
	}

} // namespace