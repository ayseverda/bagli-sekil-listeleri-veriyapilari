/**
 * @file ControlList.hpp
 * @description Ana çift yönlü liste yönetimini (ekleme/silme/gezinme) uygular.
 * @course 1C
 * @assignment 1. ÖDEV
 * @date 11.2025
 * @author Ayşe Verda Gülcemal ayse.gulcemal@ogr.sakarya.edu.tr
 */

 #ifndef CONTROL_LIST_HPP
 #define CONTROL_LIST_HPP
 
 #include "ControlNode.hpp"
 
 class ControlList {
 public:
     ControlList();
     ~ControlList();
 
     ControlNode* addNode(int id); // Yeni düğüm ekler
     bool removeCurrentNode(); // Şu anki düğümü siler
     void clear(); // Listeyi temizler
 
     ControlNode* getHead() const; // Baş düğümü döndürür
     ControlNode* getTail() const; // Son düğümü döndürür
     ControlNode* getCurrent() const; // Şu anki düğümü döndürür
 
     void moveNext(); // Sonraki düğüme geçer
     void movePrev(); // Önceki düğüme geçer
 
     int getCount() const; // Toplam düğüm sayısını döndürür
 
 private:
     ControlNode* head; // Baş düğümü
     ControlNode* tail; // Son düğümü
     ControlNode* current; // Şu anki düğümü
     int count; // Toplam düğüm sayısı
 };
 
 #endif

