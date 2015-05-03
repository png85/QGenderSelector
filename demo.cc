#include "QGenderSelector.h"

#include <iostream>
#include <memory>
#include <QApplication>


int main(int argc, char** argv)
{
    QApplication a(argc, argv);

    Q_INIT_RESOURCE(QGenderSelector);

    QGenderSelector* g = new QGenderSelector();
    g->show();

    return a.exec();
}
