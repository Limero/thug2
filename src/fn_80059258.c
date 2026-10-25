// range 0x80059258-0x80059284 (0x2C). Byte-identical.
// Identification: snapshot + notify — copies *self into the global
// lbl_80364C38 (.bss) then calls fn_8007C148 (matched).
#include "types.h"
extern char lbl_80364C38[];
extern void fn_8007C148(void);
void fn_80059258(void *self) {
    *(s32 *)lbl_80364C38 = *(s32 *)self;
    fn_8007C148();
}