// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80222A1C-0x80222B60 (324B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern s32 lbl_80305F9C;
extern s32 lbl_8030191C;
extern s32 lbl_80303148;
extern void *lbl_802FFE98;
extern s32 fn_80216DC8(void);
extern s32 fn_80216E24(void);
extern char lbl_802AFFB8[];
extern char lbl_802B0038[];
s32 NextItem(void *arg0);
s32 fn_8022989C(void);
s32 fn_802298B4(CScript * arg0);
void fn_8000F2F8(Unk_9F352E7C * arg0, s32 arg1);
void *Mem_NewZero(s32 arg0);
void fn_80009B04(Unk_5EF41E38 * arg0, void * arg1);
void fn_8000A578(void *arg0, void *arg1);
void fn_8000F320(Unk_F12C5E01 * arg0);

bool ScriptEnterSurveyorMode(CStruct *pParams, CScript *pScript) {
    register s32 mgr __asm__("r27");
    register s32 *arr __asm__("r26");
    register s32 *lst __asm__("r25");
    CScript *e;
    CScript *obj1;
    CScript *obj2;
    s32 dc8;
    s32 b38;
    s32 e24;
    register char *b8 __asm__("r10");
    register char *p58 __asm__("r9");
    s32 prod;
    register s32 v20 __asm__("r11");
    void *g2;
    Unk_FFAD6788 *g;
    register s32 t __asm__("r24");

    mgr = (s32 *)lbl_80305F9C;
    arr = (s32 *)lbl_8030191C;
    lst = (s32 *)lbl_80303148;
    e = (void *)NextItem((void *)mgr);
    if (fn_8022989C() != 0) {
        goto ret0;
    }
    if ((t = fn_802298B4((s32)e)) != 0) {
    ret0:
        return false;
    }
    __asm__("" : "+r"(t));
    g = lbl_802FFE98;
    fn_8000F2F8(g, g->unk0x134);
    obj1 = (void *)Mem_NewZero(0x24);
    dc8 = (s32)fn_80216DC8;
    fn_80009B04(obj1, 0);
    b38 = (s32)lbl_802B0038;
    obj1->unk0x1C = dc8;
    obj1->unk0x20 = (s32)e;
    obj1->unk0x18 = b38;
    fn_8000A578((char *)lst + 8, (e->unk0x1F4 = (s32)obj1, obj1));
    obj2 = (void *)Mem_NewZero(0x30);
    e24 = (s32)fn_80216E24;
    fn_80009B04(obj2, -1000);
    obj2->unk0x24 = t;
    obj2->unk0x28 = e24;
    obj2->unk0x18 = (s32)lbl_802AFFB8;
    obj2->unk0x2C = (s32)mgr;
    ((Unk_FFAD6788 *)mgr)->unk0x108 = (s32)obj2;
    fn_8000A578((char *)(((obj2->unk0x24) * 0x94) + (s32)arr + 0xC), obj2);
    prod = obj2->unk0x24;
    b8 = (char *)arr + 8;
    g2 = lbl_802FFE98;
    __asm__("" : "+r"(g2));
    prod *= 0x94;
    p58 = (char *)(prod + (s32)arr);
    p58 += 0x58;
    obj2->unk0x1C = (s32)p58;
    v20 = *(s32 *)(b8 + prod);
    obj2->unk0x20 = v20;
    e->unk0x1D8 = e->unk0x1D8 | 0x10000;
    fn_8000F320(g2);
    return true;
}
