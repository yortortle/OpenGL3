#include <iostream>
#include <utility>

#define LOG(...) std::cout , __VA_ARGS__ , std::endl

template <typename T>
std::ostream& operator,(std::ostream& out, const T& t) {
    out << t;
    return out;
}

std::ostream& operator,(std::ostream& out, std::ostream& (*f)(std::ostream&)) {
    out << f;
    return out;
}

//void log() {}
//
//template<typename First, typename ...Rest>
//void log(First&& first, Rest && ...rest)
//{
//    std::cout << std::forward<First>(first);
//    log(std::forward<Rest>(rest)...);
//}