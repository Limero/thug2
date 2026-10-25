// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80041BA4-0x80041D08 (356B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"

s32 GetStructure_2(void *arg0, s32 arg1, s32 *arg2, s32 arg3);
s32 GetPair(void *arg0, s32 arg1, void *arg2, s32 arg3);
s32 ContainsFlag(void *arg0, s32 arg1);
s32 GetVector(void *arg0, s32 arg1, void *arg2, s32 arg3);
void *fn_80125000(void *arg0);

/* Stack locals, laid out by want: object at r1+0x08 (floats at +4,+8 — filled by
 * fn_80125000 and GetPair), GetVector out at r1+0x18 (floats at +0,+4,+8,+C),
 * s32 out of GetStructure_2 at r1+0x28.  locals region = stmw offset - 8 = 0x28. */
typedef struct { s32 unk0; f32 a; f32 b; f32 c; } Loc_t;
typedef struct { f32 x; f32 y; f32 z; f32 w; } Vec_t;
/* sub-object reached through a pointer taken at arg0+0xD0 */
typedef struct { char pad0x00[0x18]; f32 f18; f32 f1C; } Sub_t;
/* sub-object reached through the pointer stored at arg0+0x58 (re-loaded twice) */
typedef struct { char pad0x00[0x178]; f32 f178; f32 f17C; } Pr_t;

// CScreenElement_resolve_pos @ 0x80041BA4
bool CScreenElement_resolve_pos(void *arg0, void *arg1, f32 *arg2, f32 *arg3) {
    Loc_t loc;
    Vec_t vec;
    s32 sp28;
    Sub_t *o;
    Pr_t *p;

    fn_80125000(&loc);
    if (GetStructure_2(arg1, QB_POS, &sp28, 0) != 0) {
        GetPair(sp28, 0, &loc, 1);
        if (ContainsFlag(sp28, QB_RELATIVE) != 0) {
            o = (Sub_t *)((char *)arg0 + 0xD0);
            *arg2 = o->f18 + loc.a;
            *arg3 = o->f1C + loc.b;
        } else if (ContainsFlag(sp28, QB_PROPORTIONAL) != 0) {
            p = (Pr_t *)(*(s32 *)((char *)arg0 + 0x58));
            *arg2 = loc.a * p->f178;
            p = (Pr_t *)(*(s32 *)((char *)arg0 + 0x58));
            *arg3 = loc.b * p->f17C;
        }
        return true;
    }
    if (GetPair(arg1, QB_POS, &loc, 0) != 0) {
        *arg2 = loc.a;
        *arg3 = loc.b;
        return true;
    }
    if (GetVector(arg1, QB_POS, &vec, 0) != 0) {
        *arg2 = vec.x;
        *arg3 = vec.y;
        return true;
    }
    return false;
}
