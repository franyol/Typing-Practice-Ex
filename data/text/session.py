def summarize_sessions(sessions):
    summary = {}

    for session in sessions:
        user_id = session.get("user_id")
        duration = session.get("duration", 0)

        if user_id not in summary:
            summary[user_id] = {
                "total_time": 0,
                "visits": 0,
                "pages": []
            }

        summary[user_id]["total_time"] += duration
        summary[user_id]["visits"] += 1

        for page in session.get("pages", []):
            if page.get("active"):
                summary[user_id]["pages"].append(page.get("url"))

    result = []

    for user_id, data in summary.items():
        if data["total_time"] > 300:
            level = "heavy"
        elif data["total_time"] > 100:
            level = "medium"
        else:
            level = "light"

        result.append({
            "user": user_id,
            "level": level,
            "visits": data["visits"]
        })

    return result


output = summarize_sessions(logs)
print(output)
