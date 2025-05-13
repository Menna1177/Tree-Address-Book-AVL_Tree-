# AVL Tree Address Book

This project is a simple console-based **Address Book application** built using C++ and implemented with an **AVL Tree** data structure to manage contacts efficiently. Each contact is uniquely identified by an integer ID, and the tree remains balanced to ensure optimal search, insertion, and deletion performance.

---

## 🧠 Features

- Add a new contact with name, phone number, and email.
- Search for a contact by ID.
- Delete a contact by ID.
- List all contacts in ascending order of ID (in-order traversal).
- Display the AVL tree structure in a visualized format.
- Choose to input test cases manually or load them from a file (`test_cases.txt`).

---

## 🛠 How It Works

The core logic is based on an **AVL tree**, which is a self-balancing binary search tree. After each insertion or deletion, the tree automatically balances itself to maintain `O(log n)` performance.

### Contact Structure:
Each node in the AVL tree represents a contact and stores:
- `ID` (unique key)
- `Name`
- `Phone`
- `Email`

---

## 📂 Files

- `main.cpp` – The complete source code.
- `test_cases.txt` – (Optional) A file containing a predefined list of test inputs.
- `README.md` – This file.

---

## 📋 Example Menu

```
Address Book Application
------------------------
1. Add New Contact
2. Search for Contact
3. Delete Contact
4. List All Contacts (Sorted by ID)
5. Display Current Tree Structure
6. Exit
```

---

## 📎 Sample Input File (`test_cases.txt`)

```txt
1
101
Alice
01012345678
alice@example.com
1
202
Bob
01187654321
bob@example.com
4
2
101
3
202
5
6
```

To load this automatically, choose option `2` in the menu and ensure the file is named `test_cases.txt` and is in the same directory as the executable.

---

## 🚀 How to Compile

Use a C++ compiler like `g++` or any IDE (e.g., CLion, Code::Blocks):

```bash
g++ main.cpp -o address_book
./address_book
```

---

## 🧪 How to Test

You can either:
- Manually input the test cases via the console (Option 1), **OR**
- Load them from a file named `test_cases.txt` (Option 2)

---

## 👨‍💻 Author

Developed as a student project to demonstrate AVL tree applications in a real-world scenario.

---

## 📜 License

This project is intended for educational purposes only.
