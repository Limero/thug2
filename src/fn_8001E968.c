// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8001E968-0x8001EA14 (172B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -Ilibs/dolphin/include
#include "types.h"
#include "dolphin/gx/GXEnum.h"
typedef struct {
    u32 format;
    u32 address;
    u16 numEntries;
} GXTlutObj;
typedef struct {
    u32 texture_filter;
    u32 texture_lod;
    u32 texture_size;
    u32 texture_address;
    u32 user_data;
    u32 texture_format;
    u32 tlut_name;
    u16 texture_time_count;
    u8 texture_tile_type;
    u8 texture_flags;
} GXTexObj;
void GXInitTlutObj(GXTlutObj *, void *, GXTlutFmt, u16);
void GXLoadTlut(GXTlutObj *, u32);
void GXInitTexObjCI(GXTexObj *, void *, u16, u16, GXCITexFmt, GXTexWrapMode, GXTexWrapMode, GXBool, u32);
void GXInitTexObjFilter(GXTexObj *, GXTexFilter, GXTexFilter);
void GXLoadTexObj(GXTexObj *, GXTexMapID);
void fn_8001E968(void *image, u16 width, u16 height, GXCITexFmt format,
                 GXTexWrapMode wrapS, GXTexWrapMode wrapT, GXTexMapID map,
                 void *lut, u16 tlutEntries, GXTlutFmt tlutFormat, u32 tlutName) {
    GXTlutObj tlutObj;
    GXTexObj texObj;
    GXInitTlutObj(&tlutObj, lut, tlutFormat, tlutEntries);
    GXLoadTlut(&tlutObj, tlutName);
    GXInitTexObjCI(&texObj, image, width, height, format, wrapS, wrapT, GX_FALSE, tlutName);
    GXInitTexObjFilter(&texObj, GX_LINEAR, GX_LINEAR);
    GXLoadTexObj(&texObj, map);
}
