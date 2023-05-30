//
// Created by sasha on 23.12.2022.
//

#ifndef NIR_VAD_H
#define NIR_VAD_H

#include "windows.h"

namespace nir_vad {


    struct _DISPATCHER_HEADER
    {
        union
        {
            volatile LONG Lock;                                                 //0x0
            LONG LockNV;                                                        //0x0
            struct
            {
                UCHAR Type;                                                     //0x0
                UCHAR Signalling;                                               //0x1
                UCHAR Size;                                                     //0x2
                UCHAR Reserved1;                                                //0x3
            };
            struct
            {
                UCHAR TimerType;                                                //0x0
                union
                {
                    UCHAR TimerControlFlags;                                    //0x1
                    struct
                    {
                        UCHAR Absolute:1;                                       //0x1
                        UCHAR Wake:1;                                           //0x1
                        UCHAR EncodedTolerableDelay:6;                          //0x1
                    };
                };
                UCHAR Hand;                                                     //0x2
                union
                {
                    UCHAR TimerMiscFlags;                                       //0x3
                    struct
                    {
                        UCHAR Index:6;                                          //0x3
                        UCHAR Inserted:1;                                       //0x3
                        volatile UCHAR Expired:1;                               //0x3
                    };
                };
            };
            struct
            {
                UCHAR Timer2Type;                                               //0x0
                union
                {
                    UCHAR Timer2Flags;                                          //0x1
                    struct
                    {
                        UCHAR Timer2Inserted:1;                                 //0x1
                        UCHAR Timer2Expiring:1;                                 //0x1
                        UCHAR Timer2CancelPending:1;                            //0x1
                        UCHAR Timer2SetPending:1;                               //0x1
                        UCHAR Timer2Running:1;                                  //0x1
                        UCHAR Timer2Disabled:1;                                 //0x1
                        UCHAR Timer2ReservedFlags:2;                            //0x1
                    };
                };
                UCHAR Timer2ComponentId;                                        //0x2
                UCHAR Timer2RelativeId;                                         //0x3
            };
            struct
            {
                UCHAR QueueType;                                                //0x0
                union
                {
                    UCHAR QueueControlFlags;                                    //0x1
                    struct
                    {
                        UCHAR Abandoned:1;                                      //0x1
                        UCHAR DisableIncrement:1;                               //0x1
                        UCHAR QueueReservedControlFlags:6;                      //0x1
                    };
                };
                UCHAR QueueSize;                                                //0x2
                UCHAR QueueReserved;                                            //0x3
            };
            struct
            {
                UCHAR ThreadType;                                               //0x0
                UCHAR ThreadReserved;                                           //0x1
                union
                {
                    UCHAR ThreadControlFlags;                                   //0x2
                    struct
                    {
                        UCHAR CycleProfiling:1;                                 //0x2
                        UCHAR CounterProfiling:1;                               //0x2
                        UCHAR GroupScheduling:1;                                //0x2
                        UCHAR AffinitySet:1;                                    //0x2
                        UCHAR Tagged:1;                                         //0x2
                        UCHAR EnergyProfiling:1;                                //0x2
                        UCHAR SchedulerAssist:1;                                //0x2
                        UCHAR ThreadReservedControlFlags:1;                     //0x2
                    };
                };
                union
                {
                    UCHAR DebugActive;                                          //0x3
                    struct
                    {
                        UCHAR ActiveDR7:1;                                      //0x3
                        UCHAR Instrumented:1;                                   //0x3
                        UCHAR Minimal:1;                                        //0x3
                        UCHAR Reserved4:2;                                      //0x3
                        UCHAR AltSyscall:1;                                     //0x3
                        UCHAR UmsScheduled:1;                                   //0x3
                        UCHAR UmsPrimary:1;                                     //0x3
                    };
                };
            };
            struct
            {
                UCHAR MutantType;                                               //0x0
                UCHAR MutantSize;                                               //0x1
                UCHAR DpcActive;                                                //0x2
                UCHAR MutantReserved;                                           //0x3
            };
        };
        LONG SignalState;                                                       //0x4
        struct _LIST_ENTRY WaitListHead;                                        //0x8
    };

    struct KEVENT
    {
        struct _DISPATCHER_HEADER Header;                                       //0x0
    };

    struct UNICODE_STRING
    {
        USHORT Length;                                                          //0x0
        USHORT MaximumLength;                                                   //0x2
        WCHAR* Buffer;                                                          //0x8
    };
    struct FILE_OBJECT
    {
        SHORT Type;                                                             //0x0
        SHORT Size;                                                             //0x2
        struct DEVICE_OBJECT* DeviceObject;                                    //0x8
        struct VPB* Vpb;                                                       //0x10
        VOID* FsContext;                                                        //0x18
        VOID* FsContext2;                                                       //0x20
        struct SECTION_OBJECT_POINTERS* SectionObjectPointer;                  //0x28
        VOID* PrivateCacheMap;                                                  //0x30
        LONG FinalStatus;                                                       //0x38
        struct FILE_OBJECT* RelatedFileObject;                                 //0x40
        UCHAR LockOperation;                                                    //0x48
        UCHAR DeletePending;                                                    //0x49
        UCHAR ReadAccess;                                                       //0x4a
        UCHAR WriteAccess;                                                      //0x4b
        UCHAR DeleteAccess;                                                     //0x4c
        UCHAR SharedRead;                                                       //0x4d
        UCHAR SharedWrite;                                                      //0x4e
        UCHAR SharedDelete;                                                     //0x4f
        ULONG Flags;                                                            //0x50
        struct UNICODE_STRING FileName;                                        //0x58
        union _LARGE_INTEGER CurrentByteOffset;                                 //0x68
        ULONG Waiters;                                                          //0x70
        ULONG Busy;                                                             //0x74
        VOID* LastLock;                                                         //0x78
        struct KEVENT Lock;                                                    //0x80
        struct KEVENT Event;                                                   //0x98
        struct IO_COMPLETION_CONTEXT* CompletionContext;                       //0xb0
        ULONGLONG IrpListLock;                                                  //0xb8
        struct _LIST_ENTRY IrpList;                                             //0xc0
        VOID* FileObjectExtension;                                              //0xd0
    };

    struct MMEXTEND_INFO {
        ULONGLONG CommittedSize;                                                //0x0
        ULONG ReferenceCount;                                                   //0x8
    };
    struct MI_VAD_SEQUENTIAL_INFO {
        ULONGLONG Length: 12;                                                    //0x0
        ULONGLONG Vpn: 52;                                                       //0x0
    };
    struct MMVAD_FLAGS2 {
        ULONG FileOffset: 24;                                                    //0x0
        ULONG Large: 1;                                                          //0x0
        ULONG TrimBehind: 1;                                                     //0x0
        ULONG Inherit: 1;                                                        //0x0
        ULONG NoValidationNeeded: 1;                                             //0x0
        ULONG PrivateDemandZero: 1;                                              //0x0
        ULONG Spare: 3;                                                          //0x0
    };

    struct MMVAD_FLAGS1 {
        ULONG CommitCharge: 31;                                                  //0x0
        ULONG MemCommit: 1;                                                      //0x0
    };
    struct EX_PUSH_LOCK {
        union {
            struct {
                ULONGLONG Locked: 1;                                             //0x0
                ULONGLONG Waiting: 1;                                            //0x0
                ULONGLONG Waking: 1;                                             //0x0
                ULONGLONG MultipleShared: 1;                                     //0x0
                ULONGLONG Shared: 60;                                            //0x0
            };
            ULONGLONG Value;                                                    //0x0
            VOID *Ptr;                                                          //0x0
        };
    };

    struct MM_SHARED_VAD_FLAGS {
        ULONG Lock: 1;                                                           //0x0
        ULONG LockContended: 1;                                                  //0x0
        ULONG DeleteInProgress: 1;                                               //0x0
        ULONG NoChange: 1;                                                       //0x0
        ULONG VadType: 3;                                                        //0x0
        ULONG Protection: 5;                                                     //0x0
        ULONG PreferredNode: 6;                                                  //0x0
        ULONG PageSize: 2;                                                       //0x0
        ULONG PrivateMemoryAlwaysClear: 1;                                       //0x0
        ULONG PrivateFixup: 1;                                                   //0x0
        ULONG HotPatchAllowed: 1;                                                //0x0
    };
    struct MM_GRAPHICS_VAD_FLAGS {
        ULONG Lock: 1;                                                           //0x0
        ULONG LockContended: 1;                                                  //0x0
        ULONG DeleteInProgress: 1;                                               //0x0
        ULONG NoChange: 1;                                                       //0x0
        ULONG VadType: 3;                                                        //0x0
        ULONG Protection: 5;                                                     //0x0
        ULONG PreferredNode: 6;                                                  //0x0
        ULONG PageSize: 2;                                                       //0x0
        ULONG PrivateMemoryAlwaysSet: 1;                                         //0x0
        ULONG WriteWatch: 1;                                                     //0x0
        ULONG FixedLargePageSize: 1;                                             //0x0
        ULONG ZeroFillPagesOptional: 1;                                          //0x0
        ULONG GraphicsAlwaysSet: 1;                                              //0x0
        ULONG GraphicsUseCoherentBus: 1;                                         //0x0
        ULONG GraphicsNoCache: 1;                                                //0x0
        ULONG GraphicsPageProtection: 3;                                         //0x0
    };

    struct MM_PRIVATE_VAD_FLAGS {
        ULONG Lock: 1;                                                           //0x0
        ULONG LockContended: 1;                                                  //0x0
        ULONG DeleteInProgress: 1;                                               //0x0
        ULONG NoChange: 1;                                                       //0x0
        ULONG VadType: 3;                                                        //0x0
        ULONG Protection: 5;                                                     //0x0
        ULONG PreferredNode: 6;                                                  //0x0
        ULONG PageSize: 2;                                                       //0x0
        ULONG PrivateMemoryAlwaysSet: 1;                                         //0x0
        ULONG WriteWatch: 1;                                                     //0x0
        ULONG FixedLargePageSize: 1;                                             //0x0
        ULONG ZeroFillPagesOptional: 1;                                          //0x0
        ULONG Graphics: 1;                                                       //0x0
        ULONG Enclave: 1;                                                        //0x0
        ULONG ShadowStack: 1;                                                    //0x0
        ULONG PhysicalMemoryPfnsReferenced: 1;                                   //0x0
    };

    struct MMVAD_FLAGS {
        ULONG Lock: 1;                                                           //0x0
        ULONG LockContended: 1;                                                  //0x0
        ULONG DeleteInProgress: 1;                                               //0x0
        ULONG NoChange: 1;                                                       //0x0
        ULONG VadType: 3;                                                        //0x0
        ULONG Protection: 5;                                                     //0x0
        ULONG PreferredNode: 6;                                                  //0x0
        ULONG PageSize: 2;                                                       //0x0
        ULONG PrivateMemory: 1;                                                  //0x0
    };


    struct RTL_BALANCED_NODE {
        union {
            struct RTL_BALANCED_NODE *Children[2];                             //0x0
            struct {
                struct RTL_BALANCED_NODE *Left;                                //0x0
                struct RTL_BALANCED_NODE *Right;                               //0x8
            };
        };
        union {
            struct {
                UCHAR Red: 1;                                                    //0x10
                UCHAR Balance: 2;                                                //0x10
            };
            ULONGLONG ParentValue;                                              //0x10
        };
    };

    struct MMVAD_SHORT {
        union {
            struct {
                struct MMVAD_SHORT *NextVad;                                   //0x0
                VOID *ExtraCreateInfo;                                          //0x8
            };
            struct RTL_BALANCED_NODE VadNode;                                  //0x0
        };
        ULONG StartingVpn;                                                      //0x18
        ULONG EndingVpn;                                                        //0x1c
        UCHAR StartingVpnHigh;                                                  //0x20
        UCHAR EndingVpnHigh;                                                    //0x21
        UCHAR CommitChargeHigh;                                                 //0x22
        UCHAR SpareNT64VadUChar;                                                //0x23
        LONG ReferenceCount;                                                    //0x24
        struct EX_PUSH_LOCK PushLock;                                          //0x28
        union {
            ULONG LongFlags;                                                    //0x30
            struct MMVAD_FLAGS VadFlags;                                       //0x30
            struct MM_PRIVATE_VAD_FLAGS PrivateVadFlags;                       //0x30
            struct MM_GRAPHICS_VAD_FLAGS GraphicsVadFlags;                     //0x30
            struct MM_SHARED_VAD_FLAGS SharedVadFlags;                         //0x30
            volatile ULONG VolatileVadLong;                                     //0x30
        } u;                                                                    //0x30
        union {
            ULONG LongFlags1;                                                   //0x34
            struct MMVAD_FLAGS1 VadFlags1;                                     //0x34
        } u1;                                                                   //0x34
        struct MI_VAD_EVENT_BLOCK *EventList;                                  //0x38
    };

    struct LIST_ENTRY
    {
        struct _LIST_ENTRY* Flink;                                              //0x0
        struct _LIST_ENTRY* Blink;                                              //0x8
    };
    struct MMSECTION_FLAGS2
    {
        USHORT PartitionId:10;                                                  //0x0
        UCHAR NoCrossPartitionAccess:1;                                         //0x2
        UCHAR SubsectionCrossPartitionReferenceOverflow:1;                      //0x2
    };
    struct MMSECTION_FLAGS
    {
        ULONG BeingDeleted:1;                                                   //0x0
        ULONG BeingCreated:1;                                                   //0x0
        ULONG BeingPurged:1;                                                    //0x0
        ULONG NoModifiedWriting:1;                                              //0x0
        ULONG FailAllIo:1;                                                      //0x0
        ULONG Image:1;                                                          //0x0
        ULONG Based:1;                                                          //0x0
        ULONG File:1;                                                           //0x0
        ULONG AttemptingDelete:1;                                               //0x0
        ULONG PrefetchCreated:1;                                                //0x0
        ULONG PhysicalMemory:1;                                                 //0x0
        ULONG ImageControlAreaOnRemovableMedia:1;                               //0x0
        ULONG Reserve:1;                                                        //0x0
        ULONG Commit:1;                                                         //0x0
        ULONG NoChange:1;                                                       //0x0
        ULONG WasPurged:1;                                                      //0x0
        ULONG UserReference:1;                                                  //0x0
        ULONG GlobalMemory:1;                                                   //0x0
        ULONG DeleteOnClose:1;                                                  //0x0
        ULONG FilePointerNull:1;                                                //0x0
        ULONG PreferredNode:6;                                                  //0x0
        ULONG GlobalOnlyPerSession:1;                                           //0x0
        ULONG UserWritable:1;                                                   //0x0
        ULONG SystemVaAllocated:1;                                              //0x0
        ULONG PreferredFsCompressionBoundary:1;                                 //0x0
        ULONG UsingFileExtents:1;                                               //0x0
        ULONG PageSize64K:1;                                                    //0x0
    };
    struct EX_FAST_REF
    {
        union
        {
            VOID* Object;                                                       //0x0
            ULONGLONG RefCnt:4;                                                 //0x0
            ULONGLONG Value;                                                    //0x0
        };
    };

    struct CONTROL_AREA
    {
        struct SEGMENT* Segment;                                               //0x0
        union
        {
            struct _LIST_ENTRY ListHead;                                        //0x8
            VOID* AweContext;                                                   //0x8
        };
        ULONGLONG NumberOfSectionReferences;                                    //0x18
        ULONGLONG NumberOfPfnReferences;                                        //0x20
        ULONGLONG NumberOfMappedViews;                                          //0x28
        ULONGLONG NumberOfUserReferences;                                       //0x30
        union
        {
            ULONG LongFlags;                                                    //0x38
            struct MMSECTION_FLAGS Flags;                                      //0x38
        } u;                                                                    //0x38
        union
        {
            ULONG LongFlags;                                                    //0x3c
            struct MMSECTION_FLAGS2 Flags;                                     //0x3c
        } u1;                                                                   //0x3c
        struct EX_FAST_REF FilePointer;                                        //0x40
        volatile LONG ControlAreaLock;                                          //0x48
        ULONG ModifiedWriteCount;                                               //0x4c
        struct MI_CONTROL_AREA_WAIT_BLOCK* WaitList;                           //0x50
        union
        {
            struct
            {
                union
                {
                    ULONG NumberOfSystemCacheViews;                             //0x58
                    ULONG ImageRelocationStartBit;                              //0x58
                };
                union
                {
                    volatile LONG WritableUserReferences;                       //0x5c
                    struct
                    {
                        ULONG ImageRelocationSizeIn64k:16;                      //0x5c
                        ULONG SystemImage:1;                                    //0x5c
                        ULONG CantMove:1;                                       //0x5c
                        ULONG StrongCode:2;                                     //0x5c
                        ULONG BitMap:2;                                         //0x5c
                        ULONG ImageActive:1;                                    //0x5c
                        ULONG ImageBaseOkToReuse:1;                             //0x5c
                    };
                };
                union
                {
                    ULONG FlushInProgressCount;                                 //0x60
                    ULONG NumberOfSubsections;                                  //0x60
                    struct MI_IMAGE_SECURITY_REFERENCE* SeImageStub;           //0x60
                };
            } e2;                                                               //0x58
        } u2;                                                                   //0x58
        struct EX_PUSH_LOCK FileObjectLock;                                    //0x68
        volatile ULONGLONG LockedPages;                                         //0x70
        union
        {
            ULONGLONG IoAttributionContext:61;                                  //0x78
            ULONGLONG Spare:3;                                                  //0x78
            ULONGLONG ImageCrossPartitionCharge;                                //0x78
            ULONGLONG CommittedPageCount:36;                                    //0x78
        } u3;                                                                   //0x78
    };
    struct RTL_AVL_TREE
    {
        struct RTL_BALANCED_NODE* Root;                                        //0x0
    };
    struct MI_SUBSECTION_ENTRY1
    {
        ULONG CrossPartitionReferences:30;                                      //0x0
        ULONG SubsectionMappedLarge:2;                                          //0x0
    };
    struct MMSUBSECTION_FLAGS
    {
        USHORT SubsectionAccessed:1;                                            //0x0
        USHORT Protection:5;                                                    //0x0
        USHORT StartingSector4132:10;                                           //0x0
        USHORT SubsectionStatic:1;                                              //0x2
        USHORT GlobalMemory:1;                                                  //0x2
        USHORT Spare:1;                                                         //0x2
        USHORT OnDereferenceList:1;                                             //0x2
        USHORT SectorEndOffset:12;                                              //0x2
    };

    struct SUBSECTION
    {
        struct CONTROL_AREA* ControlArea;                                      //0x0
        struct MMPTE* SubsectionBase;                                          //0x8
        struct SUBSECTION* NextSubsection;                                     //0x10
        union
        {
            struct RTL_AVL_TREE GlobalPerSessionHead;                          //0x18
            struct MI_CONTROL_AREA_WAIT_BLOCK* CreationWaitList;               //0x18
            struct MI_PER_SESSION_PROTOS* SessionDriverProtos;                 //0x18
        };
        union
        {
            ULONG LongFlags;                                                    //0x20
            struct MMSUBSECTION_FLAGS SubsectionFlags;                         //0x20
        } u;                                                                    //0x20
        ULONG StartingSector;                                                   //0x24
        ULONG NumberOfFullSectors;                                              //0x28
        ULONG PtesInSubsection;                                                 //0x2c
        union
        {
            struct MI_SUBSECTION_ENTRY1 e1;                                    //0x30
            ULONG EntireField;                                                  //0x30
        } u1;                                                                   //0x30
        ULONG UnusedPtes:30;                                                    //0x34
        ULONG ExtentQueryNeeded:1;                                              //0x34
        ULONG DirtyPages:1;                                                     //0x34
    };

    struct MMVAD {
        struct MMVAD_SHORT Core;                                               //0x0
        union {
            ULONG LongFlags2;                                                   //0x40
            volatile struct MMVAD_FLAGS2 VadFlags2;                            //0x40
        } u2;                                                                   //0x40
        struct SUBSECTION *Subsection;                                         //0x48
        struct MMPTE *FirstPrototypePte;                                       //0x50
        struct MMPTE *LastContiguousPte;                                       //0x58
        struct LIST_ENTRY ViewLinks;                                           //0x60
        struct EPROCESS *VadsProcess;                                          //0x70
        union {
            struct MI_VAD_SEQUENTIAL_INFO SequentialVa;                        //0x78
            struct MMEXTEND_INFO *ExtendedInfo;                                //0x78
        } u4;                                                                   //0x78
        struct FILE_OBJECT *FileObject;                                        //0x80
    };
}
#endif //NIR_VAD_H
