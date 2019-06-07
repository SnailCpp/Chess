/********************************************************************************
** Form generated from reading UI file 'settingsdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGSDIALOG_H
#define UI_SETTINGSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SettingsDialog
{
public:
    QPushButton *btnApply;
    QPushButton *btnConfirm;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLineEdit *ledStepTime;
    QComboBox *cmbGameType;
    QComboBox *cmbCompetitorSide;
    QComboBox *cmbAhead;

    void setupUi(QDialog *SettingsDialog)
    {
        if (SettingsDialog->objectName().isEmpty())
            SettingsDialog->setObjectName(QStringLiteral("SettingsDialog"));
        SettingsDialog->resize(312, 282);
        QIcon icon;
        icon.addFile(QStringLiteral(":/ICON/Qxxl.ICO"), QSize(), QIcon::Normal, QIcon::Off);
        SettingsDialog->setWindowIcon(icon);
        btnApply = new QPushButton(SettingsDialog);
        btnApply->setObjectName(QStringLiteral("btnApply"));
        btnApply->setGeometry(QRect(90, 230, 51, 27));
        btnConfirm = new QPushButton(SettingsDialog);
        btnConfirm->setObjectName(QStringLiteral("btnConfirm"));
        btnConfirm->setGeometry(QRect(160, 230, 51, 27));
        label = new QLabel(SettingsDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 30, 61, 21));
        label_2 = new QLabel(SettingsDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 130, 61, 21));
        label_3 = new QLabel(SettingsDialog);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(20, 80, 61, 21));
        label_4 = new QLabel(SettingsDialog);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(20, 180, 61, 21));
        ledStepTime = new QLineEdit(SettingsDialog);
        ledStepTime->setObjectName(QStringLiteral("ledStepTime"));
        ledStepTime->setGeometry(QRect(100, 180, 131, 27));
        cmbGameType = new QComboBox(SettingsDialog);
        cmbGameType->setObjectName(QStringLiteral("cmbGameType"));
        cmbGameType->setGeometry(QRect(100, 20, 121, 33));
        cmbCompetitorSide = new QComboBox(SettingsDialog);
        cmbCompetitorSide->setObjectName(QStringLiteral("cmbCompetitorSide"));
        cmbCompetitorSide->setGeometry(QRect(100, 70, 81, 33));
        cmbAhead = new QComboBox(SettingsDialog);
        cmbAhead->setObjectName(QStringLiteral("cmbAhead"));
        cmbAhead->setGeometry(QRect(100, 120, 131, 33));

        retranslateUi(SettingsDialog);

        QMetaObject::connectSlotsByName(SettingsDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingsDialog)
    {
        SettingsDialog->setWindowTitle(QApplication::translate("SettingsDialog", "\346\270\270\346\210\217\350\256\276\347\275\256", Q_NULLPTR));
        btnApply->setText(QApplication::translate("SettingsDialog", "\345\272\224\347\224\250", Q_NULLPTR));
        btnConfirm->setText(QApplication::translate("SettingsDialog", "\347\241\256\345\256\232", Q_NULLPTR));
        label->setText(QApplication::translate("SettingsDialog", "\346\270\270\346\210\217\347\261\273\345\236\213\357\274\232", Q_NULLPTR));
        label_2->setText(QApplication::translate("SettingsDialog", "\350\260\201\345\205\210\350\265\260\357\274\232", Q_NULLPTR));
        label_3->setText(QApplication::translate("SettingsDialog", "\347\224\265\350\204\221\346\211\247\357\274\232", Q_NULLPTR));
        label_4->setText(QApplication::translate("SettingsDialog", "\345\274\225\346\223\216\346\227\266\351\227\264\357\274\232", Q_NULLPTR));
        ledStepTime->setText(QApplication::translate("SettingsDialog", "3000", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SettingsDialog: public Ui_SettingsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGSDIALOG_H
