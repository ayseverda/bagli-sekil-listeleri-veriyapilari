/**
 * @file Persistence.hpp
 * @description JSON okuma/yazma yardımcıları; program durumunu dosyaya aktarır/alır.
 * @course 1C
 * @assignment 1. ÖDEV
 * @date 11.2025
 * @author Ayşe Verda Gülcemal ayse.gulcemal@ogr.sakarya.edu.tr
 */

#ifndef PERSISTENCE_HPP
#define PERSISTENCE_HPP
using namespace std;
#include <string>

class ControlList; 

namespace Persistence {

bool loadFromJson(const string& path, ControlList& list, bool& isEmptyFile); // JSON dosyasından veri okur
bool saveToJson(const string& path, const ControlList& list); // JSON dosyasına veri yazar

}

#endif

