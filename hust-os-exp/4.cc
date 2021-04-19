
#include <filesystem>
#include <rlib/stdio.hpp>
#include <rlib/opt.hpp>
#include "fs_prettyprint.hpp"

using namespace rlib::literals;
using namespace rlib::prettyprint;
namespace fs = std::filesystem;

void list_dir(const fs::path &dir, const size_t depth) {
    if(std::string(dir).find("/dev/fd/") == 0)
        return;
    for(const auto &entry : fs::directory_iterator(dir)) {
        rlib::printfln("{}{} {}", std::string(depth*2, ' '), entry.path(), entry);
        if(entry.is_directory())
            list_dir(entry, depth + 1);
    }
}

int main(int argc, char **argv) {
    rlib::opt_parser args(argc, argv);
    std::string path = args.getSubCommand();
    
    list_dir(path, 0);
}


