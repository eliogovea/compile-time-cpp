#include "types.hpp"

#include <cstdlib>

int main(int argc, char* argv[]) {
  // is_list
  static_assert(types::is_list_v<types::list<>>);
  static_assert(!types::is_list_v<int>);

  // count
  static_assert(types::count_v<types::list<>> == 0);
  static_assert(types::count_v<types::list<int>> == 1);
  static_assert(types::count_v<types::list<int, int>> == 2);

  // push
  static_assert(std::is_same_v<types::push_t<types::list<int>, int>,
                               types::list<int, int>>);

  // extend
  static_assert(std::is_same_v<
                types::extend_t<types::list<int, int>, types::list<int, int>>,
                types::list<int, int, int, int>>);

  // reverse
  static_assert(std::is_same_v<types::reverse_t<types::list<char, int>>,
                               types::list<int, char>>);
  static_assert(std::is_same_v<types::reverse_t<types::list<char, int, double>>,
                               types::list<double, int, char>>);

  // at
  static_assert(std::is_same_v<types::at_t<types::list<int, double>, 0>, int>);
  static_assert(
      std::is_same_v<types::at_t<types::list<int, double>, 1>, double>);

  // filter
  static_assert(std::is_same_v<
                types::filter_t<types::list<int, const int>, std::is_const>,
                types::list<const int>>);

  // transform
  static_assert(std::is_same_v<types::transform_t<types::list<int, const int>,
                                                std::remove_const>,
                               types::list<int, int>>);

  // prefix
  static_assert(std::is_same_v<types::prefix_t<types::list<int, double>, 0>,
                               types::list<>>);
  static_assert(std::is_same_v<types::prefix_t<types::list<int, double>, 1>,
                               types::list<int>>);
  static_assert(std::is_same_v<types::prefix_t<types::list<int, double>, 2>,
                               types::list<int, double>>);
  static_assert(std::is_same_v<types::prefix_t<types::list<int, double>, 3>,
                               types::list<int, double>>);

  // suffix
  static_assert(std::is_same_v<types::suffix_t<types::list<int, double>, 0>,
                               types::list<>>);
  static_assert(std::is_same_v<types::suffix_t<types::list<int, double>, 1>,
                               types::list<double>>);
  static_assert(std::is_same_v<types::suffix_t<types::list<int, double>, 2>,
                               types::list<int, double>>);
  static_assert(std::is_same_v<types::suffix_t<types::list<int, double>, 3>,
                               types::list<int, double>>);
  return EXIT_SUCCESS;
}
