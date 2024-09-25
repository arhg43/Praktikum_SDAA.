#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

const int MAX_BARANG = 100;

// Struct untuk menyimpan data barang
struct Barang {
    int id;
    string nama;
    int stok;
    float harga;
};

// Array barang dengan ukuran maksimum
Barang listBarang[MAX_BARANG];
int jumlahBarang = 0;

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
    if (jumlahBarang < MAX_BARANG) {
        Barang* b = &listBarang[jumlahBarang];
        cout << "Masukkan ID barang: ";
        cin >> b->id;
        cout << "Masukkan nama barang: ";
        cin.ignore();
        getline(cin, b->nama);
        cout << "Masukkan stok barang: ";
        cin >> b->stok;
        cout << "Masukkan harga barang: ";
        cin >> b->harga;
        jumlahBarang++;
        cout << "Barang berhasil ditambahkan!" << endl;
    } else {
        cout << "Stok penuh, tidak bisa menambah barang lagi." << endl;
    }
}

// Fungsi untuk menampilkan barang 
void tampilBarang() {
    if (jumlahBarang > 0) {
        printTableHeader();
        for (int i = 0; i < jumlahBarang; i++) {
            Barang* b = &listBarang[i];
            cout << "| " << setw(3) << b->id 
                 << " | " << setw(22) << b->nama
                 << " | " << setw(5) << b->stok
                 << " | " << setw(10) << fixed << setprecision(2) << b->harga 
                 << " |" << endl;
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
    bool ditemukan = false;
    
    for (int i = 0; i < jumlahBarang; i++) {
        Barang* b = &listBarang[i];
        if (b->id == id) {
            cout << "Nama baru: ";
            cin.ignore();
            getline(cin, b->nama);
            cout << "Stok baru: ";
            cin >> b->stok;
            cout << "Harga baru: ";
            cin >> b->harga;
            cout << "Barang berhasil diubah!" << endl;
            ditemukan = true;
            break;
        }
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
    bool ditemukan = false;
    
    for (int i = 0; i < jumlahBarang; i++) {
        if (listBarang[i].id == id) {
            for (int j = i; j < jumlahBarang - 1; j++) {
                listBarang[j] = listBarang[j + 1];
            }
            jumlahBarang--;
            cout << "Barang berhasil dihapus!" << endl;
            ditemukan = true;
            break;
        }
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
