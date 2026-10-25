// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8013B3DC-0x8013B42C (80B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 fn_800145AC(void);
extern void fn_8013B038(void *);
void fn_8013B3DC(Unk_C7387A53 *arg0) {
    void *temp_r30;
    Unk_4E705049 *temp_r9;

    temp_r30 = *((void * *)&arg0->unk0x20);
    *(s32 *)temp_r30 = fn_800145AC();
    fn_8013B038(temp_r30);
    temp_r9 = ((Unk_82779A3F *)temp_r30)->unk0x2300;
    ((void (*)(void *))temp_r9->unk0x1C)(temp_r30 + temp_r9->unk0x18);
}
