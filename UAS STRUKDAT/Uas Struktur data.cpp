#include <iostream>
#include <string>
#include <vector>
#include <limits>

using namespace std;

struct Product {
    int id;
    string name;
    string price;
    int stock;
};

struct User {
    string username;
    string password;
};

vector<Product> products;
vector<User> users;

const string ADMIN_USERNAME = "ram";
const string ADMIN_PASSWORD = "xzlr4m";



void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int findProductById(int id) {
    for (int i = 0; i < products.size(); ++i) {
        if (products[i].id == id) {
            return i;
        }
    }
    return -1;
}

int findUserByUsername(const string& username) {
    for (int i = 0; i < users.size(); ++i) {
        if (users[i].username == username) {
            return i;
        }
    }
    return -1;
}
void addProduct() {
    Product newProduct;
    cout << "\n--- Tambah Produk ---\n";
    cout << "ID Produk: ";
    while (!(cin >> newProduct.id)) {
        cout << "ID harus berupa angka. Masukkan lagi: ";
        clearInputBuffer();
    }
    clearInputBuffer();
    cout << "Nama Produk: ";
    getline(cin, newProduct.name);
    cout << "Harga Produk: ";
    getline(cin, newProduct.price);
    cout << "Stok Produk: ";
    while (!(cin >> newProduct.stock)) {
        cout << "Stok harus berupa angka. Masukkan lagi: ";
        clearInputBuffer();
    }
    products.push_back(newProduct);
    cout << "Produk berhasil ditambahkan!\n";
}

void readProduct() {
    cout << "\n--- Lihat Produk ---\n";
    if (products.empty()) {
        cout << "Tidak ada produk yang tersedia.\n";
    } else {
        for (const auto& product : products) {
            cout << "ID: " << product.id << "\n";
            cout << "Nama: " << product.name << "\n";
            cout << "Harga: " << product.price << "\n";
            cout << "Stok: " << product.stock << "\n";
            cout << "------------------------\n";
        }
    }
}

void updateProduct() {
    int id;
    cout << "\n--- Ubah Produk ---\n";
    cout << "Masukkan ID produk yang akan diubah: ";
    while (!(cin >> id)) {
        cout << "ID harus berupa angka. Masukkan lagi: ";
        clearInputBuffer();
    }
    int index = findProductById(id);
    if (index != -1) {
        Product& product = products[index];
        cout << "Nama Baru (kosongkan jika tidak ingin mengubah): ";
        clearInputBuffer();
        string newName;
        getline(cin, newName);
        if (!newName.empty()) {
            product.name = newName;
        }
        cout << "Harga Baru (0 jika tidak ingin mengubah): ";
        string newPrice;
        clearInputBuffer();
        getline(cin, newPrice);
        if (!newPrice.empty() && newPrice != "0") {
            product.price = newPrice;
        }
        cout << "Stok Baru (0 jika tidak ingin mengubah): ";
        int newStock;
        if (cin >> newStock && newStock != 0) {
            product.stock = newStock;
        }
        cout << "Produk berhasil diubah!\n";
    } else {
        cout << "Produk dengan ID tersebut tidak ditemukan.\n";
    }
}

void deleteProduct() {
    int id;
    cout << "\n--- Hapus Produk ---\n";
    cout << "Masukkan ID produk yang akan dihapus: ";
    while (!(cin >> id)) {
        cout << "ID harus berupa angka. Masukkan lagi: ";
        clearInputBuffer();
    }
    int index = findProductById(id);
    if (index != -1) {
        products.erase(products.begin() + index);
        cout << "Produk berhasil dihapus!\n";
    } else {
        cout << "Produk dengan ID tersebut tidak ditemukan.\n";
    }
}
void registerUser() {
    User newUser;
    cout << "\n--- Registrasi Pengguna ---\n";
    cout << "Username: ";
    cin >> newUser.username;
    if (findUserByUsername(newUser.username) != -1) {
        cout << "Username sudah ada. Pilih username lain.\n";
        return;
    }
    cout << "Password: ";
    cin >> newUser.password;
    users.push_back(newUser);
    cout << "Registrasi berhasil!\n";
}

void login(bool& isLoggedIn, bool& isAdmin) {
    string username, password;
    cout << "\n--- Login ---\n";
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    if (username == ADMIN_USERNAME && password == ADMIN_PASSWORD) {
        cout << "Login berhasil sebagai admin!\n" << endl;
        isLoggedIn = true;
        isAdmin = true;
    } else if (findUserByUsername(username) != -1 && users[findUserByUsername(username)].password == password) {
        cout << "Login berhasil sebagai user!\n" << endl;
        isLoggedIn = true;
        isAdmin = false;
    } else {
        cout << "Login gagal. Periksa username dan password.\n" << endl;
        isLoggedIn = false;
    }
}
int main() {
    int choice;
    bool isLoggedIn = false;
    bool isAdmin = false;

    do {
        cout << "\n===== Toko Ram =====\n";
        cout << "\nMenu Utama\n";
        if (!isLoggedIn) {
            cout << "1. Login\n";
            cout << "2. Registrasi\n";
        } else {
            cout << "1. Lihat Produk\n";
            cout << "2. Tambah Produk\n";
            cout << "3. Ubah Produk\n";
            cout << "4. Hapus Produk\n";
            cout << "5. Logout\n";
            if (isAdmin) {
                cout << "\n--- Informasi Admin ---\n";
                cout << "Anda memiliki akses untuk menambah dan mengubah produk.\n";
            }
        }
        cout << "0. Keluar\n";
        cout << "Pilihan: ";
        while (!(cin >> choice)) {
            cout << "Pilihan harus berupa angka. Masukkan lagi: ";
            clearInputBuffer();
        }

        switch (choice) {
            case 1:
                if (!isLoggedIn) {
                    login(isLoggedIn, isAdmin);
                } else {
                    readProduct();
                }
                break;
            case 2:
                if (!isLoggedIn) {
                    registerUser();
                } else if (isAdmin) {
                    addProduct();
                } else {
                    cout << "Akses ditolak. Hanya admin yang dapat menambah produk.\n";
                }
                break;
            case 3:
                if (isLoggedIn) {
                    if (isAdmin) {
                        updateProduct();
                    } else {
                        cout << "Akses ditolak. Hanya admin yang dapat mengubah produk.\n";
                    }
                } else {
                    cout << "Anda harus login terlebih dahulu.\n";
                }
                break;
            case 4:
                if (isLoggedIn) {
                    deleteProduct();
                } else {
                    cout << "Anda harus login untuk menghapus produk.\n";
                }
                break;
            case 5:
                if (isLoggedIn) {
                    isLoggedIn = false;
                    isAdmin = false;
                    cout << "Logout berhasil.\n" << endl;
                } else {
                    cout << "Anda belum login.\n" << endl;
                }
                break;
            case 0:
                cout << "Keluar dari program.\n" << endl;
                break;
            default:
                cout << "Pilihan tidak valid.\n" << endl;
        }
    } while (choice != 0);

    return 0;
}
