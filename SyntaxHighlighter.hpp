#pragma once
#include <nana/gui/widgets/textbox.hpp>
#include <vector>
#include <string>

class SyntaxHighlighter {
private:
    std::vector<std::string> blue_keywords;
    std::vector<std::string> green_keywords;
    std::vector<std::string> firebrick_keywords;

public:
    SyntaxHighlighter();
    void apply(nana::textbox& box);
};