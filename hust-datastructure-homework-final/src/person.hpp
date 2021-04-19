#ifndef RCPP_PERSON_HPP_
#define RCPP_PERSON_HPP_

#include <string>
#include <random>
#include <unordered_map>
#include <set.hpp>
using std::string;
using person_id = uint64_t;

struct person;

class id_manager : rlib::noncopyable {
public:
    id_manager() : randGen(std::random_device()()) {}
    person_id generate(const person *pp) {
        while(true) {
            person_id trial = randGen();
            if(id_pool.find(trial) == id_pool.end()) {
                id_pool[trial] = pp;
                return trial;
            }
        }
        throw std::runtime_error("Unknown error.");
    }
    const person *check_id(person_id id) const {
        auto pos = id_pool.find(id);
        if(pos == id_pool.cend())
            throw std::invalid_argument("Invalid id.");
        return pos->second;
    }
    void update(person_id id, const person *pp) {
        if(id_pool.find(id) != id_pool.end())
            id_pool[id] = pp;
        else
            throw std::invalid_argument("Invalid id to update.");
    }
    void assign(person_id id, const person *pp) {
        if(id_pool.find(id) == id_pool.end())
            id_pool[id] = pp;
        else
            throw std::invalid_argument("Id already used.");
    }
    void clear() {
        id_pool.clear();
    }
private:
    std::unordered_map<person_id, const person *> id_pool;
    std::mt19937_64 randGen;
};

struct person : public rlib::noncopyable {
    person() {}
    explicit person(id_manager &idgen) : id(idgen.generate(this)), pmanager(&idgen) {}
    explicit person(id_manager &idgen, person_id id) : id(id), pmanager(&idgen) {idgen.assign(id, this);}
    person(person &&another) {
        swap(std::move(another));
    }
    const person &operator=(person &&another) {
        swap(std::move(another));
        return *this;
    }

    bool operator==(const person &another) const {
        return id == another.id;
    }
    bool operator!=(const person &another) const {
        return ! operator==(another);
    }
    bool operator<(const person &another) const {
        return id < another.id;
    }
    bool operator>(const person &another) const {
        return ! ( operator<(another) || operator==(another) );
    }

    void show() const {
        rlib::println("Person", id);
        friends.show("Friends");
        followers.show("Followers");
        followings.show("Followings");
    }
    void swap(person &&another) {
        std::swap(pmanager, another.pmanager);
        std::swap(id, another.id);
        if(id) pmanager->update(id, this);
        if(another.id) pmanager->update(another.id, &another);

        friends.swap(another.friends);
        followers.swap(another.followers);
        followings.swap(another.followings);
    }

    person_id id = 0;
    id_manager *pmanager = nullptr;
    r::set<person_id> friends;
    r::set<person_id> followers;
    r::set<person_id> followings;
};

#endif
