// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801CE65C-0x801CE800 (420B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f32 lbl_802AD314;
extern f32 lbl_802AD318;
extern char lbl_802ADA34[];
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 fn_801EC3F0(Unk_83A1E37F *, void *);
void fn_801D60F4(void *, Unk_5EF41E38 *);
void fn_801D1458(Unk_6EBFA797 *, s32);

bool fn_801CE65C(Unk_820D4746 *arg0, CStruct *arg1) {
    s32 sp18;
    f32 buf[4];
    f32 *q;

    sp18 = 0;
    GetChecksum_2(arg1, 0, &sp18, 0);
    if ((s32)*(s32 *)(arg0->unk0x15BC + (s32)0x1C) == 3) {
        if (sp18 != QB_LIP) {
            fn_801EC3F0(arg0, (s32)lbl_802ADA34);
        }
        if ((s32)*(s32 *)(arg0->unk0x15BC + (s32)0x1C) != 3) {
block_4:
            if (sp18 == QB_LIP) {
                arg0->unk0x25C = 0;
            }
        }
    } else {
        goto block_4;
    }
    if ((s32)*(s32 *)(arg0->unk0x15BC + (s32)0x1C) == 2) {
        f32 v0 = lbl_802AD314;
        f32 v1 = lbl_802AD318;
        q = buf;
        buf[0] = v0;
        q[2] = v0;
        q[1] = v1;
        q[3] = v1;
        fn_801D60F4(arg0, q);
        {
            void *o = *((void * *)&arg0->unk0xC);
            __ps_t *b20;
            __ps_t *b5;

            b20 = (__ps_t *)((char *)arg0 + (s32)0x20);
            b5 = b20 + 4;
            arg0->unk0x20 = ((Unk_130D31C8 *)o)->unk0x78;
            arg0->unk0x28 = ((Unk_130D31C8 *)o)->unk0x80;
            arg0->unk0x30 = ((Unk_130D31C8 *)o)->unk0x88;
            arg0->unk0x38 = ((Unk_130D31C8 *)o)->unk0x90;
            b5[0] = ((Unk_130D31C8 *)o)->unk0x98;
            b5[1] = ((Unk_130D31C8 *)o)->unk0xA0;
            arg0->unk0x50 = ((Unk_130D31C8 *)o)->unk0xA8;
            arg0->unk0x58 = ((Unk_130D31C8 *)o)->unk0xB0;
        }
    }
    if (sp18 == QB_AIR) {
        goto case_439f;
    }
    if ((u32)sp18 <= (u32)QB_AIR) {
        goto done;
    }
    if (sp18 == QB_GROUND) {
        goto case_gnd;
    }
    if (sp18 == QB_LIP) {
        goto case_a549;
    }
    goto done;
case_439f:
    fn_801D1458(arg0, 1);
    goto done;
case_gnd:
    arg0->unk0x1E5 = 0;
    fn_801D1458(arg0, 0);
    goto done;
case_a549:
    fn_801D1458(arg0, 3);
done:
    return true;
}
