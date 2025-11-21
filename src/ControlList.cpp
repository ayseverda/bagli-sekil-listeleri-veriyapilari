/**
 * @file ControlList.cpp
 * @description Ana çift yönlü liste yönetimini (ekleme/silme/gezinme) uygular.
 * @course 1C
 * @assignment 1. ÖDEV
 * @date 11.2025
 * @author Ayşe Verda Gülcemal ayse.gulcemal@ogr.sakarya.edu.tr
 */

// Bu dosya ana çift yönlü liste yönetimini (ekleme/silme/gezinme) uygular.
#include "ControlList.hpp"
// Çift yönlü liste başlangıçta boş.
ControlList::ControlList() 
     : head(nullptr), tail(nullptr), current(nullptr), count(0) {}
 
 ControlList::~ControlList() {
     clear(); // Listeyi temizler
 }
 
// Yeni düğümü listenin sonuna ekler ve toplam sayıyı günceller.
ControlNode* ControlList::addNode(int id) { // Yeni düğüm ekler
     ControlNode* node = new ControlNode(id); // Yeni düğüm oluşturur
 
     if (!head) { // Liste boşsa
         head = tail = node; // Baş ve son düğümü ayarlar
         current = head;
     } else {
         tail->setNext(node); // Son düğümün sonraki düğümünü ayarlar
         node->setPrev(tail); // Yeni düğümün önceki düğümünü ayarlar
         tail = node; // Son düğümü yeni düğümle günceller
     }
 
     ++count; // Toplam düğüm sayısını günceller
     return node;
 }
 
// Şu anki düğümü listeden çıkarır; komşuları birbirine bağlar.
bool ControlList::removeCurrentNode() {
     if (!current) {
         return false; // Şu anki düğüm yoksa false döndürür
     }
 
     ControlNode* toDelete = current; // Şu anki düğümü silmek için
    ControlNode* nextNode = current->getNext();
    ControlNode* prevNode = current->getPrev();
 
     if (prevNode) { // Şu anki düğümün önceki düğümü varsa
         prevNode->setNext(nextNode); // Önceki düğümün sonraki düğümünü günceller
     } else { // Şu anki düğümün önceki düğümü yoksa
         head = nextNode; // Baş düğümünü günceller
     }

    if (nextNode) {
        nextNode->setPrev(prevNode);
    } else {
        tail = prevNode;
    }
 
    current = nextNode ? nextNode : prevNode;
 
     delete toDelete; // Şu anki düğümü siler
     --count; // Toplam düğüm sayısını günceller
    if (count == 0) {
        head = tail = current = nullptr;
    }
 
     return true; // Başarılı bir şekilde silindi
 }
 
// Listedeki tüm düğümleri ve içlerindeki şekilleri serbest bırakır.
void ControlList::clear() {
     ControlNode* node = head; // Baş düğümünü silmek için
     while (node) {
         ControlNode* nextNode = node->getNext(); // Sonraki düğümü silmek için
         delete node; // Şu anki düğümü siler
         node = nextNode; // Sonraki düğümü günceller
     }
     head = tail = current = nullptr; // Baş, son ve şu anki düğümü null olarak ayarlar
     count = 0; // Toplam düğüm sayısını 0 olarak ayarlar
 }
 
 ControlNode* ControlList::getHead() const { return head; } // Baş düğümü döndürür
 ControlNode* ControlList::getTail() const { return tail; } // Son düğümü döndürür
 ControlNode* ControlList::getCurrent() const { return current; } // Şu anki düğümü döndürür
 
void ControlList::moveNext() {
     if (current && current->getNext()) { // Şu anki düğümün sonraki düğümü varsa
         current = current->getNext(); // Şu anki düğümün sonraki düğümüne geçer
     }
 }
 
void ControlList::movePrev() {
     if (current && current->getPrev()) { // Şu anki düğümün önceki düğümü varsa
         current = current->getPrev(); // Şu anki düğümün önceki düğümüne geçer
     }
 }
 
 int ControlList::getCount() const { return count; } // Toplam düğüm sayısını döndürür