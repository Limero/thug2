// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80237604-0x80237708 (260B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
//
// Node-list enumerator. Searches arg0's collection for a list whose head
// matches the 6-byte Unk6 key from arg1 (fn_80237D14), walks the linked list
// (+0xC next) and, when arg2&4 is set and a node's data (fn_802432A0 ->
// fn_802416F8) has bit 0x20 of its +8 field clear, counts it and sums its u16
// +0x32 field while calling fn_802371CC(arg0, data, arg2). Returns the packed
// (count << 16 | sum). Suggested rename: CountNodesMatchingKey.
#include "types.h"
#include "structs.h"
s32 fn_802432A0(Unk_9994C3F5 *);
s32 fn_802416F8(s32);
s32 fn_80237D14(s32, Unk_8C3FE072 *, s32, Unk_4CED4D63 *, void *);
void fn_802371CC(Unk_673C6403 *, Unk_4A174A22 *, u32);
void fn_802432A8(void *);
void fn_80236E10(s32 *, void *);
typedef struct {
    s32 a;
    u16 b;
} __attribute__((packed)) Unk6;
s32 fn_80237604(Unk_673C6403 *arg0, Unk_F5317C5D *arg1, u32 arg2) {
    Unk6 sp8;
    Unk6 *p8 = &sp8;
    u16 count1 = 0;
    u16 count2 = 0;
    Unk_C7387A53 *node;
    void *head;

    p8->a = arg1->unk0x0;
    p8->b = arg1->unk0x4;
    head = (void *)fn_80237D14(arg0, p8, 0, 0, (arg2 >> 1) & 1);
    node = head;
    if (node != NULL) {
        do {
            if (arg2 & 4) {
                s32 n2 = fn_802416F8(fn_802432A0(node));
                if (((Unk_9994C3F5 *)n2)->unk0x8 & 0x20)
                    goto node_next;
            }
            count1 = (u16)(count1 + 1);
            count2 = (u16)(count2 + *(u16 *)((char *)fn_802416F8(fn_802432A0(node)) + 0x32));
            fn_802371CC(arg0, fn_802416F8(fn_802432A0(node)), arg2);
        node_next:
            node = *((void * *)&node->unk0xC);
        } while (node != NULL);
    }
    fn_802432A8(head);
    fn_80236E10((void *)arg0, 0);
    return (s32)((count1 << 16) | count2);
}
