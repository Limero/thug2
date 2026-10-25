// UPDATED 2026-08-29: WA-split applied (f78c call-spec pattern, +45 words,
// now 53.3% masked vs ~26%).
// WIP DRAFT (non-matching) — hand rebuild from disasm
// family=m2c range=0x8023E9D0-0x8023EC64 size=660B
// PARKED ~26%: allocator home-order wall (same class as fn_8023E724 this
// round). Want homes {arg0:r31, arg1:r30->recycled mgr/v2, arg2:r29->recycled
// v1, argp:r28, &sp8-web:r27 born prologue}; pins fix argp/sp8p but the rest
// of the cascade (sp10p web, v1/v2 recycling into freed arg regs, block
// placement of the shared *p=v2 store tail) resists. Semantics fully decoded:
// e724 pre/post calls, sp8 snapshot {w@+4,h@+8} taken BEFORE byte += mods,
// byte adds via fn_80240B2C(arg0+4,{0,2}), type==5 mgr branch (45094 store +
// 0x6B byte copy / zero-store via kept-live reg), else-arm min(v1,v2) of two
// fn_8023821C calls (first reads CURRENT arg0 fields, second reads the
// PRE-MOD snapshot), then (u32)(type-2)<=1 block: 37D14→43318→[4336C→432A0→
// 416F8 chain]→38C40, 0x6C-byte Ent108 struct assign to arg0+0x78,
// EDE4(mode 2/3), 394F8 both arms, 43320(&sp18,2).
// NOTE: zero-path shares want's [bl; b] into the common stb tail via goto.
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// SEARCHED 2026-09-11 (tools/store_order_search.py): store/assignment block(s) re-ordered (reversed / ascending / descending); score now 53.9% ([1]rev->53.9%).
#include "types.h"
#include "structs.h"
void fn_8023E724(CStruct * arg0);
void *fn_80240B2C(void *arg0, s32 arg1);
s32 fn_80245094(Unk_09BB4394 * arg0, CStruct * arg1);
s32 fn_8023821C(void *arg0, Unk_5D1D68CC * arg1, s32 * arg2);
s32 fn_80237D14(void *arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
s32 fn_80243318(CStruct * arg0, s32 arg1);
s32 fn_8024336C(CStruct * arg0);
s32 fn_802432A0(Unk_9994C3F5 * arg0);
s32 fn_802416F8(s32 arg0);
s32 fn_80238C40(Unk_673C6403 * arg0, Unk_ECD1B899 * arg1, void *arg2);
void fn_8023EDE4(Unk_C7387A53 * arg0, s32 arg1);
void fn_802394F8(Unk_673C6403 * arg0, s32 arg1, Unk_C7387A53 * arg2);
void fn_80243320(s32 * arg0, s32 arg1);

typedef struct Ent108 {
    char b[0x6C];
} Ent108;

typedef struct SpW {
    s32 w;
    u16 h;
} SpW;

void fn_8023E9D0(Unk_2EE8F436 *arg0, s32 arg1, s32 arg2) {
s32 fs_t;
    SpW sp8;
    SpW sp10;
    s32 sp18;
    s32 sp1C;
    register char *argp __asm__("r28");
    register char *sp8p __asm__("r27");
    Unk_21634967 *sp10p;
    s32 v1;
    s32 v2;
    Unk_897A0ACF *handle;
    s32 mode;

    argp = (char *)arg0 + 4;
    sp8p = (char *)&sp8;
    fn_8023E724(arg0);
    ((Unk_21634967 *)sp8p)->unk0x4 = ((Unk_21634967 *)argp)->unk0x4;
    *(s32 *)sp8p = arg0->unk0x4;
    *(u8 *)fn_80240B2C(argp, 0) += (u8)arg1;
    *(u8 *)fn_80240B2C(argp, 2) += (u8)arg2;
    fn_8023E724(arg0);
    if (arg0->unk0x74 == 5) {
        v2 = arg0->unk0x64;
        if (v2 == 0) {
            goto common;
        }
        arg0->unk0x68 = fn_80245094(v2, (void *)arg0);
        *(u8 *)fn_80240B2C(argp, 1) = ((Unk_D17A2A5A *)arg0)->unk0x6B;
        goto t23;
    } else {
        sp10p->unk0x4 = ((Unk_21634967 *)argp)->unk0x4;
        sp10p = (char *)&sp10;
        *(s32 *)sp10p = arg0->unk0x4;
        v1 = fn_8023821C(*(void **)arg0, sp10p, NULL);
        *(s32 *)sp10p = *(s32 *)sp8p;
        sp10p->unk0x4 = ((Unk_21634967 *)sp8p)->unk0x4;
        v2 = fn_8023821C(*(void **)arg0, sp10p, NULL);
        if (v2 < v1) {
            v2 = v1;
        }
    }
common:;
    *(u8 *)fn_80240B2C(argp, 1) = (u8)v2;
t23:;
    if ((u32)(arg0->unk0x74 - 2) <= 1U) {
        sp10p = (char *)&sp10;
        sp10p->unk0x4 = ((Unk_21634967 *)argp)->unk0x4;
        *(s32 *)sp10p = arg0->unk0x4;
        mode = 2;
        v1 = fn_80237D14(*(void **)arg0, sp10p, 0, 0, 0, 0);
        handle = fn_80243318((char *)&sp18, v1);
        if (sp18 != 0) {
            fs_t = fn_802416F8(fn_802432A0(fn_8024336C((char *)&sp18)));
            *(s32 *)sp10p = *(s32 *)handle;
            handle = fs_t;
            sp10p->unk0x4 = handle->unk0x4;
            v2 = fn_80238C40(*(void **)arg0, sp10p, &sp1C);
            if (v2 != 0) {
                if (arg0->unk0xC0 != 1) {
                    *((Ent108 *)&arg0->unk0x78) = *(Ent108 *)v2;
                }
                mode = 3;
            }
        }
        fn_8023EDE4(arg0, mode);
        if (arg0->unk0xC0 > 0) {
            fn_802394F8(*(void **)arg0, 1, (char *)arg0 + 0x78);
        } else {
            fn_802394F8(*(void **)arg0, 1, NULL);
        }
        fn_80243320((char *)&sp18, 2);
    }
}
