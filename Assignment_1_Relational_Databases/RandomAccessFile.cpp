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
Product searchRecordByPosition(const char* filename, int position);
void updateProduct(const char* filename, int position, Product product);
void deleteProduct(const char* filename, int position);
int calculateHash(int position);
//add delete

void addProduct(const char* filename, int productId, Product product) {
    FILE* file = fopen(filename, "ab");
    // change postion for product Id check if the product Id is 0 and check if there is another one with the same product id.
   // (if there is nothing with that product then create the product, else return error)
    if (productId == 0) {
        printf("You cant add a product with product Id = 0\n");
        exit(EXIT_FAILURE);
    }

    if (file == NULL) {
        printf("Cannot open file");
        exit(EXIT_FAILURE);
    }
    int whereToWriteTheRecord = calculateHash(productId);
    if (fseek(file, whereToWriteTheRecord, SEEK_SET) != 0) {
        printf("Error seeking to the position %d. \n", whereToWriteTheRecord);
        exit(EXIT_FAILURE);
    }
    if (fwrite(&product, sizeof(Product), 1, file) != 1) {
        printf("Error writing to the file\n");
        exit(EXIT_FAILURE);
    }
    if (fclose(file) != 0) {
        printf("Error closing the file\n");
        exit(EXIT_FAILURE);
    }
}

Product searchRecordByPosition(const char* filename, int position) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Cannot open file");
        exit(EXIT_FAILURE);
    }
    int whereToReadTheRecord = calculateHash(position);
    if (fseek(file, whereToReadTheRecord, SEEK_SET) != 0) {
        printf("Error seeking to the position %d. \n", whereToReadTheRecord);
        exit(EXIT_FAILURE);
    }
    Product product;
    if (fread(&product, sizeof(Product), 1, file) != 0) {
        printf("Error reading the file");
        exit(EXIT_FAILURE);
    }//error cheking
    if (fclose(file) != 0) {
        printf("Error closing the file\n");
        exit(EXIT_FAILURE);
    }
    return product;
}

void updateProduct(const char* filename, int position, Product product) {
    FILE* file = fopen(filename, "rb+");
    if (file == NULL) {
        printf("Cannot open file");
        exit(EXIT_FAILURE);
    }
    int whereToReadTheRecord = calculateHash(position);
    if(fseek(file, whereToReadTheRecord, SEEK_SET) != 0) {
        printf("Error seeking to the position %d. \n", whereToReadTheRecord);
        exit(EXIT_FAILURE);
    }
   if (fwrite(&product, sizeof(Product), 1, file) != 1) {
       printf("Error writing to the file\n");
       exit(EXIT_FAILURE);
    }
    if (fclose(file) != 0) {
        printf("Error closing the file\n");
        exit(EXIT_FAILURE);
    }
}

void deleteProduct(const char* filename, int position) {
    FILE* file = fopen(filename, "rb+");
    if (file == NULL) {
        printf("Cannot open file");
        exit(EXIT_FAILURE);
    }
    int whereToDeleteTheRecord = calculateHash(position);
   if (fseek(file, whereToDeleteTheRecord, SEEK_SET) != 0) {
       printf("Error seeking to the position \n");
       exit(EXIT_FAILURE);
   }

    Product deletedProduct = { -1, "", "", 0, 0.0 };  // Mark as deleted
    if (fwrite(&deletedProduct, sizeof(Product), 1, file) != 1) {
        printf("Error writing to the file\n");
        exit(EXIT_FAILURE);
    }

    printf("Product at position %d has been deleted.\n", position);
    if (fclose(file) != 0) {
        printf("Error closing the file\n");
        exit(EXIT_FAILURE);
    }
}

int calculateHash(int position) {
    return position * sizeof(Product);
}


