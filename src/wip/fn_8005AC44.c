// PARKED 2026-10-16: 23.1% masked, size-exact 640B (was 22.5% redraft).
// Full rewrite: dropped the Color union (it built the packed word in a
// register via rlwimi) for the want's in-memory idiom — four byte stores
// (order 0,3,1,2) to a stack word plus a word reload (stb x4 + lwz + stw now
// verbatim); green/blue stored WITHOUT the (u8) casts; sp8/cw are plain s32
// with the u8 overlay scoped after the out-param calls so it stays scratch.
// Residual is global allocation: want saves 5 (stmw r27, frame 0x40) while
// this draft saves 7 (stmw r25, frame 0x48) because &green/&blue get homes
// where want computes them inline (addi r5,r1,0x18/0x1c at the call). Tried:
// u8* overlay before vs after the calls (before homes the overlay too),
// nested scope for the overlay (fixes only that), cast vs no-cast value
// stores (no-cast still yields lbz here, so want's lwz likely cascades from
// the un-homed inline form, not from source spelling). The homes shift every
// stack offset by 4 and rotate all homes; needs a live-range lever, not
// another spelling variant.
// TRIED 2026-10-20: block-scope green/blue per arm (shorten live ranges):
// frame grows to 0x50 (slots stop sharing), worse. Reverted.
// WIP DRAFT (non-matching) — hand-rebuilt from the want disassembly.
// family=m2c range=0x8005AC44-0x8005AEC4 size=640B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
#include "qb_constants.h"
s32 GetFloat(void *arg0, s32 key, f32 *out, s32 arg3);
s32 GetInteger(void *arg0, s32 key, s32 *out, s32 arg3);
s32 fn_80128C80(void *arg0, s32 key, s32 *out, s32 arg3);
void *fn_80054E40(void);
void *fn_80059EE4(void *arg0);
void *fn_80059BB8(void *arg0);
void fn_8005A00C(void *arg0, f32 farg0);
void fn_80059F8C(void *arg0, f32 farg0);
void fn_8005A180(void *arg0, void *arg1);
void fn_8005A060(void *arg0, s32 *arg1);
void fn_8005ABC8(void *arg0, void *arg1);
typedef struct {
    char pad0x00[0x1C];
    f32 unk0x1C;
    f32 unk0x20;
    f32 unk0x24;
    s32 unk0x28;
} Obj8005AC44;
extern f32 lbl_802934FC;
extern f32 lbl_80293500;
extern f32 lbl_80293504;
extern f32 lbl_80293508;
// family=m2c range=0x8005AC44-0x8005AEC4 size=640B
void fn_8005AC44(void *arg0, void *arg1) {
    void *mgr;
    void *rec;
    void *slot;
    s32 sp8;
    f32 spC;
    f32 sp10;
    s32 sp14;
    s32 green;
    s32 blue;

    mgr = fn_80054E40();
    rec = fn_80059EE4(arg0);
    if (rec != 0) {
        if (GetFloat(arg1, 0x9E497FC6, &spC, 0) != 0) {
            spC = spC * lbl_802934FC;
            fn_8005A00C(rec, spC);
        }
        if (GetFloat(arg1, 0x0999151B, &sp10, 0) != 0) {
            fn_80059F8C(rec, sp10);
            fn_8005A180(rec, 0);
        }
        if (GetInteger(arg1, 0x059EA070, &sp14, 0) != 0) {
            s32 cw;
            fn_80128C80(arg1, QB_GREEN, &green, 1);
            fn_80128C80(arg1, QB_BLUE, &blue, 1);
            {
                u8 *cp = (u8 *)&cw;
                cp[0] = ((u8 *)&sp14)[3];
                cp[3] = -1;
                cp[1] = green;
                cp[2] = blue;
            }
            sp8 = cw;
            fn_8005A060(rec, &sp8);
        }
        fn_8005ABC8(mgr, arg0);
        return;
    }
    slot = fn_80059BB8(arg0);
    if (slot != 0) {
        if (GetFloat(arg1, 0x9E497FC6, &spC, 0) != 0) {
            Obj8005AC44 *obj;
            spC = spC * lbl_802934FC;
            obj = (Obj8005AC44 *)*(s32 *)slot;
            obj->unk0x24 = spC;
        }
        if (GetFloat(arg1, 0x0999151B, &sp10, 0) != 0) {
            Obj8005AC44 *obj;
            f32 t;
            t = sp10;
            obj = (Obj8005AC44 *)*(s32 *)slot;
            obj->unk0x1C = t;
            if (t != lbl_80293500) {
                obj->unk0x20 = lbl_80293504 / t;
            } else {
                obj->unk0x20 = lbl_80293508;
            }
        }
        if (GetInteger(arg1, 0x059EA070, &sp14, 0) != 0) {
            Obj8005AC44 *obj;
            s32 cw;
            fn_80128C80(arg1, QB_GREEN, &green, 1);
            fn_80128C80(arg1, QB_BLUE, &blue, 1);
            {
                u8 *cp = (u8 *)&cw;
                cp[0] = ((u8 *)&sp14)[3];
                cp[3] = -1;
                cp[1] = green;
                cp[2] = blue;
            }
            obj = (Obj8005AC44 *)*(s32 *)slot;
            obj->unk0x28 = cw;
        }
    }
}
