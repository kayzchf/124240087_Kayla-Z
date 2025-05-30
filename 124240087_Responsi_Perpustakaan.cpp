#include <iostream>
#include <cstdio>
#include <cstring>
#include <iomanip>
using namespace std;

struct Buku {
    string judul;
    string author;
    int tahun;
} dataBuku;

struct Node {
    Buku data;
    Node* left;
    Node* right;
};

struct undoData {
    string aksi;
    Buku book;
};

Node* root = nullptr;
const int MAX_UNDO = 100;
undoData undoStack[MAX_UNDO];
int topUndo = -1;

Node* buatNode(Buku dataBuku);
Node* tambahBST(Node* node, Buku dataBuku);
Node* cariBST(Node* node, string judul);
Node* hapusBST(Node* root, string judul);
void inorderDesc(Node* node);
void inputBuku();
void tampilBuku();
void cariBuku();
void hapusBuku();
void pushUndo(string aksi, Buku dataBuku);
void undoAksi();
bool isUndoAvailable();
undoData popUndo();

int main() {
    int pilih;

    do {
        system("cls");
        cout << endl << right << setw(12) << "MENU" << "" << endl;
        cout << setw(20) << setfill('-') << "" << endl;
        cout << "1. Tambah Buku Baru" << endl;
        cout << "2. Lihat Daftar Buku" << endl;
        cout << "3. Cari Buku" << endl;
        cout << "4. Hapus Buku" << endl;
        cout << "5. Undo Aksi terakhir" << endl;
        cout << "0. Keluar" << endl;
        cout << setw(20) << setfill('-') << "" << endl;
        cout << "Pilih Menu: "; cin >> pilih;
        system("cls");

        switch (pilih) {
            case 1: inputBuku(); break;
            case 2: tampilBuku(); break;
            case 3: cariBuku(); break;
            case 4: hapusBuku(); break;
            case 5: undoAksi(); break;
            case 0: cout << "Keluar dari program.\n"; break;
            default: cout << "Pilihan tidak valid!\n";
        }
        system("pause");
    } while (pilih != 0);
    return 0;
}

Node* buatNode(Buku dataBuku) {
    Node* baru = new Node;
    baru->data = dataBuku;
    baru->left = baru->right = nullptr;
    return baru;
}

Node* tambahBST(Node* node, Buku dataBuku) {
    if (!node) return buatNode(dataBuku);
    if (dataBuku.judul < node->data.judul)
        node->left = tambahBST(node->left, dataBuku);
    else if (dataBuku.judul > node->data.judul)
        node->right = tambahBST(node->right, dataBuku);
    return node;
}

void inorderDesc(Node* node) {
    if (!node) return;
    inorderDesc(node->right);
    cout << "[" << node->data.judul << "] - [" << node->data.author<< "] - [" << node->data.tahun << "]\n";
    inorderDesc(node->left);
}

Node* cariBST(Node* node, string cari) {
    if (!node || node->data.judul == cari) 
        return node;
    if (cari < node->data.judul)
        return cariBST(node->left, cari);
    else 
        return cariBST(node->right, cari);
}

Node* hapusBST(Node* root, string hapus) {
    if (root == nullptr) return nullptr;

    if (hapus < root->data.judul) 
        root->left = hapusBST(root->left, hapus);
    else if (hapus > root->data.judul) 
        root->right = hapusBST(root->right, hapus);
    else {
        if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        } 
        else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        Node* successor = root->right;
        while (successor->left != nullptr)
            successor = successor->left;
        root->data = successor->data;
        root->right = hapusBST(root->right, successor->data.judul);
    }
    return root;
}

void pushUndo(string aksi, Buku dataBuku) {
    if (topUndo < MAX_UNDO -1) {
        topUndo++;
        undoStack[topUndo].aksi = aksi;
        undoStack[topUndo].book = dataBuku;
    }
}

bool isUndoAvailable() {
    return topUndo >= 0;
}

undoData popUndo() {
    if (topUndo >= 0) return undoStack[topUndo--];
    return {"", {0, ""}};
}

void inputBuku() {
    int jumlah;
    cout << "Jumlah buku yang ingin ditambah: "; cin >> jumlah;
    cin.ignore();

    for (int i = 0; i < jumlah; i++) {
        cout << "\nBuku ke-" << i + 1 << endl;
        cout << "Judul Buku\t: "; getline(cin, dataBuku.judul);
        cout << "Nama Penulis\t: "; getline(cin, dataBuku.author);
        cout << "Tahun Terbit\t: "; cin >> dataBuku.tahun; cin.ignore();

        root = tambahBST(root, dataBuku);
        pushUndo("tambah", dataBuku);
    }
}

void tampilBuku() {
    if (root == nullptr) {
        cout << "\nBelum ada daftar buku.\n";
        return;
    }

    cout << "Daftar Buku:" << endl;
    inorderDesc(root);
}

void cariBuku() {
    string cari;
    cin.ignore();
    cout << "Masukkan judul buku yang dicari: "; 
    getline(cin, cari);

    Node* hasil = cariBST(root, cari);
    if (hasil) {
        cout << "\nBuku ditemukan: " << endl;
        cout << setw(15) << setfill('-') << "" << endl;
        cout << "Judul Buku\t: " << hasil->data.judul << endl;
        cout << "Nama Penulis\t: " << hasil->data.author << endl;
        cout << "Tahun Terbit\t: " << hasil->data.tahun << endl;
    } else {
        cout << "\nBuku dengan judul " << cari << " tidak ditemukan.\n" << endl;
    }
}

void hapusBuku() {
    string hapus;
    cin.ignore();
    cout << "Masukkan judul buku yang akan dihapus: ";
    getline(cin, hapus);

    Node *hasil = cariBST(root, hapus);
    if (hasil) {
        pushUndo ("hapus", hasil->data);
        root = hapusBST(root, hapus);
        cout << "\nBuku dengan judul " << hapus << " berhasil dihapus.\n" << endl;
    } else
        cout << "\n\nJudul buku tidak ditemukan.\n" << endl;
}

void undoAksi() {
    if (!isUndoAvailable()) {
        cout << "Tidak ada aksi untuk dikembalikan." << endl;
        return;
    }
    undoData aksi = popUndo();
    if (aksi.aksi == "tambah") {
        root = hapusBST(root, aksi.book.judul);
        cout << "\nUndo Berhasil: Buku dengan judul " << aksi.book.judul << " dibatalkan penambahannya" << endl;
    } else if (aksi.aksi == "hapus") {
        root = tambahBST(root, aksi.book);
        cout << "\nUndo Berhasil: Buku dengan judul " << aksi.book.judul << " dibatalkan penghapusannya" << endl;
    }
}