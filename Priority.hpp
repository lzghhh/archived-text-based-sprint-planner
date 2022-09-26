//
// Created by ASUS on 2022/6/25.
//

#ifndef PRIORITY_H
#define PRIORITY_H
enum Priority {
    LOW = 1,
    MID = 2,
    HIGH = 3
};

inline ostream& operator<<(ostream& out, const Priority& p) {
    switch (p) {
        case LOW: out << "Low";break;
        case MID: out << "Mid";break;
        case HIGH: out << "High";break;
    }
    return out;
}
#endif //PRIORITY_H

