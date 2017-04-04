#ifndef POINTREGULARGRID_HPP
#define POINTREGULARGRID_HPP

#include "PointCloud.hpp"
#include "Utilities.hpp"
#include <vector>

typedef enum _E_Exrema_Label
{
	X_MIN = 0,
	X_MAX = 1,
	Y_MIN = 2,
	Y_MAX = 3
} E_Extrema_Label;
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
template <typename T> class PointRegularGrid : public PointCloud< T >
{
	public:
		PointRegularGrid< T >(void) : PointCloud< T >() {}

		std::vector< size_t > GetIndicesOfExtremaPoints()
		{
			Utilities::value_info_t< float > nfo_Xmin = GetXMin();
			Utilities::value_info_t< float > nfo_Xmax = GetXMax();
			Utilities::value_info_t< float > nfo_Ymin = GetYMin();
			Utilities::value_info_t< float > nfo_Ymax = GetYMax();

			std::vector< size_t > indices;
			indices.push_back(nfo_Xmin.Index());
			indices.push_back(nfo_Xmax.Index());
			indices.push_back(nfo_Ymin.Index());
			indices.push_back(nfo_Ymax.Index());
			return indices;
		}
};
#endif // POINTREGULARGRID_HPP

