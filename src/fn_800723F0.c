// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800723F0-0x8007257C (396B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_802953DC[];
extern char lbl_80295404[];
extern char lbl_80295414[];
extern char lbl_80295460[];
extern char lbl_802954AC[];
extern int sprintf(char *dst, const char *fmt, ...);
extern void OSVReport(const char *msg, s32 arg);
extern s32 MemAvailable(Unk_C8FEE62D *h);

typedef struct MemHeap {
    s32 unk0x0;
    s32 unk0x4;
    s32 nblocks;
    char pad0xC[0x14];
    s32 used;
    s32 peak;
    s32 unk0x28;
    s32 frag;
    s32 unk0x30;
    Unk_C8FEE62D *sub;
    s32 unk0x38;
    s32 unk0x3C;
    s32 unk0x40;
    char *name;
} MemHeap;

extern MemHeap **lbl_802FFE98;
extern MemHeap *fn_8000FA54(MemHeap **);
extern MemHeap *fn_8000FA70(MemHeap **, MemHeap *);

void fn_800723F0(s32 arg0, char *arg1) {
    char buf[128];
    MemHeap **g;
    MemHeap *cur;

    g = lbl_802FFE98;
    if (arg0 > 0) {
        sprintf(buf, lbl_802953DC, arg0, arg1);
        OSVReport(buf, 0);
    } else if (arg0 == -1) {
        sprintf(buf, lbl_80295404, arg1);
        OSVReport(buf, 0);
    }
    OSVReport(lbl_80295414, 0);
    OSVReport(lbl_80295460, 0);
    for (cur = fn_8000FA54(g); cur != NULL; cur = fn_8000FA70(g, cur)) {
        Unk_C8FEE62D *hi = cur->sub;
        char *nm = cur->name;
        s32 availK = MemAvailable(hi) / 1024;
        s32 minK = hi->unk0x8 / 1024;
        s32 sizeK = (hi->unk0xC - hi->unk0x4) / 1024;

        sprintf(buf, lbl_802954AC, nm, cur->peak / 1024, cur->used / 1024,
                cur->frag / 1024, availK, minK, cur->nblocks, sizeK);
        OSVReport(buf, 0);
    }
}
