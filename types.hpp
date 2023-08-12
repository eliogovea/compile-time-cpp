#include <cstdlib>
#include <type_traits>

namespace types {

/// @brief List of types
/// @tparam ...Ts
template <typename... Ts>
struct list {};

/// @brief Check if T is a `list`
/// @tparam T
template <typename T>
struct is_list : public std::false_type {};

template <typename... Ts>
struct is_list<list<Ts...>> : public std::true_type {};

template <typename T>
inline constexpr bool is_list_v = is_list<T>::value;

/// @brief Count types in a list
/// @tparam List List of types
template <typename List>
struct count : public std::integral_constant<std::size_t, 0> {};

template <typename... Ts>
struct count<list<Ts...>>
    : public std::integral_constant<std::size_t, sizeof...(Ts)> {};

template <typename List>
inline constexpr std::size_t count_v = count<List>::value;

/// @brief Push `T` to the end of `List`
/// @tparam List List of types
/// @tparam T Type to add to the end of list
template <typename List, typename T>
struct push;

template <typename List, typename T>
using push_t = typename push<List, T>::type;

template <typename T, typename... ListTs>
struct push<list<ListTs...>, T> {
  using type = list<ListTs..., T>;
};

/// @brief Create a new list with the types of
/// `ListL` and `ListR`
/// @tparam ListR List of types
/// @tparam ListL List of types
template <typename ListL, typename ListR>
struct extend;

template <typename ListL, typename ListR>
using extend_t = typename extend<ListL, ListR>::type;

template <typename ListL>
struct extend<ListL, list<>> {
  using type = ListL;
};

template <typename ListL, typename ListRT, typename... ListRTs>
struct extend<ListL, list<ListRT, ListRTs...>> {
  using type = extend_t<push_t<ListL, ListRT>, list<ListRTs...>>;
};

/// @brief Reverse types in `List`.
/// Example: reverse<list<int, double>>::type is list<double, int>
/// @tparam List List of types
template <typename List>
struct reverse;

template <typename List>
using reverse_t = typename reverse<List>::type;

template <>
struct reverse<list<>> {
  using type = list<>;
};

template <typename T, typename... Ts>
struct reverse<list<T, Ts...>> {
  using type = push_t<reverse_t<list<Ts...>>, T>;
};

/// @brief Type from `List` at `Index`
/// @tparam List List of types
/// @tparam Index
template <typename List, std::size_t Index>
struct at;

template <typename T, typename... Ts>
struct at<list<T, Ts...>, std::size_t{0}> {
  using type = T;
};

template <std::size_t Index, typename T, typename... Ts>
struct at<list<T, Ts...>, Index> {
  using type = typename at<list<Ts...>, Index - 1>::type;
};

template <typename List, std::size_t Index>
using at_t = typename at<List, Index>::type;

/// @brief Filter `List` using `Predicate`
/// @tparam List List of types
template <typename List, template <typename> class Predicate>
struct filter;

template <typename List, template <typename> class Predicate>
using filter_t = typename filter<List, Predicate>::type;

template <template <typename> class Predicate>
struct filter<list<>, Predicate> {
  using type = list<>;
};

template <typename T, template <typename> class Predicate>
struct filter<list<T>, Predicate> {
  using type = std::conditional_t<Predicate<T>::value, list<T>, list<>>;
};

template <template <typename> class Predicate, typename T, typename... Ts>
struct filter<list<T, Ts...>, Predicate> {
  using type =
      extend_t<filter_t<list<T>, Predicate>, filter_t<list<Ts...>, Predicate>>;
};

/// @brief Transform `List` using `Operation`
/// @tparam List List of types
template <typename List, template <typename> class Operation>
struct transform;

template <typename List, template <typename> class Operation>
using transform_t = typename transform<List, Operation>::type;

template <template <typename> class Operation>
struct transform<list<>, Operation> {
  using type = list<>;
};

template <template <typename> class Operation, typename T, typename... Ts>
struct transform<list<T, Ts...>, Operation> {
  using type = typename extend<list<typename Operation<T>::type>,
                               transform_t<list<Ts...>, Operation>>::type;
};

/// @brief `List' prefix of size std::min(N, count_v<List>)
/// @tparam List List of types
/// @tparam N Preifx size
template <typename List, std::size_t N>
struct prefix;

template <typename List, std::size_t N>
using prefix_t = typename prefix<List, N>::type;

template <std::size_t N>
struct prefix<list<>, N> {
  using type = list<>;
};

template <std::size_t N, typename T, typename... Ts>
struct prefix<list<T, Ts...>, N> {
  using type =
      std::conditional_t<N == std::size_t{0}, list<>,
                         extend_t<list<T>, prefix_t<list<Ts...>, N - 1>>>;
};

/// @brief `List' suffix of size std::min(N, count_v<List>)
/// @tparam List List of types
/// @tparam N Suffix size
template <typename List, std::size_t N>
struct suffix : public reverse<prefix_t<reverse_t<List>, N>> {};

template <typename List, std::size_t N>
using suffix_t = typename suffix<List, N>::type;

}  // namespace types
