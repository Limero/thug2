// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80009738-0x8000978C (84B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
// DehexifyDigit @ 0x80009738
u32 DehexifyDigit(const char *arg0) {
  u32 var_r9 = 0;
  if (*arg0 >= '0' && *arg0 <= '9')
    var_r9 = *arg0 - '0';
  else if (*arg0 >= 'a' && *arg0 <= 'v')
    var_r9 = *arg0 - 'a' + 10;
  else if (*arg0 >= 'A' && *arg0 <= 'V')
    var_r9 = *arg0 - 'A' + 10;

  return var_r9;
}
