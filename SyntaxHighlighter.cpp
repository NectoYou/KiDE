#include "SyntaxHighlighter.hpp"

SyntaxHighlighter::SyntaxHighlighter() {
    blue_keywords = {  
        "if", "else", "for", "while", "do", "return",
        "class", "struct", "public", "private", "using", "namespace",
        "include", "const", "true", "false" , "elseif"
    };
    green_keywords = {
        "int", "float", "double", "char", "void", "bool"
    };
    firebrick_keywords = {
        "main", "(", "{", "}", ")", "#" , "print" , "()" ,"def","in","is","len","raise",":"
    };
}

void SyntaxHighlighter::apply(nana::textbox& box) {
    box.set_highlight("blue_style", nana::colors::blue, nana::colors::white);
    for (const auto& word : blue_keywords) {
        box.set_keywords("blue_style", true, true, { word });
    }

    box.set_highlight("green_style", nana::colors::dark_green, nana::colors::white);
    for (const auto& word : green_keywords) {
        box.set_keywords("green_style", true, true, { word });
    }

    box.set_highlight("firebrick_style", nana::colors::firebrick, nana::colors::white);
    for (const auto& word : firebrick_keywords) {
        box.set_keywords("firebrick_style", true, true, { word });
    }
}