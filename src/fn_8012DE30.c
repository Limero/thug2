// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8012DE30-0x8012DF28 (248B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct {
    union {
        s32 unk0;                                   // 0x00
        struct { char pad0[2]; u8 type; } t;        // 0x00 / 0x02
    } u;
    s32 unk4;      // 0x04
    s32 unk8;      // 0x08
    s32 unkC;      // 0x0C
} Unk_8012DE30;

// Callee audit: every one of these is 1- or 2-arg and returns void, so the
// CR0 clobber after each call is dead (no `crclr cr1eq`, which an
// implicit-declaration artifact would have added).
void fn_801254E4(Unk_8012DE30 *);   // unlink from the pool list (0x801254E4)
void DeleteString(s32);              // type 3/4 (0x80125230)
void fn_80117CC0(s32);               // type 5   (0x80117CC0)
void fn_80117D74(s32);               // type 6   (0x80117D74)
void Mem_Free_3(s32);                // type 7   (0x800106A8)
void CStruct_delete(s32, s32);       // type 10  (0x8012701C)
void fn_80126A30(s32);               // type 12  (0x80126A30)
void fn_80128FB4(s32, s32);          // type 12  (0x80128FB4)
void fn_8012E760(Unk_8012DE30 *);    // release the node (0x8012E760)

void fn_8012DE30(Unk_8012DE30 *arg0) {
    s32 t;

    fn_801254E4(arg0);
    if (arg0->u.unk0 & 0x200000) {
        return;
    }
    t = arg0->u.t.type;
    if (t == 5) {
        goto str5;
    }
    if (t > 5) {
        goto high;
    }
    if (t == 3) {
        goto str34;
    }
    if (t > 3) {
        goto str34;
    }
    goto tail;
high:
    if (t == 10) {
        goto str10;
    }
    if (t > 10) {
        goto l12;
    }
    if (t == 6) {
        goto str6;
    }
    if (t == 7) {
        goto str7;
    }
    goto tail;
l12:
    if (t == 12) {
        goto str12;
    }
    goto tail;
str34:
    DeleteString(arg0->unkC);
    goto tail;
str5:
    fn_80117CC0(arg0->unkC);
    goto tail;
str6:
    fn_80117D74(arg0->unkC);
    goto tail;
str7:
    Mem_Free_3(arg0->unkC);
    goto tail;
str10:
    if (arg0->unkC != 0) {
        CStruct_delete(arg0->unkC, 3);
    }
    goto tail;
str12:
    fn_80126A30(arg0->unkC);
    if (arg0->unkC != 0) {
        fn_80128FB4(arg0->unkC, 3);
    }
tail:
    arg0->unkC = 0;
    fn_8012E760(arg0);
}
