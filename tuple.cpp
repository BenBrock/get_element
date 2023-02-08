#include <tuple>
#include <string>
#include <iostream>
#include <ranges>
#include <vector>
#include <any>

#include "get_element.hpp"
#include "tuple_like.hpp"

struct bar {};



template <TupleLike<int, int, float, std::string> T>
void foo(T&&) { std::cout << "tuple!" << std::endl; }

template <std::ranges::range R>
void foo(R&&) { std::cout << "range!" << std::endl; }

void foo(int) { std::cout << "int!" << std::endl; }
void foo(bar) { std::cout << "bar!" << std::endl; }

int main(int argc, char** argv) {
  std::tuple x{1, 2, 3.0f, std::string("jklser")};

  foo(12);
  foo(x);
  foo(bar{});

  static_assert(value_equal<13, 13>);

  foo(std::vector<int>{});

  return 0;
}