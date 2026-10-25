// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80016304-0x800163A0 (156B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

typedef struct {
    char pad0x0[0x18];
    void *fileHandle;
} CardSlotRef;

typedef struct {
    char fileName[0x20];
    u32 length;
    u32 time;
    u8 gameName[4];
    u8 company[2];
    u8 bannerFormat;
    char pad0;
    u32 iconAddr;
    u16 iconFormat;
    u16 iconSpeed;
    u32 commentAddr;
    u32 offsetBanner;
    u32 offsetBannerTlut;
    u32 offsetIcon[8];
    u32 offsetIconTlut;
    u32 offsetData;
} CStat;

s32 CARDGetStatus(s32, s32, CStat *);
void Mem_Free_3(s32);

s32 fn_80016304(CStruct *arg0, s32 arg1, s32 arg2) {
    CStat sp8;
    s32 var_r28;

    arg0->unk0x74 = arg1;
    if (arg0->unk0x78 != 0) {
        Mem_Free_3(arg0->unk0x78);
        arg0->unk0x78 = 0;
    }
    var_r28 = 0;
    switch (arg2) {
    case 0:
    case 1:
        break;
    case 2:
        if (CARDGetStatus((s32)((CardSlotRef *)arg0->unk0x80)->fileHandle,
                          arg0->unk0x64, &sp8) == 0) {
            var_r28 = sp8.length - arg1;
        }
        break;
    default:
        return 0;
    }
    return var_r28;
}
