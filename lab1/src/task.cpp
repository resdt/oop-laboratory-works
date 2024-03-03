#include "task.h"

std::string& removeVowelsByRef(std::string& str) {
    const std::string vowels = "aeiouyAEIOUY";
    size_t i = 0;
    while (i < str.length()) {
        if (vowels.find(str[i]) != std::string::npos)
            str.erase(str.begin() + i);
        else
            i++;
    }
    return str;
}

std::string removeVowels(const std::string& str) {
    const std::string vowels = "aeiouyAEIOUY";
    std::string new_str;
    for (size_t i = 0; i < str.length(); ++i)
        if (vowels.find(str[i]) == std::string::npos)
            new_str += str[i];
    return new_str;
}