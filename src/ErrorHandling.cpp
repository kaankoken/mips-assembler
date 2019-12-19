#include "ErrorHandling.h"

ErrorHandling::ErrorHandling() {};
ErrorHandling::~ErrorHandling() {};

//Checks the option and handles the errors if exist
bool ErrorHandling::optionChecker(std::string option) {
    if (option.length() > 1)
        return false;
    else {
        if (option.at(0) == ' ')
            return false;
    }
    return true;
}