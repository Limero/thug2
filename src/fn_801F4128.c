// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F4128-0x801F4374 (588B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 GetString(CStruct *, s32, char **, s32);
void GetArray(CStruct *, s32, CStruct **, s32);
s32 ContainsFlag(CStruct *, s32);
s32 fn_801293FC(CStruct *, s32);
char *strcpy(char *, const char *);
void fn_801F3C18(void *, CStruct *);
void fn_801F3D10(void *, CStruct *);

typedef struct Goal_s {
    char pad0x0[0x32C];
    u8 gap_ids[10];
    u8 gap_count;
} Goal;

void fn_801F4128(Unk_4D38C000 *arg0, CStruct *arg1) {
    Goal *g = (Goal *)arg0;
    char *name;
    CStruct *arr;
    s32 i;
    s32 w;

    switch (*(u32 *)&arg0->unk0x114) {
    case QB_TRICKTRIS:
        GetInteger(arg1, QB_TRICKTRIS_BLOCK_SIZE, (s32 *)((char *)arg0 + 0x2F8), 0);
        GetInteger(arg1, QB_TRICKTRIS_TOTAL_TO_WIN, (s32 *)((char *)arg0 + 0x2FC), 0);
        goto block_18;
    case QB_COMBOSKATETRIS:
        GetInteger(arg1, QB_COMBO_SIZE, (s32 *)((char *)arg0 + 0x2F4), 0);
        if (ContainsFlag(arg1, QB_SINGLE_COMBO) != 0) {
            arg0->unk0x2F0 = 1;
        }
    case QB_SKATETRIS:
block_18:
        fn_801F3C18(arg0, arg1);
        break;
    case QB_HIGHSCORE:
    case QB_HIGHCOMBO:
        GetInteger(arg1, QB_SCORE, (s32 *)((char *)arg0 + 0x2CC), 0);
        break;
    case QB_GAP:
        name = 0;
        if (GetString(arg1, QB_REQUIRED_TRICK_NAME, &name, 0) != 0) {
            strcpy((char *)arg0 + 0x337, name);
        }
        arr = 0;
        GetArray(arg1, QB_GAPS, &arr, 0);
        if (arr != 0) {
            w = arr->unk0x4;
            g->gap_count = (u8)w;
            for (i = 0; i < g->gap_count; i++) {
                g->gap_ids[i] = (u8)fn_801293FC(arr, i);
            }
        }
        break;
    case QB_TRICKBEAT:
        fn_801F3D10(arg0, arg1);
        break;
    case QB_RACE:
        GetInteger(arg1, QB_RACE_TOTAL_LAPS, (s32 *)((char *)arg0 + 0x2D0), 0);
        GetInteger(arg1, QB_RACE_PER_CHECKPOINT_TIME, (s32 *)((char *)arg0 + 0x2D4), 0);
        break;
    }
}
