// WIP DRAFT (non-matching) — hand rebuild from disasm
// family=m2c range=0x8023E724-0x8023E9D0 size=684B
// PARKED ~38%: allocator home-order wall. Want homes {arg0:r31, argp:r27,
// &sp8-web:r28 (born AFTER call#1 as second addi), var_r29:r29, var_r30:r30};
// every C shape reaches only partial orderings. Pins (argp->r27,
// var_r29->r29, var_r30->r30) fix those homes and frame/stmw span but the
// remaining cascade resists: "+r" opacity barriers (needed for want's
// [extsb copy]+[clrlwi-in-place] signed/unsigned byte-view pairs) corrupt
// allocation under local pins (73-151); "=r" extsb wedges shift stmw;
// -fno-gcse/-fno-schedule-* no-ops; decl-order perms no-op; homed-vs-inline
// pa/pb forms swing ±5%. Structure/semantics fully decoded in body:
// clamp-up blocks ×2, sum-clamp blocks ×2, block-5 sp8 out-param dance with
// fn_80240B0C 7-arg zero-fill + fn_802451A4.
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// UPDATED 2026-09-15 (m2): doc-59 forwarded-test-argument sweep over the newly exposed pool; now 37.5%.
#include "types.h"
#include "structs.h"
void *fn_80240B2C(void *arg0, s32 arg1);
void fn_80240B0C(s32, Unk_F96D0DC8 * arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
void fn_802451A4(Unk_F96D0DC8 * arg0, void *arg1, Unk_F96D0DC8 * arg2);
void fn_8023E724(CStruct *arg0) {
    s32 sp8;
    char *sp8p;
    register char *argp __asm__("r27");
    u8 *pa;
    u8 *pb;
    u8 x;
    u8 vhi;
    u8 vlo;
    s32 c0;
    s32 c2;
    s32 sc0;
    s32 sc2;
    s32 t;
    register s32 var_r29 __asm__("r29");
    register s32 var_r30 __asm__("r30");

    argp = (char *)arg0 + 4;
    if (*(u8 *)fn_80240B2C(argp, 0) < *(u8 *)((char *)*(s32 **)arg0 + 0x3524)) {
        *(u8 *)fn_80240B2C(argp, 0) = *(u8 *)((char *)*(s32 **)arg0 + 0x3524);
    }
    if (*(u8 *)fn_80240B2C(argp, 0) + *(u8 *)fn_80240B2C(argp, 3) >
        *(u8 *)((char *)*(s32 **)arg0 + 0x3524) + *(u8 *)((char *)*(s32 **)arg0 + 0x3527)) {
        pa = fn_80240B2C(argp, 0);
        pb = fn_80240B2C(argp, 3);
        *(u8 *)pa = *(u8 *)((char *)*(s32 **)arg0 + 0x3524) +
                    *(u8 *)((char *)*(s32 **)arg0 + 0x3527) -
                    *(u8 *)pb;
    }
    if (*(u8 *)fn_80240B2C(argp, 2) < *(u8 *)((char *)*(s32 **)arg0 + 0x3526)) {
        *(u8 *)fn_80240B2C(argp, 2) = *(u8 *)((char *)*(s32 **)arg0 + 0x3526);
    }
    if (*(u8 *)fn_80240B2C(argp, 2) + *(u8 *)fn_80240B2C(argp, 5) >
        *(u8 *)((char *)*(s32 **)arg0 + 0x3524 + 2) + *(u8 *)((char *)*(s32 **)arg0 + 0x3524 + 5)) {
        pa = fn_80240B2C(argp, 2);
        pb = fn_80240B2C(argp, 5);
        *(u8 *)pa = *(u8 *)((char *)*(s32 **)arg0 + 0x3524 + 2) +
                    *(u8 *)((char *)*(s32 **)arg0 + 0x3524 + 5) -
                    *(u8 *)pb;
    }
    if (arg0->unk0x74 == 5 && arg0->unk0x64 != 0) {
        fn_80240B0C(arg0->unk0x74, (char *)&sp8, 0, 0, 0, 0, 0, 0);
        sp8p = (char *)&sp8;
        fn_802451A4(*((void * *)&arg0->unk0x64), arg0, sp8p);
        var_r29 = 0;
        c0 = *(u8 *)sp8p;
        vlo = *(u8 *)((char *)*(s32 **)arg0 + 0x3524);
        vhi = *(u8 *)((char *)*(s32 **)arg0 + 0x3527);
        if ((s8)c0 < (s8)vlo) {
            var_r29 = vlo - (s8)c0;
        }
        t = c0 + (sp8p[3] + 255);
        if ((s8)t > (s8)(vlo + vhi - 1)) {
            var_r29 = (vlo + vhi - 1) - (s8)t;
        }
        pb = fn_80240B2C(argp, 0);
        var_r30 = 0;
        *(u8 *)pb += var_r29;
        c2 = ((Unk_1D62F22E_2 *)sp8p)->unk0x2;
        vlo = *(u8 *)((char *)*(s32 **)arg0 + 0x3524 + 2);
        vhi = *(u8 *)((char *)*(s32 **)arg0 + 0x3524 + 5);
        if ((s8)c2 < (s8)vlo) {
            var_r30 = vlo - (s8)c2;
        }
        t = c2 + (sp8p[5] + 255);
        if ((s8)t > (s8)(vlo + vhi - 1)) {
            var_r30 = (vlo + vhi - 1) - (s8)t;
        }
        pb = fn_80240B2C(argp, 2);
        *(u8 *)pb += var_r30;
    }
}
