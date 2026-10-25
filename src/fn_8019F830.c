// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8019F830-0x8019F938 (264B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

extern float lbl_802AAFD0;
extern float lbl_802AAFD4;

void *GetChecksum_3(void *, s32);
void fn_800CC038(void *, s32, s32, s32, f32);
void *CStruct_new(s32);
s32 CStruct_ctor(s32);
void fn_8012772C(void *, s32, f32);
void CStruct_delete(void *, s32);

void fn_8019F830(void *arg0, f32 farg0) {
    f32 temp_f0;
    f32 temp_f13;
    void *node;
    void *temp_r30;
    void **t;
    void (*fp)(void *, s32, void *, s32);

    temp_f0 = lbl_802AAFD0;
    *(f32 *)((char *)arg0 + 0x128) = farg0;
    if (farg0 > temp_f0) {
        *(f32 *)((char *)arg0 + 0x128) = temp_f0;
    }
    temp_f13 = lbl_802AAFD4;
    if (*(f32 *)((char *)arg0 + 0x128) < temp_f13) {
        *(f32 *)((char *)arg0 + 0x128) = temp_f13;
    }
    if (GetChecksum_3(arg0, 0x7149B753) != NULL) {
        fn_800CC038(GetChecksum_3(arg0, 0x7149B753), 0, 0, 0,
                    *(f32 *)((char *)arg0 + 0x128));
        temp_r30 = (void *)CStruct_ctor(CStruct_new(8));
        fn_8012772C(temp_r30, 0xF0D90109, *(f32 *)((char *)arg0 + 0x128));
        node = GetChecksum_3(arg0, 0x7149B753);
        t = *(void **)((char *)node + 0x18);
        fp = (void (*)(void *, s32, void *, s32))t[0x19];
        fp((char *)node + (signed short)((s16 *)t)[0x30], 0xBD4EDD44,
           temp_r30, 0);
        if (temp_r30 != NULL) {
            CStruct_delete(temp_r30, 3);
        }
    }
    *(s32 *)((char *)arg0 + 0x134) = 0;
}
