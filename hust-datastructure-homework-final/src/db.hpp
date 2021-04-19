#ifndef _HUST_DS_DB_HPP
#define _HUST_DS_DB_HPP 1

#include <person.hpp>
#include <nlohmann/json.hpp>
#include <rlib/class_decorator.hpp>
#include <fstream>

struct person_db : rlib::static_class {
    using json = nlohmann::json;

    static json r_set_to_json(const r::set<person_id> &buf) {
        json res;
        std::for_each(buf.cbegin(), buf.cend(), [&](const person_id &i){
            res.push_back(i);
        });
        return std::move(res);
    }

    static void save(/*const*/ r::set<person> &buffer, const std::string &file) {
        std::ofstream out(file);
        if(!out)
            throw std::invalid_argument(rlib::format_string("Failed to write to `{}`.", file));
        json result;
        for(const person &p : buffer) {
            result.push_back({
                {"id", p.id}, 
                {"friends", r_set_to_json(p.friends)}, 
                {"followers", r_set_to_json(p.followers)},
                {"followings", r_set_to_json(p.followings)}
            });
        }
        out << result << std::endl;
    }
    static void load(r::set<person> &buffer, const std::string &file, id_manager &id_manager1) {
        std::ifstream in(file);
        if(!in)
            throw std::invalid_argument(rlib::format_string("Failed to read from `{}`.", file));
        json content;
        in >> content;
        for(json &p_json : content) {
            person p(id_manager1, p_json["id"]);
            for(const person_id &i : p_json["friends"])
                p.friends.insert(i);
            for(const person_id &i : p_json["followers"])
                p.followers.insert(i);
            for(const person_id &i : p_json["followings"])
                p.followings.insert(i);
            buffer.insert(std::move(p)); 
        }
    }
};

#endif //_HUST_DS_DB_HPP
