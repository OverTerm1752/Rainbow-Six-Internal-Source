#pragma once

struct Vftable
{
    constexpr void* GetFunction(void* thisptr, const size_t index) noexcept
    {
        return (*static_cast<void***>(thisptr))[index];
    }

    template <typename T, typename ... U>
    constexpr T CallFunction(void* thisptr, const size_t index, U ... params) noexcept
    {
        using Fn = T(__thiscall*)(void*, decltype(params)...);
        return (*static_cast<Fn**>(thisptr))[index](thisptr, params...);
    }
};