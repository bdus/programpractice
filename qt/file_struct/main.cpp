
#include <QApplication>
#include <iostream>
#include <QFile>
#include <QMessageBox>

typedef struct
{
    QString str1;
    QString str2;
}data;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();
    data ins,get;
    ins.str1 = "jhgsjhgfa";
    ins.str2 = "13245689";
    FILE * fp;
    fp = fopen("savdata.txt","w+");
    if(!fp)
        exit(-1);
    fwrite(&ins,sizeof(ins),1,fp);

    QMessageBox::information(NULL,"x","ye");

    rewind(fp);
    fread(&get,sizeof(get),1,fp);

    QMessageBox::information(NULL,"x",get.str2);
    QMessageBox::information(NULL,"x",get.str1);

    fclose(fp);

    return a.exec();
}
