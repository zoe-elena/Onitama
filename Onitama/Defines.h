#pragma once

#define DEFINES_H
#define BOARDSIZE 5
#define CARDS 1
#define PLAYERS 2
#define STUDENTS 4
#define MASTER 1
#define TEMPLEREDX BOARDSIZE / 2
#define TEMPLEREDY 0
#define TEMPLEBLUEX BOARDSIZE / 2
#define TEMPLEBLUEY BOARDSIZE - 1

enum class E_PLAYERCOLOR { none, red, blue };
enum class E_PIECETYPE { none, master, student };
enum class E_CARDTYPE { none, debug };
enum class E_CARDPOSITIONS { none, topLeft, topRight, sideRight, lowRight, lowLeft, sideLeft };

#define TILESIZE 100
#define TILEPADDING 10
#define SIDEPANELWIDTH 250
#define CARDPANELHEIGHT 150
#define WINDOWLENGTHSIZE CARDPANELHEIGHT * 2 + TILESIZE * BOARDSIZE + 2 * TILEPADDING + (BOARDSIZE - 1) * TILEPADDING
#define WINDOWWIDTHSIZE SIDEPANELWIDTH * 2 + TILESIZE * BOARDSIZE + 2 * TILEPADDING + (BOARDSIZE - 1) * TILEPADDING
#define CARDWIDTH TILESIZE * 2 + TILEPADDING * 2 + (TILESIZE - TILEPADDING * 2) / 2
#define CARDHEIGHT CARDPANELHEIGHT - TILEPADDING * 2

// TODO: Render Temple after highlighted Tile

// TODO: What happends if no move possible
