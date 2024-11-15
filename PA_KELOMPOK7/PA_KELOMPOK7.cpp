#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

struct Peminjam {
    string id;
    string nama;
    string no_hp;
    string no_ktp;
    string alamat;
    string buku;
    string batas_pengembalian;
    Peminjam* next;
};

void hapusPeminjam(Peminjam*& head, const string& id);
void hapusPeminjamBerdasarkanID(Peminjam*& head);


// Prosedur untuk menambahkan data peminjam ke dalam linked list
void tambahPeminjam(Peminjam*& head) {
    Peminjam* baru = new Peminjam;
    cout << "Masukkan ID Peminjam: ";
    cin >> baru->id;
    cin.ignore();  // Mengabaikan karakter newline yang tertinggal setelah cin

    // Memastikan ID tidak duplikat
    Peminjam* temp = head;
    while (temp != nullptr) {
        if (temp->id == baru->id) {
            cout << "ID sudah ada, masukkan ID lain!" << endl;
            delete baru;
            return;
        }
        temp = temp->next;
    }

    cout << "Masukkan Nama Peminjam: ";
    getline(cin, baru->nama);  

    // Validasi input untuk No HP (hanya angka)
    while (true) {
        cout << "Masukkan No HP: ";
        cin >> baru->no_hp;
        if (baru->no_hp.find_first_not_of("0123456789") == string::npos) {
            break;
        } else {
            cout << "No HP hanya boleh berisi angka!" << endl;
        }
    }

    // Validasi input untuk No KTP (hanya angka)
    while (true) {
        cout << "Masukkan No KTP: ";
        cin >> baru->no_ktp;
        if (baru->no_ktp.find_first_not_of("0123456789") == string::npos) {
            break;
        } else {
            cout << "No KTP hanya boleh berisi angka!" << endl;
        }
    }

    cin.ignore();  // Mengabaikan karakter newline setelah input No KTP

    cout << "Masukkan Alamat: ";
    getline(cin, baru->alamat);  

    cout << "Masukkan Buku yang Dipinjam: ";
    getline(cin, baru->buku);  

    cout << "Masukkan Batas Pengembalian: ";
    getline(cin, baru->batas_pengembalian);  

    baru->next = nullptr;

    if (head == nullptr) {
        head = baru;
    } else {
        Peminjam* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = baru;
    }

    cout << "Data peminjam berhasil ditambahkan!" << endl;
}

// Prosedur untuk menampilkan semua data peminjam dalam bentuk tabel menggunakan | dan =
void tampilkanPeminjam(Peminjam* head) {
    if (head == nullptr) {
        cout << "Tidak ada data peminjam!" << endl;
        return;
    }

    // Menampilkan header tabel
    cout << "==================================================================================================================================" << endl;
    cout << "| ID   | Nama              | No HP       | Alamat                  | No KTP        | Buku yang Dipinjam  | Batas Pengembalian    |" << endl;
    cout << "==================================================================================================================================" << endl;

    // Menampilkan data peminjam dalam tabel
    Peminjam* temp = head;
    while (temp != nullptr) {
        cout << "| " << left << setw(5) << temp->id
             << "| " << setw(18) << temp->nama
             << "| " << setw(12) << temp->no_hp
             << "| " << setw(30) << temp->alamat
             << "| " << setw(12) << temp->no_ktp
             << "| " << setw(20) << temp->buku
             << "| " << setw(17) << temp->batas_pengembalian << " |" << endl;
        cout << "==================================================================================================================================" << endl;
        temp = temp->next;
    }
}

// Fungsi untuk mengedit data peminjam
void editPeminjam(Peminjam* head, const string& id) {
    Peminjam* temp = head;
    while (temp != nullptr) {
        if (temp->id == id) {
            cout << "Data Peminjam ditemukan, silakan edit data:" << endl;
            
            // Menggunakan getline untuk membaca input string
            cout << "Masukkan Nama Peminjam: ";
            cin.ignore();  // Membersihkan newline yang tersisa
            getline(cin, temp->nama);

            // Menggunakan getline untuk No HP, Alamat, No KTP, Buku yang Dipinjam, dan Batas Pengembalian
            cout << "Masukkan No HP: ";
            getline(cin, temp->no_hp);

            cout << "Masukkan Alamat: ";
            getline(cin, temp->alamat);

            cout << "Masukkan No KTP: ";
            getline(cin, temp->no_ktp);

            cout << "Masukkan Buku yang Dipinjam: ";
            getline(cin, temp->buku);

            cout << "Masukkan Batas Pengembalian: ";
            getline(cin, temp->batas_pengembalian);

            cout << "Data peminjam berhasil diubah!" << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "Peminjam dengan ID " << id << " tidak ditemukan!" << endl;
}


// Menu Hapus Berdasarkan ID
void hapusPeminjamBerdasarkanID(Peminjam*& head) {
    string id;
    cout << "Masukkan ID peminjam yang akan dihapus: ";
    cin >> id;
    hapusPeminjam(head, id);  
}

// Prosedur untuk menghapus data peminjam
void hapusPeminjam(Peminjam*& head, const string& id) {
    if (head == nullptr) {
        cout << "Tidak ada data untuk dihapus!" << endl;
        return;
    }

    Peminjam* temp = head;
    Peminjam* prev = nullptr;

    if (temp != nullptr && temp->id == id) {
        head = temp->next;
        delete temp;
        cout << "Data peminjam berhasil dihapus!" << endl;
        return;
    }

    while (temp != nullptr && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == nullptr) {
        cout << "Peminjam dengan ID " << id << " tidak ditemukan!" << endl;
        return;
    }

    prev->next = temp->next;
    delete temp;
    cout << "Data peminjam berhasil dihapus!" << endl;
}

// Fungsi untuk menghapus data peminjam dengan metode Queue (FIFO)
void hapusPeminjamQueue(Peminjam*& head) {
    if (head == nullptr) {
        cout << "Tidak ada data untuk dihapus!" << endl;
        return;
    }

    Peminjam* temp = head;
    head = head->next;  // Mengubah head ke peminjam berikutnya
    delete temp;  // Menghapus peminjam yang pertama (head)
    cout << "Peminjam pertama (Queue) berhasil dihapus!" << endl;
}

// Fungsi untuk mengurutkan data peminjam menggunakan Shell Sort
void shellSort(Peminjam* head) {
    if (head == nullptr) {
        cout << "Tidak ada data untuk diurutkan!" << endl;
        return;
    }

    // Menghitung jumlah elemen dalam linked list
    int n = 0;
    Peminjam* temp = head;
    while (temp != nullptr) {
        n++;
        temp = temp->next;
    }

    // Array untuk menyimpan pointer ke elemen-elemen linked list
    Peminjam** arr = new Peminjam*[n];
    temp = head;
    for (int i = 0; i < n; i++) {
        arr[i] = temp;
        temp = temp->next;
    }

    // Menggunakan Shell Sort untuk mengurutkan berdasarkan ID peminjam
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            Peminjam* key = arr[i];
            int j = i;
            while (j >= gap && arr[j - gap]->id > key->id) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = key;
        }
    }

    // Menata ulang linked list berdasarkan urutan yang sudah diurutkan
    for (int i = 0; i < n - 1; i++) {
        arr[i]->next = arr[i + 1];
    }
    arr[n - 1]->next = nullptr;
    head = arr[0];  // Mengatur head menjadi elemen pertama

    delete[] arr;
    cout << "Data berhasil diurutkan!" << endl;
}

// Fungsi untuk menghapus data peminjam dari stack
void pop(Peminjam*& top) {
    if (top == nullptr) {
        cout << "Stack kosong, tidak ada data untuk dihapus!" << endl;
        return;
    }
    Peminjam* temp = top;
    top = top->next; // Mengubah top ke elemen berikutnya
    cout << "Data peminjam dengan ID " << temp->id << " berhasil dihapus dari stack!" << endl;
    delete temp; // Menghapus elemen top sebelumnya
}

Peminjam* quickSort(Peminjam* head) {
    // Jika list kosong atau hanya ada satu elemen
    if (head == nullptr || head->next == nullptr) {
        return head;
    }

    // Pivot (kami ambil elemen pertama)
    Peminjam* pivot = head;
    Peminjam* less = nullptr; // Elemen yang lebih kecil dari pivot
    Peminjam* greater = nullptr; // Elemen yang lebih besar dari pivot
    Peminjam* temp = head->next;

    // Pisahkan elemen berdasarkan pivot
    while (temp != nullptr) {
        if (temp->id < pivot->id) {
            temp->next = less;
            less = temp;
        } else {
            temp->next = greater;
            greater = temp;
        }
        temp = temp->next;
    }

    // Urutkan sublist less dan greater secara rekursif
    less = quickSort(less);
    greater = quickSort(greater);

    // Gabungkan less -> pivot -> greater
    if (less == nullptr) {
        pivot->next = greater;
        return pivot;
    }

    // Temukan akhir dari less dan sambungkan dengan pivot
    Peminjam* tempLess = less;
    while (tempLess->next != nullptr) {
        tempLess = tempLess->next;
    }
    tempLess->next = pivot;  // Sambungkan node terakhir di less ke pivot
    pivot->next = greater;  // Sambungkan pivot ke greater

    return less; // Mengembalikan kepala baru dari list yang telah diurutkan
}


void quickSortMenu(Peminjam*& head) {
    cout << "Mengurutkan data menggunakan Quick Sort..." << endl;
    head = quickSort(head);
    cout << "Data berhasil diurutkan!" << endl;
}

// Fungsi untuk pencarian dengan Fibonacci Search
void fibonacciSearch(Peminjam* head, const string& id) {
    // Menghitung jumlah elemen dalam linked list
    int n = 0;
    Peminjam* temp = head;
    while (temp != nullptr) {
        n++;
        temp = temp->next;
    }

    // Menyimpan elemen-elemen linked list dalam array
    Peminjam** arr = new Peminjam*[n];
    temp = head;
    for (int i = 0; i < n; i++) {
        arr[i] = temp;
        temp = temp->next;
    }

    int fibMMm2 = 0;
    int fibMMm1 = 1;
    int fibM = fibMMm2 + fibMMm1;

    while (fibM < n) {
        fibMMm2 = fibMMm1;
        fibMMm1 = fibM;
        fibM = fibMMm2 + fibMMm1;
    }

    int offset = -1;
    while (fibM > 1) {
        int i = min(offset + fibMMm2, n - 1);

        if (arr[i]->id == id) {
            cout << "Peminjam ditemukan: " << endl;
            cout << "ID: " << arr[i]->id << endl;
            cout << "Nama: " << arr[i]->nama << endl;
            cout << "No HP: " << arr[i]->no_hp << endl;
            cout << "Alamat: " << arr[i]->alamat << endl;
            cout << "No KTP: " << arr[i]->no_ktp << endl;
            cout << "Buku yang Dipinjam: " << arr[i]->buku << endl;
            cout << "Batas Pengembalian: " << arr[i]->batas_pengembalian << endl;
            delete[] arr;
            return;
        }

        if (arr[i]->id < id) {
            fibM = fibMMm1;
            fibMMm1 = fibMMm2;
            fibMMm2 = fibM - fibMMm1;
            offset = i;
        } else {
            fibM = fibMMm2;
            fibMMm2 = fibMMm1;
            fibMMm1 = fibM - fibMMm2;
        }
    }

    if (arr[offset + 1]->id == id) {
        cout << "Peminjam ditemukan: " << endl;
        cout << "ID: " << arr[offset + 1]->id << endl;
        cout << "Nama: " << arr[offset + 1]->nama << endl;
        cout << "No HP: " << arr[offset + 1]->no_hp << endl;
        cout << "Alamat: " << arr[offset + 1]->alamat << endl;
        cout << "No KTP: " << arr[offset + 1]->no_ktp << endl;
        cout << "Buku yang Dipinjam: " << arr[offset + 1]->buku << endl;
        cout << "Batas Pengembalian: " << arr[offset + 1]->batas_pengembalian << endl;
        delete[] arr;
        return;
    }

    cout << "Peminjam dengan ID " << id << " tidak ditemukan!" << endl;
    delete[] arr;
}

// Fungsi untuk pencarian dengan Jumper Search
void jumperSearch(Peminjam* head, const string& id) {
    int n = 0;
    Peminjam* temp = head;
    while (temp != nullptr) {
        n++;
        temp = temp->next;
    }

    Peminjam** arr = new Peminjam*[n];
    temp = head;
    for (int i = 0; i < n; i++) {
        arr[i] = temp;
        temp = temp->next;
    }

    int step = 0;
    while (step * step < n) {
        step++;
    }

    int prev = 0;
    while (arr[min(prev + step, n - 1)]->id < id) {
        prev = step;
        step += step;
        if (prev >= n) {
            cout << "Peminjam dengan ID " << id << " tidak ditemukan!" << endl;
 delete[] arr;
            return;
        }
    }

    for (int i = prev; i < min(prev + step, n); i++) {
        if (arr[i]->id == id) {
            cout << "Peminjam ditemukan: " << endl;
            cout << "ID: " << arr[i]->id << endl;
            cout << "Nama: " << arr[i]->nama << endl;
            cout << "No HP: " << arr[i]->no_hp << endl;
            cout << "Alamat: " << arr[i]->alamat << endl;
            cout << "No KTP: " << arr[i]->no_ktp << endl;
            cout << "Buku yang Dipinjam: " << arr[i]->buku << endl;
            cout << "Batas Pengembalian: " << arr[i]->batas_pengembalian << endl;
            delete[] arr;
            return;
        }
    }

    cout << "Peminjam dengan ID " << id << " tidak ditemukan!" << endl;
    delete[] arr;
}

// Fungsi untuk pencarian dengan Boyer-Moore Search
void boyerMooreSearch(Peminjam* head, const string& id) {
    Peminjam* temp = head;
    while (temp != nullptr) {
        if (temp->id == id) {
            cout << "Peminjam ditemukan: " << endl;
            cout << "ID: " << temp->id << endl;
            cout << "Nama: " << temp->nama << endl;
            cout << "No HP: " << temp->no_hp << endl;
            cout << "Alamat: " << temp->alamat << endl;
            cout << "No KTP: " << temp->no_ktp << endl;
            cout << "Buku yang Dipinjam: " << temp->buku << endl;
            cout << "Batas Pengembalian: " << temp->batas_pengembalian << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "Peminjam dengan ID " << id << " tidak ditemukan!" << endl;
}

// Menu pencarian
void searchingMenu(Peminjam* head) {
    int searchingMenu;
    cout << "Menu Searching:\n";
    cout << "1. Fibonacci Search\n";
    cout << "2. Jumper Search\n";
    cout << "3. Boyer-Moore Search\n"; // Menambahkan opsi Boyer-Moore
    cout << "4. Keluar\n";
    cout << "Pilih menu searching (1-4): ";
    cin >> searchingMenu;

    switch (searchingMenu) {
        case 1: {
            string id;
            cout << "Masukkan ID peminjam yang akan dicari: ";
            cin >> id;
            fibonacciSearch(head, id);
            break;
        }
        case 2: {
            string id;
            cout << "Masukkan ID peminjam yang akan dicari: ";
            cin >> id;
            jumperSearch(head, id);
            break;
        }
        case 3: {
            string id;
            cout << "Masukkan ID peminjam yang akan dicari: ";
            cin >> id;
            boyerMooreSearch(head, id); // Memanggil fungsi Boyer-Moore
            break;
        }
        case 4:
            cout << "Keluar dari menu searching." << endl;
            break;
        default:
            cout << "Pilihan tidak valid!" << endl;
    }
}

// Menu utama
void mainMenu(Peminjam*& head) {
    int pilihan = 0;
    while (pilihan != 7) {
        cout << "Menu:\n";
        cout << "1. Tambah Peminjam\n";
        cout << "2. Tampilkan Semua Peminjam\n";
        cout << "3. Edit Peminjam\n";
        cout << "4. Hapus Peminjam\n";
        cout << "5. Menu Sorting\n";
        cout << "6. Menu Searching\n";  // Update this menu option
        cout << "7. Keluar\n";
        cout << "Pilih menu (1-7): ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tambahPeminjam(head);
                break;
            case 2:
                tampilkanPeminjam(head);
                break;
            case 3: {
                string id;
                cout << "Masukkan ID peminjam yang akan diedit: ";
                cin >> id;
                editPeminjam(head, id);
                break;
            }
            case 4: {
                int metodeHapus;
                cout << "\nMetode Hapus:\n";
                cout << "1. Hapus Metode Queue\n";
                cout << "2. Hapus Berdasarkan ID\n";
                cout << "3. Hapus Metode Stack\n";
                cout << "4. Kembali ke Menu Utama\n";
                cout << "Pilih metode (1/2/3): ";
                cin >> metodeHapus;

                if (metodeHapus == 1) {
                    hapusPeminjamQueue(head);
                } else if (metodeHapus == 2) {
                    pop(head);
                } else if (metodeHapus == 3) {
                    hapusPeminjamBerdasarkanID(head);  // Menambahkan pemanggilan hapus berdasarkan ID
                } else if (metodeHapus == 4) {
                    cout << "Kembali ke menu awal...\n";
                    break;
                } else {
                    cout << "Pilihan tidak valid!" << endl;
                }
                break;
            }
            case 5: {
                int sortingMenu;
                cout << "Menu Sorting:\n";
                cout << "1. Shell Sort\n";
                cout << "2. Quick Sort\n";
                cout << "3. Keluar\n";
                cout << "Pilih menu sorting (1/2/3): ";
                cin >> sortingMenu;

                switch (sortingMenu) {
                    case 1:
                    shellSort(head);
                    tampilkanPeminjam(head); 
                    break;
                case 2:
                    quickSortMenu(head);
                    tampilkanPeminjam(head);
                    break;
                case 3:
                    cout << "Keluar dari menu sorting." << endl;
                    break;
                default:
                    cout << "Pilihan tidak valid!" << endl;
                }
                break;
            }
            case 6:
                searchingMenu(head); 
                break;
            case 7:
                cout << "Keluar dari program." << endl;
                break;
            default:
                cout << "Pilihan tidak valid! Silakan pilih menu yang benar." << endl;
        }
    }
}

int main() {
    Peminjam* head = nullptr;
    mainMenu(head);
    return 0;
}
