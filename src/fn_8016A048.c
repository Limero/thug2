// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8016A048-0x8016A1BC (372B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern void* lbl_802FFE98;
extern void *lbl_80300368;
extern Unk_9F352E7C * lbl_80305E78;
extern char lbl_80305E7C[];
extern s32 lbl_803A0178;
extern char lbl_802A8854[];
extern char lbl_802A8868[];
extern char lbl_802A887C[];
extern char lbl_802A8890[];
extern char lbl_802A88A0[];
extern char lbl_802A88B4[];
void fn_8016A30C(void);
s32 fn_8016A320(void);
void fn_8016A374(void);
void fn_8016A34C(void);
void fn_8016A388(void);
void fn_8016A360(void);
void fn_8016A39C(void);
void fn_8000F2F8(Unk_9F352E7C *, s32);
void fn_8000F320(Unk_F12C5E01 *);
void fn_8001075C(s32);
void fn_80010760(void);
void fn_80125E20(s32, s32);
void fn_80125E94(s32, s32);
void fn_80125F08(s32, s32);
void fn_80024000(s32);
void *memset(void *, int, s32);
void fn_8025ED48(void);
void fn_8025ED70(void);
void fn_8025EDA0(s32);
s32 fn_8025EDA8(void);

bool ScriptCreateTemporaryMemCardPools(CStruct *pParams, CScript *pScript) {
    s32 temp_r3_2;

    fn_8016A30C();
    if (fn_8016A320() != 0) {
        fn_8016A374();
        fn_8016A34C();
        fn_8016A388();
        fn_8016A360();
        fn_8016A39C();
    } else {
        register s32 *e7c __asm__("r30");
        fn_8016A374();
        fn_8000F2F8(lbl_802FFE98, ({ s32 vld = ((Unk_B0F19D72 *)lbl_802FFE98)->unk0x168; lbl_80305E78 = 1; __asm__("lis %0,%1@ha" : "=r"(e7c) : "s"(lbl_80305E7C)); vld; }));
        temp_r3_2 = Mem_Alloc(0x59D80);
        ((Unk_DD583DF7 *)e7c)->unk0x5E7C = temp_r3_2;
        if (temp_r3_2 != 0) {
            memcpy(temp_r3_2, lbl_80300368, 0x59D80);
        }
        fn_8025ED48();
        fn_8025ED70();
        lbl_803A0178 = fn_8025EDA8();
        fn_8025EDA0(2);
        memset(lbl_80300368, 0, 0x59D80);
        fn_80024000(0);
        fn_8000F320(lbl_802FFE98);
        fn_8000F2F8(lbl_802FFE98, ((Unk_B0F19D72 *)lbl_802FFE98)->unk0x118);
        fn_8001075C(lbl_802A8854);
        fn_8016A30C();
        fn_80125E20(0x3E80, (s32)lbl_802A8868);
        fn_8016A374();
        fn_80010760();
        fn_8001075C(lbl_802A887C);
        fn_8016A34C();
        fn_80125E94(0x1F40, (s32)lbl_802A8890);
        fn_8016A388();
        fn_80010760();
        fn_8001075C(lbl_802A88A0);
        fn_8016A360();
        fn_80125F08(0xBB8, (s32)lbl_802A88B4);
        fn_8016A39C();
        fn_80010760();
        fn_8000F320(lbl_802FFE98);
    }
    return true;
}
