/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_new;
    QAction *action_play;
    QAction *action_exit;
    QAction *action_start;
    QAction *action_end;
    QAction *action_next;
    QAction *action_previous;
    QAction *action_undo;
    QAction *action_flip;
    QAction *action_red;
    QAction *action_black;
    QAction *action_load;
    QAction *action_unload;
    QAction *action_about;
    QAction *action_sound;
    QAction *action_set;
    QAction *action_open;
    QAction *action_save;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menu_3;
    QMenu *menu_4;
    QMenu *menu_5;
    QMenu *menu_6;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(874, 720);
        MainWindow->setMinimumSize(QSize(874, 720));
        MainWindow->setMaximumSize(QSize(874, 720));
        QIcon icon;
        icon.addFile(QStringLiteral(":/ICON/Qxxl.ICO"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        action_new = new QAction(MainWindow);
        action_new->setObjectName(QStringLiteral("action_new"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/ICON/546384.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_new->setIcon(icon1);
        action_play = new QAction(MainWindow);
        action_play->setObjectName(QStringLiteral("action_play"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/ICON/1072692.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_play->setIcon(icon2);
        action_exit = new QAction(MainWindow);
        action_exit->setObjectName(QStringLiteral("action_exit"));
        action_start = new QAction(MainWindow);
        action_start->setObjectName(QStringLiteral("action_start"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/ICON/1072686.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_start->setIcon(icon3);
        action_end = new QAction(MainWindow);
        action_end->setObjectName(QStringLiteral("action_end"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/ICON/1072690.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_end->setIcon(icon4);
        action_next = new QAction(MainWindow);
        action_next->setObjectName(QStringLiteral("action_next"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/ICON/1072683.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_next->setIcon(icon5);
        action_previous = new QAction(MainWindow);
        action_previous->setObjectName(QStringLiteral("action_previous"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/ICON/1072676.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_previous->setIcon(icon6);
        action_undo = new QAction(MainWindow);
        action_undo->setObjectName(QStringLiteral("action_undo"));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/ICON/1072701.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_undo->setIcon(icon7);
        action_flip = new QAction(MainWindow);
        action_flip->setObjectName(QStringLiteral("action_flip"));
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/ICON/1072687.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_flip->setIcon(icon8);
        action_red = new QAction(MainWindow);
        action_red->setObjectName(QStringLiteral("action_red"));
        action_black = new QAction(MainWindow);
        action_black->setObjectName(QStringLiteral("action_black"));
        action_load = new QAction(MainWindow);
        action_load->setObjectName(QStringLiteral("action_load"));
        action_unload = new QAction(MainWindow);
        action_unload->setObjectName(QStringLiteral("action_unload"));
        action_about = new QAction(MainWindow);
        action_about->setObjectName(QStringLiteral("action_about"));
        action_sound = new QAction(MainWindow);
        action_sound->setObjectName(QStringLiteral("action_sound"));
        action_set = new QAction(MainWindow);
        action_set->setObjectName(QStringLiteral("action_set"));
        action_open = new QAction(MainWindow);
        action_open->setObjectName(QStringLiteral("action_open"));
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/ICON/1072442.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_open->setIcon(icon9);
        action_save = new QAction(MainWindow);
        action_save->setObjectName(QStringLiteral("action_save"));
        QIcon icon10;
        icon10.addFile(QStringLiteral(":/ICON/1072697.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_save->setIcon(icon10);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 874, 22));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QStringLiteral("menu_2"));
        menu_3 = new QMenu(menuBar);
        menu_3->setObjectName(QStringLiteral("menu_3"));
        menu_4 = new QMenu(menuBar);
        menu_4->setObjectName(QStringLiteral("menu_4"));
        menu_5 = new QMenu(menuBar);
        menu_5->setObjectName(QStringLiteral("menu_5"));
        menu_6 = new QMenu(menuBar);
        menu_6->setObjectName(QStringLiteral("menu_6"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_2->menuAction());
        menuBar->addAction(menu_3->menuAction());
        menuBar->addAction(menu_4->menuAction());
        menuBar->addAction(menu_5->menuAction());
        menuBar->addAction(menu_6->menuAction());
        menu->addAction(action_new);
        menu->addAction(action_open);
        menu->addAction(action_save);
        menu->addAction(action_exit);
        menu_2->addSeparator();
        menu_2->addAction(action_play);
        menu_2->addSeparator();
        menu_2->addAction(action_start);
        menu_2->addAction(action_end);
        menu_2->addAction(action_next);
        menu_2->addAction(action_previous);
        menu_2->addSeparator();
        menu_2->addAction(action_undo);
        menu_3->addAction(action_flip);
        menu_3->addSeparator();
        menu_3->addAction(action_red);
        menu_3->addAction(action_black);
        menu_4->addAction(action_sound);
        menu_4->addAction(action_set);
        menu_5->addAction(action_load);
        menu_5->addAction(action_unload);
        menu_6->addAction(action_about);
        mainToolBar->addAction(action_new);
        mainToolBar->addSeparator();
        mainToolBar->addAction(action_save);
        mainToolBar->addAction(action_open);
        mainToolBar->addSeparator();
        mainToolBar->addAction(action_play);
        mainToolBar->addAction(action_start);
        mainToolBar->addAction(action_previous);
        mainToolBar->addAction(action_next);
        mainToolBar->addAction(action_end);
        mainToolBar->addSeparator();
        mainToolBar->addAction(action_undo);
        mainToolBar->addAction(action_flip);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Qxxl", Q_NULLPTR));
        action_new->setText(QApplication::translate("MainWindow", "\346\226\260\346\270\270\346\210\217(&N)", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        action_new->setToolTip(QApplication::translate("MainWindow", "\346\226\260\346\270\270\346\210\217(N)", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        action_play->setText(QApplication::translate("MainWindow", "\345\274\200\345\247\213(&P)", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        action_play->setToolTip(QApplication::translate("MainWindow", "\345\274\200\345\247\213(P)", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        action_exit->setText(QApplication::translate("MainWindow", "\351\200\200\345\207\272(&X)", Q_NULLPTR));
        action_start->setText(QApplication::translate("MainWindow", "\345\274\200\345\261\200 ", Q_NULLPTR));
        action_end->setText(QApplication::translate("MainWindow", "\347\273\223\345\261\200", Q_NULLPTR));
        action_next->setText(QApplication::translate("MainWindow", "\345\211\215\350\277\233", Q_NULLPTR));
        action_previous->setText(QApplication::translate("MainWindow", "\345\220\216\351\200\200", Q_NULLPTR));
        action_undo->setText(QApplication::translate("MainWindow", "\346\202\224\346\243\213", Q_NULLPTR));
        action_flip->setText(QApplication::translate("MainWindow", "\347\277\273\350\275\254\346\243\213\347\233\230(&F)", Q_NULLPTR));
        action_red->setText(QApplication::translate("MainWindow", "\347\272\242\346\226\271\345\205\210\350\265\260(&R)", Q_NULLPTR));
        action_black->setText(QApplication::translate("MainWindow", "\351\273\221\346\226\271\345\205\210\350\265\260(&B)", Q_NULLPTR));
        action_load->setText(QApplication::translate("MainWindow", "\345\212\240\350\275\275\345\274\225\346\223\216", Q_NULLPTR));
        action_unload->setText(QApplication::translate("MainWindow", "\345\215\270\350\275\275\345\274\225\346\223\216", Q_NULLPTR));
        action_about->setText(QApplication::translate("MainWindow", "\345\205\263\344\272\216", Q_NULLPTR));
        action_sound->setText(QApplication::translate("MainWindow", "\350\265\260\345\255\220\345\217\221\345\243\260", Q_NULLPTR));
        action_set->setText(QApplication::translate("MainWindow", "\346\270\270\346\210\217\350\256\276\347\275\256", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        action_set->setToolTip(QApplication::translate("MainWindow", "\346\270\270\346\210\217\350\256\276\347\275\256", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        action_open->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200(&O)", Q_NULLPTR));
        action_save->setText(QApplication::translate("MainWindow", "\344\277\235\345\255\230(&S)", Q_NULLPTR));
        menu->setTitle(QApplication::translate("MainWindow", "\346\226\207\344\273\266(&F)", Q_NULLPTR));
        menu_2->setTitle(QApplication::translate("MainWindow", "\347\235\200\346\263\225(&M)", Q_NULLPTR));
        menu_3->setTitle(QApplication::translate("MainWindow", "\345\261\200\351\235\242(&B)", Q_NULLPTR));
        menu_4->setTitle(QApplication::translate("MainWindow", "\345\267\245\345\205\267(&T)", Q_NULLPTR));
        menu_5->setTitle(QApplication::translate("MainWindow", "\345\274\225\346\223\216(&E)", Q_NULLPTR));
        menu_6->setTitle(QApplication::translate("MainWindow", "\345\205\263\344\272\216(&A)", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
