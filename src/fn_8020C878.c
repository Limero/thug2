// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8020C878-0x8020C928 (176B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_802AF760[];
extern void CObject_RemoveRefLink(CStruct *, CStruct *);
extern void fn_80105C34(void *, s32);
extern void fn_8009F558(Unk_C8FEE62D *, s32);
void fn_8020C878(Unk_F71F817E *arg0, s32 arg1) {
    char *walker;
    char *ptr;
    char *ptr2;
    s32 temp_r3;

    arg0->unk0x18 = (s32)lbl_802AF760;
    temp_r3 = arg0->unk0x1928;
    ptr = (char *)arg0 + (s32)0x1928;
    if (temp_r3 != 0) {
        CObject_RemoveRefLink(temp_r3, ptr);
        arg0->unk0x1928 = 0;
    }
    fn_80105C34((char *)arg0 + (s32)0x858, 2);
    if (((char *)arg0 + (s32)0xB8) != NULL) {
        walker = (char *)arg0 + (s32)0x7B8;
        if ((char *)arg0 + (s32)0xB8 != walker) {
            do {
                walker -= 0xE0;
                temp_r3 = ((Unk_E93B8C39 *)walker)->unk0xC8;
                ptr2 = walker + (s32)0xC8;
                if (temp_r3 != 0) {
                    CObject_RemoveRefLink(temp_r3, ptr2);
                    ((Unk_E93B8C39 *)walker)->unk0xC8 = 0;
                }
            } while ((char *)arg0 + (s32)0xB8 != walker);
        }
    }
    fn_8009F558(arg0, arg1);
}
