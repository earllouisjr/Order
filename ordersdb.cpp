#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>

#include "orders.h"

item::item(uint16_t s, uint16_t q)
: sku(s), quantity(q)
{
}

item_list::item_list()
: items(NULL), num_products(0)
{
}

void item_list::add(const item& i)
{
    items = (item**)realloc(items, (num_products+1)*sizeof(item*));
    items[num_products] = new item(i);
    num_products++;
}

order::order(uint16_t o, std::string n)
: order_id(o), customer_name(n)
{
}

void order::addItem(const item& i)
{
    product_items.add(i);
}

order** read_orders(const char* filename, uint16_t* num_orders)
{
    int fd;
    fd = open(filename, O_RDONLY);
    int err = fd;
    if (err == -1) {
        return NULL;
    }

    read(fd, num_orders, sizeof(*num_orders));
    order** orders = new order*[*num_orders];

    for (int i=0; i<*num_orders; i++) {
        uint16_t order_id;
	uint16_t num_products;

        read(fd, &order_id, sizeof(order_id));

        uint32_t sz;
        read(fd, &sz, sizeof(sz));
        char customer_name[sz+1];
        read(fd, customer_name, sz);
        customer_name[sz] = 0;
        orders[i] = new order(order_id, customer_name);

        read(fd, &num_products, sizeof(num_products));

        for (int j=0; j<num_products; j++) {
            short sku;
            short quantity;
            read(fd, &sku, sizeof(sku));
            read(fd, &quantity, sizeof(quantity));
            item it(sku, quantity);
            orders[i]->addItem(it);
        }
    }

    close(fd);
    return orders;
}

