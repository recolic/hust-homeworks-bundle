#ifndef R_SET_
#define R_SET_

#include <avl.hpp>
#include <algorithm>

namespace r
{
    template<typename T, bool __multi = false, typename _equal_func = std::equal_to<T>, typename _less_func = std::less<T>>
    class set : public avl::tree<T, __multi, _equal_func, _less_func>
    {
    public:
        using this_type = set<T, __multi>;
        using base_type = avl::tree<T, __multi, _equal_func, _less_func>;

        this_type operator^(const this_type &another) const noexcept
        {
            this_type result;
            auto curr_a = base_type::cbegin();
            auto curr_b = another.cbegin();
            static auto is_less = _less_func();
            static auto is_equal = _equal_func();

            while (curr_a && curr_b)
            {
                if (is_equal(*curr_a, *curr_b))
                {
                    if (!__multi)
                        result.insert(*curr_a);
                    else
                    {
                        size_t shift_time = base_type::count(*curr_a);
                        size_t insert_time = std::min(shift_time, another.count(*curr_a));
                        for (size_t cter = 0; cter < insert_time; ++cter)
                            result.insert(*curr_a);
                        for (size_t cter = 1; cter < shift_time; ++cter)
                            ++curr_a;
                    }
                    ++curr_a;
                    ++curr_b;
                    continue;
                }
                if (is_less(*curr_a, *curr_b))
                    ++curr_a;
                else
                    ++curr_b;
            }
            return std::move(result);
        }

        this_type operator+(const this_type &another) const noexcept
        {
            this_type result;
            for (auto iter = base_type::cbegin(); iter; ++iter)
            {
                result.insert(*iter, true);
            }
            for (auto iter = another.cbegin(); iter; ++iter)
            {
                result.insert(*iter, true);
            }
            return std::move(result);
        }

        this_type operator-(const this_type &another) const noexcept
        {
            this_type result;
            for (auto iter = base_type::cbegin(); iter; ++iter)
            {
                if (!__multi)
                {
                    if (!another.exist(*iter))
                        result.insert(*iter);
                } else
                {
                    size_t shift_time = base_type::count(*iter);
                    int insert_time = shift_time - another.count(*iter);
                    for (int cter = 0; cter < insert_time; ++cter)
                        result.insert(*iter);
                    for (size_t cter = 1; cter < shift_time; ++cter)
                        ++iter;
                }
            }
            return std::move(result);
        }

        this_type clone() const noexcept
        {
            this_type result;
            std::for_each(base_type::cbegin(), base_type::cend(), [&result](const T &dat) { result.insert(dat); });
            return std::move(result);
        }

        bool operator==(const this_type &another) const noexcept
        {
            if (base_type::size() != another.size())
                return false;
            for (auto itera = base_type::cbegin(), iterb = another.cbegin(); itera && iterb; ++itera, ++iterb)
            {
                if (!_equal_func()(*itera, *iterb))
                    return false;
            }
            return true;
        }

        bool operator!=(const this_type &another) const noexcept
        {
            return !operator==(another);
        }

        bool contain(const this_type &another) const noexcept
        {
            for (auto iter = another.cbegin(); iter; ++iter)
            {
                if (base_type::count(*iter) < another.count(*iter)) //Warning: Unnecessary `another.count` is O(log(n)) slow.
                    return false;
            }
            return true;
        }

        void show(const std::string &name) const noexcept
        {
            rlib::printf("{}: ", name);
            show();
        }
        void show() const noexcept
        {
            std::for_each(base_type::cbegin(), base_type::cend(), [](const int &i) { rlib::print(i, ""); });
            rlib::println();
        }
        constexpr const this_type &crange() const noexcept {
            return *this;
        }
    };

    template<typename T, typename _equal_func = std::equal_to<T>, typename _less_func = std::less<T>>
    class multiset : public set<T, true, _equal_func, _less_func>
    {};

}
#endif
