#include "mainwindow.h"

#include <QApplication>
#include "Tools/TextEditor/editor.h"
#include <iostream>
#include "Core/fundamental.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    Editor editor(&w);
    w.setCentralWidget(&editor);

    w.show();
    return a.exec();
}
