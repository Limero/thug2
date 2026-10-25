// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8001A7F0-0x8001A8F0 (256B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

extern char lbl_80320E48[256]; // buffer

char* strcpy(char*, const char*);
u32 strlen(const char*);

char* dvd_file_fix_name(const char* arg0) {
    char *p;
    s32 len;

    strcpy(lbl_80320E48, arg0);

    p = lbl_80320E48;
    while (*p != '\0') {
      if (*p == '\\') *p = '/';
      p++;
    }

    len = strlen(lbl_80320E48);
    if (lbl_80320E48[len - 1] == 'e' && lbl_80320E48[len - 2] == 'r' && lbl_80320E48[len - 3] == 'p') {
      lbl_80320E48[len - 1] = 'g';
    }

    if (lbl_80320E48[len - 2] == 'e' && lbl_80320E48[len - 3] == 'r' && lbl_80320E48[len - 4] == 'p') {
      lbl_80320E48[len - 2] = lbl_80320E48[len - 1];
      lbl_80320E48[len - 1] = lbl_80320E48[len];
    }

    return lbl_80320E48;
}
