#include <general_ui.hpp>
#include <parser.hpp>

reflected_impl impl;
//GCThread gc;

int main() {
    fake_terminal::go(parser::parse);
}