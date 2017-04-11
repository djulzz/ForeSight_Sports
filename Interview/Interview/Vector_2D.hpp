#ifndef VECTOR_2D_HPP
#define VECTOR_2D_HPP

#include "Point_2D.hpp"
#include "Utilities.hpp"
#include <cmath>
template <typename T> class Vector_2D : public Point_2D< T >
{
	public:
		/******************************************************************/
		/******************************************************************/
		Vector_2D< T >(T x, T y)
			: Point_2D< T >( x, y )
		{

		}

		/******************************************************************/
		/******************************************************************/
		Vector_2D< T >(const Point_2D< T >& rhs) : Point_2D< T >(rhs) {}

		/******************************************************************/
		/******************************************************************/
		Vector_2D< T > operator=(const Point_2D< T >& rhs)
		{
			return Point_2D< T >::operator=(rhs);
		}
		/******************************************************************/
		/******************************************************************/
		Vector_2D< T >(void) : Point_2D< T >() {}

		/******************************************************************/
		/******************************************************************/
		Vector_2D< T >(const Vector_2D< T >& rhs) : Point_2D< T >(rhs) {}

		/******************************************************************/
		/******************************************************************/
		T Norm() const
		{
			double x2 = (double)(m_x * m_x);
			double y2 = (double)(m_y * m_y);
			T res =  (T)std::sqrt(x2 + y2);
			//std::cout << "Norm = " << res << std::endl;
			return res;
		}
		/******************************************************************/
		/******************************************************************/
		T Dot(const Vector_2D< T >& rhs)
		{
			return m_x * rhs.m_x + m_y * rhs.m_y;
		}
		/******************************************************************/
		/******************************************************************/
		T AngleWith(const Vector_2D< T >& rhs)
		{
			double nProduct = double( Norm() * rhs.Norm() );
			double dot = (double)(Dot(rhs));
			return ( T )( std::acos( ( double )( dot / nProduct) ) );
		}

		/******************************************************************/
		/******************************************************************/
		bool MakesRightAngleWith(const Vector_2D< T >& rhs)
		{
			T angle = this->AngleWith(rhs);
			bool c1 = Utilities::AreValuesAlmostSame< T >(angle, Utilities::PI_OVER_2< T >);
			bool c2 = Utilities::AreValuesAlmostSame< T >(angle, -Utilities::PI_OVER_2< T >);
			return (c1 || c2);
		}

		/******************************************************************/
		/******************************************************************/
		bool MakesCWRightAngleWith(const Vector_2D< T >& rhs)
		{
			T angle = this->AngleWith(rhs);
			bool c1 = Utilities::AreValuesAlmostSame< T >(angle, Utilities::PI_OVER_2< T >);
			return (c1);
		}

		/******************************************************************/
		/******************************************************************/
		static void Unit_Test(void)
		{
			std::cout << "Unit Test Vector_2D Class" << std::endl;
			
			Point_2D< T > end(T(3), T(4));
			Point_2D< T > origin = end;

			Vector_2D< T > v = end - origin;
			std::cout << "Vector " << end << " - " << origin << " = " << v << std::endl;
			std::cout << "End Unit Test Vector_2D Class" << std::endl;
		}

	//	/******************************************************************/
	//	/******************************************************************/
	//	Vector_2D< T >& operator=(const Vector_2D< T >& rhs)
	//	{
	//		m_x = rhs.m_x;
	//		m_y = rhs.m_y;
	//		return *this;
	//	}

};

#endif // VECTOR_2D_HPP

