// WIP DRAFT (non-matching) — hand rebuild from the original disassembly.
// family=m2c range=0x802442A8-0x80244440 size=408B
// FLAG: -fno-rerun-cse-after-loop
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// STRUCTURE (script-message send with retry loop):
//   * seven-argument zero-init of the volatile message block `sp8`, then the
//     send helper with (arg0, &sp8, arg1, arg3, arg4) — arg2 is skipped there
//     because it only feeds the additive length.
//   * length = arg2 + the signed byte at arg0+0x9, plus the unsigned byte at
//     +0x4 of the node held at arg0+0x4 when that node's +0x8 word has bit 3
//     set; clamped to 0xF and written to the message's +0x1 byte.
//   * retry loop: the head zeroes the result slot and re-sends the message
//     copy, then exits when the reply exceeds the length, when the counter
//     passes 0x28, or when a non-zero reply equals the length. The body
//     re-copies the message, bumps the counter and sends it again.
//   * on the reply path a second helper (handle, node, 0) yields the object
//     for the follow-up send (handle, &msg, object) at phase
//     (arg0+0xC + arg4+0x3C) & 3.
//
// OPEN: the remaining diff is the saved-register home set — the original homes
// the handle in r31, the message copy in r25, the two out-pointers in r29/r30
// and the counter in r27, while this body allocates them in different
// callee-saved registers.
#include "types.h"
#include "structs.h"

typedef struct {
    s32 w;
    u16 h;
} Msg6;

typedef struct {
    u8 pad00[4];
    void *node;
    u8 pad08;
    s8 unk09;
    u8 pad0A[2];
    s32 unk0C;
} Arg0View;

typedef struct {
    u8 pad00[4];
    u8 unk04;
    u8 pad05[3];
    s32 unk08;
} NodeView;

s32 fn_80240B0C(Unk_F96D0DC8 *, s32, s32, s32, s32, s32, s32);
s32 fn_8024402C(Unk_7044F700 *, Msg6 *, s32, s32, Unk_C7387A53 *);
s32 fn_80238964(void);
s32 fn_8023821C(s32, Msg6 *, s32 *);
s32 fn_8023869C(s32, Msg6 *, s32);
s32 fn_80236FE4(s32, void *, s32);
s32 fn_80241804(void *, s32);
s32 fn_802377C8(s32, Msg6 *, s32);

void fn_802442A8(Arg0View *arg0, s32 arg1, s32 arg2, s32 arg3, Unk_C7387A53 *arg4) {
    volatile Msg6 sp8;
    Msg6 sp10;
    s32 sp18;
    s32 count;
    s32 handle;
    s32 temp;
    s32 len;
    NodeView *node;
    Msg6 *msg;
    Msg6 *out;
    s32 *res;

    fn_80240B0C((Unk_F96D0DC8 *)&sp8, 0, 0, 0, 0, 0, 0);
    fn_8024402C((Unk_7044F700 *)arg0, (Msg6 *)&sp8, arg1, arg3, arg4);

    len = ((s8)arg0->unk09) + arg2;
    node = (NodeView *)arg0->node;
    if (node != NULL && (node->unk08 & 8)) {
        len += node->unk04;
    }
    if (len > 0xF) {
        len = 0xF;
    }

    ((s8 *)&sp8)[1] = (s8)len;
    count = 0;
    handle = fn_80238964();
    msg = (Msg6 *)&sp8;
    out = &sp10;
    res = &sp18;

    goto head;
    do {
        /* body: re-send and count */
        out->w = sp8.w;
        out->h = msg->h;
        count += 1;
        fn_8023869C(handle, out, 1);
    head:
        sp18 = 0;
        out->w = sp8.w;
        out->h = msg->h;
        temp = fn_8023821C(handle, out, res);
    } while (temp <= len && count <= 0x28 && (sp18 == 0 || temp != len));

    node = (NodeView *)arg0->node;
    if (node != NULL && !(node->unk08 & 8)) {
        temp = fn_80236FE4(handle, node, 0);
        fn_80241804((void *)temp, (arg0->unk0C + arg4->unk0x3C) & 3);
        out->w = sp8.w;
        out->h = msg->h;
        fn_802377C8(handle, out, temp);
    }
}
