// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80124DA0-0x80124E54 (180B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8005481C(void);
void fn_8000A510(Unk_C8FEE62D *, void *);
void sRenderWorld(void);
void fn_80176FA8(void);
void fn_8005483C(void);
void fn_800142FC(void);
void fn_80124DA0(Unk_C5BAE83F *arg0) {
    s32 temp_r30;
    s32 temp_r9;

    temp_r30 = arg0->unk0x4;
    arg0->unk0x4 = 0;
    do {
        temp_r9 = arg0->unk0xF8;
        if (temp_r9 != 0) {
            arg0->unk0xFC = 1;
            arg0->unk0xF8 = (s32) (temp_r9 - 1);
        }
        fn_8005481C();
        fn_8000A510((char *)arg0 + 0xA0, ((s32) arg0->unk0xFC == 0) ? 0 : 1);
        fn_8000A510((char *)arg0 + 8, ((s32) arg0->unk0xFC == 0) ? 0 : 1);
        sRenderWorld();
        fn_80176FA8();
        fn_8005483C();
        fn_800142FC();
        arg0->unk0xFC = 0;
    } while ((s32) arg0->unk0x4 == 0);
    arg0->unk0x4 = temp_r30;
}
