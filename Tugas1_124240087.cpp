#include <iostream>
#include <iomanip>

using namespace std;

int jmlBarang = 0;
const int maxBarang = 100;

struct Barang {
    string nama;
    int harga;
} dataBarang[maxBarang];

void menu();
void input();
void view();
void search();
void bubble_sort();
int binary_search(string cari);
void sequential_search(int cari);

int main() {
    menu();
    return 0;
}

void menu() {
    int pilih;
    do {
        system("cls");
        cout << "\n\tToko Kelontong B-2\n";
        cout << setw(35) << setfill('=') << "" << endl;
        cout << "1. Input Barang\n";
        cout << "2. Tampilkan Barang\n";
        cout << "3. Cari Barang\n";
        cout << "4. Keluar\n";
        cout << "Pilih menu [1-4]: ";
        cin >> pilih;

        system("cls");
        switch (pilih) {
            case 1: input(); break;
            case 2: view(); break;
            case 3: search(); break;
            case 4: cout << "Terima kasih!\n"; exit(0);
            default: cout << "Pilihan tidak valid! Masukkan angka 1-4.\n";
        }
    } while (pilih != 4);
}

void input() {
    cout << "Input Barang" << endl;
    cout << setw(12) << setfill('-') << "" << endl;

    if (jmlBarang >= maxBarang) {
        cout << "Penyimpanan penuh! Gagal menambahkan barang.\n";
        system("pause");
        return;
    }

    int inputData;
    cout << "Jumlah barang yang ingin diinput: ";
    cin >> inputData;
    cin.ignore(); 

    for (int a = 0; a < inputData; a++) {
        if (jmlBarang >= maxBarang) {
            cout << "Penyimpanan penuh! Berhenti menambahkan barang.\n";
            break;
        }

        cout << "\nBarang ke-" << jmlBarang + 1 << endl;
        cout << "Masukkan nama barang\t: ";
        getline(cin, dataBarang[jmlBarang].nama);
        cout << "Masukkan harga barang\t: ";
        cin >> dataBarang[jmlBarang].harga;
        cin.ignore(); 
        jmlBarang++;
    }
    cout << "\nBarang berhasil ditambahkan!\n";
    system("pause");
}

void bubble_sort() {
    for (int i = 0; i < jmlBarang - 1; i++) {
        for (int j = 0; j < jmlBarang - i - 1; j++) {
            if (dataBarang[j].nama > dataBarang[j + 1].nama) {
                swap(dataBarang[j], dataBarang[j + 1]);
            }
        }
    }
}

void view() {
    if (jmlBarang == 0) {
        cout << "Belum ada data barang!\n";
        system("pause");
        return;
    }

    bubble_sort();

    cout << "Daftar Barang\n";
    cout << setw(13) << setfill('-') << "" << endl;
    for (int i = 0; i < jmlBarang; i++) {
        cout << "- " << dataBarang[i].nama << " (Rp" << dataBarang[i].harga << ")\n";
    }
    system("pause");
}

int binary_search(string cari) {
    system("cls");
    int kiri = 0, kanan = jmlBarang - 1;
    
    while (kiri <= kanan) {
        int tengah = (kiri + kanan) / 2;
        
        if (dataBarang[tengah].nama == cari) {
            return tengah;
        }
        if (dataBarang[tengah].nama < cari) {
            kiri = tengah + 1;
        } else {
            kanan = tengah - 1;
        }
    }
    return -1; // Barang tidak ditemukan
}

void sequential_search(int cari) {
    system("cls");
    bool found = false;
    
    for (int i = 0; i < jmlBarang; i++) {
        if (dataBarang[i].harga == cari) {
            cout << "Barang ditemukan: " << dataBarang[i].nama << " (Rp" << dataBarang[i].harga << ")\n";
            found = true;
        }
    }
    if (!found) {
        cout << "Barang dengan harga tersebut tidak ditemukan!\n";
    }
}

void search() {
    if (jmlBarang == 0) {
        cout << "Belum ada data barang!\n";
        system("pause");
        return;
    }

    int pilihan;
    cout << "\nPilih metode pencarian:\n";
    cout << "1. Cari berdasarkan Nama (Binary Search)\n";
    cout << "2. Cari berdasarkan Harga (Sequential Search)\n";
    cout << "3. Kembali ke Menu Utama\n";
    cout << "Pilih metode: ";
    cin >> pilihan;
    cin.ignore(); 

    if (pilihan == 1) {
        string cari;
        cout << "Masukkan nama barang yang dicari: ";
        getline(cin, cari);

        bubble_sort(); 
        int hasil = binary_search(cari);

        if (hasil != -1) {
            cout << "Barang ditemukan:\n" << dataBarang[hasil].nama << " (Rp" << dataBarang[hasil].harga << ")\n";
        } else {
            cout << "Barang tidak ditemukan!\n";
        }
    } 
    else if (pilihan == 2) {
        int cari;
        cout << "Masukkan harga barang yang dicari: ";
        cin >> cari;
        sequential_search(cari);
    } 
    else if (pilihan == 3) {
        return;
    } 
    else {
        cout << "Pilihan tidak valid!\n";
    }
    system("pause");
}
