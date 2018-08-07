#ifndef MYAPP_H
#define MYAPP_H

#include <QObject>
#include <QString>

class myApp : public QObject
{
    Q_OBJECT
public:

    static myApp * getInstance()
    {
        return m_pInstance;
    }
    static void Release()
    {
        if (m_pInstance != NULL)
        {
            delete m_pInstance;
            m_pInstance = NULL;
        }
    }


    //data
    QString str;

//    ~myApp();
private:
    myApp();
    myApp(const myApp&) {}
    myApp& operator ==(const myApp&) {}

private:
    static myApp* m_pInstance;


};

#endif // MYAPP_H

