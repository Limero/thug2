// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011D588-0x8011D6CC (324B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_8038C8C0[];
extern char lbl_8038A97C[];
extern char lbl_8029D5E0[];
s32 fn_8011BC38();
void strcpy(char *, char *);
u32 strlen(char *);
char *strncpy(char *, char *, s32);
s32 fn_80120580(void *, s32);
// AddTrackToPlaylist @ 0x8011D588
void AddTrackToPlaylist(void *arg0, s8 arg1, void *arg2) {
    s32 i;
    char *temp_r29;
    char *temp_r30;
    Unk_719FF300 *temp_r31;
    u8 c;

    if (fn_8011BC38() == 0) {
        temp_r29 = (char *)lbl_8038C8C0 + arg1 * 0xCB0;
        if (((Unk_B8BF4382 *)temp_r29)->unk0xC80 <= 0x4F) {
            temp_r30 = temp_r29 + ((Unk_B8BF4382 *)temp_r29)->unk0xC80 * 0x28;
            strcpy(temp_r30, (char *)arg0);
            for (i = 0; i < strlen(temp_r30); i++) {
                c = temp_r30[i];
                if ((u32)(c - 0x61) <= 0x19U) {
                    temp_r30[i] = c - 0x20;
                }
            }
            if (arg1 == 0) {
                temp_r31 = (char *)lbl_8038A97C + ((Unk_B8BF4382 *)temp_r29)->unk0xC80 * 0x64;
                if (arg2 != 0) {
                    strncpy(temp_r31, (char *)arg2, 0x64);
                    temp_r31->unk0x63 = (u8)arg1;
                } else {
                    *(s32 *)((char *)lbl_8038A97C + ((Unk_B8BF4382 *)temp_r29)->unk0xC80 * 0x64) = *(s32 *)&lbl_8029D5E0;
                    temp_r31->unk0x4 = ((Unk_2F50C85F *)&lbl_8029D5E0)->unk0x4;
                    temp_r31->unk0x8 = ((Unk_2F50C85F *)&lbl_8029D5E0)->unk0x8;
                    temp_r31->unk0xC = ((Unk_2F50C85F *)&lbl_8029D5E0)->unk0xC;
                    temp_r31->unk0x10 = ((Unk_2F50C85F *)&lbl_8029D5E0)->unk0x10;
                }
            }
            if (fn_80120580(temp_r30, 1) != 0) {
                ((Unk_B8BF4382 *)temp_r29)->unk0xCA8 = 0;
                ((Unk_B8BF4382 *)temp_r29)->unk0xC80 = ((Unk_B8BF4382 *)temp_r29)->unk0xC80 + 1;
            }
        }
    }
}
