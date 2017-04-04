#ifndef VECTOR_2D_HPP
#define VECTOR_2D_HPP

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
template < typename T > class Vector_2D : public T::template Point_2D< T >
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
		Vector_2D< T >(void) : Point_2D< T >() {}

		/******************************************************************/
		/******************************************************************/


};
#endif // VECTOR_2D_HPP
