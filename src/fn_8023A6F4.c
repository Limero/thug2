// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8023A6F4-0x8023A7B8 (196B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

void *fn_8023F778(s32);

typedef struct A6F4Grid {
    u8 offRow;          /* 0 */
    u8 pad1;            /* 1 */
    u8 offCol;          /* 2 */
    u8 rows;            /* 3 */
    u8 pad4;            /* 4 */
    u8 cols;            /* 5 */
} A6F4Grid;

void fn_8023A6F4(s32 arg0, A6F4Grid *arg1) {
    s32 row;
    s32 col;
    register s32 lim __asm__("r9");

    row = 0;
    while (row < arg1->rows) {
        col = 0;
        if (col < arg1->cols) {
            do {
                char *base;
                s32 off;
                void *node;

                node = fn_8023F778(0x10);
                *(s32 *)((char *)node + 8) = (s32)arg1;
                base = (char *)arg0 + 0x90;
                off = (col + arg1->offCol) * 4 + (row + arg1->offRow) * 0xE8;
                *(s32 *)((char *)node + 0xC) = *(s32 *)(base + off);
                off = (col + arg1->offCol) * 4 + (row + arg1->offRow) * 0xE8;
                *(s32 *)(base + off) = (s32)node;
                col += 1;
                lim = arg1->cols;
            } while (col < lim);
        }
        row += 1;
    }
}
