#ifndef __PIECES_H
#define __PIECES_H

#include <Arduino.h>
#include <MCUFRIEND_kbv.h>
#include "consts_types.h"

#include "touchs.h"
#include "move.h"

#define PC_RAD 15 // piece radius

Piece findPiece(int8_t piecePos);
screenPos piecePosition(int8_t pos);

void choosePiece(selected& pieceSel);
void highlightPiece(Piece& piece);
void unhighlightPiece(Piece& piece);
void drawPiece(Piece& piece);
void test();

#endif