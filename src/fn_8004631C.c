// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8004631C-0x80046440 (292B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern char lbl_80301A38[];

/* self: array of 32-byte-strided element records (idx<<5); the record's ref-link
   sits at +0x190 and the 16-byte PS payload block at +0x1A0. */
typedef struct {
    char _000[0x190];
    s32 unk190;
    char _194[0xC];
    char _1A0[0x10];
    char _1B0[0x300];
    s32 unk4B0;
} S4631C_t;

/* obj->+8 is a descriptor whose +0x48 is a signed 16-bit method offset and
   +0x4C the entry point. */
typedef struct {
    char _0[0x48];
    s16 off;
    s16 _p;
    void *fn;
} Vt4631C_t;

void Script_RunScript(s32, s32, s32, s32, s32);
void CObject_AddRefLink(void *, void *);
void CObject_RemoveRefLink(void *, void *);
s32 fn_800A1A84(s32, s32);

void fn_8004631C(S4631C_t *arg0, void *arg1, s32 arg2) {
    s32 idx;
    s32 newl;
    s32 ga;
    s32 *link;
    s32 old;

    idx = arg0->unk4B0;
    ga = *(s32 *)&lbl_80301A38;
    __asm__("" : "+r"(ga));
    newl = fn_800A1A84(ga, arg1);

    link = (s32 *)((idx << 5) + (s32)arg0);
    link = (s32 *)((char *)link + 0x190);
    old = *link;

    if (old != 0) {
        CObject_RemoveRefLink(old, link);
        *link = 0;
    }
    *link = newl;
    if (newl != 0) {
        CObject_AddRefLink(newl, link);
    }
    Script_RunScript(QB_ELEMENT3D_ADD_COMPONENTS, (s32)arg1,
                    *(s32 *)((arg0->unk4B0 << 5) + (s32)arg0 + 0x190), 0, 0);
    {
        void *obj = *(s32 *)((arg0->unk4B0 << 5) + (s32)arg0 + 0x190);
        Vt4631C_t *vt = *(Vt4631C_t **)((char *)obj + 8);

        ((void (*)(void *))vt->fn)(obj + vt->off);
    }
    Script_RunScript(QB_ELEMENT3D_INIT_MODEL, (s32)arg1,
                    *(s32 *)((arg0->unk4B0 << 5) + (s32)arg0 + 0x190), 0, 0);
    {
        char *dp = (char *)((arg0->unk4B0 << 5) + (s32)arg0);
        volatile __ps_t *d;

        dp += 0x1A0;
        d = (volatile __ps_t *)dp;
        d[0] = *(volatile __ps_t *)arg2;
        d[1] = *(volatile __ps_t *)(arg2 + 8);
    }
    arg0->unk4B0 = arg0->unk4B0 + 1;
}
