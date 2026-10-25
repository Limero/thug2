// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80222C2C-0x80222D6C (320B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_80305EAC;
void fn_801746A4(void);

void fn_80222C2C(Unk_C7387A53 *arg0, s32 arg1) {
    u32 count;
    register s32 *head __asm__("r11");
    CStruct *walker;
    Unk_C7387A53 *mgrv;
    s32 id;
    s32 i;
    Unk_9994C3F5 *n;
    Unk_E71E4713 *vt;

    if (arg1 == arg0->unk0x1B4) {
        return;
    }
    arg0->unk0x1B4 = arg1;
    if (arg1 != 0) {
        count = 0U;
        mgrv = (s32 *)lbl_80305EAC;
        head = *((s32 * *)&mgrv->unk0x38);
        id = ((CStruct *)head)->unk0x4;
        __asm__ volatile("mr %0,%1" : "=r"(walker) : "r"(head));
        goto check;
        for (;;) {
            walker = *((s32 * *)&walker->unk0xC);
            count += 1;
            id = walker->unk0x4;
        check:
            if (id == -1) {
                walker = NULL;
            }
            if (walker == NULL) {
                break;
            }
        }
        __asm__("" : "+r"(walker));
        for (i = 0; (u32)i < count; i++) {
            n = (void *)((s32 (*)(void *, s32))fn_801746A4)(mgrv, i);
            if (n != NULL) {
                vt = *((void * *)&n->unk0x8);
                vt->unk0x6C((char *)n + vt->unk0x68);
            }
        }
    } else {
        count = 0U;
        mgrv = (s32 *)lbl_80305EAC;
        head = *((s32 * *)&mgrv->unk0x38);
        id = ((CStruct *)head)->unk0x4;
        __asm__ volatile("mr %0,%1" : "=r"(walker) : "r"(head));
        goto check2;
        for (;;) {
            walker = *((s32 * *)&walker->unk0xC);
            count += 1;
            id = walker->unk0x4;
        check2:
            if (id == -1) {
                walker = NULL;
            }
            if (walker == NULL) {
                break;
            }
        }
        __asm__("" : "+r"(walker));
        for (i = 0; (u32)i < count; i++) {
            n = (void *)((s32 (*)(void *, s32))fn_801746A4)(mgrv, i);
            if (n != NULL) {
                vt = *((void * *)&n->unk0x8);
                ((s32 (*)(void *)) *((void * *)&vt->unk0x64))((char *)n + vt->unk0x60);
            }
        }
    }
}
