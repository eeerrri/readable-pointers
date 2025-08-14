#pragma once

#include <string>
#include <typeinfo>
#include <stdexcept>

template <typename Tip>
class Pointer
{
    private:
        Tip* pointer; // the pointer of the class.
        bool dynamic; // if the pointer was initialise dynamicly with "new".

        inline static int counter = 0; 
        char serial_number[9]; // Labels the pointer

        Pointer (const Pointer&) = delete; // prevents copying of the object, because it might lead to undefined behavior.

        Pointer (Pointer&& pointer_class) noexcept : pointer(pointer_class.pointer), // moves the class and clears the old one.
                                                     dynamic(pointer_class.dynamic)
        {
            for (int index = 0; index < 9; index++) this -> serial_number[index] = pointer_class.serial_number[index]; 
            pointer_class.pointer = nullptr;
            pointer_class.dynamic = false;
        }

        Pointer& operator=(Pointer&& pointer_class) noexcept // allows moving under condition.
        {
            if (this == &pointer_class) return *this;

            dispose();
            this -> pointer = pointer_class.pointer;
            this -> dynamic = pointer_class.dynamic;

            copy_char_serial(pointer_class.serial_number);

            pointer_class.pointer = nullptr;
            pointer_class.dynamic = false;

            return *this;
        }

        inline std::string char_to_string_serial() const // converts char array to string
        {
            return std::string(serial_number, 8);
        }

        inline void copy_char_serial(const char* char_array) noexcept
        {
            for (int index = 0; index < 9; index++) serial_number[index] = char_array[index];
        }

    public:
        Pointer(Tip& ref, bool is_dynamic = false) : pointer (&ref), dynamic(is_dynamic) // constructor of the Pointer class.
        {
            if (counter > 99999999) throw std::invalid_argument("Too many pointers declared (" + std::string(typeid(Tip).name()) + ")");

            int divider = 10000000;
            for (int index = 0; index < 7; index++, divider /= 10) serial_number[index] = '0' + ((counter / divider) % 10); // Calculates the serial number by dividing the counter by 10. Converts int to char.
            
            serial_number[7] = '0' + (counter % 10);
            
            serial_number[8] = '\0'; // char array becomes a c-string.
            counter++;
        };
        
        ~Pointer() noexcept 
        {
            if (dynamic && pointer != nullptr) delete pointer;
            dynamic = false;
            pointer = nullptr;
        }

        Tip& point() const // Replaces the '*' key and check's if it's not nullptr.
        {
            if (pointer == nullptr) throw std::invalid_argument("Pointer " + char_to_string_serial() + " is null (" + std::string(typeid(Tip).name()) + ")");
            return *pointer;           
        }

        inline Tip& operator*() const
        {
            return point();
        }

        inline Tip* operator->() const
        {
            return point();
        }

        const char* get_serial_number() const noexcept // return an const char array witch is the serial number of the pointer.
        {
            return serial_number;
        }

        bool is_null() const noexcept
        {
            return pointer == nullptr;
        }

        void dispose() noexcept // clears the pointer
        {
            if (dynamic && pointer != nullptr) delete pointer; // dynamic memory is released.
            dynamic = false;
            pointer = nullptr;
        }

        static void override_counter(int number = 0) // can override the counter by the user.
        {
            if (number > 99999999) throw std::invalid_argument("Pointer override can't be over 99999999");
            if (number < 0) throw std::invalid_argument("Pointer override can't be negative");
            counter = number;
        }
};

/*
To create a pointer the syntax is:
Pointer<data type> name_of_the_pointer(variable);

Data type must be the same as the variable.
*/