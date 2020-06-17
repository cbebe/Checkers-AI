// ---------------
// consts_types.h
// ---------------
// Contains all constants and type definitions
//

#ifndef _CONSTS_TYPES_H
#define _CONSTS_TYPES_H

#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>

#include "screenpos.h"
#include "Touch.h"

typedef enum win
{
  NONE,
  BOT_WIN,
  PLAYER_WIN,
  DRAW
} Win;

typedef enum selected
{
  NO_PIECE,
  PIECE,
  DONE
} Selected;

typedef enum piece_type
{
  EMPTY,
  PLAYER,
  BOT,
  PK,
  BK,
  OUT
} Piece;

// moves that can be made by a piece
typedef enum move
{
  NOT,
  MOVE,
  CAPTURE
} Move;

// struct to store moves in all 4 directions
struct move_st
{
  Move m[4]; // wrap move array in a struct
};

// defined constants
namespace c
{
  const uint8_t sd_cs = 10; // sd card pin

  const uint8_t num_pcs = 12; // pieces per player
  const uint8_t b_size = 32;  // board array size

  const uint8_t b_sq = 35;           // board square side length
  const uint16_t b_width = b_sq * 8; // board width

  const uint16_t b_dark = 19458;  // colours for game board
  const uint16_t b_light = 57113; // please change i don't like

  const uint8_t pc_rad = 15; // piece radius
  // board offsets
  const uint8_t off_x = 100;
  const uint8_t off_y = 10;
  // diagonal moves are constant
  const int8_t dg[] = {-9, -7, 7, 9};
  // empty move array
  const move_st empty_m = {{NOT, NOT, NOT, NOT}};

}; // namespace c

#endif