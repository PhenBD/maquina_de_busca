#ifndef STRINGS_H
#define STRINGS_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

typedef struct string String;
typedef struct string_array StringArray;

// String

/**
 * @brief Create a String object
 * 
 * @param c string
 * @return String object
 */
String *strings_create(char *c);

/**
 * @brief Convert a String object to a char *
 * 
 * @param s String object
 * @return string (char *)
 */
char *strings_get(String *s);

/**
 * @brief Get the char at the i-th position of the String object
 * 
 * @param s String object
 * @param i position
 * @return char
 */
char strings_get_char(String *s, int i);

/**
 * @brief Get the length of the String object
 * 
 * @param s String object
 * @return length
 */
int strings_get_len(String *s);

/**
 * @brief Convert all characters of the String object to lowercase
 * 
 * @param s String object
 * @return String object lowercase
 */
String *strings_to_lower(String *s);

/**
 * @brief Compare two String objects
 * 
 * @param a String object A
 * @param b String object B
 * @return 1, -1 or 0 based on strcmp
 */
int strings_compare(void *a, void *b);

/**
 * @brief Destroy a String object
 * 
 * @param s String object
 */
void strings_destroy(String *s);

// StringArray

/**
 * @brief Create a StringArray object
 * 
 * @param size size of the array
 * @return StringArray object
 */
StringArray *string_array_create(int size);

/**
 * @brief Push a String object to the back of the StringArray object
 * 
 * @param sa StringArray object
 * @param s String object
 */
void string_array_push_back(StringArray *sa, String *s);

/**
 * @brief Get the String object at the i-th position of the StringArray object
 * 
 * @param sa StringArray object
 * @param i position
 * @return String object
 */
String *string_array_get(StringArray *sa, int i);

/**
 * @brief Get the size of the StringArray object
 * 
 * @param sa StringArray object
 * @return size
 */
int string_array_size(StringArray *sa);

/**
 * @brief Destroy a StringArray object
 * 
 * @param sa StringArray object
 */
void string_array_destroy(StringArray *sa);

#endif