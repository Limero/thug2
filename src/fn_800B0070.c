// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800B0070-0x800B01B4 (324B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void fn_800AF738(void);
void fn_800AE194(void *, void *, void *);
void fn_800AEBCC(void *);
void fn_800AB990(void *);
#include "structs.h"
s32 fn_800AF78C(s32);
void Script_RunScript(s32, s32, s32, s32, s32);
typedef struct {
    u8 _pad[0x68];
    s16 unk0x68;
    s32 (*unk0x6C)(void *, s32);
} Vtbl800B0070;
void fn_800B0070(Unk_C8FEE62D *arg0) {
    s32 temp_r0;
    s32 temp_r9;
    CStruct *temp_r9_2;
    register s32 t3c __asm__("r3");

    t3c = arg0->unk0x3C;
    if (t3c != 0) {
        if ((s32) arg0->unk0x6C != 0) {
            if (fn_800ADCD4() != 0) {
                if (((s32) arg0->unk0x48 == 0) && ((s32) arg0->unk0x44 != 0)) {
                    Script_RunScript(arg0->unk0x44, 0, 0, 0, 0);
                    arg0->unk0x48 = 1;
                }
                if ((s32) arg0->unk0x70 != 0) {
                    fn_800AF78C(arg0->unk0x3C);
                    fn_800AB990(arg0->unk0x3C);
                    fn_800AEBCC(arg0->unk0x3C);
                } else {
                    fn_800AE194(arg0->unk0x3C, arg0->unk0x18, arg0->unk0x50);
                }
                temp_r9 = arg0->unk0x74;
                if (temp_r9 > -1) {
                    temp_r0 = temp_r9 - 1;
                    arg0->unk0x74 = temp_r0;
                    if (temp_r0 == 0) {
                        temp_r9_2 = arg0->unk0x14;
                        arg0->unk0x74 = -1;
                        ((Vtbl800B0070 *)temp_r9_2)->unk0x6C((char *)arg0 + ((Vtbl800B0070 *)temp_r9_2)->unk0x68, 1);
                    }
                }
            }
        } else {
            if ((s32) arg0->unk0x48 == 0) {
                fn_800AF738();
                if ((s32) arg0->unk0x44 != 0) {
                    Script_RunScript(arg0->unk0x44, 0, 0, 0, 0);
                }
            }
            arg0->unk0x48 = 1;
            fn_800AE194(arg0->unk0x3C, arg0->unk0x18, arg0->unk0x50);
        }
    }
}
