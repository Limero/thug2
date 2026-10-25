// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80137980-0x801379D4 (84B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
//
// Thin strcmp/strcpy wrapper that (re)initialises a 0x54-entry record at
// offset arg1<<4 + 0x2154 into the object: copies arg2's C string there if
// it differs from the stored one. The offset is materialised separately so
// ngccc emits addi-then-add (address association), matching the game.
// Suggested rename: UpdateStringField(arg0, idx, str).
#include "types.h"
int strcmp(const char *, const char *);
char *strcpy(char *, const char *);
void fn_80137980(s32 arg0, s32 arg1, void *arg2) {
    s32 temp_r31;
    s32 off;

    off = (arg1 << 4) + 0x2154;
    temp_r31 = arg0 + off;
    if (strcmp((char *)arg2, (char *)temp_r31) != 0) {
        strcpy((char *)temp_r31, (char *)arg2);
    }
}
