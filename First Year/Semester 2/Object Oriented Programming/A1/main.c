//11.a. Determine the first n pairs of twin numbers, where n is a given natural and non-null number.
// Two prime numbers p and q are called twin if q – p = 2.
//b. Given a vector of numbers, find the longest decreasing contiguous subsequence.
//c. Given a vector of numbers, find the longest contiguous subsequence such that any consecutive elements have at least 2 distinct digits in common.
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int prime(int value){
    /// Functionality 2
    ///This function checks if a number is prime or not
    /// \param value - the value to be checked
    /// \return - 0 if the number is not prime, 1 otherwise
    if (value == 2) // 2 is a prime number
        return 1;
    if (value % 2 == 0) // if the number divides by 2 it is not prime
        return 0;
    for (int i=3; i <= value / 2; i += 2) // check by half, if we find at least one divisor the number is not prime
        if (value % i == 0)
            return 0;
    return 1;
}

int determine_if_twin(int num_1){
    /// Functionality 2
    ///This function checks if two numbers are twin numbers: both must be prime and the difference between the second one and the first one must be 2
    /// \param num_1 - The number for which we try to find if it has a twin
    /// \return - 1 if the numbers num_1 and num_1 + 2 are twin, 0 otherwise
    if ((prime(num_1) == 1) && (prime(num_1 + 2) == 1))
        return 1;
    return 0;
}

int longest_decreasing_subsequence(const int vector[], int number_of_elements, int result[]){
    ///Functionality 3
    ///This function determines the longest decreasing subsequence of a given vector
    /// \param vector - the initial vector for which we need to find the longest decreasing contiguous subsequence
    /// \param number_of_elements = the number of elements of the initial vector
    /// \param result - the vector in which we store the longest decreasing subsequence of the initial vector
    /// \return - the length of the longest decreasing contiguous subsequence
    int index, current_length = 1, max_length = 0;
    // the first element can always be a solution
    for(index = 1; index < number_of_elements; index++) {
        if (vector[index - 1] > vector[index]) // condition for decreasing
            current_length++;
        else if (current_length > max_length) { // check if the current subsequence has the maximum length
            max_length = current_length;
            int difference = index - current_length; // find the index of the first element of the subsequence
            for (int j = 0; j < max_length; j++)
                result[j] = vector[j + difference];
            current_length = 1;
        } else
            current_length = 1;
    }
    // this case is for when the subsequence is at the end of the vector
    if (current_length > max_length) {
        max_length = current_length;
        int difference = index - current_length;
        for (int j = 0; j < max_length; j++)
            result[j] = vector[j + difference];
    }
    return max_length;
}

int checkIfValid(int number_1, int number_2) {
    int counter = 0;
    char string_no_1[12];
    char string_no_2[12];
    char appearance[10] = {0};
    sprintf(string_no_1, "%d", number_1);
    sprintf(string_no_2, "%d", number_2);
    for (int i=0; i < strlen(string_no_1); i++)
        for (int j=0; j < strlen(string_no_2); j++)
            if (string_no_1[i] == string_no_2[j] && appearance[string_no_1[i]-'0'] == 0) {
                counter++;
                appearance[string_no_1[i] - '0']++;
            }
    if (counter < 2)
        return 0;
    else
        return 1;
}

int longest_subsequence_distinct_digits(int vector[], int number_of_elements, int result[]) {
    int index, current_length = 1, max_length = 0;
    for (index = 1; index < number_of_elements; index++) {
        if (checkIfValid(vector[index-1], vector[index]) == 1)
            current_length++;
        else if (current_length > max_length) { // check if the current subsequence has the maximum length
            max_length = current_length;
            int difference = index - current_length; // find the index of the first element of the subsequence
            for (int j = 0; j < max_length; j++)
                result[j] = vector[j + difference];
            current_length = 1;
        } else
            current_length = 1;
    }
    // this case is for when the subsequence is at the end of the vector
    if (current_length > max_length) {
        max_length = current_length;
        int difference = index - current_length;
        for (int j = 0; j < max_length; j++)
            result[j] = vector[j + difference];
    }
    return max_length;
}

void print_menu(){
    /// Void function for printing the menu
    printf("MENU: \n 0. Exit."
           " \n 1. Read a vector. "
           "\n 2. Given a natural non-null number, determine the first n pairs of twin numbers. "
           "\n    Two prime numbers p and q are called twin if p - q = 2."
           "\n 3. Given a vector of numbers, find the longest decreasing contiguous subsequence."
           "\n 4. Given a vector of numbers, find the longest contiguous subsequence such that any consecutive elements have at least 2 distinct digits in common.\n");
}

int read_vector(int vector[], int number_of_elements){
    /// Function to read the vector for functionality 1
    /// \param vector - the array in which we will store the vector we read
    /// \param number_of_elements - the number of elements that we want to store in the array
    /// Doesn't return anything
    printf("Enter the number of elements of the vector: ");
    scanf_s("%d", &number_of_elements);
    for (int i=0; i < number_of_elements; i++){
        printf("Enter element %d of the vector: ", i+1);
        scanf_s("%d", &vector[i]);
    }
    return number_of_elements;
}

void twin_numbers_ui() {
    ///UI function related to functionality 2: determine the first n pairs of twin numbers
    ///No parameters and no return value
    int number = 0;
    printf("Enter a number: ");
    scanf_s("%d", &number);
    int index = 0;
    int p = 2;
    if (number == 0)
        printf("The number must be non-null.");
    while (index < number) {
        if (determine_if_twin(p) == 1) {
            if (index + 1 == 1)
                printf("1st pair: %d and %d \n", p, p + 2);
            else if (index + 1 == 2)
                printf("2nd pair: %d and %d \n", p, p + 2);
            else if (index + 1 == 3)
                printf("3rd pair: %d and %d \n", p, p + 2);
            else
                printf("%dth pair: %d and %d \n", index + 1, p, p + 2);
            index += 1;
        }
        p += 1;
    }
}

void option_3(int vector[], int n) {
    int result[100], length;
    length = longest_decreasing_subsequence(vector, n, result);
    for (int i = 0; i < length; i++)
        printf("%d ", result[i]);
    printf("\n");
}

void option_4(int vector[], int n) {
    int result_2[100], length_2;
    length_2 = longest_subsequence_distinct_digits(vector, n, result_2);
    for (int index=0; index< length_2; index++)
        printf("%d ", result_2[index]);
    printf("\n");
}

int main(){
    ///Main function, no parameters and no return value
    int vector[100];
    int n = 0;
    bool done = false;
    while (!done == true){
        print_menu();
        int option = -1;
        scanf_s("%d", &option);
        if (option == 0)
            done = true;
        else if (option == 1)
            n = read_vector(vector, n);
        else if (option == 2)
            twin_numbers_ui();
        else if (option == 3) {
            option_3(vector, n);
        }else if (option == 4) {
            option_4(vector, n);
        }else
            printf("Invalid input. Please choose between 0, 1, 2 and 3.");
    }
    return 0;
}