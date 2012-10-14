/* 
 * File:   PreferencesForm.h
 * Author: andre
 *
 * Created on September 25, 2012, 2:09 PM
 */

#ifndef _PREFERENCESFORM_H
#define	_PREFERENCESFORM_H

#include "ui_PreferencesForm.h"

class PreferencesForm : public QDialog {
    Q_OBJECT
public:
    PreferencesForm();
    virtual ~PreferencesForm();
    QString getMapTheme();

signals:
       void moreMapsClicked();

private slots:
    void browse();
    void saveSettings();
    void emitMoreMapsButtonClicked();

private:
    Ui::PreferencesForm widget;

    void setupSignalsSlots();
    void customSetupUi();
    void fillUpMapThemesComboBox();
};

#endif	/* _PREFERENCESFORM_H */
