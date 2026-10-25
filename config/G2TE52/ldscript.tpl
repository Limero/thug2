MEMORY
{
    text : origin = $ORIGIN
}

SECTIONS
{
    GROUP:
    {
        $SECTIONS
        .stack ALIGN(0x100):{}
    } > text

    lbl_CC008000 = 0xCC008000; /* GP fifo write register */
    lbl_CC006828 = 0xCC006828; /* DB/EXI debug register (DBInitComm) */
    lbl_800000F8 = 0x800000F8; /* OS bus clock (OS_BUS_CLOCK / __OSBusClock) */
    _stack_end = 0x803CC200;
    _stack_addr = (_stack_end + 0xFFFF + 0x7) & ~0x7;
    _db_stack_addr = (_stack_addr + 0x2000);
    _db_stack_end = _stack_addr;
    __ArenaLo = _stack_addr + 0x20; /* orig: 0x803DC220 (see docs/dolphin-sdk.md 8.3) */
    __ArenaHi = $ARENAHI;
}

FORCEACTIVE
{
    $FORCEACTIVE
}
