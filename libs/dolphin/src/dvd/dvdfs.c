#include "dolphin/dvd.h"
#include "dolphin/os.h"

typedef struct FSTEntry FSTEntry;

struct FSTEntry
{
    unsigned int isDirAndStringOff;
    unsigned int parentOrPosition;
    unsigned int nextEntryOrLength;
};

/* rodata/sdata strings referenced by OSPanic calls (defined by auto units) */
extern char lbl_803060D8[]; /* "DVDConvertEntrynumToPath(...) 8.3 format..." */
extern char lbl_803061D8[]; /* "DVDReadAsync(): specified area is out of the file  " */
extern char lbl_8030620C[]; /* "DVDRead(): specified area is out of the file  " */

OSThreadQueue __DVDThreadQueue;
u32 __DVDLongFileNameFlag;
u32 currentDirectory;
u32 MaxEntryNum;
char *FstStringStart;
FSTEntry *FstStart;
OSBootInfo *BootInfo;

static void cbForReadAsync(s32 result, DVDCommandBlock *block);
static void cbForReadSync(s32 result, DVDCommandBlock *block);

void __DVDFSInit()
{
    BootInfo = (OSBootInfo *)OSPhysicalToCached(0);
    FstStart = (FSTEntry *)BootInfo->FSTLocation;

    if (FstStart)
    {
        MaxEntryNum = FstStart[0].nextEntryOrLength;
        FstStringStart = (char *)&(FstStart[MaxEntryNum]);
    }
}

/* For convenience */
#define entryIsDir(i) (((FstStart[i].isDirAndStringOff & 0xff000000) == 0) ? FALSE : TRUE)
#define stringOff(i) (FstStart[i].isDirAndStringOff & ~0xff000000)
#define parentDir(i) (FstStart[i].parentOrPosition)
#define nextDir(i) (FstStart[i].nextEntryOrLength)
#define filePosition(i) (FstStart[i].parentOrPosition)
#define fileLength(i) (FstStart[i].nextEntryOrLength)

static inline BOOL isSame(const char *path, const char *string)
{
    while (*string != '\0')
    {
        if (tolower(*path++) != tolower(*string++))
        {
            return FALSE;
        }
    }

    if ((*path == '/') || (*path == '\0'))
    {
        return TRUE;
    }

    return FALSE;
}

s32 DVDConvertPathToEntrynum(const char *pathPtr)
{
    const char *ptr;
    char *stringPtr;
    BOOL isDir;
    u32 length;
    u32 dirLookAt;
    u32 i;
    const char *origPathPtr = pathPtr;
    const char *extentionStart;
    BOOL illegal;
    BOOL extention;

    dirLookAt = currentDirectory;

    while (1)
    {
        if (*pathPtr == '\0')
        {
            return (s32)dirLookAt;
        }
        else if (*pathPtr == '/')
        {
            dirLookAt = 0;
            pathPtr++;
            continue;
        }
        else if (*pathPtr == '.')
        {
            if (*(pathPtr + 1) == '.')
            {
                if (*(pathPtr + 2) == '/')
                {
                    dirLookAt = parentDir(dirLookAt);
                    pathPtr += 3;
                    continue;
                }
                else if (*(pathPtr + 2) == '\0')
                {
                    return (s32)parentDir(dirLookAt);
                }
            }
            else if (*(pathPtr + 1) == '/')
            {
                pathPtr += 2;
                continue;
            }
            else if (*(pathPtr + 1) == '\0')
            {
                return (s32)dirLookAt;
            }
        }

        if (__DVDLongFileNameFlag == 0)
        {
            extention = FALSE;
            illegal = FALSE;

            for (ptr = pathPtr; (*ptr != '\0') && (*ptr != '/'); ptr++)
            {
                if (*ptr == '.')
                {
                    if ((ptr - pathPtr > 8) || (extention == TRUE))
                    {
                        illegal = TRUE;
                        break;
                    }
                    extention = TRUE;
                    extentionStart = ptr + 1;
                }
                else if (*ptr == ' ')
                    illegal = TRUE;
            }

            if ((extention == TRUE) && (ptr - extentionStart > 3))
                illegal = TRUE;

            if (illegal)
            {
                OSPanic(__FILE__, 379, lbl_803060D8, origPathPtr);
            }
        }
        else
        {
            for (ptr = pathPtr; (*ptr != '\0') && (*ptr != '/'); ptr++)
                ;
        }

        isDir = (*ptr == '\0') ? FALSE : TRUE;
        length = (u32)(ptr - pathPtr);

        ptr = pathPtr;

        for (i = dirLookAt + 1; i < nextDir(dirLookAt); i = entryIsDir(i) ? nextDir(i) : (i + 1))
        {
            if ((entryIsDir(i) == FALSE) && (isDir == TRUE))
            {
                continue;
            }

            stringPtr = FstStringStart + stringOff(i);

            if (isSame(ptr, stringPtr) == TRUE)
            {
                goto next_hier;
            }
        }

        return -1;

    next_hier:
        if (!isDir)
        {
            return (s32)i;
        }

        dirLookAt = i;
        pathPtr += length + 1;
    }
}

BOOL DVDFastOpen(s32 entrynum, DVDFileInfo *fileInfo)
{
    if ((entrynum < 0) || (entrynum >= MaxEntryNum) || entryIsDir(entrynum))
    {
        return FALSE;
    }

    fileInfo->startAddr = filePosition(entrynum);
    fileInfo->length = fileLength(entrynum);
    fileInfo->callback = (DVDCallback)NULL;
    fileInfo->cb.state = DVD_STATE_END;

    return TRUE;
}

BOOL DVDClose(DVDFileInfo *fileInfo)
{
    DVDCancel(&(fileInfo->cb));
    return TRUE;
}

BOOL DVDReadAsyncPrio(DVDFileInfo *fileInfo, void *addr, s32 length, s32 offset,
                      DVDCallback callback, s32 prio)
{
    if (!((0 <= offset) && (offset < fileInfo->length)))
    {
        OSPanic(__FILE__, 742, lbl_803061D8);
    }

    if (!((0 <= offset + length) && (offset + length < fileInfo->length + DVD_MIN_TRANSFER_SIZE)))
    {
        OSPanic(__FILE__, 748, lbl_803061D8);
    }

    fileInfo->callback = callback;
    DVDReadAbsAsyncPrio(&(fileInfo->cb), addr, length, (s32)(fileInfo->startAddr + offset),
                        cbForReadAsync, prio);

    return TRUE;
}
#ifndef offsetof
#define offsetof(type, memb) ((u32) & ((type *)0)->memb)
#endif

static void cbForReadAsync(s32 result, DVDCommandBlock *block)
{
    DVDFileInfo *fileInfo;

    fileInfo = (DVDFileInfo *)((char *)block - offsetof(DVDFileInfo, cb));
    if (fileInfo->callback)
    {
        (fileInfo->callback)(result, fileInfo);
    }
}

s32 DVDReadPrio(DVDFileInfo *fileInfo, void *addr, s32 length, s32 offset, s32 prio)
{
    BOOL result;
    DVDCommandBlock *block;
    s32 state;
    BOOL enabled;
    s32 retVal;

    if (!((0 <= offset) && (offset < fileInfo->length)))
    {
        OSPanic(__FILE__, 812, lbl_8030620C);
    }

    if (!((0 <= offset + length) && (offset + length < fileInfo->length + DVD_MIN_TRANSFER_SIZE)))
    {
        OSPanic(__FILE__, 818, lbl_8030620C);
    }

    block = &(fileInfo->cb);

    result = DVDReadAbsAsyncPrio(block, addr, length, (s32)(fileInfo->startAddr + offset),
                                 cbForReadSync, prio);

    if (result == FALSE)
    {
        return -1;
    }

    enabled = OSDisableInterrupts();

    while (1)
    {
        state = ((volatile DVDCommandBlock *)block)->state;

        if (state == DVD_STATE_END)
        {
            retVal = (s32)block->transferredSize;
            break;
        }
        else if (state == DVD_STATE_FATAL_ERROR)
        {
            retVal = -1;
            break;
        }
        else if (state == DVD_STATE_CANCELED)
        {
            retVal = -3;
            break;
        }

        OSSleepThread(&__DVDThreadQueue);
    }

    OSRestoreInterrupts(enabled);
    return retVal;
}

static void cbForReadSync(s32 result, DVDCommandBlock *block)
{
    OSWakeupThread(&__DVDThreadQueue);
}
