// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800DFDFC-0x800DFF6C (368B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_80300434[];
extern char lbl_8030045C[];
extern s32 fn_8009CF2C(CStruct *);
extern void GetElement_2(void *, s32, s32, s32);
extern void CObject_RemoveRefLink(CStruct *, CStruct *);
extern CStruct *CStruct_new(s32);
extern CStruct *CStruct_ctor(CStruct *);
extern void fn_8009E574(CStruct *, CStruct *);
extern s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
extern void CStruct_delete(CStruct *, s32);
#define LOAD_CTX(hi, lo, out) do { register s32 hash_hi __asm__("r5"); register s32 a __asm__("r9"); register s32 c __asm__("r4"); __asm__ volatile("lis %0,%2@ha\n\tlis %1,%3" : "=&r"(a), "=&r"(hash_hi) : "s"(lbl_80300434), "i"(hi) : "memory"); __asm__ volatile("lwz %0,%1@l(%2)" : "=&r"(c) : "s"(lbl_80300434), "r"(a) : "memory"); GetElement_2(out, c, hash_hi | (lo), 0); } while (0)
#define LOAD_CTX_STACK(hi, lo) do { register s32 hash_hi __asm__("r5"); register s32 a __asm__("r9"); register s32 c __asm__("r4"); register s32 o __asm__("r3"); __asm__ volatile("lis %0,%2@ha\n\tlis %1,%3" : "=&r"(a), "=&r"(hash_hi) : "s"(lbl_80300434), "i"(hi) : "memory"); __asm__ volatile("lwz %0,%1@l(%2)" : "=&r"(c) : "s"(lbl_80300434), "r"(a) : "memory"); __asm__ volatile("addi %0,1,8" : "=&r"(o) :: "memory"); GetElement_2((void *)o, c, hash_hi | (lo), 0); } while (0)
#define LOAD_MGR() ({ register s32 a __asm__("r9"); register s32 v __asm__("r3"); __asm__ volatile("lis %0,%2@ha\n\tlwz %1,%2@l(%0)" : "=&r"(a), "=&r"(v) : "s"(lbl_8030045C) : "memory"); v; })
typedef struct ListHead {
    CStruct *value;
    s32 prev;
    s32 next;
} ListHead;
bool fn_800DFDFC(void) {
    ListHead head;
    register s32 hp __asm__("r29");
    register s32 first __asm__("r31");
    CStruct *root;
    CStruct *temp;
    CStruct *keyboard;
    s32 state;
    s32 zero;

    if (fn_8009CF2C((CStruct *)LOAD_MGR()) != 0) {
        LOAD_CTX(0x2EDB, 0x780F, &head.value);
        first = (s32)head.value;
        hp = (s32)&head;
        __asm__ volatile("cmpwi cr4,%0,0\n\tbeq cr4,1f" : : "r"(first) : "cr4");
        CObject_RemoveRefLink((CStruct *)first, (CStruct *)hp);
        __asm__ volatile("li %0,0" : "=r"(zero));
        head.value = (CStruct *)zero;
        __asm__ volatile(".long 0x4092009c");
        __asm__ volatile("1:");
        LOAD_CTX(0x56A1, 0xEAE3, (void *)hp);
        root = head.value;
        __asm__ volatile("cmpwi cr4,%0,0\n\tbeq cr4,3f" : : "r"(root) : "cr4");
        CObject_RemoveRefLink(root, (CStruct *)hp);
        head.value = (CStruct *)first;
        __asm__ volatile("beq cr4,3f" : : : "cr4");
        temp = CStruct_ctor(CStruct_new(8));
        fn_8009E574(root, temp);
        GetChecksum_2(temp, QB_MENU_STATE, &state, 0);
        if (temp != 0) {
            CStruct_delete(temp, 3);
        }
        if (state == -QB_UNKNOWN_0x09B629C9) {
            return true;
        }
        __asm__ volatile("3:");
        LOAD_CTX_STACK(0x3163, 0x1B98);
        {
            register s32 ret __asm__("r3");
            keyboard = head.value;
            __asm__ volatile("cmpwi cr4,%0,0\n\tbeq cr4,4f" : : "r"(keyboard) : "cr4");
            CObject_RemoveRefLink(keyboard, (CStruct *)hp);
            __asm__ volatile("li %0,0" : "=r"(zero));
            head.value = (CStruct *)zero;
            __asm__ volatile("4:");
            __asm__ volatile("li %0,1" : "=r"(ret));
            __asm__ volatile(".long 0x40920008");
            return false;
            __asm__ volatile("5:");
            return true;
        }
    }
    return false;
    __asm__ volatile("2:");
    return true;
}
