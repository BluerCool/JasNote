#pragma once
#include <QString>

namespace S {

// ── Window ──────────────────────────────────────────────
inline int    WIN_MIN_W         = 900;
inline int    WIN_MIN_H         = 600;
inline int    WIN_DEFAULT_W     = 1100;
inline int    WIN_DEFAULT_H     = 750;
inline double WIN_OPACITY       = 0.25;
inline int    WIN_RADIUS        = 16;
inline int    WIN_LAYOUT_MARGIN = 16;
inline int    WIN_BORDER_WIDTH  = 2;
inline int    WIN_BORDER_ALPHA_BASE = 153;

inline int    BG1_R = 18, BG1_G = 22, BG1_B = 30;
inline int    BG2_R = 22, BG2_G = 28, BG2_B = 38;
inline int    BG3_R = 16, BG3_G = 20, BG3_B = 28;

// ── Status Bar (bottom-left label) ──────────────────────
inline int    STATUS_FONT_SIZE      = 15;
inline QString STATUS_FONT          = "Cascadia Code, Fira Code, monospace";
inline QString STATUS_COLOR         = "black";
inline QString STATUS_MODIFIED      = "#ff6b9d";
inline int    STATUS_MODIFIED_SIZE  = 18;
inline int    STATUS_X              = 20;
inline int    STATUS_Y_OFFSET       = 36;
inline int    STATUS_W              = 500;
inline int    STATUS_H              = 20;
inline int    STATUS_MARGIN_LEFT    = 4;

// ── Editor ──────────────────────────────────────────────
inline int    ED_FONT_SIZE    = 14;
inline QString ED_FONT        = "Cascadia Code, Fira Code, JetBrains Mono, monospace";
inline QString ED_COLOR       = "#d4d4dc";
inline QString ED_SEL_BG      = "#2a6f6f";
inline int    ED_PADDING      = 16;
inline int    ED_TAB_STOP     = 40;
inline int    ED_AUTOSAVE_MS  = 800;

// ── Glass Dialog ────────────────────────────────────────
inline int    DLG_W           = 440;
inline int    DLG_H           = 180;
inline int    DLG_BG_ALPHA    = 242;
inline int    DLG_RADIUS      = 16;
inline int    DLG_BORDER_ALPHA= 160;
inline int    DLG_BORDER_W    = 2;
inline int    DLG_ML = 28, DLG_MT = 24, DLG_MR = 28, DLG_MB = 20;
inline QString DLG_TITLE_COLOR = "#d4d4dc";
inline int    DLG_TITLE_SIZE  = 15;

// ── Dialog Buttons ──────────────────────────────────────
inline int    BTN_W           = 110;
inline int    BTN_H           = 34;
inline int    BTN_RADIUS      = 8;
inline int    BTN_FONT_SIZE   = 13;
inline QString BTN_COLOR      = "#d4d4dc";
inline QString BTN_CANCEL_BG    = "rgba(255,255,255,0.06)";
inline QString BTN_CANCEL_HOVER = "rgba(255,255,255,0.12)";
inline QString BTN_DONTSAVE_BG    = "rgba(200,60,60,0.35)";
inline QString BTN_DONTSAVE_HOVER = "rgba(200,60,60,0.55)";
inline QString BTN_SAVE_BG    = "rgba(78,201,176,0.3)";
inline QString BTN_SAVE_HOVER = "rgba(78,201,176,0.5)";

// ── Title Bar (Windows only) ────────────────────────────
inline int    TB_HEIGHT        = 36;
inline QString TB_TITLE        = "JasNote";
inline QString TB_FONT         = "Cascadia Code, Fira Code, monospace";
inline int    TB_FONT_SIZE     = 13;
inline QString TB_COLOR        = "rgba(255,255,255,0.7)";
inline int    TB_BTN_SIZE      = 36;
inline int    TB_BTN_FONT      = 14;
inline QString TB_BTN_COLOR    = "rgba(255,255,255,0.6)";
inline QString TB_BTN_HOVER    = "rgba(255,255,255,0.1)";
inline QString TB_BTN_CLOSE_HOVER = "rgba(220,50,50,0.8)";

} // namespace S

void loadConfig();
