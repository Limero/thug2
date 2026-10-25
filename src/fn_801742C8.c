// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801742C8-0x801744B8 (496B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
#include "mem.h"
extern char lbl_802A8F08[];
extern char lbl_8029F940[];
extern void fn_8002D244(void);
extern void fn_8010BDA4(void);
extern s32 Script_RunScript(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern void fn_8019A3A4(s32 arg0, s32 arg1);
extern void fn_801AAF54(Unk_C7387A53 * arg0, s32 arg1);
extern void fn_801774E4(CScript * arg0);
extern void fn_801834C4(Unk_31DE137E * arg0, s32 arg1);
extern void fn_8012EE64(Unk_069CE08E * arg0, s32 arg1);
extern void fn_8009C8A8(Unk_C8FEE62D * arg0, s32 arg1);
void fn_801742C8(Unk_40426380 *arg0, s32 arg1) {
    register s32 temp_r11 __asm__("r11");
    register s32 temp_r9 __asm__("r9");
    s32 temp_r3;

    arg0->unk0x14 = (s32)lbl_802A8F08;
    fn_8002D244();
    fn_8010BDA4();
    Script_RunScript(QB_UNINIT_LIGHT_MANAGER, 0, 0, 0, 0);
    temp_r3 = arg0->unk0x370;
    if (temp_r3 != 0) {
        fn_8019A3A4(temp_r3, 3);
    }
    Mem_Free(arg0->unk0x374);
    temp_r11 = arg0->unk0x378;
    if (temp_r11 != 0) {
        temp_r9 = ((Unk_68BE2997 *)temp_r11)->unk0x8;
        ((s32 (*)(void *, s32)) ((Unk_4E705049 *)temp_r9)->unk0xC)((void *)((char *)temp_r11 + ((Unk_4E705049 *)temp_r9)->unk0x8), 3);
    }
    temp_r11 = arg0->unk0x37C;
    if (temp_r11 != 0) {
        temp_r9 = ((Unk_68BE2997 *)temp_r11)->unk0x8;
        ((s32 (*)(void *, s32)) ((Unk_4E705049 *)temp_r9)->unk0xC)((void *)((char *)temp_r11 + ((Unk_4E705049 *)temp_r9)->unk0x8), 3);
    }
    temp_r3 = arg0->unk0x28;
    if (temp_r3 != 0) {
        fn_801AAF54(temp_r3, 3);
    }
    temp_r11 = arg0->unk0x24;
    if (temp_r11 != 0) {
        temp_r9 = ((Unk_68BE2997 *)temp_r11)->unk0x6E8;
        ((s32 (*)(void *, s32)) ((Unk_4E705049 *)temp_r9)->unk0xC)((void *)((char *)temp_r11 + ((Unk_4E705049 *)temp_r9)->unk0x8), 3);
    }
    fn_801774E4(arg0);
    temp_r11 = arg0->unk0x398;
    if (temp_r11 != 0) {
        temp_r9 = ((Unk_68BE2997 *)temp_r11)->unk0x10;
        ((s32 (*)(void *, s32)) ((Unk_4E705049 *)temp_r9)->unk0xC)((void *)((char *)temp_r11 + ((Unk_4E705049 *)temp_r9)->unk0x8), 3);
    }
    temp_r3 = arg0->unk0x39C;
    if (temp_r3 != 0) {
        fn_801834C4(temp_r3, 3);
    }
    temp_r11 = arg0->unk0x18;
    if (temp_r11 != 0) {
        temp_r9 = ((Unk_68BE2997 *)temp_r11)->unk0x18;
        ((s32 (*)(void *, s32)) ((Unk_4E705049 *)temp_r9)->unk0x1C)((void *)((char *)temp_r11 + ((Unk_4E705049 *)temp_r9)->unk0x18), 3);
    }
    temp_r11 = arg0->unk0x68;
    if (temp_r11 != 0) {
        temp_r9 = ((Unk_68BE2997 *)temp_r11)->unk0xC;
        ((s32 (*)(void *, s32)) ((Unk_4E705049 *)temp_r9)->unk0xC)((void *)((char *)temp_r11 + ((Unk_4E705049 *)temp_r9)->unk0x8), 3);
    }
    Mem_Free(arg0->unk0x64);
    temp_r3 = arg0->unk0x428;
    if (temp_r3 != 0) {
        fn_8012EE64(temp_r3, 3);
    }
    temp_r9 = (s32)((char *)arg0 + 0x2C);
    ((Unk_4E705049 *)temp_r9)->unk0x14 = (s32)lbl_8029F940;
    *(s32 *)(((Unk_4E705049 *)temp_r9)->unk0x10 + 0xC) = ((Unk_4E705049 *)temp_r9)->unk0xC;
    *(s32 *)(((Unk_4E705049 *)temp_r9)->unk0xC + 0x10) = ((Unk_4E705049 *)temp_r9)->unk0x10;
    ((Unk_4E705049 *)temp_r9)->unk0xC = temp_r9;
    ((Unk_4E705049 *)temp_r9)->unk0x10 = temp_r9;
    fn_8009C8A8(arg0, arg1);
}
