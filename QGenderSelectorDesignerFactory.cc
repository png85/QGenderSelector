#include <QDebug>
#include <QMessageBox>
#include <QtPlugin>

#ifndef HAS_CXX11_NULLPTR
#define nullptr 0
#endif

#include "QGenderSelector.h"
#include "QGenderSelectorDesignerFactory.h"

QGenderSelectorDesignerFactory::QGenderSelectorDesignerFactory(QObject *parent) :
    QObject(parent)
{
    // ... nothing ...
}


QWidget* QGenderSelectorDesignerFactory::createWidget(QWidget *parent) {
    QGenderSelector* widget = nullptr;
    try {
        widget = new QGenderSelector(parent);
    }

    catch (std::bad_alloc& ex) {
        QString msg = tr("Failed to allocate memory for new QGenderSelector instance in %1: %2").arg(Q_FUNC_INFO, ex.what());
        qCritical() << msg;
        QMessageBox::critical(parent, tr("Out of memory"), msg, QMessageBox::Ok);
        throw;
    }

    return reinterpret_cast<QWidget*>(widget);
}


QString QGenderSelectorDesignerFactory::group() const {
    return "#das-system";
}


QIcon QGenderSelectorDesignerFactory::icon() const {
    return QIcon::fromTheme("input-mouse");
}


QString QGenderSelectorDesignerFactory::includeFile() const {
    return "QGenderSelector.h";
}


QString QGenderSelectorDesignerFactory::toolTip() const {
    return tr("Radio button group for gender selection");
}


QString QGenderSelectorDesignerFactory::whatsThis() const {
    return tr("Radio button group for gender selection");
}


bool QGenderSelectorDesignerFactory::isContainer() const {
    return false;
}


QString QGenderSelectorDesignerFactory::name() const {
    return "QGenderSelector";
}


Q_EXPORT_PLUGIN2(QGenderSelectorDesignerPlugin, QGenderSelectorDesignerFactory)
