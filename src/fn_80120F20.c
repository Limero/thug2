// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80120F20-0x801210B4 (404B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct {
    char pad0x00[0x10];
    f32 unk10;
    f32 unk14;
    char pad0x18[0x1F4];
    void *unk20C;
    char pad210[0xC];
} Unk_8038F0C0;

/* The two dead stack webs of want: `unkC` gets &lbl_80290E38 (twice) and the
 * nested struct at +4 holds the fn_80119510 result (stored, reloaded for both
 * fn_8011A8FC calls). 0x30 total so the frame is want's 0x88. */
typedef struct {
    s32 unk0;
    s32 unk4;
} In_t;

typedef struct {
    s32 unk0;
    In_t in;
    s32 unkC;
    char pad10[0x20];
} Unk_sp;

extern Unk_8038F0C0 lbl_8038F0C0[];
extern f32 lbl_8029D850;
extern f32 lbl_8029D854;
extern f32 lbl_8029D858;
extern f64 lbl_8029D860;
extern f32 lbl_8029D868;
extern f32 lbl_80302F0C;
extern char lbl_80290E38[];

s32 OSDisableInterrupts(void);
void OSRestoreInterrupts(s32);
s32 fn_80119510(s32);
void fn_80119578(void);
f32 fn_8011A8FC(s32);
void fn_8011F590(void *, void *, f32, f32, f32, s32, s32);

bool fn_80120F20(s32 arg0, f32 farg0, f32 farg1) {
    Unk_sp sp;
    Unk_sp *p8;
    Unk_sp *q8;
    In_t *qC;
    s32 temp_r26;
    s32 temp_r27;
    s32 var_r5;
    f32 temp_f0;
    f32 c850;
    f32 c854;
    f32 fscale;

    if (lbl_8038F0C0[arg0].unk20C != 0) {
        temp_r26 = OSDisableInterrupts();
        p8 = &sp;
        p8->unkC = (s32)lbl_80290E38;
        temp_r27 = (s32)lbl_8038F0C0[arg0].unk20C + 0x138;
        qC = &sp.in;
        qC->unk4 = fn_80119510(0);
        fscale = fn_8011A8FC(qC->unk4);
        c850 = lbl_8029D850;
        c854 = lbl_8029D854;
        farg0 = fscale * c850 * farg0 * c854;
        farg1 = fn_8011A8FC(qC->unk4) * c850 * farg1 * c854;
        temp_f0 = lbl_8038F0C0[arg0].unk10 * lbl_8038F0C0[arg0].unk14 * c854 * lbl_80302F0C * lbl_8029D858 * c854;
        if (!(temp_f0 >= lbl_8029D860)) {
            var_r5 = (s32)temp_f0;
        } else {
            var_r5 = (s32)(temp_f0 - lbl_8029D860);
            var_r5 ^= 0x80000000;
        }
        fn_8011F590((void *)temp_r27, lbl_8038F0C0[arg0].unk20C, farg0, farg1, lbl_8029D868, var_r5, 1);
        OSRestoreInterrupts(temp_r26);
        q8 = &sp;
        q8->unkC = (s32)lbl_80290E38;
        fn_80119578();
    }
    return true;
}
