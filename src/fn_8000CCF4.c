// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000CCF4-0x8000CDDC (232B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
typedef struct Entry {
    s32 value;
    u8 *arg1;
    u8 *arg2;
    s32 pad0xC;
    s32 size;
} Entry;
typedef struct Owner {
    char pad0x0[0xC];
    s32 allocator;
    Entry *entry;
    s32 pad0x14;
    s32 flag;
} Owner;
typedef struct AllocPool {
    char pad0x0[0x118];
    Unk_E15B2970 *unk0x118;
    Unk_E15B2970 *unk0x11C;
} AllocPool;
extern char lbl_802FFE98[];
void fn_8000C9CC(u8 *, u8 *, s32);
char *fn_8000F10C(Unk_4897C6F8 *, s32, s32, Unk_E15B2970 *);
void fn_8001075C(s32);
s32 fn_8000CE8C(Owner *, s32);
s32 fn_8000E68C(s32, void *, s32);
void fn_800181A4(s32, s32);
s32 fn_8000CCF4(Owner *arg0, s32 arg1) {
    s32 temp_r3;
    s32 var_r4;
    s32 one;
    Unk_E15B2970 *var_r6;
    AllocPool *pool;
    register char *page __asm__("r9");
    register s32 entry_base __asm__("r30");
    Entry *temp_r9;
    Entry *temp_r9_2;

    temp_r3 = fn_8000E68C(arg0->allocator, arg1, 0);
    if (temp_r3 == 0) {
        __asm__ __volatile__("" ::: "memory");
        return 0;
    }
    fn_8000CE8C(arg0, temp_r3);
    fn_800181A4(0, 0);
    temp_r9 = arg0->entry;
    if ((temp_r9->arg2 == NULL) && (temp_r9->value != 0)) {
        fn_8001075C(arg1);
        if (arg0->flag != 0) {
            __asm__("lis %0,0x8030" : "=r"(page));
            entry_base = (s32)arg0->entry;
            __asm__("lwz %0,-0x168(%1)" : "=r"(pool) : "r"(page));
            __asm__("li %0,1" : "=r"(one));
            var_r4 = ((Entry *)entry_base)->size;
            var_r6 = pool->unk0x11C;
        } else {
            __asm__("lis %0,0x8030" : "=r"(page));
            entry_base = (s32)arg0->entry;
            __asm__("lwz %0,-0x168(%1)" : "=r"(pool) : "r"(page));
            __asm__("li %0,1" : "=r"(one));
            var_r4 = ((Entry *)entry_base)->size;
            var_r6 = pool->unk0x118;
        }
        ((Entry *)entry_base)->arg2 = (u8 *)fn_8000F10C((Unk_4897C6F8 *)pool,
                                                         var_r4, one, var_r6);
        fn_80010760();
        temp_r9_2 = arg0->entry;
        fn_8000C9CC(temp_r9_2->arg1, temp_r9_2->arg2, temp_r9_2->value);
    }
    return temp_r3;
}
