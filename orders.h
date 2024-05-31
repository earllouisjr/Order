#include <string>
#include <stdint.h>

class product {
    uint16_t sku;
    std::string name;
    float price;
public:
    product(uint16_t, std::string, float);
    std::string getName() {return name;}
    float getPrice() {return price;}
    friend product* find_product(int sku);
    void print();
};

class item {
    uint16_t sku;
    uint16_t quantity;
public:
    item(uint16_t, uint16_t);
    void print();
    float cost();
};

class item_list {
    item **items;
    uint16_t num_products;
public:
    item_list();
    void add(const item&);
    void print();
};

class order 
{
    uint16_t order_id;
    std::string customer_name;
    item_list product_items;
public:
    void addItem(const item&);
    void print();
    order(uint16_t, std::string);
};

order** read_orders(const char* filename, uint16_t* num_orders);

