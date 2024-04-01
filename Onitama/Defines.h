#pragma once

#define DEFINES_H
#define BOARDSIZE 5
#define CARDS 5
#define CARDSLOTS 6
#define PLAYERS 2
#define STUDENTS 4
#define MASTER 1
#define PIECECOUNT (STUDENTS + MASTER)
#define TEMPLEREDX (BOARDSIZE / 2)
#define TEMPLEREDY 0
#define TEMPLEBLUEX (BOARDSIZE / 2)
#define TEMPLEBLUEY (BOARDSIZE - 1)

enum class E_PLAYERCOLOR { none, red, blue };
enum class E_PIECETYPE { none, master, student };
enum class E_CARDTYPE { none, mantis, dragon, ox, horse, rabbit };
enum class E_CARDPOSITIONTYPE { none, sideLeft, topLeft, topRight, sideRight, bottomRight, bottomLeft };

#define TILESIZE 100
#define TILEPADDING 10
#define CARDWIDTH 260
#define CARDHEIGHT 130
#define SIDEPANELWIDTH (CARDWIDTH + TILEPADDING * 2)
#define CARDPANELHEIGHT (CARDHEIGHT + TILEPADDING * 2)
#define WINDOWLENGTHSIZE (CARDPANELHEIGHT * 2 + TILESIZE * BOARDSIZE + 2 * TILEPADDING + (BOARDSIZE - 1) * TILEPADDING)
#define WINDOWWIDTHSIZE (SIDEPANELWIDTH * 2 + TILESIZE * BOARDSIZE + 2 * TILEPADDING + (BOARDSIZE - 1) * TILEPADDING)

//TODO: Replace #define with precomputed const?
