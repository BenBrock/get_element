#pragma once

namespace std
{
namespace ranges
{
namespace __detail
{

template <typename _T, std::size_t _I>
concept __method_gettable = // exposition only
requires(_T __tuple_like) {
    { __tuple_like. template get<_I>() };
};

template <typename _T, std::size_t _I>
concept __adl_gettable = // exposition only
requires(_T __tuple_like) {
    { get<_I>(__tuple_like) };
};

template <std::size_t _Ip>
struct __get_element_fn
{
    template <typename _TupleLike>
    requires(__method_gettable<_TupleLike, _Ip> ||
             __adl_gettable<_TupleLike, _Ip>)
    decltype(auto) operator()(_TupleLike&& __tuple_like) const
    {
        if constexpr(__method_gettable<_TupleLike, _Ip>) {
            return std::forward<_TupleLike>(__tuple_like). template get<_Ip>();
        } else {
            return get<_Ip>(std::forward<_TupleLike>(__tuple_like));
        }
    }
};
} // namespace __detail

inline namespace __get_element_namespace
{
template <std::size_t _Ip>
inline constexpr __detail::__get_element_fn<_Ip> get_element;
} // inline namespace __get_element_namespace

inline constexpr auto get_key = get_element<0>;
inline constexpr auto get_value = get_element<1>;
} // namespace ranges
} // namespace std
