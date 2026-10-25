// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000B348-0x8000B554 (524B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

extern char lbl_8029003C[];
extern char lbl_80290040[];
extern char lbl_80290048[];
extern char lbl_80290054[];
extern char lbl_80290068[];
extern char lbl_80290078[];
extern char lbl_8029007C[];
extern char lbl_80290084[];
extern char lbl_803122B4[];
extern char lbl_80312334[];
extern char lbl_80290038[];
extern char lbl_80290060[];
extern char lbl_80290090[];
extern char lbl_80290094[];
extern s32 lbl_802FFE6C;
extern s32 lbl_802FFE54;
extern bool lbl_802FFE58;
extern bool lbl_802FFE5C;
extern bool lbl_802FFE68;

const char *GetCommandLineParam(const char *, s32, char**);
void* fn_8000B560(void*);
void fn_800168BC(s32, char**);
s32 CommandLineContainsFlag(const char *, s32, char**);
char *strcpy(char *, const char *);
s32 strcmp(const char*, const char*);
s32 sprintf(s32 arg0, ...);

void fn_8000B348(s32 argc, char** argv) {
    const char* temp_r3;

    fn_8000B560(lbl_80290038);
    fn_800168BC(argc, argv);

    if (CommandLineContainsFlag(lbl_8029003C, argc, argv)) {
        lbl_802FFE58 = 1;
    }
    if (CommandLineContainsFlag(lbl_80290040, argc, argv)) {
        lbl_802FFE58 = 0;
    }
    if (CommandLineContainsFlag(lbl_80290048, argc, argv)) {
        lbl_802FFE54 = 0;
    }

    if (CommandLineContainsFlag(lbl_80290054, argc, argv)) {
        lbl_802FFE5C = 1;
        if (argc > 2) {
            strcpy(lbl_803122B4, argv[2]);
            if (argc > 3) {
                strcpy(lbl_80312334, argv[3]);
            } else {
                sprintf(lbl_80312334, lbl_80290060);
            }
        }
    }

    if (CommandLineContainsFlag(lbl_80290068, argc, argv)) {
        lbl_802FFE5C = 0;
    }
    if (CommandLineContainsFlag(lbl_80290078, argc, argv)) {
        lbl_802FFE68 = 0;
    }
    if (CommandLineContainsFlag(lbl_8029007C, argc, argv)) {
        lbl_802FFE68 = 1;
    }

    temp_r3 = GetCommandLineParam(lbl_80290084, argc, argv);
    if (temp_r3) {
        if (strcmp(temp_r3, lbl_80290090) == 0) {
            lbl_802FFE6C = 50;
        }
        if (strcmp(temp_r3, lbl_80290094) == 0) {
            lbl_802FFE6C = 60;
        }
    }
}
