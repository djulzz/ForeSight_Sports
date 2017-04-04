/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Point_2D.hpp
 * Author: Esposito
 *
 * Created on April 3, 2017, 4:13 PM
 */

#ifndef POINT_2D_HPP
#define POINT_2D_HPP


//#ifdef __cplusplus
//extern "C" {
//#endif

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
    template <typename T> class Point_2D {
        public:
            Point_2D< T >( T x, T y )
            {
                m_x = x;
                m_y = y;
            }
            
            Point_2D< T >( void )
            {
                m_x = static_cast< T >( 0 );
                m_y = static_cast< T >( 0 );
            }
            
            void SetCoords( T x, T y )
            {
                m_x = x;
                m_y = y;
                return;
            }
            
            virtual ~Point_2D() {}
            
            inline T X( void ) { return m_x; }
            inline T Y( void ) { return m_y; }
            
        protected:
            T m_x;
            T m_y;
    };

    typedef Point_2D< double > Point_2DD;
	typedef Point_2D< float > Point_2DF;
//#ifdef __cplusplus
//}
//#endif

#endif /* POINT_2D_HPP */

