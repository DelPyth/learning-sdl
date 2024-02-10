# Learning SDL
This repository is nothing more than a learning experience for SDL2.

# Do not expect good code.

# Styling
- I write code using K&R bracket styling, 2 space indentation with the following format of elements:
```
StructName
functionName
variable_name
CONST_NAME
```
- I do not append the last close bracket to the same line as the next `else if` or `else` statement.
- I do not leave if statements without curly brackets. This is to allow for a consistent style and easier control for future development.
```c
if (x == 5)
  printf("Incorrect Styling\n");

if (x == 5) {
  printf("Correct Styling\n");
}
```
- I prefer to use `bool` as much as I can unless needing to specify beyond the bound of two numbers.