#ifndef CHESSENGINE_H
#define CHESSENGINE_H

#include "infolist.h"
#include <QProcess>

class ChessEngine : public QObject
{
    Q_OBJECT
public:
    static ChessEngine * instance();
    ~ChessEngine();
    void Read(int pid, const char *fen);
    void ReadFromEngine(int pid);
    void ProcessChangeState(int pid, QProcess::ProcessState s);
    void Init();
    void Exit();

signals:
    void Write(const QString &message);
    void ShowInfoList(const QString &info);

public slots:
    void ReadFromEngine0();
    void ProcessChangeState0(QProcess::ProcessState s);
    void ReadFromEngine1();
    void ProcessChangeState1(QProcess::ProcessState s);
    void Open(QString engineName);
    void Close(int pid);

private:
    static  ChessEngine * INSTANCE;
    explicit ChessEngine(QObject *parent = 0);
    void WriteToEngine(int pid, const char *ic);
    QProcess engine[2];
};

#endif // CHESSENGINE_H
