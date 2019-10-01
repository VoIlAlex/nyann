#pragma once
#include <exception>
#include <stdexcept>

namespace nyann {

	class DifferentSizeError : public ::std::exception {};

	class ConversionError : public ::std::exception {};

	class IndexError : public ::std::out_of_range
	{
	public:
		using ::std::out_of_range::out_of_range;
	};

	class IndexSizeError : public IndexError
	{
	public:
		using IndexError::IndexError;
	};

	class IndexOverflowError : public IndexSizeError
	{
	public:
		using IndexSizeError::IndexSizeError;
	};

} // namespace nyann