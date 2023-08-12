# C++ at compile time

This project aims to provide a set of utilities to manipulate `C++` types and values at compile time.

## Types

### `types::list` 

`types::list` is the essential type from `types.hpp`, it represents a list of types

```cpp
template <typename... Ts>
struct list {};
```

### Operations

#### `types::at`

```cpp
template <typename List, std::size_t Index>
struct at;
```

`types::at` is used to know the type at some index in a `types::list`, for example

`types::at_t<types::list<int, double>, 0>` is `int` while `types::at_t<types::list<int, double>, 1>` is `double`

#### `types::push`

```cpp
template <typename List, typename T>
struct push;
```

Add a type `T` the end of a `type::list`. Example `types::push_t<types::list<int, int>, char>` is `types::list<int, int, char>`

#### `types::extend`

```cpp
template <typename ListL, typename ListR>
struct extend;
```

Generate a new type that include all types from two `types::list`. Example `types::extend_t<types::list<char, int>, types::list<char, double>>` is `types::list<char, int, char, double>`

#### `types::reverse`

```cpp
template <typename List>
struct reverse;
```

Generates a new type all types from a `types::list` in reverse order

#### `types::filter`

```cpp
template <typename List, template <typename> class Predicate>
struct filter;
```

Filter a `types::list` using `Predicate`. Example `types::filter_t<types::list<int, const int>, std::is_const>` is `types::list<const int>>`

#### `types::transform`

```cpp
template <typename List, template <typename> class Operation>
struct transform;
```

Transform a `types::list` using `Operation`. Example `types::transform_t<types::list<int, const int>, std::remove_const>` is `types::list<int, int>`

#### `types::prefix`

```cpp
template <typename List, std::size_t N>
struct prefix;
```

Generate a `types::list` with the first `N` elements of another

#### `types::suffix`

```cpp
template <typename List, std::size_t N>
struct suffix;
```

Generate a `types::list` with the last `N` elements of another
 
