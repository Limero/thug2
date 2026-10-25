// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A9D2C-0x801A9DE8 (188B). Byte-identical.
#include "types.h"
#include "structs.h"
struct it {
    s32 bits;
    s32 *arr;
    char _8[4];
    s32 idx;
    s32 *cur;
};
struct nd {
    s32 val;
    s32 ret;
    s32 *next;
};
s32 fn_801A9D2C(struct it *arg0, s32 *arg1) {
    register struct nd *bkt __asm__("r9");
    register s32 *jt __asm__("r0");
    register s32 *ct __asm__("r9");
    Unk_9994C3F5 *cur;
    s32 *nxt;
    u32 mask;
    s32 r0;
    s32 temp;
    s32 idx;

    cur = arg0->cur;
    mask = 1U << arg0->bits;
    if (cur == NULL) {
        if (arg0->idx >= 0) {
            r0 = 0;
            goto check;
        }
    } else {
        nxt = *((s32 * *)&cur->unk0x8);
        arg0->cur = nxt;
    }
    jt = arg0->cur;
    if (jt != NULL) {
        r0 = 1;
        goto check;
    }
    for (;;) {
        temp = arg0->idx;
        idx = temp + 1;
        arg0->idx = idx;
        if ((s32)idx >= (s32)mask) {
            r0 = 0;
            goto check;
        }
        bkt = (struct nd *)((char *)arg0->arr + idx * 12);
        arg0->cur = (s32 *)bkt;
        if (bkt->ret != 0) {
            r0 = 1;
            goto check;
        }
        nxt = *((s32 * *)&((Unk_9994C3F5 *)bkt)->unk0x8);
        if (nxt == NULL) {
            continue;
        }
        arg0->cur = nxt;
        break;
    }
    r0 = 1;
check:
    if (r0 == 0) {
        return 0;
    }
    ct = arg0->cur;
    if (ct == NULL) {
        return 0;
    }
    if (arg1 != NULL) {
        *arg1 = ((CStruct *)ct)->unk0x0;
    }
    return *(s32 *)((char *)(*(s32 **)((char *)&arg0->cur)) + 4);
}
