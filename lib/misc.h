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
  if (!GetModuleFileName(NULL, path, MAX_PATH)) {
    perror("GetCurrentDirectory() error");
    return false;
  }

  // Remove the executable name from the path
  char* last_slash = strrchr(path, '\\');
  if (last_slash == NULL) {
    perror("strrchr() error");
    return false;
  }

  *last_slash = '\0';

  // Set the working directory to the directory of the executable
  if (_chdir(path) != 0) {
    perror("_chdir() error");
    return false;
  }

  // If all passed, return true
  return true;
}