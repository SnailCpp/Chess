#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "chessposition.h"
#include "chessprotocol.h"
#include "chessengine.h"
#include <QWidget>
#include <QDebug>
#include <QTimer>

class ChessBoard : public QWidget
{
    Q_OBJECT
public:
    static ChessBoard *instance(QWidget *parent);
    ~ChessBoard();

    // 游戏初始化
    void Init();
    void StartUp();
    void OpenBoard(unsigned char *ucpcOpen);

    void paintEvent(QPaintEvent *);
    void DrawSquare(QPainter &painter, int sq, bool bSelected = false);

    void mousePressEvent(QMouseEvent *click);
    void MousePress(int sq);

    void Computer0Think();
    void Computer1Think();

    void ShowChinessStep(int mv);
    void Sleep(unsigned int msec);

signals:
    void SetStepList(QString step);
    void ClearLastStep();
    void SelectionStep(int row);
//    void ChangeCmd(const char* info);

public slots:
    void StartGame();  
    void SaveMove(int mv, int pcCaptured);
    void StartMove();
    void EndMove();
    void PreMove();
    void NextMove();
    void UndoMove();
    void FlipBoard();
    void Write(QString bestmove);

protected:
    bool eventFilter(QObject *watched, QEvent *event);

private:
    // 与游戏界面有关的全局变量
   struct Qxxl{

        QPixmap bmpBoard, bmpPieces[24];            // 游戏资源
        int sqSelected,  mvLast, pcCaptured ;       // 选中的格子
        unsigned char ucpcSquares[256];             // 棋盘数组
        MoveStruct mvsList[MAX_MOVES];              // 历史走法信息列表
        int nDistance, nMoveNum;                    // 距离根节点的步数，历史走法数
        bool bFlipped;                              // 是否翻转

        void SetIrrev(void) {                       // 清空(初始化)历史走法信息
            mvsList[0].Set(0, 0);
            nDistance = nMoveNum = 0;
        }

        void SaveMove(int mv, int pcCaptured){

            nDistance++;
            nMoveNum++;
            mvsList[nDistance].mv = mv;
            mvsList[nDistance].ucpcCaptured = pcCaptured;

        }

        int PreMove(int &mv, int &pcCaptured, int &sqSelected){

            if(nDistance == 0){
                mv = 0;
                pcCaptured = 0;
                sqSelected = 0;
                return 0;
            }

            mv = mvsList[nDistance].mv;
            pcCaptured = mvsList[nDistance].ucpcCaptured;
            nDistance --;

            sqSelected = SRC(mvsList[nDistance].mv);
            return mvsList[nDistance].mv;

        }

        void NextMove(int &mv){

            if(nDistance  == nMoveNum){
                mv = 0;
                return ;
            }

            nDistance++;
            mv = mvsList[nDistance].mv;

        }

    }Qxxl;

   static  ChessBoard * INSTANCE;
   explicit ChessBoard(QWidget *parent = 0);

   // "DrawSquare"参数
   const bool DRAW_SELECTED = true;
   bool isDemo;
   ChessPosition* chessPosition;
   ChessProtocol* chessProtocol;
   ChessEngine *chessEngine;
   QString FEN;
};

#endif // CHESSBOARD_H
