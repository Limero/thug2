// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80017C14-0x80017DA4 (400B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
/* Forward-declare OS types */
typedef struct OSThread OSThread;
typedef struct OSThreadQueue { OSThread* head; OSThread* tail; } OSThreadQueue;
typedef struct OSAlarm OSAlarm;
typedef s64 OSTime;
typedef void (*OSAlarmHandler)(OSAlarm*, void*);
struct OSThread { u8 _opaque[0x314]; };
struct OSAlarm { u8 _opaque[0x28]; };
void OSInitThreadQueue(OSThreadQueue*);
int OSCreateThread(OSThread*, void*(*)(void*), void*, void*, u32, s32, u16);
s32 OSResumeThread(OSThread*);
void OSSetAlarm(OSAlarm*, OSTime, OSAlarmHandler);
void fn_8001BA14(void *);
void GX_SetDispCopyGamma(s32);
void fn_800186CC(Unk_F6ED4C32 *);
void VISetPreRetraceCallback(void*);
void VISetPostRetraceCallback(void*);
void GX_SetBreakPtCallback(void (*)(void));
void fn_8001E17C(s32);
extern s32 lbl_80300148;
extern s32 lbl_8031E7C8;
extern s32 lbl_8031E7CC;
extern s32 lbl_8031E7D0;
extern s32 lbl_8031E7D4;
extern s8  lbl_8031E7D8;
extern s8  lbl_8031E7D9;
extern s8  lbl_8031E7DA;
extern s16 lbl_8031E7DC;
extern s16 lbl_8031E7DE;
extern OSThreadQueue lbl_8031E7E0;
extern OSThread lbl_8031E7E8;
extern OSThread lbl_8031FB28;
extern s32 lbl_803213CC;
extern s32 lbl_803213D0;
extern u8 lbl_80320E40[];
extern u32 lbl_800000F8; /* OS bus clock (absolute symbol, ldscript.tpl) */
void *fn_8001867C(void*);
void *fn_80018834(void*);
void VIPreCallback(void);
void VIPostCallback(void);
void BPCallback(void);
void fn_80018DEC(OSAlarm*, void*);
extern u8 lbl_8031E748[];
extern u8 lbl_8031E788[];
extern OSAlarm lbl_8031FB00;
#define ALARM1 (&lbl_8031FB00)
/* == lbl_8031FB00, but reached through the adjacent symbol so GCC keeps this
   address web separate from the &lbl_8031FB00 in OSSetAlarm (see header). */
#define ALARM1_STACK ((void *)((char *)&lbl_8031FB28 - 0x28))
void fn_80017C14(void) {
    u32 bus;
    lbl_80300148++;
    fn_8001BA14(0);
    GX_SetDispCopyGamma(0);
    lbl_8031E7D8 = 0;
    lbl_8031E7D9 = 0;
    lbl_8031E7DA = 0;
    lbl_8031E7DC = 0;
    lbl_8031E7DE = 1;
    fn_800186CC(lbl_8031E748);
    fn_800186CC(lbl_8031E788);
    OSInitThreadQueue(&lbl_8031E7E0);
    OSCreateThread(&lbl_8031E7E8, fn_8001867C, NULL,
                   ALARM1_STACK, 0x1000, 0xE, 1);
    OSResumeThread(&lbl_8031E7E8);
    /* Statement order is load-bearing (reverse-of-source store order + the
       base-register colouring want uses); see header. */
    lbl_8031E7C8 = lbl_803213CC;
    lbl_8031E7CC = lbl_803213D0;
    lbl_8031E7D4 = lbl_803213CC;
    lbl_8031E7D0 = lbl_803213D0;
    VISetPreRetraceCallback(VIPreCallback);
    VISetPostRetraceCallback(VIPostCallback);
    GX_SetBreakPtCallback(BPCallback);
    fn_8001E17C(0);
    OSCreateThread(&lbl_8031FB28, fn_80018834, NULL,
                   lbl_80320E40, 0x1000, 0xE, 1);
    bus = lbl_800000F8;
    OSSetAlarm(ALARM1, (OSTime)(bus / 4000) * 16, fn_80018DEC);
}
