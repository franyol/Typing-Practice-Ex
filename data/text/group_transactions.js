function groupTransactions(transactions) {
    const result = {};

    transactions.forEach(tx => {
        const key = tx.type + ":" + tx.currency;

        if (!result[key]) {
            result[key] = {
                count: 0,
                total: 0,
                items: []
            };
        }

        if (tx.amount > 0) {
            result[key].count += 1;
            result[key].total += tx.amount;
            result[key].items.push({
                id: tx.id,
                amount: tx.amount,
                date: tx.date
            });
        }
    });

    return Object.keys(result).map(key => {
        const entry = result[key];

        if (entry.total > 1000) {
            return { key: key, level: "high", data: entry };
        } else if (entry.total > 100) {
            return { key: key, level: "medium", data: entry };
        }

        return { key: key, level: "low", data: entry };
    });
}

const grouped = groupTransactions(data);
console.log(grouped);
