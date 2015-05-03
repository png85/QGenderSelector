#include "QGenderSelector.h"

#include <iostream>
#include <memory>
#include <QApplication>


int main(int argc, char** argv)
{
    QApplication a(argc, argv);

    QGenderSelector_initResources();

    try {
        std::unique_ptr<QGenderSelector> g(new QGenderSelector());
        g->show();

        return a.exec();
    }

    catch (std::bad_alloc& ex) {
        std::cerr << "Failed to allocate memory for QGenderSelector: " << ex.what() << std::endl;
        return EXIT_FAILURE;
    }
}
