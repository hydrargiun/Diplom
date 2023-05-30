//
// Created by sasha on 23.12.2022.
//

#include "Kdbg.h"
namespace nir{
    UINT64 magic(UINT64 input, Kdbg kdbgStruct);

    Kdbg::Kdbg(UINT64 WaitNever, UINT64 WaitAlways, UINT64 DataBlockEncodedAddress, PhysicalAddress *addr) {
        this->KiWaitNever = WaitNever;
        this->KiWaitAlways = WaitAlways;
        this->KdpDataBlockEncodedAddress = DataBlockEncodedAddress;
        this->KDBG = reinterpret_cast<KDDEBUGGER_DATA64 *>(addr->readBytes(sizeof(KDDEBUGGER_DATA64)));
    }

    Kdbg &Kdbg::DecryptKDBG() {
        KDBG->PsActiveProcessHead = magic(KDBG->PsActiveProcessHead, *this);
        KDBG->MmPfnDatabase = magic(KDBG->MmPfnDatabase,*this);
        KDBG->KernBase= magic(KDBG->KernBase,*this);

        return *this;
    }
    UINT64 magic(UINT64 input, Kdbg kdbgStruct){
        UINT64 low_byte = (kdbgStruct.KiWaitNever & 0xFFFFFFFF) & 0xFF;
        input = _rotl64(input ^ kdbgStruct.KiWaitNever, (int)low_byte);
        UINT64 swap_xor = (_magic + kdbgStruct.KdpDataBlockEncodedAddress) | 0xFFFF000000000000;
        input =  _byteswap_uint64(input ^ swap_xor);
        input = input ^ kdbgStruct.KiWaitAlways;
        return input;
    }
}