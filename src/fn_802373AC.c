// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802373AC-0x80237454 (168B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// Walks the node list at arg0->unk0x80 calling fn_802371CC per node with
// fn_802416F8(fn_802432A0(node)) as the middle argument; clears
// lbl_80305FF4 and frees arg0->unk0x177C8 first.
// Suggested rename: ProcessNodeList
#include "types.h"
#include "structs.h"
void fn_80243B14(s32);
s32 fn_802432A0(Unk_9994C3F5 *);
s32 fn_802416F8(s32);
s32 fn_802371CC(Unk_673C6403 *, Unk_4A174A22 *, void *);
void fn_8022E028(Unk_DB0E2BAB *, s32);
void fn_80230BA4(s32);
void fn_8022D4C4(Unk_DB0E2BAB *);
extern s32 lbl_80305FF4;
void fn_802373AC(Unk_673C6403 *arg0, s32 arg1) {
    Unk_C7387A53 *node;
    void *next;

    lbl_80305FF4 = 0;
    fn_80243B14(arg0->unk0x177C8);
    node = arg0->unk0x80;
    if (node != NULL) {
        do {
            next = *((void * *)&node->unk0xC);
            fn_802371CC(arg0, (void *)fn_802416F8(fn_802432A0(node)), 0);
            node = next;
        } while (node != NULL);
    }
    fn_8022E028(arg0->unk0x0, arg1);
    fn_80230BA4(arg0->unk0x0);
    lbl_80305FF4 = 1;
    if (arg1 != 0) {
        fn_8022D4C4(arg0->unk0x0);
    }
}
