// range 0x8000B0A0-0x8000B0BC (28B). Byte-identical.
// Identification: guarded singleton setter. If the "enabled" flag
// (lbl_802FFE68) is set to exactly 1, store the argument to lbl_802FFE70;
// otherwise do nothing. Reads and writes go through two separate .data
// globals, reproduced with a plain (non-volatile) address.
#include "types.h"
extern bool lbl_802FFE68;
extern s32 lbl_802FFE70;
void fn_8000B0A0(s32 v) {
    if (lbl_802FFE68 != 1) return;
    lbl_802FFE70 = v;
}