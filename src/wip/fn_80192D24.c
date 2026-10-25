// PARKED 2026-10-05: best body 70.8% masked (draft below unchanged — every
// source-shape variant tried compiled to the identical object or worse).
// 70.3% (135/192) once the internal branch targets are actually resolved
// (tools/reloc_diff.py) instead of being masked away. The body below is
// unchanged either way.
//
// ROOT CAUSE (one extra word + one extra callee-saved reg shifts everything):
// ngccc keeps the loop-invariant address of the sprintf/CRC buffer in a
// register. GOT has `addi r27, r1, 0x18` at the loop top (0x80192DA4) and
// `mr r3, r27` at both use sites; WANT rematerialises `addi r3, r1, 0x10` at
// each use (0x80192F98, 0x80192FA4) and keeps arg1 in r27. The register grab
// cascades: stmw saves r26 (arg1 moves there), frame 0x148 vs want 0x138, all
// stack offsets +8, and every instruction after the insertion is index-shifted
// (56/192 words differ, most of them by the shift alone).
// Tested and IDENTICAL object (md5) or worse: struct member vs standalone
// `char sp10[0x100]`, `volatile` on member/array, `&f.sp10[0]` spelling,
// `register char *p` short-lived pointer, stores-first reorder (68.8%), while
// loop (67.2%), two arrays (23.4%). -fno-strength-reduce / -fno-gcse /
// -fno-schedule-insns2 / -fno-thread-jumps all leave the hoist in place.
// Minimal repro: a `char buf[256]` standalone in a small loop rematerialises
// (fn_800723F0-style), but the same buffer inside a struct that also holds the
// loop counter lives in a saved reg — this function's big loop body makes the
// allocator keep the invariant. No C-level lever found; parked (see
// docs/parkings if a GC/loop-alloc recipe is added).
// Residual after a hypothetical fix: old78/unk0x74 temp colour (mr r0,r9 +
// addi r9,r9,1 vs addi r11,r9,1) and the f.sp8/f.spC zero-store placement
// (before vs after the Script_GenerateCRC call).
// family=m2c range=0x80192D24-0x80193024 size=768B
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_802A9B94[];
int sprintf(char *, char *, ...);
void *CStruct_new(s32);
CStruct *CStruct_ctor(void *);
void CStruct_delete(CStruct *, s32);
s32 GetArray(CStruct *, s32, void *, s32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 GetString(CStruct *, s32, void *, s32);
void AddInteger(CStruct *, s32, s32);
void AddChecksum(CStruct *, s32, s32);
s32 ContainsFlag(CStruct *, s32);
void fn_8012720C(CStruct *, s32);
void fn_80126FF4(CStruct *, CStruct *);
CStruct *fn_80129528(CStruct *, s32);
s32 fn_8018D614(Unk_8B98B2B7 *, s32, s32, s32);
void fn_8018D684(Unk_8B98B2B7 *);
void fn_8018C068(Unk_8B98B2B7 *, s32);
s32 Script_GenerateCRC(char *);
void Script_SpawnScript(s32, CStruct *, s32, s32, s32, s32, s32, s32);
typedef struct {
    char pad0x0[0x10];
    s16 off10;
    s16 pad12;
    s32 (*fn14)(void *);
} Vt_192D24;
typedef struct {
    char pad0x0[0x14];
    Vt_192D24 *vt14;
} W_192D24;
s32 NextRaceWaypoint(Unk_8B98B2B7 *arg0, s32 arg1) {
    struct {
        char hole[8];
        s32 sp8;
        s32 spC;
        char sp10[0x100];
        CStruct *sp110;
        s32 sp114;
        s32 sp118;
        char *sp11C;
    } f;
    CStruct *temp_r28;
    CStruct *temp_r30;
    s32 var_r29;
    s32 old78;
retry:
    {
        Vt_192D24 *v = ((W_192D24 *)arg0)->vt14;
        if (v->fn14((char *)arg0 + v->off10) != 0) {
            return 0;
        }
    }
    GetArray(arg0->unk0x20, QB_RACE_WAYPOINTS, &f.sp110, 1);
    for (var_r29 = 0; (u32)var_r29 < (u32)f.sp110->unk0x4; var_r29++) {
        temp_r28 = fn_80129528(f.sp110, var_r29);
        GetChecksum_2(temp_r28, QB_FLAG, &f.sp114, 1);
        if (fn_8018D614(arg0, f.sp114, 1, 0) != 0) {
            if (var_r29 != f.sp110->unk0x4 - 1) {
                continue;
            }
            old78 = arg0->unk0x78;
            arg0->unk0x78 = old78 + 1;
            if (old78 < arg0->unk0x74) {
                fn_8018D684(arg0);
                goto retry;
            }
            return 1;
        }
        temp_r30 = CStruct_ctor(CStruct_new(8));
        AddChecksum(temp_r30, QB_GOAL_ID, arg1);
        if (var_r29 == 0 && arg0->unk0x74 > 1) {
            AddInteger(temp_r30, QB_START_LAP, arg0->unk0x78);
        }
        if (var_r29 == f.sp110->unk0x4 - 1 && arg0->unk0x78 == arg0->unk0x74) {
            AddChecksum(temp_r30, QB_LAST_WAYPOINT, 1);
        }
        if (ContainsFlag(arg0->unk0x20, QB_QUICK_START) != 0) {
            AddChecksum(temp_r30, 0, QB_QUICK_START);
        } else {
            fn_8012720C(temp_r30, QB_QUICK_START);
        }
        if (arg0->unk0x78 == 1 && var_r29 == 0) {
            AddInteger(temp_r30, QB_FIRST_WAYPOINT, 1);
        } else {
            AddChecksum(temp_r30, QB_SCR, QB_GOAL_RACE_CHECKPOINT_MESSAGE);
            if ((arg0->unk0x70 & 0x80000) == 0 && arg0->unk0x7C != 0) {
                GetInteger(temp_r28, QB_TIME, &f.sp118, 0);
                fn_8018C068(arg0, f.sp118);
                AddInteger(temp_r30, QB_ADDED_TIME, f.sp118);
            }
        }
        fn_80126FF4(temp_r30, temp_r28);
        GetString(arg0->unk0x20, QB_GOAL_NAME, &f.sp11C, 1);
        sprintf(f.sp10, lbl_802A9B94, f.sp11C);
        f.sp8 = 0;
        f.spC = 0;
        Script_SpawnScript(QB_GOAL_RACE_NEXT_WAYPOINT, temp_r30, 0, 0, 0, Script_GenerateCRC(f.sp10), 0, 0);
        if (temp_r30 != 0) {
            CStruct_delete(temp_r30, 3);
        }
        return 1;
    }
    return 1;
}
