#ifndef __k_means__
#define __k_means__
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <iterator>
#include <assert.h>

//#include <omp.h>

typedef struct {
	double x1;
	double x2;
}Point;
/**
class Point{

public:
	Point(double x11 = 0.0, double x22 = 0.0 ) {
		x1 = x11; x2 = x22;
	}

	friend Point operator+(const Point&, const Point&);
	friend Point operator-(const Point&, const Point&);

private:
	double x1;
	double x2;

	//_Point() { x1 = 0; x2 = 0; }
};
//typedef std::vector<Point> * DataSet;

//DataSet __dataSet__ loadDataSet(const std::string & fpath , const DataSet & dataSet);

//void loadDataSet(const std::string & fpath, const std::vector<Point> & dataSet);

Point operator +(const Point & p1, const Point & p2) {
	return Point(p1.x1 + p2.x1, p1.x2 + p2.x2);
}
Point operator +(const Point & p1, const Point & p2) {
	return Point(p1.x1 - p2.x1, p1.x2 - p2.x2);
}*/

void hello();
#endif // !__k_means__

