// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8007EC7C-0x8007ED94 (280B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_8007DF14(s32);
s32 fn_8009955C(void *, s32, s32);
s32 fn_800963D0(s32, s32);
void Mem_Free(void *);
void Mem_Free2(void *);
void fn_8007EC7C(CScript *arg0) {
    s32 var_r27;
    s32 var_r28;
    u32 var_r29;
    Unk_C8FEE62D *temp_r31;

    if (arg0->unk0x20 != 0) {
        if ((arg0->unk0x18 != 0) && (fn_8007DF14(arg0->unk0x18) != 0)) {
            fn_8009955C((void *)fn_8007DF14(arg0->unk0x18), arg0->unk0x24, arg0->unk0x20);
        }
        var_r29 = 0;
        if (var_r29 < (u32) arg0->unk0x24) {
            var_r27 = 0;
            var_r28 = 0;
            do {
                temp_r31 = *(Unk_C8FEE62D **)(char *)(var_r28 + arg0->unk0x20);
                if (*(u16 *)((char *)temp_r31 + 4) & 0x10) {
                    Mem_Free(*(void **)(*(s32 *)((char *)temp_r31 + 0x14) + 0x34));
                    *(s32 *)(*(s32 *)((char *)temp_r31 + 0x14) + 0x34) = var_r27;
                }
                if (*(u16 *)((char *)temp_r31 + 4) & 0x20) {
                    Mem_Free(*(void **)(*(s32 *)((char *)temp_r31 + 0x14) + 0x3C));
                    *(s32 *)(*(s32 *)((char *)temp_r31 + 0x14) + 0x3C) = var_r27;
                }
                if (*(u16 *)((char *)temp_r31 + 4) & 0x100) {
                    Mem_Free((void *)temp_r31->unk0x14);
                    temp_r31->unk0x14 = var_r27;
                }
                if (temp_r31 != NULL) {
                    fn_800963D0((s32)temp_r31, 3);
                }
                var_r29 += 1;
                var_r28 += 4;
            } while (var_r29 < (u32) arg0->unk0x24);
        }
        if (arg0->unk0x20 != 0) {
            Mem_Free2((void *)arg0->unk0x20);
        }
        arg0->unk0x20 = 0;
    }
}
