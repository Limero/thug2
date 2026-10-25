// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80077164-0x800771FC (152B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
/* obj1 = fn_80076F8C result: large object, this fn writes +0x80/+0x84. */
typedef struct Obj1_80077164 {
    char pad0x0[0x80];
    s32 unk0x80;
    s32 unk0x84;
} Obj1_80077164;
/* obj2 = fn_8007E710 result: this fn writes +0x4 and returns it. */
typedef struct Obj2_80077164 {
    char pad0x0[0x4];
    s32 unk0x4;
} Obj2_80077164;
extern bool lbl_803016A8;
void *fn_80076F8C(void *, void *, s32, s32, s32);
s32 Script_GenerateCRC(void *);
void fn_8005626C(void *, void *);
void fn_80095574(void);
void *Mem_NewZero(s32);
Obj1_80077164 *fn_8007E710(void *, void *);
void fn_8007E820(void *, void *);
Obj2_80077164 *fn_80077164(Unk_FFAD6788 *arg0, Unk_9994C3F5 *arg1) {
    Obj1_80077164 *obj1;
    Obj2_80077164 *obj2;

    lbl_803016A8 = 0;
    obj1 = (Obj1_80077164 *) fn_80076F8C(arg0, arg1, 0, 0, 0);
    obj1->unk0x80 = Script_GenerateCRC(arg0);
    obj1->unk0x84 = (s32) arg1;
    fn_8005626C((void *) obj1, arg0);
    fn_80095574();
    obj2 = (Obj2_80077164 *) fn_8007E710(Mem_NewZero(0xD0), arg0);
    fn_8007E820((void *) obj2, (void *) obj1);
    obj2->unk0x4 = (s32) arg1;
    lbl_803016A8 = 1;
    return obj2;
}
