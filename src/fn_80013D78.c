// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80013D78-0x80013DB0 (56B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
typedef struct {
    s32 unk0x00; s32 unk0x04; s32 unk0x08; s32 unk0x0C;
    char _pad[0x2330];
    s32 unk0x2340; s32 unk0x2344; s32 unk0x2348; s32 unk0x234C;
    s32 unk0x2350; s32 unk0x2354;
} T13D78;
extern char lbl_802909B0[];
void *fn_80013D78(void *arg0) {
    T13D78 *p = (T13D78 *)arg0;
    p->unk0x2354 = (s32)lbl_802909B0;
    p->unk0x08 = 0;
    p->unk0x0C = 0;
    p->unk0x04 = 0;
    p->unk0x2340 = 0;
    p->unk0x2348 = 0;
    p->unk0x2344 = 0;
    p->unk0x234C = 0;
    p->unk0x2350 = 0;
    return arg0;
}
