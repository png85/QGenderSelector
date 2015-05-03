#ifndef QGENDERSELECTOR_H
#define QGENDERSELECTOR_H

#include <QFrame>
#include <QBoxLayout>
#include <QButtonGroup>
#include <QRadioButton>

#include <QGenderSelector_Export.h>

/**
 * @brief Gender selection widget
 *
 * This simple widget consists of a group of three radio buttons with icons and descriptions
 * that allow the user to select between male/female/other genders.
 *
 * @author Peter Hille (png!das-system) <peter@das-system-networks.de>
 *
 * @version 1.0 Initial implementation
 */
class QGenderSelector_EXPORT QGenderSelector : public QFrame {
    Q_OBJECT

    /**
     * @brief Currently selected gender
     *
     * Holds a \a Gender value that contains the gender which is currently selected in the UI.
     *
     * @see getSelectedGender
     * @see setSelectedGender
     */
    Q_PROPERTY(QGenderSelector::Gender selectedGender READ getSelectedGender WRITE setSelectedGender)

public:
    explicit QGenderSelector(QWidget* parent = 0);

    /**
     * @brief Supported genders
     */
    enum Gender {
        Male = 0x0,
        Female = 0x1,
        Other = 0x2
    };

    /**
     * @brief Get selected gender
     * @return Currently selected gender as enum value
     * @see setSelectedGender
     * @see selectedGender
     */
    Gender getSelectedGender() const { return m_selectedGender; }

    /**
     * @brief Convert \a Gender to DICOM VR string
     *
     * Creates a string with the corresponding DICOM VR (M/F/O) for the given \a Gender enum.
     *
     * @param g \a Gender that shall be converted to a VR string
     * @return DICOM VR string for the given \a Gender value
     */
    static QString genderToDicomVR(Gender g)
    {
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
    QBoxLayout* m_layout;

    QRadioButton* m_radioMale;
    QRadioButton* m_radioFemale;
    QRadioButton* m_radioOther;

    QButtonGroup* m_buttonGroup;

    void setupUi();

    /**
     * @brief Selected gender value
     *
     * Holds the \a Gender value that has currently been selected in the UI.
     *
     * @see getSelectedGender
     * @see setSelectedGender
     * @see selectedGender
     *
     * @attention This shouldn't be accessed directly since the UI widget's state might need to be
     * changed so use the provided accessor methods!
     */
    Gender m_selectedGender;

signals:
    /**
     * @brief User selected new gender in UI
     * @param gender \a Gender enum value for the newly selected gender
     */
    void selectedGenderChanged(QGenderSelector::Gender gender);

    /**
     * @brief User selected new gender in UI
     * @param genderVR DICOM VR string for the \a Gender value that has been selected
     */
    void selectedGenderChanged(QString genderVR);

public slots:
    void setSelectedGender(QGenderSelector::Gender g);

private slots:
    void buttonGroup_buttonClicked(int);
};

void QGenderSelector_EXPORT QGenderSelector_initResources(void);

#endif // QGENDERSELECTOR_H
