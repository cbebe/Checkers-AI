# I'M GETTING CONFUSED WITH ALL THE DEPENDENCIES

game_states.cpp

- bool menuScreen()
- void gameInit(bool start)
- win endCheck()
- void doTurn(bool turn)
- void game(bool start)

move.cpp

- validateCapture(Piece& piece, moveSt& moves, bool &chain)
- void captureCheck(Piece& piece, moveSt& moves, bool &chain)
- void emptyCheck(int8_t p, moveSt& moves)
- void moveCheck(Piece piece, moveSt& moves)
- moveSt findMove(Piece piece)
- bool hasMoves(moveSt moves)
- void markMove(int8_t pos)
- void showMoves(int8_t pos, moveSt& moves)
- bool pieceCanMove(int8_t piecePos, moveSt& moves)

pieces.cpp

- void adjTileOS(int8_t p, int8_t *os)
- int8_t touchPiece()
- void choosePiece(selected& pieceSel, bool turn)
- Piece findPiece(int8_t piecePos)
- screenPos piecePosition(int8_t pos)
- void clearTile(int8_t tileNum)
- void drawPiece(Piece& piece)
- void highlightPiece(Piece& piece)
- void unhighlightPiece(Piece& piece)
- int8_t pieceIndex(int8_t pos)
- void movePiece(int8_t oldPos, int8_t newPos)
