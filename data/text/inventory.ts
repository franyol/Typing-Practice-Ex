type Product = {
    id: number;
    name: string;
    price: number;
    quantity: number;
};

function calculateInventory(products: Product[]): number {
    let totalValue = 0;

    for (const product of products) {
        if (product.quantity > 0) {
            totalValue += product.price * product.quantity;
        }
    }

    return totalValue;
}

function formatProducts(products: Product[]): string[] {
    return products.map(product => {
        const value = product.price * product.quantity;

        if (value > 100) {
            return `${product.name} (high value)`;
        } else if (value > 50) {
            return `${product.name} (medium value)`;
        }

        return `${product.name} (low value)`;
    });
}

const total = calculateInventory(items);
const labels = formatProducts(items);
console.log(total, labels);
