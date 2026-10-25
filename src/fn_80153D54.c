// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80153D54-0x80153EAC (344B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-schedule-insns
#include "types.h"
#include "structs.h"
typedef struct { char pad[0x1008]; s32 values[64]; } NetStats1008;
typedef struct { char pad[0xC08]; s32 values[64]; } NetStatsC08;
typedef struct { char pad[0xC]; s32 values[64]; } NetMessageList;
s32 fn_80137344(NetStats1008 *, s32);
s32 fn_80137354(NetStatsC08 *, s32);
s32 fn_8013E034(s32, CStruct *);
s32 fn_8013E068(void *, CStruct *);
s32 fn_8021B554(Unk_9994C3F5 *);
s32 fn_8021B55C(NetMessageList *, s32);
extern s32 lbl_80305F9C;
extern char lbl_8029F480[];
typedef struct iter_s {
    s32 pad0;
    s32 current;
    char *end;
} iter_s;
register s32 r29_guard __asm__("r29");
// RETRACTED — the 2026-09-26 park note (kept here only as a record of what was
// believed wrong, so it is not re-derived): its two claims "needs an opaque-zero
// or reload-blocking mechanism GCC 2.95 does not expose to plain C" and "[both]
// store orders emit the arg copy pinned first at +0x2C" were BOTH wrong. The
// opaque-zero `__asm__("li %0,0" : "=r"(z))` birth and an empty
// `__asm__ __volatile__("" ::: "memory")` are enough; the arg copy is only
// pinned ahead of the stores while there is no clobber between them. Also note
// that the note's list of "resisting spellings" never tried the one lever that
// mattered: an asm BIRTH (`"=r"`) rather than a named local, which is what makes
// the zero opaque to const-prop.
// The script parameters are the standard CStruct/CScript pair and are unused.
// The callee prototypes carry the retail array layouts: +0x1008 for fn_80137344,
// +0xC08 for fn_80137354, +0xC for fn_8021B55C; the iterator is the +0/+4/+8
// cursor/sentinel object consumed by fn_8013E034/068. All six callee arities were
// re-audited against their prologues this round (all correct, no change needed).
bool ScriptDumpNetMessageStats(CStruct *pParams, CScript *pScript) {
    struct iter_s sp8;
    struct iter_s *p;
    register struct iter_s *out __asm__("r26");
    register s32 var_r27 __asm__("r27");
    register s32 temp_r28 __asm__("r28");
    s32 temp_r31;
    s32 temp_r30;
    s32 temp_r4;
    s32 temp_r4_2;
    s32 var_r3;
    s32 var_r31;
    s32 var_r31_2;
    s32 var_r31_3;
    s32 var_r31_4;

    temp_r31 = lbl_80305F9C;
    temp_r30 = (s32)lbl_8029F480;
    p = &sp8;
    out = p;
    __asm__("" : "+r"(p));
    p->current = 0;
    p->end = (char *)temp_r30;
    __asm__ __volatile__("" ::: "memory");
    if ((var_r27 = fn_8021B554((Unk_9994C3F5 *)temp_r31)) == 0) {
        register s32 zz1;
        __asm__("li %0,0" : "=r"(zz1));
        if ((var_r27 = fn_8021B55C((NetMessageList *)temp_r31, zz1)) == 0) {
            out->end = (char *)lbl_8029F480;
            return true;
        }
    }
    var_r3 = fn_8013E034(var_r27, &sp8);
    if (var_r3 != 0) {
        do {
            temp_r28 = var_r3 + 0x34FC;
            temp_r30 = var_r3 + 0x20EC;
            var_r31 = 0;
loop_5:
            fn_80137344((NetStats1008 *)temp_r30, var_r31);
            temp_r4 = var_r31;
            var_r31 += 1;
            fn_80137354((NetStatsC08 *)temp_r30, temp_r4);
            if (var_r31 <= 0xFF) {
                goto loop_5;
            }
            var_r31_2 = 0;
loop_7:
            fn_80137344((NetStats1008 *)temp_r30, var_r31_2);
            fn_80137354((NetStatsC08 *)temp_r30, var_r31_2);
            var_r31_2 += 1;
            if (var_r31_2 <= 0xFF) {
                goto loop_7;
            }
            var_r31_3 = 0;
loop_9:
            fn_80137344((NetStats1008 *)temp_r28, var_r31_3);
            temp_r4_2 = var_r31_3;
            var_r31_3 += 1;
            fn_80137354((NetStatsC08 *)temp_r28, temp_r4_2);
            if (var_r31_3 <= 0xFF) {
                goto loop_9;
            }
            var_r31_4 = 0;
loop_11:
            fn_80137344((NetStats1008 *)temp_r28, var_r31_4);
            fn_80137354((NetStatsC08 *)temp_r28, var_r31_4);
            var_r31_4 += 1;
            if (var_r31_4 <= 0xFF) {
                goto loop_11;
            }
            var_r3 = fn_8013E068(var_r27, &sp8);
        } while (var_r3 != 0);
    }
    out->end = (char *)lbl_8029F480;
    return true;
}
