#pragma once

#define DEFINES_H
// Game variables
constexpr int BOARDSIZE = 5;
constexpr int CARDS = 5;
constexpr int  CARDSLOTS = 6;
constexpr int  PLAYERS = 2;
constexpr int  STUDENTS = 4;
constexpr int  MASTER = 1;
constexpr int  PIECECOUNT = STUDENTS + MASTER;
constexpr int  TEMPLEREDX = BOARDSIZE / 2;
constexpr int  TEMPLEREDY = 0;
constexpr int  TEMPLEBLUEX = BOARDSIZE / 2;
constexpr int  TEMPLEBLUEY = BOARDSIZE - 1;

// Render varibles
constexpr int  TILESIZE = 100;
constexpr int  TILEPADDING = 10;
constexpr int  CARDWIDTH = 260;
constexpr int  CARDHEIGHT = 130;
constexpr int  SIDEPANELWIDTH = CARDWIDTH + TILEPADDING * 2;
constexpr int  CARDPANELHEIGHT = CARDHEIGHT + TILEPADDING * 2;
constexpr int  WINDOWWIDTH = SIDEPANELWIDTH * 2 + TILESIZE * BOARDSIZE + 2 * TILEPADDING + (BOARDSIZE - 1) * TILEPADDING;
constexpr int  WINDOWLENGTH = CARDPANELHEIGHT * 2 + TILESIZE * BOARDSIZE + 2 * TILEPADDING + (BOARDSIZE - 1) * TILEPADDING;

// Card collision varibles
constexpr int LEFTCARDX = SIDEPANELWIDTH + TILEPADDING;
constexpr int RIGHTCARDX = LEFTCARDX + CARDWIDTH + TILEPADDING * 2;
constexpr int SIDECARDY = (WINDOWLENGTH - CARDHEIGHT) / 2;
constexpr int SIDECARDRIGHTX = RIGHTCARDX + CARDWIDTH + TILEPADDING;
constexpr int TOPCARDSY = TILEPADDING;
constexpr int BOTTOMCARDSY = TILEPADDING * 4 + CARDHEIGHT + BOARDSIZE * TILESIZE + BOARDSIZE * TILEPADDING;
constexpr int SIDECARDLEFTX = TILEPADDING;

enum class E_PLAYERCOLOR { none, red, blue };
enum class E_PIECETYPE { none, master, student };
enum class E_CARDTYPE { none, mantis, dragon, ox, horse, rabbit };
enum class E_CARDPOSITIONTYPE { none, sideLeft, topLeft, topRight, sideRight, bottomRight, bottomLeft };
