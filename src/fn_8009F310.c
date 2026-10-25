// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009F310-0x8009F3D0 (192B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern void fn_80131474(s32, s32, s32, s32);
extern s32 Script_SpawnScript(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
extern void CObject_RemoveRefLink(s32, void *);
extern void CObject_AddRefLink(void *, void *);
extern void fn_801309EC(s32);
void *fn_8009F310(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 temp_r3;
    void *temp_r30;

    if (arg3 != 0) {
        fn_80131474(arg1, 0, arg2, arg4);
    }
    temp_r3 = Script_SpawnScript(arg1, arg5, 0, 0, arg2, 0, 0, 0, 0, 0);
    temp_r30 = (char *)temp_r3 + 0xBC;
    if (*(s32 *)temp_r30 != 0) {
        CObject_RemoveRefLink(*(s32 *)temp_r30, temp_r30);
        *(s32 *)temp_r30 = 0;
    }
    *(s32 *)temp_r30 = arg0;
    if (arg0 != 0) {
        CObject_AddRefLink(arg0, temp_r30);
    }
    fn_801309EC(temp_r3);
    return temp_r3;
}
