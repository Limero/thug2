// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801790E0-0x801791B8 (216B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_80301A38;
extern s32 lbl_80305F9C;
extern s32 fn_800A398C(s32, s32);
extern void *Script_SpawnScript(Unk_15EF4A35 *, s32, s32, Unk_80577C09 *, s32, s32, s32, s32, s32, s32);
extern void CObject_RemoveRefLink(CStruct *, CStruct *);
extern void CObject_AddRefLink(CStruct *, Unk_9994C3F5 *);
extern void fn_801309EC(Unk_DB0E2BAB *);
extern void fn_8021FE30(s32, s32, s32, s32);

bool fn_801790E0(void **arg0) {
    Unk_72CEBC39 *t;
    Unk_C7387A53 *g;
    s32 z;
    s32 r;
    char *p;

    t = *arg0;
    g = (void *)lbl_80305F9C;
    if (g->unk0x1B4 != 0) {
        z = 0;
        r = fn_800A398C(lbl_80301A38, t->unk0x4);
        t = Script_SpawnScript(*(s32 *)t, 0, 0, 0, t->unk0x8, 0, 0, 0, z, z);
        p = (char *)t + 0xBC;
        if (t->unk0xBC != 0) {
            CObject_RemoveRefLink(*(s32 *)p, p);
            *(s32 *)p = z;
        }
        *(s32 *)p = r;
        if (r != 0) {
            CObject_AddRefLink(r, p);
        }
        fn_801309EC(t);
    } else {
        fn_8021FE30((s32)g, t->unk0x8, t->unk0x4, *(s32 *)t);
    }
    return true;
}
