/******************
Name: Aviv Sayer
ID: 326552304
Assignment: ex3
*******************/

#include <stdio.h>

/**
 * it was very fun to write this hehe                                                           <br>
 *                                                                                              <br>
 * To whomever this concerns.                                                                   <br>
 * Whilst I have had many problems with the homework instructions,                              <br>
 * what I have come to realize is truly unacceptable.                                           <br>
 * I, an innocent programmer, was reading the instructions of an exercise,                      <br>
 * when suddenly I saw that one can not use a library but \<stdio.h\>!                          <br>
 * I burst into tear; (>_<) "I can not use the [bool] type!", said I, distraught.               <br>
 * Why hath this fate befallen me? For the bool type hath been taught to us,                    <br>
 * so why should we not use it?                                                                 <br>
 * But alas! The word "bool" is defined verily in \<stdbool.h\>!                                <br>
 * Do you now see the problem here inlies?                                                      <br>
 * Hark, for \<stdbool.h\> is not of \<stdio.h\>!                                               <br>
 * So why should we not use [_Bool], defined in C itself?                                       <br>
 * We know in \<stdbool.h\>, [bool] is merely provided as:                                      <br>
 * <code>                                                                                       <br>
 * #define bool         _Bool                                                                   <br>
 * </code>                                                                                      <br>
 * But here yet hides a tricky trap, for this, we have not yet learned!                         <br>
 * What we have not learned we may not use; truly, woe is us.                                   <br>
 * I thank you for your consideration, dear respected faculty.                                  <br>
 */

#define bool            char    // the smallest datatype that we had learnt and is not bool
#define true            1       // like in <stdbool.h>
#define false           0       // like in <stdbool.h>

// define constants for array sizes and other values
#define NUM_OF_BRANDS   5
#define BRANDS_NAMES    15
#define NUM_OF_TYPES    4
#define TYPES_NAMES     10
#define DAYS_IN_YEAR    365
#define EMPTY_CELL      (-1)

// define constants for car types
#define SUV             0
#define SEDAN           1
#define COUPE           2
#define GT              3

// define constants for menu options
#define ADD_ONE         1
#define ADD_ALL         2
#define STATS           3
#define PRINT           4
#define INSIGHTS        5
#define DELTAS          6
#define DONE            7

// declare arrays for brand and car type names
char brands[NUM_OF_BRANDS][BRANDS_NAMES] = {
        "Toyoga",
        "HyunNight",
        "Mazduh",
        "FolksVegan",
        "Key-Yuh"
};
char types[NUM_OF_TYPES][TYPES_NAMES] = {
        "SUV",
        "Sedan",
        "Coupe",
        "GT"
};

// declare all funcs
void printMenu();
void initValues(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]);
void setSales(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day, int brand,
              int suvSales, int sedanSales, int coupeSales, int gtSales);
void scanBrand(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int days[NUM_OF_BRANDS]);
bool scanEnabledBrands(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],
                       int days[NUM_OF_BRANDS], bool enabled[NUM_OF_BRANDS]);
int indexOfMax(int arr[], int size);
int indexOfMin(int arr[], int size);
void printString(char str[]);

int main() {
    // declare a 3D array to store sales data for each day, brand, and car type
    int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES];
    // declare an array to track the number of days of data for each brand
    int days[NUM_OF_BRANDS] = {};
    // declare a variable to store the user's choice from the menu
    int choice;

    // initialize the cube array with empty cell values
    initValues(cube);

    // loop indefinitely until the user chooses to exit
    while (true) {
        // print the menu options
        printMenu();
        // read the user's choice
        scanf(" %d", &choice);

        // switch-case block to handle different user choices
        switch (choice) {
            case ADD_ONE: // scan and add sales data for a single brand
                scanBrand(cube, days);
                break;
            case ADD_ALL: { // scan and add sales data for all brands
                int brandCount = NUM_OF_BRANDS; // remaining brands counter
                bool remainingBrands[NUM_OF_BRANDS];
                // initialize all brands as enabled
                for (int i = 0; i < NUM_OF_BRANDS; ++i) // iterate over each brand
                    remainingBrands[i] = true;
                // loop until all brands have been processed
                while (brandCount) {
                    // print a message indicating which brands still need data
                    printf("No data for brands");
                    for (int i = 0; i < NUM_OF_BRANDS; ++i) { // iterate over each brand
                        if (remainingBrands[i]) {
                            printf(" ");
                            printString(brands[i]); // (>_<)
                        }
                    }
                    printf("\n"
                           "Please complete the data\n");
                    // scan and add sales data for enabled brands, decreasing the brand count for each successful scan
                    brandCount -= scanEnabledBrands(cube, days, remainingBrands);
                }
                break;
            }
            case STATS: { // print the stats of a specific day
                int day;
                // prompt the user to enter a valid day
                printf("What day would you like to analyze?\n");
                scanf(" %d", &day);

                // validate the input day
                while (day > DAYS_IN_YEAR || day < 1 || days[indexOfMin(days, NUM_OF_BRANDS)] < day) {
                    printf("Please enter a valid day.\n"
                           "What day would you like to analyze?\n");
                    scanf(" %d", &day);
                }

                // declare variables to store total sales, brand sales, and type sales
                int salesSum = 0, brandSales[NUM_OF_BRANDS] = {}, typeSales[NUM_OF_TYPES] = {};
                // calculate total sales, brand sales, and type sales for the specified day
                for (int i = 0; i < NUM_OF_BRANDS; ++i) { // iterate over each brand
                    for (int j = 0; j < NUM_OF_TYPES; ++j) { // iterate over each car type for the brand
                        salesSum += cube[day - 1][i][j];
                        brandSales[i] += cube[day - 1][i][j];
                        typeSales[j] += cube[day - 1][i][j];
                    }
                }

                // print the calculated statistics
                printf("In day number %d:\n"
                       "The sales total was %d\n"
                       "The best sold brand with %d sales was ",
                       day, salesSum, brandSales[indexOfMax(brandSales, NUM_OF_BRANDS)]);
                printString(brands[indexOfMax(brandSales, NUM_OF_BRANDS)]); // (>_<)
                printf("\n"
                       "The best sold type with %d sales was ",
                       typeSales[indexOfMax(typeSales, NUM_OF_TYPES)]);
                printString(types[indexOfMax(typeSales, NUM_OF_TYPES)]); // (>_<)
                printf("\n\n");

                break;
            }
            case PRINT: { // print all the data
                printf("*****************************************\n\n"); // header
                for (int i = 0; i < NUM_OF_BRANDS; ++i) { // iterate over each brand
                    printf("Sales for ");
                    printString(brands[i]); // (>_<)
                    printf(":\n");
                    for (int j = 0; j < days[i]; ++j) { // iterate over each day for the brand
                        printf("Day %d-", j + 1);
                        for (int k = 0; k < NUM_OF_TYPES; ++k) { // iterate over each car type for the day and brand
                            // print brand's day's type data
                            printf(" ");
                            printString(types[k]); // (>_<)
                            printf(": %d", cube[j][i][k]);
                        }
                        printf("\n");
                    }
                }
                printf("\n\n*****************************************\n"); // footer

                break;
            }
            case INSIGHTS: { // print the best-selling {x} overall
                // declare arrays to store total sales for each brand, type, and day
                int brandSales[NUM_OF_BRANDS] = {}, typeSales[NUM_OF_TYPES] = {}, daySales[DAYS_IN_YEAR] = {};
                // calculate total sales for each brand, type, and day
                for (int i = 0; i < NUM_OF_BRANDS; ++i) { // iterate over each brand
                    for (int j = 0; j < days[i]; ++j) { // iterate over each day for the brand
                        for (int k = 0; k < NUM_OF_TYPES; ++k) { // iterate over each car type for the day and brand
                            brandSales[i] += cube[j][i][k];
                            typeSales[k] += cube[j][i][k];
                            daySales[j] += cube[j][i][k];
                        }
                    }
                }

                // print overall insights
                printf("The best-selling brand overall is ");
                printString(brands[indexOfMax(brandSales, NUM_OF_BRANDS)]); // (>_<)
                printf(": %d$\n"
                       "The best-selling type of car is ",
                       brandSales[indexOfMax(brandSales, NUM_OF_BRANDS)]);
                printString(types[indexOfMax(typeSales, NUM_OF_TYPES)]); // (>_<)
                printf(": %d$\n"
                       "The most profitable day was day number %d: %d$\n",
                       typeSales[indexOfMax(typeSales, NUM_OF_TYPES)],
                       indexOfMax(daySales, DAYS_IN_YEAR) + 1,
                       daySales[indexOfMax(daySales, DAYS_IN_YEAR)]);

                break;
            }
            case DELTAS: { // print the average deltas for each brand
                // declare arrays to store daily sales for each brand and daily deltas for ach brand
                int brandSales[NUM_OF_BRANDS][DAYS_IN_YEAR] = {};
                int brandDeltas[NUM_OF_BRANDS] = {};
                // calculate daily sales for each brand
                for (int i = 0; i < NUM_OF_BRANDS; ++i) // iterate over each brand
                    for (int j = 0; j < days[i]; ++j) // iterate over each day for the brand
                        for (int k = 0; k < NUM_OF_TYPES; ++k) // iterate over each car type for the day and brand
                            brandSales[i][j] += cube[j][i][k];

                // calculate daily deltas for each brand
                for (int i = 0; i < NUM_OF_BRANDS; ++i) // iterate over each brand
                    for (int j = 1; j < days[i]; ++j) // iterate over each day for the brand
                        brandDeltas[i] += brandSales[i][j] - brandSales[i][j - 1];

                // print average deltas for each brand
                for (int i = 0; i < NUM_OF_BRANDS; ++i) { // iterate over each brand
                    // print the average delta
                    printf("Brand: ");
                    printString(brands[i]); // (>_<)
                    printf(", Average Delta: %f\n",
                           (double) brandDeltas[i] / (days[i] - 1));
                }

                break;
            }
            case DONE:
                // Print a goodbye message and exit the program
                printf("Goodbye!\n");
                return 0;
            default:
                // Print an error message for invalid input
                printf("Invalid input\n");
        }
    }
}

/**
 * prints the menu into stdout
 */
void printMenu() {
    printf("Welcome to the Cars Data Cube! What would you like to do?\n"
           "1.Enter Daily Data For A Brand\n"
           "2.Populate A Day Of Sales For All Brands\n"
           "3.Provide Daily Stats\n"
           "4.Print All Data\n"
           "5.Provide Overall (simple) Insights\n"
           "6.Provide Average Delta Metrics\n"
           "7.exit\n");
}

/**
 * The function initializes all the values in {cube} to {EMPTY_CELL = -1}
 * @param cube the 3d-array that we want to initialize
 */
void initValues(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]) {
    for (int i = 0; i < DAYS_IN_YEAR; ++i) // iterate over each day in the year
        for (int j = 0; j < NUM_OF_BRANDS; ++j) // iterate over each brand
            for (int k = 0; k < NUM_OF_TYPES; ++k) // iterate over each car type for the day and brand
                cube[i][j][k] = EMPTY_CELL;
}

/**
 * The function sets the daily sales of first brand in first specific day
 * @param cube the 3d-array that we want to update the information in it
 * @param day the day which the info will be inserted in
 * @param brand the brand which the info will be inserted in
 * @param suvSales the daily sales of the SUV car type
 * @param sedanSales the daily sales of the SEDAN car type
 * @param coupeSales the daily sales of the COUPE car type
 * @param gtSales the daily sales of the GT car type
 */
void setSales(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day, int brand,
              int suvSales, int sedanSales, int coupeSales, int gtSales) {
    cube[day][brand][SUV] = suvSales;
    cube[day][brand][SEDAN] = sedanSales;
    cube[day][brand][COUPE] = coupeSales;
    cube[day][brand][GT] = gtSales;
}

/**
 * The function scans the daily sales of first brand for the next day
 * @param cube the 3d-array that we want to update the information in it
 * @param days the days which the info will be inserted in
 */
void scanBrand(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int days[NUM_OF_BRANDS]) {
    int brand, suvSales, sedanSales, coupeSales, gtSales;
    scanf(" %d %d %d %d %d", &brand, &suvSales, &sedanSales, &coupeSales, &gtSales); // get sales input

    if (brand >= NUM_OF_BRANDS || brand < 0) { // validate the input
        printf("This brand is not valid\n");
    } else {
        setSales(cube, days[brand], brand, // set sales according to the inputs
                 suvSales, sedanSales, coupeSales, gtSales);

        days[brand]++; // update the day
    }
}

/**
 * The function scans the daily sales of first brand for the next day, but accepts it iff the brand is enabled
 * @param cube the 3d-array that we want to update the information in it
 * @param days the days which the info will be inserted in
 * @param enabled the array which indicates the first brand is enabled to be scanned scanned before
 * @returns if the brand was successfully scanned
 */
bool scanEnabledBrands(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],
                       int days[NUM_OF_BRANDS], bool enabled[NUM_OF_BRANDS]) {
    int brand, suvSales, sedanSales, coupeSales, gtSales;
    scanf(" %d %d %d %d %d", &brand, &suvSales, &sedanSales, &coupeSales, &gtSales); // get sales input

    if (brand >= NUM_OF_BRANDS || brand < 0 || !enabled[brand]) { // validate the input
        printf("This brand is not valid\n");
        return false;
    } else {
        setSales(cube, days[brand], brand, // set sales according to the inputs
                 suvSales, sedanSales, coupeSales, gtSales);
        enabled[brand] = false; // disable another input for the same brand in this day
        days[brand]++; // update the day
        return true;
    }
}

/**
 * scans the given array and outputs the index of the max number in it
 * @param arr the array which will be scanned
 * @param size the size of {arr}
 * @returns the index of the max value in {arr}
 */
int indexOfMax(int arr[], int size) {
    int index = 0;
    for (int i = 1; i < size; ++i)
        if (arr[index] < arr[i])
            index = i;
    return index;
}

/**
 * scans the given array and outputs the index of the min number in it
 * @param arr the array which will be scanned
 * @param size the size of {arr}
 * @returns the index of the min value in {arr}
 */
int indexOfMin(int arr[], int size) {
    int index = 0;
    for (int i = 1; i < size; ++i)
        if (arr[index] > arr[i])
            index = i;
    return index;
}

/**
 * A task so simple, yet a trial so dire,       <br>
 * To print a string, a humble desire.          <br>
 * No %s to aid, no format specifier,           <br>
 * A cruel decree, programmer's mare.           <br>
 *                                              <br>
 * A for loop's toil, a %c's plight,            <br>
 * A character by character, a dismal sight.    <br>
 * No smickery, no hield, no ofold art,         <br>
 * A tintrey soul, a broken heart.              <br>
 *                                              <br>
 * Oh, cruel fate, set us in restrain,          <br>
 * To shackle our code, to cause such pain.     <br>
 * A simpler time, a bygone era,                <br>
 * When %s was mightened, and coding was fair.  <br>
 *                                              <br>
 * prints the string provided char by char (>_<).
 * @param str the provided string
 */
void printString(char str[]) {
    for (int i = 0; str[i] != '\0'; ++i) {
        printf("%c", str[i]);
    }
}