#include <QDebug>
#include <QMessageBox>
#include <QtPlugin>

#ifndef HAS_CXX11_NULLPTR
#define nullptr 0
#endif

#include "QGenderSelector.h"
#include "QGenderSelectorDesignerFactory.h"


/**
 * @brief Default constructor
 *
 * Registers meta types and initialies the icon resources for QGenderSelector so that
 * its icons get shown properly in Qt Designer.
 *
 * @param parent Parent object that owns the newly created instance
 */
QGenderSelectorDesignerFactory::QGenderSelectorDesignerFactory(QObject *parent) :
    QObject(parent)
{
    Q_INIT_RESOURCE(QGenderSelector);
    qRegisterMetaType<QGenderSelector::Gender>("QGenderSelector::Gender");
}


/**
 * @brief Create new QGenderSelector instance
 * @param parent Parent widget of the newly created QGenderSelector instance
 * @return New QGenderSelector instance
 */
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


/**
 * @brief Widget group name
 * @return Name of the group under which the widget shall show up in Qt Designer
 */
QString QGenderSelectorDesignerFactory::group() const {
    return "#das-system";
}


/**
 * @brief Widget icon
 * @return Icon to show in Qt Designer's widget list
 */
QIcon QGenderSelectorDesignerFactory::icon() const {
    return QIcon::fromTheme("input-mouse");
}


/**
 * @brief Header name for Qt Designer
 * @return Name of C++ header to include for our widget
 */
QString QGenderSelectorDesignerFactory::includeFile() const {
    return "QGenderSelector.h";
}


/**
 * @brief Tooltip text
 * @return Tooltip text that is shown for our widget
 */
QString QGenderSelectorDesignerFactory::toolTip() const {
    return tr("Radio button group for gender selection");
}


/**
 * @brief "What's this?" description
 * @return Descriptive text for "What's this?"
 */
QString QGenderSelectorDesignerFactory::whatsThis() const {
    return tr("Radio button group for gender selection");
}


/**
 * @brief Is our widget a container?
 * @return Boolean flag indicating wether our widget is a container (false)
 */
bool QGenderSelectorDesignerFactory::isContainer() const {
    return false;
}


/**
 * @brief Widget name
 * @return Name of our widget that is shown in Qt Designer's widget list
 */
QString QGenderSelectorDesignerFactory::name() const {
    return "QGenderSelector";
}


Q_EXPORT_PLUGIN2(QGenderSelectorDesignerPlugin, QGenderSelectorDesignerFactory)
