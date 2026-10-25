// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801AF82C-0x801AFA18 (492B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

typedef union {
    __ps_t p;
    f32 f[2];
} Pair;

typedef struct GapNode {
    s32 unk0x0;
    s32 unk0x4;
    s32 unk0x8;
    struct GapNode *unk0xC;
    struct GapNode *unk0x10;
    s32 unk0x14;
    __ps_t unk0x18;
    __ps_t unk0x20;
    __ps_t unk0x28;
    __ps_t unk0x30;
    s32 unk0x38;
    s32 unk0x3C;
    s32 unk0x40;
} GapNode;

s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
void AddChecksum(CStruct *, s32, s32);
void AddInteger(CStruct *, s32, s32);
void AddString(CStruct *, s32, void *);
void fn_8012788C(CStruct *, s32, f32, f32, f32);
void *fn_801AED74(GapNode *);
s32 fn_801AED20(GapNode *);
s32 CStruct_new(s32);
s32 CStruct_ctor(s32);
void CStruct_delete(CStruct *, s32);
void Script_RunScript(s32, s32, s32, s32, s32);

s32 fn_801AF82C(CStruct *arg0, CStruct *arg1) {
    Pair fr[2];
    Pair *base;
    s32 checksum;
    s32 ret;
    GapNode *raw;
    GapNode *nxt;
    GapNode *walk;
    s32 idx;
    CStruct *obj;

    checksum = QB_NULLSCRIPT;
    GetChecksum_2(arg1, QB_CHOOSE_SCRIPT, &checksum, 0);
    raw = (GapNode *)arg0->unk0x10;
    if (raw->unk0x4 == -1) raw = NULL;
    idx = 0;
    walk = raw;
    if (walk != NULL) {
        base = fr;
        do {
            obj = (CStruct *)CStruct_ctor(CStruct_new(8));
            raw = walk->unk0xC;
            if (raw->unk0x4 == -1) {
                nxt = NULL;
            } else {
                nxt = raw;
            }
            if (idx == 0) {
                AddChecksum(obj, 0, QB_FIRST_ITEM);
            } else if (nxt == NULL) {
                AddChecksum(obj, 0, QB_LAST_ITEM);
            }
            AddInteger(obj, QB_GAP_SCORE, walk->unk0x40);
            AddString(obj, QB_GAP_NAME, fn_801AED74(walk));
            AddInteger(obj, QB_TIMES, fn_801AED20(walk));
            AddInteger(obj, QB_GAP_NUMBER, idx);
            fr[0].p = walk->unk0x18;
            base[1].p = walk->unk0x20;
            fn_8012788C(obj, QB_SKATER_START_POS, fr[0].f[0], fr[0].f[1], base[1].f[0]);
            fr[0].p = walk->unk0x28;
            base[1].p = walk->unk0x30;
            fn_8012788C(obj, QB_SKATER_START_DIR, fr[0].f[0], fr[0].f[1], base[1].f[0]);
            AddChecksum(obj, QB_CHOOSE_SCRIPT, checksum);
            Script_RunScript(QB_GAP_MENU_ADD_ITEM, obj, 0, 0, 0);
            if (obj != 0) CStruct_delete(obj, 3);
            idx += 1;
            walk = nxt;
        } while (walk != NULL);
    }
    ret = 0;
    if (idx != 0) {
        ret = 1;
    }
    return ret;
}
