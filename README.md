# readable-pointers

![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)
![C++17](https://img.shields.io/badge/C%2B%2B-17-blue.svg)

A small **C++** library that makes pointers easier to read and with null pointer checkers.
It can also clear dynamic memory.

## How to set up

Requires C++17 or above.

To use the library, you need to download the ***header file*** (`readable_pointers.h`) and the ***template file*** (`readable_pointers.tpp`). Then you will need to place them in the **same working directory** and then include them with `#include "readable_pointers.h"`.
If they are not in the same working directory as the project, then add a path to the files in the include statement in the ***.cpp*** file.

## How to get started
To declare and initialize a pointer, you need to write `Pointer<T> variable_name(&variable);` if the input variable is made at compile time. If not, the reference (`&`) is not included in the front of the input variable.
You can also initialize a dynamic variable by writing like this:

`Pointer<int> example_pointer(new int(24), true);`

The constructor has 3 input arguments. These are:
- **variable** that the pointer object will point to
- **is dynamic** (defaults to false. Set it to true when initializing dynamic memory.)
- **is array** (defaults to false. Set it to true if the input variable is an array.)

>Every pointer has its own serial number, so **if an exception may occur then the serial number and the datatype will be listed**. 

### Functions
The library contains functions that help you control the pointer. All functions that need a pointer to be dereferenced will check if it's a **nullptr**.


| Functions                        | Description                                                            |
|----------------------------------|------------------------------------------------------------------------|
| point();                         | returns the reference to the variable T                                |
| get_pointer();                   | returns the pointer to the variable T                                  |
| get_serial_number();             | returns the object's / pointer's serial number in c-string format      |
| is_null();                       | returns a bool value depending on the pointer. Checks if it's `nullptr`|
| dispose();                       | clears the object and releases dynamic memory                          |
| override_counter(int number = 0);| enables the user to change the counter of the serial number            |

The override_counter function is static, so it should be called like this:
`Pointer<int>::override_counter(120); <br> <br>

**Warning: The pointer counter can't surpass 99999999 pointers. You can reset it with the `override_counter` function.**

*Notice: Every data type has its own pointer counter.*\
*Notice: The object can't be copied, as the function has been deleted for safety.*


## Operator overrides

To **move** the object, you will need the std::move constructor.
Example of the code:

```
Pointer<int> moveA(new int(6), true);
Pointer<int> moveB = move(moveA);
```

The operators **'*'** and **'->'** have both been overridden, so they both contain safety checks.

## License

This project is licensed under the MIT license - See the [LICENSE](LICENSE) file for details.

