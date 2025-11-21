#ifndef CONTROL_NODE_HPP
#define CONTROL_NODE_HPP

/**
 * @file ControlNode.hpp
 * @description Ana listedeki tek düğümün şekil zincirini nasıl sakladığını ve yönettiğini açıklar.
 * @course 1C
 * @assignment 1. ÖDEV
 * @date 11.2025
 * @author Ayşe Verda Gülcemal ayse.gulcemal@ogr.sakarya.edu.tr
 */

#include "ShapeNode.hpp"

class Shape;

class ControlNode {
public:
    explicit ControlNode(int id); // Yeni düğüm oluşturur
    ~ControlNode(); // Düğümü yok eder

    void insertShapeSorted(Shape* shape); // Şekli sıralı şekilde ekler
    bool removeShapeByIndex(int index); // Belirtilen indeksdeki şekli siler
    bool removeShape(Shape* shape); // Şekli siler

    void clearShapes(); // Şekilleri temizler
    int getShapeCount() const; // Şekil sayısını döndürür

    ShapeNode* getShapesHead() const; // Şekil zincirinin başını döndürür

    ControlNode* getPrev() const; // Önceki düğümü döndürür
    ControlNode* getNext() const; // Sonraki düğümü döndürür
    void setPrev(ControlNode* node); // Önceki düğümü ayarlar
    void setNext(ControlNode* node); // Sonraki düğümü ayarlar

    int getId() const; // Düğüm ID'sini döndürür
    void setId(int newId); // Düğüm ID'sini ayarlar

private:
    int id;
    ShapeNode* shapesHead; // Şekil zincirinin başı
    ControlNode* prev; // Önceki düğüm
    ControlNode* next; // Sonraki düğüm
};

#endif

