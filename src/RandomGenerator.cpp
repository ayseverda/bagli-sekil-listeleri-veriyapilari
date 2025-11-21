/**
 * @file RandomGenerator.cpp
 * @description Rastgele düğüm/şekil üretimi için yardımcı fonksiyonları içerir.
 * @course 1C
 * @assignment 1. ÖDEV
 * @date 11.2025
 * @author Ayşe Verda Gülcemal ayse.gulcemal@ogr.sakarya.edu.tr
 */
#include "RandomGenerator.hpp"

#include <random>
#include <algorithm>

#include "Config.hpp"
#include "ControlList.hpp"
#include "ControlNode.hpp"
#include "Triangle.hpp"
#include "Rectangle.hpp"
#include "Star.hpp"

// Bu dosya rastgele düğüm/şekil üretimi için yardımcı fonksiyonları içerir.
using namespace std;

namespace {

// Tek bir RNG örneği uygulama boyunca kullanılıyor.
mt19937& rng() {
    static mt19937 engine{random_device{}()};
    return engine;
}

int randomInt(int minVal, int maxVal) {
    uniform_int_distribution<int> dist(minVal, maxVal);
    return dist(rng());
}

// Şekillerin karakterini farklılaştırmak için basit bir seçim dizisi.
char randomChar() {
    const char chars[] = {'*', '#', '+', 'o', 'x', '%', '@' };
    uniform_int_distribution<int> dist(0, sizeof(chars) / sizeof(chars[0]) - 1);
    return chars[dist(rng())];
}

// Rastgele tür seçip sınırlar içinde bir şekil nesnesi üretir.
// Şekillerin kenarları hiçbir zaman ekran sınırlarından taşmayacak şekilde oluşturulur.
Shape* createRandomShape(int cols, int rows) {
    int type = randomInt(0, 2);
    int z = randomInt(0, 100);
    char ch = randomChar();

    if (type == 0) { // Rectangle
        int width = randomInt(3, 10);
        int height = randomInt(2, 6);
        
        // Sol sınır: x >= SHAPE_AREA_START_X
        // Sağ sınır: x + width <= SCREEN_COLS, yani x <= SCREEN_COLS - width
        int minX = SHAPE_AREA_START_X;
        int maxX = max(minX, cols - width);
        
        // Üst sınır: y >= 0
        // Alt sınır: y + height <= SCREEN_ROWS, yani y <= SCREEN_ROWS - height
        int minY = 0;
        int maxY = max(minY, rows - height);
        
        int x = randomInt(minX, maxX);
        int y = randomInt(minY, maxY);
        return new Rectangle(x, y, width, height, ch, z);
    }

    if (type == 1) { // Triangle
        int size = randomInt(2, 6);
        
        // Sol sınır: x - (size-1) >= SHAPE_AREA_START_X, yani x >= SHAPE_AREA_START_X + (size-1)
        // Sağ sınır: x + (size-1) < SCREEN_COLS, yani x < SCREEN_COLS - (size-1), yani x <= SCREEN_COLS - (size-1) - 1
        int minX = SHAPE_AREA_START_X + (size - 1);
        int maxX = max(minX, cols - (size - 1) - 1);
        
        // Üst sınır: y >= 0
        // Alt sınır: y + size <= SCREEN_ROWS, yani y <= SCREEN_ROWS - size
        int minY = 0;
        int maxY = max(minY, rows - size);
        
        int x = randomInt(minX, maxX);
        int y = randomInt(minY, maxY);
        return new Triangle(x, y, size, ch, z);
    }

    // Star
    int radius = randomInt(1, 4);
    
    // Sol sınır: x - radius >= SHAPE_AREA_START_X, yani x >= SHAPE_AREA_START_X + radius
    // Sağ sınır: x + radius < SCREEN_COLS, yani x < SCREEN_COLS - radius, yani x <= SCREEN_COLS - radius - 1
    int minX = SHAPE_AREA_START_X + radius;
    int maxX = max(minX, cols - radius - 1);
    
    // Üst sınır: y - radius >= 0, yani y >= radius
    // Alt sınır: y + radius < SCREEN_ROWS, yani y < SCREEN_ROWS - radius, yani y <= SCREEN_ROWS - radius - 1
    int minY = radius;
    int maxY = max(minY, rows - radius - 1);
    
    int x = randomInt(minX, maxX);
    int y = randomInt(minY, maxY);
    return new Star(x, y, radius, ch, z);
}

} 

namespace RandomGenerator {

void seed() {
    rng().seed(static_cast<unsigned>(random_device{}()));
}

void populateRandomData(ControlList& list, int nodeCount, int minShapes, int maxShapes) {
    const int rows = SCREEN_ROWS;
    const int cols = SCREEN_COLS;
    list.clear();

    for (int i = 0; i < nodeCount; ++i) {
        ControlNode* node = list.addNode(i);
        int shapeCount = randomInt(minShapes, maxShapes);
        for (int j = 0; j < shapeCount; ++j) {
            node->insertShapeSorted(createRandomShape(cols, rows));
        }
    }
}

} // namespace RandomGenerator

