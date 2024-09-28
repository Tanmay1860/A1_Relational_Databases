#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 50
#define MAX_CATEGORY_LEN 50

// Define the product structure
typedef struct {
    int productId;
    char name[MAX_NAME_LEN];
    char category[MAX_CATEGORY_LEN];
    int quantity;
    float price;
} Product;
void addProduct(Product product);
void readProducts();
void updateProduct(int productId, Product updatedProduct);
void deleteProduct(int productId);
int loadProducts(Product products[]);

int menuSequentialAccess() 
    int choice, id;
    Product product, updatedProduct;
while (1) {
    printf("\nInventory Management System\n");
    printf("1. Add Product\n");
    printf("2. Read Products\n");
    printf("3. Update Product\n");
    printf("4. Delete Product\n");
    printf("5. Exit\n");
    printf("Choose an option: ");
    scanf("%d", &choice);
    getchar();

    switch (choice) {
    case 1:
        printf("Enter Product ID: ");
        scanf("%d", &product.productId);
        getchar();
        printf("Enter Name: ");
        fgets(product.name, sizeof(product.name), stdin);
        product.name[strcspn(product.name, "\n")] = 0;
        printf("Enter Category: ");
        fgets(product.category, sizeof(product.category), stdin);
        product.category[strcspn(product.category, "\n")] = 0;
        printf("Enter Quantity: ");
        scanf("%d", &product.quantity);
        printf("Enter Price: ");
        scanf("%f", &product.price);
        addProduct(product);
        break;

                case 2:
            readProducts();
            break;

        case 3:
            printf("Enter Product ID to update: ");
            scanf("%d", &id);
            getchar();
            printf("Enter new Name: ");
            fgets(updatedProduct.name, sizeof(updatedProduct.name), stdin);
            updatedProduct.name[strcspn(updatedProduct.name, "\n")] = 0;
            printf("Enter new Category: ");
            fgets(updatedProduct.category, sizeof(updatedProduct.category), stdin);
            updatedProduct.category[strcspn(updatedProduct.category, "\n")] = 0;
            printf("Enter new Quantity: ");
            scanf("%d", &updatedProduct.quantity);
            printf("Enter new Price: ");
            scanf("%f", &updatedProduct.price);
            updateProduct(id, updatedProduct);
            break;

        case 4:
            printf("Enter Product ID to delete: ");
            scanf("%d", &id);
            deleteProduct(id);
            break;

        case 5:
            exit(0);
        default:
            printf("Invalid option\n");
        }
    }
    return 0;
}

void addProduct(Product product) {
    FILE* file = fopen(FILENAME, "a");
    if (!file) {
        perror("Cannot open file");
        return;
    }

    fprintf(file, "%d %s %s %d %.2f\n", product.productId, product.name, product.category, product.quantity, product.price);
    fclose(file);
    printf("Product added successfully.\n");
}

void readProducts() {
    FILE* file = fopen(FILENAME, "r");
    if (!file) {
        perror("Cannot open file");
        return;
    }

    Product product;
    while (fscanf(file, "%d %49s %49s %d %f", &product.productId, product.name, product.category, &product.quantity, &product.price) == 5) {
        printf("ID: %d, Name: %s, Category: %s, Quantity: %d, Price: %.2f\n",
            product.productId, product.name, product.category, product.quantity, product.price);
    }

    fclose(file);
}

void updateProduct(int productId, Product updatedProduct) {
    Product products[MAX_RECORDS];
    int count = loadProducts(products);
    int found = 0;

    for (int i = 0; i < count; i++) {
        if (products[i].productId == productId) {
            products[i] = updatedProduct;
            found = 1;
            break;
        }
    }

    if (found) {
        FILE* file = fopen(FILENAME, "w");
        for (int i = 0; i < count; i++) {
            fprintf(file, "%d %s %s %d %.2f\n", products[i].productId, products[i].name, products[i].category, products[i].quantity, products[i].price);
        }
        fclose(file);
        printf("Product updated successfully.\n");
    }
    else {
        printf("Product not found.\n");
    }
}

void deleteProduct(int productId) {
    Product products[MAX_RECORDS];
    int count = loadProducts(products);
    int found = 0;

    for (int i = 0; i < count; i++) {
        if (products[i].productId == productId) {
            for (int j = i; j < count - 1; j++) {
                products[j] = products[j + 1];
            }
            count--;
            found = 1;
            break;
        }
    }

    if (found) {
        FILE* file = fopen(FILENAME, "w");
        for (int i = 0; i < count; i++) {
            fprintf(file, "%d %s %s %d %.2f\n", products[i].productId, products[i].name, products[i].category, products[i].quantity, products[i].price);
        }
        fclose(file);
        printf("Product deleted successfully.\n");
    }
    else {
        printf("Product not found.\n");
    }
}

int loadProducts(Product products[]) {
    FILE* file = fopen(FILENAME, "r");
    if (!file) {
        perror("Cannot open file");
        return 0;
    }

    int count = 0;
    while (fscanf(file, "%d %49s %49s %d %f", &products[count].productId, products[count].name, products[count].category, &products[count].quantity, &products[count].price) == 5) {
        count++;
    }

    fclose(file);
    return count;
}
 gsdfcsdgkjc