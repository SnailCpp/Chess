/********************************************************************************
** Form generated from reading UI file 'enginedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ENGINEDIALOG_H
#define UI_ENGINEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_EngineDialog
{
public:
    QDialogButtonBox *buttonBox;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;

    void setupUi(QDialog *EngineDialog)
    {
        if (EngineDialog->objectName().isEmpty())
            EngineDialog->setObjectName(QStringLiteral("EngineDialog"));
        EngineDialog->resize(245, 228);
        QIcon icon;
        icon.addFile(QStringLiteral(":/ICON/Qxxl.ICO"), QSize(), QIcon::Normal, QIcon::Off);
        EngineDialog->setWindowIcon(icon);
        buttonBox = new QDialogButtonBox(EngineDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(20, 170, 171, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        checkBox = new QCheckBox(EngineDialog);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setGeometry(QRect(30, 50, 161, 18));
        checkBox_2 = new QCheckBox(EngineDialog);
        checkBox_2->setObjectName(QStringLiteral("checkBox_2"));
        checkBox_2->setGeometry(QRect(30, 110, 161, 18));

        retranslateUi(EngineDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), EngineDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), EngineDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(EngineDialog);
    } // setupUi

    void retranslateUi(QDialog *EngineDialog)
    {
        EngineDialog->setWindowTitle(QApplication::translate("EngineDialog", "\345\215\270\350\275\275\345\274\225\346\223\216", Q_NULLPTR));
        checkBox->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class EngineDialog: public Ui_EngineDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ENGINEDIALOG_H
