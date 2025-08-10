#pragma once

#include <string>
template <typename Tip>
class Pointer
{
    private:
        Tip* pointer; // the pointer of the class.
        bool dynamic; // if the pointer was initialise dynamicly with "new".

        inline static int counter = 0; 
        char serial_number[9]; // Labels the pointer

        inline std::string char_to_string_serial() // converts char array to string
        {
            return std::string(serial_number, 8);
        }

    public:
        Pointer(Tip& ref, bool is_dynamic = false) : pointer (&ref), dynamic(is_dynamic)
        {
            if (counter > 99999999) throw std::invalid_argument("Too many pointers declared (" + std::string(typeid(Tip).name()) + ")");

            int divider = 10000000;
            for (int index = 0; index < 7; index++, divider /= 10) serial_number[index] = '0' + ((counter / divider) % 10); // Calculates the serial number by dividing the counter by 10. Converts int to char.
            
            serial_number[7] = '0' + (counter % 10);
            
            serial_number[8] = '\0'; // char array becomes a c-string.
            counter++;
        };
        
        ~Pointer()
        {
            if (dynamic && pointer != nullptr) delete pointer;
            pointer = nullptr;
        }

        Tip& point() // Replaces the '*' key and check's if it's not nullptr.
        {
            if (pointer == nullptr) throw std::invalid_argument("Pointer " + char_to_string_serial() + " is null (" + std::string(typeid(Tip).name()) + ")");
            return *pointer;           
        }

        Tip& operator*()
        {
            return point();
        }

        const char* get_serial_number() const // return an const char array witch is the serial number of the pointer.
        {
            return serial_number;
        }

        bool is_null() const
        {
            return pointer == nullptr;
        }

        void dispose() // clears the pointer
        {
            if (dynamic && pointer != nullptr) delete pointer; // dynamic memory is released.
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