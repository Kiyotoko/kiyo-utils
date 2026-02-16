# Kiyo-Collections

| Collection | Description                                         |
| ---------- | --------------------------------------------------- |
| Vec        | Dynamically growing array                           |
| LinkedList | Double linked linked_list                           |
| BTreeMap   | Traverseble AVL binary tree                         |
| BTreeSet   | Set without duplicates implemented as a binary tree |

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
  // Create a new vec which stores integers
  Vec* vec = vec_new(sizeof(int));
  for (int i = 0; i < 64; i++) {
      // Add a new element to the end
      vec_push(vec, &i);
  }

  // Access them with get and store it in a
  int a;
  vec_get(vec, 21, &a);

  // Print a, should be 21
  printf("Got element: %i\n", a);

  // Free heap allocated memory
  vec_free(vec);

  return 0;
}
```
