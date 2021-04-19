#ifndef HUST___REFLECTED_IMPL_HPP_
#define HUST___REFLECTED_IMPL_HPP_

/*
 * You should NEVER use this code in ANY consequence,
 *     as these code is just to make hust happy.
 */

#include <utility>
#include <functional>
#include <algorithm>
#include <person.hpp>
#include <db.hpp>

#include <rlib/stdio.hpp>
#include <unordered_set>

using std::to_string;
using std::stoull;
using std::string;

__refl_class__ class reflected_impl : public rlib::nonmovable {
public:
    using stref = const string &;
    using id_t = person_id;

    __refl_func__ void save(stref fname) {
        person_db::save(buf, fname);
    }
    __refl_func__ void load(stref fname) {
        clear();
        person_db::load(buf, fname, id_manager1);
    }
    __refl_func__ void clear() {
        buf.clear();
        id_manager1.clear();
    }

    __refl_func__ string new_person() {
        auto iter = buf.insert(person(id_manager1));
        return to_string(iter->id);
    }
    __refl_func__ string new_person_at(stref id_to_assign) {
        auto iter = buf.insert(person(id_manager1, stoull(id_to_assign)));
        return to_string(iter->id);
    }
    __refl_func__ string rm_person(stref person_id) {
        const person *pp = id_manager1.check_id(stoull(person_id));
        buf.erase(buf.find(*pp));
        return person_id;
    }
    __refl_func__ void get(stref person_id) {
        id_manager1.check_id(stoull(person_id)) -> show();
    }
    __refl_func__ void ls() {
        rlib::println(buf.size(), "person:");
        std::for_each(buf.cbegin(), buf.cend(), [](const person &p){rlib::print(p.id, "");});
        rlib::println();
    }

    __refl_func__ string add(stref what, stref person_id, stref to_add_id) {
        person *pp = const_cast<person *>(id_manager1.check_id(stoull(person_id)));
        id_manager1.check_id(stoull(to_add_id));

#define OPERATION_(what_) pp->what_.insert(stoull(to_add_id));
        if(what == "friend") {
            OPERATION_(friends)
        }
        else if(what == "follower") {
            OPERATION_(followers)
        }
        else if(what == "following") {
            OPERATION_(followings)
        }
        else
            throw std::invalid_argument(rlib::format_string("Can not understand {}. Try `help`.", what));
#undef OPERATION_
        return rlib::format_string("{} -> {}", person_id, to_add_id);
    }

    __refl_func__ string rm(stref what, stref person_id, stref to_remove_id) {
        person *pp = const_cast<person *>(id_manager1.check_id(stoull(person_id)));
        id_manager1.check_id(stoull(to_remove_id));

#define OPERATION_(what_) pp->what_.erase(pp->what_.find(stoull(to_remove_id)));
        if(what == "friend") {
            OPERATION_(friends)
        }
        else if(what == "follower") {
            OPERATION_(followers)
        }
        else if(what == "following") {
            OPERATION_(followings)
        }
        else
            throw std::invalid_argument(rlib::format_string("Can not understand {}. Try `help`.", what));
#undef OPERATION_
        return rlib::format_string("{} -/> {}", person_id, to_remove_id);
    }

    __refl_func__ void common(stref what, stref person1_id, stref person2_id) {
        const person *pp1 = id_manager1.check_id(stoull(person1_id));
        const person *pp2 = id_manager1.check_id(stoull(person2_id));

#define OPERATION_(what_) (pp1->what_ ^ pp2->what_).show();
        if(what == "friend") {
            OPERATION_(friends)
        }
        else if(what == "follower") {
            OPERATION_(followers)
        }
        else if(what == "following") {
            OPERATION_(followings)
        }
        else
            throw std::invalid_argument(rlib::format_string("Can not understand {}. Try `help`.", what));
#undef OPERATION_
    }

    __refl_func__ void indirect(stref what, stref person_id) {
        std::unordered_set<id_t> buffer;
        const person *pp = id_manager1.check_id(stoull(person_id));

#define OPERATION_(what_) \
        std::for_each(pp->what_.cbegin(), pp->what_.cend(), [&buffer, self=this](const id_t &id){ \
            const person *pp = self->id_manager1.check_id(id); \
            std::for_each(pp->what_.cbegin(), pp->what_.cend(), [&buffer](const id_t &id){ \
                buffer.insert(id); \
            }); \
        }); \
        std::for_each(pp->what_.cbegin(), pp->what_.cend(), [&buffer](const id_t &id) { \
            buffer.erase(id); \
        }); \
        buffer.erase(pp->id);

        if(what == "friend") {
            OPERATION_(friends)
        }
        else if(what == "follower") {
            OPERATION_(followers)
        }
        else if(what == "following") {
            OPERATION_(followings)
        }
        else
            throw std::invalid_argument(rlib::format_string("Can not understand {}. Try `help`.", what));
#undef OPERATION_

        std::for_each(buffer.cbegin(), buffer.cend(), [&buffer](const id_t &id){
            rlib::print(id, "");
        });
        rlib::println();
    }

private:
    r::set<person> buf;
    id_manager id_manager1;
};

extern reflected_impl impl;

#endif
