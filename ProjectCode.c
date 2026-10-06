#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PRODUCTS 100
#define MAX_SUPPLIERS 50

// Product structure
struct Product
{
    int productId;
    char productName[50];
    int supplierId;
    int quantity;
    float price;
    int reorderLevel;
    int sales[6];
};

// Supplier structure
struct Supplier
{
    int supplierId;
    char supplierName[50];
    char contact[20];
};

// Global arrays
struct Product products[MAX_PRODUCTS];
struct Supplier suppliers[MAX_SUPPLIERS];

int productCount = 0;
int supplierCount = 0;


// ---------------- PRODUCT MANAGEMENT ----------------

void addProduct()
{
    int i;

    if (productCount >= MAX_PRODUCTS)
    {
        printf("\nProduct storage is full!\n");
        return;
    }

    printf("\nEnter Product ID: ");
    scanf("%d", &products[productCount].productId);

    for (i = 0; i < productCount; i++)
    {
        if (products[i].productId == products[productCount].productId)
        {
            printf("Product ID already exists!\n");
            return;
        }
    }

    printf("Enter Product Name: ");
    scanf(" %49[^\n]", products[productCount].productName);

    printf("Enter Supplier ID: ");
    scanf("%d", &products[productCount].supplierId);

    printf("Enter Quantity: ");
    scanf("%d", &products[productCount].quantity);

    printf("Enter Price: ");
    scanf("%f", &products[productCount].price);

    printf("Enter Reorder Level: ");
    scanf("%d", &products[productCount].reorderLevel);

    printf("\nEnter sales for last 6 months:\n");

    for (i = 0; i < 6; i++)
    {
        printf("Month %d: ", i + 1);
        scanf("%d", &products[productCount].sales[i]);
    }

    productCount++;

    printf("\nProduct added successfully!\n");
}


void displayProducts()
{
    int i;

    if (productCount == 0)
    {
        printf("\nNo products available.\n");
        return;
    }

    printf("\n--------------- PRODUCT LIST ---------------\n");

    printf("ID\tName\t\tSupplier\tQuantity\tPrice\n");

    for (i = 0; i < productCount; i++)
    {
        printf("%d\t%-15s\t%d\t\t%d\t\t%.2f\n",
               products[i].productId,
               products[i].productName,
               products[i].supplierId,
               products[i].quantity,
               products[i].price);
    }
}


// ---------------- SUPPLIER MANAGEMENT ----------------

void addSupplier()
{
    int i;

    if (supplierCount >= MAX_SUPPLIERS)
    {
        printf("\nSupplier storage is full!\n");
        return;
    }

    printf("\nEnter Supplier ID: ");
    scanf("%d", &suppliers[supplierCount].supplierId);

    for (i = 0; i < supplierCount; i++)
    {
        if (suppliers[i].supplierId == suppliers[supplierCount].supplierId)
        {
            printf("Supplier ID already exists!\n");
            return;
        }
    }

    printf("Enter Supplier Name: ");
    scanf(" %49[^\n]", suppliers[supplierCount].supplierName);

    printf("Enter Contact Number: ");
    scanf("%19s", suppliers[supplierCount].contact);

    supplierCount++;

    printf("\nSupplier added successfully!\n");
}


void displaySuppliers()
{
    int i;

    if (supplierCount == 0)
    {
        printf("\nNo suppliers available.\n");
        return;
    }

    printf("\n--------------- SUPPLIER LIST ---------------\n");

    printf("ID\tSupplier Name\t\tContact\n");

    for (i = 0; i < supplierCount; i++)
    {
        printf("%d\t%-20s\t%s\n",
               suppliers[i].supplierId,
               suppliers[i].supplierName,
               suppliers[i].contact);
    }
}


// ---------------- INVENTORY MANAGEMENT ----------------

void updateStock()
{
    int id, quantity, i, found = 0;

    printf("\nEnter Product ID: ");
    scanf("%d", &id);

    for (i = 0; i < productCount; i++)
    {
        if (products[i].productId == id)
        {
            printf("Current Stock: %d\n", products[i].quantity);

            printf("Enter quantity to add: ");
            scanf("%d", &quantity);

            if (quantity <= 0)
            {
                printf("Enter a positive quantity!\n");
                return;
            }

            products[i].quantity += quantity;

            printf("\nStock updated successfully!\n");
            printf("New Stock: %d\n", products[i].quantity);

            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("\nProduct not found!\n");
    }
}


void displayInventory()
{
    int i;

    if (productCount == 0)
    {
        printf("\nInventory is empty.\n");
        return;
    }

    printf("\n--------------- INVENTORY ---------------\n");

    printf("ID\tProduct\t\tQuantity\tPrice\tReorder Level\n");

    for (i = 0; i < productCount; i++)
    {
        printf("%d\t%-15s\t%d\t\t%.2f\t%d\n",
               products[i].productId,
               products[i].productName,
               products[i].quantity,
               products[i].price,
               products[i].reorderLevel);
    }
}


// ---------------- LOW STOCK ALERT ----------------

void lowStockAlert()
{
    int i, found = 0;

    printf("\n--------------- LOW STOCK PRODUCTS ---------------\n");

    for (i = 0; i < productCount; i++)
    {
        if (products[i].quantity <= products[i].reorderLevel)
        {
            printf("Product ID: %d\n", products[i].productId);
            printf("Product Name: %s\n", products[i].productName);
            printf("Current Stock: %d\n", products[i].quantity);
            printf("Reorder Level: %d\n\n", products[i].reorderLevel);

            found = 1;
        }
    }

    if (!found)
    {
        printf("No products are currently low in stock.\n");
    }
}


// ---------------- AI DATA CREATION ----------------

void createCSV()
{
    FILE *fp = fopen("sales.csv", "w");

    int i, j;

    if (fp == NULL)
    {
        printf("Cannot create CSV file!\n");
        return;
    }

    fprintf(fp, "id,name,m1,m2,m3,m4,m5,m6,stock\n");

    for (i = 0; i < productCount; i++)
    {
        fprintf(fp, "%d,%s",
                products[i].productId,
                products[i].productName);

        for (j = 0; j < 6; j++)
        {
            fprintf(fp, ",%d", products[i].sales[j]);
        }

        fprintf(fp, ",%d\n", products[i].quantity);
    }

    fclose(fp);
}


// ---------------- AI DEMAND FORECASTING ----------------

void forecastDemand()
{
    int result;

    if (productCount == 0)
    {
        printf("\nNo products available!\n");
        return;
    }

    createCSV();

    printf("\nStarting AI Demand Forecasting...\n");

    result = system("py forecast.py");

    if (result != 0)
    {
        printf("\nAI execution failed!\n");
        printf("Check Python installation and libraries.\n");
    }
}


// ---------------- MAIN FUNCTION ----------------

int main()
{
    int choice;

    while (1)
    {
        printf("\n==============================================\n");
        printf(" SMART INVENTORY AND WAREHOUSE MANAGEMENT\n");
        printf("==============================================\n");

        printf("1. Add Product\n");
        printf("2. Display Products\n");
        printf("3. Add Supplier\n");
        printf("4. Display Suppliers\n");
        printf("5. Update Stock\n");
        printf("6. Display Inventory\n");
        printf("7. Low Stock Alert\n");
        printf("8. AI Demand Forecasting\n");
        printf("9. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                addProduct();
                break;

            case 2:
                displayProducts();
                break;

            case 3:
                addSupplier();
                break;

            case 4:
                displaySuppliers();
                break;

            case 5:
                updateStock();
                break;

            case 6:
                displayInventory();
                break;

            case 7:
                lowStockAlert();
                break;

            case 8:
                forecastDemand();
                break;

            case 9:
                printf("\nExiting program...\n");
                return 0;

            default:
                printf("\nInvalid choice! Please try again.\n");
        }
    }

    return 0;
}