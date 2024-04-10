
#include "set_operations.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _crt_secure_no_warnings
#pragma warning (disable: 4996)	/* hide warning*/

set A, B, C, D, E, F;
//משתנים חיצוניים מוגדרים במקום      extern


bool validate_set_name(char setName) {
    return setName >= 'A' && setName <= 'F';
}

// check if symbol is number
bool is_digit(char c) {
    return (c >= '0' && c <= '9');
}

//check if   symbol is    letter
bool is_letter(char c) {
    return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}
//check if   symbol is special symbol
bool is_symbol(char c) {
    return ((c == '#' || c == '%' || c == ':' || c == '?' || c == '*' ||
        c == '(' || c == ')' || c == '\\' || c == '!' || c == '@' ||
        c == '#' || c == '$' || c == '%' || c == '^' || c == '&' ||
        c == '*' || c == '|' || c == '}' || c == '{' || c == ';' ||
        c == '\'' || c == ',' || c == '.' || c == '/' || c == '~' ||
        c == '`' || c == '+' || c == '=' || c == '-' || c == '_' ||
        c == '[' || c == ']' || c == '<' || c == '>'));
}

bool is_set_filled(const set* s) {
    for (int i = 0; i < MAX_SET_SIZE; i++) {
        if (s->elements[i] != 0) {
            return true; //fined element not null 
        }
    }
    return false; // all elements are null - set is not filled 
}

// REturn pointer to set via set's name in nam eis not vatide - return null
set* get_set_by_name(char setName) {
    switch (setName) {
    case 'A': return &A;
    case 'B': return &B;
    case 'C': return &C;
    case 'D': return &D;
    case 'E': return &E;
    case 'F': return &F;
    default: return NULL;
    }
}

void initialize_set(set* s) {
    for (int i = 0; i < MAX_SET_SIZE / 8; i++) {
        s->elements[i] = 0; // Zero filling into each byte of the array.
    }
}

// all validated commands
const char* valid_commands[] = { "read_set", "print_set", "union_set", "intersect_set", "sub_set","comp_set",":halt" };
const int valid_commands_count = 7;

int count_commas(const char* str) {
    int count = 0;
    while (*str) {
        if (*str == ',') {
            count++;
        }
        str++;
    }
    return count;
}

// check and validate name of entered command
char* process_command_and_get_remaining(char* input, char* commandOut) {
    char* commandEnd = strstr(input, " "); // finding end of the command
    if (commandEnd != NULL) {                // copy command
        strncpy(commandOut, input, commandEnd - input);
        commandOut[commandEnd - input] = '\0';   // correct ending of str with needed symbol

        // validate command name
        int isValidCommand = 0;
        for (int i = 0; i < valid_commands_count; i++) {
            if (strcmp(commandOut, valid_commands[i]) == 0) {
                isValidCommand = 1;
                break;
            }
        }

        if (!isValidCommand) {   //if command not found
            printf("No such command \n");
            return 0;
        }

        return commandEnd + 1;    // return input after command
    }
    return 0;     // other trouble  -return NULL
}


char extract_set_name(char** remainingInput) {
    while (**remainingInput == ' ') (*remainingInput)++; // moving after ' ' after command 
    char setName = **remainingInput; // get first symbol , that must to be the name of the set

    if (setName >= 'A' && setName <= 'F') {
        (*remainingInput)++; //   movint next (place of set name)

        while (**remainingInput == ' ' || **remainingInput == ',') {
            (*remainingInput)++; // moving next(commas or space after set name
        }
        return setName; // return set name 
    }
    else {
        return 0; //return null if name set is not valid  
    }
}

char extract_set_name_comp(char** remainingInput)
{
    while (**remainingInput == ' ') (*remainingInput)++; // moving after space before set name 
    char setName = **remainingInput; // get first symbol , that must to be the name of the set

    if (setName >= 'A' && setName <= 'F') {
        (*remainingInput)++; //movint next (place of set name)

        while (**remainingInput == ' ') {
            (*remainingInput)++; // moving next( space after set name)
        }
        return setName; //  return set name 
    }
    else {
        return 0; //return null if name set is not valid     
    }
}



//bool process_numbers_and_fill_set(char* str, set* targetSet) {
//    bool errorOccurred = false;
//    int num = 0;
//    bool negative = false;
//    bool numberStarted = false;
//    bool finishedCorrectly = false;
//    set tempSet; // temporary set 
//    initialize_set(&tempSet); // init for temp st
//    for (; *str; str++) {
//        if (*str == ',' || *str == ' ' || *str == '\n' || *str == '\0') {
//            if (numberStarted)
//            {
//                // check if number is in diapasone of 0-127
//                if (!negative && (num >= 0 && num < 128))
//                {
//                    tempSet.elements[num / 8] |= (1 << (num % 8)); // adding number to set 
//                    num = 0; // prepare for new number,null init
//                    negative = false;
//                    numberStarted = false;
//                }
//                else if (negative && num == 1)
//                {
//                    finishedCorrectly = true;
//                    //return !errorOccurred;
//                }
//                else
//                {
//                    printf("%d is out of range \n", negative ? -num : num); //ternary operator for check what a kind of mistake,prepare output
//                    errorOccurred = true;
//                    return false;
//                }
//
//            }
//        }
//        else if (is_digit(*str)) {
//            numberStarted = true; // start reading number
//            num = num * 10 + (*str - '0');
//        }// forming number from sequence of numbers in string 
//        else if (*str == '-') {
//            negative = true; // flag if nefative
//            numberStarted = true;
//        }
//        else if (is_letter(*str)) {
//            printf("Letters are not allowed for usage as a numbers,please try again. \n");
//            return false;
//
//        }
//        else if (is_symbol(*str)) {
//            printf("Special characters are not allowed,please try again.\n");
//            return false;
//        }
//        else {
//            printf("Unknown error.Try again.\n");
//            return false;
//        }
//    }
//    if (!finishedCorrectly) { // check if set completed correctcty with -1 in the end
//        printf("Set completed incorrectly. Please finish the set with number -1 to save set data, try again.\n");
//        return false;
//    }
//    else if (!errorOccurred) {
//        // if no errors copy from tempset to regular (as ptr to targetset)
//        for (int i = 0; i < MAX_SET_SIZE; i++) {
//            targetSet->elements[i] = tempSet.elements[i];
//        }
//    }
//    else {
//        printf("unknown input");
//        return false;
//
//    }
//
//    return !errorOccurred;
//}

bool process_numbers_and_fill_set(char* str, set* targetSet) {
    bool errorOccurred = false;
    int num = 0;
    bool negative = false;
    bool numberStarted = false;
    bool finishedCorrectly = false;
    set tempSet; // temporary set 
    initialize_set(&tempSet); // init for temp st
    for (; *str; str++) {
        if (*str == ',' || *str == ' ' || *str == '\n' || *str == '\0') {
            if (numberStarted)
            {
                // check if number is in diapasone of 0-127
                if (!negative && (num >= 0 && num < 128))
                {
                    tempSet.elements[num / 8] |= (1 << (num % 8)); // adding number to set 
                    num = 0; // prepare for new number,null init
                    negative = false;
                    numberStarted = false;
                }
                else if (negative && num == 1)
                {
                    finishedCorrectly = true;
                    //return !errorOccurred;
                }
                else
                {
                    printf("%d is out of range \n", negative ? -num : num); //ternary operator for check what a kind of mistake,prepare output
                    errorOccurred = true;
                    return false;
                }

            }
        }
        else if (is_digit(*str)) {
            numberStarted = true; // start reading number
            num = num * 10 + (*str - '0');
        }// forming number from sequence of numbers in string 
        else if (*str == '-') {
            negative = true; // flag if nefative
            numberStarted = true;
        }
        else if (is_letter(*str)) {
            printf("Letters are not allowed for usage as a numbers,please try again. \n");
            return false;

        }
        else if (is_symbol(*str)) {
            printf("Special characters are not allowed,please try again.\n");
            return false;
        }
        else {
            printf("Unknown error.Try again.\n");
            return false;
        }
    }
    if (!finishedCorrectly) { // check if set completed correctcty with -1 in the end
        printf("Set completed incorrectly. Please finish the set with number -1 to save set data, try again.\n");
        return false;
    }
    else if (!errorOccurred) {
        // if no errors copy from tempset to regular (as ptr to targetset)
        for (int i = 0; i < MAX_SET_SIZE; i++) {
            targetSet->elements[i] = tempSet.elements[i];
        }
    }
    else {
        printf("unknown input");
        return false;

    }

    return !errorOccurred;
}


void print_set1(const set* targetSet) {
    int count = 0;
    bool isEmpty = true;
    printf("Set content: \n");
    // print set content
    for (int i = 0; i < MAX_SET_SIZE; i++) {
        if (targetSet->elements[i / 8] & (1 << (i % 8))) {
            printf("%d ", i);
            isEmpty = false;
            count++;
            if (count % 16 == 0) {
                printf("\n");
            }
        }
    }

    if (isEmpty) {
        printf("The set is empty.\n");
    }
    else {
        printf("\n");
    }
}


void union_set_and_print(const set* setA, const set* setB) {
    set resultSet;
    int i = 0;
    // union of two set
    for (i; i < MAX_SET_SIZE; i++) {
        resultSet.elements[i] = setA->elements[i] | setB->elements[i];
    }
    // print set  result
    print_set1(&resultSet);
}

void union_set_and_store(const set* setA, const set* setB, set* resultSet) {
    // fill set result
    initialize_set(resultSet);
    // union two sets
    for (int i = 0; i < MAX_SET_SIZE; i++) {
        resultSet->elements[i] = setA->elements[i] | setB->elements[i];
    }
    // no oputput print     result saved  into  resultSet
}

void intersect_set_and_print(const set* setA, const set* setB) {
    set resultSet; // create temporary set for result 
    // func for intersect
    for (int i = 0; i < MAX_SET_SIZE; i++) {
        resultSet.elements[i] = setA->elements[i] & setB->elements[i];
    }
    // print set  result
    print_set1(&resultSet);
}

void intersect_set_and_store(const set* setA, const set* setB, set* resultSet) {
    initialize_set(resultSet);
    // func for intersect
    for (int i = 0; i < MAX_SET_SIZE; i++) {
        resultSet->elements[i] = setA->elements[i] & setB->elements[i];
    }

    // no oputput print  result saved  into  resultSet
}

void sub_set_and_print(const set* setA, const set* setB) {
    set resultSet; // create temporary set for result 
    // func for   sub sets
    for (int i = 0; i < MAX_SET_SIZE; i++) {
        resultSet.elements[i] = setA->elements[i] & ~(setB->elements[i]);
    }
    // print set  result
    print_set1(&resultSet);
}

void sub_set_and_store(const set* setA, const set* setB, set* resultSet) {
    initialize_set(resultSet);
    // func for   sub sets
    for (int i = 0; i < MAX_SET_SIZE; i++) {
        resultSet->elements[i] = setA->elements[i] & ~(setB->elements[i]);
    }
    // no oputput print  result saved  into  resultSet
}



void set_complement(const set* s, set* result) {
    for (int i = 0; i < MAX_SET_SIZE; i++) {
        result->elements[i] = ~(s->elements[i]);
    }
}

void comp_set_and_store(const set* setA, set* setB) {
    set_complement(setA, setB);
    //func for  comp а setA and save in setB
}

void comp_set_and_print(const set* setA) {
    set resultSet; // create temporary set for result 
    initialize_set(&resultSet);
    set_complement(setA, &resultSet); //func for  comp а setA and save in setB
    // print set  result
    print_set1(&resultSet);
}