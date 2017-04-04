#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <limits>
#include <vector>
#include <cmath>

namespace Utilities
{
	template <typename T>  class value_info_t
	{
		public:
			/******************************************************************/
			/******************************************************************/
			value_info_t()
			{
				m_value = 0;
				m_index = 0;
			}

			/******************************************************************/
			/******************************************************************/
			value_info_t< T >(const value_info_t< T >& rhs)
			{

					m_value = rhs.m_value;
					m_index = rhs.m_index;

			}

			/******************************************************************/
			/******************************************************************/
			value_info_t& operator=(const value_info_t& rhs)
			{

					m_value = rhs.m_value;
					m_index = rhs.m_index;

				return *this;
			}

			/******************************************************************/
			/******************************************************************/
			value_info_t( T value, size_t index )
			{
				m_value = value;
				m_index = index;
			}

			/******************************************************************/
			/******************************************************************/
			inline size_t Index() { return m_index; }

		protected:
			T	   m_value;
			size_t m_index;
	};
	////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////
	template <typename T> value_info_t< T > findMax( std::vector< T >& v)
	{
		size_t idx = 0;
		T max = std::numeric_limits< T >::min();
		size_t size = v.size();
		for (size_t i = 0; i < size; i++) {
			if (v[i] > max) {
				max = v[i];
				idx = i;
			}
		}
		value_info_t< T > info(max, idx);
		return info;
	}

	////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////
	template <typename T> value_info_t< T > findMin( std::vector< T >& v)
	{
		size_t idx = 0;
		T min = std::numeric_limits< T >::max();
		size_t size = v.size();
		for (size_t i = 0; i < size; i++) {
			if (v[i] < min) {
				min = v[i];
				idx = i;
			}
		}
		value_info_t< T > info(min, idx);
		return info;
	}

}
#endif // UTILITIES_HPP

