# Kiyo-Collections

| Collection | Description                                         |
| ---------- | --------------------------------------------------- |
| Vec        | Dynamically growing array                           |
| LinkedLinkedList | Double linked linked_list                                  |
| BTreeMap | Traverseble AVL binary tree                         |
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
#include <kiyo-collections/vec.h>
#include <stdio.h>

int main() {
  // Create a new linked_list which stores int
  Vec* linked_list = vec_new(sizeof(int));
  for (int i = 0; i < 64; i++) {
      // Add a new element to the end
      vec_push(linked_list, &i);
  }

  int a;
  // Access them with get
  vec_get(linked_list, 81, &a);
  printf("Got element: %i\n", a);

  // Free heap allocated memory
  vec_free(linked_list);

  return 0;
}
```
