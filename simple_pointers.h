// header for library simple_pointer.h

#pragma once

#include <string> 
#include <typeinfo>
#include <stdexcept>

template <typename Tip>
class Pointer
{
    private:
        Tip* pointer;
        bool dynamic;
        bool type_array;
        inline static int counter = 0;
        char serial_number[9];

        Pointer (const Pointer&) = delete; // prevents copying of the object, because it might lead to undefined behavior.

        inline std::string char_to_string_serial() const;
        inline void copy_char_serial(const char* char_array) noexcept;

    public:
        Pointer(Tip* ref, bool is_dynamic = false, bool is_array = false);
        ~Pointer() noexcept;

        Pointer (Pointer&& pointer_class) noexcept;
        Pointer& operator=(Pointer&& pointer_class) noexcept;

        Tip& point() const;
        Tip* get_pointer() const;
        inline Tip& operator*() const;
        inline Tip* operator->() const;

        const char* get_serial_number() const noexcept;
        bool is_null() const noexcept;
        void dispose() noexcept;
        static void override_counter(int number = 0);
};

#include "simple_pointers.tpp"