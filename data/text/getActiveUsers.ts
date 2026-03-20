type User = {
    id: number;
    name: string;
    isActive: boolean;
};

function getActiveUsers(users: User[]): User[] {
    return users.filter(user => user.isActive);
}

const active = getActiveUsers(allUsers);
