#include <direct.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>

/**
 * Sets the working directory to the directory of the executable
 *
 * \param path The path to the executable
 * \return True if the working directory was set successfully, false otherwise
*/
bool workingDir(char* path);

bool workingDir(char* path) {
  // Get the path to the executable
  if (!GetCurrentDirectory(MAX_PATH, path)) {
    perror("GetCurrentDirectory() error");
    return false;
  }

  // Remove trailing backslashes
  size_t len = strlen(path);
  if (path[len - 1] == '\\') {
    path[len - 1] = '\0';
  }

  // Set the working directory to the directory of the executable
  if (_chdir(path) != 0) {
    perror("_chdir() error");
    return false;
  }

  // Verify that the working directory was set correctly
  path = _getcwd(NULL, 0);
  if (path == NULL) {
    perror("_getcwd() error");
    return false;
  }

  printf("Working directory: %s\n", path);

  // If all passed, return true
  return true;
}