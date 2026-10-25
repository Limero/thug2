#include <dolphin/dolphin.h>
#include <dolphin/os.h>

#include "__os.h"

extern void (* lbl_80310AB8[])();
extern void (* lbl_80310AC0[])();

static void __init_cpp(void);
static void __fini_cpp(void);

#pragma peephole off

void __init_user(void) {
    __init_cpp();
}

static void __init_cpp(void) {
	void (* * constructor)();

	/*
	 *	call static initializers
	 */
	for (constructor = lbl_80310AB8; *constructor; constructor++) {
		(*constructor)();
	}
}

static void __fini_cpp(void) {
    void (* * destructor)();

	/*
	 *	call destructors
	 */
    for (destructor = lbl_80310AC0; *destructor; destructor++) {
        (*destructor)();
    }
}

DECL_WEAK
void abort(void) {
    _ExitProcess();
}

DECL_WEAK
void exit(int status) {
    __fini_cpp();
    _ExitProcess();
}

void _ExitProcess(void) {
    PPCHalt();
}
