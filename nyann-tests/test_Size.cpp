#include "pch.h"
#include "..//nyann//nyann.h"

namespace {

	TEST(Size, Construction)
	{
		nyann::Size<> size{ 2, 5, 10 };
	}

} // namespace