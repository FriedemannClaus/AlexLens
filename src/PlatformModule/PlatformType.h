#ifndef _PLATFORMTYPE_H
#define _PLATFORMTYPE_H

#include <iostream>

enum class PlatformType {
    CPU,
    ASIC
};


inline std::ostream &operator<<(std::ostream &out, const PlatformType &type) {
    switch(type) {
        case PlatformType::CPU:
            out << "CPU";
        case PlatformType::ASIC:
            out << "ASIC";
    }
    return out;
}

#endif //_PLATFORMTYPE_H