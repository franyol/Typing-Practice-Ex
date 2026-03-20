interface Order {
    id: number;
    user: string;
    items: { price: number; quantity: number }[];
}

function computeOrders(orders: Order[]): string[] {
    return orders.map(order => {
        const total = order.items.reduce((acc, item) => {
            if (item.quantity > 0) {
                return acc + item.price * item.quantity;
            }
            return acc;
        }, 0);

        if (total > 200) {
            return `${order.user}: premium (${total})`;
        } else if (total > 50) {
            return `${order.user}: regular (${total})`;
        }

        return `${order.user}: basic (${total})`;
    });
}

function filterOrders(orders: Order[]): Order[] {
    return orders.filter(order => {
        return order.items.some(item => item.price > 10);
    });
}

const filtered = filterOrders(allOrders);
const labels = computeOrders(filtered);
console.log(labels);
