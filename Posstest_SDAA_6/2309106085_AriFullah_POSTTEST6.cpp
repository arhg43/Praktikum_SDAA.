#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
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
void sortingMenu();
void mergeSort(Barang** headRef);
Barang* sortedMerge(Barang* a, Barang* b);
void frontBackSplit(Barang* source, Barang** frontRef, Barang** backRef);
void shellSort();
void sortDescending(Barang** headRef);
void insertSorted(Barang*& headRef, Barang* newNode);

// Fungsi searching
int fibonacciSearch(Barang* head, int x);
int jumpSearch(Barang* head, int x);
int boyerMooreSearch(string text, string pattern);

// Fungsi untuk membuat tabel
void printTableHeader() {
    cout << "-----------------------------------------------------" << endl;
    cout << "| ID  | Nama Barang            | Stok  | Harga (Rp)  |" << endl;
    cout << "-----------------------------------------------------" << endl;
}

void printTableFooter() {
    cout << "-----------------------------------------------------" << endl;
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

// Fungsi untuk menampilkan menu sorting
void sortingMenu() {
    int pilihan;
    cout << "\n======== Menu Sorting ========\n";
    cout << "1. Ascending (Merge Sort)(ID)\n";
    cout << "2. Descending (Shell Sort)(ID)\n";
    cout << "Pilihan: ";
    cin >> pilihan;

    switch (pilihan) {
        case 1:
            mergeSort(&head);
            cout << "Sorting barang berdasarkan ID (Ascending) selesai!" << endl;
            tampilBarang();
            break;
        case 2:
            shellSort();
            cout << "Sorting barang berdasarkan ID (Descending) selesai!" << endl;
            tampilBarang();
            break;
        default:
            cout << "Pilihan tidak valid!" << endl;
    }
}

// Merge Sort
void mergeSort(Barang** headRef) {
    Barang* head = *headRef;
    Barang* a;
    Barang* b;

    if (head == nullptr || head->next == nullptr) {
        return;
    }

    frontBackSplit(head, &a, &b);

    mergeSort(&a);
    mergeSort(&b);

    *headRef = sortedMerge(a, b);
}

Barang* sortedMerge(Barang* a, Barang* b) {
    Barang* result = nullptr;

    if (a == nullptr) {
        return b;
    } else if (b == nullptr) {
        return a;
    }

    if (a->id <= b->id) {
        result = a;
        result->next = sortedMerge(a->next, b);
    } else {
        result = b;
        result->next = sortedMerge(a, b->next);
    }
    return result;
}

void frontBackSplit(Barang* source, Barang** frontRef, Barang** backRef) {
    Barang* fast;
    Barang* slow;
    slow = source;
    fast = source->next;

    while (fast != nullptr) {
        fast = fast->next;
        if (fast != nullptr) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *frontRef = source;
    *backRef = slow->next;
    slow->next = nullptr;
}

// Shell Sort
void shellSort() {
    if (head == nullptr) {
        return;
    }

    int n = 0;
    Barang* temp = head;

    while (temp != nullptr) {
        n++;
        temp = temp->next;
    }

    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            Barang* current = head;
            Barang* prev = nullptr;
            int count = 0;

            while (count < i) {
                prev = current;
                current = current->next;
                count++;
            }

            Barang* tempNode = current;

            for (int j = i - gap; j >= 0; j -= gap) {
                Barang* tempNode2 = head;
                int count2 = 0;

                while (count2 < j) {
                    tempNode2 = tempNode2->next;
                    count2++;
                }

                if (tempNode->id > tempNode2->id) {
                    swap(tempNode->id, tempNode2->id);
                    swap(tempNode->nama, tempNode2->nama);
                    swap(tempNode->stok, tempNode2->stok);
                    swap(tempNode->harga, tempNode2->harga);
                } else {
                    break;
                }
            }
        }
    }
}

// Implementasi Fibonacci Search
int fibonacciSearch(Barang* head, int x) {
    if (head == nullptr) {
        return -1;
    }

    int fib2 = 0;
    int fib1 = 1;
    int fibM = fib2 + fib1;

    int n = 0;
    Barang* temp = head;
    while (temp != nullptr) {
        n++;
        temp = temp->next;
    }

    while (fibM < n) {
        fib2 = fib1;
        fib1 = fibM;
        fibM = fib2 + fib1;
    }

    int offset = -1;

    temp = head;
    for (int i = 0; i < n; i++) {
        if (temp->id == x) {
            return i;
        }
        temp = temp->next;
    }

    return -1;
}

// Implementasi Jump Search
int jumpSearch(Barang* head, int x) {
    int n = 0;
    Barang* temp = head;
    while (temp != nullptr) {
        n++;
        temp = temp->next;
    }

    int step = sqrt(n);
    int prev = 0;

    temp = head;
    while (temp != nullptr && temp->id < x) {
        prev += step;
        if (prev >= n) {
            return -1;
        }
        temp = head;
        for (int i = 0; i < prev; i++) {
            temp = temp->next;
        }
    }

    for (int i = prev - step + 1; i <= prev && temp != nullptr; i++) {
        if (temp->id == x) {
            return i;
        }
        temp = temp->next;
    }

    return -1;
}

// Implementasi Boyer-Moore Search untuk nama barang
int boyerMooreSearch(string text, string pattern) {
    int m = pattern.length();
    int n = text.length();

    if (m > n) {
        return -1;
    }

    int badChar[256];
    for (int i = 0; i < 256; i++) {
        badChar[i] = -1;
    }

    for (int i = 0; i < m; i++) {
        badChar[(int)pattern[i]] = i;
    }

    int shift = 0;
    while (shift <= (n - m)) {
        int j = m - 1;

        while (j >= 0 && pattern[j] == text[shift + j]) {
            j--;
        }

        if (j < 0) {
            return shift;
        } else {
            shift += max(1, j - badChar[(int)text[shift + j]]);
        }
    }

    return -1;
}

int main() {
    int pilihan;
    do {
        cout << "\n======== Menu Utama ========\n";
        cout << "1. Tambah Barang\n";
        cout << "2. Tampilkan Barang\n";
        cout << "3. Edit Barang\n";
        cout << "4. Hapus Barang\n";
        cout << "5. Tampilkan Stack\n";
        cout << "6. Tampilkan Queue\n";
        cout << "7. Sorting Barang\n";
        cout << "8. Pencarian Barang\n";
        cout << "0. Keluar\n";
        cout << "Pilihan: ";
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
                sortingMenu();
                break;
            case 8: {
                int subPilihan;
                cout << "\n======== Pencarian Barang ========\n";
                cout << "1. Jump Search (ID)\n";
                cout << "2. Fibonacci Search (ID)\n";
                cout << "3. Boyer-Moore Search (Nama Barang)\n";
                cout << "Pilihan: ";
                cin >> subPilihan;

                switch (subPilihan) {
                    case 1: {
                        int id;
                        cout << "Masukkan ID barang: ";
                        cin >> id;
                        int result = jumpSearch(head, id);
                        if (result != -1) {
                            cout << "Barang ditemukan di indeks " << result << endl;
                        } else {
                            cout << "Barang tidak ditemukan." << endl;
                        }
                        break;
                    }
                    case 2: {
                        int id;
                        cout << "Masukkan ID barang: ";
                        cin >> id;
                        int result = fibonacciSearch(head, id);
                        if (result != -1) {
                            cout << "Barang ditemukan di indeks " << result << endl;
                        } else {
                            cout << "Barang tidak ditemukan." << endl;
                        }
                        break;
                    }
                    case 3: {
                        string nama;
                        cout << "Masukkan nama barang: ";
                        cin.ignore();
                        getline(cin, nama);
                        Barang* temp = head;
                        int index = 0;
                        bool found = false;
                        while (temp != nullptr) {
                            if (boyerMooreSearch(temp->nama, nama) != -1) {
                                cout << "Barang ditemukan: ID: " << temp->id
                                     << ", Nama: " << temp->nama << endl;
                                found = true;
                            }
                            temp = temp->next;
                            index++;
                        }
                        if (!found) {
                            cout << "Barang tidak ditemukan." << endl;
                        }
                        break;
                    }
                    default:
                        cout << "Pilihan tidak valid!" << endl;
                }
                break;
            }
            case 0:
                cout << "Terima kasih telah menggunakan program ini!" << endl;
                break;
            default:
                cout << "Pilihan tidak valid!" << endl;
        }
    } while (pilihan != 0);

    return 0;
}