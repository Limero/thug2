// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80060490-0x800607A0 (784B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern char lbl_80293ED4[];
extern s32 lbl_8029036C;
extern void *lbl_802FFE98;
extern s32 lbl_80301B48;

s32 fn_8005D6C8(char *, s32, s32);
s32 fn_80055208(s32);
s32 fn_8005529C(char *, char *);
s32 fn_80055334(char *, s32, s32, s32);
s32 Script_GenerateCRC(char *);
void fn_8001075C(char *);
void fn_80010760(void);
void *Mem_Alloc2(s32);
void *fn_8000F10C(void *, s32, s32, void *);
void fn_8005F058(void *, void *, void *, s32);
void fn_8005F418(void *, s32);
void fn_8005F51C(void *, s32);
s32 fn_80060DEC(s32, s32);
s32 fn_800F2B64(s32, void *, s32);
s32 fn_800F2ED4(s32);
s32 fn_800F2BA8(s32, void *, s32, s32, s32, s32, s32, void *, void *, s32);
s32 fn_800F5758(void *);
char *strcat(char *, const char *);

// "<model>.tex" name buffer (fn_8005529C strips ".skin"/".mdl", strcat adds
// ".tex") unioned with the dead list-head store that want keeps at 0x10(r1),
// immediately followed by the four-word param block handed to fn_800F2BA8 as
// its 8th argument.
typedef union A6090_nm {
    char name[0x100];
    volatile s32 v;
} A6090_nm_t;

typedef struct A6090_fr {
    A6090_nm_t nm;
    s32 p0;
    s32 p1;
    s32 p2;
    s32 p3;
    char pad0x40[0x40];
} A6090_fr_t;

// Second param frame (ctor fn_800F5758 zeroes +0/+4/+8/+0x10/+0x14).
typedef struct A6090_fr2 {
    s32 q0;
    s32 q1;
    s32 q2;
    s32 q3;
    s32 q4;
    s32 q5;
} A6090_fr2_t;

bool fn_80060490(Unk_2FEA250A *arg0, char *arg1, s32 arg2, s32 arg3, s32 arg4,
                s32 arg5, s32 arg6, s32 arg7, s32 arg_sp8) {
    A6090_fr_t fr;
    A6090_fr2_t fr2;
    Unk_DB0E2BAB *var_r28;
    CStruct *var_r30;
    CStruct *temp_r29;
    Unk_9994C3F5 *temp_r30_2;
    CStruct *temp_r3_2;
    register s32 a1 = arg1;
    s32 temp_r27;
    s32 temp_r3;

    temp_r27 = lbl_80301B48;
    arg0->unk0x48 = (u32) (arg0->unk0x48 & QB_UNKNOWN_0x7FFFFFFF);
    if (arg7 == 0) {
        s32 temp_size;
        temp_size = lbl_8029036C;
        var_r28 = (Unk_DB0E2BAB *)fn_8000F10C(lbl_802FFE98, 0x18, temp_size, 0);
        if (var_r28 == NULL) {
            return false;
        }
    } else {
        var_r28 = (Unk_DB0E2BAB *)Mem_Alloc2(0x18);
    }
    var_r30 = 0;
    if (arg3 != 0) {
        fr.p3 = arg5;
        fr.p0 = 0;
        fr.p1 = arg4;
        fr.p2 = fn_8005529C(a1, fr.nm.name);
        strcat(fr.nm.name, lbl_80293ED4);
        if (arg_sp8 != 0) {
            fn_800F2B64(temp_r27, fr.nm.name, 1);
        } else {
            fn_800F2BA8(temp_r27, fr.nm.name, 0, 0, 0, 0, 0,
                        fn_800F2ED4(temp_r27), &fr.p0, var_r30);
        }
        fn_800F5758(&fr2);
        fr2.q1 = arg4;
        fr2.q0 = (arg0->unk0x48 >> 0x1A) & 1;
        if (arg_sp8 != 0) {
            var_r30 = (CStruct *)fn_800F2B64(temp_r27, a1, 1);
        } else {
            var_r30 = (CStruct *)fn_800F2BA8(temp_r27, a1, 0, 0,
                                             Script_GenerateCRC(fr.nm.name), 0, 0,
                                             fn_800F2ED4(temp_r27), &fr2,
                                             arg_sp8);
        }
        var_r28->unk0x10 = Script_GenerateCRC(a1);
        arg0->unk0x4E = (u16) (arg0->unk0x4E + 1);
        var_r28->unk0xC = NULL;
    } else {
        fn_8001075C(a1);
        var_r30 = (CStruct *)fn_80055334(a1, fn_8005D6C8(a1, arg4, arg5),
                                         arg4, (arg0->unk0x48 >> 0x1A) & 1);
        fn_80010760();
        var_r28->unk0xC = var_r30;
        arg0->unk0x4C = (u16) (arg0->unk0x4C + 1);
        var_r28->unk0x10 = arg3;
    }
    temp_r3 = fn_80055208(arg7);
    var_r28->unk0x0 = temp_r3;
    if (arg7 == 0) {
        if (temp_r3 == 0) {
            return false;
        }
    }
    fn_8005F058(var_r28->unk0x0, var_r30, arg0, arg6);
    var_r28->unk0x4 = var_r30->unk0x4;
    fn_8005F51C(var_r28->unk0x0, (arg0->unk0x48 >> 0x1B) & 1);
    var_r28->unk0x8 = arg2;
    arg0->unk0x18 = (s32) (arg0->unk0x18 | (1 << *(s16 *)((char *)arg0 + (s32)0x4A)));
    if ((s32) arg0->unk0x30 != 0) {
        fn_8005F418(var_r28->unk0x0, arg0->unk0x30);
    }
    temp_r29 = (CStruct *)((char *)arg0 + 0x10);
    *(s16 *)((char *)arg0 + (s32)0x4A) = (s16) ((u16) *(s16 *)((char *)arg0 + (s32)0x4A) + 1);
    fn_80060DEC(arg0, 0);
    var_r28->unk0x14 = 0;
    temp_r30_2 = (Unk_9994C3F5 *)arg0->unk0x10;
    fr.nm.v = (s32) temp_r30_2;
    temp_r3_2 = Mem_Alloc2(0xC);
    temp_r3_2->unk0x8 = temp_r30_2->unk0x8;
    temp_r3_2->unk0x0 = var_r28;
    temp_r3_2->unk0x4 = temp_r30_2;
    temp_r29->unk0x4 = (s32) (temp_r29->unk0x4 + 1);
    temp_r30_2->unk0x8 = temp_r3_2;
    *(s32 *) (*(s32 *) ((char *)temp_r3_2 + 0x8) + 0x4) = temp_r3_2;
    if (*(s16 *)((char *)arg0 + (s32)0x4A) == 1) {
        arg0->unk0x34 = Script_GenerateCRC(a1);
    }
    return true;
}
