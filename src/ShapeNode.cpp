/**
 * @file ShapeNode.cpp
 * @description Şekillerin tek yönlü liste düğümü; her ControlNode içinde kullanılır.
 * @course 1C
 * @assignment 1. ÖDEV
 * @date 11.2025
 * @author Ayşe Verda Gülcemal ayse.gulcemal@ogr.sakarya.edu.tr
 */

#include "ShapeNode.hpp"
#include "Shape.hpp"

// Bu dosya tek yönlü liste düğümünün yaşam döngüsü ve erişim fonksiyonlarını içerir.
 
 ShapeNode::ShapeNode(Shape* data)
     : shape(data), next(nullptr) {}
 
 ShapeNode::~ShapeNode() {
     delete shape;
 }
 
 Shape* ShapeNode::getShape() const {
     return shape;
 }
 
 void ShapeNode::setShape(Shape* data) {
     shape = data;
 }
 
 ShapeNode* ShapeNode::getNext() const {
     return next;
 }
 
 void ShapeNode::setNext(ShapeNode* nextNode) {
     next = nextNode;
 }