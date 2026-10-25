// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80012284-0x800122C4 (64B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

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

PipPreElement *fn_80012284(PipPreElement *element, u32 align_elements) {
    u32 data_size;
    u8 *next;

    data_size = element->serialized_size;
    if (element->expanded_size != 0) {
        data_size = element->expanded_size;
    }
    data_size = (data_size + 3) & ~3U;
    next = (u8 *)element + 0x10;
    next += element->name_length;
    if (align_elements != 0) {
        next = (u8 *)(((u32)next + 0xF) & ~0xFU);
    }
    return (PipPreElement *)(next + data_size);
}
