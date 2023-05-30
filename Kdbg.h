//
// Created by sasha on 23.12.2022.
//

#ifndef NIR_KDBG_H
#define NIR_KDBG_H

#include "windows.h"
#include "PhysicalAddress.h"
#include "Structures.h"

namespace nir {
    typedef struct DBGKD_DEBUG_DATA_HEADER64 {
        struct LIST_ENTRY64 {
            struct LIST_ENTRY64 *Flink;
            struct LIST_ENTRY64 *Blink;
        } List;
        UINT32 OwnerTag;
        UINT32 Size;
    } DBGKD_DEBUG_DATA_HEADER64;

    struct KDDEBUGGER_DATA64 {
        DBGKD_DEBUG_DATA_HEADER64 Header;
        UINT64 KernBase;
        UINT64 BreakpointWithStatus;
        UINT64 SavedContext;
        UINT16 ThCallbackStack;
        UINT16 NextCallback;
        UINT16 FramePointer;
        UINT16 PaeEnabled: 1;
        UINT64 KiCallUserMode;
        UINT64 KeUserCallbackDispatcher;
        UINT64 PsLoadedModuleList;
        UINT64 PsActiveProcessHead;
        UINT64 PspCidTable;
        UINT64 ExpSystemResourcesList;
        UINT64 ExpPagedPoolDescriptor;
        UINT64 ExpNumberOfPagedPools;
        UINT64 KeTimeIncrement;
        UINT64 KeBugCheckCallbackListHead;
        UINT64 KiBugcheckData;
        UINT64 IopErrorLogListHead;
        UINT64 ObpRootDirectoryObject;
        UINT64 ObpTypeObjectType;
        UINT64 MmSystemCacheStart;
        UINT64 MmSystemCacheEnd;
        UINT64 MmSystemCacheWs;
        UINT64 MmPfnDatabase;
        UINT64 MmSystemPtesStart;

    };

    class Kdbg {
    public:
        UINT64 KiWaitNever;
        UINT64 KiWaitAlways;
        UINT64 KdpDataBlockEncodedAddress;
        KDDEBUGGER_DATA64* KDBG;
        Kdbg(UINT64 KiWaitNever, UINT64 KiWaitAlways, UINT64 KdpDataBlockEncodedAddress, PhysicalAddress *);
        Kdbg & DecryptKDBG();

    };

}
#endif //NIR_KDBG_H
