// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800AC884-0x800AC93C (184B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void fn_800ABD08(void *);
void fn_800AC7A0(void *);
void fn_8000F320(void *);
s32 fn_800AC680(s32);
s32 fn_800AB508(void);
void fn_8000F2F8(void *, s32);
#include "structs.h"
extern char lbl_802FFE98[];

typedef struct {
    char pad0x0[0x8];
    s16 unk0x8;
    s32 unk0xC;
} F2F24C3E_Vtbl;

bool fn_800AC884(Unk_9B16FFA5 *arg0, s32 arg1) {
    if (arg0->unk0x34B8 != 0) {
        void *g = *(void **)lbl_802FFE98;
        fn_8000F2F8(g, fn_800AB508());
    } else {
        void *g = *(void **)lbl_802FFE98;
        fn_8000F2F8(g, ((Unk_9994C3F5 *)g)->unk0x11C);
    }
    fn_800ABD08(arg0);
    fn_800AC680(arg0);
    fn_800AC7A0(arg0);
    fn_8000F320(*(void **)lbl_802FFE98);
    if (arg0->unk0x4 != 0) {
        Unk_F2F24C3E *child = (Unk_F2F24C3E *)arg0->unk0x4;
        F2F24C3E_Vtbl *vt = (F2F24C3E_Vtbl *)child->unk0x2354;
        ((s32 (*)(void *, s32))vt->unk0xC)((char *)child + vt->unk0x8, 3);
    }
    arg0->unk0x4 = 0;
    return true;
}
