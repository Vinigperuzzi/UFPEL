#include <stdio.h>
#include <math.h>
#define NUMCITY 10
#define LANDSIZE 100
#define square(A) ((A) * (A))

typedef int City[2];

void generate(City cities[]);
void print_cities(City cities[]);
float distance(City city1, City city2);
void copy_tour(City citiesDest[], City citiesSource[]);
void copy_City(City dest, City source);
void swap_cities(City city1, City city2);
void circ_perm(City cities[], int numCities);
void scramble(City cities[], City *pivot, int numCities);
void target_function(City cities[]);
float tour_length(City cities[]);

float shortestTourLength;
City shortestTour[NUMCITY];

int main()
{
    City cities[NUMCITY]; /*create array of cities */
    generate(cities); /* fill it */
    shortestTourLength = tour_length(cities);
    copy_tour(shortestTour, cities);
    scramble(cities, cities, NUMCITY);
    printf("found the shortest tour:\n");
    print_cities(shortestTour);
    printf("Length is: %f\n", shortestTourLength);
    return 0;
}

float tour_length(City cities[])
{
    int i;
    float length = 0.0;
    for(i = 0; i < NUMCITY - 1; i++)
        length += distance(cities[i], cities[i+1]);
    length += distance(cities[NUMCITY - 1], cities[0]);
    return length;
}

void target_function(City cities[])
{
    float length;
    length = tour_length(cities);
    if (length < shortestTourLength) {
        shortestTourLength = length;
        copy_tour(shortestTour, cities);
    }
}

/*pivot is the base address in the cities[NUMCITY] array
 *for the recursive scrambling; the only reason we also
 *pass the unchanged cities address is because we need it
 *to call the target function (which does *something* to
 *the scrambled array) at each recursive call to scramble
 */
void scramble(City cities[], City *pivot, int numCities)
{
    int i;
    City *newPivot;
    if (numCities <= 1) { //Scrambled! Call the target function
        target_function(cities);
        return;
    }
    for (i = 0; i < numCities; i++) {
        newPivot = &pivot[1];
        scramble(cities, newPivot, numCities - 1);
        circ_perm(pivot, numCities);
    }
}

void circ_perm(City cities[], int numCities)
{
    int i;
    City tmp;
    copy_City(tmp, cities[0]);
    for (i = 0; i < numCities - 1; i++)
        copy_City(cities[i], cities[i + 1]);
    copy_City(cities[numCities - 1], tmp);
}

void copy_tour(City citiesDest[], City citiesSource[])
{
    int i;
    for (i = 0; i < NUMCITY; i++)
        copy_City(citiesDest[i], citiesSource[i]);
}

void copy_City(City dest, City source)
{
    dest[0] = source[0];
    dest[1] = source[1];
}

void swap_cities(City city1, City city2)
{
    City tmp;
    copy_City(tmp, city1);
    copy_City(city1, city2);
    copy_City(city2, tmp);
}

float distance(City city1, City city2)
{
    float result;
    result = sqrtf((float)square(city2[0] - city1[0]) +
                 (float)square(city2[1] - city1[1]));
    return result;
}

void generate(City cities[])
{
  cities[0][0] = 1;
  cities[0][1] = 2;
  cities[1][0] = 1;
  cities[1][1] = 1;
  cities[2][0] = 1;
  cities[2][1] = 1;
  cities[3][0] = 1;
  cities[3][1] = 1;
  cities[4][0] = 1;
  cities[4][1] = 1;
  cities[5][0] = 1;
  cities[5][1] = 1;
  cities[6][0] = 1;
  cities[6][1] = 1;
  cities[7][0] = 1;
  cities[7][1] = 1;
  cities[8][0] = 1;
  cities[8][1] = 1;
  cities[9][0] = 1;
  cities[9][1] = 1;
  //  int i, j;
  //  for (i = 0; i < NUMCITY; i++)
  //      for (j = 0; j < 2; j++)
  //          cities[i][j] = rand() % LANDSIZE;
}

void print_cities(City cities[])
{
    int i;
    for (i = 0; i < NUMCITY; i++) {
        printf("(%d,%d)", cities[i][0], cities[i][1]);
        if (i < NUMCITY - 1)
            printf(" , ");
    }
    printf("\n");
}