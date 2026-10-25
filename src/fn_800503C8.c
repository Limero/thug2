// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800503C8-0x80050428 (96B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
typedef struct {
    s32 w[6];
} S24;
void fn_80050428(char *, s32);
void fn_800503C8(Unk_9C33C03C *arg0, Unk_DB0E2BAB *arg1, s32 arg2) {
    *(S24 *) ((char *) arg0 + 0x480) = *(S24 *) arg1;
    fn_80050428((char *) arg0, arg2);
}
