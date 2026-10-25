// range 0x8000C410-0x8000C44C (0x3C). Byte-identical.
// Identification: indexed flag/state check. Reads the count-ish value
// self->0x10; if it is > 3, returns 2. Otherwise it indexes into the 4-entry
// .bss table lbl_80312434 (each entry 0xc bytes) and returns 2 if the byte at
// +0xa is non-zero, else 0. The n>3 guard bounds the index to the table's 4
// entries. The byte at +0xa is likely a per-entry "valid/allocated" flag.
//
// The matched form is the key tidbit: assigning the scaled base to a separate
// `unsigned char *p = (unsigned char*)lbl_80312434 + n*0xc` and then loading
// `p[0xa]` forces ngccc to fold the +0xa into the `lbz` displacement
// (`add r9,r9,<base>; lbz r0,0xa(r9)`) instead of folding it into a preceding
// `addi` — that single detail was the 13/15 -> 15/15 fix.
#include "types.h"
#include "structs.h"
extern unsigned char lbl_80312434[];
s32 fn_8000C410(CStruct *self) {
    s32 n = self->unk0x10;
    unsigned char *p;
    if (n > 3)
        return 2;
    p = (unsigned char *)lbl_80312434 + n * 0xc;
    return p[0xa] ? 2 : 0;
}