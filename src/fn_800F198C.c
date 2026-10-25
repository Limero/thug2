// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F198C-0x800F1A3C (176B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 fn_80129528(CStruct *, s32);

typedef union {
    struct {
        u16 idx;
        s16 arg;
    } h;
    s32 raw;
} F198C_ENT;

typedef struct {
    CStruct *node;
    char pad[8];
} F198C_TBL;

typedef struct __attribute__((packed)) {
    char f0[2];
    F198C_ENT ent[0x4000];
    F198C_ENT found;
    char pad2[0xA];
    F198C_TBL tbl[0x4000];
} F198C_S;

void fn_800F198C(F198C_S *arg0, s32 arg1) {
    s32 sp8;
    s32 idx;
    s32 off;
    s32 t;
    u16 k;
    s16 v;
    s32 zero;
    s32 *outp;
    char *kp;
    char *ap;
    register char *hp __asm__("r9");
    register char *hq __asm__("r23");
    F198C_TBL *tbl;

    hp = (char *)arg0 + 0x10000;
    arg0->found.h.idx = 0;
    arg0->found.h.arg = 0;
    if (arg1 != 0) {
        hq = hp;
        kp = (char *)&arg0->ent[0];
        tbl = (F198C_TBL *)(hq + 0x10);
        ap = (char *)&arg0->ent[0].h.arg;
        idx = arg1 & 0x3FFF;
        outp = &sp8;
        zero = 0;
    loop:
        off = idx * 4;
        k = *(u16 *)(kp + off);
        v = *(s16 *)(ap + off);
        t = fn_80129528(tbl[k].node, v);
        sp8 = zero;
        GetChecksum_2((CStruct *)t, QB_NAME, outp, 1);
        if (sp8 == arg1) goto out;
        idx = (idx + 1) & 0x3FFF;
        goto loop;
    out:
        *(s32 *)(hq + 2) = *(s32 *)((char *)arg0 + 2 + off);
    }
}
