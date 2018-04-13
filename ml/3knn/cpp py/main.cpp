#include <iostream>
#include <string>
#include <fstream>

#include <cstdio>
#include <cassert> // #include <assert.h>
//#include "kmeans.hpp"

#include <sstream>
#include <iterator>
#include <stdlib.h>
#include <cmath>

#include <algorithm>

#include <vector>

#include <assert.h>

#include <limits>


#include <omp.h>

#include <time.h>

#include <opencv2\opencv.hpp>

#define DEBUG
//#undef DEBUG

typedef struct _myPoint{
	double x1;
	double x2;
/*public:
	struct _myPoint myPoint(double, double);*/
}myPoint;

/*myPoint myPoint::myPoint(double xx1, double xx2) {
	
	x1 = xx1; x2 = xx2;
	
}*/

typedef struct _result{
	int type;
	double r;
//public:
	//struct _result::result(const int & , const double &);

}result;
/*
result result::result(const int & tt = -1, const double & rr = 0.0F) {
	type = tt; r = rr;
}*/

using namespace std;
using namespace cv;

//DATA SEGMENT
const double _INF_ = std::numeric_limits<double>::infinity();
//DATA SEGMENT END

//PROG SEGMENT
template<typename T>
std::vector<T> split(const std::string & line) {
	std::istringstream is(line);
	return std::vector<T>(std::istream_iterator<T>(is), std::istream_iterator<T>());
}

void loadDataSet(const std::string & fpath, std::vector<myPoint> & dataSet);
double distance_Eculd(myPoint p1, myPoint p2);
void randCent(const std::vector<myPoint> & dataSet, const int k, std::vector<myPoint> & centroids); //std::vector<myPoint> *  randCent(std::vector<myPoint> & dataSet, const int k)

void  _kMeans(
	const std::vector<myPoint> & dataSet,
	const int k,
	std::vector<myPoint> & Centroids,
	std::vector<result> & clustAssing,

	double(*distMeas)(myPoint , myPoint ),
	void(*createCent)(const std::vector<myPoint> & , const int , std::vector<myPoint> & )
);
void  _kMeans_vector(
	const std::vector<vector<double>> & dataSet,
	const int k,
	std::vector<vector<double>> & Centroids,
	std::vector<result> & clustAssing,

	double(*distMeas)(vector<double>, vector<double>),
	void(*createCent)(const std::vector<vector<double>> &, const int, std::vector<vector<double>> &)
);
void Display(vector<myPoint> & list);
void Display(vector<double> & list);
void Display(vector<result> & list);
void Display(vector<vector<double>> & list);
void Save(vector<result> &, std::string & );
void  _kMeans_para(
	const std::vector<myPoint> & dataSet,
	const int k,
	std::vector<myPoint> & Centroids,
	std::vector<result> & clustAssing,

	double(*distMeas)(myPoint, myPoint),
	void(*createCent)(const std::vector<myPoint> &, const int, std::vector<myPoint> &)
);
void loadDataSet_ini_1(const std::string & fpath, std::vector<myPoint> & dataSet);
//void loadDataSet_img(const std::string & imgpath, std::vector<myPoint> & dataSet);
void loadDataSet_img(const std::string & imgpath);
void loadDataSet_img_r_i(const std::string & imgpath, std::vector<myPoint> & dataSet);
void DisPlayImg(const std::string & imgpath, std::vector<result>& ans);
void loadDataSet_vector(const std::string & imgpath, std::vector<vector<double>> & dataSet);
double distance_Eculd(vector<double> p1, vector<double> p2);
void randCent_vector(const std::vector<vector<double>> & dataSet, const int k, std::vector<vector<double>> & centroids);
void loadDataSet(const std::string & fpath, std::vector<vector<double>> & dataSet);
//PROG SEGMENT END

void run_points();


int main(int argc,char* argv[])
{
	system("echo points");
	//run_points();

	system("echo img");
	//system("pause");

	//set #core
	const int core = 4;

	// load dataSet
	cout << "data set loaded" << endl;
	std::vector<vector<double>> dataSet;
	loadDataSet_vector("IMG.jpg", dataSet);
	//loadDataSet("testSet.txt", dataSet);

	
	// data set gotten
	cout << "data set gotten" << endl;
	std::vector<vector<double>> centroids;
	//randCent_vector(dataSet, core, centroids);
	//Display(centroids);

	//run
	cout << "running" << endl;
	vector<result> ans_ser;
	_kMeans_vector(dataSet, core, centroids, ans_ser, distance_Eculd, randCent_vector);

	cout << "result\n" << endl;
	Display(ans_ser);


#ifdef DEBUG
	system("pause");
#endif // DEBUG



    
    return 0;
}

void run_points()
{


	/* load dataset */
	std::vector<myPoint> dataSet;
	loadDataSet("testSet.txt", dataSet);
	//loadDataSet_ini_1("unbalance.txt", dataSet);


	const int core = 4;

	/* data set gotten */

	std::vector<myPoint> centroids; //initial clustering 
	randCent(dataSet, core, centroids);
	std::vector<myPoint> centroids_p(centroids);
	Display(centroids);
	vector<result> ans_ser, ans_par;
	clock_t start, end;


	/*  run  */
	std::cout << "# 1. serial #" << std::endl;
	start = clock();
	_kMeans(dataSet, core, centroids, ans_ser, &distance_Eculd, randCent);
	end = clock();
	std::cout << "time: " << ((end - start) * 1000) / CLOCKS_PER_SEC << std::endl;

	std::cout << "\n\nserial result :" << std::endl;
	Display(ans_ser);
	std::cout << "final centroids" << std::endl;
	Display(centroids);

	std::cout << "\n\n\n# 2. parallel #" << std::endl;

#ifdef DEBUG
	//openmp support
#ifdef _OPENMP
	std::cout << "OpenMP supported" << std::endl;
#endif
#pragma omp parallel for
	for (char c = 'a'; c <= 'z'; c++)
		std::cout << c << ' ';

	std::cout << std::endl;
#endif // DEBUG
	start = clock();
	_kMeans_para(dataSet, core, centroids_p, ans_par, &distance_Eculd, randCent);
	end = clock();
	std::cout << "time: " << ((end - start) * 1000) / CLOCKS_PER_SEC << std::endl;

	std::cout << "\n\nparallel result :" << std::endl;
	Display(ans_par);
	std::cout << "final centroids" << std::endl;
	Display(centroids_p);


#ifdef DEBUG
	system("pause");
#endif // DEBUG

}

void loadDataSet(const std::string & fpath, std::vector<vector<double>> & dataSet)
{
	//read datafile
	std::ifstream datafile(fpath);
	std::string line;
	vector<double> tmpp;
	if (datafile) // txt file exist
	{
		//int cnt = 0;
		while (std::getline(datafile, line))
		{
			std::vector<double> vec = split<double>(line);
			dataSet.push_back(vec);
			
			//dataSet.at(cnt).at(0) = vec[0]; dataSet.at(cnt).at(0) = vec[1];
			
			//dataSet[cnt].push_back(vec[0]);
			//dataSet[cnt].push_back(vec[1]);
			//cnt++;
			
		}
	}
	assert(dataSet.size() != 0);
}

void  _kMeans_vector(
	const std::vector<vector<double>> & dataSet,
	const int k,
	std::vector<vector<double>> & Centroids,
	std::vector<result> & clustAssing,

	double(*distMeas)(vector<double>, vector<double>),
	void(*createCent)(const std::vector<vector<double>> &, const int, std::vector<vector<double>> &)
)
{

	/*
	_kMeans vv


	*/
	//initilization	
	int	dim = dataSet.size(); //#myPoints

#ifdef DEBUG
	cout << "DEBUG INFO : FUNCTION _kMeans_vector VARIABLE dataSet.size() "<< dim << ", "<< dataSet.size() << endl;
#endif // DEBUG

	clustAssing.assign(dim, { -1,0.0 }); //	Display(clustAssing);


	bool clusterChanged = true;
	(*createCent)(dataSet, k, Centroids); //inital random myPoints

	while (true == clusterChanged)
	{
		clusterChanged = false;
		//for each myPoint in dataSet assign it to closest certroid  #80
		for (int i = 0; i < dim; i++)
		{
			double minDist = _INF_;	int typeKey = -1;
			for (int j = 0; j < k; j++)
			{
				assert(Centroids[j].size() == dataSet[i].size());
				double distJI = (*distMeas)(Centroids[j], dataSet[i]);
				if (distJI < minDist)
				{
					minDist = distJI; typeKey = j;
				}
			}
			if (clustAssing[i].type != typeKey)
			{
				clusterChanged = true;
			}
			clustAssing[i].type = typeKey; clustAssing[i].r = pow(minDist, 2);
		}//for each myPoint in dataSet 

		 //display Centroids  in serial
		Display(Centroids);
		//recalculate centroids
		for (int typeKey = 0; typeKey < k; typeKey++)	//each time process 
		{		
			
			int cnt = 0;
			//proc ansP
			for (int i = 0; i < dataSet.size(); i++)
			{
				if (typeKey == clustAssing[i].type)
				{
					cnt++;

					for (int j = 0; j < dataSet[0].size(); j++)
					{
						Centroids[typeKey][j] += dataSet[i][j];
					}					
				}
			}
			for (int i = 0; i < dataSet[0].size(); i++)
			{
				Centroids[typeKey][i] /= (double)cnt;
			}
			;
		}
		;
	}

}

void loadDataSet_img(const std::string & imgpath)
{
	cv::Mat img = imread(imgpath);
	if (img.data)
	{
		imshow("hh", img);
		waitKey(300);
		//one dim sample points 
		cv::Mat samples(img.cols*img.rows, 1, CV_32FC3);
		//labels
		cv::Mat labels(img.cols*img.rows, 1, CV_32FC1);
		
		uchar * op;
		int  k = 0;
		for (int i = 0; i < img.rows; i++)
		{
			op = img.ptr<uchar>(i);
			for (int j = 0; j < img.cols; j++)
			{
				samples.at<Vec3f>(k, 0)[0] = float(op[j * 3]);
				samples.at<Vec3f>(k, 0)[1] = float(op[j * 3+1]);
				samples.at<Vec3f>(k, 0)[2] = float(op[j * 3+2]);
			}
		}
		int clusterCount = 8;
		Mat centers(clusterCount, 1, samples.type());
		kmeans(samples, clusterCount, labels,
			TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 10, 1.0),
			3, KMEANS_PP_CENTERS, centers);
		Mat img1(img.rows, img.cols, CV_8UC1);
		float step = 255 / (clusterCount - 1);
		k = 0;
		for (int i = 0; i < img1.rows; i++)
		{
			op = img1.ptr<uchar>(i);
			for (int j = 0; j< img1.cols; j++)
			{
				int tt = labels.at<int>(k, 0);
				cout << tt << endl;
				k++;
				op[j] = 255 - tt*step;
			}
		}
		imshow("lab", labels);
		namedWindow("image1");
		imshow("image1", img1);

		waitKey();

		system("pause");
	}

}
void loadDataSet_img_r_i(const std::string & imgpath, std::vector<myPoint>& dataSet)
{
	cv::Mat img = imread(imgpath);
	int feature_dim = 2;
	myPoint tmp;
	uchar * op;
	
	for (int i = 0; i < img.rows; i++)
	{
		op = img.ptr<uchar>(i);
		for (int j = 0; j < img.cols; j++)
		{
			tmp.x1 = float(op[j * 3]);
			tmp.x2 = float(op[j * 3 + 1]);
			//

			dataSet.push_back(tmp);
		}
	}

}
void loadDataSet_vector(const std::string & imgpath, std::vector<vector<double>> & dataSet)
{
	//dataSet mn * feature_dim

	cv::Mat img = cv::imread(imgpath, CV_LOAD_IMAGE_COLOR);
	assert(img.data);
	
	//std::cout << img.channels() << std::endl;
	if (1 == img.channels()) //GRAY LEVEL
	{
		//doing nothing
		;
	}
	else if (3 == img.channels()) //COLOR LEVEL
	{
		//mn * k
		dataSet.resize(img.rows*img.cols); //mn
		//dataSet[0].resize(img.channels()); //k

		for (int j = 0; j < img.cols; j++)		//
		{
			for (int i = 0; i < img.rows; i++)	//
			{
				dataSet[j*img.cols + i].resize(img.channels());
				for (int k = 0; k < img.channels(); k++)
				{
					dataSet[j*img.cols + i][k] = img.at<cv::Vec3b>(i, j)[k];

					//cout << "dataSet[j*img.cols + i][k] " << dataSet[j*img.cols + i][k] << "img.at<cv::Vec3b>(i, j)[k]" << img.at<cv::Vec3b>(i, j)[k] << endl;


				}
			}
		}
#ifdef DEBUG
		cout << "DEBUG INFO: FUNCTION loadDataSet_vector EVENT dataSet.size(): " << dataSet.size() << endl;
		cout << "DEBUG INFO: FUNCTION loadDataSet_vector EVENT img.cols: " << img.cols << endl;
		cout << "DEBUG INFO: FUNCTION loadDataSet_vector EVENT img.rows: " << img.rows << endl;
#endif // DEBUG

	}//channels 3
	
}
/*
void DisPlayImg(const std::string & imgpath, std::vector<result>& ans)
{
	unsigned char  colorTab[] =
	{
		0,50,100,150,200,250
	};

	cv::Mat img = imread(imgpath);
	//Mat ansp(img.rows, img.cols, CV_8UC1);
	unsigned char ansss[img.cols][img.rows] = {0};
	if (img.cols*img.rows == ans.size())
	{
		for (int i = 0; i < img.cols; i++)
		{
			for (int j = 0; j < img.rows; j++)
			{
				//ansp[i][j] = colorTab[ans[i*img.cols + j].type];
				//ansp.at<CV_8UC3>(i, j) = colorTab[ans[i*img.cols+j].type];
				//ansp.at<uchar>(i, j) = colorTab[ans[i*img.cols + j].type];
				ansss[i][j] = colorTab[ans[i*img.cols + j].type];
				
			}
		}
		Mat ansp(img.rows, img.cols, CV_8UC1,ansss);
		imshow("anssss", ansp);
	}
}
*/

void loadDataSet_ini_1(const std::string & fpath, std::vector<myPoint> & dataSet)
{
	//read datafile
	//vector<myPoint> dataSet;
	myPoint p;
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
			std::vector<int> vec = split<int>(line);
			p.x1 = vec[0] / 10000.0;
			p.x2 = vec[1] / 10000.0;
			dataSet.push_back(p);

		}
	}
	assert(dataSet.size() != 0);
}




void  _kMeans_para(
	const std::vector<myPoint> & dataSet,
	const int k,
	std::vector<myPoint> & Centroids,
	std::vector<result> & clustAssing,

	double(*distMeas)(myPoint, myPoint),
	void(*createCent)(const std::vector<myPoint> &, const int, std::vector<myPoint> &)
)
{

	/*
	_kMeans in parallel
	input :
	std::vector<myPoint> & dataSet
	const int k
	double(*distMeas)(myPoint p1, myPoint p2)
	void(*createCent)(std::vector<myPoint> & dataSet, const int k, std::vector<myPoint> & centroids)
	output :
	std::vector<myPoint> & Centroids
	vector<result> & clustAssing

	*/


	//initilization	
	auto dim = dataSet.size(); //#myPoints
	clustAssing.assign(dim, { -1,0.0 }); //Display(clustAssing);


	bool clusterChanged = true;
	(*createCent)(dataSet, k, Centroids); //inital random myPoints

	while (true == clusterChanged)
	{
		clusterChanged = false;
		//for each myPoint in dataSet assign it to closest certroid  #80		
		#pragma omp parallel for		
			for (int i = 0; i < dim; i++)							/* fork */
			{
				double minDist = _INF_;	int typeKey = -1;
				for (int j = 0; j < k; j++)
				{
					double distJI = (*distMeas)(Centroids[j], dataSet[i]);
					if (distJI < minDist)
					{
						minDist = distJI; typeKey = j;
					}
				}
				if (clustAssing[i].type != typeKey)
				{
					clusterChanged = true;
				}
				clustAssing[i].type = typeKey; clustAssing[i].r = pow(minDist, 2);
			}//for each myPoint in dataSet							/* join */			

		 //display Centroids  in serial
		Display(Centroids);
		//recalculate centroids

		#pragma omp parallel for
		for (int typeKey = 0; typeKey < k; typeKey++)	//each time process 
		{
			myPoint ansP; ansP.x1 = 0.0; ansP.x2 = 0.0;
			double sumx1 = 0.0, sumx2 = 0.0; //make sure its value no larger than sizeof(double)
			int cnt = 0;
			//proc ansP
			for (int i = 0; i < dataSet.size(); i++)
			{
				if (typeKey == clustAssing[i].type)
				{
					cnt++;
					sumx1 += dataSet[i].x1;
					sumx2 += dataSet[i].x2;
				}
			}
			ansP.x1 = sumx1 / (double)cnt;	ansP.x2 = sumx2 / (double)cnt;
			Centroids[typeKey].x1 = ansP.x1; Centroids[typeKey].x2 = ansP.x2;
		}


	}

}



void Display(vector<myPoint> & list) {
	for each (myPoint var in list)
	{
		std::cout << var.x1 << '\t' << var.x2 << '\n';
	}
	std::cout << "\n\n" << std::endl;
}

void Display(vector<double> & list) {
	for each (double var in list)
	{
		std::cout << var << '\n';
	}
	std::cout << "\n\n" << std::endl;
}
void Display(vector<vector<double>> & list) {
	for each (vector<double> var in list)
	{
		for each (double item in var)
		{
			std::cout << item << "\t";
		}
		std::cout << std::endl;
	}
	std::cout << "\n\n" << std::endl;
}
void Display(vector<result> & list) {
	for each (result var in list)
	{
		std::cout << var.type << '\t' << var.r << '\n';
	}
	std::cout << "\n\n" << std::endl;
}

void Save(vector<result> & list, std::string & fpath) {
	ofstream out(fpath);	
	for each (result var in list)
	{
		out << var.type << '\t' << var.r << '\n';
	}
	out << std::endl;	
}



void  _kMeans(
	const std::vector<myPoint> & dataSet,
	const int k,
	std::vector<myPoint> & Centroids,
	std::vector<result> & clustAssing,

	double(*distMeas)(myPoint, myPoint),
	void(*createCent)(const std::vector<myPoint> &, const int, std::vector<myPoint> &)
)
{
	
	/*
		_kMeans in serial
		input : 
			std::vector<myPoint> & dataSet
			const int k
			double(*distMeas)(myPoint p1, myPoint p2)
			void(*createCent)(std::vector<myPoint> & dataSet, const int k, std::vector<myPoint> & centroids)
		output :
			std::vector<myPoint> & Centroids
			vector<result> & clustAssing
		
	*/
	//initilization	
	auto dim = dataSet.size(); //#myPoints
	clustAssing.assign(dim, { -1,0.0 }); //	Display(clustAssing);
	

	bool clusterChanged = true;
	(*createCent)(dataSet, k, Centroids); //inital random myPoints
		
	while (true == clusterChanged)
	{
		clusterChanged = false;
		//for each myPoint in dataSet assign it to closest certroid  #80
		for (int i = 0; i < dim; i++) 
		{
			double minDist = _INF_;	int typeKey = -1;
			for (int j = 0; j < k; j++)
			{
				double distJI = (*distMeas)(Centroids[j], dataSet[i]);
				if (distJI < minDist)
				{
					minDist = distJI; typeKey = j;
				}
			}
			if (clustAssing[i].type != typeKey)
			{
				clusterChanged = true;
			}
			clustAssing[i].type = typeKey; clustAssing[i].r = pow(minDist, 2);
		}//for each myPoint in dataSet
		
		 //display Centroids  in serial
		Display(Centroids);
		//recalculate centroids
		for (int typeKey = 0; typeKey < k; typeKey++)	//each time process 
		{
			myPoint ansP; ansP.x1 = 0.0; ansP.x2 = 0.0;
			double sumx1 = 0.0, sumx2 = 0.0; //make sure its value no larger than sizeof(double)
			int cnt = 0;
			//proc ansP
			for (int i = 0; i < dataSet.size(); i++)
			{
				if (typeKey == clustAssing[i].type)
				{
					cnt++;
					sumx1 += dataSet[i].x1;
					sumx2 += dataSet[i].x2;
				}
			}
			ansP.x1 = sumx1 / (double)cnt;	ansP.x2 = sumx2 / (double)cnt;
			Centroids[typeKey].x1 = ansP.x1; Centroids[typeKey].x2 = ansP.x2;
		}
	}

}



void loadDataSet(const std::string & fpath, std::vector<myPoint> & dataSet)
{
	//read datafile
	//vector<myPoint> dataSet;
	myPoint p;
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
double distance_Eculd(myPoint p1, myPoint p2)
{
	return sqrt(pow(p1.x1 - p2.x1, 2) + pow(p1.x2 - p2.x2, 2));
}
double distance_Eculd(vector<double> p1, vector<double> p2)
{
	//sqrt( sigma_i( power(p1[i] - p2[i], 2)/n )*n ) 
	double ans = 0;

	try
	{
		//assert(p1.size() == p2.size()); 断言移动到kmeans中
		for (int i = 0; i < p1.size(); i++)
		{
			ans += pow(p1[i] - p2[i], 2) / p1.size();
		} 
	}
	catch (const std::exception& e)
	{
		cout << "p1.size()==" << p1.size() << "\np2.size()" << p2.size() << endl;
		cout << e.what() << endl;		
	}

	return sqrt(ans)*sqrt(p1.size());
}


void randCent(const std::vector<myPoint> & dataSet, const int k, std::vector<myPoint> & centroids)
{
	//const int dim = 2;//# dim of myPoint
	//double x[k][dim];
	myPoint p;

	std::vector<double> tmpx1;
	std::vector<double> tmpx2;
	for each (myPoint var in dataSet)
	{
		tmpx1.push_back(var.x1);
		tmpx2.push_back(var.x2);
	}
	std::vector<double>::iterator max_x1 = std::max_element(std::begin(tmpx1), std::end(tmpx1));
	std::vector<double>::iterator min_x1 = std::min_element(std::begin(tmpx1), std::end(tmpx1));
	std::vector<double>::iterator max_x2 = std::max_element(std::begin(tmpx2), std::end(tmpx2));
	std::vector<double>::iterator min_x2 = std::min_element(std::begin(tmpx2), std::end(tmpx2));

	double range_x1 = *max_x1 - *min_x1;
	double range_x2 = *max_x2 - *min_x2;

	//cout << *min_x1 << " "<< *min_x2 <<	" " << range_x1 <<	" " << range_x2 << endl;
	for (int i = 0; i < k; i++)
	{
		p.x1 = *min_x1 + range_x1 * ((double)(rand() % 500 + 1) / 500.0);
		p.x2 = *min_x1 + range_x2 * ((double)(rand() % 500 + 1) / 500.0);
		centroids.push_back(p);
	}

	assert(centroids.size() != 0);
}
void randCent_vector(const std::vector<vector<double>> & dataSet, const int k, std::vector<vector<double>> & centroids)
{
	//dataSet 数据集 mn * dim
	//centroids 质心  k * dim
	

	//

	int dataVolume = dataSet.size();						//size of data
	int dataDim = dataSet[0].size();						//dim of data
	for (int cnt_k = 0; cnt_k < k; cnt_k++)					//k type
	{
		int randIndex = dataVolume * (rand() % 500) / 500;	//rand point in data set
		//std::vector<double> & tmpx = dataSet[randIndex];
		centroids.push_back(dataSet[randIndex]);
		//for (int i = 0; i < dataDim; i++)	{	//centroids[cnt_k].push_back(dataSet[randIndex][i]); wrong	}

	}//for (int cnt_k = 0; cnt_k < k; cnt_k++)
	

	assert(centroids.size() != 0);
}

