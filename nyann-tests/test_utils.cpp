#include "pch.h"
#include "..//nyann//nyann.h"

namespace {
	TEST(FrameworkExceptions, DifferentSizeError)
	{
		try
		{
			throw nyann::DifferentSizeError("Error");
		}
		catch (nyann::DifferentSizeError &e)
		{
			EXPECT_EQ(std::string(e.what()), "Error");
		}
	}

	TEST(FrameworkExceptions, ConversionError)
	{
		try
		{
			throw nyann::ConversionError("Error");
		}
		catch (nyann::ConversionError & e)
		{
			EXPECT_EQ(std::string(e.what()), "Error");
		}
	}

	TEST(FrameworkExceptions, IndexError)
	{
		try
		{
			throw nyann::IndexError("Error");
		}
		catch (nyann::IndexError & e)
		{
			EXPECT_EQ(std::string(e.what()), "Error");
		}
	}

	TEST(FrameworkExceptions, IndexSizeError)
	{
		try
		{
			throw nyann::IndexSizeError("Error");
		}
		catch (nyann::IndexSizeError & e)
		{
			EXPECT_EQ(std::string(e.what()), "Error");
		}
	}

	TEST(FrameworkExceptions, IndexOverflowError)
	{
		try
		{
			throw nyann::IndexOverflowError("Error");
		}
		catch (nyann::IndexOverflowError & e)
		{
			EXPECT_EQ(std::string(e.what()), "Error");
		}
	}

	TEST(FrameworkExceptions, NotImplementedError)
	{
		try
		{
			throw nyann::NotImplementedError("Error");
		}
		catch (nyann::NotImplementedError & e)
		{
			EXPECT_EQ(std::string(e.what()), "Error");
		}
	}
} // namespace