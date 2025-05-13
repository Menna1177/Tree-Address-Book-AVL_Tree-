#include <bits/stdc++.h>
using namespace std;

class node
{
public:
    string name;
    string phone;
    string email;
    int ID;
    int height;
    node* left;
    node* right;

    node(string name, string phone, string email, int ID)
    {
        this->name = name;
        this->phone = phone;
        this->email = email;
        this->ID = ID;
        left = nullptr;
        right = nullptr;
        height = 1;
    }
};

class AvlAdressBook
{
    node* root = nullptr;

    int maX(node* current)
    {
        if(current->right == nullptr) return current->ID;
        else return maX(current->right);
    }

    int height(node* current)
    {
        if(current == nullptr) return 0;
        return current->height;
    }

    node* rightRotation(node* current)
    {
        node* newNode = current->left;
        current->left = newNode->right;
        newNode->right = current;
        current->height = 1 + max(height(current->left), height(current->right));
        newNode->height = 1 + max(height(newNode->left), height(newNode->right));
        return newNode;
    }

    node* leftRotation(node* current)
    {
        node* newNode = current->right;
        current->right = newNode->left;
        newNode->left = current;
        current->height = 1 + max(height(current->left), height(current->right));
        newNode->height = 1 + max(height(newNode->left), height(newNode->right));
        return newNode;
    }

    void inOrder(node* current)
    {
        if(current == nullptr)
        {
            return;
        }
        inOrder(current->left);
        cout << "ID: " << current->ID << ", Name: " << current->name
             << ", Phone: " << current->phone << ", Email: " << current->email << endl;
        inOrder(current->right);
    }

    node* insert(node* current, int ID, string email, string phone, string name)
    {
        if(current == nullptr)
        {
            node* newNode = new node(name, phone, email, ID);
            return newNode;
        }
        if(ID < current->ID) current->left = insert(current->left, ID, email, phone, name);
        else if(ID > current->ID) current->right = insert(current->right, ID, email, phone, name);
        else return current; // Duplicate IDs not allowed

        current->height = 1 + max(height(current->left), height(current->right));
        int balance = height(current->left) - height(current->right);

        // Left Left Case
        if(balance > 1 && ID < current->left->ID)
            return rightRotation(current);

        // Right Right Case
        if(balance < -1 && ID > current->right->ID)
            return leftRotation(current);

        // Left Right Case
        if(balance > 1 && ID > current->left->ID)
        {
            current->left = leftRotation(current->left);
            return rightRotation(current);
        }

        // Right Left Case
        if(balance < -1 && ID < current->right->ID)
        {
            current->right = rightRotation(current->right);
            return leftRotation(current);
        }

        return current;
    }

    node* minValueNode(node* current)
    {
        node* temp = current;
        while(temp->left != nullptr)
            temp = temp->left;
        return temp;
    }
    node* removeUtility(node* current, int Id) {
        // إذا كانت الشجرة فارغة
        if (current == NULL) {
            cout << "Tree is Empty" << endl;
            return NULL;
        }

        if (Id < current->ID) {
            current->left = removeUtility(current->left, Id);
        } else if (Id > current->ID) {
            current->right = removeUtility(current->right, Id);
        } else {

            if (current->left == NULL && current->right == NULL) {
                delete current;
                return NULL;
            }

            else if (current->left != NULL && current->right != NULL) {

                int max = maX(current->left);
                current->ID = max;
                current->left = removeUtility(current->left, max);
            }

            else {
                node* child = current;
                if (current->right != NULL) {
                    current = current->right;
                } else {
                    current = current->left;
                }

                delete child;
            }
        }

        current->height = 1 + max(height(current->left), height(current->right));


        int balance = height(current->left) - height(current->right);

        if (balance > 1 && Id < current->left->ID) {
            return rightRotation(current);
        }

        if (balance > 1 && Id > current->left->ID) {
            current->left = leftRotation(current->left);
            return rightRotation(current);
        }

        if (balance < -1 && Id > current->right->ID) {
            return leftRotation(current);
        }

        if (balance < -1 && Id < current->right->ID) {
            current->right = rightRotation(current->right);
            return leftRotation(current);
        }

        return current;
    }


    node* search(node* current, int ID)
    {
        if(current == nullptr || current->ID == ID)
            return current;

        if(current->ID < ID)
            return search(current->right, ID);

        return search(current->left, ID);
    }




    int getHeight(node* root) {
        if (root == nullptr) return 0;
        int lh = getHeight(root->left);
        int rh = getHeight(root->right);
        return 1 + (lh > rh ? lh : rh);
    }


    void printSpaces(int count) {
        for (int i = 0; i < count; i++) cout << ' ';
    }


    void printNode(node* n) {
        if (n == nullptr) cout << "   ";
        else {
            if (n->ID < 10) cout << " " << n->ID << " ";
            else if (n->ID < 100) cout << " " << n->ID;
            else cout << n->ID;
        }
    }

    void displayTreeStructure(node* root) {
        int h = getHeight(root);
        int maxNodes = (int)pow(2, h + 1);

        node** levelNodes = new node*[maxNodes];
        for (int i = 0; i < maxNodes; i++) levelNodes[i] = nullptr;

        levelNodes[0] = root;
        int level = 0;
        int count = 1;

        while (count > 0 && level < h) {
            int nextCount = 0;
            int nodesInLevel = (int)pow(2, level);
            int spaceBetween = (int)pow(2, h - level) - 1;
            int leadingSpace = spaceBetween / 2;

            printSpaces(leadingSpace * 3);

            for (int i = 0; i < nodesInLevel; i++) {
                node* current = levelNodes[i];
                printNode(current);
                printSpaces(spaceBetween * 3);

                if (i * 2 + 1 < maxNodes) {
                    if (current != nullptr) {
                        levelNodes[nodesInLevel + i * 2] = current->left;
                        levelNodes[nodesInLevel + i * 2 + 1] = current->right;
                        if (current->left != nullptr || current->right != nullptr)
                            nextCount++;
                    } else {
                        levelNodes[nodesInLevel + i * 2] = nullptr;
                        levelNodes[nodesInLevel + i * 2 + 1] = nullptr;
                    }
                }
            }

            cout << "\n\n";
            for (int i = 0; i < maxNodes - nodesInLevel; i++) {
                levelNodes[i] = levelNodes[nodesInLevel + i];
            }

            level++;
            count = nextCount;
        }

        delete[] levelNodes;
    }

/*void displayTreeStructure() {
    if (root == nullptr) {
        cout << "Tree is empty." << endl;
        return;
    }
    cout << "Current AVL Tree:" << endl;
    printTreeStructure(root);
    cout << endl;
}*/
public:
    void insert(int ID, string name, string phone, string email)
    {
        root = insert(root, ID, email, phone, name);
    }

    void remove(int ID)
    {
        root = removeUtility(root, ID);
    }

    void display()
    {
        cout << "Address Book Contents (In-order traversal):" << endl;
        inOrder(root);
        cout << endl;
    }

    void searchContact(int ID)
    {
        node* result = search(root, ID);
        if(result == nullptr)
            cout << "Contact with ID " << ID << " not found." << endl;
        else
            cout << "Found Contact - ID: " << result->ID << ", Name: " << result->name
                 << ", Phone: " << result->phone << ", Email: " << result->email << endl;
    }
    void showMenu()
    {
        int choice;
        do {
            cout << "\nAddress Book Application\n";
            cout << "------------------------\n";
            cout << "1. Add New Contact\n";
            cout << "2. Search for Contact\n";
            cout << "3. Delete Contact\n";
            cout << "4. List All Contacts (Sorted by ID)\n";
            cout << "5. Display Current Tree Structure\n";
            cout << "6. Exit\n";
            cout << "------------------------\n";
            cout << "Enter operation (1-6): ";
            cin >> choice;

            switch(choice)
            {
                case 1: {
                    int id;
                    string name, phone, email;
                    cout << "Enter unique ID (integer): ";
                    cin >> id;
                    cin.ignore();
                    cout << "Enter name: ";
                    getline(cin, name);
                    cout << "Enter phone: ";
                    getline(cin, phone);
                    cout << "Enter email: ";
                    getline(cin, email);

                    node* existing = search(root, id);
                    if(existing != nullptr) {
                        cout << "Error: Contact with ID " << id << " already exists.\n";
                    } else {
                        insert(id, name, phone, email);
                        cout << "Contact added successfully.\n";
                    }
                    break;
                }
                case 2: {
                    int id;
                    cout << "Enter ID to search: ";
                    cin >> id;
                    node* result = search(root, id);
                    if(result == nullptr) {
                        cout << "Contact not found.\n";
                    } else {
                        cout << "\nContact found:\n";
                        cout << "ID: " << result->ID << "\n";
                        cout << "Name: " << result->name << "\n";
                        cout << "Phone: " << result->phone << "\n";
                        cout << "Email: " << result->email << "\n";
                    }
                    break;
                }
                case 3: {
                    int id;
                    cout << "Enter ID to delete: ";
                    cin >> id;
                    node* existing = search(root, id);
                    if(existing == nullptr) {
                        cout << "Contact not found.\n";
                    } else {
                        remove(id);
                        cout << "Contact deleted successfully.\n";
                    }
                    break;
                }
                case 4: {
                    cout << "\nContacts in Address Book (sorted by ID):\n";
                    if(root == nullptr) {
                        cout << "Address Book is empty.\n";
                    } else {
                        inOrder(root);
                    }
                    break;
                }
                case 5: {
                    cout << "\nCurrent AVL Tree:\n";
                    if(root == nullptr) {
                        cout << "Tree is empty.\n";
                    } else {
                        displayTreeStructure(root);
                    }
                    break;
                }
                case 6: {
                    cout << "Exiting...\n\n";
                    break;
                }
                default: {
                    cout << "Invalid choice. Please try again.\n";
                }
            }
        } while(choice != 6);
    }
};

int main()
{
    cout << "   --Hello--  \n";
    int choice;

    do {
        AvlAdressBook book;
        cout << "Would you like to input your test cases\n1. manual\n2. from file\n3. Exit\nselect (1-3): ";
        cin >> choice;

        switch (choice) {
            case 1: {
                book.showMenu();
                break;
            }
            case 2: {
                ifstream file("test_cases.txt");
                if (!file.is_open()) {
                    cout << "Failed to open test_cases.txt\n";
                    break;
                }

                streambuf* originalCin = cin.rdbuf();
                cin.rdbuf(file.rdbuf());

                book.showMenu();
                cin.rdbuf(originalCin);
                file.close();
                break;
            }
            case 3: {
                cout << "Exiting...\n\n";
                break;
            }
            default: {
                cout << "Invalid choice. Please try again.\n";
            }
        }

    } while (choice != 3);


}
