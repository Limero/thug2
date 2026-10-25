// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8001ACCC-0x8001AD50 (132B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 dvd_file_size(CStruct *);                            

// dvd_file_seek @ 0x8001ACCC
bool dvd_file_seek(CStruct * arg0, s32 arg1, s32 arg2) {
    switch (arg1) {                                 
    case 0:
        arg0->unk0x74 = arg2;
        break;
    case 1:
        arg0->unk0x74 = (s32) (dvd_file_size(arg0) - arg2);
        break;
    case 2:
        arg0->unk0x74 = (s32) (arg0->unk0x74 + arg2);
        break;
    }
    arg0->unk0x70 = 0;
    return false;
}
