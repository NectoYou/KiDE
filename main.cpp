#include <nana/gui.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <nana/gui/widgets/menubar.hpp>
#include <nana/gui/filebox.hpp>
#include <fstream>
#include <sstream>
#include <vector> 
#include <cstdlib>
#include <iostream> 
#include "SyntaxHighlighter.hpp" 
#include "CodeRunner.hpp"


int main()
{
    using namespace nana;

    form fm(API::make_center(800, 600));
    fm.caption("KiDE");

    menubar mbar(fm);
    textbox code_input(fm);

    SyntaxHighlighter highlighter;
    CodeRunner runner;

    auto &file_menu = mbar.push_back("Файл");

     file_menu.append("Открыть файл", [&fm, &code_input, &highlighter](menu::item_proxy& ip) {
        filebox fbox(fm, true); 
        fbox.title("Открыть исходный код");
        fbox.add_filter("C++ файлы (*.cpp;*.h)", "*.cpp;*.h");
        fbox.add_filter("Python скрипты (*.py)", "*.py");
        fbox.add_filter("lua скрипты (*.lua)", "*.lua");
        fbox.add_filter("html скрипты (*.html)", "*.html");
        fbox.add_filter("js скрипты (*.js)", "*.js");
        fbox.add_filter("Текстовые файлы (*.txt)", "*.txt");
        fbox.add_filter("Все файлы (*.*)", "*.*");

        auto files = fbox.show();
        if (!files.empty()) {
            std::filesystem::path file_path = files.front();
            
            std::ifstream in(file_path, std::ios::in | std::ios::binary);
            if (in.is_open()) {
                std::stringstream buffer;
                buffer << in.rdbuf();
                code_input.caption(buffer.str()); 
                in.close();
                
                highlighter.apply(code_input);
            }
        }
    });

    file_menu.append("Сохранить", [&fm, &code_input](menu::item_proxy& ip) {
        filebox fbox(fm, false); 
        fbox.title("Сохранить исходный код");
        fbox.add_filter("C++ файлы (*.cpp;*.h)", "*.cpp;*.h");
        fbox.add_filter("Python скрипты (*.py)", "*.py");
        fbox.add_filter("lua скрипты (*.lua)", "*.lua");
        fbox.add_filter("html скрипты (*.html)", "*.html");
        fbox.add_filter("js скрипты (*.js)", "*.js");
        fbox.add_filter("Текстовые файлы (*.txt)", "*.txt");
        fbox.add_filter("Все файлы (*.*)", "*.*");

        auto files = fbox.show();
        if (!files.empty()) {
            std::filesystem::path file_path = files.front();

            std::ofstream out(file_path, std::ios::out | std::ios::binary);
            if (out.is_open()) {
                std::string content = code_input.text();
                out.write(content.c_str(), content.size());
                out.close();
            }
        }
    });

    file_menu.append_splitter();
    file_menu.append("Выход", [&fm](menu::item_proxy& ip) {
        fm.close(); 
    });

    auto &help_menu = mbar.push_back("Справка");
    help_menu.append("О программе");

    auto &build_menu = mbar.push_back("Сборка");
    build_menu.append("Запустить код", [&code_input, &runner](nana::menu::item_proxy& ip) {
        runner.run(code_input); 
    });


    code_input.multi_lines(true);       
    code_input.indention(true);         

    paint::font code_font("Consolas", 12);
    code_input.typeface(code_font);
        highlighter.apply(code_input);
        code_input.events().text_changed([&code_input, &highlighter]() {
        highlighter.apply(code_input);
    });

  
    fm.div("vertical <weight=28 mbar> <code_field>");
    fm["mbar"] << mbar;
    fm["code_field"] << code_input;
    fm.collocate(); 

    fm.show();
    exec();



}
