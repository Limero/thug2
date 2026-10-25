// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8021FF74-0x8022004C (216B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_802AFEF8[];

void fn_8021FF74(void *arg0) {
    struct {
        char pad[4];
        void *cur;
        void *lbl;
    } sp8;
    s32 lblv;
    Unk_C7387A53 *temp_r3;
    register s32 nxt __asm__("r11");
    void *var_r31;
    register void *var_r11 __asm__("r11");
    Unk_C8FEE62D *var_r10;
    register void *p __asm__("r9");
    register s32 cur __asm__("r9");
    register void *q __asm__("r30");

    lblv = (s32)lbl_802AFEF8;
    p = &sp8;
    temp_r3 = (char *)arg0 + 0x160;
    ((CStruct *)p)->unk0x8 = lblv;
    *((void * *)&((CStruct *)p)->unk0x4) = temp_r3;
    q = p;

    var_r11 = *((void * *)&temp_r3->unk0xC);
    if (((CStruct *)var_r11)->unk0x4 == -1) {
        var_r11 = NULL;
    }
    *((void * *)&((CStruct *)q)->unk0x4) = var_r11;

    if (var_r11 != NULL) {
        goto load;
    }
    __asm__("li %0,0" : "=r"(nxt));
    goto have;
load:
    nxt = ((CStruct *)var_r11)->unk0x4;
have:
    var_r10 = (void *)nxt;
    if (var_r10 != NULL) {
        do {
            cur = ((CStruct *)q)->unk0x4;
            var_r11 = *(void **)((char *)(s32 *)cur + 0xC);
            if (((CStruct *)var_r11)->unk0x4 == -1) {
                var_r11 = NULL;
            }
            *((void * *)&((CStruct *)q)->unk0x4) = var_r11;

            if (var_r11 == NULL) {
                var_r31 = NULL;
            } else {
                var_r31 = *((void * *)&((CStruct *)var_r11)->unk0x4);
            }

            if (var_r10 != NULL) {
                void *vt = *((void * *)&var_r10->unk0x14);
                ((void (*)(void *, s32)) *((void * *)&((Unk_F5317C5D *)vt)->unk0xC))(
                    (char *)var_r10 + ((Unk_F5317C5D *)vt)->unk0x8, 3);
            }
            var_r10 = var_r31;
        } while (var_r10 != NULL);
    }
    ((CStruct *)q)->unk0x8 = (s32)lbl_802AFEF8;
}
