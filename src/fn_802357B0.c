// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802357B0-0x802358BC (268B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct {
    char _pad0x00[0x10];
    s16 unk0x10;
    s32 unk0x14;
} S8023A0C_vt;

typedef struct {
    char _pad0x00[0x38];
    S8023A0C_vt *unk0x38;
} S8023A0C_node;

typedef struct {
    void *unk0x00;
    s32 unk0x04;
    s32 unk0x08;
    s32 unk0x0C;
    char _pad0x10[0x74];
    s32 unk0x84;
    char _pad0x88[4];
    s32 unk0x8C;
    char _pad0x90[0x1769C];
    s32 unk0x1772C;
    char _pad0x17730[0x98];
    s32 unk0x177C8;
} S802357B0;

void fn_8023B364();
void fn_80243B14(s32);
s32 fn_802432A0(s32);
void fn_8023A670(void *, s32, s32 *);
void fn_802373AC(void *, s32);
void fn_8022D3C0(void *, s32);
void fn_802435EC(s32, s32);
void fn_802432A8(s32);
void fn_8023FAC4(void);

void fn_802357B0(void *arg0, s32 arg1) {
    S802357B0 *self = arg0;
    s32 temp_r3;
    s32 head;
    s32 zero;

    if (self->unk0x04 != 0) {
        s32 mask = self->unk0x1772C & 5;

        if (mask == 0) {
            fn_8023B364();
        }
        fn_80243B14(self->unk0x177C8);
        while ((head = self->unk0x84) != 0) {
            S8023A0C_node *node;

            temp_r3 = fn_802432A0(head);
            fn_8023A670(arg0, temp_r3, &self->unk0x84);
            if (temp_r3 != 0) {
                node = (S8023A0C_node *)temp_r3;
                ((s32 (*)(void *, s32))node->unk0x38->unk0x14)((char *)temp_r3 + node->unk0x38->unk0x10, 3);
            }
        }
        zero = 0;
        self->unk0x8C = zero;
        fn_802373AC(arg0, arg1);
        fn_8022D3C0(self->unk0x00, arg1);
        self->unk0x04 = zero;
        self->unk0x1772C = (self->unk0x1772C & 0xFFFFFFFE) | 4;
        self->unk0x08 = zero;
        if (self->unk0x177C8 != 0) {
            fn_802435EC(self->unk0x177C8, 3);
        }
        self->unk0x177C8 = zero;
        if (self->unk0x0C != 0) {
            fn_802432A8(self->unk0x0C);
        }
        self->unk0x0C = zero;
        fn_8023FAC4();
    }
}
