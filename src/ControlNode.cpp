/**
 * @file ControlNode.cpp
 * @description Ana listedeki tek düğümün şekil zincirini nasıl sakladığını ve yönettiğini açıklar.
 * @course 1C
 * @assignment 1. ÖDEV
 * @date 11.2025
 * @author Ayşe Verda Gülcemal ayse.gulcemal@ogr.sakarya.edu.tr
 */

#include "ControlNode.hpp"
#include "Shape.hpp"

// Bu dosya ana listedeki tek düğümün şekil zincirini nasıl sakladığını ve yönettiğini açıklar.
using namespace std;
 
ControlNode::ControlNode(int id)
     : id(id), shapesHead(nullptr), prev(nullptr), next(nullptr) {} // Düğüm ID'sini ayarlar
 
 ControlNode::~ControlNode() {
     clearShapes(); // Şekilleri temizler
 }
 
// Tek yönlü listeye z değerine göre sıralı şekilde ekler.
void ControlNode::insertShapeSorted(Shape* shape) {
     ShapeNode* newNode = new ShapeNode(shape); // Yeni şekil düğümü oluşturur
 
     if (!shapesHead || shape->getZ() < shapesHead->getShape()->getZ()) { // Şekil zincirinin başı yoksa veya şeklin z değeri başındaki şeklin z değerinden küçükse
         newNode->setNext(shapesHead); // Yeni şekil düğümünü şekil zincirinin başına ekler
         shapesHead = newNode; // Şekil zincirinin başını yeni şekil düğümüne günceller
         return;
     }
 
     ShapeNode* current = shapesHead; // Şekil zincirinin başından başlayarak geçer
     while (current->getNext() &&
            current->getNext()->getShape()->getZ() <= shape->getZ()) { // Sonraki şeklin z değeri şeklin z değerinden küçükse veya eşitse
         current = current->getNext();
     } // Sonraki şekil düğümüne geçer
 
     newNode->setNext(current->getNext()); // Yeni şekil düğümünü sonraki şekil düğümüne ekler
     current->setNext(newNode); // Sonraki şekil düğümünü yeni şekil düğümüne günceller
 }
 
// Belirtilen indeksdeki şekli listeden siler.
bool ControlNode::removeShapeByIndex(int index) {
     if (!shapesHead || index < 0) {
         return false; // Şekil zincirinin başı yoksa veya indeks negatifse false döndürür
     }
 
     if (index == 0) { // İndeks 0 ise şekil zincirinin başını siler
         ShapeNode* toDelete = shapesHead; // Şekil zincirinin başını silmek için
         shapesHead = shapesHead->getNext(); // Şekil zincirinin başını günceller
         delete toDelete; // Şekil zincirinin başını siler
         return true; // Başarılı bir şekilde silindi
     }
 
     ShapeNode* current = shapesHead; // Şekil zincirinin başından başlayarak geçer
     for (int i = 0; current && i < index - 1; ++i) { // İndeks - 1'e kadar geçer
         current = current->getNext();
     } // Sonraki şekil düğümüne geçer
 
     if (!current || !current->getNext()) { // Sonraki şekil düğümü yoksa veya indeks - 1'e kadar geçemediyse false döndürür
         return false;
     }
 
     ShapeNode* toDelete = current->getNext(); // Sonraki şekil düğümünü silmek için
     current->setNext(toDelete->getNext()); // Sonraki şekil düğümünü günceller
     delete toDelete; // Sonraki şekil düğümünü siler
     return true; // Başarılı bir şekilde silindi
 }
 
// Şeklin adresine göre arayıp siler.
bool ControlNode::removeShape(Shape* shape) {
     if (!shapesHead) {
         return false; // Şekil zincirinin başı yoksa false döndürür
     }
 
     if (shapesHead->getShape() == shape) {
         ShapeNode* toDelete = shapesHead; // Şekil zincirinin başını silmek için
         shapesHead = shapesHead->getNext(); // Şekil zincirinin başını günceller
         delete toDelete; // Şekil zincirinin başını siler
         return true; // Başarılı bir şekilde silindi
     }
 
     ShapeNode* current = shapesHead; // Şekil zincirinin başından başlayarak geçer
     while (current->getNext() &&
            current->getNext()->getShape() != shape) {
         current = current->getNext();
     } // Sonraki şekil düğümüne geçer
 
     if (!current->getNext()) {
         return false; // Sonraki şekil düğümü yoksa false döndürür
     }
 
     ShapeNode* toDelete = current->getNext(); // Sonraki şekil düğümünü silmek için
     current->setNext(toDelete->getNext()); // Sonraki şekil düğümünü günceller
     delete toDelete; // Sonraki şekil düğümünü siler
     return true; // Başarılı bir şekilde silindi
 }
 
// Düğümdeki tüm şekilleri serbest bırakır.
void ControlNode::clearShapes() {
     ShapeNode* current = shapesHead; // Şekil zincirinin başından başlayarak geçer
     while (current) {
         ShapeNode* nextNode = current->getNext(); // Sonraki şekil düğümünü silmek için
         delete current; // Şu anki şekil düğümünü siler
         current = nextNode; // Sonraki şekil düğümüne geçer
     }
     shapesHead = nullptr; // Şekil zincirinin başını null olarak ayarlar
 }
 
 int ControlNode::getShapeCount() const {
     int count = 0; // Şekil sayısını sıfırlar
     ShapeNode* current = shapesHead; // Şekil zincirinin başından başlayarak geçer
     while (current) {
         ++count; // Şekil sayısını günceller
         current = current->getNext();
     } // Sonraki şekil düğümüne geçer
     return count; // Şekil sayısını döndürür
 }
 
 ShapeNode* ControlNode::getShapesHead() const {
     return shapesHead; // Şekil zincirinin başını döndürür
 }
 
 ControlNode* ControlNode::getPrev() const { return prev; } // Önceki düğümü döndürür
 ControlNode* ControlNode::getNext() const { return next; } // Sonraki düğümü döndürür
 
 void ControlNode::setPrev(ControlNode* node) { prev = node; } // Önceki düğümü ayarlar
 void ControlNode::setNext(ControlNode* node) { next = node; } // Sonraki düğümü ayarlar
 
 int ControlNode::getId() const { return id; } // Düğüm ID'sini döndürür
 void ControlNode::setId(int newId) { id = newId; } // Düğüm ID'sini ayarlar    