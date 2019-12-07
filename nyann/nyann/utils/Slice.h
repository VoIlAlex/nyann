#pragma once
#include <vector>

// For all the framework configurations
#include "../_config.h"

namespace nyann {

	template<typename _DT=unsigned int>
	class Slice : public std::vector<_DT>
	{
		// whether it's an index
		// not an slice
		bool m_is_index;
	public:
		// Constructors
		Slice()
			: ::std::vector<_DT>{ 0, 1, 1 }, m_is_index(true)
		{}
		Slice(_DT start, _DT end, _DT step = 1)
			: ::std::vector<_DT>{ start, end, step }, m_is_index(false)
		{}
		Slice(_DT idx)
			: ::std::vector<_DT>{ idx, idx + 1, 1 }, m_is_index(true)
		{}

		_DT width() const
		{
			return (this->at(1) - this->at(0)) / this->at(2);
		}

		// Constant getters
		const bool& is_index() const
		{
			return m_is_index;
		}
		const _DT& from_value() const
		{
			return this->at(0);
		}
		const _DT& to_value() const
		{
			return this->at(1);
		}
		const _DT& step_value() const
		{
			return this->at(2);
		}

		// Mutable getters
		_DT& from_value()
		{
			return this->at(0);
		}
		_DT& to_value()
		{
			return this->at(1);
		}
		_DT& step_value()
		{
			return this->at(2);
		}
		bool& is_index()
		{
			return m_is_index;
		}

		// operators
		using std::vector<_DT>::operator[];

		/*int& operator[](int i)
		{
			return std::vector<int>::operator[](i);
		}

		const int& operator[](int i) const
		{
			return std::vector<int>::operator[](i);
		}*/

		operator _DT() const
		{
			return this->operator[](0);
		}
	};

} // namespace nyann