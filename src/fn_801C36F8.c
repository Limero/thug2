// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801C36F8-0x801C380C (276B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 ContainsFlag(CStruct *, s32);
register void *next_p __asm__("r31");
void fn_801C36F8(Unk_C7387A53 *arg0, CStruct *arg1) {
    register s32 sent __asm__("r0");
    register void *head __asm__("r9");
    register void *temp_r9 __asm__("r9");
    register void *walker __asm__("r11");
    Unk_F5317C5D *vt;

    if (ContainsFlag(arg1, QB_NOTINSAMEFRAME) != 0) {
        head = arg0->unk0x40;
        if ((s32) ((CStruct *)head)->unk0x4 == -1) {
            head = NULL;
        }
        walker = head;
        if (walker != NULL) {
            do {
                temp_r9 = ((Unk_C8FEE62D *)walker)->unk0xC;
                sent = (s32) ((CStruct *)temp_r9)->unk0x4;
                next_p = temp_r9;
                if (sent == -1) {
                    next_p = NULL;
                }
                if (((s32) ((Unk_C8FEE62D *)walker)->unk0x38 != (s32) arg0->unk0x4C) && (walker != NULL)) {
                    vt = ((Unk_C8FEE62D *)walker)->unk0x14;
                    ((s32 (*)(void *, s32))vt->unk0xC)((char *)walker + vt->unk0x8, 3);
                }
                walker = next_p;
            } while (walker != NULL);
        }
    } else {
        head = arg0->unk0x40;
        if ((s32) ((CStruct *)head)->unk0x4 == -1) {
            head = NULL;
        }
        walker = head;
        if (walker != NULL) {
            do {
                temp_r9 = ((Unk_C8FEE62D *)walker)->unk0xC;
                sent = (s32) ((CStruct *)temp_r9)->unk0x4;
                next_p = temp_r9;
                if (sent == -1) {
                    next_p = NULL;
                }
                if (walker != NULL) {
                    vt = ((Unk_C8FEE62D *)walker)->unk0x14;
                    ((s32 (*)(void *, s32))vt->unk0xC)((char *)walker + vt->unk0x8, 3);
                }
                walker = next_p;
            } while (walker != NULL);
        }
    }
}
