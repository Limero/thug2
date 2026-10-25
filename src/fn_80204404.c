// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80204404-0x80204550 (332B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"

typedef union {
    __ps_t p[2];
    f32 f[4];
} V4_44;

typedef union {
    __ps_t p;
    f32 f[2];
} V2_44;

typedef union {
    f32 f;
    __ps_t p;
} Sc_44;

typedef struct {
    V2_44 f00;
    V2_44 f08;
    V2_44 f10;
    V2_44 f18;
    u8 pad20[0x88];
    void *ref;
    u8 padAC[0x14];
} Desc_44;

typedef struct {
    char pad0x0[0xC];
    Unk_1ECA8143 *unk0xC;
    char pad0x10[0x10];
    s32 unk0x20;
    s32 unk0x24;
    s32 unk0x28;
} Owner_44;

extern f32 lbl_802AEF6C;
extern char lbl_802AF000[];

void fn_8010794C(Desc_44 *p);
s32 fn_80107B20(void *p, s32 a, s32 b);
s32 fn_800DF004(s32 handle, char *name, Desc_44 *p);
void fn_80204550(V4_44 *out, Owner_44 *arg0, s32 i);
void CObject_RemoveRefLink(void *ref, void **slot);

void fn_80204404(Owner_44 *arg0) {
    Desc_44 obj;
    V4_44 vec[4];
    Sc_44 amp;
    register void **refp __asm__("r26");
    register V4_44 *v3 __asm__("r27");
    Desc_44 *p;
    Desc_44 *q;
    __ps_t bc;
    __ps_t t0;
    __ps_t t1;
    __ps_t s0;
    __ps_t s1;
    f32 sc;
    s32 i;

    if (arg0->unk0x24 > 0) {
        arg0->unk0x24 = arg0->unk0x24 - 1;
        return;
    }
    p = &obj;
    i = 0;
    fn_8010794C(p);
    v3 = &vec[3];
    refp = &obj.ref;
    sc = lbl_802AEF6C;
    vec[0].p[0] = arg0->unk0xC->unk0x58;
    vec[0].p[1] = arg0->unk0xC->unk0x60;
    q = p;
    for (; i < 8; i++) {        p = &obj;

        obj.f00.p = vec[0].p[0];
        q->f08.p = vec[0].p[1];
        amp.f = sc;
        fn_80204550(v3, arg0, i);
        bc = amp.p;
        t0 = __builtin_ps_muls0(vec[3].p[0], bc);
        vec[2].p[0] = t0;
        s0 = __builtin_ps_add(vec[0].p[0], t0);
        t1 = __builtin_ps_muls0(vec[3].p[1], bc);
        vec[2].p[1] = t1;
        s1 = __builtin_ps_add(vec[0].p[1], t1);
        vec[1].p[0] = s0;
        vec[1].p[1] = s1;
        obj.f10.p = s0;
        obj.f18.p = s1;
        if (fn_80107B20(q, 1, 0) != 0 &&
            fn_800DF004(arg0->unk0x28, lbl_802AF000, p) != 0) {
            arg0->unk0x24 = 10;
        }
    }
    if (obj.ref != 0) {
        CObject_RemoveRefLink(obj.ref, refp);
        obj.ref = 0;
    }
}
