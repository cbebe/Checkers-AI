#ifndef __PIECES_H
#define __PIECES_H

#include <Arduino.h>
#include <MCUFRIEND_kbv.h>
#include "consts_types.h"

Piece findPiece(int8_t piecePos);

void highlightPiece(Piece piece);
void drawPiece(Piece piece);

#endif