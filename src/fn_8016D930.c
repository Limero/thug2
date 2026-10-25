// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8016D930-0x8016DAC0 (400B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

typedef struct {
    u8 data[0xA4];
} TodEnvironment;

typedef struct {
    TodEnvironment current;
    TodEnvironment next;
    CStruct *state_params;
    s32 transition_start;
    u32 current_tod;
    u32 next_tod;
    s32 transition_started;
    s32 field14;
    s32 field18;
    s32 field1C;
    s32 field20;
    s32 field24;
    s32 field28;
    s32 field2C;
    s32 field30;
    s32 state_length;
    s32 field38;
    s32 field3C;
    s32 field40;
    u8 pad0x44[4];
} TodEntry;

typedef struct {
    u8 header[0xC];
    TodEntry entries[2];
} TodManager;

extern s32 GetStructure_2(CStruct *, s32, s32 *, s32);
extern s32 GetInteger(CStruct *, s32, s32 *, s32);
extern void fn_8016F120(TodManager *, CStruct *, TodEnvironment *);

void fn_8016D930(TodManager *arg0, s32 arg1) {
    CStruct *sp8;
    u32 current_tod;
    u32 next_tod;

    if (arg0->entries[arg1].current_tod == QB_NIGHT) {
        arg0->entries[arg1].field38 += 1;
    }
    current_tod = arg0->entries[arg1].next_tod;
    arg0->entries[arg1].current_tod = current_tod;
    switch (current_tod) {
    case QB_MORNING:
        next_tod = QB_AFTERNOON;
        break;
    case QB_AFTERNOON:
        next_tod = QB_EVENING;
        break;
    case QB_EVENING:
        next_tod = QB_NIGHT;
        break;
    case QB_NIGHT:
        next_tod = QB_MORNING;
        break;
    default:
        next_tod = 0;
        break;
    }
    arg0->entries[arg1].next_tod = next_tod;
    GetStructure_2(arg0->entries[arg1].state_params, arg0->entries[arg1].current_tod, &sp8, 1);
    fn_8016F120(arg0, sp8, &arg0->entries[arg1].current);
    GetInteger(sp8, QB_STATE_LENGTH, &arg0->entries[arg1].state_length, 1);
    GetStructure_2(arg0->entries[arg1].state_params, arg0->entries[arg1].next_tod, &sp8, 1);
    fn_8016F120(arg0, sp8, &arg0->entries[arg1].next);
    arg0->entries[arg1].field40 = 0;
    arg0->entries[arg1].transition_start = 0;
    arg0->entries[arg1].field20 = 0;
    arg0->entries[arg1].field18 = 0;
    arg0->entries[arg1].transition_started = 0;
    arg0->entries[arg1].field3C = 0;
}
