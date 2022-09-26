//
// Created by ASUS on 2022/6/25.
//

#ifndef TYPE_H
#define TYPE_H
#include <iostream>
using namespace std;

enum Task_Type {
    USER_STORY,
    BUILD,
    TEST,
    DEBUG,
    DOC
};

inline ostream& operator<<(ostream& out, const Task_Type& t) {
    switch (t) {
        case USER_STORY: out << "User Story";break;
        case BUILD: out << "Building";break;
        case TEST: out << "Testing";break;
        case DEBUG: out << "Debugging";break;
        case DOC: out << "Documentation";break;
    }
    return out;
}
#endif //TYPE_H

