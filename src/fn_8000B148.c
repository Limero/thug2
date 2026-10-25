// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000B148-0x8000B23C (244B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

s32 sIsPrefixedWith(const char *, const char *);
u32 strlen(const char *);

// GetCommandLineParam @ 0x8000B148
const char *GetCommandLineParam(const char *arg0, s32 argc, char** argv) {
  s32 i, len;
  char *next_char;
  const char *found = NULL;

  for (i = 0; i < argc; i++)
  {
    if (sIsPrefixedWith(argv[i], arg0)) {
      len = strlen(arg0);
      next_char = argv[i] + len;
      if (*next_char == '=') {
        ++next_char;
        if (*next_char){
          found = argv[i] + len + 1;
        }
        else {
          if (i < argc-1) {
            found = argv[i+1];
          }
        }
      } else if (*next_char == 0) {
        if (i<argc-1 && argv[i+1][0] == '=') {
          if (argv[i+1][1] == 0) {
            if (i < argc-2) {
              found = argv[i+2];
            }
          } else {
            found = argv[i+1]+1;
          }
        }
      }
    }
  }

  return found;
}
