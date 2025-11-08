#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Weather {
    char city[50];
    float temperature;
    int humidity;
    char condition[50];
};

void addReport();
void displayAll();
void searchReport();

int main() {
    int choice;
    while (1) {
        printf("\n==============================\n");
        printf("      WEATHER REPORT SYSTEM\n");
        printf("==============================\n");
        printf("1. Add Weather Report\n");
        printf("2. View All Reports\n");
        printf("3. Search by City\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addReport();
                break;
            case 2:
                displayAll();
                break;
            case 3:
                searchReport();
                break;
            case 4:
                printf("\nExiting program. Goodbye!\n");
                exit(0);
            default:
                printf("\nInvalid choice! Try again.\n");
        }
    }
    return 0;
}

void addReport() {
    FILE *fp;
    struct Weather w;

    fp = fopen("weather.txt", "a");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("\nEnter city name: ");
    scanf(" %[^\n]", w.city);
    printf("Enter temperature (°C): ");
    scanf("%f", &w.temperature);
    printf("Enter humidity (%%): ");
    scanf("%d", &w.humidity);
    printf("Enter condition (e.g., Sunny, Rainy): ");
    scanf(" %[^\n]", w.condition);

    fprintf(fp, "%s %.2f %d %s\n", w.city, w.temperature, w.humidity, w.condition);
    fclose(fp);

    printf("\nWeather report added successfully!\n");
}

void displayAll() {
    FILE *fp;
    struct Weather w;

    fp = fopen("weather.txt", "r");
    if (fp == NULL) {
        printf("No data found! Please add some reports first.\n");
        return;
    }

    printf("\n---- All Weather Reports ----\n");
    printf("%-15s %-12s %-10s %-15s\n", "City", "Temp(°C)", "Humidity", "Condition");
    printf("--------------------------------------------------------\n");

    while (fscanf(fp, "%s %f %d %s", w.city, &w.temperature, &w.humidity, w.condition) != EOF) {
        printf("%-15s %-12.2f %-10d %-15s\n", w.city, w.temperature, w.humidity, w.condition);
    }

    fclose(fp);
}

void searchReport() {
    FILE *fp;
    struct Weather w;
    char searchCity[50];
    int found = 0;

    fp = fopen("weather.txt", "r");
    if (fp == NULL) {
        printf("No data available to search.\n");
        return;
    }

    printf("\nEnter city name to search: ");
    scanf(" %[^\n]", searchCity);

    while (fscanf(fp, "%s %f %d %s", w.city, &w.temperature, &w.humidity, w.condition) != EOF) {
        if (strcasecmp(w.city, searchCity) == 0) {
            printf("\nWeather Report for %s:\n", w.city);
            printf("Temperature: %.2f °C\n", w.temperature);
            printf("Humidity: %d %%\n", w.humidity);
            printf("Condition: %s\n", w.condition);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("\nNo report found for '%s'\n", searchCity);

    fclose(fp);
}

