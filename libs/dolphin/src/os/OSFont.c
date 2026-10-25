// OLD-SDK OSFont.c revision (thug2's Feb-2003 build, matches tww's form):
// fontEncode sentinel is 0xFFFF and OSGetFontEncode returns early when the
// encode has already been resolved (<= 1). The newer in-tree revision used a
// switch on __OSTVMode and set ParseString, which does not match the DOL.
#include <dolphin/os.h>
#include <dolphin/os/OSFont.h>
#include <dolphin/vi.h>

u16 OSGetFontEncode(void) {
    static u16 fontEncode = 0xFFFF;

    if (fontEncode <= 1) {
        return fontEncode;
    }

    switch (*(u32*)OSPhysicalToCached(0xCC)) {
    case VI_NTSC:
        fontEncode = ((__VIRegs[55] & 2) != 0)
                         ? OS_FONT_ENCODE_SJIS
                         : OS_FONT_ENCODE_ANSI;
        break;
    case VI_PAL:
    case VI_MPAL:
    case VI_DEBUG:
    case VI_DEBUG_PAL:
    case VI_EURGB60:
    default:
        fontEncode = OS_FONT_ENCODE_ANSI;
    }

    return fontEncode;
}
