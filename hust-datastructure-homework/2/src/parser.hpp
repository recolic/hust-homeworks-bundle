#ifndef _HUST___PARSER_HPP
#define _HUST___PARSER_HPP 1

#include <reflected_impl.hpp>
#include <list>
#include <string>
#include <iomanip>

#include <rlib/stdio.hpp>
#include <rlib/terminal.hpp>
using namespace rlib::terminal;

class parser {
private:
    static std::string getArg(const std::list<std::string> &ls, size_t n) {
        auto iter = ls.cbegin();
        for(size_t cter = 0; cter < n; ++cter) {
            ++iter;
        }
        return std::move(*iter);
    }
    static void help_msg() {
        std::string msg = R"_STR_(
rfaketerm 0.0 _ specially edition

Usage: <Command> [args ...]

Command List:

help : Show this message.
exit : exit politely.

InitList
DestroyList
ClearList
ListEmpty
ListLength
GetElem <size_t positionPlusOne>
LocateElem <data_t elemValue>
PriorElem <data_t elemValue>
NextElem <data_t elemValue>
ListInsert <size_t positionPlusOne> <data_t elemValue>
ListDelete <size_t positionPlusOne>
ListTraverse
)_STR_";
        rlib::io::println(msg);
    }
public:
    static void parse(const std::list<std::string> &to_parse) {
        if(to_parse.empty())
            return;
        rlib::io::print(std::boolalpha);

#define IFCMD(str) if(*to_parse.begin() == str)
#define WANT_ARG(n) if(to_parse.size() != n+1) {rlib::io::println(color_t::red, font_t::bold, "Error:", clear, color_t::lightgray, n, "arguments wanted but", to_parse.size()-1, "provided.", clear); return;}
#define SIZE_ARG(n) std::stoul(getArg(to_parse, n))
#define DATA_ARG(n) std::stoi(getArg(to_parse, n))
#define HAVE_RETURN_VALUE auto ret =
#define PRINT_RETURN_VALUE rlib::io::println(ret);

        IFCMD("InitList") {
            WANT_ARG(0)
            impl.InitList();
        }
        IFCMD("DestroyList") {
            WANT_ARG(0)
            impl.DestroyList();
        }
        IFCMD("ClearList") {
            WANT_ARG(0)
            impl.ClearList();
        }
        IFCMD("ListEmpty") {
            WANT_ARG(0)
            HAVE_RETURN_VALUE
            impl.ListEmpty();
            PRINT_RETURN_VALUE
        }
        IFCMD("ListLength") {
            WANT_ARG(0)
            HAVE_RETURN_VALUE
            impl.ListLength();
            PRINT_RETURN_VALUE
        }
        IFCMD("GetElem") {
            WANT_ARG(1)
            HAVE_RETURN_VALUE
            impl.GetElem(SIZE_ARG(1));
            PRINT_RETURN_VALUE
        }
        IFCMD("LocateElem") {
            WANT_ARG(1)
            HAVE_RETURN_VALUE
            impl.LocateElem(DATA_ARG(1));
            PRINT_RETURN_VALUE
        }
        IFCMD("PriorElem") {
            WANT_ARG(1)
            HAVE_RETURN_VALUE
            impl.PriorElem(DATA_ARG(1));
            PRINT_RETURN_VALUE
        }
        IFCMD("NextElem") {
            WANT_ARG(1)
            HAVE_RETURN_VALUE
            impl.NextElem(DATA_ARG(1));
            PRINT_RETURN_VALUE
        }
        IFCMD("ListInsert") {
            WANT_ARG(2)
            impl.ListInsert(SIZE_ARG(1), DATA_ARG(2));
        }
        IFCMD("ListDelete") {
            WANT_ARG(1)
            HAVE_RETURN_VALUE
            impl.ListDelete(SIZE_ARG(1));
            PRINT_RETURN_VALUE
        }
        IFCMD("ListTraverse") {
            WANT_ARG(0)
            impl.ListTraverse();
        }
        // _s done.
        IFCMD("exit") {
            rlib::io::println("bye~");
            ::std::exit(0);
        }
        IFCMD("help") {
            help_msg();
        }
        //impl.debug();
    }
};

#endif //_HUST___PARSER_HPP
