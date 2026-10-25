// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802533B0-0x80253694 (740B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -msdata=eabi -G4
#include "types.h"
#include "structs.h"
s32 fn_80257CC4(s32, s32);
void fn_8024EBD8(s32, s32);
void fn_80254C8C(s32);
extern s32 lbl_803CA350[]; /* class table A @0x803CA350 */
extern s32 lbl_803CA340; /* heap handle, .sdata */
extern s32 lbl_80308040[]; /* class table B @0x80308040 */

void fn_802533B0(CStruct *arg0) {
    register Unk_DB0E2BAB *r29 asm("r29");
    Unk_C8FEE62D *r26;
    Unk_C8FEE62D *r25;
    s32 i;

    if (arg0 != NULL) {
        r26 = (Unk_C8FEE62D *)arg0->unk0x0;
        r25 = NULL;
        if (r26 != NULL) {
            r25 = (Unk_C8FEE62D *)r26->unk0x1C;
        }
        r29 = (Unk_DB0E2BAB *)arg0->unk0x50;
        if (r29 != NULL) {
            if (r29->unk0x0 != 0) {
                fn_8024EBD8(lbl_803CA340, r29->unk0x0);
            }
            if (r29->unk0x4 != 0) {
                fn_8024EBD8(lbl_803CA340, r29->unk0x4);
            }
            if (r29->unk0x8 != 0) {
                fn_80254C8C(*(s32 *)r29->unk0x8);
                fn_8024EBD8(lbl_803CA340, *(s32 *)r29->unk0x8);
                fn_8024EBD8(lbl_803CA340, r29->unk0x8);
            }
            if (r29->unk0xC != 0) {
                fn_80254C8C(*(s32 *)r29->unk0xC);
                fn_8024EBD8(lbl_803CA340, *(s32 *)r29->unk0xC);
                fn_8024EBD8(lbl_803CA340, r29->unk0xC);
            }
            if (r29->unk0x14 != 0) {
                for (i = 0; i < r25->unk0x10; i++) {
                    ((void (*)(s32)) * (s32 *)((char *)lbl_803CA350[((s32 *)((char *)r25 + 0x320))[i]] + 0xC))(
                        ((s32 *)r29->unk0x14)[i]);
                }
                fn_8024EBD8(lbl_803CA340, r29->unk0x14);
            }
            if (r29->unk0x18 != 0) {
                for (i = 0; i < r25->unk0x14; i++) {
                    ((void (*)(s32)) * (s32 *)((char *)lbl_80308040[((s32 *)((char *)r25 + 0x520))[i]] + 0xC))(
                        ((s32 *)r29->unk0x18)[i]);
                }
                fn_8024EBD8(lbl_803CA340, r29->unk0x18);
            }
        }
        if (arg0->unk0x4 != 0) {
            for (i = 0; i < r26->unk0x4; i++) {
                if (((s32 *)arg0->unk0x4)[i] != 0) {
                    fn_8024EBD8(lbl_803CA340, ((s32 *)arg0->unk0x4)[i]);
                }
            }
            fn_8024EBD8(lbl_803CA340, arg0->unk0x4);
        }
        if (arg0->unk0x8 != 0) {
            for (i = 0; i < r26->unk0x4; i++) {
                if (((s32 *)arg0->unk0x8)[i] != 0) {
                    fn_8024EBD8(lbl_803CA340, ((s32 *)arg0->unk0x8)[i]);
                }
            }
            fn_8024EBD8(lbl_803CA340, arg0->unk0x8);
            if (arg0->unk0xC != 0) {
                fn_8024EBD8(lbl_803CA340, arg0->unk0xC);
            }
        }
        if (r29 != NULL) {
            if (r29->unk0x1C != 0) {
                fn_8024EBD8(lbl_803CA340, r29->unk0x1C);
            }
            if (r29->unk0x20 != 0) {
                fn_8024EBD8(lbl_803CA340, r29->unk0x20);
            }
            if (r29->unk0x24 != 0) {
                fn_8024EBD8(lbl_803CA340, r29->unk0x24);
            }
            fn_8024EBD8(lbl_803CA340, (s32)r29);
        }
        fn_80257CC4((s32)arg0, 0x58);
    }
}
