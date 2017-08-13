#include<iostream>
using namespace std;
int main()
{
    double i = 1.0;
    const double &r =  i;
    double &ii = i;
    const double &C = r*2;
    const double &S = i*i*2;
    

    cout << "r = " <<r<< " rr = " <<ii<<" C = "<<C<<" S = "<<S<< endl;
    i++;cout << "r = " <<r<< " rr = " <<ii<<" C = "<<C<<" S = "<<S<< endl;
    i++;cout << "r = " <<r<< " rr = " <<ii<<" C = "<<C<<" S = "<<S<< endl;
    i++;cout << "r = " <<r<< " rr = " <<ii<<" C = "<<C<<" S = "<<S<< endl;
    
    //point of reference
    double const *tptr = &r;
    cout << "point of i via reference r "<<  (*tptr) << endl;

    //point of tmpvarible
    double const *sao = &C;
    cout << "point of C "<<  (*sao) << endl;
    //(*sao)++; cout << "point of C "<<  (*sao) << endl; // read-only

    //reference of point
    double *iptr = &i;
    double *&iref = iptr;
    (*iref)++;
    cout << "now *tptr = " << *iptr << " pref = " << *iref << endl;

    return 0;
}
