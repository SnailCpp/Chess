#ifndef CHESSPOSITION_H
#define CHESSPOSITION_H

#include "chessbase.h"

/***************************象棋局面表示***************************/
// 局面信息结构
class ChessPosition{

public:
    static ChessPosition* instance();
    ~ChessPosition();

    void ClearBoard(void);                      // 清空棋盘
    void OpenBoard(unsigned char *ucpcOpen);    // 打开棋盘
    void Startup();                             // 游戏启动
    void ChangeSide(void);                      // 切换走方
    int MovePiece(int mv);                      // 移动棋子
    void UndoMovePiece(int mv, int pcCaptured); // 撤销棋子
    void AddPiece(int sq, int pc);              // 添加棋子
    void DelPiece(int sq);                      // 移除棋子
    int GenerateMoves(int *mvs) const;          // 生成所有走法
    bool Checked() const;                       // 判断是否被将军
    bool IsMate(void);                          // 判断是否被杀
    bool LegalMove(int mv) const;               // 判断走法是否合理
    int sdPlayer;                               // 轮到谁走， 0 = 红方， 1 = 黑方
    unsigned char ucpcSquares[256];             // 棋盘数组

private:
    explicit ChessPosition();
    static ChessPosition* INSTANCE;
};

#endif // CHESSPOSITION_H
