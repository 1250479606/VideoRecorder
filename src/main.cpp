
/**
 * Ҷ����
 * QQȺ121376426
 * http://blog.yundiantech.com/
 */

#include "mainwindow.h"
#include <QApplication>

#include <QTextCodec>

#undef main

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec *codec = QTextCodec::codecForName("GBK"); //��ȡϵͳ����
    QTextCodec::setCodecForLocale(codec);

    MainWindow w;

    //�ڶ�������Ϊ¼���ļ���·��
    if (argc >= 2)
    {
        QString str = QString(argv[1]);
        w.setSaveFile(str);
    }

    return a.exec();
}
