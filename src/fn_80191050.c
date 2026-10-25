// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80191050-0x80191260 (528B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305EAC;
extern s32 lbl_80301A38;
extern s32 lbl_80301B48;
s32 fn_8011E548(s32);
s32 fn_80191FD4(CStruct *);
s32 GetChecksum_2(s32, s32, s32 *, s32);
s32 fn_801745B4(s32);
s32 fn_800A398C(s32);
s32 CStruct_new(s32);
s32 CStruct_ctor(s32);
void AddChecksum(s32, s32, s32);
void AddInteger(s32, s32, s32);
void GetChecksum_3(s32, s32);
s32 fn_800CBDE0(void);
void fn_80191618(CStruct *, s32, s32);
s32 fn_8011C820(s32, s32);
s32 fn_800F2AD8(s32, s32, s32);
s32 Script_SpawnScript(s32, s32, s32, s32, s32, s32, s32, s32);
void CObject_RemoveRefLink(s32, s32 *);
void CObject_AddRefLink(s32, s32 *);
void CStruct_delete(s32, s32);

void fn_80191050(CStruct *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 sp10;
    volatile s32 sp8;
    volatile s32 spC;
    s32 temp_r3;
    s32 var_r3;
    /* This pin and the `sel` pin below emit no instruction; they only stop
       the allocator from swapping the two callee-saved homes (unpinned, arg1
       takes r29 and this result r28, and every use site flips with it). */
    register s32 temp_r29 asm("r29");
    s32 temp_r30;
    s32 temp_r3b;
    s32 temp_r31;

    if ((arg0->unk0x4 == 0) && (fn_8011E548(arg1) != 0)) {
        temp_r3 = fn_80191FD4(arg0);
        sp10 = arg3;
        if (arg3 == 0) {
            GetChecksum_2(temp_r3, QB_TRIGGER_OBJ_ID, &sp10, 1);
        }
        {
            /* r4 is the home the QB_TRIGGER_OBJ_ID constant leaves free. */
            register s32 sel asm("r4");

            sel = sp10;
            if (sel == QB_SKATER) {
                var_r3 = fn_801745B4(lbl_80305EAC);
            } else {
                var_r3 = fn_800A398C(lbl_80301A38);
            }
        }
        if (var_r3 != 0) {
            temp_r31 = CStruct_ctor(CStruct_new(8));
            AddChecksum(temp_r31, QB_STREAM_CHECKSUM, arg1);
            if (arg2 == 0) {
                AddInteger(temp_r31, QB_USE_POS_INFO, 0);
                GetChecksum_3(var_r3, QB_ANIMBLENDER);
                temp_r29 = fn_800CBDE0();
                if (arg4 != 0) {
                    fn_80191618(arg0, arg1, temp_r29);
                }
                temp_r30 = fn_8011C820(arg1, 0x66);
                AddChecksum(temp_r31, QB_STREAMID, temp_r30);
                arg0->unk0x10 = temp_r30;
                if (fn_800F2AD8(lbl_80301B48, arg1 + temp_r29, 0) != 0) {
                    AddChecksum(temp_r31, 0, QB_PLAY_ANIM);
                    arg0->unk0xC = sp10;
                }
            }
            sp8 = 0;
            spC = 0;
            temp_r3b = Script_SpawnScript(QB_GOAL_PLAY_STREAM, temp_r31, 0, 0, 0, 0, 0, 0);
            {
                s32 *p = &((Unk_FFAD6788 *)temp_r3b)->unk0xBC;

                if (*p != 0) {
                    CObject_RemoveRefLink(*p, p);
                    *p = 0;
                }
                *p = var_r3;
                if (*p != 0) {
                    CObject_AddRefLink(var_r3, p);
                }
            }
            if (temp_r31 != 0) {
                CStruct_delete(temp_r31, 3);
            }
        }
    }
}
