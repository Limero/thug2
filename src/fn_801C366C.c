// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801C366C-0x801C36F8 (140B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8009F310(CStruct *, Unk_15EF4A35 *, s32, s32, s32, s32);
register void *next_p __asm__("r31");
void fn_801C366C(Unk_C7387A53 *arg0) {
    register void *head __asm__("r9");
    register void *temp_r9 __asm__("r9");
    register void *walker __asm__("r11");

    head = arg0->unk0x40;
    if ((s32) ((CStruct *)head)->unk0x4 == -1) {
        head = NULL;
    }
    walker = head;
    if (walker != NULL) {
        do {
            s32 sent;

            temp_r9 = ((Unk_C7387A53 *)walker)->unk0xC;
            sent = (s32) ((CStruct *)temp_r9)->unk0x4;
            next_p = temp_r9;
            if (sent == -1) {
                next_p = NULL;
            }
            if ((s32) ((Unk_C7387A53 *)walker)->unk0x34 != 0) {
                fn_8009F310(arg0->unk0xC, ((Unk_C7387A53 *)walker)->unk0x30, ((Unk_C7387A53 *)walker)->unk0x2C, 0, 0, 0);
            }
            walker = next_p;
        } while (walker != NULL);
    }
}
