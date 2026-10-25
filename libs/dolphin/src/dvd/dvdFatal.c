#include <dolphin/os.h>

/* FatalFunc lives in .sbss at 0x803CAAD8 (owned by the sbss auto unit).
   The fatal-message strings (Japanese/English/Europe) also stay in the
   auto .data unit; nothing in code references them in thug2's Oct-2002 DOL. */
extern void (*FatalFunc)(void);

void __DVDPrintFatalMessage(void)
{
    if (!FatalFunc)
    {
        return;
    }
    FatalFunc();
}
