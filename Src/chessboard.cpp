#include <QSound>
#include <QPixmap>
#include <QBitmap>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPainter>
#include <QDateTime>
#include <QCoreApplication>
#include <QEventLoop>
#include "chessboard.h"
#include "chessbase.h"
#include "chesslog.h"
#include "gamesettings.h"

ChessBoard * ChessBoard::INSTANCE = 0;
ChessBoard * ChessBoard::instance(QWidget *parent)
{
    if(!INSTANCE)
    {
        INSTANCE = new ChessBoard(parent);
    }
    return INSTANCE;
}

ChessBoard::ChessBoard(QWidget *parent) : QWidget(parent), isDemo(false)
{
    chessPosition = ChessPosition::instance();
    chessProtocol = ChessProtocol::instance();
    chessEngine = ChessEngine::instance();

    /*************游戏资源和界面数据初始化*************/
    Init();
    StartUp();

    Chess_Trace("new ChessBoard");
}

ChessBoard::~ChessBoard()
{
    Chess_Trace("delete ChessBoard");
}

void ChessBoard::Init()
{
    resize(BOARD_WIDTH, BOARD_HEIGHT);
    move(/*1024 / 2 - 520 / 2*/ 50 , 100);

    /*************游戏资源和界面数据初始化*************/
    Qxxl.SetIrrev();

    // 加载游戏资源到内存
    Qxxl.bmpBoard.load(":/IDB_BOARD");

    //  将 士  象  马  车  炮  兵
    //  K  A  B   N   R  C   P
    //  8  9  10  11 12  13  14
    // 16 17  18  19 20  21  22
    Qxxl.bmpPieces[8].load(":/IDB_RK");
    Qxxl.bmpPieces[9].load(":/IDB_RA");
    Qxxl.bmpPieces[10].load(":/IDB_RB");
    Qxxl.bmpPieces[11].load(":/IDB_RN");
    Qxxl.bmpPieces[12].load(":/IDB_RR");
    Qxxl.bmpPieces[13].load(":/IDB_RC");
    Qxxl.bmpPieces[14].load(":/IDB_RP");
    Qxxl.bmpPieces[16].load(":/IDB_BK");
    Qxxl.bmpPieces[17].load(":/IDB_BA");
    Qxxl.bmpPieces[18].load(":/IDB_BB");
    Qxxl.bmpPieces[19].load(":/IDB_BN");
    Qxxl.bmpPieces[20].load(":/IDB_BR");
    Qxxl.bmpPieces[21].load(":/IDB_BC");
    Qxxl.bmpPieces[22].load(":/IDB_BP");
    Qxxl.bmpPieces[1].load(":/IDB_SELECTED");

    Qxxl.sqSelected = 0;
    Qxxl.mvLast = 0;
    Qxxl.pcCaptured = 0;
    Qxxl.bFlipped = false;

    this->isDemo = false;
    installEventFilter(this);
    repaint();
}

void ChessBoard::StartUp()
{
    chessPosition->ClearBoard();
    chessPosition->Startup();
    repaint();
}

void ChessBoard::paintEvent(QPaintEvent *)
{
    QPainter painter;

    // 绘制游戏界面
    painter.begin(this);

    // 绘制棋盘
    painter.drawPixmap(0, 0, BOARD_WIDTH, BOARD_HEIGHT, Qxxl.bmpBoard);
    // 确定棋子坐标，绘制棋子
    int sq;
    for(int row = ROW_TOP; row <= ROW_BOTTOM; row++){
        for(int col = COL_LEFT; col <= COL_RIGHT; col++){

            sq = COORD_XY(col, row);

            if(sq == Qxxl.sqSelected || sq == DST(Qxxl.mvLast))                 // 选中的格子或目标格子
            {
                DrawSquare(painter, sq, DRAW_SELECTED);                         // 绘制选中的棋子和选中图标
            }else
                DrawSquare(painter,sq);                                         // 绘制格子
            }
    }

    painter.end();
}

bool ChessBoard::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == this){

        if( (event->type() == QEvent::MouseButtonPress) || (event->type() == QEvent::MouseButtonDblClick) ){
            Chess_Info("QEvent::MouseButtonPress or QEvent::MouseButtonDblClick is Filtered");
            return true;
        }
    }
    return QWidget::eventFilter(watched, event);
}

void ChessBoard::mousePressEvent(QMouseEvent *click)
{
   // 鼠标点击的行列数
   int cClick = (click->x() - (BOARD_EDGE +  CLIENT_X) ) / SQUARE_SIZE + COL_LEFT;
   int rClick = (click->y() - (BOARD_EDGE + CLIENT_Y) ) / SQUARE_SIZE + ROW_TOP;

    // 转换成格子索引
    int sq = COORD_XY(cClick, rClick);                           // 点击的格子
    MousePress(sq);
}

void ChessBoard::OpenBoard(unsigned char *ucpcOpen) {            // 初始化棋盘
    chessPosition->OpenBoard(ucpcOpen);
    repaint();
}

void ChessBoard::DrawSquare(QPainter &painter, int sq, bool bSelected) {

    int pc, xx, yy;

    /*************读取象棋数据*************/
    pc =  isDemo? Qxxl.ucpcSquares[sq] : chessPosition->ucpcSquares[sq];               // 格子上的象棋

    // 翻转控制
    if(Qxxl.bFlipped){
        xx = BOARD_EDGE + (COL_FLIP( COL_X(sq) ) - COL_LEFT) * SQUARE_SIZE + CLIENT_X;
        yy = BOARD_EDGE + (ROW_FLIP( ROW_Y(sq) ) - ROW_TOP) * SQUARE_SIZE + CLIENT_Y;
    }else{
        xx = BOARD_EDGE + (COL_X(sq) - COL_LEFT) * SQUARE_SIZE + CLIENT_X;
        yy = BOARD_EDGE + (ROW_Y(sq) - ROW_TOP) * SQUARE_SIZE + CLIENT_Y;
    }

    if(0 != pc){

        QBitmap bmpPieceMask = Qxxl.bmpPieces[pc].createMaskFromColor(QColor(0,255,0));
        Qxxl.bmpPieces[pc].setMask(bmpPieceMask);
        painter.drawPixmap(xx, yy, SQUARE_SIZE, SQUARE_SIZE ,Qxxl.bmpPieces[pc]);
    }
    if(bSelected){

        QBitmap bmpSelectedMask = Qxxl.bmpPieces[bSelected].createMaskFromColor(QColor(0,255,0));
        Qxxl.bmpPieces[bSelected].setMask(bmpSelectedMask);
        painter.drawPixmap(xx, yy, SQUARE_SIZE, SQUARE_SIZE, Qxxl.bmpPieces[bSelected]);
    }
}

void ChessBoard::MousePress(int sq)
{
    if(isDemo){
        isDemo = false;
        Qxxl.mvLast = Qxxl.mvsList[Qxxl.nMoveNum].mv;
        Qxxl.sqSelected = SRC(Qxxl.mvLast);
        Qxxl.pcCaptured = Qxxl.mvsList[Qxxl.nMoveNum].ucpcCaptured;
        if(Qxxl.nDistance == 0){
            Qxxl.nDistance = Qxxl.nMoveNum;
            memcpy(Qxxl.ucpcSquares, chessPosition->ucpcSquares, 256);
        }

        emit SelectionStep(Qxxl.nMoveNum);
        repaint();
        return ;
    }

    sq = Qxxl.bFlipped ? SQUARE_FLIP(sq) : sq;                  // 实际操作的是翻转对象
    int pc = chessPosition->ucpcSquares[sq];                    // 点击的棋子， 0表示无棋
    if((pc & SIDE_TAG(chessPosition->sdPlayer)) != RED){        // 红方或黑方走棋子

        Qxxl.mvLast = 0;                                        // 清除上一步走法
        Qxxl.sqSelected = sq;                                   // 记录选中的棋子
        repaint();                                              // 立即更新画面
        QSound::play(":/IDR_CLICK");

    } else if (Qxxl.sqSelected != 0) {                          // 已选中状态, sqSelected为上次选中的格子
        // 如果点击的不是自己的子，但有子选中了(一定是自己的子)，那么走这个子
        int mv = MOVE(Qxxl.sqSelected, sq);                     // 获得走法
        // 走法检测
        if (chessPosition->LegalMove(mv)) {

            int pcCaptured = chessPosition->MovePiece(mv);
            if(chessPosition->Checked()){               // 将军检测

                Chess_Error("错误走法！");
                QSound::play(":/IDR_ILLEGAL"); // 播放被将军的声音
                chessPosition->UndoMovePiece(mv, pc);
                return ;
            }

            this->ShowChinessStep(mv);
            this->SaveMove(mv, pcCaptured);

            chessPosition->ChangeSide();
            FEN = chessProtocol->ArrayToFEN(chessPosition->ucpcSquares, chessPosition->sdPlayer);
            Chess_Debug(FEN);

            repaint();                                               // 立即更新画面

            if (chessPosition->IsMate()) {

                chessPosition->ChangeSide();
                // 如果分出胜负，那么播放胜负的声音，并且弹出不带声音的提示框
                QSound::play(":/IDR_WIN");
                if(chessPosition->sdPlayer)
                    QMessageBox::information(this, "比赛结果", "祝贺黑方取得胜利！");
                else
                    QMessageBox::information(this, "比赛结果", "祝贺红方取得胜利！");
                installEventFilter(this);

            } else {
                // 如果没有分出胜负，那么播放将军、吃子或一般走子的声音
                QSound::play(chessPosition->Checked() ? ":/IDR_CHECK" : pc != 0 ? ":/IDR_CAPTURE" : ":/IDR_MOVE");
            }

            // 人人、人机、机机  0、1、2     轮到谁走， 0 = 红方， 1 = 黑方
            if(g_gameSettings.GetGameType() == 1){

                removeEventFilter(this);
                if(chessPosition->sdPlayer == g_gameSettings.GetCompetitorSide()){       // 对手
                    Computer0Think();
                }

            }else if(g_gameSettings.GetGameType() == 2){

                removeEventFilter(this);
                if(chessPosition->sdPlayer == RED){
                   Computer0Think();
                }else{
                   Computer1Think();
                }
            }

            repaint();                                               // 立即更新画面
            // 如果根本就不符合走法(例如马不走日字)，那么程序不予理会
        }
    }
}

void ChessBoard::StartGame()
{
    removeEventFilter(this);

    chessPosition->sdPlayer = g_gameSettings.GetAhead();
    FEN = chessProtocol->ArrayToFEN(chessPosition->ucpcSquares, chessPosition->sdPlayer);
    Chess_Debug(FEN);

    if(g_gameSettings.GetGameType() == 1){

        if(g_gameSettings.GetCompetitorSide() == chessPosition->sdPlayer){
                Computer0Think();
        }

    }else if(g_gameSettings.GetGameType() == 2){
        Computer0Think();
    }
}

void ChessBoard::SaveMove(int mv, int pcCaptured)
{
    Qxxl.mvLast = mv;                                        // 记录上一步走法
    Qxxl.pcCaptured = pcCaptured;

    Qxxl.SaveMove(Qxxl.mvLast, Qxxl.pcCaptured);
    memcpy(Qxxl.ucpcSquares, chessPosition->ucpcSquares, 256);
}

void ChessBoard::StartMove()
{
    for(int i = Qxxl.nDistance; i != 0; i--){
        PreMove();
        Sleep(1000);
    }

}

void ChessBoard::EndMove()
{
    for(int i = Qxxl.nDistance; i != Qxxl.nMoveNum; i++){
        NextMove();
        Sleep(1000);
    }
}

void ChessBoard::PreMove()
{
    isDemo = true;

    int preMove = Qxxl.PreMove(Qxxl.mvLast, Qxxl.pcCaptured, Qxxl.sqSelected);
    emit SelectionStep(Qxxl.nDistance);

    if(Qxxl.mvLast){    

        int sqSrc, sqDst, pc;
        sqSrc = SRC(Qxxl.mvLast);
        sqDst = DST(Qxxl.mvLast);
        pc = Qxxl.ucpcSquares[sqDst];               // 保存目标位置的棋子
        if(pc == Qxxl.pcCaptured){

            Qxxl.ucpcSquares[sqDst] = 0;                // 从棋盘上拿走一枚棋子

        }else{

            Qxxl.ucpcSquares[sqDst] = Qxxl.pcCaptured;

        }
        Qxxl.ucpcSquares[sqSrc] = pc;
        Qxxl.mvLast = preMove;
        QSound::play(":/IDR_MOVE");

        repaint();
    }
}

void ChessBoard::NextMove()
{
    isDemo = true;

    Qxxl.NextMove(Qxxl.mvLast);
    emit SelectionStep(Qxxl.nDistance);

    if(Qxxl.mvLast){
        Qxxl.sqSelected =  SRC(Qxxl.mvLast);
        int sqSrc, sqDst, pc;
        sqSrc = SRC(Qxxl.mvLast);
        sqDst = DST(Qxxl.mvLast);
        Qxxl.pcCaptured = Qxxl.ucpcSquares[sqDst];
        Qxxl.ucpcSquares[sqDst] = 0;                   // 从棋盘上拿走一枚棋子
        pc = Qxxl.ucpcSquares[sqSrc];
        Qxxl.ucpcSquares[sqSrc] = 0;                       // 从棋盘上拿走一枚棋子
        Qxxl.ucpcSquares[sqDst] = pc;                      // 在棋盘上放一枚棋子
        QSound::play(Qxxl.pcCaptured != 0 ? ":/IDR_CAPTURE" : ":/IDR_MOVE");
        repaint();
    }
}

// 撤销走法
void ChessBoard::UndoMove()
{
    /****************撤销一步棋**************/
    // 撤销已保存的走法， 界面与数据保持同步
    if(Qxxl.mvLast){

        // 更改棋盘结构状态
        chessPosition->UndoMovePiece(Qxxl.mvLast, Qxxl.pcCaptured);
        chessPosition->ChangeSide();
        // 清除走法痕迹
        Qxxl.mvLast = 0;
        Qxxl.sqSelected = 0;
        Qxxl.pcCaptured = 0;
        // 清除走法列表条目
        emit ClearLastStep();
        // 如果没有分出胜负，那么播放将军、吃子或一般走子的声音
        QSound::play(":/IDR_MOVE");
        repaint();

    }
}

void ChessBoard::FlipBoard()
{
    Qxxl.bFlipped = !Qxxl.bFlipped;
    repaint();
}

// 计算机0走棋
void ChessBoard::Computer0Think()
{
    installEventFilter(this);
    FEN = chessProtocol->ArrayToFEN(chessPosition->ucpcSquares, chessPosition->sdPlayer);
    chessEngine->Read(0, FEN.toStdString().c_str());
}

// 计算机1走棋
void ChessBoard::Computer1Think()
{
    installEventFilter(this);
    FEN = chessProtocol->ArrayToFEN(chessPosition->ucpcSquares, chessPosition->sdPlayer);
    chessEngine->Read(0, FEN.toStdString().c_str());
}

void ChessBoard::ShowChinessStep(int mv)
{
    QString alphaFmt,chineseFmt;
    chessProtocol->GetMoveStepAlpha(mv, alphaFmt);
    Chess_Debug(alphaFmt);

    chessProtocol->AlphaFmtToChiness(alphaFmt, chineseFmt, chessPosition->sdPlayer == BLACK);
    Chess_Debug(chineseFmt);
    emit SetStepList(chineseFmt);
}

void ChessBoard::Write(QString bestmove)
{
    int mv, from, to;
    Chess_Debug(bestmove);
    mv = chessProtocol->Move(bestmove.toStdString().c_str());

    if(Qxxl.bFlipped){
        from = SQUARE_FLIP(SRC(mv));
        to = SQUARE_FLIP(DST(mv));
    }else{
        from = SRC(mv);
        to = DST(mv);
    }

    MousePress(from);
    MousePress(to);
}

void ChessBoard::Sleep(unsigned int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
