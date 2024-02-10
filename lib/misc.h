#include <direct.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <stdbool.h>

#pragma once

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


/**
 * Prints a formatted error message to stderr
 *
 * \param msg The message to print
 * \param ... The arguments to format the message with
 * \return void
*/
void perrorf(char* msg, ...);

void perrorf(char* msg, ...) {
  va_list args;
  va_start(args, msg);
  vfprintf(stderr, msg, args);
  va_end(args);
  return;
}
