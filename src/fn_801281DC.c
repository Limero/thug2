// Identified as a script-property lookup wrapper; suggested rename: ScriptGetProperty.
// range 0x801281DC-0x80128228 (76B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_8000A778(s32);
void GetString(CStruct *, s32 *, s32 *, s32);
void fn_801281DC(CStruct *arg0, void *arg1, void *arg2, s32 arg3) {
    GetString(arg0, fn_8000A778(arg1), arg2, arg3);
}
