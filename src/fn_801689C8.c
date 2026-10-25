// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801689C8-0x80168F8C (1476B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern s32 lbl_802FFE50;
extern s32 lbl_802FFF6C;
extern s32 lbl_80305E80;
extern Unk_80577C09 * lbl_80305E84;
extern s32 lbl_80305E88;
extern char lbl_802A8480[];
extern char lbl_802A8760[];
extern char lbl_802A8768[];
extern char lbl_802A8838[];
extern char lbl_802A8844[];

extern void ScriptCreateTemporaryMemCardPools(s32, s32);
extern void ScriptRemoveTemporaryMemCardPools(s32, s32);
extern void fn_8016A30C(void);
extern s32 fn_8016A320(void);
extern void fn_8016A34C(void);
extern void fn_8016A360(void);
extern void fn_8016A374(void);
extern void fn_8016A388(void);
extern void fn_8016A39C(void);
extern void PauseMusic(s32);
extern void PauseStream(s32);
extern s32 fn_80128C20(CStruct *, void *, void *, s32);
extern s32 GetChecksum_4(CStruct *, void *, void *, s32);
extern s32 GetInteger(CStruct *, s32, s32 *, s32);
extern s32 Game_GetGoalManager(void);
extern void fn_8018568C(Unk_526DA6F2 *);
extern s32 CStruct_new(s32);
extern s32 CStruct_ctor(s32);
extern void fn_80126FF4(Unk_80577C09 *, CStruct *);
extern void s_insert_game_save_info(s32, CStruct *);
extern void s_generate_summary_info(s32, s32, CStruct *);
extern void fn_801275D4(CStruct *, void *, void *);
extern s32 fn_80168890(s32);
extern s32 fn_80129E28(void *, void *);
extern s32 Mem_Alloc_3(s32);
extern s32 fn_80015A58(s32, s32, s32);
extern s32 BannerExists(Unk_C8FEE62D *);
extern s32 s_make_ps2_dir_and_icons(s32, s32, s32, void *, void *);
extern s32 s_make_xbox_dir_and_icons(Unk_31DE137E *, s32, s32, s8 *, s32 *);
extern void fn_801677BC(s32, s32, void *);
extern void sprintf(s32, ...);
extern s32 fn_80015EE0(Unk_C8FEE62D *, u8 *, s32, s32);
extern s32 s_insert_ngc_icon(char *, CScript *, Unk_31DE137E *, s32, s32);
extern s32 s_get_version_number(s32);
extern void fn_80129C08(s32, void *, s32, s32, s32);
extern s32 Crc_GenerateCRCCaseSensitive(void *, s32);
extern s32 fn_80016448(CStruct *, void *, s32);
extern void Mem_Free_3(void *);
extern s32 fn_800163A0(CStruct *);
extern s32 fn_800167E4(s32);
extern void CStruct_delete(CStruct *, s32);
extern s32 fn_8016899C();

s32 ScriptSaveToMemoryCard(CStruct *pParams, CScript *pScript) {
    struct {
        u8 sp8[0x68];
        u8 sp70[0x64];
        s32 pad_D4;
        s32 spD8;
        s32 spDC;
        s32 spE0;
    } fr;
    s32 var_r19;
    s32 flag;
    Unk_31DE137E *fileopen;
    Unk_C8FEE62D *file21;
    s32 temp_r20;
    u8 *buf24;
    u8 *walker;
    u32 temp_r22;
    s32 temp_r23;
    s32 temp_r25;
    s32 temp_r26;
    s32 temp_r27;
    u32 temp_r28;
    s32 temp_r29;
    s32 ctr;
    u32 j;
    register u32 i __asm__("r9");
    s32 wr;
    s32 keyv;
    s32 wr2;

    if (lbl_802FFE50 == 5) {
        ScriptCreateTemporaryMemCardPools(0, 0);
    }
    if (lbl_802FFE50 != 4) {
        PauseMusic(1);
        PauseStream(1);
    }
    lbl_80305E80 = 0;
    fr.spD8 = (s32)lbl_802A8480;
    fn_80128C20(pParams, (s32)lbl_802A8760, &fr.spD8, 0);
    fr.spDC = 0;
    GetChecksum_4(pParams, (s32)lbl_802A8768, &fr.spDC, 0);
    fr.spE0 = 0;
    GetInteger(pParams, QB_SAVEVAULTDATA, &fr.spE0, 0);
    if (fr.spE0 != 0) {
        fr.spDC = lbl_80305E88;
    } else if (fr.spDC == QB_OPTIONSANDPROS) {
        fn_8018568C(Game_GetGoalManager());
    }
    fn_8016A30C();
    flag = 0;
    if (fn_8016A320() != 0) {
        fn_8016A34C();
        flag = 1;
        fn_8016A360();
    } else {
        fn_8016A374();
    }
    temp_r23 = CStruct_ctor(CStruct_new(8));
    if (fr.spE0 != 0) {
        fn_80126FF4(temp_r23, lbl_80305E84);
    } else {
        s_insert_game_save_info(fr.spDC, temp_r23);
    }
    file21 = NULL;
    temp_r26 = CStruct_ctor(CStruct_new(8));
    buf24 = NULL;
    temp_r20 = NULL;
    s_generate_summary_info(temp_r26, fr.spDC, temp_r23);
    var_r19 = 0;
    fn_801275D4(temp_r26, (s32)lbl_802A8838, fr.spD8);
    temp_r27 = fn_80168890(fr.spDC);
    temp_r22 = fn_80129E28(temp_r23, temp_r27);
    temp_r25 = fn_80129E28(temp_r26, 0x64);
    // Operand roles matter, not association: writing the s32 addend first makes
    // ngccc put the +0x2C54 on r22 (want) instead of r25; both are the same sum.
    temp_r29 = (temp_r25 + 0x2C54) + temp_r22;
    temp_r28 = temp_r27 - temp_r29;
    if (temp_r28 != 0 && lbl_802FFE50 != 5) {
        temp_r20 = (s32)Mem_Alloc_3(temp_r28);
        i = 0U;
        if ((u32)var_r19 < temp_r28) {
            do {
                *((u8 *)temp_r20 + i) = 0x69;
                i += 1;
            } while (i < temp_r28);
        }
    }
    fileopen = fn_80015A58(lbl_802FFF6C, 0, 0);
    if (fileopen == NULL || BannerExists(fileopen) == 0) {
        goto exit_free;
    }
    switch (lbl_802FFE50) {
    case 1:
    case 2:
    case 3:
        /* ps2 */
        if (s_make_ps2_dir_and_icons(fileopen, fr.spDC, fr.spD8, &fr.sp8[0], &lbl_80305E80) == 0) {
            goto exit_free;
        }
        break;
    case 5:
        /* gamecube */
        fn_801677BC(fr.spDC, fr.spD8, &fr.sp70[0]);
        sprintf((s32)&fr.sp8[0], (s32)lbl_802A8844, &fr.sp70[0], &fr.sp70[0]);
        break;
    case 4:
        /* xbox */
        if (s_make_xbox_dir_and_icons(fileopen, fr.spDC, fr.spD8, &fr.sp8[0], &lbl_80305E80) == 0) {
            goto exit_free;
        }
        break;
    default:
        goto exit_free;
    }
common:
    file21 = fn_80015EE0(fileopen, &fr.sp8[0], 6, temp_r27);
    lbl_80305E80 = (fileopen->unk0x1C ^ 2) == 0;
    if (file21 == NULL) {
        goto exit_free;
    }
    buf24 = (u8 *)Mem_Alloc_3(temp_r29);
    walker = buf24;
    for (ctr = 0x2C54; ctr != 0; ctr--) {
        *walker = 0;
        walker += 1;
    }
    if (lbl_802FFE50 == 5) {
        if (s_insert_ngc_icon((s32)buf24, fileopen, file21, fr.spDC, fr.spD8) == 0) {
            goto exit_free;
        }
    }
    walker = buf24 + 0x2C54;
    keyv = s_get_version_number(fr.spDC);
    ((Unk_8E42A773 *)buf24)->unk0x2C50 = keyv;
    ((Unk_8E42A773 *)buf24)->unk0x2C48 = temp_r25;
    ((Unk_8E42A773 *)buf24)->unk0x2C4C = temp_r29;
    if (lbl_802FFE50 == 4) {
        fn_80129C08(temp_r26, walker, temp_r25, 0, (s32)fn_8016899C);
    } else {
        fn_80129C08(temp_r26, walker, temp_r25, 0, 0);
    }
    ((Unk_8E42A773 *)buf24)->unk0x2C44 = Crc_GenerateCRCCaseSensitive(walker, temp_r25);
    walker += temp_r25;
    fn_80129C08(temp_r23, walker, temp_r22, 0, 0);
    if (fr.spDC == QB_NETWORKSETTINGS) {
        j = 0U;
        if (j < temp_r22) {
            do {
                walker[j] += 0x69;
                j += 1;
            } while (j < temp_r22);
        }
    }
    ((Unk_8E42A773 *)buf24)->unk0x2C40 = Crc_GenerateCRCCaseSensitive(buf24, temp_r29);
    wr = fn_80016448(file21, buf24, temp_r29);
    lbl_80305E80 = (fileopen->unk0x1C ^ 2) == 0;
    if (wr != temp_r29) {
        goto exit_free;
    }
    if (lbl_802FFE50 != 5 && temp_r28 != 0) {
        wr2 = fn_80016448(file21, (void *)temp_r20, temp_r28);
        lbl_80305E80 = (fileopen->unk0x1C ^ 2) == 0;
        if (wr2 != temp_r28) {
            goto exit_free;
        }
    }
    var_r19 = 1;
exit_free:
    if (temp_r20 != 0) {
        Mem_Free_3((void *)temp_r20);
    }
    if (buf24 != NULL) {
        Mem_Free_3(buf24);
    }
    if (file21 != NULL) {
        s32 vt;
        if (fn_800163A0(file21) == 0) {
            var_r19 = 0;
        }
        if (fn_800167E4(file21) == 0) {
            var_r19 = 0;
        }
        vt = file21->unk0x14;
        ((s32 (*)(void *, s32))((Unk_F5317C5D *)vt)->unk0xC)((char *)file21 + ((Unk_F5317C5D *)vt)->unk0x8, 3);
    }
    if (temp_r26 != 0) {
        CStruct_delete(temp_r26, 3);
    }
    if (temp_r23 != 0) {
        CStruct_delete(temp_r23, 3);
    }
    if (flag != 0) {
        fn_8016A374();
        fn_8016A388();
        fn_8016A39C();
    }
    if (lbl_802FFE50 != 4) {
        PauseMusic(-1);
        PauseStream(-1);
    }
    if (lbl_802FFE50 == 5) {
        ScriptRemoveTemporaryMemCardPools(0, 0);
    }
    return var_r19;
}
