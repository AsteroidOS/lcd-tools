#ifndef FEATURE_H
#define FEATURE_H
#include <string_view>
#include <CLI/CLI.hpp>

struct Feature {
    std::string_view flag;
    std::string_view description;
};

// C++20 fixed_string NTTP
template <std::size_t N>
struct fixed_string {
    char v[N];

    constexpr fixed_string(char const (&str)[N]) {
        for (std::size_t i = 0; i < N; ++i) v[i] = str[i];
    }
    constexpr std::string_view view() const { return {v, N - 1}; }
};

struct IWatch {
    static CLI::App app;
    virtual int run(int argc, char* argv[]) {
        try {
            app.parse(argc, argv);
        } catch (const CLI::ParseError &e) {
            return app.exit(e);
        }
        return 0;
    }
    virtual ~IWatch() = default;
};

template <fixed_string Flag, fixed_string Desc>
struct NamedFeature : Feature {
    template <class Invokable>
    NamedFeature(Invokable&& inv)
        : Feature{Flag.view(), Desc.view()}
    {
        register_feature(flag, description, std::forward<Invokable>(inv));
    }

    template <class InvokableT>
    static void register_feature(std::string_view f,
                                  std::string_view d,
                                  InvokableT&& inv)
    {
        // CLI11 expects a callback with signature: void(void)
        std::function<void()> cb{std::forward<InvokableT>(inv)};

        IWatch::app.add_flag_callback(std::string(f), std::move(cb), std::string(d));
    }
};
#endif /* FEATURE_H */
