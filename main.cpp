#include <iostream>

#include "PhysicalLayer.h"
#include "VirtualAddress.h"
#include "PhysicalAddress.h"
#include "VirtualLayer.h"
#include "Structures.h"
#include "VirtualLayerSystem.h"
#include "Constants.h"
#include "Kdbg.h"
#include "Vad.h"
#include "TreeForVad.h"
#include "Mmpfn.h"
using namespace nir;
#include "Carving.h"

int main() {

    auto phlayer = new PhysicalLayer("memdump.mem");
    auto base = new PhysicalAddress(0x1ad002, phlayer);
    auto virt = new VirtualLayerSystem(base);
    auto kdbg = virt->vtop(0xf8051c8cc5e0);
    Kdbg obj = Kdbg(0x107c117ff007f042,0xfe083912630b200, 0xf8051c74aa54,kdbg);
    obj = obj.DecryptKDBG();

    printf("Virtual Address Base: 0x%p\n", obj.KDBG->KernBase);
    printf("Virtual Address PsActiveProcessHead: 0x%p\n", obj.KDBG->PsActiveProcessHead);
    printf("Virtual Address MmPfnDatabase: 0x%p\n", obj.KDBG->MmPfnDatabase);
    VirtualAddress psActive = VirtualAddress(obj.KDBG->PsActiveProcessHead);
    virt->genList(psActive);
   //--------------------------------------------------------------------------
    auto mmpfn = new Mmpfn(virt,VirtualAddress(obj.KDBG->MmPfnDatabase));
    //--------------------------------------------------------------------------
    auto vec = virt->ProcessVirtualLayers();
    for (auto x : vec) {
        std::cout << x->Eprocess->name->ReadStr(_fileNameLen)<<std::endl;
        x->Vad = virt->GenVadForLayer(x);
//            std::cout << "Num of vads = " <<x->Vad->m_size<<std::endl;
//            std::cout<< "\nType Address of vad    FirstPrototypePte  LastContiguousPte"<<std::endl<<std::endl;
//            x->Vad->print();

    }
    //--------------------------------------------------------------------------
//
//    Carving carv = Carving(phlayer, &vec, mmpfn);
//    Scaner* ipv4 = new IPv4("res.pcap", 4096);
//    carv.scan(ipv4);


    //--------------------------------------------------------------------------

//    int i = 0;
//    for(auto  x : vec){
//        std::cout << x->Eprocess->name->ReadStr(_fileNameLen)<<std::endl;
//        std::cout << i<< std::endl;
//        x->Vad->vadtree();
//        i++;
//        }
//=-------------------------------------------------------------------------------
    vec[85]->Vad->vadtree();
    std::cout <<vec[85]->Eprocess->name->ReadStr(_fileNameLen)<<std::endl;
    auto a = vec[85]->vtop(0x53de000000);
//    std::cout << a->paddr << std::endl;
//    auto b = vec[85]->vtop(0x53de000000 + 0x1000);
//    std::cout << b->paddr<< std::endl;
//    auto c = vec[85]->vtop(0x53de000000 + 0x1000  *2);
//    std::cout << c->paddr<< std::endl;

    delete phlayer->file;
    return 0;
}
