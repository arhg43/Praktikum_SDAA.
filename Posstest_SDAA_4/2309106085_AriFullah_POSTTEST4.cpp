#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

struct Barang {
    int id;
    string nama;
    int stok;
    float harga;
    Barang* next; 
};

Barang* head = nullptr;

struct StackNode {
    Barang* data;
    StackNode* next;
};
StackNode* top = nullptr; 

struct QueueNode {
    Barang* data;
    QueueNode* next;
};
QueueNode* front = nullptr; 
QueueNode* rear = nullptr; 

// Deklarasi fungsi
void printTableHeader();
void printTableFooter();
void tambahBarang();
void tampilBarang();
void editBarang();
void hapusBarang();
void pushStack(Barang* barang);
void printStack();
void enqueue(Barang* barang);
void printQueue();

// Fungsi untuk membuat tabel
void printTableHeader() {
    cout << "+-----+------------------------+-------+------------+" << endl;
    cout << "| ID  | Nama Barang            | Stok  | Harga (Rp)  |" << endl;
    cout << "+-----+------------------------+-------+------------+" << endl;
}

void printTableFooter() {
    cout << "+-----+------------------------+-------+------------+" << endl;
}

// Fungsi untuk menambahkan barang
void tambahBarang() {
    Barang* b = new Barang(); 
    cout << "Masukkan ID barang: ";
    cin >> b->id;
    cout << "Masukkan nama barang: ";
    cin.ignore();
    getline(cin, b->nama);
    cout << "Masukkan stok barang: ";
    cin >> b->stok;
    cout << "Masukkan harga barang: ";
    cin >> b->harga;
    b->next = nullptr;

    if (head == nullptr) {
        head = b;
    } else {
        Barang* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = b;
    }

    pushStack(b);
    enqueue(b);
    
    cout << "Barang berhasil ditambahkan!" << endl;
}

// Fungsi untuk menampilkan barang 
void tampilBarang() {
    if (head != nullptr) {
        printTableHeader();
        Barang* temp = head;
        while (temp != nullptr) {
            cout << "| " << setw(3) << temp->id
                 << " | " << setw(22) << temp->nama
                 << " | " << setw(5) << temp->stok
                 << " | " << setw(10) << fixed << setprecision(2) << temp->harga
                 << " |" << endl;
            temp = temp->next;
        }
        printTableFooter();
    } else {
        cout << "Tidak ada barang di dalam stok." << endl;
    }
}

// Fungsi untuk mengedit barang
void editBarang() {
    int id;
    cout << "Masukkan ID barang yang ingin diubah: ";
    cin >> id;

    Barang* temp = head;
    bool ditemukan = false;
    while (temp != nullptr) {
        if (temp->id == id) {
            cout << "Nama baru: ";
            cin.ignore();
            getline(cin, temp->nama);
            cout << "Stok baru: ";
            cin >> temp->stok;
            cout << "Harga baru: ";
            cin >> temp->harga;
            cout << "Barang berhasil diubah!" << endl;
            ditemukan = true;
            break;
        }
        temp = temp->next;
    }

    if (!ditemukan) {
        cout << "Barang dengan ID " << id << " tidak ditemukan." << endl;
    }
}

// Fungsi untuk menghapus barang
void hapusBarang() {
    int id;
    cout << "Masukkan ID barang yang ingin dihapus: ";
    cin >> id;

    Barang* temp = head;
    Barang* prev = nullptr;
    bool ditemukan = false;

    while (temp != nullptr) {
        if (temp->id == id) {
            if (prev == nullptr) {
                head = temp->next;
            } else {
                prev->next = temp->next;
            }
            
            cout << "Barang berhasil dihapus!" << endl;
            delete temp; 
            ditemukan = true;
            break;
        }
        prev = temp;
        temp = temp->next;
    }

    if (!ditemukan) {
        cout << "Barang dengan ID " << id << " tidak ditemukan." << endl;
    }
}

// Fungsi untuk menambahkan ke Stack
void pushStack(Barang* barang) {
    StackNode* newNode = new StackNode();
    newNode->data = barang;
    newNode->next = top;
    top = newNode;
}

// Fungsi untuk menampilkan Stack
void printStack() {
    if (top == nullptr) {
        cout << "Stack kosong." << endl;
        return;
    }
    cout << "\nData Barang di Stack (LIFO):\n";
    StackNode* temp = top;
    while (temp != nullptr) {
        cout << "ID: " << temp->data->id << ", Nama: " << temp->data->nama << endl;
        temp = temp->next;
    }
}

// Fungsi untuk menambahkan ke Queue
void enqueue(Barang* barang) {
    QueueNode* newNode = new QueueNode();
    newNode->data = barang;
    newNode->next = nullptr;
    if (rear == nullptr) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
}

// Fungsi untuk menampilkan Queue
void printQueue() {
    if (front == nullptr) {
        cout << "Queue kosong." << endl;
        return;
    }
    cout << "\nData Barang di Queue (FIFO):\n";
    QueueNode* temp = front;
    while (temp != nullptr) {
        cout << "ID: " << temp->data->id << ", Nama: " << temp->data->nama << endl;
        temp = temp->next;
    }
}

// Main program
int main() {
    int pilihan;
    do {
        cout << "\n========== Menu Toko Elektronik ==========\n";
        cout << "1. Tambah Barang\n";
        cout << "2. Tampilkan Barang\n";
        cout << "3. Edit Barang\n";
        cout << "4. Hapus Barang\n";
        cout << "5. Tampilkan Stack\n";
        cout << "6. Tampilkan Queue\n";
        cout << "7. Keluar\n";
        cout << "==========================================\n";
        cout << "Pilih menu: ";
        cin >> pilihan;
        
        switch (pilihan) {
            case 1:
                tambahBarang();
                break;
            case 2:
                tampilBarang();
                break;
            case 3:
                editBarang();
                break;
            case 4:
                hapusBarang();
                break;
            case 5:
                printStack();
                break;
            case 6:
                printQueue();
                break;
            case 7:
                cout << "Keluar dari program." << endl;
                break;
            default:
                cout << "Pilihan tidak valid!" << endl;
        }
    } while (pilihan != 7);

    return 0;
}
