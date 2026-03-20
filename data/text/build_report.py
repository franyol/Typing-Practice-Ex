def build_report(users):
    report = []

    for user in users:
        if not user.get("active"):
            continue

        full_name = user["first_name"] + " " + user["last_name"]
        total_spent = 0

        for order in user.get("orders", []):
            for item in order.get("items", []):
                if item["price"] > 0:
                    total_spent += item["price"] * item["quantity"]

        report.append({
            "name": full_name,
            "email": user.get("email"),
            "total": total_spent,
            "order_count": len(user.get("orders", []))
        })

    return sorted(report, key=lambda x: x["total"], reverse=True)


final_report = build_report(data)
print(final_report)
