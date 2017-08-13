/*************************************************************************
	> File Name: Sales_data.h
	> Author: 
	> Mail: 
	> Created Time: 2017年08月07日 星期一 17时25分12秒
 ************************************************************************/

#ifndef _SALES_DATA_H
#define _SALES_DATA_H
#include <string>
struct Sales_data {
    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
}
#endif //_SALES_DATA_H
