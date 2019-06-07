#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "infolist.h"
#include "steplist.h"
#include "settingsdialog.h"
#include "enginedialog.h"
#include <QMainWindow>
#include <QLabel>
#include <chessboard.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    StartGame();
    StartMove();
    EndMove();
    PreMove();
    NextMove();
    UndoMove();
    FlipBoard();
    OpenEngine(QString &path);
    CloseEngine(int id);
    ShowStepList(QString step);

private slots:
    void SetStepList(QString step);
    void DialogMessage(int id);
    void GameInit();
    void closeEvent(QCloseEvent *);
    void on_action_new_triggered();    
    void on_action_open_triggered();
    void on_action_save_triggered();
    void on_action_play_triggered();
    void on_action_exit_triggered();
    void on_action_start_triggered();
    void on_action_end_triggered();
    void on_action_next_triggered();
    void on_action_previous_triggered();
    void on_action_undo_triggered();
    void on_action_flip_triggered();
    void on_action_red_triggered();
    void on_action_black_triggered();
    void on_action_load_triggered();
    void on_action_unload_triggered();
    void on_action_sound_triggered();
    void on_action_set_triggered();
    void on_action_about_triggered();

private:
    Ui::MainWindow *ui;
    ChessBoard *chessBoard;
    StepList *stepList;
    InfoList *infoList;
    QLabel *stepLabel, *infoLabel;
    SettingsDialog *settingsDialog;
    EngineDialog *engineDialog;
    ChessProtocol *chessProtocol;
    ChessEngine *chessEngine;
    ChessPosition *chessPosition;
    QString engineName[2];
};

#endif // MAINWINDOW_H
