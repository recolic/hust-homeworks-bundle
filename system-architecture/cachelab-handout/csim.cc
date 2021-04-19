#include <rlib/stdio.hpp>
#include <rlib/opt.hpp>
#include <fstream>
using namespace rlib::literals;

using addr_t = uint64_t;
constexpr addr_t INVALID_ADDR = (addr_t)-1;
struct cache_line_t {
    addr_t addr = INVALID_ADDR; uint64_t time;
}; // cache line contains ANY ONE addr, which lies in this cacheline.
using cache_set_t = std::vector<cache_line_t>; // E cache lines in every cache set.
using cache_t = std::vector<cache_set_t>; // 2^s cache sets.

cache_t cache;
uint64_t wall_time = 0;
auto hit_counter = 0, miss_counter = 0, evict_counter = 0;

int main(int argc, char **argv) {
    rlib::opt_parser args(argc, argv);
    
    // Prepare parameters. //////////////////////////////////////////////
    if(args.getBoolArg("-h")) {
        rlib::println("Sorry, no help message provided.");
        return 1;
    }
    auto fname = args.getValueArg("-t");
    auto s = args.getValueArg("-s").as<size_t>();
    auto E = args.getValueArg("-E").as<size_t>();
    auto b = args.getValueArg("-b").as<size_t>();
    auto verbose = args.getBoolArg("-v");

    cache.resize(1 << s); // 2^s cache sets.
    for(auto &cache_set : cache) cache_set.resize(E); // E cache lines in every cache set.

    // Actual implementation. //////////////////////////////////////////
    auto is_addr_match = [&](addr_t l, addr_t r) {
        return (l xor r) >> b == 0;
    };
    auto process_query = [&](addr_t addr) {
        // Return 'H' for Hit, 'M' for miss, 'E' for miss+eviction.
        ++wall_time;
        auto &my_cache_set = cache[(addr >> b) % cache.size()];
        auto *cache_line_to_evict = &my_cache_set[0];
        for(auto &cache_line : my_cache_set) {
            if(is_addr_match(cache_line.addr, addr)) {
                cache_line.time = wall_time;
                return 'H'; // Cache hit.
            }
            if(cache_line.time < cache_line_to_evict->time)
                cache_line_to_evict = &cache_line;
        }

        // Cache miss.
        auto returnVal = cache_line_to_evict->addr == INVALID_ADDR ? 'M' : 'E';
        cache_line_to_evict->addr = addr;
        cache_line_to_evict->time = wall_time;
        return returnVal;
    };
    auto update_counters = [&](char res) {
        if(verbose)
            rlib::println(res);
        switch(res) {
            case 'H':
                ++hit_counter;
                return;
            case 'E':
                ++evict_counter;
            case 'M':
                ++miss_counter;
                return;
        }
    };
    auto parse_line = [](const auto &line) -> std::pair<char, addr_t> {
        auto op = line[1];
        if(op == ' ') return std::make_pair('I', 0); // 'I' operation.
        auto addr_and_size = line.substr(3);
        auto pos = addr_and_size.find(',');
        if(pos == std::string::npos)
            throw std::invalid_argument(line);
        return std::make_pair(op, std::stoull(addr_and_size.substr(0, pos), 0, 16));
    };

    // Main loop here. ////////////////////////////////////////////
    auto finput = std::ifstream(fname);
    while(true) {
        auto line = rlib::scanln(finput);
        if(finput.eof()) break;
        auto [op, addr] = parse_line(line);
        switch(op) {
            case 'I':
                break;
            case 'M':
                update_counters(process_query(addr));
                [[fallthrough]];
            case 'L':
            case 'S':
                update_counters(process_query(addr));
                break;
            default:
                throw std::invalid_argument("Unknown op.");
        }
    }

    // Results.
    rlib::println("hits:{} misses:{} evictions:{}"_format(hit_counter, miss_counter, evict_counter));
    std::ofstream(".csim_results", std::ios::trunc) << "{} {} {}\n"_format(hit_counter, miss_counter, evict_counter);
}
