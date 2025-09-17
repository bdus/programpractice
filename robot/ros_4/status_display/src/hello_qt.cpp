#include <QApplication>
#include <QLabel>
#include <QString>


int main(int argc, char * argv[])
{
    QApplication app(argc, argv);
    QLabel* lable  = new QLabel();
    QString message = QString::fromStdString("Hello Qt");
    lable->setText(message);
    lable->show();
    app.exec();

    return 0;
}