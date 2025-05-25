#include <iostream>
#include <cstdio>
#include <cstring>
#include <iomanip>
using namespace std;

struct Mahasiswa {
    int nim;
    char nama[50];
};

struct Node {
    Mahasiswa data;
    Node* left;
    Node* right;
};

FILE *file;
Node* root = nullptr;

Node* buatNode(Mahasiswa mhs) {
    Node* baru = new Node;
    baru->data = mhs;
    baru->left = baru->right = nullptr;
    return baru;
}

Node* tambahBST(Node* node, Mahasiswa mhs) {
    if (!node) return buatNode(mhs);
    if (mhs.nim < node->data.nim)
        node->left = tambahBST(node->left, mhs);
    else if (mhs.nim > node->data.nim)
        node->right = tambahBST(node->right, mhs);
    return node;
}

void inorder(Node* node) {
    if (node) {
        inorder(node->left);
        cout << left << setw(10) << node->data.nim << setw(30) << node->data.nama << endl;
        inorder(node->right);
    }
}

Node* cariBST(Node* node, int nim) {
    if (!node || node->data.nim == nim)
        return node;
    if (nim < node->data.nim)
        return cariBST(node->left, nim);
    else
        return cariBST(node->right, nim);
}

Node* minValueNode(Node* node) {
    Node* current = node;
    while (current && current->left)
        current = current->left;
    return current;
}

Node* hapusBST(Node* root, int nim) {
    if (!root) return root;

    if (nim < root->data.nim)
        root->left = hapusBST(root->left, nim);
    else if (nim > root->data.nim)
        root->right = hapusBST(root->right, nim);
    else {
        if (!root->left) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (!root->right) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        Node* temp = minValueNode(root->right);
        root->data = temp->data;
        root->right = hapusBST(root->right, temp->data.nim);
    }
    return root;
}

void simpanFile(Mahasiswa mhs) {
    file = fopen("dataMhs.dat", "ab");
    if (file) {
        fwrite(&mhs, sizeof(Mahasiswa), 1, file);
        fclose(file);
    }
}

void bacaDariFile() {
    file = fopen("dataMhs.dat", "rb");
    if (!file) return;

    Mahasiswa mhs;
    while (fread(&mhs, sizeof(Mahasiswa), 1, file)) {
        root = tambahBST(root, mhs);
    }
    fclose(file);
}

void simpanBSTkeFile(Node* node, FILE* file) {
    if (node) {
        simpanBSTkeFile(node->left, file);
        fwrite(&node->data, sizeof(Mahasiswa), 1, file);
        simpanBSTkeFile(node->right, file);
    }
}

void updateFileDariBST() {
    FILE* file = fopen("dataMhs.dat", "wb");
    if (!file) {
        cout << "Gagal membuka file.\n";
        return;
    }
    simpanBSTkeFile(root, file);
    fclose(file);
}

void tambahMahasiswa() {
    int jumlah;
    cout << "Jumlah mahasiswa yang ingin ditambah: ";
    cin >> jumlah;
    cin.ignore();

    for (int i = 0; i < jumlah; i++) {
        Mahasiswa mhs;
        cout << "\nMahasiswa ke-" << i + 1 << endl;
        cout << "NIM\t: ";
        cin >> mhs.nim;
        cin.ignore();
        cout << "Nama\t: ";
        cin.getline(mhs.nama, 50);

        root = tambahBST(root, mhs);
        simpanFile(mhs);
    }
}

void tampilkanMahasiswa() {
    if (!root) {
        cout << "Belum ada data mahasiswa.\n";
        return;
    }

    cout << left << setw(10) << "NIM" << setw(30) << "Nama" << endl;
    cout << "-------------------------------------\n";
    inorder(root);
}

void cariMahasiswa() {
    int nim;
    cout << "Masukkan NIM yang dicari: ";
    cin >> nim;

    Node* hasil = cariBST(root, nim);
    if (hasil) {
        cout << "\nData ditemukan:\n";
        cout << "NIM\t: " << hasil->data.nim << endl;
        cout << "Nama\t: " << hasil->data.nama << endl;
    } else {
        cout << "Data tidak ditemukan.\n";
    }
}

void hapusMahasiswa() {
    int nim;
    cout << "Masukkan NIM yang akan dihapus: ";
    cin >> nim;

    if (cariBST(root, nim)) {
        root = hapusBST(root, nim);
        updateFileDariBST(); // Simpan perubahan ke file
        cout << "Data berhasil dihapus dari BST dan file.\n";
    } else {
        cout << "Data tidak ditemukan.\n";
    }
}

int main() {
    bacaDariFile();
    int pilih;

    do {
        system("cls");
        cout << "\n=== MENU ===\n";
        cout << "1. Tambah Mahasiswa\n";
        cout << "2. Tampilkan Data\n";
        cout << "3. Cari Mahasiswa\n";
        cout << "4. Hapus Mahasiswa\n";
        cout << "0. Keluar\n";
        cout << "Pilih: ";
        cin >> pilih;
        cin.ignore();
        system("cls");

        switch (pilih) {
            case 1: tambahMahasiswa(); break;
            case 2: tampilkanMahasiswa(); break;
            case 3: cariMahasiswa(); break;
            case 4: hapusMahasiswa(); break;
            case 0: cout << "Keluar dari program.\n"; break;
            default: cout << "Pilihan tidak valid.\n";
        }

        cout << "\n";
        system("pause");
    } while (pilih != 0);

    return 0;
}