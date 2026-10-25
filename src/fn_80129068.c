// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80129068-0x80129114 (172B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

typedef struct {
    char pad0x0[2];
    s8 unk0x2;
    char pad0x3;
    volatile s32 unk0x4;
    s32 unk0x8;
} A129068;

extern s32 lbl_802FFE98;
extern void *Mem_Alloc_3(u32);
extern void fn_8000F2F8(void *, void *);
extern void fn_8000F320(void *);
extern void fn_80128FFC(void);

void fn_80129068(A129068 *arg0, s32 arg1, s8 arg2) {
    u32 i;
    char *p;

    fn_80128FFC();
    arg0->unk0x2 = arg2;
    arg0->unk0x4 = arg1;
    if (arg1 != 0) {
        if (arg1 != 1) {
            fn_8000F2F8((void *)lbl_802FFE98,
                        *(s32 *)((char *)lbl_802FFE98 + 0x12C));
            arg0->unk0x8 = (s32)Mem_Alloc_3((u32)arg0->unk0x4 * 4);
            fn_8000F320((void *)lbl_802FFE98);
            i = 0U;
            p = (char *)arg0->unk0x8;
            while (i < (u32)arg0->unk0x4) {
                *(s32 *)p = 0;
                i += 1;
                p += 4;
            }
        }
    } else {
        arg0->unk0x2 = (s8)arg1;
    }
}
