// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80169070-0x801694D4 (1124B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern s32 lbl_802FFE50;
extern s32 lbl_802FFF6C;
extern s32 lbl_80305E84;
extern s32 lbl_80305E88;
extern char lbl_802A8480[];
extern char lbl_802A8578[];
extern char lbl_802A8760[];
extern char lbl_802A8768[];
extern char lbl_802A8770[];
extern char lbl_802A8844[];

extern void PauseMusic(s32);
extern void PauseStream(s32);
extern s32 CStruct_new(s32);
extern s32 CStruct_ctor(s32);
extern void fn_80126FF4(Unk_80577C09 *, CStruct *);
extern void CStruct_delete(CStruct *, s32);
extern s32 GetInteger(CStruct *, s32, s32 *, s32);
extern s32 fn_80128C20(CStruct *, void *, void *, s32);
extern s32 GetChecksum_4(CStruct *, void *, void *, s32);
extern s32 fn_80015A58(s32, s32, s32);
extern s32 BannerExists(Unk_C8FEE62D *);
extern s32 fn_80015AB8(s32, s32);
extern s32 fn_80016304(CStruct *, s32, s32);
extern s32 fn_8001666C(Unk_C7387A53 *, void *, s32);
extern s32 fn_800167E4(s32);
extern s32 fn_80015EE0(Unk_C8FEE62D *, u8 *, s32, s32);
extern void Mem_Free_3(void *);
extern s32 Mem_Alloc_3(s32);
extern s32 Crc_GenerateCRCCaseSensitive(void *, s32);
extern s32 fn_8000B554(void);
extern void AddChecksum(CStruct *, s32, s32);
extern s32 fn_80165660(Unk_F96D0DC8 *, s32, s32);
extern void fn_801677BC(s32, s32, void *);
extern s32 s_get_version_number(s32);
extern s32 s_generate_xbox_directory_name(s32, s32);
extern s32 fn_80168890(s32);
extern s32 fn_80129EA0(CStruct *, u8 *);
extern s32 s_read_game_save_info(s32, CStruct *, CScript *, CStruct *);
extern s32 Script_RunScript(s32, s32, s32, s32, s32);
extern void sprintf(s32, ...);

s32 ScriptLoadFromMemoryCard(CStruct *pParams, CScript *pScript) {
    struct {
        u8 sp8[0x68];
        u8 sp70[0x18];
        u8 sp88[0x68];
        s32 spF0;
        s32 spF4;
        s32 spF8;
    } fr;
    register s32 var_r22 __asm__("r22");
    s32 temp_r23;
    s32 temp_r26;
    Unk_C8FEE62D *fh;
    u8 *buf;
    s32 size;
    s32 ok;
    s32 szfield;
    s32 savedck;
    u8 *ptr;
    s32 newEntry;
    s32 *p84;
    s32 fileopen;
    s32 temp_r3;
    s32 i;
    s32 n;
    s32 b554;

    if (lbl_802FFE50 != 4) {
        PauseMusic(1);
        PauseStream(1);
    }
    var_r22 = 0;
    fh = NULL;
    buf = NULL;
    temp_r23 = CStruct_ctor(CStruct_new(8));
    temp_r26 = CStruct_ctor(CStruct_new(8));
    fr.spF0 = var_r22;
    { register s32 z8 __asm__("r0"); z8 = 0; fr.spF8 = z8; }
    fr.spF4 = (s32)lbl_802A8480;
    GetInteger(pParams, QB_LOADFORUPLOAD, &fr.spF0, 0);
    fileopen = fn_80015A58(lbl_802FFF6C, 0, 0);
    if (fileopen == NULL) {
        goto cleanup;
    }
    if (BannerExists(fileopen) == 0) {
        goto cleanup;
    }
    fn_80128C20(pParams, (s32)lbl_802A8760, &fr.spF4, 0);
    GetChecksum_4(pParams, (s32)lbl_802A8768, &fr.spF8, 0);
    fr.sp8[0] = (u8)var_r22;
    switch (lbl_802FFE50) {
    case 1:
    case 2:
    case 3:
        b554 = fn_8000B554();
        fn_80165660(&fr.sp70[0], fr.spF4, fr.spF8);
        sprintf((s32)&fr.sp8[0], (s32)lbl_802A8770, b554, &fr.sp70[0], b554, &fr.sp70[0]);
        break;
    case 5:
        fn_801677BC(fr.spF8, fr.spF4, &fr.sp88[0]);
        sprintf((s32)&fr.sp8[0], (s32)lbl_802A8844, &fr.sp88[0], &fr.sp88[0]);
        break;
    case 4:
        temp_r3 = fn_80015AB8(fileopen, s_generate_xbox_directory_name(fr.spF8, fr.spF4));
        if (temp_r3 == NULL) {
            goto cleanup;
        }
        sprintf((s32)&fr.sp8[0], (s32)lbl_802A8578, temp_r3, temp_r3);
        break;
    default:
        goto cleanup;
    }
    fh = fn_80015EE0(fileopen, &fr.sp8[0], 1, 0);
    if (fh == NULL) {
        goto release;
    }
    size = fn_80016304(fh, 0, 2);
    if (size != fn_80168890(fr.spF8)) {
        AddChecksum(pScript->unk0x18, 0, QB_CORRUPTEDDATA);
        goto cleanup;
    }
    buf = Mem_Alloc_3(size);
    fn_80016304(fh, 0, 0);
    if (fn_8001666C(fh, buf, size) != size) {
        goto cleanup;
    }
    szfield = ((Unk_8E42A773 *)buf)->unk0x2C4C;
    ok = 0;
    savedck = ((Unk_8E42A773 *)buf)->unk0x2C40;
    ((Unk_8E42A773 *)buf)->unk0x2C40 = 0;
    if ((szfield <= 0x7A120) && (Crc_GenerateCRCCaseSensitive(buf, szfield) == savedck)) {
        ok = (((Unk_8E42A773 *)buf)->unk0x2C50 ^ s_get_version_number(fr.spF8)) == 0;
    }
    if (ok != 0) {
        ptr = (u8 *)fn_80129EA0(temp_r23, buf + 0x2C54);
        if (fr.spF8 == QB_NETWORKSETTINGS) {
            n = ((Unk_8E42A773 *)buf)->unk0x2C4C - ((s32)((char *)ptr - (char *)buf));
            i = 0;
            if (i < n) {
                do {
                    ptr[i] -= 0x69;
                    i += 1;
                } while (i < n);
            }
        }
        fn_80129EA0(temp_r26, ptr);
        if (fr.spF0 != 0) {
            p84 = &lbl_80305E84;
            newEntry = CStruct_ctor(CStruct_new(8));
            *p84 = newEntry;
            fn_80126FF4(newEntry, temp_r26);
            lbl_80305E88 = fr.spF8;
            if (fr.spF8 == QB_CAT) {
                s_read_game_save_info(QB_CAT, temp_r26, pScript, 0);
            }
        } else {
            s_read_game_save_info(fr.spF8, temp_r26, pScript, pParams);
        }
        var_r22 = 1;
    } else {
        AddChecksum(pScript->unk0x18, 0, QB_CORRUPTEDDATA);
    }
    if (var_r22 == 0) {
        goto cleanup;
    }
    if (fr.spF0 != 0) {
        goto cleanup;
    }
    Script_RunScript(QB_POST_LOAD_FROM_MEMORY_CARD, pParams, 0, 0, 0);
cleanup:
    if (fh != NULL) {
        s32 vt;
        fn_800167E4(fh);
        vt = fh->unk0x14;
        ((s32 (*)(void *, s32))((Unk_F5317C5D *)vt)->unk0xC)((char *)fh + ((Unk_F5317C5D *)vt)->unk0x8, 3);
    }
release:
    if (buf != NULL) {
        Mem_Free_3(buf);
    }
    if (temp_r23 != NULL) {
        CStruct_delete(temp_r23, 3);
    }
    if (temp_r26 != NULL) {
        CStruct_delete(temp_r26, 3);
    }
    if (lbl_802FFE50 != 4) {
        PauseMusic(-1);
        PauseStream(-1);
    }
    return var_r22;
}
