// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8022B000-0x8022B1B0 (432B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern void fn_8000F2F8(Unk_9F352E7C * obj, s32 val);
extern void fn_8000F320(Unk_F12C5E01 * obj);
extern s32 fn_8022AF44(void * arg0);
extern void Script_RunScript(s32 hash, s32 a, s32 b, s32 c, s32 d);
extern s32 CStruct_new(s32 size);
extern s32 CStruct_ctor(s32 obj);
extern void AddString(CStruct * obj, u32 hash, void *val);
extern void AddChecksum(CStruct * obj, u32 hash, void *val);
extern void fn_80127C14(CStruct * obj, u32 hash, CStruct * val);
extern void CStruct_delete(CStruct * val, s32 flag);

void fn_8022B000(s32 arg0, Unk_FFAD6788 *arg1) {
    register char *page __asm__("r28");
    register s32 v30 __asm__("r30");
    void *a1;
    s32 hnd;
    Unk_89783F6B *t;

    v30 = arg0;
    page = (char *)0x80300000;
    a1 = arg1;
    t = *(s32 *)(page - 0x168);
    fn_8000F2F8(t, t->unk0x124);
    if (fn_8022AF44(v30) == 0) {
        Script_RunScript(QB_DESTROY_SERVER_MENU_CHILDREN, 0, 0, 0, 0);
    }
    {
        register s32 h3 __asm__("r3");
        register s32 za __asm__("r4");
        register s32 zb __asm__("r5");
        register s32 zc __asm__("r6");
        register s32 zd __asm__("r7");
        __asm__ volatile("lis %0,0x56e2" : "=r"(h3));
        __asm__ volatile("li %0,0" : "=r"(zc));
        __asm__ volatile("li %0,0" : "=r"(zd));
        __asm__ volatile("li %0,0" : "=r"(za));
        __asm__ volatile("li %0,0" : "=r"(zb));
        __asm__ volatile("ori %0,%0,0xb51" : "+r"(h3));
        Script_RunScript(h3, za, zb, zc, zd);
    }
    v30 = CStruct_ctor(CStruct_new(8));
    {
        register s32 hh __asm__("r4");
        __asm__ volatile("lis %0,0xc474\n\tori %0,%0,0x5838" : "=r"(hh));
        AddString(v30, hh, (char *)arg1 + 0x18);
    }
    AddString(v30, QB_MODE, (char *)arg1 + 0x64);
    AddChecksum(v30, QB_ID, arg1);
    AddChecksum(v30, QB_PARENT, (void *)QB_SERVER_LIST_MENU);
    AddChecksum(v30, QB_PAD_CHOOSE_SCRIPT, (void *)QB_CHOOSE_SELECTED_SERVER);
    AddChecksum(v30, QB_FOCUS_SCRIPT, (void *)QB_DESCRIBE_SELECTED_SERVER);
    AddChecksum(hnd = CStruct_ctor(CStruct_new(8)), QB_ID, arg1);
    fn_80127C14(v30, QB_PAD_CHOOSE_PARAMS, hnd);
    fn_80127C14(v30, QB_FOCUS_PARAMS, hnd);
    Script_RunScript(QB_SERVER_LIST_MENU_ADD_ITEM, v30, 0, 0, 0);
    arg1->unk0x9C = 1;
    if (v30 != 0) {
        CStruct_delete(v30, 3);
    }
    if (hnd != 0) {
        CStruct_delete(hnd, 3);
    }
    fn_8000F320(*(s32 *)(page - 0x168));
}
