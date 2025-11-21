/**
 * @file Persistence.cpp
 * @description JSON dosyasından veri okuma/yazma işlemlerini uygular.
 * @course 1C
 * @assignment 1. ÖDEV
 * @date 11.2025
 * @author Ayşe Verda Gülcemal ayse.gulcemal@ogr.sakarya.edu.tr
*/

#include "Persistence.hpp"

#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <cctype>

#include "Config.hpp"
#include "ControlList.hpp"
#include "ControlNode.hpp"
#include "ShapeNode.hpp"
#include "Triangle.hpp"
#include "Rectangle.hpp"
#include "Star.hpp"

// Bu dosya JSON dosyasından veri okuma/yazma işlemlerini uygular.
using namespace std;

namespace {

string trim(const string& str) {
    const char* whitespace = " \t\n\r";
    size_t start = str.find_first_not_of(whitespace);
    if (start == string::npos) {
        return "";
    }
    size_t end = str.find_last_not_of(whitespace);
    return str.substr(start, end - start + 1);
}

string extractStringValue(const string& line) {
    auto colonPos = line.find(':');
    if (colonPos == string::npos) return "";
    auto firstQuote = line.find('"', colonPos);
    auto secondQuote = line.find('"', firstQuote + 1);
    if (firstQuote == string::npos || secondQuote == string::npos) return "";
    return line.substr(firstQuote + 1, secondQuote - firstQuote - 1);
}

int extractIntValue(const string& line) {
    auto colonPos = line.find(':');
    if (colonPos == string::npos) return 0;
    string numberPart = trim(line.substr(colonPos + 1));
    string digits;
    for (char ch : numberPart) {
        if (isdigit(static_cast<unsigned char>(ch)) || ch == '-' || ch == '+') {
            digits.push_back(ch);
        } else if (!digits.empty()) {
            break;
        }
    }
    if (digits.empty()) {
        return 0;
    }
    try {
        return stoi(digits);
    } catch (...) {
        return 0;
    }
}

char extractCharValue(const string& line) {
    string value = extractStringValue(line);
    return value.empty() ? 'x' : value[0];
}

struct ShapeDraft {
    string type;
    int x = 0;
    int y = 0;
    int width = 0;
    int height = 0;
    int size = 0;
    int radius = 0;
    int z = 0;
    char ch = '#';
};

void resetDraft(ShapeDraft& draft) {
    draft = ShapeDraft();
}

bool draftReady(const ShapeDraft& draft) {
    return !draft.type.empty();
}

} // namespace

namespace Persistence {

// JSON içeriğini satır satır okuyup ControlList yapısını yeniden kurar.
bool loadFromJson(const string& path, ControlList& list, bool& isEmptyFile) {
    ifstream file(path);
    if (!file.is_open()) {
        isEmptyFile = false;
        return false;
    }

    list.clear();
    string line;
    ControlNode* currentNode = nullptr;
    ShapeDraft draft;
    bool anyNodeFound = false;

    while (getline(file, line)) {
        line = trim(line);
        if (line.find("\"id\"") != string::npos) {
            int nodeId = extractIntValue(line);
            currentNode = list.addNode(nodeId);
            anyNodeFound = true;
        } else if (line.find("\"type\"") != string::npos) {
            draft.type = extractStringValue(line);
        } else if (line.find("\"x\"") != string::npos) {
            draft.x = extractIntValue(line);
        } else if (line.find("\"y\"") != string::npos) {
            draft.y = extractIntValue(line);
        } else if (line.find("\"width\"") != string::npos) {
            draft.width = extractIntValue(line);
        } else if (line.find("\"height\"") != string::npos) {
            draft.height = extractIntValue(line);
        } else if (line.find("\"size\"") != string::npos) {
            draft.size = extractIntValue(line);
        } else if (line.find("\"radius\"") != string::npos) {
            draft.radius = extractIntValue(line);
        } else if (line.find("\"char\"") != string::npos) {
            draft.ch = extractCharValue(line);
        } else if (line.find("\"z\"") != string::npos) {
            draft.z = extractIntValue(line);

            if (currentNode && draftReady(draft)) {
                Shape* shape = nullptr;
                if (draft.type == "RECT") {
                    shape = new Rectangle(draft.x, draft.y, draft.width, draft.height, draft.ch, draft.z);
                } else if (draft.type == "TRI") {
                    shape = new Triangle(draft.x, draft.y, draft.size, draft.ch, draft.z);
                } else if (draft.type == "STAR") {
                    shape = new Star(draft.x, draft.y, draft.radius, draft.ch, draft.z);
                }

                if (shape) {
                    // Şekillerin sınırlar içinde kalmasını sağla (enforceBounds mantığı)
                    int x = shape->getX();
                    int y = shape->getY();
                    int newX = x;
                    int newY = y;
                    
                    // Rectangle için sınır kontrolü
                    Rectangle* rect = dynamic_cast<Rectangle*>(shape);
                    if (rect) {
                        int width = rect->getWidth();
                        int height = rect->getHeight();
                        if (newX < SHAPE_AREA_START_X) {
                            newX = SHAPE_AREA_START_X;
                        }
                        if (newX + width > SCREEN_COLS) {
                            newX = SCREEN_COLS - width;
                        }
                        if (newY < 0) {
                            newY = 0;
                        }
                        if (newY + height > SCREEN_ROWS) {
                            newY = SCREEN_ROWS - height;
                        }
                        shape->setPosition(newX, newY);
                    }
                    
                    // Triangle için sınır kontrolü
                    Triangle* tri = dynamic_cast<Triangle*>(shape);
                    if (tri) {
                        int height = tri->getHeight();
                        if (newX - (height - 1) < SHAPE_AREA_START_X) {
                            newX = SHAPE_AREA_START_X + (height - 1);
                        }
                        if (newX + (height - 1) >= SCREEN_COLS) {
                            newX = SCREEN_COLS - (height - 1) - 1;
                        }
                        if (newY < 0) {
                            newY = 0;
                        }
                        if (newY + height > SCREEN_ROWS) {
                            newY = SCREEN_ROWS - height;
                        }
                        shape->setPosition(newX, newY);
                    }
                    
                    // Star için sınır kontrolü
                    Star* star = dynamic_cast<Star*>(shape);
                    if (star) {
                        int radius = star->getRadius();
                        if (newX - radius < SHAPE_AREA_START_X) {
                            newX = SHAPE_AREA_START_X + radius;
                        }
                        if (newX + radius >= SCREEN_COLS) {
                            newX = SCREEN_COLS - radius - 1;
                        }
                        if (newY - radius < 0) {
                            newY = radius;
                        }
                        if (newY + radius >= SCREEN_ROWS) {
                            newY = SCREEN_ROWS - radius - 1;
                        }
                        shape->setPosition(newX, newY);
                    }
                    
                    currentNode->insertShapeSorted(shape);
                }
            }

            resetDraft(draft);
        }
    }

    if (!anyNodeFound) {
        isEmptyFile = true;
    } else {
        isEmptyFile = false;
    }

    return list.getCount() > 0;
}

// Mevcut listeyi JSON formatında dosyaya yazar.
bool saveToJson(const string& path, const ControlList& list) {
    ofstream file(path);
    if (!file.is_open()) {
        return false;
    }

    file << "{\n";
    file << "  \"nodes\": [\n";

    ControlNode* node = list.getHead();
    int nodeIndex = 0;
    while (node) {
        if (nodeIndex > 0) {
            file << ",\n";
        }
        file << "    {\n";
        file << "      \"id\": " << node->getId() << ",\n";
        file << "      \"shapes\": [\n";

        ShapeNode* shapeNode = node->getShapesHead();
        int shapeIndex = 0;
        while (shapeNode) {
            Shape* shape = shapeNode->getShape();
            if (shapeIndex > 0) {
                file << ",\n";
            }
            file << "        {\n";

            Rectangle* rect = dynamic_cast<Rectangle*>(shape);
            Triangle* tri = dynamic_cast<Triangle*>(shape);
            Star* star = dynamic_cast<Star*>(shape);

            if (rect) {
                file << "          \"type\": \"RECT\",\n";
                file << "          \"x\": " << rect->getX() << ",\n";
                file << "          \"y\": " << rect->getY() << ",\n";
                file << "          \"width\": " << rect->getWidth() << ",\n";
                file << "          \"height\": " << rect->getHeight() << ",\n";
            } else if (tri) {
                file << "          \"type\": \"TRI\",\n";
                file << "          \"x\": " << tri->getX() << ",\n";
                file << "          \"y\": " << tri->getY() << ",\n";
                file << "          \"size\": " << tri->getHeight() << ",\n";
            } else if (star) {
                file << "          \"type\": \"STAR\",\n";
                file << "          \"x\": " << star->getX() << ",\n";
                file << "          \"y\": " << star->getY() << ",\n";
                file << "          \"radius\": " << star->getRadius() << ",\n";
            }

            file << "          \"char\": \"" << shape->getChar() << "\",\n";
            file << "          \"z\": " << shape->getZ() << "\n";
            file << "        }";

            shapeNode = shapeNode->getNext();
            ++shapeIndex;
        }

        file << "\n      ]\n";
        file << "    }";

        node = node->getNext();
        ++nodeIndex;
    }

    file << "\n  ]\n";
    file << "}\n";

    return true;
}

} // namespace Persistence

