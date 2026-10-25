// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802327E0-0x80232A40 (608B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// Identification: object/UI struct init (the 608B-class exemplar) — copies
// byte values from a child struct (+0x1C, minus 0x80) into f32 fields
// +0x58..+0x64 and sets the +0x48 flag word from bits 0x10/0x20.
#include "types.h"
#include "structs.h"
void fn_802327E0(CScript *arg0, s32 arg7) {
    s32 temp_r0;
    CStruct *temp_r4;
    CScript *temp_r9;
    CScript *temp_r9_2;
    CScript *temp_r9_3;
    CScript *temp_r9_4;
    CScript *temp_r9_5;

    temp_r4 = arg0->unk0x2C;
    temp_r4->unk0x48 = 0;
    *((f32 *)&temp_r4->unk0x58) = (f32) (f64) (*(u8 *)(*(s32 *)((char *)((char *)arg0) + 0x1C) + 0x1) - 0x80);
    *((f32 *)&temp_r4->unk0x5C) = (f32) (f64) (*(u8 *)(*(s32 *)((char *)((char *)arg0) + 0x1C) + 0x2) - 0x80);
    *((f32 *)&temp_r4->unk0x60) = (f32) (f64) (*(u8 *)(*(s32 *)((char *)((char *)arg0) + 0x1C) + 0x3) - 0x80);
    *((f32 *)&temp_r4->unk0x64) = (f32) (f64) (*(u8 *)(*(s32 *)((char *)((char *)arg0) + 0x1C) + 0x4) - 0x80);
    if (*(s32 *)(*(s32 *)((char *)((char *)arg0) + 0x1C) + 0x20) & 0x10) {
        temp_r4->unk0x48 = 4;
    }
    if (*(s32 *)(*(s32 *)((char *)((char *)arg0) + 0x1C) + 0x20) & 0x20) {
        temp_r4->unk0x48 = (s32) (temp_r4->unk0x48 | 2);
    }
    if (*(s32 *)(*(s32 *)((char *)((char *)arg0) + 0x1C) + 0x20) & 0x40) {
        temp_r4->unk0x48 = (s32) (temp_r4->unk0x48 | 0x20);
    }
    if (*(s32 *)(*(s32 *)((char *)((char *)arg0) + 0x1C) + 0x20) & 0x80) {
        temp_r4->unk0x48 = (s32) (temp_r4->unk0x48 | 0x40);
    }
    temp_r9 = arg0->unk0x1C;
    if (!(temp_r9->unk0x1C & 0x40000)) {
        if (temp_r9->unk0x20 & 4) {
            temp_r4->unk0x48 = (s32) (temp_r4->unk0x48 | 0x80);
        }
        if (*(s32 *)(*(s32 *)((char *)((char *)arg0) + 0x1C) + 0x20) & 8) {
            temp_r4->unk0x48 = (s32) (temp_r4->unk0x48 | 0x100);
        }
    }
    temp_r9_2 = arg0->unk0x1C;
    if ((temp_r9_2->unk0x20 & 0x1000) && (temp_r9_2->unk0x1C & 8)) {
        temp_r4->unk0x48 = (s32) (temp_r4->unk0x48 | 0x800);
    }
    temp_r9_3 = arg0->unk0x1C;
    if ((temp_r9_3->unk0x20 & 0x4000) && (temp_r9_3->unk0x1C & 8)) {
        temp_r4->unk0x48 = (s32) (temp_r4->unk0x48 | 0x1000);
    }
    temp_r9_4 = arg0->unk0x1C;
    if ((temp_r9_4->unk0x20 & 0x1000) && (temp_r9_4->unk0x1C & 4)) {
        temp_r4->unk0x48 = (s32) (temp_r4->unk0x48 | 1);
    }
    temp_r9_5 = arg0->unk0x1C;
    if ((temp_r9_5->unk0x20 & 0x4000) && (temp_r9_5->unk0x1C & 4)) {
        temp_r4->unk0x48 = (s32) (temp_r4->unk0x48 | 0x8000);
    }
    temp_r0 = *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0x1C) + 0x1C);
    if (temp_r0 & 0x40000) {
        if (temp_r0 & 4) {
            temp_r4->unk0x48 = (s32) (temp_r4->unk0x48 | 0x4000);
        }
        if (*(s32 *)(*(s32 *)((char *)((char *)arg0) + 0x1C) + 0x1C) & 8) {
            temp_r4->unk0x48 = (s32) (temp_r4->unk0x48 | 0x2000);
        }
    }
}
