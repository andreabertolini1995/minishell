#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char** environ;

void add_environment_variable(const char* name, const char* value) {
    // Calculate the size of the new environment array
    int current_env_count = 0;
    while (environ[current_env_count] != NULL) {
        current_env_count++;
    }

    // Allocate memory for the new environment array, including the new variable
    char** new_environ = (char**)malloc((current_env_count + 1) * sizeof(char*));

    // Copy the existing environment variables to the new array
    for (int i = 0; i < current_env_count; i++) {
        new_environ[i] = strdup(environ[i]);
    }

    // Create the new environment variable as "name=value" string
    char* new_variable;
    int variable_length = strlen(name) + strlen(value) + 2; // +2 for '=' and '\0'
    new_variable = (char*)malloc(variable_length);
    snprintf(new_variable, variable_length, "%s=%s", name, value);

    // Add the new environment variable to the new array
    new_environ[current_env_count] = new_variable;
    new_environ[current_env_count + 1] = NULL; // Set the last element to NULL as required by environ

    // Free the old environment array (if it was dynamically allocated)
    // free(environ);

    // Update environ to point to the new environment array
    environ = new_environ;
}

int main() {
    // Before adding the variable
    printf("Before:\n");
    for (char** env = environ; *env != NULL; env++) {
        printf("%s\n", *env);
    }

    // Adding a new environment variable
    add_environment_variable("NEW_VAR", "new_value");

    // After adding the variable
    printf("\n\nAfter:\n");
    for (char** env = environ; *env != NULL; env++) {
        printf("%s\n", *env);
    }

    return 0;
}