#pragma once


// For all the framework configurations
#include "../_config.h"

#include <exception>
#include <stdexcept>


namespace nyann {

	class NyannError
	{};

	class DataSetError
	{};

	class DifferentSizeError : public NyannError, public ::std::out_of_range
	{
	public:
		using ::std::out_of_range::out_of_range;
	};

	class ConversionError : public NyannError, public ::std::runtime_error {
	public:
		using ::std::runtime_error::runtime_error;
	};

	class SizeError : public NyannError, public  ::std::runtime_error {
	public:
		using ::std::runtime_error::runtime_error;
	};

	class IndexError : public NyannError, public ::std::out_of_range
	{
	public:
		using ::std::out_of_range::out_of_range;
	};

	class IndexSizeError : public NyannError, public IndexError
	{
	public:
		IndexSizeError(const std::string &message)
			:
			IndexError(message.c_str()) {}
	};

	class IndexOverflowError : public NyannError, public IndexSizeError
	{
	public:
		using IndexSizeError::IndexSizeError;
	};

	class NotImplementedError : public NyannError, public ::std::runtime_error
	{
	public:
		using ::std::runtime_error::runtime_error;
	};

	class ConstParentError : public DataSetError, public ::std::runtime_error
	{
	public:
		using ::std::runtime_error::runtime_error;
	};

	class DeprecationError : public NyannError, public ::std::runtime_error
	{
	public:
		using ::std::runtime_error::runtime_error;
	};

} // namespace nyann