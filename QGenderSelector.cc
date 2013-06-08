#include <QDebug>

#ifndef HAS_CXX11_NULLPTR
#define nullptr 0
#endif

#include "QGenderSelector.h"

QGenderSelector::QGenderSelector(QWidget *parent) :
    QFrame(parent),
    m_orientation(Qt::Horizontal),
    m_layout(nullptr),
    m_radioMale(nullptr), m_radioFemale(nullptr), m_radioOther(nullptr),
    m_selectedGender(Other)
{
    qRegisterMetaType<Gender>("QGenderSelector::Gender");
    setupUi();
    setSelectedGender(m_selectedGender);
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
        QString msg = tr("Failed to allocate memory for new QBoxLayout in %1: %2").arg(Q_FUNC_INFO, ex.what());
        qCritical() << msg;
        throw;
    }

    try {
        m_buttonGroup = new QButtonGroup(m_layout);
    }

    catch (std::bad_alloc& ex) {
        QString msg = tr("Failed to allocate memory for new QButtonGroup in %1: %2").arg(Q_FUNC_INFO, ex.what());
        qCritical() << msg;
        throw;
    }

    QList<QRadioButton*> radioButtons;
    try {
        m_radioMale = new QRadioButton(tr("Male"), this);
        m_radioMale->setIcon(QIcon(":/icons/genders/male.png"));
        m_layout->addWidget(m_radioMale);
        m_buttonGroup->addButton(m_radioMale, static_cast<int>(Male));

        m_radioFemale = new QRadioButton(tr("Female"), this);
        m_radioFemale->setIcon(QIcon(":/icons/genders/female.png"));
        m_layout->addWidget(m_radioFemale);
        m_buttonGroup->addButton(m_radioFemale, static_cast<int>(Female));

        m_radioOther = new QRadioButton(tr("Other"), this);
        m_radioOther->setIcon(QIcon(":/icons/genders/other.png"));
        m_layout->addWidget(m_radioOther);
        m_buttonGroup->addButton(m_radioOther, static_cast<int>(Other));
    }

    catch (std::bad_alloc& ex) {
        QString msg = tr("Failed to allocate memory for new QRadioButton in %1: %2").arg(Q_FUNC_INFO, ex.what());
        qCritical() << msg;
        throw;
    }

    connect(m_buttonGroup, SIGNAL(buttonClicked(int)), this, SLOT(buttonGroup_buttonClicked(int)));

    QFrame::setLayout(m_layout);

    if (layoutBackup != nullptr)
        delete layoutBackup;

    foreach (QRadioButton* button, radioBackup)
        if (button != nullptr)
            delete button;
}


void QGenderSelector::buttonGroup_buttonClicked(int id) {
    m_selectedGender = static_cast<Gender>(id);
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
