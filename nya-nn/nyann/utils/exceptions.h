#pragma once
#include <exception>
#include <stdexcept>

namespace nyann {

	class DifferentSizeError : public std::exception {}

} // namespace nyann