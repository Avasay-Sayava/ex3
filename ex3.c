/******************
Name: Aviv Sayer
ID: 326552304
Assignment: ex3
*******************/

#include <stdio.h>

/*
 * it was very fun to write this hehe
 *
 * To whomever this concerns.
 * Whilst I have had many problems with the homework instructions, what I have come to realize is truly unacceptable.
 * I, an innocent programmer, was reading the instructions of an exercise,
 * when suddenly I saw that one can not use a library but <stdio.h>!
 * I burst into tear; (>_<) "I can not use the [bool] type!", said I, distraught.
 * Why hath this fate befallen me? For the bool type hath been taught to us,
 * so why should we not use it?
 * But alas! The word "bool" is defined verily in <stdbool.h>!
 * Do you now see the problem here inlies? Hark, for <stdbool.h> is not of <stdio.h>!
 * So why should we not use [_Bool], defined in C itself? We know in <stdbool.h>, [bool] is merely provided as:
 * ```c
 * #define bool         _Bool
 * ```
 * But here yet hides a tricky trap, for this, we have not yet learned!
 * What we have not learned we may not use; truly, woe is us.
 * This failing befuddles me, so in this work I do use [_Bool], defining it just as in <stdbool.h>.
 * In addition, the {true, false} values have thus been defined similarly.
 * I thank you for your consideration, dear respected faculty.
 */

#define bool            _Bool
#define true            1
#define false           0

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

int main() {
    int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES];
    int days[NUM_OF_BRANDS] = {};
    int choice;

    initValues(cube);

    while (true) {
        printMenu();
        scanf(" %d", &choice);

        switch (choice) {
            case ADD_ONE: // scan and add sales data for a single brand
                scanBrand(cube, days);
                break;
            case ADD_ALL: {
                int brandCount = NUM_OF_BRANDS;
                bool remainingBrands[NUM_OF_BRANDS];
                for (int i = 0; i < NUM_OF_BRANDS; ++i)
                    remainingBrands[i] = true;
                while (brandCount) {
                    printf("No data for brands");
                    for (int i = 0; i < NUM_OF_BRANDS; ++i)
                        if (remainingBrands[i])
                            printf(" %s", brands[i]);
                    printf(".\n"
                           "Please complete the data.\n");
                    brandCount -= scanEnabledBrands(cube, days, remainingBrands);
                }
                break;
            }
            case STATS: {
                int day;
                printf("What day would you like to analyze?\n");
                scanf(" %d", &day);

                while (day > 365 || day < 1 || days[indexOfMin(days, DAYS_IN_YEAR)] < day) {
                    printf("Please enter first valid day.\n"
                           "What day would you like to analyze?\n");
                    scanf(" %d", &day);
                }

                int salesSum = 0, brandSales[NUM_OF_BRANDS] = {}, typeSales[NUM_OF_TYPES] = {};
                for (int i = 0; i < NUM_OF_BRANDS; ++i) {
                    for (int j = 0; j < NUM_OF_TYPES; ++j) {
                        salesSum += cube[day - 1][i][j];
                        brandSales[i] += cube[day - 1][i][j];
                        typeSales[j] += cube[day - 1][i][j];
                    }
                }

                printf("In day number %d:\n"
                       "The sales total was %d\n"
                       "The best sold brand with %d sales was %s\n"
                       "The best sold type with %d sales was %s\n\n",
                       day, salesSum,
                       brandSales[indexOfMax(brandSales, NUM_OF_BRANDS)],
                       brands[indexOfMax(brandSales, NUM_OF_BRANDS)],
                       typeSales[indexOfMax(typeSales, NUM_OF_TYPES)],
                       types[indexOfMax(typeSales, NUM_OF_TYPES)]);

                break;
            }
            case PRINT: {
                printf("*****************************************\n\n");
                for (int i = 0; i < NUM_OF_BRANDS; ++i) {
                    printf("Sales for %s:\n", brands[i]);
                    for (int j = 0; j < days[i]; ++j) {
                        printf("Day %d-", j + 1);
                        for (int k = 0; k < NUM_OF_TYPES; ++k)
                            printf(" %s: %d", types[k], cube[j][i][k]);
                        printf("\n");
                    }
                }
                printf("\n\n*****************************************\n");

                break;
            }
            case INSIGHTS: {
                int brandSales[NUM_OF_BRANDS] = {}, typeSales[NUM_OF_TYPES] = {}, daySales[DAYS_IN_YEAR] = {};
                for (int i = 0; i < NUM_OF_BRANDS; ++i) {
                    for (int j = 0; j < days[i]; ++j) {
                        for (int k = 0; k < NUM_OF_TYPES; ++k) {
                            brandSales[i] += cube[j][i][k];
                            typeSales[k] += cube[j][i][k];
                            daySales[j] += cube[j][i][k];
                        }
                    }
                }

                printf("The best-selling brand overall is %s: %d$\n"
                       "The best-selling type of car is %s: %d$\n"
                       "The most profitable day was day number %d: %d$\n",
                       brands[indexOfMax(brandSales, NUM_OF_BRANDS)],
                       brandSales[indexOfMax(brandSales, NUM_OF_BRANDS)],
                       types[indexOfMax(typeSales, NUM_OF_TYPES)],
                       typeSales[indexOfMax(typeSales, NUM_OF_TYPES)],
                       indexOfMax(daySales, DAYS_IN_YEAR) + 1,
                       daySales[indexOfMax(daySales, DAYS_IN_YEAR)]);

                break;
            }
            case DELTAS: {
                int brandSales[NUM_OF_BRANDS][DAYS_IN_YEAR] = {};
                int brandDeltas[NUM_OF_BRANDS] = {};
                for (int i = 0; i < NUM_OF_BRANDS; ++i) {
                    for (int j = 0; j < days[i]; ++j) {
                        for (int k = 0; k < NUM_OF_TYPES; ++k) {
                            brandSales[i][j] += cube[j][i][k];
                        }
                    }
                }

                for (int i = 0; i < NUM_OF_BRANDS; ++i) {
                    for (int j = 1; j < days[i]; ++j) {
                        brandDeltas[i] += brandSales[i][j] - brandSales[i][j - 1];
                    }
                }

                for (int i = 0; i < NUM_OF_BRANDS; ++i) {
                    printf("Brand: %s, Average Delta: %f\n",
                           brands[i], (double) brandDeltas[i] / (days[i] - 1));
                }

                break;
            }
            case DONE:
                printf("Goodbye!\n");
                return 0;
            default:
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
    for (int i = 0; i < DAYS_IN_YEAR; ++i)
        for (int j = 0; j < NUM_OF_BRANDS; ++j)
            for (int k = 0; k < NUM_OF_TYPES; ++k)
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
    scanf(" %d %d %d %d %d", &brand, &suvSales, &sedanSales, &coupeSales, &gtSales);

    if (brand >= NUM_OF_BRANDS || brand < 0) {
        printf("This brand is not valid\n");
    } else {
        setSales(cube, days[brand], brand,
                 suvSales, sedanSales, coupeSales, gtSales);

        days[brand]++;
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
    scanf(" %d %d %d %d %d", &brand, &suvSales, &sedanSales, &coupeSales, &gtSales);

    if (brand >= NUM_OF_BRANDS || brand < 0 || !enabled[brand]) {
        printf("This brand is not valid\n");
        return false;
    } else {
        setSales(cube, days[brand], brand,
                 suvSales, sedanSales, coupeSales, gtSales);
        enabled[brand] = false;
        days[brand]++;
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
