// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A4D1C-0x801A4F84 (616B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 CStruct_new(s32);
s32 CStruct_ctor(s32);
void CStruct_delete(CStruct *, s32);
void *fn_80127358(CStruct *, Unk_C7387A53 *);
void AddComponent(CStruct *, s32, s32, void *);
void fn_80127E70(void *, s32, s32, s32);
s32 fn_80129C08(void *, s32, s32, s32, s32);
s32 fn_801A4D1C(CStruct *arg0, s32 arg1, s32 arg2) {
    void *mgr;
    CStruct *entry;
    void *next;
    u32 h;
    s32 ret;

    mgr = (void *)CStruct_ctor(CStruct_new(8));
    entry = fn_80127358((char *)arg0 + 0x6C, NULL);
    if (entry != NULL) {
        do {
            next = fn_80127358((char *)arg0 + 0x6C, entry);
            h = *((u32 *)&entry->unk0x4);
            switch (h) {
            case 0x7D02BCC3u:
            case 0xA1DC81F9u:
            case 0xC15DBF86u:
                fn_80127E70(mgr, entry->unk0x4, 0xD, entry->unk0x8);
                break;
            case 0x130618A0u:
            case 0x2820E997u:
            case 0x2AB66CB8u:
            case 0x4FA8DF27u:
            case 0x562E3ECDu:
                AddComponent(mgr, entry->unk0x4, 3, entry->unk0x8);
                break;
            case 0x3F813177u:
            case 0x439F4704u:
            case 0x6DCB497Cu:
            case 0x9016B4E7u:
            case 0x9B65D7B8u:
            case 0xAE798769u:
            case 0xAF895B3Fu:
            case 0xB1FC0722u:
            case 0xB78D4AAEu:
            case 0xD82F8AC8u:
            case 0xEDF5DB70u:
            case 0xF0D90109u:
            case 0xF73A13E3u:
                fn_80127E70(mgr, entry->unk0x4, 1, entry->unk0x8);
                break;
            }
            entry = next;
        } while (entry != NULL);
    }
    ret = fn_80129C08(mgr, arg1, arg2, 1, 0);
    if (mgr != NULL) {
        CStruct_delete((s32)mgr, 3);
    }
    return ret;
}
