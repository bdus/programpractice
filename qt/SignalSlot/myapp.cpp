#include "myapp.h"

myApp* myApp::m_pInstance = new myApp;
myApp::myApp() //(QObject *parent) : QObject(parent)
{
    this->str = "nothing";
}
//myApp::myApp(QObject *parent) : QObject(parent)
//{

//}

//myApp::~myApp()
//{
//    delete(m_pInstance);
//}
