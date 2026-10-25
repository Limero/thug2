// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801CBA64-0x801CBB24 (192B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
typedef struct {
    char _0[0x4];
    s32 unk4;
    char _8[0x10];
    s32 unk18;
    s32 unk1C;
    char _20[0xAC0 - 0x20];
    s32 unkAC0;
    char _AC4[0x730];
    s32 unk11F4;
} CBA64;
extern void fn_8009F53C(CBA64 *);
extern void fn_801CD118(void *);
extern void fn_801CD190(void *);
extern void *memset(void *, s32, s32);
extern char lbl_802AD200[];
void *fn_801CBA64(CBA64 *arg0) {
    register s32 cnt __asm__("r29");
    char *p;
    char *base1;
    char *base2;

    cnt = 0x13;
    p = (char *)arg0 + 0x20;
    fn_8009F53C(arg0);
    arg0->unk18 = (s32)lbl_802AD200;
    do {
        fn_801CD118(p);
        p += 0x88;
    } while (--cnt != -1);
    p = (char *)arg0 + 0xAC4;
    cnt = 0x13;
    base2 = p;
    base1 = (char *)arg0 + 0x20;
    do {
        fn_801CD190(p);
        p += 0x5C;
    } while (--cnt != -1);
    arg0->unk11F4 = 0;
    arg0->unk1C = 0;
    arg0->unk4 = QB_SKATERSTATEHISTORY;
    arg0->unkAC0 = 0;
    memset(base1, 0, 0xAA0);
    memset(base2, 0, 0x730);
    return arg0;
}
