// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80243CE8-0x80243E4C (356B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 CStruct_new(s32);
s32 CStruct_ctor(s32);
void AddChecksum(CStruct *, s32, s32);
void AddInteger(CStruct *, s32, s32);
void AddString(CStruct *, s32, void *);
s32 Script_GetInteger(s32, s32);
void CStruct_delete(CStruct *, s32);

void fn_80243CE8(s32 arg0, s32 arg1, Unk_FFAD6788 *arg2) {
    s32 mgr;
    s32 i;
    s32 off = arg1 * 4;
    register s32 sel __asm__("r29");

    for (i = 0; i <= 1; i++) {
        char *fb = (char *)arg0 + 0x84;
        char *base;
        sel = 1 - i;
        __asm__ volatile("" : "+r"(fb));
        if (*(s32 *)(fb + off) != 0) {
            sel = i;
        }
        base = (char *)arg0 + 4;
        mgr = CStruct_ctor(CStruct_new(8));
        {
            register s32 e __asm__("r9");
            s32 sx;
            __asm__("slwi %0,%1,2" : "=&r"(sx) : "r"(sel));
            e = *(s32 *)(base + off);
            e = e + 4;
            AddChecksum(mgr, QB_GAPID, *(s32 *)(e + sx));
        }
        AddInteger(mgr, QB_SCORE, *(s32 *)(*(s32 *)(base + off) + 0xE0));
        AddString(mgr, QB_TEXT, *(s32 *)(base + off) + 0x1C);
        if (i == 0) {
            s32 v;
            void *obj;
            s32 vt;
            v = *(s32 *)(*(s32 *)(base + off) + 0xEC);
            if (v == 0) {
                v = Script_GetInteger(QB_CANCEL_GROUND, 0);
            }
            AddChecksum(mgr, QB_COMBINED_FLAGS, v);
            obj = *((void * *)&arg2->unk0xBC);
            vt = ((Unk_9994C3F5 *)obj)->unk0x8;
            ((Unk_4ADE3CE7 *)vt)->unk0x1C(
                (s32)obj + ((Unk_4ADE3CE7 *)vt)->unk0x18, QB_STARTGAP, mgr, (s32)arg2);
        } else {
            void *obj;
            s32 vt;
            obj = *((void * *)&arg2->unk0xBC);
            vt = ((Unk_9994C3F5 *)obj)->unk0x8;
            ((Unk_4ADE3CE7 *)vt)->unk0x1C(
                (s32)obj + ((Unk_4ADE3CE7 *)vt)->unk0x18, QB_ENDGAP, mgr, (s32)arg2);
        }
        if (mgr != 0) {
            CStruct_delete(mgr, 3);
        }
    }
}
