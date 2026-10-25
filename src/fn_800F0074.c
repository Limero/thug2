// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F0074-0x800F0224 (432B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct {
    char _p0[4];
    void *unk4;
    s32 unk8;
    void *unkC;
} F0074_node;

typedef struct {
    char _p0[4];
    s32 unk4;
} F0074_list;

void *Mem_NewZero(s32);
F0074_node *fn_800EFDC0(void *);
F0074_list *fn_801259C8(s32, s32);
s32 fn_80129528(F0074_list *, s32);
void fn_800F0AFC(void);
u8 *fn_8012DF28(void);
s32 strcasecmp(const char *, const char *);
s32 Script_GenerateCRC(const char *);
void fn_800EFEB8(F0074_node *, s32, s32);
void fn_801263A0(s32, char *);
void fn_800EFF9C(F0074_node *);
extern char lbl_8029B2FC[];

void fn_800F0074(F0074_node *arg0, s32 arg1) {
    char sp8[0x3E4];
    F0074_node *p;
    F0074_node *q;
    F0074_node *obj;
    F0074_list *list;
    u32 i;
    u32 count;
    register s32 next __asm__("r23");
    u8 *src;
    char *dst;
    char *firstdigit;
    s32 zero;
    u8 c;
    s8 sc;
    s32 crc;

    q = arg0->unk4;
    if (q != NULL) {
        do {
            q = (F0074_node *)q->unkC;
        } while (q != NULL);
    }
    i = 0;
    obj = fn_800EFDC0(Mem_NewZero(0x10));
    obj->unkC = arg0->unk4;
    arg0->unk4 = obj;
    obj->unk8 = arg1;
    list = fn_801259C8(arg1, 1);
    count = list->unk4;
    if (i < count) {
        do {
            fn_80129528(list, i);
            next = i + 1;
            fn_800F0AFC();
            p = (F0074_node *)fn_8012DF28();
            if (p != NULL) {
                src = (u8 *)p;
                firstdigit = NULL;
                c = *src;
                dst = sp8;
                if (c != 0) {
                    do {
                        *dst = (char)c;
                        if ((u32)(*src - 0x30) <= 9) {
                            if (firstdigit == NULL) {
                                firstdigit = dst;
                            }
                        } else {
                            firstdigit = NULL;
                        }
                        sc = (s8)*src;
                        if (sc == 0x5F) {
                            zero = 0;
                            *dst = 0;
                            if (strcasecmp(sp8, lbl_8029B2FC) != 0) {
                                fn_800EFEB8(obj, Script_GenerateCRC(sp8), i);
                            }
                            fn_801263A0(Script_GenerateCRC(sp8), sp8);
                            *dst = (char)sc;
                            dst[1] = 0;
                            fn_801263A0(Script_GenerateCRC(sp8), sp8);
                        }
                        c = *++src;
                        dst++;
                    } while (c != 0);
                }
                if (firstdigit != NULL) {
                    *firstdigit = 0;
                    crc = Script_GenerateCRC(sp8);
                    fn_800EFEB8(obj, crc, i);
                    fn_801263A0(crc, sp8);
                }
            }
            i = next;
        } while (i < count);
    }
    fn_800EFF9C(obj);
}
