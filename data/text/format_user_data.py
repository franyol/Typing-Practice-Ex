def format_user_data(users):
    result = []
    for user in users:
        if user["active"]:
            name = user["first_name"] + " " + user["last_name"]
            result.append({
                "name": name,
                "email": user["email"]
            })
    return result

print(format_user_data(data))
