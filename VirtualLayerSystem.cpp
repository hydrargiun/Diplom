//
// Created by sasha on 18.12.2022.
//

#include <iostream>
#include "VirtualLayerSystem.h"

namespace nir {
    listEntry *add(VirtualLayer *layer, PhysicalAddress *ptr);

    VirtualLayerSystem::VirtualLayerSystem(PhysicalAddress *pml4Base) : VirtualLayer(pml4Base), List(nullptr) {
    }

    void VirtualLayerSystem::genList(VirtualAddress PsActiveProcessHead) {
        auto *list = new Structures_ListEntry(PsActiveProcessHead);
        list->PhisPsActiveProcessHead = this->vtop(PsActiveProcessHead);
        list->listEntry64 = add(this, list->PhisPsActiveProcessHead);
        //* init //
        listEntry *ptr = list->listEntry64;
        listEntry *prevPtr = nullptr;
        do {
            ptr->Next = add(this, ptr->Links->Flink);
            ptr->Prev = prevPtr;
            prevPtr = ptr;
            ptr = ptr->Next;
        } while (ptr->Links->Flink->paddr != list->PhisPsActiveProcessHead->paddr);

        ptr->Next = nullptr;


        this->List = list;
    }

    std::vector<VirtualLayer *> VirtualLayerSystem::ProcessVirtualLayers() const {
        std::vector<VirtualLayer *> ProcessesLayers;
        std::vector<EPROCESS *> Eprocess = this->List->GetEprocess();
        std::vector<EPROCESS *>::iterator iter;
        for (iter = Eprocess.begin(); iter != Eprocess.end(); ++iter) {
            ProcessesLayers.push_back(new VirtualLayer(*iter));
        }
        return ProcessesLayers;

    }

    binary_tree *VirtualLayerSystem::GenVadForLayer(VirtualLayer *procLayer) {
        auto treeRoot = new binary_tree(
                VirtualAddress(procLayer->Eprocess->vadRoot->ReadVirtFromMemory(sizeof(DWORD_PTR))));
        if (treeRoot->m_root->Addr.vaddr == 0x0) {
            treeRoot->m_size = 0;
            return treeRoot;
        }
        auto PhAddrVadRoot = this->vtop(treeRoot->m_root->Addr);
        auto *avlNode = reinterpret_cast<nir_vad::RTL_BALANCED_NODE *>(PhAddrVadRoot->readBytes(
                sizeof(nir_vad::RTL_BALANCED_NODE)));
        int num_of_vads = 0;
        walk(avlNode, treeRoot->m_root, num_of_vads);
        treeRoot->m_size = num_of_vads;
        return treeRoot;
    }

    void VirtualLayerSystem::walk(nir_vad::RTL_BALANCED_NODE *memoryNode, Node *treeNode, int &num) {
        if (memoryNode == nullptr) {
            treeNode = nullptr;
            return;
        }
        num++;
        auto currentMMVAD = reinterpret_cast<nir_vad::MMVAD *>(vtop(treeNode->Addr)->readBytes(sizeof(nir_vad::MMVAD)));
        treeNode->tag = vtop(treeNode->Addr)->ReadStr(4, _offsetVadTag);
        treeNode->FirstPrototypePte = VirtualAddress(reinterpret_cast<DWORD_PTR>(currentMMVAD->FirstPrototypePte));
        treeNode->LastContiguousPte = VirtualAddress(reinterpret_cast<DWORD_PTR>(currentMMVAD->LastContiguousPte));
        treeNode->start = VirtualAddress(reinterpret_cast<DWORD>(currentMMVAD->Core.StartingVpn));
        treeNode->end = VirtualAddress(reinterpret_cast<DWORD>(currentMMVAD->Core.EndingVpn));
        treeNode->start.vaddr *= _physiscalPageSize;
        treeNode->end.vaddr *= _physiscalPageSize;
        if (currentMMVAD->Subsection && treeNode->tag == "Vad ") {
            auto subsectionAddr = vtop(reinterpret_cast<DWORD_PTR>(currentMMVAD->Subsection));
            auto subsection = reinterpret_cast<nir_vad::SUBSECTION *>(subsectionAddr->readBytes(
                    sizeof(nir_vad::SUBSECTION)));
            auto controlAreaAddr = vtop(reinterpret_cast<DWORD_PTR>(subsection->ControlArea));
            auto controlArea = reinterpret_cast<nir_vad::CONTROL_AREA *>(controlAreaAddr->readBytes(
                    sizeof(nir_vad::CONTROL_AREA)));
            if(controlArea->FilePointer.Value) {
                auto filePointerAddr = vtop(controlArea->FilePointer.Value & 0xFFFFFFFFFFFF0);
                auto fileObject = reinterpret_cast<nir_vad::FILE_OBJECT* >(filePointerAddr->readBytes(sizeof (nir_vad::FILE_OBJECT)));
                auto bufAddr = vtop(reinterpret_cast<DWORD_PTR>(fileObject->FileName.Buffer));
                treeNode->FilenameAddr = VirtualAddress(reinterpret_cast<DWORD_PTR>(fileObject->FileName.Buffer));
                auto buffValue =bufAddr->ReadUnclearStr(fileObject->FileName.Length);
                treeNode->filename = buffValue;
                delete(filePointerAddr);
                delete(fileObject);
                delete(bufAddr);
            }
            delete(controlArea);
            delete(subsection);
            delete(controlAreaAddr);
            delete(subsectionAddr);

        }
        delete (currentMMVAD);
        treeNode->m_left = new Node(VirtualAddress(reinterpret_cast<DWORD_PTR>(memoryNode->Left)));
        auto leftPhVad = this->vtop(treeNode->m_left->Addr);
        nir_vad::RTL_BALANCED_NODE *avlLeftNode = nullptr;
        if (leftPhVad && leftPhVad->isVad()) {
            avlLeftNode = reinterpret_cast<nir_vad::RTL_BALANCED_NODE *>(leftPhVad->readBytes(
                    sizeof(nir_vad::RTL_BALANCED_NODE)));
        }
        walk(avlLeftNode, treeNode->m_left, num);
        delete (avlLeftNode);
        treeNode->m_right = new Node(VirtualAddress(reinterpret_cast<DWORD_PTR>(memoryNode->Right)));
        auto RightPhVad = this->vtop(treeNode->m_right->Addr);
        nir_vad::RTL_BALANCED_NODE *avlRightNode = nullptr;
        if (RightPhVad && RightPhVad->isVad()) {
            avlRightNode = reinterpret_cast<nir_vad::RTL_BALANCED_NODE *>(RightPhVad->readBytes(
                    sizeof(nir_vad::RTL_BALANCED_NODE)));
        }
        walk(avlRightNode, treeNode->m_right, num);
        delete (avlRightNode);

    }


    listEntry *add(VirtualLayer *layer, PhysicalAddress *ptr) {
        auto *listEntry64 = new listEntry;
        listEntry64->paddr = ptr;
        listEntry64->Links = new LINKS;
        listEntry64->Links->Flink = layer->vtop(listEntry64->paddr->ReadVirtFromMemory(sizeof(DWORD_PTR)));
        auto *PointerOfPlink = new PhysicalAddress(listEntry64->paddr, sizeof(DWORD_PTR));
        listEntry64->Links->Plink = layer->vtop(PointerOfPlink->ReadVirtFromMemory(sizeof(DWORD_PTR)));
        return listEntry64;
    }
}