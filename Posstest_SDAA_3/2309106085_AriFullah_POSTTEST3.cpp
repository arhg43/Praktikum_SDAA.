#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

// Struct untuk menyimpan data barang
struct Barang {
    int id;
    string nama;
    int stok;
    float harga;
    Barang* next; // Pointer untuk elemen berikutnya dalam linked list
};

// Pointer untuk head linked list
Barang* head = nullptr;

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
    Barang* b = new Barang(); // Alokasi memori untuk node baru
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

    // Jika list kosong, tambahkan sebagai head
    if (head == nullptr) {
        head = b;
    } else {
        // Jika tidak, tambahkan di akhir linked list
        Barang* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = b;
    }
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

    // Mencari barang dengan ID yang cocok
    while (temp != nullptr) {
        if (temp->id == id) {
            // Jika barang ditemukan di head
            if (prev == nullptr) {
                head = temp->next;
            } else {
                prev->next = temp->next;
            }
            delete temp; // Dealokasi memori
            cout << "Barang berhasil dihapus!" << endl;
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

// Main program
int main() {
    int pilihan;
    do {
        cout << "\n========== Menu Toko Elektronik ==========\n";
        cout << "1. Tambah Barang\n";
        cout << "2. Tampilkan Barang\n";
        cout << "3. Edit Barang\n";
        cout << "4. Hapus Barang\n";
        cout << "5. Keluar\n";
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
                cout << "Keluar dari program." << endl;
                break;
            default:
                cout << "Pilihan tidak valid!" << endl;
        }
    } while (pilihan != 5);

    return 0;
}
