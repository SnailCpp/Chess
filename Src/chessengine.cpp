#include "chessengine.h"
#include "chessprotocol.h"
#include "chesslog.h"
#include "gamesettings.h"
#include <QMessageBox>

ChessEngine * ChessEngine::INSTANCE = 0;
ChessEngine * ChessEngine::instance()
{
    if(!INSTANCE)
    {
        INSTANCE = new ChessEngine;
    }
    return INSTANCE;
}

ChessEngine::ChessEngine(QObject *parent) :
     QObject(parent)
{
    Init();
    Chess_Trace("new ChessEngine");
}

ChessEngine::~ChessEngine()
{
   Chess_Trace("delete ChessEngine");
}

// 读取对手的消息
void ChessEngine::Read(int pid, const char *fen)
{

    char cmd[128] = "position fen ";
    char go[128] = "go time ";
    char time[128];

    itoa(g_gameSettings.GetStepTime(), time, 10);
    strcat(go, time);
    strcat(go," increment 0\r\n");
    strcat(cmd, fen);
    strcat(cmd, " - - 0 1\r\n");

    WriteToEngine(pid, cmd);
    WriteToEngine(pid, go);
}

void ChessEngine::Init()
{
    connect(&engine[0], SIGNAL(stateChanged(QProcess::ProcessState)),
            this, SLOT(ProcessChangeState0(QProcess::ProcessState)));
    connect(&engine[0], SIGNAL(readyReadStandardOutput()), this, SLOT(ReadFromEngine0()));
    connect(&engine[0], SIGNAL(readyReadStandardError()), this, SLOT(ReadFromEngine0()));

    connect(&engine[1], SIGNAL(stateChanged(QProcess::ProcessState)),
            this, SLOT(ProcessChangeState1(QProcess::ProcessState)));
    connect(&engine[1], SIGNAL(readyReadStandardOutput()), this, SLOT(ReadFromEngine1()));
    connect(&engine[1], SIGNAL(readyReadStandardError()), this, SLOT(ReadFromEngine1()));
}

void ChessEngine::Open(QString engineName)
{
    // 启动引擎
    if(!engine[0].isOpen()){
        engine[0].start(engineName);
    }else{
        engine[1].start(engineName);
    }
}

void ChessEngine::Close(int pid)
{
    WriteToEngine(pid, "quit\r\n");
    engine[pid].close();
}

void ChessEngine::Exit()
{
    for(int pid = 0; pid != 2; pid++){

        if(engine[pid].isOpen()){
            WriteToEngine(pid, "quit\r\n");
            engine[pid].close();
        }

    }
}

void ChessEngine::WriteToEngine(int pid, const char *ic)
{
    Chess_Info(ic);
    emit ShowInfoList(ic);
    engine[pid].write(ic);

}

void ChessEngine::ReadFromEngine0()
{
    ReadFromEngine(0);
}

void ChessEngine::ProcessChangeState0(QProcess::ProcessState s)
{
    ProcessChangeState(0, s);

}

void ChessEngine::ReadFromEngine1()
{
    ReadFromEngine(1);
}

void ChessEngine::ProcessChangeState1(QProcess::ProcessState s)
{
    ProcessChangeState(1, s);

}

void ChessEngine::ReadFromEngine(int pid)
{
    QString data = QString(engine[pid].readAllStandardOutput());

    Chess_Info(data);
    emit ShowInfoList(data);

    if(!data.contains("bestmove", Qt::CaseInsensitive))
        return;

    QStringList sl = data.split('\n', QString::SkipEmptyParts);

    int size = sl.size();
    for(int i=0; i<size; ++i)
    {
        QString tmp = sl.at(i).trimmed();
        if(tmp.startsWith("bestmove", Qt::CaseInsensitive))
        {
            QStringList ll = tmp.split(' ', QString::SkipEmptyParts);
            if(ll.size()>=2)
            {
                QString bestmove = ll.at(1);
                emit Write(bestmove);
                return ;
            }
        }
    }
}

void ChessEngine::ProcessChangeState(int pid, QProcess::ProcessState s)
{
    if(s == QProcess::Running)
    {
        Chess_Info("Engine is running");
        WriteToEngine(pid, "ucci\r\n");

    }
}
