/**
* @file main.cpp
* @description Programın ana kontrol döngüsünü ve kullanıcı girdisi yönetimini içerir.
* @course 1C
* @assignment 1. ÖDEV
* @date 11.2025
* @author Ayşe Verda Gülcemal ayse.gulcemal@ogr.sakarya.edu.tr
*/
#include <iostream>
#include <conio.h>
#include <string>
#include <algorithm>

#include "Config.hpp"
#include "ControlList.hpp"
#include "Screen.hpp"
#include "Persistence.hpp"
#include "RandomGenerator.hpp"
#include "ShapeNode.hpp"
#include "Shape.hpp"
#include "Triangle.hpp"
#include "Rectangle.hpp"
#include "Star.hpp"

// Bu dosya programın ana kontrol döngüsünü ve kullanıcı girdisi yönetimini içerir.

using namespace std;

namespace {

// Kullanıcıya hangi tuşların aktif olduğunu göstermek için basit bir yazdırma fonksiyonu.
void printMenu(bool shapeMode) {
    if (shapeMode) {
        cout << "\n(awsd) hareket  (q) onceki sekil  (e) sonraki sekil  (c) sekil sil  (g) listeye don\n";
    } else {
        cout << "\n[W/S] dugum gez | [F] sekillere gir | [C] dugumu sil | [Esc] cikis\n";
    }
}

// Screen::getBuffer() ile verilen tampon dizisine ID ve adet bilgilerini yazar.
void writeText(char** buffer, int row, int col, const string& text, int limitCol) {
    int available = max(0, limitCol - col); // Kullanılabilir sütun sayısını hesaplar
    for (size_t i = 0; i < text.size() && static_cast<int>(i) < available; ++i) {
        int targetCol = col + static_cast<int>(i); // Hedef sütunu hesaplar
        if (targetCol >= limitCol) {
            break; // Hedef sütun limitini aşarsa döngüyü sonlandırır
        }
        buffer[row][targetCol] = text[i]; // Hedef sütuna metni yazar
    }
}

// Tek yönlü listede geri gitmek için baştan itibaren önceki düğümü buluyoruz.
ShapeNode* getPrevShape(ControlNode* node, ShapeNode* current) {
    if (!node || !current || node->getShapesHead() == current) {
        return nullptr; // Node veya current null veya şekil zincirinin başına eşitse null döndürür
    }
    ShapeNode* iter = node->getShapesHead(); // Şekil zincirinin başından başlayarak geçer
    while (iter && iter->getNext() != current) {
        iter = iter->getNext(); // Sonraki şekil düğümüne geçer
    }
    return iter; // Sonraki şekil düğümünü döndürür veya null döndürür
}

// Sol taraftaki çift yönlü liste panelini çizer.
void drawNodePanel(Screen& screen, const ControlList& list, int offset) {
    char** buffer = screen.getBuffer(); // Ekran tamponunu alır
    int rows = screen.getRows(); // Ekran satır sayısını alır

    // temizle
    for (int r = 0; r < rows; ++r) { // Her satır için
        for (int c = 0; c < NODE_PANEL_WIDTH; ++c) { // Her sütun için
            buffer[r][c] = ' '; // Boş karakter yazar
        }
    }
    ControlNode* node = list.getHead(); // Baş düğümünü alır
    int skipped = 0; // Atlanan düğüm sayısını sıfırlar
    while (node && skipped < offset) { // Baş düğümü ve atlanan düğüm sayısı kontrol edilir
        node = node->getNext(); // Sonraki düğümü alır
        ++skipped; // Atlanan düğüm sayısını günceller
    }
    ControlNode* current = list.getCurrent(); // Şu anki düğümü alır
    int index = 0; // İndeksi sıfırlar
    while (node && index < NODE_PANEL_VISIBLE && (index * NODE_PANEL_STEP + 2) < rows) { // Baş düğümü ve indeks kontrol edilir ve alt sınırı hesaplar
        int top = index * NODE_PANEL_STEP; // Üst sınırı hesaplar
        int middle = top + 1; // Orta sınırı hesaplar
        int bottom = top + 2; // Alt sınırı hesaplar
        for (int c = 0; c < NODE_PANEL_WIDTH; ++c) { // Her sütun için
            buffer[top][c] = '*'; // Üst sınırı yazar
            buffer[bottom][c] = '*'; // Alt sınırı yazar
            buffer[middle][c] = (c == 0 || c == NODE_PANEL_WIDTH - 1) ? '*' : ' '; // Orta sınırı yazar
        }
        string idText = "ID " + to_string(node->getId()); // Düğüm ID'sini yazar
        string countText = "C " + to_string(node->getShapeCount()); // Şekil sayısını yazar
        writeText(buffer, middle, 2, idText, NODE_PANEL_WIDTH - 2);
        int countCol = NODE_PANEL_WIDTH - static_cast<int>(countText.size()) - 2; // Şekil sayısının sütun sayısını hesaplar
        countCol = max(2, countCol); // Şekil sayısının sütun sayısını günceller
        writeText(buffer, middle, countCol, countText, NODE_PANEL_WIDTH - 2); // Şekil sayısının sütun sayısını yazar

        if (node == current) {
            buffer[middle][1] = '>'; // Şu anki düğümü gösterir
            writeText(buffer, top, NODE_PANEL_WIDTH - 4, "<--", NODE_PANEL_WIDTH - 1); // Önceki düğümü gösterir
        }

        node = node->getNext(); // Sonraki düğümü alır
        ++index;
    }

    for (int r = 0; r < rows; ++r) { // Her satır için
        buffer[r][NODE_PANEL_WIDTH - 1] = '|';
    } // Sonraki düğümü gösterir
} // Düğüm panelini çizer

// Şekillerin sol paneli aşmaması ve ekran dışına çıkmaması için koordinatlarını sınırlar.
// Şeklin boyutlarını da hesaba katarak hiçbir kenarın taşmamasını sağlar.
void enforceBounds(Shape* shape) {
    if (!shape) return; // Şekil yoksa döndürür
    
    int x = shape->getX(); // Şeklin x eksenindeki konumunu alır
    int y = shape->getY(); // Şeklin y eksenindeki konumunu alır
    int newX = x; // Yeni x koordinatı
    int newY = y; // Yeni y koordinatı
    
    // Rectangle için sınır kontrolü
    Rectangle* rect = dynamic_cast<Rectangle*>(shape);
    if (rect) {
        int width = rect->getWidth(); // Dikdörtgenin genişliğini alır
        int height = rect->getHeight(); // Dikdörtgenin yüksekliğini alır
        
        // Sol sınır: SHAPE_AREA_START_X'den küçük olamaz
        if (newX < SHAPE_AREA_START_X) {
            newX = SHAPE_AREA_START_X; // X koordinatını sol sınıra ayarlar
        }
        // Sağ sınır: x + width, SCREEN_COLS'u aşamaz
        if (newX + width > SCREEN_COLS) {
            newX = SCREEN_COLS - width; // X koordinatını sağ sınıra ayarlar
        }
        // Üst sınır: 0'dan küçük olamaz
        if (newY < 0) {
            newY = 0; // Y koordinatını üst sınıra ayarlar
        }
        // Alt sınır: y + height, SCREEN_ROWS'u aşamaz
        if (newY + height > SCREEN_ROWS) {
            newY = SCREEN_ROWS - height; // Y koordinatını alt sınıra ayarlar
        }
        
        shape->setPosition(newX, newY); // Yeni konumu ayarlar
        return; // Dikdörtgen için işlem tamamlandı
    }
    
    // Triangle için sınır kontrolü
    Triangle* tri = dynamic_cast<Triangle*>(shape);
    if (tri) {
        int height = tri->getHeight(); // Üçgenin yüksekliğini alır
        int maxWidth = 2 * (height - 1) + 1; // Üçgenin en geniş kısmının genişliği
        
        // Sol sınır: x - (height-1), SHAPE_AREA_START_X'den küçük olamaz
        if (newX - (height - 1) < SHAPE_AREA_START_X) {
            newX = SHAPE_AREA_START_X + (height - 1); // X koordinatını sol sınıra ayarlar
        }
        // Sağ sınır: x + (height-1), SCREEN_COLS'u aşamaz
        if (newX + (height - 1) >= SCREEN_COLS) {
            newX = SCREEN_COLS - (height - 1) - 1; // X koordinatını sağ sınıra ayarlar
        }
        // Üst sınır: 0'dan küçük olamaz
        if (newY < 0) {
            newY = 0; // Y koordinatını üst sınıra ayarlar
        }
        // Alt sınır: y + height, SCREEN_ROWS'u aşamaz
        if (newY + height > SCREEN_ROWS) {
            newY = SCREEN_ROWS - height; // Y koordinatını alt sınıra ayarlar
        }
        
        shape->setPosition(newX, newY); // Yeni konumu ayarlar
        return; // Üçgen için işlem tamamlandı
    }
    
    // Star için sınır kontrolü
    Star* star = dynamic_cast<Star*>(shape);
    if (star) {
        int radius = star->getRadius(); // Yıldızın yarıçapını alır
        
        // Sol sınır: x - radius, SHAPE_AREA_START_X'den küçük olamaz
        if (newX - radius < SHAPE_AREA_START_X) {
            newX = SHAPE_AREA_START_X + radius; // X koordinatını sol sınıra ayarlar
        }
        // Sağ sınır: x + radius, SCREEN_COLS'u aşamaz
        if (newX + radius >= SCREEN_COLS) {
            newX = SCREEN_COLS - radius - 1; // X koordinatını sağ sınıra ayarlar
        }
        // Üst sınır: y - radius, 0'dan küçük olamaz
        if (newY - radius < 0) {
            newY = radius; // Y koordinatını üst sınıra ayarlar
        }
        // Alt sınır: y + radius, SCREEN_ROWS'u aşamaz
        if (newY + radius >= SCREEN_ROWS) {
            newY = SCREEN_ROWS - radius - 1; // Y koordinatını alt sınıra ayarlar
        }
        
        shape->setPosition(newX, newY); // Yeni konumu ayarlar
        return; // Yıldız için işlem tamamlandı
    }
}

} 

int main() { 
    RandomGenerator::seed(); // RNG'yi başlatır
    ControlList controlList;
    Screen screen(SCREEN_ROWS, SCREEN_COLS, ' '); // Ekran oluşturur

    cout << "1) Rastgele olustur\n2) Dosyadan oku\nSecim: ";
    int choice = 0; // Seçim için sıfırlar
    cin >> choice;

    string statusMessage; // Durum mesajı için sıfırlar

    if (choice == 2) {
        bool isEmptyFile = false; // Dosya boş mu kontrol eder
        if (!Persistence::loadFromJson("data/state.json", controlList, isEmptyFile)) {
            if (isEmptyFile) { // Dosya boşsa
                statusMessage = "Dosya bos, rastgele veri olusturuluyor.";
            } else { // Dosya boş değilse
                statusMessage = "Dosya okunamadi, rastgele veri olusturuluyor.";
            }
            RandomGenerator::populateRandomData(controlList); // Rastgele veri oluşturur
        } else {
            statusMessage = "Dosyadan okuma basarili."; // Dosyadan okuma başarılı
        }
    } else {
        RandomGenerator::populateRandomData(controlList);
        statusMessage = "Rastgele veri olusturuldu."; // Rastgele veri oluşturuldu  
    }

    bool running = true; // Çalışma durumunu kontrol eder
    bool shapeMode = false; // Şekil modunu kontrol eder
    ShapeNode* currentShape = nullptr;
    int panelOffset = 0; // Panel kaydırma ofsetini kontrol eder

    // Seçili düğüm ekran dışında kaldıysa panel kaydırma ofsetini güncelle.
    auto ensureCurrentVisible = [&](ControlNode* current) {
        int total = controlList.getCount(); // Toplam düğüm sayısını kontrol eder 
        int maxOffset = max(0, total - NODE_PANEL_VISIBLE); // Maksimum kaydırma ofsetini hesaplar
        if (panelOffset > maxOffset) panelOffset = maxOffset;
        if (panelOffset < 0) panelOffset = 0; // Kaydırma ofsetini 0'a ayarlar
        if (!current) return; // Şu anki düğüm yoksa döndürür
        ControlNode* node = controlList.getHead(); // Baş düğümünü alır
        int index = 0; // İndeksi sıfırlar
        while (node && node != current) {
            node = node->getNext(); // Sonraki düğümü alır
            ++index;
        }
        if (index < 0) return; // İndeks negatifse döndürür
        if (index < panelOffset) {
            panelOffset = index; // Panel kaydırma ofsetini günceller
        } else if (index >= panelOffset + NODE_PANEL_VISIBLE) {
            panelOffset = index - NODE_PANEL_VISIBLE + 1; // Panel kaydırma ofsetini günceller
        }
        maxOffset = max(0, controlList.getCount() - NODE_PANEL_VISIBLE);
        if (panelOffset > maxOffset) panelOffset = maxOffset; // Panel kaydırma ofsetini günceller
        if (panelOffset < 0) panelOffset = 0; // Panel kaydırma ofsetini 0'a ayarlar
    };
    ensureCurrentVisible(controlList.getCurrent()); // Şu anki düğümü gösterir

    while (running) { // Çalışma durumunu kontrol eder
        // Her döngüde ekranı tazeleyip sadece aktif düğümün şekillerini çiziyoruz.
        ControlNode* currentNode = controlList.getCurrent(); // Şu anki düğümü alır

        screen.clear(); // Ekranı temizler
        drawNodePanel(screen, controlList, panelOffset); // Düğüm panelini çizer
        if (currentNode) {
            ShapeNode* sNode = currentNode->getShapesHead(); // Şekil zincirinin başından başlayarak geçer
            while (sNode) {
                Shape* shape = sNode->getShape();
                if (shape) screen.drawShape(*shape); // Şekili çizer
                sNode = sNode->getNext();
            }
        }
        screen.renderToConsole(); // Ekranı konsola yazdırır    
        if (!statusMessage.empty()) {
            cout << statusMessage << '\n'; // Durum mesajını yazdırır
        }

        if (currentNode) {
            cout << "Aktif dugum ID: " << currentNode->getId() // Şu anki düğümün ID'sini yazdırır
                      << " | Sekil sayisi: " << currentNode->getShapeCount() << "\n"; // Şekil sayısını yazdırır
        } else {
            cout << "Listede hic dugum yok.\n"; // Listede hiç düğüm yoksa mesaj yazdırır
        }

        printMenu(shapeMode); // Menüyü yazdırır
        int key = _getch(); // Tuşa basılınca tuş kodunu alır   

        if (!shapeMode) {
            switch (key) { // Tuşa göre işlem yapar
                case 'w':
                case 'W':
                    controlList.movePrev(); // Önceki düğümü alır
                    ensureCurrentVisible(controlList.getCurrent());
                    break; // Önceki düğümü gösterir
                case 's':
                case 'S':
                    controlList.moveNext(); // Sonraki düğümü alır
                    ensureCurrentVisible(controlList.getCurrent());
                    break; // Sonraki düğümü gösterir
                case 'f':
                case 'F':
                    currentNode = controlList.getCurrent(); // Şu anki düğümü alır
                    if (currentNode && currentNode->getShapesHead()) {
                        shapeMode = true; // Şekil modunu açar
                        currentShape = currentNode->getShapesHead();
                    }
                    break; // Şekil modunu açar
                case 'c':
                case 'C':
                    if (controlList.removeCurrentNode()) {
                        currentShape = nullptr; // Şekil modunu kapatır
                        if (!controlList.getCurrent()) {
                            shapeMode = false; // Şekil modunu kapatır
                        }
                    }
                    ensureCurrentVisible(controlList.getCurrent());
                    break; // Şekil modunu kapatır
                case 27: // ESC
                    running = false;
                    break; // Çalışma durumunu kapatır
                default:
                    break;
            }
        } else {
            currentNode = controlList.getCurrent(); // Şu anki düğümü alır  
            if (!currentNode) {
                shapeMode = false; // Şekil modunu kapatır
                continue; // Çalışma durumunu kapatır
            }
            switch (key) {
                case 'e': // Sonraki şekil
                case 'E':
                    if (currentShape && currentShape->getNext()) {
                        currentShape = currentShape->getNext(); // Sonraki şekil
                    }
                    break; // Sonraki şekil
                case 'q': // Önceki şekil
                case 'Q': {
                    ShapeNode* prev = getPrevShape(currentNode, currentShape);
                    if (prev) {
                        currentShape = prev; // Önceki şekil
                    }
                    break; // Önceki şekil
                }
                case 'a': // sola hareket
                case 'A':
                    if (currentShape) {
                        currentShape->getShape()->move(-1, 0); // sola hareket
                        enforceBounds(currentShape->getShape());
                    }
                    break; // sola hareket
                case 'd': // sağa hareket
                case 'D':
                    if (currentShape) {
                        currentShape->getShape()->move(1, 0); // sağa hareket
                        enforceBounds(currentShape->getShape());
                    }
                    break; // sağa hareket
                case 's': // aşağı hareket
                case 'S':
                    if (currentShape) {
                        currentShape->getShape()->move(0, 1); // aşağı hareket
                        enforceBounds(currentShape->getShape());
                    }
                    break; // aşağı hareket
                case 'w': // yukarı hareket
                case 'W':
                    if (currentShape) {
                        currentShape->getShape()->move(0, -1); // yukarı hareket
                        enforceBounds(currentShape->getShape());
                    }
                    break; // yukarı hareket
                case 'c': // şekli sil
                case 'C':
                    if (currentShape) {
                        ShapeNode* nextNode = currentShape->getNext(); // Sonraki şekil
                        ShapeNode* prevNode = getPrevShape(currentNode, currentShape); // Önceki şekil
                        Shape* shapePtr = currentShape->getShape();
                        if (currentNode->removeShape(shapePtr)) {
                            if (nextNode) {
                                currentShape = nextNode; // Sonraki şekil
                            } else if (prevNode) {
                                currentShape = prevNode; // Önceki şekil
                            } else {
                                currentShape = nullptr; // Şekil modunu kapatır  
                                shapeMode = false; // Şekil modunu kapatır  
                                controlList.removeCurrentNode(); // Şu anki düğümü siler
                                ensureCurrentVisible(controlList.getCurrent()); // Şu anki düğümü gösterir
                            }
                        }
                    }
                    break; // şekli sil
                case 'g':
                case 'G':
                    shapeMode = false; // Şekil modunu kapatır
                    currentShape = nullptr; // Şekil modunu kapatır
                    break;
                default:
                    break; // Çalışma durumunu kapatır
            }
        }
    }

    Persistence::saveToJson("data/state.json", controlList); // Durum kaydedildi
    cout << "Cikis yapildi, durum kaydedildi.\n"; // Çıkış yapıldı, durum kaydedildi mesajı yazdırır
    return 0; // Programı sonlandırır
}

