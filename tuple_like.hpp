#pragma once

#include "get_element.hpp"

// Helper concept to determine whether two values are equal.
template <auto A, auto B>
struct value_equal_impl_ : std::false_type {};
template <auto A, auto B>
requires(A == B)
struct value_equal_impl_<A, B> : std::true_type {};

template <auto A, auto B>
concept value_equal = value_equal_impl_<A, B>::value;

// Tuple-like type `Tuple` has a gettable element at index `I` of type `U`.
template <typename Tuple, std::size_t I, typename U = std::any>
concept TupleElementGettable =
requires(Tuple& tuple) {
    {std::ranges::get_element<I>(tuple)} -> std::common_reference_with<U>;
};

// Tuple-like type `Tuple`:
// 1) Has a `tuple_size` equal to `sizeof...(Types)`.
// 2) For index I in `[0, sizeof...(Types))`, tuple element I is gettable
//    (using `std::ranges::get_element`)
//    and returns an element that shares a common reference with Types[I].
template <typename T, typename... Types>
concept TupleLike =
requires {
    typename std::tuple_size<std::remove_cvref_t<T>>::type;
    requires(value_equal<std::tuple_size_v<std::remove_cvref_t<T>>, sizeof...(Types)>);
}
&& []<std::size_t... I>(std::index_sequence<I...>) {
       return (TupleElementGettable<T, I, Types> && ...);
   }(std::make_index_sequence<sizeof...(Types)>());