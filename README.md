# readable-pointers
A small **C++** library that makes pointers easier to read and with null pointer checkers.
It can also clear dynamic memory.

## How to set up

You will need C++17 or above.

To use the library, you need to download the ***header file*** (`readable_pointers.h`) and the ***template file*** (`redable_pointers.tpp`). Then you will need to place them in the **same working directory** and then include them with `#include "readable_pointers.h"`.
If they are not in the same working directory as the project, then add a path to the files in the include statement in the ***.cpp*** file.

## How to get started
To declare and initialize a pointer, you need to write `Pointer<T> variable_name(&variable);` if the input variable is made at compile time. If not, the refrence (`&`) is not included in the front of the input variable.
You can also initialize dynamic veriable by writing like this:

```
Pointer<int> example_pointer(new int(24), true);
```

The constructor has 3 input arguments, these are:
- **variable** which the Pointer will point to
- **is dyanmic** (by defulat is false. Set it to true when initializing dynamic memory)
- **is array** (by deafult is false. Set it to true if the input variable is an array)

>Every pointer has its own serial number, so **if an exception may occur then the serial number and the datatype will be listed**. 

### Functions
The library contains functions that help you control the pointer. All function that need a pointer to be derefrenced will check if its a **nullptr**.


| Functions                        | Description                                                          |
|----------------------------------|----------------------------------------------------------------------|
| point();                         | returns the refrence to the varaible T                               |
| get_pointer();                   | returns the pointer to the variable T                                |
| get_serial_number();             | returns the object's / pointer's serial number in c-string format    |
| is_null();                       | returns a bool value depended on the pointer. Checks if its `nullptr`|
| dispose();                       | cleares the object and releases dynamic memory                       |
| override_counter(int number = 0);| enables the user to change the counter of the serial number          |

The override_counter function is static, so it should be called like this:
`Pointer<int>::override_counter(120);`

**Warining: The pointer counter can't surpass 99999999 pointers. You can reset it with the `override_counter` function.**

*Notice: Every datatype has its own pointer counter.*
*Notice: The object can't be copied as the function has been deleted for safety*


## Operator overrides

To **move** the object, you will need the std::move constructor.
Example of the code:

```
Pointer<int> moveA(new int(6), true);
Pointer<int> moveB = move(moveA);
```

The operator **'*'** and **'->'** have both been overriden so they both contain safety checks.


````
