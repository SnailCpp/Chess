#include "chessprotocol.h"
#include "chessbase.h"
#include "chesslog.h"
#include <QString>


ChessProtocol * ChessProtocol::INSTANCE = 0;
ChessProtocol * ChessProtocol::instance()
{
    if(!INSTANCE)
    {
        INSTANCE = new ChessProtocol;
    }
    return INSTANCE;
}

ChessProtocol::ChessProtocol()
{
    chessPosition = ChessPosition::instance();
    Chess_Trace("new ChessProtocol");
}

ChessProtocol::~ChessProtocol()
{
    Chess_Trace("delete ChessProtocol");

}

QString ChessProtocol::ArrayToFEN(const unsigned char *ucpcSquares, int currentTurn)
{
    int k = 0;                                                  // 计数器
    QString strFEN;
    for (int i = ROW_TOP; i <= ROW_BOTTOM; ++i)
    {
        k = 0;
        for (int j = COL_LEFT; j <= COL_RIGHT; ++j)
        {
            int coord = COORD_XY(j, i);
            char pc = ucpcSquares[coord];                       // 获取棋子

            if (pc == 0)
            {
                k++;

                if (j == COL_RIGHT)
                {
                    strFEN.append(k + '0');
                    strFEN.append('/');
                }
            }
            else
            {
                if (k > 0)
                {
                    strFEN.append(k + '0');
                    k = 0;
                }

                strFEN.append(IntToChar(pc));
                if (j == COL_RIGHT)
                {
                    strFEN.append('/');
                }
            }
        }
    }

    strFEN.replace(strFEN.size() - 1, 1, ' ');
    strFEN.append(currentTurn == BLACK ? 'b' : 'w');
    return strFEN;
}

char ChessProtocol::IntToChar(int pc)
{
    switch(pc)
    {
    case 8:  return 'K';
    case 9:  return 'A';
    case 10: return 'B';
    case 11: return 'N';
    case 12: return 'R';
    case 13: return 'C';
    case 14: return 'P';

    case 16: return 'k';
    case 17: return 'a';
    case 18: return 'b';
    case 19: return 'n';
    case 20: return 'r';
    case 21: return 'c';
    case 22: return 'p';
    default: return 0;
    }
}

void ChessProtocol::FENToArray(QString strFEN, unsigned char *ucpcSquares, int &currentTurn)
{
    int slashCount = 0;                 // 斜线个数
    int i = 0;
    int k = 0;                          // 列数

    while (strFEN[i] != ' ')
    {
        int coord = COORD_XY(COL_LEFT + k, ROW_TOP + slashCount);
        if (strFEN[i] >= 'A' && strFEN[i] <= 'z')
        {
            char type = CharToInt(strFEN[i].toLatin1());
            ucpcSquares[coord] = type;
            k++;
        }
        if (strFEN[i] >= '0' && strFEN[i] <= '9')
        {
            k += (strFEN[i].toLatin1() - '0');
        }

        if (strFEN[i] == '/')
        {
            slashCount++;
            k = 0;
        }

        i++;
    }

    i++;
    currentTurn = (strFEN[i] == 'w') ? RED : BLACK;
}

int ChessProtocol::CharToInt(char ch)
{
    switch(ch)
    {
    case 'K': return 8;
    case 'A': return 9;
    case 'B': return 10;
    case 'N': return 11;
    case 'R': return 12;
    case 'C': return 13;
    case 'P': return 14;

    case 'k': return 16;
    case 'a': return 17;
    case 'b': return 18;
    case 'n': return 19;
    case 'r': return 20;
    case 'c': return 21;
    case 'p': return 22;
    default: return 0;
    }

}

int ChessProtocol::Move(const char *ch)
{
    int sqSrc, sqDst, mv;
    sqSrc = (ch[0] - 'a' + 3) + (( '9' - ch[1] + 3) << 4);
    sqDst = (ch[2] - 'a' + 3) + (( '9' - ch[3] + 3) << 4);
    mv = MOVE(sqSrc, sqDst);

    return mv;
}


void ChessProtocol::GetMoveStepAlpha(int mv, /*int pcCaptured,*/ QString &stepAlpha)
{

    int fromPos = SRC(mv);
    int pc = chessPosition->ucpcSquares[DST(mv)];
    stepAlpha.append(IntToChar(pc));

    int fromX = COL_X(fromPos);
    int fromY = ROW_Y(fromPos);

    int dstPos = DST(mv);
    int toX = COL_X(dstPos);
    int toY = ROW_Y(dstPos);

    GetGeneralMoveStepAlpha(fromX, fromY, toX, toY, stepAlpha);

}

void ChessProtocol::GetGeneralMoveStepAlpha(int fromX, int fromY, int toX, int toY, QString &stepAlpha)
{
    bool black = chessPosition->sdPlayer;    
    int edge = black ? COL_LEFT : COL_RIGHT;                                    // 黑方左列是最大列， 红方右列是最大列

    stepAlpha += (abs(edge - fromX) + 1 + '0');
    if (fromY == toY)                                                           // 同一列为平.
    {
        stepAlpha += '.';
        stepAlpha += (abs(edge - toX) + 1 + '0');
    }
    else
    {
        stepAlpha += toY > fromY ? (black ? '+' : '-') : (black ? '-' : '+');   // 目标行大于原始行 黑：进  红：退
        stepAlpha += (abs(fromY - toY) + '0');
    }
}

QString ChessProtocol::DigitToChinese(const QChar &digit, bool black)
{
    QString strDigit;
    if (black)
    {
        switch(digit.toLatin1())
        {
        case '1':
            strDigit = "1";
            break;
        case '2':
            strDigit = "2";
            break;
        case '3':
            strDigit = "3";
            break;
        case '4':
            strDigit = "4";
            break;
        case '5':
            strDigit = "5";
            break;
        case '6':
            strDigit = "6";
            break;
        case '7':
            strDigit = "7";
            break;
        case '8':
            strDigit = "8";
            break;
        case '9':
            strDigit = "9";
            break;
        default:
            break;
        }
    }
    else
    {
        switch(digit.toLatin1())
        {
        case '1':
            strDigit = "一";
            break;
        case '2':
            strDigit = "二";
            break;
        case '3':
            strDigit = "三";
            break;
        case '4':
            strDigit = "四";
            break;
        case '5':
            strDigit = "五";
            break;
        case '6':
            strDigit = "六";
            break;
        case '7':
            strDigit = "七";
            break;
        case '8':
            strDigit = "八";
            break;
        case '9':
            strDigit = "九";
            break;
        default:
            break;
        }
    }

    return strDigit;
}

QString ChessProtocol::PieceCodeToChinese(const QChar &code)
{
    QString strCode;
    switch(code.toLatin1())
    {
    case 'k':
        strCode = "将";
        break;
    case 'r':
        strCode = "车";
        break;
    case 'n':
        strCode = "马";
        break;
    case 'c':
        strCode = "炮";
        break;
    case 'a':
        strCode = "士";
        break;
    case 'b':
        strCode = "象";
        break;
    case 'p':
        strCode = "卒";
        break;
    case 'K':
        strCode = "帅";
        break;
    case 'R':
        strCode = "车";
        break;
    case 'N':
        strCode = "马";
        break;
    case 'C':
        strCode = "炮";
        break;
    case 'A':
        strCode = "仕";
        break;
    case 'B':
        strCode = "相";
        break;
    case 'P':
        strCode = "兵";
        break;
    default:
        break;
    }

    return strCode;
}

QString ChessProtocol::ActionToChinese(const QChar &action)
{
    QString strAction;
    switch(action.toLatin1())
    {
    case '.':
        strAction = "平";
        break;
    case '+':
        strAction = "进";
        break;
    case '-':
        strAction = "退";
        break;
    default:
        break;
    }

    return strAction;
}

void ChessProtocol::AlphaFmtToChiness(const QString &alphaFmt, QString &chineseFmt, bool black)
{
    if (alphaFmt[1] >= 'a')         // 黑方
    {
        chineseFmt = DigitToChinese(alphaFmt[1], black) + " " +
                PieceCodeToChinese(alphaFmt[0]) + " " +
                ActionToChinese(alphaFmt[2]) + " " +
                DigitToChinese(alphaFmt[3], black);
    }
    else                            // 红方
    {
        chineseFmt = PieceCodeToChinese(alphaFmt[0]) + " " +
                DigitToChinese(alphaFmt[1], black) + " " +
                ActionToChinese(alphaFmt[2]) + " " +
                DigitToChinese(alphaFmt[3], black);
   }
}
