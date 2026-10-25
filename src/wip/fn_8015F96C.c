// WIP DRAFT (non-matching) — hand-rebuilt from disasm: big configurable-tricks collector
// family=m2c range=0x8015F96C-0x8015FCA4 size=824B
// PARKED ~33%: structure + CR machinery (cmpwi cr4/mfcr/mtcrf) emerge naturally but the
// callee-saved map is rotated by one slot (special->r21 vs want r22; count2 inverse;
// stmw r17 vs r18; frame -0x450 vs -0x458). Init order permutations shift which zero-reg
// sp408's store reuses and cascade everywhere. Needs a fresh idea on GCC-2.95 pseudo->cr
// coloring; compare byte-twins in other batches before retrying.
// UPDATED 2026-09-13 (c): extended flag matrix (recipe 49) found `-fno-schedule-insns` -> 33.01% to 38.65%.
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// FLAG: -fno-schedule-insns
// UPDATED 2026-09-15: phantom-arg drop (addr-literal + bare-0 classes); now 38.8%.
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305EAC;
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 ContainsFlag(CStruct *, s32);
s32 fn_801259C8(s32, s32);
s32 GetChecksum(CStruct *, s32);
s32 GetStructure(s32, s32);
s32 GetStructure_2(CStruct *, s32, s32 *, s32);
s32 GetInteger(CStruct *, s32, s32 *);
s32 fn_801745B4(s32);
s32 fn_8009CF2C(CStruct *);
s32 fn_8003E7CC(s32);
s32 fn_80128F94(Unk_9D4ED6AF *);
s32 fn_80129068(Unk_5AA7B5D7 *, s32, s32);
s32 fn_801292A8(CStruct *, s32, s32);
s32 fn_80129260(CStruct *, s32, s32);
void AddArrayPointer(CStruct *, s32, s32);
bool ScriptGetConfigurableTricksFromType(CStruct *arg0, CScript *arg1) {
    s32 sp8[128];
    s32 arr208[128];
    s32 sp408;
    s32 sp40C;
    s32 sp410;
    s32 sp414;
    s32 var_r21;
    s32 var_r22;
    CStruct *var_r23;
    s32 var_r24;
    s32 var_r26;
    s32 var_r28;
    s32 var_r30;
    s32 *out;
    s32 i;
    s32 j;
    register s32 cA __asm__("r19");
    register s32 cB __asm__("r20");
    var_r21 = 0;
    sp408 = 0;
    cA = QB_GRABTRICK;
    cB = QB_FLIPTRICK;
    GetChecksum_2(arg0, QB_TYPE, &sp408, 0);
    var_r22 = ContainsFlag(arg0, QB_SPECIAL);
    var_r23 = fn_801259C8(QB_CONFIGURABLETRICKS, 1);
    var_r26 = 0;
    var_r24 = var_r23->unk0x4;
    out = sp8;
    for (i = 0; i < var_r24; i++) {
        var_r28 = GetChecksum(var_r23, i);
        var_r30 = GetStructure(var_r28, 0);
        if (var_r30 == 0) {
            continue;
        }
        if (GetChecksum_2(var_r30, QB_TRICKTYPE, &sp40C, 0) == 0 &&
            GetChecksum_2(var_r30, QB_SCR, &sp40C, 0) == 0) {
            sp40C = QB_GRINDTRICK;
        }
        if (var_r22 == 0 || sp408 != 0) {
            if (sp40C != sp408) {
                continue;
            }
        }
        GetStructure_2(var_r30, QB_PARAMS, &sp410, 1);
        if (var_r22 == 0) {
            if (ContainsFlag(sp410, QB_ISSPECIAL) != 0) {
                continue;
            }
        } else {
            if (ContainsFlag(sp410, QB_ISSPECIAL) == 0) {
                continue;
            }
        }
        *out = var_r28;
        out += 1;
        var_r26 += 1;
    }
    if (sp408 == cA || (var_r26 == 0 && sp408 == cB)) {
        s32 base = fn_801745B4(lbl_80305EAC);
        if (base != 0) {
            s32 *walk = (s32 *)((char *)base + 0x198);
            s32 *out2 = &arr208[var_r21];
            for (j = 1; j < 11; j++) {
                s32 item = *walk++;
                sp414 = 0;
                if (GetInteger(item, QB_FULL, &sp414) != 0 && sp414 != 0) {
                    *out2 = j;
                    out2 += 1;
                    var_r21 += 1;
                }
            }
        }
    }
    if (var_r26 != 0) {
        s32 list;
        i = 0;
        list = fn_80128F94(fn_8003E7CC(12));
        fn_80129068(list, var_r26, 13);
        for (i = 0; i < var_r26; i++) {
            fn_801292A8(list, i, sp8[i]);
        }
        AddArrayPointer(arg1->unk0x18, QB_CONFIGURABLETRICKS, list);
        if (var_r21 > 0) {
            list = fn_80128F94(fn_8003E7CC(12));
            fn_80129068(list, var_r21, 1);
            for (i = 0; i < var_r21; i++) {
                fn_80129260(list, i, arr208[i]);
            }
            AddArrayPointer(arg1->unk0x18, QB_CONFIGURABLECATS, list);
        }
        return true;
    }
    return false;
}
