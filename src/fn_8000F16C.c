// range 0x8000F16C-0x8000F1A8 (60B). Byte-identical.
// Identification: virtual dispatch wrapper. Resolves the dispatcher object via
// this->cc->0, reads the vtable through dispatcher+0x80, and calls the method
// whose half-word offset is at vtable+0x28 back on `dispatcher + offset`
// (thunk-self dispatch). Pure indirect-branch — no inlined asm required; the
// `s16` jumptable-offset + vtable function-pointer form reproduces the want
// shape directly.
#include "types.h"
#include "structs.h"
s32 fn_8000F16C(Unk_4897C6F8 *self) {
    char *obj = self->unk0xCC;
    char *disp = *(char **)obj;
    char *vt = ((Unk_E15B2970 *)disp)->unk0x80;
    s32 (*fp)(char *) = *(s32 (**)(char *))(vt + 0x2c);
    return fp(disp + ((Unk_4F699D10 *)vt)->unk0x28);
}