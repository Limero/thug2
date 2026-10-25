// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801835B4-0x801839F0 (1084B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct _Arr801835B4 {
    char _pad0x0[4];
    s32 count;              /* +0x4 : element count */
} Arr801835B4;

extern char lbl_80305EC0[];
extern char lbl_802A948C[];

s32 IsTrue(s32, s32);
s32 ScriptInMultiplayerGame(s32, s32);
s32 ContainsFlag(void *, s32);
void AddChecksum(void *, s32, s32);
void *Mem_NewZero(s32);
void *fn_80192008(void *, void *);
void *fn_80192688(void *, void *);
void *fn_80192B9C(void *, void *);
void *fn_80193024(void *, void *);
void *fn_8019528C(void *, void *);
void *fn_80195544(void *, void *);
void *fn_801957E0(void *, void *);
void *fn_80195DA0(void *, void *);
void *fn_8019614C(void *, void *);
void *fn_801964F8(void *, void *);
void *fn_801965D4(void *, void *);
void *fn_8018B6F8(void *, void *);
void fn_8018B3E8(s32, s32 *, void *);
void fn_80190764(void *);
void *fn_8018BFAC(void *);
s32 GetArray(void *, s32, void *, s32);
s32 GetChecksum(Arr801835B4 *, s32);
s32 GetChecksum_2(void *, s32, void *, s32);
void fn_801877F4(s32, s32, s32);
void fn_8018BC9C(void *, s32);
void AddString(void *, s32, s32);
s32 fn_801258B0(s32, s32);

s32 fn_801835B4(s32 arg0, s32 arg1, void *arg2) {
    s32 t;
    s32 sp8;
    Arr801835B4 *spC;
    s32 sp10;
    void *res1;
    void *obj;
    s32 count;
    s32 i;

    t = IsTrue(*(s32 *)lbl_80305EC0, 0x337E7779);
    if (ScriptInMultiplayerGame(0, 0) == 0 && t != 0) {
        return 0;
    }
    if (IsTrue(*(s32 *)lbl_80305EC0, 0x353961D7) != 0) {
        if (ContainsFlag(arg2, 0x981D3AD0) == 0) {
            return 0;
        }
    }
    AddChecksum(arg2, 0x9982E501, arg1);
    if (ContainsFlag(arg2, 0xC18FEF36) != 0) {
        if (ScriptInMultiplayerGame(0, 0) != 0) {
            return 0;
        }
    }

    if (ContainsFlag(arg2, 0x4AF5D34E) != 0) {
        obj = fn_80192008(Mem_NewZero(0x88), arg2);
    } else if (ContainsFlag(arg2, 0x0D15EA00) != 0) {
        obj = fn_80192688(Mem_NewZero(0x78), arg2);
    } else if (ContainsFlag(arg2, 0x25904450) != 0) {
        obj = fn_80192B9C(Mem_NewZero(0x80), arg2);
    } else if (ContainsFlag(arg2, 0x4147922B) != 0) {
        obj = fn_80193024(Mem_NewZero(0x52C), arg2);
    } else if (ContainsFlag(arg2, 0x9D65D0E7) != 0) {
        obj = fn_8019528C(Mem_NewZero(0x74), arg2);
    } else if (ContainsFlag(arg2, 0xC5EC08E6) != 0) {
        obj = fn_80195544(Mem_NewZero(0x78), arg2);
    } else if (ContainsFlag(arg2, 0x7DBB41DD) != 0) {
        obj = fn_801957E0(Mem_NewZero(0x8C), arg2);
    } else if (ContainsFlag(arg2, 0xEFC35592) != 0) {
        obj = fn_80195DA0(Mem_NewZero(0x74), arg2);
    } else if (ContainsFlag(arg2, 0xF268C278) != 0) {
        obj = fn_8019614C(Mem_NewZero(0x74), arg2);
    } else if (ContainsFlag(arg2, 0xD3C2899D) != 0) {
        obj = fn_801964F8(Mem_NewZero(0x74), arg2);
    } else if (ContainsFlag(arg2, 0xD0DD047B) != 0) {
        obj = fn_801965D4(Mem_NewZero(0x5C8), arg2);
    } else {
        obj = fn_8018B6F8(Mem_NewZero(0x74), arg2);
    }

    sp8 = arg1;
    fn_8018B3E8(arg0 + 4, &sp8, obj);
    fn_80190764(obj);
    res1 = fn_8018BFAC(obj);
    if (GetArray(res1, 0x5E684E45, &spC, 0) != 0) {
        count = spC->count;
        for (i = 0; i < count; i++) {
            fn_801877F4(arg0, arg1, GetChecksum(spC, i));
            fn_8018BC9C(obj, GetChecksum(spC, i));
        }
    } else if (GetChecksum_2(res1, 0xDD4CABD6, &sp10, 0) != 0) {
        fn_801877F4(arg0, arg1, sp10);
        fn_8018BC9C(obj, sp10);
    }

    if (ScriptInMultiplayerGame(0, 0) != 0) {
        AddString(fn_8018BFAC(obj), 0x944B2900, (s32)lbl_802A948C);
        AddString(fn_8018BFAC(obj), 0x243B9C3B, fn_801258B0(0xA500BC5F, 0));
    }

    return obj != 0;
}

// NOTE 2026-10-06 (worker): this is an unmeasured rebuild — the slice had no
// compiler.  The structural fixes above (no outer condition wrapper, 2-arg
// ctors with the alloc in r3, res1 as GetArray/GetChecksum_2's first argument,
// the same-index double GetChecksum, `return obj != 0`) are all read directly
// from the WANT.  Lowest-confidence detail: the prologue CR save
// (`mfcr r12` / `stw r12,0x18` / `mtcrf 8,r12`) implies the `obj != 0`
// comparison is evaluated early and held in non-volatile CR4 across the tail
// calls (want emits `cmpwi cr4,r30,0` inside BOTH GetArray arms at 0x801838D4
// and 0x8018393C, then `bne cr4` at 0x801839CC).  A plain `return obj != 0;`
// may place the compare at the end instead; if so the coordinator should try
// capturing it in a `s32 ok`/BOOL local assigned before the tail so ngccc can
// keep it in CR4 (and re-measure, then keep whichever scores higher).
