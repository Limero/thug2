// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80016094-0x80016114 (128B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
typedef s64 OSTime;
typedef u32 OSTick;
typedef struct { s32 sec, min, hour, mday, mon, year, wday, yday, msec, usec; } OSCalendarTime;
typedef struct { u8 sec, min, hour, mday, mon, pad; u16 year; } PackedDate;
extern u32 lbl_800000F8;
void OSTicksToCalendarTime(OSTime, OSCalendarTime *);
void fn_80016094(OSTick arg0, PackedDate *arg1) {
    OSCalendarTime t;
    OSTime ticks;
    ticks = (OSTime)arg0 * (OSTime)(lbl_800000F8 >> 2);
    OSTicksToCalendarTime(ticks, &t);
    arg1->sec = t.sec;
    arg1->min = t.min;
    arg1->hour = t.hour;
    arg1->mday = t.mday;
    arg1->mon = t.mon + 1;
    arg1->year = t.year;
}
