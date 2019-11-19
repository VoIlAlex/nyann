#pragma once
#include <exception>
#include <stdexcept>

namespace nyann {

	class DifferentSizeError : public ::std::out_of_range 
	{
		public:
		using ::std::out_of_range::out_of_range;
	};

	class ConversionError : public ::std::runtime_error {
		public:
		using ::std::runtime_error::runtime_error;
	};

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

	class NotImplementedError : public ::std::runtime_error {
		public:
		using ::std::runtime_error::runtime_error;
	};

} // namespace nyann