/**
 * @file RandomGenerator.hpp
 * @description Rastgele düğüm/şekil üretimi için yardımcı fonksiyonları içerir.
 * @course 1C
 * @assignment 1. ÖDEV
 * @date 11.2025
 * @author Ayşe Verda Gülcemal ayse.gulcemal@ogr.sakarya.edu.tr
 */

#ifndef RANDOM_GENERATOR_HPP
#define RANDOM_GENERATOR_HPP

class ControlList;

namespace RandomGenerator {

void seed(); // RNG'yi başlatır
void populateRandomData(ControlList& list, int nodeCount = 20, int minShapes = 2, int maxShapes = 7); // Rastgele verileri oluşturur

}

#endif

