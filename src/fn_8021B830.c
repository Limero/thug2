// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8021B830-0x8021B9E8 (440B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_802AFFB8[];
extern char lbl_802B0038[];
extern char lbl_802FFE98[];
extern char lbl_80303148[];
extern s32 lbl_8030191C;
void fn_8000F2F8(Unk_9F352E7C * arg0, s32 arg1);
void *Mem_NewZero(s32 arg0);
s32 fn_80229404(void *arg0, s32 arg1);
s32 fn_8022986C(CScript * arg0);
s32 fn_8022989C(CScript * arg0);
void Script_RunScript(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32 fn_8021C9B8(CScript * arg0);
void fn_8021CB74(CScript * arg0, CScript * arg1);
void fn_80009B04(Unk_5EF41E38 * arg0, void * arg1);
void fn_8000A578(void *arg0, s32 arg1);
void *NextItem(void *arg0);
void fn_8000F320(Unk_F12C5E01 * arg0);
void fn_80216DC8();
void fn_80216E24();

void *fn_8021B830(Unk_1DD1B27C *arg0, s32 arg1, s32 arg2, s32 arg3) {
    Unk_FFAD6788 *mgr;
    CScript *obj;
    CScript *task1;
    CScript *task2;
    s32 g148;
    s32 g191C;
    s32 t989c;
    register s32 zero __asm__("r26");
    s32 cb1;
    s32 cb2;
    s32 idx1;
    s32 idx2;
    char *base2;
    char *p;
    s32 loaded;
    s32 t94;

    mgr = *(void **)&lbl_802FFE98;
    fn_8000F2F8(mgr, mgr->unk0x134);
    obj = (void *)fn_80229404(Mem_NewZero(0x1F8), arg3);
    obj->unk0x18 = arg1;
    obj->unk0x1C = arg2;
    if (fn_8022986C(obj) != 0) {
        t989c = fn_8022989C(obj);
        if (t989c != 0) {
            g148 = *(s32 *)&lbl_80303148;
            g191C = lbl_8030191C;
            Script_RunScript(QB_HIDE_PANEL_STUFF, 0, 0, 0, 0);
            zero = 0;
            fn_8021CB74(arg0, fn_8021C9B8(arg0));
            task1 = Mem_NewZero(0x24);
            cb1 = (s32)fn_80216DC8;
            fn_80009B04(task1, 0);
            task1->unk0x1C = cb1;
            task1->unk0x20 = (s32)obj;
            task1->unk0x18 = (s32)lbl_802B0038;
            obj->unk0x1F4 = task1;
            fn_8000A578((char *)g148 + 8, task1);
            task2 = Mem_NewZero(0x30);
            cb2 = (s32)fn_80216E24;
            fn_80009B04(task2, -1000);
            task2->unk0x24 = zero;
            task2->unk0x28 = cb2;
            task2->unk0x18 = (s32)lbl_802AFFB8;
            task2->unk0x2C = arg0;
            arg0->unk0x108 = (s32)task2;
            idx1 = task2->unk0x24;
            fn_8000A578((char *)(idx1 * 0x94 + (s32)g191C) + 0xC, task2);
            idx2 = task2->unk0x24;
            base2 = (char *)g191C + 8;
            t94 = idx2 * 0x94;
            p = (char *)(t94 + (s32)g191C);
            task2->unk0x1C = p + 0x58;
            loaded = *(s32 *)((char *)base2 + (s32)t94);
            task2->unk0x20 = loaded;
        } else {
            arg0->unk0x1F8 = t989c;
        }
    } else {
        if ((fn_8022989C(NextItem(arg0)) != 0) && (arg0->unk0x1F8 == 0)) {
            fn_8021CB74(arg0, (s32)obj);
        }
    }
    fn_8000F320(*(void **)&lbl_802FFE98);
    return obj;
}
