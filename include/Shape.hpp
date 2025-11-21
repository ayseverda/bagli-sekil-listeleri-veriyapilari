/**
 * @file Shape.hpp
 * @description Taban Shape sınıfı ve ortak davranışları tanımlar.
 * Tüm şekillerin ortak özellikleri (konum, karakter, z değeri) buradan gelir ve çizim/hareket gibi davranışları virtual fonksiyonlarla tanımlanır.
 * @course 1C
 * @assignment 1. ÖDEV
 * @date 11.2025
 * @author Ayşe Verda Gülcemal ayse.gulcemal@ogr.sakarya.edu.tr
 */

#ifndef SHAPE_HPP
#define SHAPE_HPP

class Shape {
public:
    Shape(int x, int y, char drawChar, int z); // Yeni şekil oluşturur
    virtual ~Shape(); // Şekli yok eder

    virtual void draw(char** buffer, int rows, int cols) const = 0; // Şekli çizer
    virtual void move(int dx, int dy); // Şekli hareket ettirir

    int getX() const; // Şeklin x eksenindeki konumunu döndürür
    int getY() const; // Şeklin y eksenindeki konumunu döndürür
    int getZ() const; // Şeklin z eksenindeki konumunu döndürür
    char getChar() const; // Şeklin karakterini döndürür

    void setPosition(int newX, int newY); // Şeklin konumunu ayarlar
    void setZ(int newZ); // Şeklin z değerini ayarlar

protected:
    int x; // Şeklin x eksenindeki konumu
    int y; // Şeklin y eksenindeki konumu
    char character; // Şeklin karakteri
    int z; // Şeklin z değeri
};

#endif

