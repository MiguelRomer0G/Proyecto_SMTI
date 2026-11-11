#ifndef EXCEPCIONES_SMTI_H
#define EXCEPCIONES_SMTI_H
#include <stdexcept>
#include <string>
class ErrorSMTI:public std::runtime_error {
public: explicit ErrorSMTI(const std::string& s):std::runtime_error(s){}
};
#endif
