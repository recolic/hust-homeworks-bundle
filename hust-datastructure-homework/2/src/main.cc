#include <general_ui.hpp>
#include <parser.hpp>

reflected_impl impl;

int main() {
    fake_terminal::go(parser::parse);
}