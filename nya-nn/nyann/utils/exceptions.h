#pragma once
#include <exception>
#include <stdexcept>

namespace nyann {

	class DifferentSizeError : public ::std::exception {};
	class ConversionError : public ::std::exception {};
	class IndexOverflowError : public ::std::exception {};

} // namespace nyann