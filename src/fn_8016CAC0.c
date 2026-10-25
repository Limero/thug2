// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8016CAC0-0x8016CCAC (492B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_802FFE98;
extern bool lbl_802FFE58;
extern s32 lbl_8030191C;
extern s32 lbl_80303148;
extern void fn_8000F2F8(Unk_9F352E7C * arg0, s32 arg1);
extern void fn_8000A578(void *arg0, s32 arg1);
extern void fn_8000F320(Unk_F12C5E01 * arg0);
extern void *fn_80139510(s32 arg0, s32 arg1, Unk_C8FEE62D * arg2, s32 arg3, s32 arg4, s32 arg5);
void fn_8016C6FC(void);
void fn_8016C814(void);
void fn_8016C81C(void);
void fn_8016C77C(void);
void fn_8016C890(void);
void fn_8016C918(void);
void fn_8016C940(void);
void fn_8016CAC0(Unk_A9157FE7 *arg0) {
    register s32 temp_r26 __asm__("r26");
    register s32 temp_r27 __asm__("r27");
    register s32 temp_r28 __asm__("r28");
    register s32 off2 __asm__("r11");
    register s32 val2 __asm__("r9");
    Unk_89783F6B *temp_r3;
    CScript *temp_r29;
    CScript *temp_r30;

    temp_r3 = (void *)lbl_802FFE98;
    temp_r26 = lbl_8030191C;
    temp_r28 = lbl_80303148;
    fn_8000F2F8(temp_r3, temp_r3->unk0x124);
    if (lbl_802FFE58 == 0) {
        fn_80139510(arg0->unk0x54 + 4, 0x20, (s32)fn_8016C6FC, 3, 0, 0x80);
        fn_80139510(arg0->unk0x54 + 4, 0x21, (s32)fn_8016C814, 3, 0, 0x80);
        fn_80139510(arg0->unk0x54 + 4, 0x22, (s32)fn_8016C81C, 3, 0, 0x80);
        fn_80139510(arg0->unk0x54 + 4, 0x2A, (s32)fn_8016C77C, 3, 0, 0x80);
        fn_80139510(arg0->unk0x54 + 4, 0x23, (s32)fn_8016C890, 3, (s32)arg0, 0x80);
        fn_80139510(arg0->unk0x54 + 4, 0x24, (s32)fn_8016C918, 3, (s32)arg0, 0x80);
        fn_80139510(arg0->unk0x54 + 4, 0x2B, (s32)fn_8016C940, 3, (s32)arg0, 0x80);
    }
    temp_r28 += 8;
    temp_r27 = temp_r26 + 8;
    fn_8000A578(temp_r28, arg0->unk0x20);
    temp_r30 = *((s32 *)&arg0->unk0x18);
    fn_8000A578(((temp_r30->unk0x24 * 0x94) + temp_r26 + 0xC), temp_r30);
    temp_r30->unk0x1C = (temp_r30->unk0x24 * 0x94) + temp_r26 + 0x58;
    temp_r30->unk0x20 = *(s32 *)((char *)temp_r27 + (temp_r30->unk0x24 * 0x94));
    temp_r29 = *((s32 *)&arg0->unk0x1C);
    fn_8000A578(((temp_r29->unk0x24 * 0x94) + temp_r26 + 0xC), temp_r29);
    off2 = temp_r29->unk0x24 * 0x94;
    val2 = off2 + temp_r26 + 0x58;
    temp_r29->unk0x1C = val2;
    temp_r29->unk0x20 = *(s32 *)((char *)temp_r27 + off2);
    fn_8000A578(temp_r28, arg0->unk0x24);
    fn_8000F320((void *)lbl_802FFE98);
}
