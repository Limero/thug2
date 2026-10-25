// Promoted from src/wip — byte-identical match
// family=proto range=0x8011BEAC-0x8011BEFC size=80B
#include "types.h"
extern s32 fn_8011BC60(void);
extern void fn_80121178(void);
extern void fn_801210C4(s32, s32);
void fn_8011BEAC(s32 arg0) {
    if (fn_8011BC60() == 0) {
        if (arg0 == -1) {
            fn_80121178();
            return;
        }
        fn_801210C4(arg0, 1);
    }
}