# Kiyo-Collections

| Collection | Description                                         |
| ---------- | --------------------------------------------------- |
| ArrayList  | Dynamically growing array                           |
| LinkedList | Single linked list                                  |
| List       | Double linked list                                  |
| BinaryTree | Traverseble AVL binary tree                         |
| TreeSet    | Set without duplicates implemented as a binary tree |

## Installation

With CMake:

```cmake
FetchContent_Declare(
    kiyo-collections
    GIT_REPOSITORY https://github.com/Kiyotoko/kiyo-utils.git
    GIT_TAG master
)
FetchContent_MakeAvailable(kiyo-collections)
```

## Example

```c
#include <kiyo-collections/array_list.h>
#include <stdio.h>

int main() {
  // Create a new list which stores int
  ArrayList* list = array_list_create(sizeof(int));
  for (int i = 0; i < 64; i++) {
      // Add a new element to the end
      array_list_add(list, &i);
  }

  int a;
  // Access them with get
  array_list_get(list, 81, &a);
  printf("Got element: %i\n", a);

  // Free heap allocated memory
  array_list_destroy(list);

  return 0;
}
```
