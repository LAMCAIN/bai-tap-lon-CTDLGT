#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
#include <algorithm> // thư viện để chuyển chữ hoa

using namespace std;

const int VIEW = 1, EDIT = 2, EXPORT = 4, DELETE = 8;

struct Role 
{
    string roleName;
    int permissions;
};

struct User 
{
    string username;
    size_t passwordHash;
    string roleName;
};

// --- HASH TABLE ---
template <typename T>
struct Node 
{
    string key;
    T data;
    Node* next;
    Node(string k, T d) : key(k), data(d), next(nullptr) {}
};

template <typename T>
class SimpleHash 
{
private:
    static const int SIZE = 20;
    Node<T>* table[SIZE];
    int hashFunc(string s) 
    {
        int h = 0;
        for (char c : s) h = (h * 31 + c) % SIZE;
        return h;
    }
public:
    SimpleHash() { for (int i = 0; i < SIZE; i++) table[i] = nullptr; }

    void clear() 
    {
        for (int i = 0; i < SIZE; i++) 
        {
            Node<T>* current = table[i];
            while (current) 
            {
                Node<T>* toDelete = current;
                current = current->next;
                delete toDelete;
            }
            table[i] = nullptr;
        }
    }

    void insert(string k, T d) 
    {
        int h = hashFunc(k);
        Node<T>* newNode = new Node<T>(k, d);
        newNode->next = table[h];
        table[h] = newNode;
    }
    T* find(string k) 
    {
        int h = hashFunc(k);
        Node<T>* temp = table[h];
        while (temp) 
        {
            if (temp->key == k) return &(temp->data);
            temp = temp->next;
        }
        return nullptr;
    }
};

class LabManager 
{
private:
    vector<User> users;
    SimpleHash<User> userMap;
    SimpleHash<Role> roleMap;
    User* currentUser = nullptr;

    size_t simpleHash(string pass) 
    {
        size_t h = 5381;
        for (char c : pass) h = ((h << 5) + h) + c;
        return h;
    }

    // Hàm phụ trợ chuyển chuỗi thành chữ hoa để tránh lỗi nhập "user" vs "USER"
    string toUpper(string s) 
    {
        for (auto& c : s) c = toupper(c);
        return s;
    }

public:
    void loadData() 
    {
        users.clear();
        userMap.clear();
        roleMap.clear(); // Quan trọng: Reset role map mỗi lần nạp

        // Khởi tạo các Role hợp lệ vào bảng băm Role
        roleMap.insert("ADMIN", { "ADMIN", VIEW | EDIT | EXPORT | DELETE });
        roleMap.insert("USER", { "USER", VIEW | EXPORT });

        ifstream f("users.txt");
        if (!f.is_open()) 
        {
            User admin = { "admin", simpleHash("123"), "ADMIN" };
            users.push_back(admin);
            userMap.insert("admin", admin);
            saveToFile();
        }
        else 
        {
            string u, r; size_t h;
            while (f >> u >> h >> r) 
            {
                User user = { u, h, r };
                users.push_back(user);
                userMap.insert(u, user);
            }
            f.close();
        }
    }

    void saveToFile() 
    {
        ofstream f("users.txt");
        for (const auto& u : users) 
        {
            f << u.username << " " << u.passwordHash << " " << u.roleName << endl;
        }
        f.close();
    }

    bool login(string u, string p) 
    {
        User* found = userMap.find(u);
        if (found && found->passwordHash == simpleHash(p)) 
        {
            currentUser = found;
            return true;
        }
        return false;
    }

    void createNewUser(string u, string p, string r) 
    {
        if (!currentUser || currentUser->roleName != "ADMIN") 
        {
            cout << "Loi: Chi ADMIN moi co quyen nay!\n";
            return;
        }

        // Chuẩn hóa role nhập vào thành chữ hoa (USER/ADMIN)
        string upperRole = toUpper(r);

        // Kiểm tra xem Role nhập vào có tồn tại trong hệ thống không
        if (roleMap.find(upperRole) == nullptr) 
        {
            cout << "Loi: Role '" << r << "' khong hop le! (Chi nhan ADMIN hoac USER)\n";
            return;
        }

        if (userMap.find(u)) 
        {
            cout << "Loi: Username da ton tai!\n";
            return;
        }

        User newUser = { u, simpleHash(p), upperRole };
        users.push_back(newUser);
        userMap.insert(u, newUser);
        saveToFile();
        cout << "Tao user " << u << " voi quyen " << upperRole << " thanh cong.\n";
    }

    void exportReport() 
    {
        if (!currentUser) return;
        Role* r = roleMap.find(currentUser->roleName);
        if (r && (r->permissions & EXPORT)) 
        {
            ofstream f("report.csv");
            f << "Username,Role\n";
            for (auto& u : users) f << u.username << "," << u.roleName << "\n";
            f.close();
            cout << "Xuat file report.csv thanh cong!\n";
        }
        else 
        {
            cout << "Tu choi: Role " << currentUser->roleName << " khong co quyen EXPORT.\n";
        }
    }
};

int main() {
    LabManager lab;
    lab.loadData();

    int choice;
    while (true) 
    {
        cout << "\n=== QLY PHONG LAB ===\n1. Dang nhap\n2. Tao User (Chon ADMIN/USER)\n3. Xuat bao cao\n4. Thoat\nChon: ";
        if (!(cin >> choice)) break;

        if (choice == 1) 
        {
            string u, p;
            cout << "User: "; cin >> u;
            cout << "Pass: "; cin >> p;
            if (lab.login(u, p)) cout << "Dang nhap thanh cong!\n";
            else cout << "Sai thong tin!\n";
        }
        else if (choice == 2) 
        {
            string u, p, r;
            cout << "Username moi: "; cin >> u;
            cout << "Pass moi: "; cin >> p;
            cout << "Role (ADMIN hoặc USER): "; cin >> r;
            lab.createNewUser(u, p, r);
        }
        else if (choice == 3) 
        {
            lab.exportReport();
        }
        else if (choice == 4) break;
    }
    return 0;
}