// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8006A4B0-0x8006A5F0 (320B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

typedef struct A4B0_VT {
    char _00[8];
    s16 off8;
    char _0A[2];
    s32 (*fn0C)(void *, s32);
} A4B0_VT;

typedef struct A4B0_OBJ {
    s32 unk0x0;
    s32 unk0x4;
    s32 unk0x8;
    s32 unk0xC;
    char pad0x10[0x1A8];
    A4B0_VT *unk0x1B8;
} A4B0_OBJ;

typedef struct A4B0_NODE {
    A4B0_OBJ *unk0x0;
    struct A4B0_NODE *unk0x4;
    struct A4B0_NODE *unk0x8;
} A4B0_NODE;

typedef struct A4B0_HDR {
    A4B0_NODE *unk0x0;
    s32 unk0x4;
} A4B0_HDR;

void Mem_Free(s32);
void fn_8013183C(s32);
s32 fn_80069838(void *);
void fn_800698E0(void *);

void fn_8006A4B0(A4B0_HDR *arg0, A4B0_OBJ *arg1) {
    A4B0_NODE *sp8[9];
    A4B0_OBJ *temp_r11;
    A4B0_VT *temp_r9;
    A4B0_NODE *n;

    if (*(s32 *)((char *)fn_80069838(arg1) + 0x50) != 0) {
        fn_8013183C(*(s32 *)((char *)fn_80069838(arg1) + 0x50));
        *(s32 *)((char *)fn_80069838(arg1) + 0x50) = 0;
    }
    sp8[0] = arg0->unk0x0 != 0 ? arg0->unk0x0->unk0x4 : 0;
    sp8[2] = arg0->unk0x0;
    if (sp8[0] != arg0->unk0x0) {
        do {
            if (((A4B0_OBJ *)sp8[0]->unk0x0)->unk0xC == arg1->unk0xC) {
                fn_800698E0(sp8[0]->unk0x0);
                temp_r11 = sp8[0]->unk0x0;
                if (temp_r11 != NULL) {
                    temp_r9 = temp_r11->unk0x1B8;
                    temp_r9->fn0C((char *)temp_r11 + temp_r9->off8, 3);
                }
                n = sp8[0];
                sp8[4] = n;
                sp8[8] = n;
                sp8[4] = n->unk0x4;
                sp8[6] = n;
                if (n != arg0->unk0x0) {
                    n->unk0x8->unk0x4 = n->unk0x4;
                    n->unk0x4->unk0x8 = n->unk0x8;
                    Mem_Free((s32)n);
                    arg0->unk0x4 = arg0->unk0x4 - 1;
                }
                sp8[2] = sp8[4];
                break;
            }
            sp8[0] = sp8[0]->unk0x4;
            sp8[2] = arg0->unk0x0;
        } while (sp8[0] != arg0->unk0x0);
    }
}
