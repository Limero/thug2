// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80012D4C-0x80012E88 (316B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

typedef struct PipPreElement {
    u32 serialized_size;
    u32 expanded_size;
    u16 name_length;
    u16 flags;
    u32 name_hash;
    u8 payload[1];
} PipPreElement;

typedef struct PipPreFile {
    u32 serialized_size;
    u32 expanded_size;
    u32 element_count;
    PipPreElement element[1];
} PipPreFile;

extern s32 lbl_8031349C[];
extern char lbl_80290848[];
extern char lbl_80290858[];
extern char lbl_8029086C[];

s32 fn_80128A90(CStruct *, void *);
s32 fn_800122C4(s32);
PipPreElement *fn_80012284(PipPreElement *, u32);

bool ScriptDumpPipPreStatus(CStruct *arg0) {
    volatile s32 sp8;
    s32 show_preed, show_unpreed, only_open;
    s32 file_idx, elem_idx, elem_count, nx, spin_ctr;
    PipPreElement *elem;
    PipPreFile *file;

    show_preed = fn_80128A90(arg0, (s32)lbl_80290848);
    show_unpreed = fn_80128A90(arg0, (s32)lbl_80290858);
    only_open = fn_80128A90(arg0, (s32)lbl_8029086C);

    file_idx = 0;
    while (file_idx <= 0x63) {
        if (lbl_8031349C[file_idx] != 0 && show_preed != 0) {
            file = (PipPreFile *)fn_800122C4(lbl_8031349C[file_idx]);
            elem_count = file->element_count;
            elem = (PipPreElement *)((char *)file + 0xC);
            elem_idx = 0;
            while (elem_idx < elem_count) {
                __asm__("" : "+r"(elem_idx));
                if (only_open != 0) {
                    nx = elem_idx + 1;
                    if (elem->flags == 0) goto next_elem;
                }
                sp8 = 0;
                nx = elem_idx + 1;
                if (sp8 <= 0x1869F) {
                    do {
                        sp8 += 1;
                    } while (sp8 <= 0x1869F);
                }
next_elem:
                elem = fn_80012284(elem, 1);
                elem_idx = nx;
            }
        }
        file_idx++;
    }
    if (show_unpreed != 0) {
        spin_ctr = 0xC8;
        do {
            spin_ctr -= 1;
        } while (spin_ctr != 0);
    }
    return true;
}
