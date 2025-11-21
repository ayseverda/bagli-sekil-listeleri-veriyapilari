/**
 * @file Screen.cpp
 * @description 2B tampon ayırma, temizleme ve ekrana yazdırma sorumluluğunu taşır.
 * @course 1C
 * @assignment 1. ÖDEV
 * @date 11.2025
 * @author Ayşe Verda Gülcemal ayse.gulcemal@ogr.sakarya.edu.tr
 */

#include <iostream>
#include <cstring>
#include "Screen.hpp"

// Bu dosya 2B tampon ayırma, temizleme ve ekrana yazdırma sorumluluğunu taşır.
using namespace std;

 Screen::Screen(int rows, int cols, char blank)
     : rows(rows), cols(cols), blankChar(blank), buffer(nullptr) {
     allocateBuffer();
     clear();
 }
 
 Screen::~Screen() {
     releaseBuffer();
 }
 
 void Screen::allocateBuffer() {
     buffer = new char*[rows];
     for (int i = 0; i < rows; ++i) {
         buffer[i] = new char[cols];
     }
 }
 
 void Screen::releaseBuffer() {
     if (!buffer) return;
     for (int i = 0; i < rows; ++i) {
         delete[] buffer[i];
     }
     delete[] buffer;
     buffer = nullptr;
 }
 
 void Screen::clear() {
    for (int i = 0; i < rows; ++i) {
        memset(buffer[i], blankChar, cols);
    }
 }
 
 void Screen::drawShape(const Shape& shape) {
     shape.draw(buffer, rows, cols);
 }
 
 void Screen::renderToConsole() const {
    system("cls");
    for (int i = 0; i < rows; ++i) {
        cout.write(buffer[i], cols);
        cout << '\n';
    }
 }
 
 char** Screen::getBuffer() { return buffer; }
 int Screen::getRows() const { return rows; }
 int Screen::getCols() const { return cols; }