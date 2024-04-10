
#ifndef SET_OPERATIONS_H
#define SET_OPERATIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include < string.h >
#define _crt_secure_no_warnings
#pragma warning (disable: 4996)	/* hide warning*/

#define MAX_SET_SIZE 128     // מספר התאים במערך, מכיוון שיש לנו 128 אפשרויות  unsigned char


typedef struct {
    unsigned char elements[MAX_SET_SIZE];
} set;

//   הגדרת המשתנים החיצוניים
extern set A, B, C, D, E, F;


bool validate_set_name(char setName);
bool is_digit(char c);
bool is_set_filled(const set* s);
set* get_set_by_name(char setName);
void initialize_set(set* s);
int count_commas(const char* str);
char* process_command_and_get_remaining(char* input, char* commandOut);
char extract_set_name(char** remainingInput);
char extract_set_name_comp(char** remainingInput);
bool process_numbers_and_fill_set(char* str, set* targetSet);
void print_set1(const set* targetSet);
void union_set_and_print(const set* setA, const set* setB);
void union_set_and_store(const set* setA, const set* setB, set* resultSet);
void intersect_set_and_print(const set* setA, const set* setB);
void intersect_set_and_store(const set* setA, const set* setB, set* resultSet);
void sub_set_and_print(const set* setA, const set* setB);
void sub_set_and_store(const set* setA, const set* setB, set* resultSet);
void set_complement(const set* s, set* result);
void comp_set_and_store(const set* setA, set* setB);
void comp_set_and_print(const set* setA);


#endif  SET_OPERATIONS_H