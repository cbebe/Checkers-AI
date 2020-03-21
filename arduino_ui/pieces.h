#ifndef __PIECES_H
#define __PIECES_H

#include <Arduino.h>
#include <MCUFRIEND_kbv.h>
#include "consts_types.h"

#include "touchs.h"
#include "move.h"

Piece findPiece(int8_t piecePos);
screenPos piecePosition(int8_t pos);

void choosePiece(selected& pieceSel, bool turn, moveSt& moves);
void highlightPiece(const Piece& piece);
void unhighlightPiece(const Piece& piece);
void drawPiece(const Piece& piece);
void adjTileOS(int8_t p, int8_t *os);
int8_t pieceIndex(int8_t pos);
tile board(int8_t pos);
#endif