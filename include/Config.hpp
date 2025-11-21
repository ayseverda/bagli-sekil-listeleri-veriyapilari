/**
* @file Config.hpp
* @description Ekran ve panel boyutlari icin sabitler. Her yerde kullanılacak ortak ölçüleri tek noktadan yönetmek için yazılmıştır.
* @course 1C
* @assignment 1. ÖDEV
* @date 11.2025
* @author Ayşe Verda Gülcemal ayse.gulcemal@ogr.sakarya.edu.tr
*/

#ifndef CONFIG_HPP
#define CONFIG_HPP

// Sabitler
constexpr int SCREEN_ROWS = 25; // Ekran satır sayısı
constexpr int SCREEN_COLS = 80; // Ekran sütun sayısı
constexpr int NODE_PANEL_WIDTH = 20; // Düğüm paneli genişliği
constexpr int NODE_PANEL_STEP = 3; // her düğüm paneli 3 satır yüksekliğinde
constexpr int NODE_PANEL_VISIBLE = SCREEN_ROWS / NODE_PANEL_STEP; // Görünür düğüm paneli satır sayısı
constexpr int SHAPE_AREA_START_X = NODE_PANEL_WIDTH + 1; // Şekil alanının başlangıç sütunu
constexpr int SHAPE_AREA_WIDTH = SCREEN_COLS - SHAPE_AREA_START_X; // Şekil alanının genişliği

#endif

