// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800698E0-0x80069938 (88B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8013183C(void *);;
void fn_800698E0(Unk_7A675EAB *arg0) {
    void *temp_r3;
    Unk_4E705049 *temp_r9;

    temp_r3 = arg0->unk0x58;
    if (temp_r3 != NULL) {
        fn_8013183C(temp_r3);
        arg0->unk0x58 = 0;
    }
    temp_r9 = arg0->unk0x1B8;
    ((s32 (*)(void *))temp_r9->unk0x1C)((char *)arg0 + temp_r9->unk0x18);
}
