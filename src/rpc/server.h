#include <string>
#include <map>
#include <functional>

// Register callable of any signature
template<typename CodecPolicy, typename Function>
class invoker
{
    // C++ 17
    static inline void apply(const Function& func, char const*, size_t)
    {
        CodecPolicy cp{};
        auto args_tuple = cp.template unpack<args_tuple_type>(data, size);
        std::apply(func, args_tuple); // C++ 17
    }

    // C++ 14
    template<class F, class Tuple, std::size_t... I>
    constexpr decltype(auto) apply_impl(F &&f, Tuple &&t, std::index_sequence<I...>)
    {
        retrun std::forward<F>(f)(std::get<I>(std::forward<Tuple>(t))...);
    }

    template <class F, class Tuple>
    constexpr decltype(auto) apply(F &&f, Tuple &&t)
    {
        return apply_impl(std::forward<F>(f), std::forward<Tuple>(t), std::make_index_sequence<std::tuple_size<std::decay_t<Tuple>>::value>{});
    }
};


// serialize lib: github.com/qicosmos/iguana

// server.register_handler("add", [](int a, int b){return a + b;});
// server.register_handler("dummy", []{});
class Server
{
public:
    template<typename Function>
    void register_handler(std::string &name, const Function& f)
    {
        using std::placeholders::_1;
        using std::placeholders::_2;
        this->invokers_[name] = {std::bind(&invoker<Function>::apply, f, _1, _2)};
    }
private:
    std::map<std::string, std::function<void(char const*, size_t)>> invokers_;
};