# Bank Management System & Currency Exchange 🏦💱

A console-based banking and currency exchange system written in C++.
I built it after learning object-oriented programming, to practise classes,
inheritance, encapsulation, file handling and design patterns. It was
challenging, and I'm proud of it.

## Screenshots
![Login screen](screenshots/login.png)
![Main menu](screenshots/main-menu.png)
![Currency calculator](screenshots/currency-calculator.png)

## Features
- 🔐 Login system with password obfuscation (Caesar cipher, see note below)
- 👥 Client management: add, delete, update, find, list
- 💰 Transactions: deposit, withdraw, transfer (with logging)
- 👤 User management with role-based permissions (bitmasks)
- 📋 Audit logs: login register and transfer log
- 💱 Currency exchange: list, find, update rates, calculator

## How to Run
Requires Windows and Visual Studio.
1. Clone the repository.
2. Open `BankProjectPremium.vcxproj` in Visual Studio.
3. Build and run (Ctrl+F5).
4. Log in with one of the demo accounts below.

## Demo Accounts
These are test accounts only, not real credentials.

| Username | Password |
|----------|----------|
| User1    | Pass1234 |
| User2    | Pass1234 |
| User3    | Pass1234 |
| User4    | Pass1234 |
| User5    | Word5555 |
| User6    | Bank4323 |

## Security Note
Passwords are stored with a Caesar cipher to practise encryption logic.
This is **not secure**. A real system would use salted password hashing
(for example bcrypt or Argon2). I'm aware of this limitation and plan to
learn proper hashing.

## Tech Stack
- Language: C++
- IDE: Visual Studio
- Storage: text files (.txt)

## What I Learned
- Object-oriented programming: inheritance and encapsulation
- File handling in C++
- Design patterns (Factory method)
- Permission systems using bitmasks
- Caesar cipher and why it is not real security
- Currency conversion logic

## Possible Improvements
- Replace the Caesar cipher with proper password hashing
- Replace text files with a database (e.g. SQLite)
- Add unit tests
