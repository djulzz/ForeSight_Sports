//
//  main.cpp
//  Interview
//
//  Created by Julien Esposito on 4/3/17.
//  Copyright © 2017 Julien Esposito. All rights reserved.
//

#include <iostream>
#include <string>
#include "Point_2D.hpp"
#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
#include <limits>
#include "PointCloud.hpp"
#include "PointRegularGrid.hpp"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
static const int Error_Invalid_arg_num = -1;
static const int Error_Opening_File = -2;
static const int Error_Not_A_Grid = -3;

static const int Error_None = 0;
static const int MAX_BUFFER_SIZE = 256;

float* array = 0;
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
int main(int argc, const char * argv[]) {
    
	Test();
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
	std::vector< Point_2DF > pts;
	std::vector< float > Xs;
	std::vector< float > Ys;

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
			Point_2DF pt(x, y);
			cloud.AddPoint(pt);
			pts.push_back( pt );
			Xs.push_back(x);
			Ys.push_back(y);
		}
		//printf("%s\r\n", buffer);
	}
	fclose(f);

	printf("Number of points added to cloud = %i\r\n", cloud.NumberOfPoints());
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

	printf("END TEST INSIDE MAIN\r\n\r\n");
	size_t nPoints_collected = pts.size();

	printf("Printing out the the number of points collected...\r\n");
	for (size_t i = 0; i < nPoints_collected; i++) {
		printf("pts %i/%i --> (%.1f,%.1f)\r\n", i + 1, nPoints_collected, pts[i].X(), pts[i].Y());
	}
	printf("The numbers of points collected is %li\r\n", nPoints_collected );
	printf("Calculating the number of rows and collumns - H1 - nRows = nColums\r\n");

	unsigned int nRows = static_cast< int >( sqrtf(static_cast<float>(nPoints_collected)));
	unsigned int nCols = nRows;
	if( nRows * nCols != nPoints_collected ) {
		printf("The number of points collected does not form a grid - Aborting\r\n");
		return Error_Not_A_Grid;
	}

	printf("The grid of points collected has %i Rows and %i Columns\r\n", nRows, nCols);

	float minX, maxX, minY, maxY;
	
	size_t index_minX = findMin(minX, Xs);
	size_t index_maxX = findMax(maxX, Xs);
	size_t index_minY = findMin(minY, Ys);
	size_t index_maxY = findMax(maxY, Ys);
	printf("MinX found for Xs @ IDX = %i - MIN = %.1f\r\n", index_minX, minX);
	printf("MaxX found for Xs @ IDX = %i - MIN = %.1f\r\n", index_maxX, maxX);
	printf("MinY found for Ys @ IDX = %i - MIN = %.1f\r\n", index_minY, minY);
	printf("MaxY found for Ys @ IDX = %i - MIN = %.1f\r\n", index_maxY, maxY);

	printf("\r\n\r\n");
	printf("The extrema of the grid ar located at the following indices with following coordinates\r\n");
	printf("Extremum 0 - INDEX = %i - (x,y) = (%.1f,%.1f)\r\n", index_minX, Xs[index_minX], Ys[index_minX]);
	printf("Extremum 1 - INDEX = %i - (x,y) = (%.1f,%.1f)\r\n", index_maxX, Xs[index_maxX], Ys[index_maxX]);
	printf("Extremum 2 - INDEX = %i - (x,y) = (%.1f,%.1f)\r\n", index_minY, Xs[index_minY], Ys[index_minY]);
	printf("Extremum 3 - INDEX = %i - (x,y) = (%.1f,%.1f)\r\n", index_maxY, Xs[index_maxY], Ys[index_maxY]);

	float x1, y1, x2, y2, x3, y3, x4, y4;

	x1 = Xs[index_minX];
	y1 = Ys[index_minX];

	x2 = Xs[index_maxX];
	y2 = Ys[index_maxX];

	x3 = Xs[index_minY];
	y3 = Ys[index_minY];

	x4 = Xs[index_maxY];
	y4 = Ys[index_maxY];

	// we take a reference point for distance:
	// - index_minX --> index_maxX -- Distance between P1, P2
	// - index_minX --> index_minY -- Distance between P1, P3
	// - index_minX --> index_maxY -- Distance between P1, P4

	float d2_index_maxX = distance( x1, y1, x2, y2);
	float d2_index_minY = distance(x1, y1, x3, y3);
	float d2_index_maxY = distance(x1, y1, x4, y4);
	printf("Distance from point index_minX to index_maxX = %f\r\n", d2_index_maxX);
	printf("Distance from point index_minX to index_minY = %f\r\n", d2_index_minY);
	printf("Distance from point index_minX to index_maxY = %f\r\n", d2_index_maxY);

	printf("\r\n\r\n");
	printf("Assumption is made we have a grid, so the two closest distances are consecutive edges\r\n");
	float d1 = fabsf(d2_index_maxX - d2_index_minY);
	float d2 = fabsf(d2_index_maxX - d2_index_maxY);

	//// if d1 <= d2, then Distance between { P[index_minX], P[index_maxX] }
	//// is                      comparable { P[index_minX], P[index_minY] }
	//if (d1 <= d2)
	//{
	//	printf("Points with indices %i %i %i make two consecutive edges\r\n", index_minX, index_maxX, index_minY );
	//}
	//// else 
	//else {
	//	printf("Points with indices %i %i %i make two consecutive edges\r\n", index_minX, d2_index_maxX, d2_index_maxY);
	//}
	//std::vector< size_t > index;
	//for (size_t i = 0; i<nPoints_collected; i++) {
	//	index.push_back( i );
	//}

	//printf("Checking the indices...\r\n");
	//size_t* ptr_index = &index[0];
	//for (size_t i = 0; i<index.size(); i++) {
	//	printf( "%li\r\n", ptr_index[i] );
	//}

	//array = ( float* )( &Xs[ 0 ] );
	//printf("Checking the X values...\r\n");
	//for (size_t i = 0; i<Xs.size(); i++) {
	//	printf("%f\r\n", array[i]);
	//}

	//std::qsort( &index[ 0 ], nPoints_collected, nPoints_collected * sizeof( size_t ), cmp);
	//for (size_t i = 0; i<nPoints_collected; i++) {
	//	printf("%d\t%d\n", Xs[index[i]], index[i]);
	//}
	printf("Program done executing properly - Exiting with success\r\n");

	// cleaning the vector of points
	pts.clear();
    return Error_None;
}
