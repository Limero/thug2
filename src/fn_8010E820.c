// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8010E820-0x8010E958 (312B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 *fn_80125388(s32 *);
void fn_801252BC(Unk_5D1D68CC *);

bool ScriptTest(CStruct *pParams, CScript *pScript) {
    struct {
        s32 w[5];
        s32 gap;
        s32 v[4];
    } l;
    char *cp;
    char *p31;
    char *cq;
    s32 ctr;
    union {
        u32 w;
        struct { u32 pad:9; u32 fld:7; u32 rest:16; } b;
    } u;

    p31 = (char *)&l.v[0];
    fn_80125388(&l.w[0]);
    cp = (char *)&l.w[0];
    ctr = 0x14;
    do {
        *cp = 0;
        cp += 1;
        ctr -= 1;
    } while (ctr != 0);
    *(u32 *)&l.w[0] = (*(u32 *)&l.w[0] & QB_UNKNOWN_0xFF3FFFFF) | 0x200000;
    l.w[1] = QB_UNKNOWN_0xC1C935B2;
    *(u8 *)((char *)&l.w[0] + 2) = 0xA;
    ctr = 0x14;
    do {
        ctr -= 1;
    } while (ctr != 0);
    *(volatile u32 *)&l.w[0] |= 0x800000;
    ctr = 0x14;
    do {
        ctr -= 1;
    } while (ctr != 0);
    *(volatile u32 *)&l.w[0] |= 0x400000;
    ctr = 0x14;
    do {
        ctr -= 1;
    } while (ctr != 0);
    *(volatile u32 *)&l.w[0] &= QB_UNKNOWN_0xFFDFFFFF;
    fn_801252BC(p31);
    cq = p31;
    ctr = 0x10;
    do {
        *cq = 0;
        cq += 1;
        ctr -= 1;
    } while (ctr != 0);
    u.w = *(u32 *)&l.v[0] | 0x800000;
    u.b.fld = 0x2B;
    *(u32 *)&l.v[0] = u.w;
    *(u16 *)((char *)&l.v[0] + 2) = 0x3E8;
    l.v[1] = QB_UNKNOWN_0x480A2607;
    l.v[2] = QB_UNKNOWN_0x01020304;
    ctr = 0x10;
    do {
        ctr -= 1;
    } while (ctr != 0);
    l.v[2] = 0;
    *(volatile u32 *)&l.v[0] &= QB_UNKNOWN_0xFF7FFFFF;
    *(u16 *)((char *)&l.v[0] + 2) = 0;
    return true;
}
