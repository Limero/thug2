// range 0x800098F4-0x80009950 (92B). Byte-identical.
// Identification: memory allocator wrapper. Loads the allocator object from
// the global lbl_802FFE98, calls fn_8000F10C(obj, size, 1, 0) to allocate,
// then zeroes the fresh block via memset(). Returns the new block (NULL if
// allocation failed). Sibling of fn_800099AC, which allocates the same way but
// passes a per-call flag (the 4th arg) and wires arg-2 differently.
#include "types.h"
#include "structs.h"
void *fn_8000F10C(Unk_4897C6F8 *, s32, s32, Unk_E15B2970 *);
void *memset(void *, s32, s32);
extern char lbl_802FFE98[];
// Mem_NewZero @ 0x800098F4
void *Mem_NewZero(s32 size) {
    void *obj;
    obj = fn_8000F10C(*(void **)lbl_802FFE98, size, 1, 0);
    if (obj != 0) {
        memset(obj, 0, size);
    }
    return obj;
}