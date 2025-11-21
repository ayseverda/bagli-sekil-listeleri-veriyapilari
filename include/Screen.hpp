/**
 * @file Screen.hpp
 * @description Konsol çizim tamponu yönetimi; 2B char dizisini tutar ve ekrana basar.
 * @course 1C
 * @assignment 1. ÖDEV
 * @date 11.2025
 * @author Ayşe Verda Gülcemal ayse.gulcemal@ogr.sakarya.edu.tr
 */

#ifndef SCREEN_HPP
#define SCREEN_HPP


#include "Shape.hpp"

class Screen {
public:
    Screen(int rows = 25, int cols = 80, char blank = ' '); // Yeni ekran oluşturur
    ~Screen(); // Ekranı yok eder

    void clear(); // Ekranı temizler
    void drawShape(const Shape& shape); // Şekili çizer
    void renderToConsole() const; // Ekranı konsola yazdırır

    char** getBuffer(); // Ekran tamponunu döndürür
    int getRows() const; // Ekran satır sayısını döndürür
    int getCols() const; // Ekran sütun sayısını döndürür

private:
    void allocateBuffer(); // Ekran tamponunu ayırır
    void releaseBuffer(); // Ekran tamponunu serbest bırakır

    int rows; // Ekran satır sayısı
    int cols; // Ekran sütun sayısı
    char blankChar; // Boş karakter
    char** buffer; // Ekran tamponu
};

#endif

