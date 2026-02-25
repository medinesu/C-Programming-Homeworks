#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "products.dat"

struct Product {
    int id;
    char name[20];
    float price;
    int stock;
};

void menu();
void addProduct();
void updateProduct();
void showProducts();
void deleteProduct();

int main() {
    menu();
    return 0;
}

void menu() {
    int choice;
    while (1) {
        printf("\n---- Product Management ----\n");
        printf("1. Add Product\n");
        printf("2. Update Stock\n");
        printf("3. Show Products\n");
        printf("4. Delete Product\n");
        printf("5. Exit\n");
        printf("Your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addProduct();
                break;
            case 2:
                updateProduct();
                break;
            case 3:
                showProducts();
                break;
            case 4:
                deleteProduct();
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}

void addProduct() {
    struct Product p;
    FILE *file = fopen(FILE_NAME, "ab");
    if (file == NULL) {
        printf("File could not be opened.\n");
        return;
    }

    printf("Product ID: ");
    scanf("%d", &p.id);
    printf("Product name: ");
    scanf("%s", p.name);
    printf("Product price: ");
    scanf("%f", &p.price);
    printf("Stock amount: ");
    scanf("%d", &p.stock);

    fwrite(&p, sizeof(struct Product), 1, file);
    fclose(file);
    printf("Product added successfully.\n");
}

void updateProduct() {
    struct Product p;
    int id, newStock;
    FILE *file = fopen(FILE_NAME, "rb+");
    if (file == NULL) {
        printf("File could not be opened.\n");
        return;
    }

    printf("Enter ID of the product to update: ");
    scanf("%d", &id);

    int found = 0;
    while (fread(&p, sizeof(struct Product), 1, file)) {
        if (p.id == id) {
            printf("New stock amount: ");
            scanf("%d", &newStock);
            p.stock = newStock;

            fseek(file, -sizeof(struct Product), SEEK_CUR);
            fwrite(&p, sizeof(struct Product), 1, file);
            printf("Stock updated.\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Product not found.\n");
    }

    fclose(file);
}

void showProducts() {
    struct Product p;
    FILE *file = fopen(FILE_NAME, "rb");
    if (file == NULL) {
        printf("File could not be opened.\n");
        return;
    }

    printf("\n--- Registered Products ---\n");
    while (fread(&p, sizeof(struct Product), 1, file)) {
        if (p.id != -1) {
            printf("ID: %d | Name: %s | Price: %.2f | Stock: %d\n",
                   p.id, p.name, p.price, p.stock);
        }
    }

    fclose(file);
}

void deleteProduct() {
    struct Product p;
    int id;
    FILE *file = fopen(FILE_NAME, "rb+");
    if (file == NULL) {
        printf("File could not be opened.\n");
        return;
    }

    printf("Enter ID of the product to delete: ");
    scanf("%d", &id);

    int found = 0;
    while (fread(&p, sizeof(struct Product), 1, file)) {
        if (p.id == id) {
            p.id = -1;  // Logical deletion
            fseek(file, -sizeof(struct Product), SEEK_CUR);
            fwrite(&p, sizeof(struct Product), 1, file);
            printf("Product deleted.\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Product not found.\n");
    }

    fclose(file);
}
