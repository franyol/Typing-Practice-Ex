function calculateTotal(items) {
    return items
        .filter(item => item.price > 10)
        .map(item => ({
            name: item.name,
            total: item.price * item.quantity
        }))
        .reduce((acc, curr) => acc + curr.total, 0);
}

const result = calculateTotal(cartItems);
console.log(result);