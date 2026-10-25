// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F9B90-0x801F9C64 (212B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 fn_801FC344(void);
void fn_801F83E8(Unk_C7387A53 *, s32);
void fn_801F8B94(Unk_C7387A53 *);

void *fn_801F9B90(Unk_C7387A53 *arg0, void *arg1) {
    void *var_r30;
    Unk_C7387A53 *node;
    s32 var_r29;
    Unk_C7387A53 *temp_r0;
    Unk_C7387A53 *temp_r9;

    var_r30 = arg0;
    node = arg1;
    if (node == NULL) {
        return NULL;
    }
    if ((node->unk0x28 != NULL) &&
        (node->unk0x24 != NULL)) {
        if (fn_801FC344() == 0xC8) {
            return NULL;
        }
    }
    if (node == *((void * *)&arg0->unk0xC)) {
        *((void * *)&arg0->unk0xC) = *((void * *)&node->unk0x24);
        temp_r0 = *((void * *)&node->unk0x24);
        if (temp_r0 != NULL) {
            temp_r0->unk0x28 = 0;
        }
        if (node != NULL) {
            fn_801F83E8(node, 3);
        }
        return NULL;
    }
    fn_801F8B94(*((void * *)&node->unk0x28));
    var_r29 = 0;
    *(s32 *)((node->unk0x28) + 0x24) = var_r29;
    var_r30 = *((void * *)&node->unk0x24);
    if (node != NULL) {
        fn_801F83E8(node, 3);
    }
    temp_r9 = var_r30;
    if (temp_r9 != NULL) {
        temp_r9->unk0x28 = var_r29;
    }
    return var_r30;
}
