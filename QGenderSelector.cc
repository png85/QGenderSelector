#include <QDebug>

#ifndef HAS_CXX11_NULLPTR
#define nullptr 0
#endif

#include "QGenderSelector.h"

QGenderSelector::QGenderSelector(QWidget *parent) :
    QFrame(parent),
    m_orientation(Qt::Horizontal),
    m_layout(nullptr),
    m_radioMale(nullptr), m_radioFemale(nullptr), m_radioOther(nullptr)
{
    qRegisterMetaType<Gender>("QGenderSelector::Gender");
    setupUi();
}


void QGenderSelector::setOrientation(Qt::Orientation o) {
    if (m_orientation == o)
        return;

    setupUi();
    m_orientation = o;
}


void QGenderSelector::setupUi() {
    QLayout* layoutBackup = m_layout;
    QList<QRadioButton*> radioBackup = QList<QRadioButton*>() << m_radioMale << m_radioFemale << m_radioOther;

    try {
        switch (m_orientation) {
        case Qt::Horizontal:
            m_layout = new QHBoxLayout(this);
            break;

        case Qt::Vertical:
            m_layout = new QVBoxLayout(this);
            break;
        }
    }

    catch (std::bad_alloc& ex) {
        qCritical() << "Caught exception when trying to create new QBoxLayout in" << Q_FUNC_INFO << ":" << ex.what();
        throw;
    }

    try {
        m_buttonGroup = new QButtonGroup(m_layout);
    }

    catch (std::bad_alloc& ex) {
        qCritical() << "Caught exception when trying to create new QButtonGroup in " << Q_FUNC_INFO << ":" << ex.what();
        throw;
    }

    QList<QRadioButton*> radioButtons;
    try {
        m_radioMale = new QRadioButton(tr("Male"), this);
        m_radioMale->setIcon(QIcon(":/icons/genders/male.png"));

        m_radioFemale = new QRadioButton(tr("Female"), this);
        m_radioFemale->setIcon(QIcon(":/icons/genders/female.png"));

        m_radioOther = new QRadioButton(tr("Other"), this);
        m_radioOther->setIcon(QIcon(":/icons/genders/other.png"));
    }

    catch (std::bad_alloc& ex) {
        qCritical() << "Caught exception when trying to create new QRadioButton in " << Q_FUNC_INFO << ":" << ex.what();
        throw;
    }

    radioButtons << m_radioMale << m_radioFemale << m_radioOther;
    foreach (QRadioButton* button, radioButtons) {
        m_layout->addWidget(button);
        m_buttonGroup->addButton(button);
    }

    connect(m_buttonGroup, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(buttonGroup_buttonClicked(QAbstractButton*)));

    QFrame::setLayout(m_layout);

    if (layoutBackup != nullptr)
        delete layoutBackup;

    foreach (QRadioButton* button, radioBackup)
        if (button != nullptr)
            delete button;
}


void QGenderSelector::buttonGroup_buttonClicked(QAbstractButton* button) {
    if (button == m_radioMale) {
        m_selectedGender = Male;
    } else if (button == m_radioFemale) {
        m_selectedGender = Female;
    } else {
        m_selectedGender = Other;
    }

    emit selectedGenderChanged(m_selectedGender);
    emit selectedGenderChanged(genderToDicomVR(m_selectedGender));
}


void QGenderSelector::setSelectedGender(QGenderSelector::Gender g) {
    m_selectedGender = g;
    switch (g) {
    case Male:
        m_radioMale->setChecked(true);
        m_radioFemale->setChecked(false);
        m_radioOther->setChecked(false);
        break;

    case Female:
        m_radioMale->setChecked(false);
        m_radioFemale->setChecked(true);
        m_radioOther->setChecked(false);
        break;

    case Other:
    default:
        m_radioMale->setChecked(false);
        m_radioFemale->setChecked(false);
        m_radioOther->setChecked(true);
        break;
    }
}
