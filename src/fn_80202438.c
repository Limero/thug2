// range 0x80202438-0x80202448 (0x10 = 16B). Byte-identical.
// Identification: array element getter — returns *(void**)(self + 0x30 +
// idx * 0x24) (a 0x24-byte stride table). The index product must be
// materialized as a temp (`s32 off = idx * 0x24`) so ngccc emits the
// base in rA of the lwzx (recipe 66): `mulli r4; addi r3,r3,0x30;
// lwzx r3,r3,r4` — the inline form puts the mulli term in rA (or merges
// into add+lwz).
// Suggested rename: Fn_80202438_TableGet.
#include "types.h"
void *fn_80202438(void *self, s32 idx) {
    char *base = (char *)self + 0x30;
    s32 off = idx * 0x24;
    return *(void **)(base + off);
}
