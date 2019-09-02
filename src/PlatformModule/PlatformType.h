#ifndef _PLATFORMTYPE_H
#define _PLATFORMTYPE_H

#include <iostream>

enum class PlatformType {
    CPU,
    CPU_TORCH,
    GPU,
    ASIC
};


inline std::ostream &operator<<(std::ostream &out, const PlatformType &type) {
    switch(type) {
        case PlatformType::CPU:
            out << "CPU";
        case PlatformType::CPU_TORCH:
            out << "CPU_TORCH";
        case PlatformType::GPU:
            out << "GPU";
        case PlatformType::ASIC:
            out << "ASIC";
    }
    return out;
}

#endif //_PLATFORMTYPE_H