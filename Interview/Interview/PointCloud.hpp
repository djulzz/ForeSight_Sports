#ifndef POINTCLOUD_HPP
#define POINTCLOUD_HPP

#include "Point_2D.hpp"

#include <vector>

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
template <typename T> class PointCloud
{
	public:
		PointCloud< T >()
		{
			p_clear();
		}
		virtual ~PointCloud()
		{
			p_clear();
		}

		void AddPoint(const Point_2D< T >& pt)
		{
			m_pts.push_back(pt);
			m_Xs.push_back(pt.X());
			m_Xs.push_back(pt.Y());
		}

		size_t NumberOfPoints(void)
		{
			return m_pts.size();
		}

	protected:
		void p_clear(void)
		{
			m_pts.clear();
			m_Xs.clear();
			m_Ys.clear();
		}
	protected:
		std::vector< Point_2D< T > > m_pts;
		std::vector< T > m_Xs;
		std::vector< T > m_Ys;

};
#endif // POINTCLOUD_HPP defined
