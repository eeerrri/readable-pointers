template <typename Tip>
inline std::string Pointer<Tip>::char_to_string_serial() const // converts char array to string
{
    return std::string(serial_number, 8);
}

template <typename Tip>
inline void Pointer<Tip>::copy_char_serial(const char* char_array) noexcept
{
    for (int index = 0; index < 9; index++) serial_number[index] = char_array[index];
}

template <typename Tip>
Pointer<Tip>::Pointer(Tip* ref, bool is_dynamic, bool is_array) : pointer (ref), dynamic(is_dynamic), type_array(is_array) // constructor of the Pointer class.
{ // if type_array / is_array is true then the pointer must be declared as new[].
    if (counter > 99999999) throw std::invalid_argument("Too many pointers declared (" + std::string(typeid(Tip).name()) + ")");

    int divider = 10000000;
    for (int index = 0; index < 7; index++, divider /= 10) serial_number[index] = '0' + ((counter / divider) % 10); // Calculates the serial number by dividing the counter by 10. Converts int to char.
        
    serial_number[7] = '0' + (counter % 10);
        
    serial_number[8] = '\0'; // char array becomes a c-string.
    counter++;
}
        
template <typename Tip>
Pointer<Tip>::~Pointer() noexcept 
{
    dispose();
}

template <typename Tip>
Pointer<Tip>::Pointer (Pointer<Tip>&& pointer_class) noexcept : pointer(pointer_class.pointer), // moves the class and clears the old one.
                                             dynamic(pointer_class.dynamic)
{
    for (int index = 0; index < 9; index++) this -> serial_number[index] = pointer_class.serial_number[index]; 
    pointer_class.pointer = nullptr;
    pointer_class.dynamic = false;
}

template <typename Tip>
Pointer<Tip>& Pointer<Tip>::operator=(Pointer<Tip>&& pointer_class) noexcept // allows moving under condition.
{
    if (this == &pointer_class) return *this;

    dispose();
    this -> pointer = pointer_class.pointer;
    this -> dynamic = pointer_class.dynamic;
    this -> type_array = pointer_class.type_array;
    copy_char_serial(pointer_class.serial_number);

    pointer_class.pointer = nullptr;
    pointer_class.dynamic = false;
    pointer_class.type_array = false;
    pointer_class.serial_number[0] = '\0';

    return *this;
}

template <typename Tip>
Tip& Pointer<Tip>::point() const // Replaces the '*' key and check's if it's not nullptr.
{
    if (pointer == nullptr) throw std::invalid_argument("Pointer " + char_to_string_serial() + " is null (" + std::string(typeid(Tip).name()) + ")");
    return *pointer;           
}

template <typename Tip>
Tip* Pointer<Tip>::get_pointer() const
{
    return &point();
}

template <typename Tip>
inline Tip& Pointer<Tip>::operator*() const
{
    return point();
}

template <typename Tip>
inline Tip* Pointer<Tip>::operator->() const
{
    if (pointer == nullptr) throw std::invalid_argument("Pointer " + char_to_string_serial() + " is null (" + std::string(typeid(Tip).name()) + ")");
    return pointer;
}

template <typename Tip>
const char* Pointer<Tip>::get_serial_number() const noexcept // return an const char array witch is the serial number of the pointer.
{
    return serial_number;
}

template <typename Tip>
bool Pointer<Tip>::is_null() const noexcept
{
    return pointer == nullptr;
}

template <typename Tip>
void Pointer<Tip>::dispose() noexcept // clears the pointer
{
    if (pointer == nullptr) return;
    
    if (dynamic)
        if (type_array) delete [] pointer; 
        else delete pointer;

    dynamic = false;
    pointer = nullptr; // dynamic memory is released.   
}

template <typename Tip>
void Pointer<Tip>::override_counter(int number) // can override the counter by the user.
{
   if (number > 99999999) throw std::invalid_argument("Pointer override can't be over 99999999");
   if (number < 0) throw std::invalid_argument("Pointer override can't be negative");
    counter = number;
}


/*
To create a pointer the syntax is:
Pointer<data type> name_of_the_pointer(variable);

Data type must be the same as the variable.
*/