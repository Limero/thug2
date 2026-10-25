// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801680AC-0x80168298 (492B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_802FFF6C;
extern s32 lbl_802FFE50;
extern char lbl_802A8578[];
extern char lbl_802A8760[];
extern char lbl_802A8768[];
extern char lbl_802A8770[];
extern char lbl_802A877C[];
s32 fn_80015A58(s32, s32, s32);
s32 fn_80128C20(CStruct *, void *, void *, s32);
s32 GetChecksum_4(CStruct *, void *, void *, s32);
s32 s_generate_xbox_directory_name(s32);
s32 fn_80015AB8(s32, s32);
s32 fn_8000B554(void);
void fn_80165660(Unk_F96D0DC8 *, s32, s32);
extern void sprintf(s32, ...);
s32 fn_80015EE0(Unk_C8FEE62D *, u8 *, s32, s32);
s32 fn_80016304(CStruct *, s32, s32);
s32 s_calculate_total_space_used_on_card(s32, s32);
void fn_801276E8(CStruct *, void *, s32);
s32 fn_800163A0(CStruct *);
s32 fn_800167E4(s32);
void fn_80015AB0(s32, s32);
bool ScriptMemCardFileExists(s32 arg0, CScript *arg1) {
    register s32 a0 __asm__("r29");
    u8 sp8[104];
    s32 sp70[6];
    s32 sp88;
    s32 sp8C;
    register s32 chk __asm__("r4");
    s32 card;
    s32 slot;
    Unk_C8FEE62D *file;
    s32 ab8ret;
    s32 b554ret;
    Unk_F5317C5D *vptr;
    s32 size;
    s32 val;

    a0 = arg0;
    card = fn_80015A58(lbl_802FFF6C, 0, 0);
    if (card == 0) {
        return false;
    }
    sp88 = 0;
    fn_80128C20(a0, (s32)lbl_802A8760, &sp88, 0);
    sp8C = 0;
    GetChecksum_4(a0, (s32)lbl_802A8768, &sp8C, 0);
    chk = sp88;
    if (chk == 0 || sp8C == 0) {
        return false;
    }
    sp8[0] = 0;
    slot = 0;
    switch (lbl_802FFE50) {
    case 4:
        slot = s_generate_xbox_directory_name(sp8C);
        ab8ret = fn_80015AB8(card, slot);
        if (ab8ret == 0) {
            return false;
        }
        sprintf((s32)sp8, (s32)lbl_802A8578, ab8ret, ab8ret);
        break;
    case 1:
    case 2:
    case 3:
    case 5:
        a0 = fn_8000B554();
        fn_80165660(sp70, sp88, sp8C);
        sprintf((s32)sp8, (s32)lbl_802A8770, a0, (s32)sp70,
                    a0, (s32)sp70);
        break;
    }
    file = fn_80015EE0(card, sp8, 1, 0);
    if (file != 0) {
        size = fn_80016304(file, 0, 2);
        val = s_calculate_total_space_used_on_card(sp8C, size);
        fn_801276E8(arg1->unk0x18, (s32)lbl_802A877C, val);
        fn_800163A0(file);
        fn_800167E4(file);
        vptr = file->unk0x14;
        ((s32 (*)(s32, s32))(vptr->unk0xC))(
            (s32)((char *)file + vptr->unk0x8), 3);
        return true;
    }
    if (lbl_802FFE50 == 4) {
        fn_80015AB0(card, slot);
    }
    return false;
}
