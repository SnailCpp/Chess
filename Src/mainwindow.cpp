#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "chessbase.h"
#include "chesslog.h"
#include "chessengine.h"
#include "enginedialog.h"
#include "gamesettings.h"
#include <QInputDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QDesktopWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    engineName[0].clear();
    engineName[1].clear();

    settingsDialog = SettingsDialog::instance(this);
    chessPosition = ChessPosition::instance();
    chessProtocol = ChessProtocol::instance();
    chessEngine = ChessEngine::instance();
    chessBoard =  ChessBoard::instance(this);
    stepList = StepList::instance(this);
    infoList = InfoList::instance(this);
    stepLabel = new QLabel(this);
    stepLabel->move(619,100);
    stepLabel->setText("走法列表");
    infoLabel = new QLabel(this);
    infoLabel->move(619,385);
    infoLabel->setText("信息列表");

    connect(this, StartGame, chessBoard, chessBoard->StartGame);
    connect(this, StartMove, chessBoard, chessBoard->StartMove);
    connect(this, EndMove, chessBoard, chessBoard->EndMove);
    connect(this, PreMove, chessBoard, chessBoard->PreMove);
    connect(this, NextMove, chessBoard, chessBoard->NextMove);
    connect(this, UndoMove, chessBoard, chessBoard->UndoMove);
    connect(this, FlipBoard, chessBoard, chessBoard->FlipBoard);
    connect(this, OpenEngine, chessEngine, chessEngine->Open);
    connect(this, CloseEngine, chessEngine, chessEngine->Close);
    connect(this, ShowStepList, stepList, stepList->ShowStepList);
    connect(chessEngine, chessEngine->Write, chessBoard, chessBoard->Write);
    connect(chessEngine, chessEngine->ShowInfoList, infoList, infoList->ShowInfoList);
    connect(chessBoard, chessBoard->SetStepList, this, SetStepList);
    connect(chessBoard, chessBoard->ClearLastStep, stepList, stepList->ClearLastStep);
    connect(chessBoard, chessBoard->SelectionStep, stepList, stepList->SelectionStep);
    connect(settingsDialog, settingsDialog->SetOk, this, GameInit);

    Chess_Trace("new MainWindow");
}

MainWindow::~MainWindow()
{
    delete chessEngine;
    delete chessProtocol;
    delete chessPosition;
    delete ui;
    Chess_Trace("delete MainWindow");

}


void MainWindow::GameInit()
{
    chessBoard->Init();
    chessBoard->StartUp();
    stepList->ClearStepList();
    infoList->ClearInfoList();

    ui->action_open->setEnabled(true);
    ui->action_save->setEnabled(false);
    ui->action_play->setEnabled(true);
    ui->action_start->setEnabled(false);
    ui->action_end->setEnabled(false);
    ui->action_previous->setEnabled(false);
    ui->action_next->setEnabled(false);
    ui->action_undo->setEnabled(false);
    ui->action_black->setEnabled(true);
    ui->action_red->setEnabled(true);
    ui->action_set->setEnabled(true);
    ui->action_unload->setEnabled(false);
    ui->action_load->setEnabled(false);

    if(g_gameSettings.GetGameType() == human_computer){

        if(!engineName[0].isEmpty() || !engineName[1].isEmpty()){
            ui->action_play->setEnabled(true);
            ui->action_unload->setEnabled(true);
        }else if(engineName[0].isEmpty() && engineName[1].isEmpty()){
            ui->action_play->setEnabled(false);
            ui->action_load->setEnabled(true);
        }

    }else if(g_gameSettings.GetGameType() == computer_compter){

        if(!engineName[0].isEmpty() && !engineName[1].isEmpty()){

            ui->action_unload->setEnabled(true);
            ui->action_play->setEnabled(true);

        }else if( engineName[0].isEmpty() && engineName[1].isEmpty()){

             ui->action_play->setEnabled(false);
             ui->action_load->setEnabled(true);
             ui->action_unload->setEnabled(false);

        }else{
            ui->action_play->setEnabled(false);
            ui->action_load->setEnabled(true);
            ui->action_unload->setEnabled(true);
        }
    }

}

void MainWindow::SetStepList(QString step)
{
    emit ShowStepList(step);
}

void MainWindow::closeEvent(QCloseEvent *)
{
    chessEngine->Exit();
}

void MainWindow::DialogMessage(int id)
{
    if(id == 0){

        emit CloseEngine(0);
        engineName[0].clear();
        QMessageBox::information(this, "卸载引擎", "引擎已卸载！", QMessageBox::Ok);
        ui->action_load->setEnabled(true);
        ui->action_play->setEnabled(false);

    }else if(id == 1){

        emit CloseEngine(1);
        engineName[1].clear();
        QMessageBox::information(this, "卸载引擎", "引擎已卸载！", QMessageBox::Ok);
        ui->action_load->setEnabled(true);
        ui->action_play->setEnabled(false);

    }

    if(engineName[0].isEmpty() && engineName[1].isEmpty()){
        ui->action_unload->setEnabled(false);
    }
}

void MainWindow::on_action_new_triggered()
{
    GameInit();
}

void MainWindow::on_action_open_triggered()
{
    QString fn = QFileDialog::getOpenFileName(this,tr("加载棋局"),QString(),tr("Files(*.fen)"));
    QFile file(fn);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return;
    }
    QTextStream in(&file);
    QString line = in.readLine();
    if (line.isNull())
    {
        return;
    }

    unsigned char ucpcSquares[256];
    int currentTurn = 0;
    memset(ucpcSquares, 0, sizeof(ucpcSquares));
    chessProtocol->FENToArray(line, ucpcSquares, currentTurn);
    GameInit();
    chessBoard->OpenBoard(ucpcSquares);
}

void MainWindow::on_action_save_triggered()
{
    QString fn = QFileDialog::getSaveFileName(this, tr("保存棋局"), QString(), "Files(*.fen)");
    if (fn.isEmpty())
    {
        return;
    }
    if (! fn.endsWith(".fen",Qt::CaseInsensitive))
    {
        fn += ".fen";
    }

    QFile file(fn);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        return;
    }
    QTextStream out(&file);
    out << chessProtocol->ArrayToFEN(chessPosition->ucpcSquares, chessPosition->sdPlayer);
    file.close();
}


void MainWindow::on_action_play_triggered()
{
    ui->action_open->setEnabled(false);
    ui->action_save->setEnabled(true);
    ui->action_start->setEnabled(true);
    ui->action_end->setEnabled(true);
    ui->action_previous->setEnabled(true);
    ui->action_next->setEnabled(true);
    ui->action_undo->setEnabled(true);

    emit StartGame();
    ui->action_play->setEnabled(false);
    ui->action_red->setEnabled(false);
    ui->action_black->setEnabled(false);
    ui->action_set->setEnabled(false);
}

void MainWindow::on_action_exit_triggered()
{
    chessEngine->Exit();
    exit(0);
}

void MainWindow::on_action_start_triggered()
{
    emit StartMove();
}

void MainWindow::on_action_end_triggered()
{
    emit EndMove();
}

void MainWindow::on_action_next_triggered()
{
    emit NextMove();
}

void MainWindow::on_action_previous_triggered()
{
    emit PreMove();
}

void MainWindow::on_action_undo_triggered()
{
    emit UndoMove();
}

void MainWindow::on_action_flip_triggered()
{
    emit FlipBoard();
}


void MainWindow::on_action_red_triggered()
{
    g_gameSettings.SetAhead(RED);
}

void MainWindow::on_action_black_triggered()
{
    g_gameSettings.SetAhead(BLACK);
}

void MainWindow::on_action_load_triggered()
{
    QString path = QFileDialog::getOpenFileName(this, "加载引擎", ".", "exe file(*.exe)");

    if(!path.isEmpty()){

        if(g_gameSettings.GetGameType() == 1){

            engineName[0] = QFileInfo(path).fileName().split(".exe").at(0);
            Chess_Debug(engineName[0]);
            emit OpenEngine(path);
            QMessageBox::information(this, "加载引擎", "引擎已加载！", QMessageBox::Ok);
            ui->action_load->setEnabled(false);

        }else{

            if(engineName[0].isEmpty()){

                engineName[0] = QFileInfo(path).fileName().split(".exe").at(0);
                Chess_Debug(engineName[0]);
                emit OpenEngine(path);
                QMessageBox::information(this, "加载引擎", "引擎已加载！", QMessageBox::Ok);

            }else if(engineName[1].isEmpty()){

                engineName[1] = QFileInfo(path).fileName().split(".exe").at(0);
                emit OpenEngine(path);
                QMessageBox::information(this, "加载引擎", "引擎已加载！", QMessageBox::Ok);
            }

            if(!engineName[0].isEmpty() && !engineName[1].isEmpty()){
                ui->action_load->setEnabled(false);
            }
        }

        ui->action_unload->setEnabled(true);
        ui->action_play->setEnabled(true);

    }else{
        QMessageBox::warning(this, "路径",
                   "您未选择任何文件！");
    }
}

void MainWindow::on_action_unload_triggered()
{
    if(!engineName[0].isEmpty() && engineName[1].isEmpty()){

        emit CloseEngine(0);
        engineName[0].clear();
        QMessageBox::information(this, "卸载引擎", "引擎已卸载！", QMessageBox::Ok);

        ui->action_unload->setEnabled(false);
        ui->action_play->setEnabled(false);

    }else if(engineName[0].isEmpty() && !engineName[1].isEmpty()){

        emit CloseEngine(1);
        engineName[1].clear();
        QMessageBox::information(this, "卸载引擎", "引擎已卸载！", QMessageBox::Ok);
        ui->action_unload->setEnabled(false);
        ui->action_play->setEnabled(false);

    }else if(!engineName[0].isEmpty() && !engineName[1].isEmpty()){

        engineDialog = EngineDialog::instance(this);
        engineDialog->setModal(true);

        connect(engineDialog, engineDialog->checked_checkBox, this, DialogMessage);
        engineDialog->ShowEngineName(engineName);
        engineDialog->show();
    }
}

void MainWindow::on_action_sound_triggered()
{
    QMessageBox::information(this, "声音设置", "无声音资源！", QMessageBox::Warning);
}

void MainWindow::on_action_set_triggered()
{
    settingsDialog->show();
}

void MainWindow::on_action_about_triggered()
{
   QMessageBox::about(NULL, "关于本软件", "Chinese Chess Version 1.0");
}
