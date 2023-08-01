#include <stdio.h>
#include <string.h>

#define MAX_CUSTOMERS 100
#define MAX_PRODUCTS 100

struct Product {
    char name[50];
    double price;
};

struct Customer {
    char name[50];
    char address[100];
    double balance;
};

struct Customer customers[MAX_CUSTOMERS];
struct Product products[MAX_PRODUCTS];
int numCustomers = 0;
int numProducts = 0;

// Function prototypes
void addCustomer();
void addProduct();
void generateBill(int customerIndex);
void makePayment(int customerIndex);

int main() {
    int choice, customerIndex;

    while (1) {
        printf("\nCustomer Billing System\n");
        printf("1. Add Customer\n");
        printf("2. Add Product\n");
        printf("3. Generate Bill\n");
        printf("4. Make Payment\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addCustomer();
                break;
            case 2:
                addProduct();
                break;
            case 3:
                printf("Enter customer index: ");
                scanf("%d", &customerIndex);
                generateBill(customerIndex);
                break;
            case 4:
                printf("Enter customer index: ");
                scanf("%d", &customerIndex);
                makePayment(customerIndex);
                break;
            case 5:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

void addCustomer() {
    if (numCustomers >= MAX_CUSTOMERS) {
        printf("Customer database is full. Cannot add more customers.\n");
        return;
    }

    struct Customer newCustomer;
    printf("Enter customer name: ");
    scanf(" %[^\n]", newCustomer.name);
    printf("Enter customer address: ");
    scanf(" %[^\n]", newCustomer.address);
    newCustomer.balance = 0.0;

    customers[numCustomers] = newCustomer;
    numCustomers++;

    printf("Customer added successfully!\n");
}

void addProduct() {
    if (numProducts >= MAX_PRODUCTS) {
        printf("Product database is full. Cannot add more products.\n");
        return;
    }

    struct Product newProduct;
    printf("Enter product name: ");
    scanf(" %[^\n]", newProduct.name);
    printf("Enter product price: ");
    scanf("%lf", &newProduct.price);

    products[numProducts] = newProduct;
    numProducts++;

    printf("Product added successfully!\n");
}

void generateBill(int customerIndex) {
    if (customerIndex < 0 || (customerIndex >= numCustomers) ){
        printf("Invalid customer index.\n");
        return;
    }

    struct Customer customer = customers[customerIndex];
    printf("Bill for Customer: %s\n", customer.name);

    double totalAmount = 0.0;
    int choice, quantity;
    do {
        printf("Available Products:\n");
        for (int i = 0; i < numProducts; i++) {
            printf("%d. %s - %.2f\n", i + 1, products[i].name, products[i].price);
        }
        printf("Enter product index (0 to exit): ");
        scanf("%d", &choice);

        if (choice > 0 && choice <= numProducts) {
            printf("Enter quantity: ");
            scanf("%d", &quantity);

            double productTotal = products[choice - 1].price * quantity;
            printf("Added %d x %s to the bill - %.2f\n", quantity, products[choice - 1].name, productTotal);

            totalAmount += productTotal;
        }
    } while (choice != 0);

    printf("Total amount to be paid: %.2f\n", totalAmount);
    customers[customerIndex].balance += totalAmount;
}

void makePayment(int customerIndex) {
    if (customerIndex < 0 || customerIndex >= numCustomers) {
        printf("Invalid customer index.\n");
        return;
    }

    struct Customer customer = customers[customerIndex];
    double paymentAmount;

    printf("Customer: %s\n", customer.name);
    printf("Current Balance: %.2f\n", customer.balance);
    printf("Enter payment amount: ");
    scanf("%lf", &paymentAmount);

    if (paymentAmount < customer.balance) {
        customer.balance -= paymentAmount;
        printf("Payment unsuccessful.More required amount is : %.2f\n", customer.balance);
    }
    else if(paymentAmount == customer.balance){
        printf("Payment successful...Thank you!");
    } else {
        printf("Payment amount exceeds the balance.\n");
        paymentAmount -= customer.balance ;
        printf("Payment successful.Your balance is: %.2f\n", paymentAmount);
    }
}
