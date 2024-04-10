
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#define _crt_secure_no_warnings
#pragma warning (disable: 4996)	/* hide warning*/
#include "set_operations.h"



int main()
{
    while (true)
    {

        char command[20] = { 0 };
        char input[(MAX_SET_SIZE * 5)] = { 0 };

        printf("Enter command, set name, and numbers (end with -1): ");
        fgets(input, sizeof(input), stdin);
        char* remainingInput = { 0 };
        remainingInput = process_command_and_get_remaining(input, command);

        set* targetSet;
        targetSet = NULL;
        if (strcmp(command, "read_set") == 0)
        {
            char setName = extract_set_name(&remainingInput);
            if (validate_set_name(setName))
            {
                targetSet = get_set_by_name(setName);
                initialize_set(targetSet);
                if (!is_set_filled(targetSet))
                {
                    if ((!process_numbers_and_fill_set(remainingInput, targetSet)))
                    {
                        continue;
                    }
                }

            }
            else
            {
                printf("No such set\n");
            }
        }
        else if (strcmp(command, "print_set") == 0)
        {
            char setName = extract_set_name(&remainingInput);
            if (validate_set_name(setName))
            {
                targetSet = get_set_by_name(setName);
                if (targetSet)
                {
                    print_set1(targetSet);
                }
                else {
                    printf("Set '%c' not found.\n", setName);

                }
            }
            else {
                printf("Invalid set name.\n");
            }
        }
        else if (strcmp(command, "union_set") == 0) {
            int commas = 0;
            set* setA = NULL;
            set* setB = NULL;
            commas = count_commas(remainingInput);
            char setNameA = extract_set_name(&remainingInput);
            char setNameB = extract_set_name(&remainingInput);
            char setNameC = '\0'; // use only if 3 sets needed           
            setA = get_set_by_name(setNameA);
            setB = get_set_by_name(setNameB);
            set* setC = NULL;// initialisation with NULL, using only if 3 sets 
            // check set's name and if it is not null
            if (setA == NULL || setB == NULL || (commas == 2 && !(setC = get_set_by_name(extract_set_name(&remainingInput))))) {
                printf("One of the sets does not exist.\n");
            }
            else {
                // check which function to use(commas func helper)
                if (commas == 2) { // 2 commas - 3 sets
                    // union for  A and B, result save to set C
                    union_set_and_store(setA, setB, setC);
                }
                else if (commas == 1) { // one comme - two sets 
                 // result only printed
                    union_set_and_print(setA, setB);
                }
                else {
                    printf("Invalid input format or unknown command.\n");
                }
            }
        }
        else if (strcmp(command, "intersect_set") == 0)
        {
            int commas = 0;
            set* setA = NULL;
            set* setB = NULL;
            commas = count_commas(remainingInput);
            char setNameA = extract_set_name(&remainingInput);
            char setNameB = extract_set_name(&remainingInput);
            char setNameC = '\0';
            setA = get_set_by_name(setNameA);
            setB = get_set_by_name(setNameB);
            set* setC = NULL;
            // check set's name and if it is not null
            if (setA == NULL || setB == NULL || (commas == 2 && !(setC = get_set_by_name(extract_set_name(&remainingInput))))) {
                printf("One of the sets does not exist.\n");
            }
            else {
                // check which function to use(commas func helper)
                if (commas == 2) {  // union for  A and B, result save to set C
                      // union func for  A and B, result save to set C
                    intersect_set_and_store(setA, setB, setC);
                }
                else if (commas == 1) { // one comme - two sets
                  // result only printed
                    intersect_set_and_print(setA, setB);
                }
                else {
                    printf("Invalid input format or unknown command.\n");
                }
            }
        }
        else if (strcmp(command, "sub_set") == 0) {
            int commas = 0;
            set* setA = NULL;
            set* setB = NULL;
            commas = count_commas(remainingInput);
            char setNameA = extract_set_name(&remainingInput);
            char setNameB = extract_set_name(&remainingInput);
            char setNameC = '\0';
            setA = get_set_by_name(setNameA);
            setB = get_set_by_name(setNameB);
            set* setC = NULL;
            // check set's name and if it is not null
            if (setA == NULL || setB == NULL || (commas == 2 && !(setC = get_set_by_name(extract_set_name(&remainingInput))))) {
                printf("One of the sets does not exist.\n");
            }
            else {
                // check which function to use(commas func helper)
                if (commas == 2) {
                    // union for  A and B, result save to set C
                    sub_set_and_store(setA, setB, setC);
                }
                else if (commas == 1) { // union func for  A and B, result save to set C
                  // result only printed
                    sub_set_and_print(setA, setB);
                }
                else {
                    printf("Invalid input format or unknown command.\n");
                }
            }
        }
        else if (strcmp(command, "comp_set") == 0) {

            int commas = 0;
            set* setA = NULL;
            set* setB = NULL;
            commas = count_commas(remainingInput);
            char setNameA = extract_set_name(&remainingInput);
            setA = get_set_by_name(setNameA);
            // check set's name and if it is not null
            if (setA == NULL) {
                printf("The set does not exist.\n");
            }
            else if (commas == 0 && setA != NULL) { // only one need to comp
                comp_set_and_print(setA);
            }
            else if (commas == 1) { // two needed to comp - one to save
                char setNameB = extract_set_name(&remainingInput);
                setB = get_set_by_name(setNameB);
                if (setB == NULL) {
                    printf("Second set does not exist.\n");
                }
                else {
                    comp_set_and_store(setA, setB);
                }
            }
            // sets validation
            else if (setA == NULL || setB == NULL || !(commas == 1)) {
                printf("One of the sets does not exist.\n");
            }
            else {
                printf("Invalid format of input.\n");
            }
        }
        else if (strncmp(input, ":halt", 5) == 0) {
            printf("Exiting program...\n");
            break;
        }
    }

    return 0;
}
