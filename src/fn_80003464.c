// range 0x80003464-0x80003468 (4B). Byte-identical.
// Empty init stub (blr); section attribute routes the object into .init
// (same mechanism as src/fn_80003334.c).
__attribute__((section(".init"))) void fn_80003464(void) {
}
