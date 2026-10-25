// range=0x800245E0-0x80024610 size=48B
// Calls fn_800244E0(arg0), then returns *(float*)(arg0 + 0xBC).
// Suggested rename: GetField_0xBC
#include "types.h"
#include "structs.h"

void fn_800244E0(Unk_FFAD6788 *);

f32 fn_800245E0(Unk_FFAD6788 *arg0) {
    fn_800244E0(arg0);
    return *((f32 *)&arg0->unk0xBC);
}
