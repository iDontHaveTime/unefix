#ifndef EFIUTILS_HPP
#define EFIUTILS_HPP

#include "types/uefi_stddef.h"

namespace uefi{

    using nullptr_t = decltype(nullptr);
    enum class align_val_t : size_t {};

    template<typename T>
    constexpr T&& move(T& t) noexcept{
        return (T&&)t;
    }

    template<typename T> struct remove_reference{
        using type = T; 
    };

    template<typename T> struct remove_reference<T&>{
        using type = T; 
    };

    template<typename T> struct remove_reference<T&&>{
        using type = T; 
    };

    template<typename T>
    using remove_reference_t = typename remove_reference<T>::type;


    template<typename T>
    constexpr T&& forward(remove_reference_t<T>& t) noexcept{
        return (T&&)t;
    }

    template<typename T>
    constexpr T&& forward(remove_reference_t<T>&& t) noexcept{
        return (T&&)t;
    }

    template<typename T>
    constexpr bool is_nothrow_destructible = noexcept(T{}.~T());

    template<typename T>
    constexpr bool is_nothrow_move_constructible = noexcept(T(uefi::move(T{})));

    template<typename T>
    constexpr bool is_nothrow_move_assignable = noexcept(T{} = uefi::move(T{}));

    template<typename T>
    constexpr bool is_nothrow_copy_constructible = noexcept(T(T{}));

    template<typename T>
    constexpr bool is_nothrow_copy_assignable = noexcept(T{} = T{});

}

#endif // EFIUTILS_HPP
