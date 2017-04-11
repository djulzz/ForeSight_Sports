//
//  main.cpp
//  Interview
//
//  Created by Julien Esposito on 4/3/17.
//  Copyright © 2017 Julien Esposito. All rights reserved.
//

#include <iostream>
#include <string>
#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
#include <limits>

#include "Point_2D.hpp"
#include "Vector_2D.hpp"

#include "PointCloud.hpp"
#include "PointRegularGrid.hpp"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
static const int Error_Invalid_arg_num = -1;
static const int Error_Opening_File = -2;
static const int Error_Not_A_Grid = -3;
static const int Error_Not_Ortho_Base = -4;

static const int Error_None = 0;
static const int MAX_BUFFER_SIZE = 256;

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
template <typename T> Point_2D< T > rotate_point(T cx, T cy, T angle, Point_2D< T >& p)
{
	double dangle = (double)angle;
	T s = (T)sin(dangle);
	T c = (T)cos(dangle);

	// translate point back to origin:
	T x = p.X() - cx;
	T y = p.Y() - cy;
	p.SetCoords(x, y);

	// rotate point
	T xnew = p.X() * c - p.Y() * s;
	T ynew = p.X() * s + p.Y() * c;

	// translate point back:
	p.SetCoords(xnew + cx, ynew + cy);
	return p;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
size_t findMin(float& minFound, std::vector< float >& v)
{
	size_t idx = 0;
	float min = std::numeric_limits< float >::max();
	size_t size = v.size();
	for (size_t i = 0; i < size; i++) {
		if (v[i] < min) {
			min = v[i];
			idx = i;
		}
	}
	minFound = min;
	return idx;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
size_t findMax(float& maxFound, std::vector< float >& v)
{
	size_t idx = 0;
	float max = std::numeric_limits< float >::min();
	size_t size = v.size();
	for (size_t i = 0; i < size; i++) {
		if (v[i] > max) {
			max = v[i];
			idx = i;
		}
	}
	maxFound = max;
	return idx;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
float distance(float x1, float y1, float x2, float y2)
{
	float dx = x2 - x1;
	float dy = y2 - y1;
	return sqrtf(dx * dx + dy * dy);
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void Test(void)
{
	PointCloud< float > cloud;
	Point_2DF pt(1, 1);
	std::cout << "pt = " << pt << std::endl;
	cloud.AddPoint(pt);
	size_t nPts = cloud.NumberOfPoints();

	printf("Number of points = %i\r\n", nPts);
	std::cout << cloud << std::endl;
	printf("END OF TEST\r\n\r\n");
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
int main(int argc, const char * argv[])
{
	Point_2D< float >::Unit_Test();
	Vector_2D< float >::Unit_Test();

	int nArgs = argc;
	if (nArgs != 2)
	{
		printf("Usage: <progname> <input_file> - Aborting\r\n");
		return Error_Invalid_arg_num;
	}
	const char* filename =  static_cast< const char* >( argv[1] );
	FILE* f = fopen(filename, "r");
	PointRegularGrid< float > cloud;
	if (NULL == f) {
		printf("Error opening file provided as input argument - Aborting\r\n");
		return Error_Opening_File;
	}

	printf("File <%s> opened successfully - proceeding\r\n", filename );


	char buffer[MAX_BUFFER_SIZE];

	float x = 0;
	float y = 0;
	while (!feof(f)) {
		memset(buffer, 0, MAX_BUFFER_SIZE * sizeof(char));
		fgets(buffer, MAX_BUFFER_SIZE, f);

		// we dont want to add a point if the scanned buffer is just \r\n
		if (strlen(buffer) > 3) {
			sscanf(buffer, "%f,%f\r\n", &x, &y);
			printf("x = %.1f, y= %.1f\r\n", x, y);
			Point_2D< float > pt(x, y);
			cloud.AddPoint(pt);

		}
		//printf("%s\r\n", buffer);
	}
	fclose(f);

	size_t nPoints_collected = cloud.NumberOfPoints();
	printf("Number of points added to cloud = %i\r\n", nPoints_collected );
	std::cout << cloud << std::endl;
	Utilities::value_info_t< float > nfo_Xmin = cloud.GetXMin();
	Utilities::value_info_t< float > nfo_Xmax = cloud.GetXMax();
	Utilities::value_info_t< float > nfo_Ymin = cloud.GetYMin();
	Utilities::value_info_t< float > nfo_Ymax = cloud.GetYMax();

	std::vector< size_t > extremas = cloud.GetIndicesOfExtremaPoints();

	std::cout << "XMIN - idx = " << extremas[X_MIN] << " - value = " << cloud[extremas[X_MIN]] << std::endl;
	std::cout << "XMAX - idx = " << extremas[X_MAX] << " - value = " << cloud[extremas[X_MAX]] << std::endl;
	std::cout << "YMIN - idx = " << extremas[Y_MIN] << " - value = " << cloud[extremas[Y_MIN]] << std::endl;
	std::cout << "YMAX - idx = " << extremas[Y_MAX] << " - value = " << cloud[extremas[Y_MAX]] << std::endl;

	Point_2D< float > origin(cloud[extremas[Y_MIN]]); // 0
	Vector_2D< float > Y_MIN_TO_XMIN = cloud[extremas[X_MIN]] - origin; // 0 to 2
	Vector_2D< float > Y_MIN_TO_XMAX = cloud[extremas[X_MAX]] - origin; // 0 to 6
	Vector_2D< float > Y_MIN_TO_YMAX = cloud[extremas[Y_MAX]] - origin; // 0 to 8
	
	std::cout << "Norm Y_MIN_TO_XMIN = " << Y_MIN_TO_XMIN.Norm() << std::endl; // 0 to 2 --> upward
	std::cout << "Norm Y_MIN_TO_XMAX = " << Y_MIN_TO_XMAX.Norm() << std::endl; // 0 to 6 --> forward
	std::cout << "Norm Y_MIN_TO_YMAX = " << Y_MIN_TO_YMAX.Norm() << std::endl; // 0 to 8

	if(!Y_MIN_TO_XMAX.MakesRightAngleWith(Y_MIN_TO_XMIN))
	{
		std::cout << "The vectors Y_MIN_TO_XMAX and Y_MIN_TO_XMIN DO NOT FORM an Orthonormed base - Aborting" << std::endl;
		return Error_Not_Ortho_Base;
	}
	std::cout << "We have an orthonormal base - Yeah!" << std::endl;
	std::cout << "Calculating the angle between [1, 0] and Y_MIN_TO_XMAX..." << std::endl;
	Vector_2D< float > v_xaxis(1, 0);
	float angle_grid_in_radians = v_xaxis.AngleWith(Y_MIN_TO_XMAX);
	float angle_grid_in_degree = angle_grid_in_radians * 180 / Utilities::PI< float >;
	std::cout << "The grid makes an angle of " << angle_grid_in_degree << " wrt x-axis" << std::endl;
	printf("Printing out the the number of points collected...\r\n");
	for (size_t i = 0; i < nPoints_collected; i++) {
		std::cout << cloud[i] << std::endl;
	}

	printf("Calculating the number of rows and collumns - H1 - nRows = nColums\r\n");

	unsigned int nRows = static_cast< int >( sqrtf(static_cast<float>(nPoints_collected)));
	unsigned int nCols = nRows;
	if( nRows * nCols != nPoints_collected ) {
		printf("The number of points collected does not form a grid - Aborting\r\n");
		return Error_Not_A_Grid;
	}

	Point_2D< float > center_rotation = cloud[ extremas[Y_MIN] ];
	float cx = center_rotation.X();
	float cy = center_rotation.Y();
	std::cout << "Displaying rotated points..." << std::endl;
	for (size_t i = 0; i < nPoints_collected; i++) {
		Point_2D< float > p = rotate_point< float >(cx, cy, -angle_grid_in_radians, cloud[i]);
		std::cout << p << std::endl;
	}
	
	

	printf("The grid of points collected has %i Rows and %i Columns\r\n", nRows, nCols);



	printf("\r\n\r\n");

	printf("Program done executing properly - Exiting with success\r\n");

	// cleaning the vector of points

    return Error_None;
}
