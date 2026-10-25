// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801EE948-0x801EEC10 (712B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern f32 lbl_802ADBBC;

void fn_80004518(s32, s32);
s32 fn_80005490(Unk_DB0E2BAB *);
extern s32 GetChecksum_3(Unk_6A70655D * arg0, s32 arg1);
f32 fn_801417B8(CScript *, s32);
void fn_801C1A9C(Unk_FFAD6788 *, f32);
extern f32 sqrtf(f32);

void fn_801EE948(void *arg0) {
    s32 sp8;
    f32 temp_f0;
    f32 temp_f1;
    f32 temp_f31;
    s32 temp_r10;
    s32 var_r11;
    s32 var_r0;
    s32 tb3;
    Unk_1187CD3D *temp_r3;
    Unk_FFAD6788 *p20;
    Unk_2DD055BA *p1c;
    register void *a0 __asm__("r31");
    register void *pin __asm__("r30");
    register void *pa __asm__("r9");
    register void *pb __asm__("r10");
    register void *oc __asm__("r11");
    register void *pc __asm__("r9");
    register __ps_t *ps1 __asm__("r9");
    register __ps_t *pd1 __asm__("r10");
    register __ps_t *ps2 __asm__("r9");
    register __ps_t *pd2 __asm__("r11");
    register void *bbase __asm__("r9");
    register void *bsrc __asm__("r11");
    register void *bmid __asm__("r10");
    register void *csrc __asm__("r11");
    register void *cdst __asm__("r9");
    register void *cmid __asm__("r10");

    a0 = arg0;
    if (*(s32 *)(((Unk_C8FEE62D *)a0)->unk0x1C + 0x294) != 0) {
        pa = *((void * *)&((Unk_C8FEE62D *)a0)->unk0x20);
        sp8 = ((Unk_31DE137E *)pa)->unk0x1C;
        if (sp8 != 3) {
            ((Unk_31DE137E *)pa)->unk0x160 = 0;
            pb = *((void * *)&((Unk_C8FEE62D *)a0)->unk0x20);
            sp8 = ((Unk_31DE137E *)pb)->unk0x1C;
            if (sp8 == 1) {
                oc = *((void * *)&((Unk_C8FEE62D *)a0)->unk0xC);
                if (fabs(*((f32 *)&((Unk_FFAD6788 *)oc)->unk0xB8)) < lbl_802ADBBC &&
                    fabs(*((f32 *)&((Unk_FFAD6788 *)oc)->unk0xC0)) < lbl_802ADBBC) {
                    ((Unk_31DE137E *)pb)->unk0x160 = sp8;
                }
            }
        }
    }
    pc = *((void * *)&((Unk_C8FEE62D *)a0)->unk0x20);
    if (((Unk_31DE137E *)pc)->unk0x1C != 1) {
        ((Unk_31DE137E *)pc)->unk0x160 = 0;
    }
    ps1 = (__ps_t *)((Unk_C8FEE62D *)a0)->unk0x1C;
    pd1 = (__ps_t *)((Unk_C8FEE62D *)a0)->unk0x20;
    pd1[45] = ps1[12];
    pd1[46] = ps1[13];
    ps2 = (__ps_t *)((Unk_C8FEE62D *)a0)->unk0x1C;
    pd2 = (__ps_t *)((Unk_C8FEE62D *)a0)->unk0x20;
    pd2[47] = ps2[14];
    pd2[48] = ps2[15];
    fn_80004518(((Unk_C8FEE62D *)a0)->unk0xC + 0x78, 1);
    fn_80004518(((Unk_C8FEE62D *)a0)->unk0x1C + 0x20, 1);
    if (fn_80005490(((Unk_C8FEE62D *)a0)->unk0xC + 0x78) != 0) {
        bbase = *((void * *)&((Unk_C8FEE62D *)a0)->unk0x1C);
        bsrc = *((void * *)&((Unk_C7387A53 *)bbase)->unk0xC);
        __asm__("" : "=r"(bmid) : "r"((char *)bbase + 0x20));
        ((__ps_t *)bbase)[4] = ((__ps_t *)bsrc)[15];
        ((__ps_t *)bbase)[5] = ((__ps_t *)bsrc)[16];
        ((__ps_t *)bbase)[6] = ((__ps_t *)bsrc)[17];
        ((__ps_t *)bbase)[7] = ((__ps_t *)bsrc)[18];
        ((__ps_t *)bmid)[4] = ((__ps_t *)bsrc)[19];
        ((__ps_t *)bmid)[5] = ((__ps_t *)bsrc)[20];
        ((__ps_t *)bbase)[10] = ((__ps_t *)bsrc)[21];
        ((__ps_t *)bbase)[11] = ((__ps_t *)bsrc)[22];
    }
    csrc = *((void * *)&((Unk_C8FEE62D *)a0)->unk0x1C);
    cdst = *((void * *)&((Unk_C8FEE62D *)a0)->unk0xC);
    __asm__("" : "=r"(cmid) : "r"((char *)csrc + 0x20));
    ((__ps_t *)cdst)[26] = ((__ps_t *)csrc)[4];
    ((__ps_t *)cdst)[27] = ((__ps_t *)csrc)[5];
    ((__ps_t *)cdst)[28] = ((__ps_t *)csrc)[6];
    ((__ps_t *)cdst)[29] = ((__ps_t *)csrc)[7];
    ((__ps_t *)cdst)[30] = ((__ps_t *)cmid)[4];
    ((__ps_t *)cdst)[31] = ((__ps_t *)cmid)[5];
    ((__ps_t *)cdst)[32] = ((__ps_t *)csrc)[10];
    ((__ps_t *)cdst)[33] = ((__ps_t *)csrc)[11];
    temp_r3 = (void *)GetChecksum_3(((Unk_C8FEE62D *)a0)->unk0xC, QB_SKATERSOUND);
    p20 = *((void * *)&((Unk_C8FEE62D *)a0)->unk0x20);
    temp_r3->unk0x24 = p20->unk0x7C;
    p1c = *((void * *)&((Unk_C8FEE62D *)a0)->unk0x20);
    temp_r3->unk0x20 = p1c->unk0x148;
    pin = (void *)GetChecksum_3(((Unk_C8FEE62D *)a0)->unk0xC, QB_SKATERLOOPINGSOUND);
    temp_f31 = fn_801417B8(((Unk_C8FEE62D *)a0)->unk0xC, QB_SKATER_MAX_MAX_SPEED_STAT);
    {
        register f32 tf0 __asm__("fr0");
        register f32 tf1 __asm__("fr1");
        tf0 = *(f32 *)(((Unk_C8FEE62D *)a0)->unk0xC + 0xB8);
        tf1 = *(f32 *)(((Unk_C8FEE62D *)a0)->unk0xC + 0xC0);
        fn_801C1A9C(pin, sqrtf((tf0 * tf0) + (tf1 * tf1)) / temp_f31);
    }
    temp_r10 = ((Unk_52F5DCA2 *)pin)->unk0xE0;
    ((Unk_52F5DCA2 *)pin)->unk0xE8 = *(s32 *)(((Unk_C8FEE62D *)a0)->unk0x20 + 0xA0);
    var_r0 = *(s32 *)(((Unk_C8FEE62D *)a0)->unk0x20 + 0x7C);
    if (((Unk_52F5DCA2 *)pin)->unk0xEC != var_r0) {
        temp_r10 |= 1;
    }
    var_r11 = (((Unk_52F5DCA2 *)pin)->unk0xE0 = (temp_r10 != 0), ((Unk_52F5DCA2 *)pin)->unk0xE0);
    ((Unk_52F5DCA2 *)pin)->unk0xEC = var_r0;
    var_r0 = *(u8 *)(((Unk_C8FEE62D *)a0)->unk0x20 + 0x148);
    if (((Unk_52F5DCA2 *)pin)->unk0x50 != var_r0) {
        var_r11 |= 1;
    }
    var_r11 = (((Unk_52F5DCA2 *)pin)->unk0xE0 = (var_r11 != 0), ((Unk_52F5DCA2 *)pin)->unk0xE0);
    ((Unk_52F5DCA2 *)pin)->unk0x50 = var_r0;
    temp_r3 = *(s32 *)(((Unk_C8FEE62D *)a0)->unk0x20 + 0x1C);
    if (((Unk_52F5DCA2 *)pin)->unk0x54 != temp_r3) {
        var_r11 |= 1;
    }
    tb3 = (var_r11 != 0);
    ((Unk_52F5DCA2 *)pin)->unk0xE0 = tb3;
    ((Unk_52F5DCA2 *)pin)->unk0x54 = temp_r3;
}
