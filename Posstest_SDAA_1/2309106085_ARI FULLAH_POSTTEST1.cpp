#include <iostream>
#include <string>
using namespace std;

// Fungsi rekursif untuk memindahkan piringan
void pindahkanPiringan(int jumlahPiringan, const string& menaraAsal, const string& menaraTujuan, const string& menaraSementara) {
    // Jika hanya ada 1 piringan, langsung pindahkan dari menara asal ke menara tujuan
    if (jumlahPiringan == 1) {
        cout << "Pindahkan piringan dari " << menaraAsal << " ke " << menaraTujuan << endl;
        return;
    }
    
    // Pindahkan n-1 piringan dari menara asal ke menara sementara
    pindahkanPiringan(jumlahPiringan - 1, menaraAsal, menaraSementara, menaraTujuan);
    
    // Pindahkan piringan terakhir dari menara asal ke menara tujuan
    cout << "Pindahkan piringan dari " << menaraAsal << " ke " << menaraTujuan << endl;
    
    // Pindahkan n-1 piringan dari menara sementara ke menara tujuan
    pindahkanPiringan(jumlahPiringan - 1, menaraSementara, menaraTujuan, menaraAsal);
}

int main() {
    int jumlahPiringan;
    
    // Meminta input jumlah piringan dari pengguna
    cout << "Selamat datang di simulasi Menara Hanoi!" << endl;
    cout << "Masukkan jumlah piringan yang ingin dipindahkan: ";
    cin >> jumlahPiringan;
    
    // Validasi input jumlah piringan
    if (jumlahPiringan <= 0) {
        cout << "Jumlah piringan harus lebih dari 0. Program berakhir." << endl;
        return 1;
    }

    // Menampilkan simulasi perpindahan piringan
    cout << "\nProses memindahkan " << jumlahPiringan << " piringan:\n" << endl;
    pindahkanPiringan(jumlahPiringan, "Menara A", "Menara C", "Menara B");
    
    cout << "\nProses selesai!" << endl;
    
    return 0;
}
