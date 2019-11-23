#include "ErrorHandling.h"

ErrorHandling::ErrorHandling() {};
ErrorHandling::~ErrorHandling() {};

bool ErrorHandling::optionChecker(std::string option) {
    if (option.length() > 1)
        return false;
    else {
        if (option.at(0) == ' ')
            return false;
    }
    return true;
}