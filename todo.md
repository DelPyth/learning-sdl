# TODO list
- [ ] **Refactor.** Remake `main.c` to split drawing and events into separate functions to clean `int main()`.
- [ ] **Do not use magic numbers.** Add `#define`s or `const`s instead of free-floating numbers to which have no way of being modified in a controlled manor.
- [ ] **Void or go broke.**
  - Go through all functions that have a return value and verify they worked/returned what was required, raising an error if not.
  - Go through all functions that return void and cast their output to void, for example: `(void)printf(...);`
- [ ] **Does it need to go there?**
  - Remove `main.exe` as well as the `.dll` files within `target` and use the `makefile` to automatically move the correct DLLs there.
  - Move `target/assets` into the current workspace and force the build target to use the current workspace as its working directory (UNLESS BUILT TO RELEASE).
