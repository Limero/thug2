// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8016C4B0-0x8016C6FC (588B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 fn_80125A3C(void *, s32);
extern s32 fn_8016C444(Unk_15EF4A35 *);

void fn_8016C4B0(Unk_C7387A53 *arg0) {
    void *obj = *((void * *)&arg0->unk0x20);
    register s32 st __asm__("r9");
    s32 flags;
    s32 t;
    register s32 u __asm__("r0");

    if (fn_80125A3C(QB_SELECT_SHIFT, 1) != 0) {
        flags = ((Unk_C7387A53 *)obj)->unk0x4C;
        st = flags;
        __asm__("" : "+r"(st));
        t = 1;
        if (!(flags & 0x10)) {
            t = 0;
        }
        if (t != 0) {
            fn_8016C444(QB_USERSELECTTRIANGLE);
            return;
        }
        u = 1;
        if (!(st & 0x80)) {
            u = 0;
        }
        if (u != 0) {
            fn_8016C444(QB_USERSELECTSQUARE);
            return;
        }
        u = 1;
        if (!(st & 0x20)) {
            u = 0;
        }
        if (u != 0) {
            fn_8016C444(QB_USERSELECTCIRCLE);
            return;
        }
        u = 1;
        if (!(st & 0x800)) {
            u = 0;
        }
        if (u != 0) {
            fn_8016C444(QB_USERSELECTSTART);
            return;
        }
        u = 1;
        if (!(st & 0x40)) {
            u = 0;
        }
        if (u != 0) {
            fn_8016C444(QB_USERSELECTX);
            return;
        }
        u = 1;
        if (!(st & 4)) {
            u = 0;
        }
        if (u != 0) {
            fn_8016C444(QB_USERSELECTL1);
            return;
        }
        u = 1;
        if (!(st & 1)) {
            u = 0;
        }
        if (u != 0) {
            fn_8016C444(QB_USERSELECTL2);
            return;
        }
        u = 1;
        if (!(st & 8)) {
            u = 0;
        }
        if (u != 0) {
            fn_8016C444(QB_USERSELECTR1);
            return;
        }
        u = 1;
        if (!(st & 2)) {
            u = 0;
        }
        if (u != 0) {
            fn_8016C444(QB_USERSELECTR2);
            return;
        }
        u = 1;
        if (!(st & 0x1000)) {
            u = 0;
        }
        if (u != 0) {
            fn_8016C444(QB_USERSELECTUP);
            return;
        }
        u = 1;
        if (!(st & 0x4000)) {
            u = 0;
        }
        if (u != 0) {
            fn_8016C444(QB_USERSELECTDOWN);
            return;
        }
        u = 1;
        if (!(st & 0x8000)) {
            u = 0;
        }
        if (u != 0) {
            fn_8016C444(QB_USERSELECTLEFT);
            return;
        }
        u = 1;
        if (!(st & 0x2000)) {
            u = 0;
        }
        if (u != 0) {
            fn_8016C444(QB_USERSELECTRIGHT);
        }
    }
}
