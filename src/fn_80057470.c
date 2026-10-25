// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80057470-0x800575DC (364B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void AddInteger(CStruct *, s32, s32);
void AddString(CStruct *, s32, void *);
void fn_800577A0(CStruct *);
s32 fn_800577B4(CStruct *, s32 *);
s32 fn_80057CA0(CStruct *);
s32 fn_8005F550(s32);
s32 fn_8005F5EC(s32);
s32 fn_8005F620(s32);
s32 fn_8005F654(s32);
s32 fn_80056AC8(Unk_FFAD6788 *);
void fn_80057470(Unk_FFAD6788 *arg0, CStruct *arg1) {
    register s32 a0 __asm__("r27");
    s32 numSectors;
    CStruct *geoList;
    s32 numVerts;
    s32 numPolys;
    s32 numBasePolys;
    s32 numEnvMapPolys;
    CStruct *node;
    s32 geo;

    a0 = (s32)arg0;
    AddString(arg1, QB_FILENAME, (void *)a0);
    numSectors = 0;
    geoList = (CStruct *)(s32)((Unk_FFAD6788 *)a0)->unk0xD0;
    numVerts = 0;
    numPolys = 0;
    numBasePolys = 0;
    numEnvMapPolys = 0;
    if (geoList != 0) {
        fn_800577A0(geoList);
        while ((node = (CStruct *)fn_800577B4(geoList, 0)) != 0) {
            geo = fn_80057CA0(node);
            numSectors += 1;
            if (geo != 0) {
                numVerts += fn_8005F550(geo);
                numPolys += fn_8005F5EC(geo);
                numBasePolys += fn_8005F620(geo);
                numEnvMapPolys += fn_8005F654(geo);
            }
        }
    }
    AddInteger(arg1, QB_SECTORS, numSectors);
    AddInteger(arg1, QB_COLSECTORS, fn_80056AC8((Unk_FFAD6788 *)a0));
    AddInteger(arg1, QB_VERTS, numVerts);
    AddInteger(arg1, QB_POLYS, numPolys);
    AddInteger(arg1, QB_BASEPOLYS, numBasePolys);
    AddInteger(arg1, QB_BASEPOLYS, numBasePolys);
    AddInteger(arg1, QB_ENVMAPPOLYS, numEnvMapPolys);
    AddInteger(arg1, QB_TEXTUREMEMORY, *(s32 *)(*(s32 *)((char *)a0 + 0x84) + 0xC));
}
