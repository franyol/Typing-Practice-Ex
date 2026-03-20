function processOrders(orders) {
    const validOrders = orders
        .filter(order => order.status === "completed")
        .map(order => ({
            id: order.id,
            total: order.items.reduce((sum, item) => {
                if (item.price > 0) {
                    return sum + item.price * item.quantity;
                }
                return sum;
            }, 0),
            customer: {
                name: order.customer.firstName + " " + order.customer.lastName,
                email: order.customer.email
            }
        }));

    return validOrders.sort((a, b) => {
        if (a.total > b.total) {
            return -1;
        } else if (a.total < b.total) {
            return 1;
        }
        return 0;
    });
}

const result = processOrders(orderList);
console.log(result);
