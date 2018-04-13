#include "kmeans.hpp"

/*  support functions */

void hello()
{
	std::cout << "hello" << std::endl;
}

/**
template<typename T>
std::vector<T> split(const std::string & line) {
	std::istringstream is(line);
	return std::vector<T>(std::istream_iterator<T>(is), std::istream_iterator<T>());
}

void loadDataSet(const std::string & fpath, std::vector<Point> & dataSet)
{
	//read datafile
	//vector<Point> dataSet;
	Point p;
	p.x1 = 0; p.x2 = 0;
	std::string str1, str2;
	std::ifstream datafile(fpath);
	std::string line;
	if (datafile) // txt file exist
	{
		while (std::getline(datafile, line))
		{
			//cout << line << endl;
			//char * str = line.c_str();
			//sscanf(str, "%lf\t%lf", p.x1, p.x2); //?? cpp implements
			std::vector<double> vec = split<double>(line);
			p.x1 = vec[0];
			p.x2 = vec[1];
			dataSet.push_back(p);
			
		}
	}
	assert(dataSet.size() != 0);
}
*/