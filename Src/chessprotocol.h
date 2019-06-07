#ifndef CHESSPROTOCOL_H
#define CHESSPROTOCOL_H

#include "chessposition.h"
#include <QString>
#include <QChar>
#include <qstring.h>

class ChessProtocol
{
public:
    static ChessProtocol *instance();
    ~ChessProtocol();

    int side;
    char FenString[128];
    QString ArrayToFEN(const unsigned char *ucpcSquares, int currentTurn);
    void FENToArray(QString strFEN, unsigned char *ucpcSquares, int &currentTurn);
    char IntToChar(int pc);
    int CharToInt(char ch);
    int Move(const char *ch);
    QString DigitToChinese(const QChar &digit, bool black);
    QString PieceCodeToChinese(const QChar &code);
    QString ActionToChinese(const QChar &action);
    void AlphaFmtToChiness(const QString &alphaFmt, QString &chineseFmt, bool black);
    void GetMoveStepAlpha(int mv, QString &stepAlpha);
    void GetGeneralMoveStepAlpha(int fromX, int fromY, int toX, int toY, QString &stepAlpha);

private:
    static ChessProtocol *INSTANCE;
    explicit ChessProtocol();
    ChessPosition *chessPosition;
};

#endif // CHESSPROTOCOL_H
