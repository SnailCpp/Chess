#include "chesslog.h"
#include <QDateTime>

QString LevelToText(LogLevel level)
{
    switch (level)
    {
    case TraceLevel: return "Trace";
    case DebugLevel: return "Debug";
    case InfoLevel: return "Info";
    case WarnLevel: return "Warning";
    case ErrorLevel: return "Error";
    case FatalLevel: return "Fatal";
    default: return QString();
    }
}

void Chess_Log(LogLevel level, const QString &message)
{
    if(level < TraceLevel) return;
    QString msg = QString("%1 [%2] %3")
            .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss.zzz"))
            .arg(LevelToText(level))
            .arg(message);
    switch (level)
    {
    case TraceLevel: qDebug() << msg; break;
    case DebugLevel: qDebug() << msg; break;
    case InfoLevel: qDebug() << msg; break;
    case WarnLevel: qWarning() << msg; break;
    case ErrorLevel: qCritical() << msg; break;
    case FatalLevel: qFatal(msg.toLocal8Bit().data()); break;
    default: break;
    }
}

void Chess_Trace(const QString &message)
{
    Chess_Log(TraceLevel, message);
}

void Chess_Debug(const QString &message)
{
    Chess_Log( DebugLevel, message);
}

void Chess_Info(const QString &message)
{
    Chess_Log(InfoLevel, message);
}

void Chess_Warning(const QString &message)
{
    Chess_Log(WarnLevel, message);
}

void Chess_Error(const QString &message)
{
    Chess_Log(ErrorLevel, message);
}

void Chess_Fatal(const QString &message)
{
    Chess_Log(FatalLevel, message);
}

