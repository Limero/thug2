// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8007E710-0x8007E7B8 (168B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
typedef struct {
    s32 f0;
    s32 f4;
} Unk_802961EC;
char *strstr(const char *, const char *);
char *strcpy(char *, const char *);
void LowerCase(u8 *);
s32 fn_80062934(Unk_FFAD6788 *);
s32 fn_8007E504(Unk_FFAD6788 *, void *);
extern char lbl_802961D8[];
extern char lbl_802961E0[];
extern char lbl_802961EC[];
extern char lbl_802961F8[];
void *fn_8007E710(Unk_FFAD6788 *arg0, char *arg1) {
    char sp8[256];
    Unk_802961EC *temp_r3;
    s32 src0, src1;

    fn_80062934(arg0);
    arg0->unk0xBC = (s32)lbl_802961F8;
    if (strstr(arg1, lbl_802961D8) != NULL) {
        strcpy(&sp8, arg1);
        LowerCase(&sp8);
        temp_r3 = (Unk_802961EC *)strstr(&sp8, lbl_802961E0);
        if (temp_r3 != NULL) {
            src0 = *(s32 *)lbl_802961EC;
            src1 = *(s32 *)(lbl_802961EC + 4);
            temp_r3->f0 = src0;
            temp_r3->f4 = src1;
            fn_8007E504(arg0, &sp8);
        }
    }
    return arg0;
}
