/**
 * @file ShapeNode.hpp
 * @description Şekillerin tek yönlü liste düğümü; her ControlNode içinde kullanılır.
 * @course 1C
 * @assignment 1. ÖDEV
 * @date 11.2025
 * @author Ayşe Verda Gülcemal ayse.gulcemal@ogr.sakarya.edu.tr
 */

#ifndef SHAPE_NODE_HPP
#define SHAPE_NODE_HPP


class Shape;

class ShapeNode {
public:
    explicit ShapeNode(Shape* data); // Yeni şekil düğümü oluşturur
    ~ShapeNode(); // Şekil düğümünü yok eder

    Shape* getShape() const; // Şekli döndürür
    void setShape(Shape* data); // Şekli ayarlar

    ShapeNode* getNext() const; // Sonraki düğümü döndürür
    void setNext(ShapeNode* nextNode); // Sonraki düğümü ayarlar

private:
    Shape* shape; // Şekil
    ShapeNode* next; // Sonraki düğüm
};

#endif

