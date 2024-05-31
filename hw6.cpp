#include <stdio.h>
#include "orders.h"

using namespace std;

product products[] = {
    product(1234, "Bread", 2.99),
    product(5678, "Milk", 4.19),
    product(9012, "Eggs", 3.49),
    product(3456, "Butter", 3.99),
    product(7890, "Juice", 2.49),
    product(2345, "Muffin", 1.49)
};

product* find_product(int sku)
{
    // complete the find_product function.  Iterate 
    // through the products array and return the product 
    // that has the matching sku
	for (int i=0;i<sizeof(products);i++) {
		if (products[i].sku == sku) {return &products[i];}
		}
	return nullptr;
	}


// write the product constructor and the following methods:
// order::print(), item_list::print(), item::total(), 
// item::print()
product::product(uint16_t s, string n, float p)
: sku(s), name(n), price(p)
{
}

float item::cost() {
    return quantity * find_product(sku)->getPrice();
}

void item::print() {
    printf("%s  %d  %.2f  %.2f\n", find_product(sku)->getName().c_str(), quantity, find_product(sku)->getPrice(), cost()); 
}

void item_list::print() {
    float total = 0.0;
    for (int i = 0; i < num_products; i++) {
        items[i]->print();
        total += items[i]->cost();
    }
    printf("Total = %.2f\n\n", total);
}
	
void order::print() {
    printf("Order ID: %d\n", order_id);
    printf("Name: %s\n", customer_name.c_str());
    product_items.print();
}

int main()
{
    uint16_t num_orders;
    order** orders = read_orders("orders.db", &num_orders);
    if (orders == NULL) {
        printf("Order database does not exist\n");
    }

    // iterate over orders array and call
    // the print method for each order
	for (int i = 0; i < num_orders; i++) {
        orders[i]->print();
    }

    // Free memory
    for (int i = 0; i < num_orders; i++) {
        delete orders[i];
    }
    delete[] orders;

    return 0;
}
