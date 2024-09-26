#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable: 4996) // required by Visual Studio

#define MAX_RECORDS 100
#define RECORD_SIZE 256
#define FILENAME "products.dat"

typedef struct {
    int productId;
    char name[50];
    char category[50];
    int quantity;
    float price;
} Product;


//Function prototypes
void addProduct(const char* filename, int position, Product product);
void searchRecordByPosition(const char* filename, int position);
void updateProduct(const char* filename, int position, Product product);
int calculateHash(int position);
//add delete

void addProduct(const char* filename, int position, Product product) {
    FILE* file = fopen(filename, "ab");
    if (file == NULL) {
        printf("Cannot open file");
        exit(EXIT_FAILURE);
    }
    int whereToWriteTheRecord = calculateHash(position);
    fseek(file, whereToWriteTheRecord, SEEK_SET);
    fwrite(&product, sizeof(Product), 1, file);
    fclose(file);
}

void searchRecordByPosition(const char* filename, int position) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Cannot open file");
        exit(EXIT_FAILURE);
    }
    int whereToReadTheRecord = calculateHash(position);
    fseek(file, whereToReadTheRecord, SEEK_SET);
    Product product;
    fread(&product, sizeof(Product), 1, file);
    fclose(file);
}

void updateProduct(const char* filename, int position, Product product) {
    FILE* file = fopen(filename, "rb+");
    if (file == NULL) {
        printf("Cannot open file");
        exit(EXIT_FAILURE);
    }
    int whereToReadTheRecord = calculateHash(position);
    fseek(file, whereToReadTheRecord, SEEK_SET);
    fwrite(&product, sizeof(Product), 1, file);
    fclose(file);
}

int calculateHash(int position) {
    return position * sizeof(Product);
}