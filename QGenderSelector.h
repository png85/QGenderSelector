#ifndef QGENDERSELECTOR_H
#define QGENDERSELECTOR_H

#include <QFrame>
#include <QBoxLayout>
#include <QButtonGroup>
#include <QRadioButton>

class QGenderSelector : public QFrame
{
    Q_OBJECT

    Q_PROPERTY(Qt::Orientation orientation READ getOrientation WRITE setOrientation)
    Q_PROPERTY(Gender selectedGender READ getSelectedGender WRITE setSelectedGender)

public:
    explicit QGenderSelector(QWidget *parent = 0);
    
    Qt::Orientation getOrientation() const { return m_orientation; }

    enum Gender {
        Male=0x0, Female=0x1, Other=0x2
    };

    Gender getSelectedGender() const { return m_selectedGender; }

    static QString genderToDicomVR(Gender g) {
        switch (g) {
        case Male:
            return "M";

        case Female:
            return "F";

        case Other:
        default:
            return "O";
        }
    }

private:
    Qt::Orientation m_orientation;

    QBoxLayout* m_layout;

    QRadioButton* m_radioMale;
    QRadioButton* m_radioFemale;
    QRadioButton* m_radioOther;

    QButtonGroup* m_buttonGroup;

    void setupUi();

    Gender m_selectedGender;

signals:
    void selectedGenderChanged(QGenderSelector::Gender);
    void selectedGenderChanged(QString);

public slots:
    void setOrientation(Qt::Orientation o);
    void setSelectedGender(QGenderSelector::Gender g);


private slots:
    void buttonGroup_buttonClicked(QAbstractButton*);
};

#endif // QGENDERSELECTOR_H
