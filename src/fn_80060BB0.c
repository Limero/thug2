// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80060BB0-0x80060C60 (176B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void *fn_800F2AD8(s32, s32, s32);
extern s32 lbl_80301B48;

// Payload object reached through node->unk0x0.
typedef struct S60BB0Obj {
    struct S60BB0Obj *unk0x0;
    struct S60BB0Obj *unk0x4;
    char pad0x8[4];
    struct S60BB0Obj *unk0xC;   // direct owner, preferred when non-NULL
    struct S60BB0Obj *unk0x10;  // otherwise resolved through the registry
    char pad0x14[0x9C];
    s32 unk0xB0;                // the flag word this whole function ORs together
} S60BB0Obj;

// 12-byte local walk cursor. want allocates a 0x8..0x17 local region and
// references only 0x8 (head) and 0x10 (cur); 0xC is allocated but never
// touched, which only happens for a three-word local. Being an aggregate is
// what keeps both pointers memory-resident and reproduces the 0x20 frame
// with just r30/r31 callee-saved.
typedef struct S60BB0Cursor {
    S60BB0Obj *head;
    s32 pad;
    S60BB0Obj *cur;
} S60BB0Cursor;

s32 fn_80060BB0(S60BB0Obj *arg0) {
    S60BB0Cursor w;
    s32 result;

    w.head = arg0->unk0x10;
    result = 0;
    w.cur = (w.head != NULL) ? w.head->unk0x4 : NULL;
    if (w.cur != w.head) {
        do {
            S60BB0Obj *obj = w.cur->unk0x0;
            S60BB0Obj *m = obj->unk0xC;
            if (m != NULL) {
                result |= m->unk0xB0;
            } else {
                S60BB0Obj *x = obj->unk0x10;
                if (x != NULL) {
                    S60BB0Obj *t = (S60BB0Obj *)fn_800F2AD8(lbl_80301B48, (s32)x, 1);
                    if (t != NULL) {
                        result |= t->unk0xB0;
                    }
                }
            }
            w.cur = w.cur->unk0x4;
        } while (w.cur != w.head);
    }
    return result;
}
