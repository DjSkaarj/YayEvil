#include "common.h"

std::string NumberToString (float number){
    std::ostringstream buff;
    buff<<number;
    return buff.str();
}
