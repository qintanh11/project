#include <cstdio>
#include <iostream>
#include <cstring>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

FILE* market;

struct stok {
    string nama_barang;
    int harga, jumlah;
    stok* next;
    stok* prev;
};

stok* head = NULL;
stok* tail = NULL;

// ============================================================
// Simpan seluruh linked list ke file (untuk update & hapus)
// ============================================================
void simpan_semua() {
    market = fopen("projek.txt", "w");
    if (market == NULL) {
        cout << "Gagal membuka file untuk disimpan!\n";
        return;
    }
    stok* bantu = head;
    while (bantu != NULL) {
        // Ganti spasi dengan underscore agar mudah dibaca kembali
        string nama = bantu->nama_barang;
        fprintf(market, "%s %d %d\n", nama.c_str(), bantu->harga, bantu->jumlah);
        bantu = bantu->next;
    }
    fclose(market);
}

// ============================================================
// Cetak header tabel
// ============================================================
void cetakHeader() {
    cout << "\n" << left
         << setw(25) << "Nama Barang"
         << setw(12) << "Harga (Rp)"
         << setw(10) << "Stok" << "\n";
    cout << string(47, '-') << "\n";
}

// ============================================================
// Cetak data terurut berdasarkan kriteria
// kriteria: 1 = stok, 2 = harga
// ascending: true = terkecil dulu, false = terbesar dulu
// ============================================================
void cetakTerurut(int kriteria, bool ascending) {
    vector<stok*> daftar;
    for (stok* bantu = head; bantu != NULL; bantu = bantu->next) {
        daftar.push_back(bantu);
    }
    if (daftar.empty()) {
        cout << "Tidak ada barang dalam daftar.\n";
        return;
    }
    sort(daftar.begin(), daftar.end(), [kriteria, ascending](stok* a, stok* b) {
        if (kriteria == 1) {
            return ascending ? a->jumlah < b->jumlah : a->jumlah > b->jumlah;
        }
        return ascending ? a->harga < b->harga : a->harga > b->harga;
    });
    cetakHeader();
	while (fscanf(market, "%25s %d %d", nama_barang, &harga, &jumlah) != EOF) {
    cout << left
         << setw(25) << nama_barang
         << setw(12) << harga
         << setw(10) << jumlah << "\n";
}
    cout << "\n";
}

// ============================================================
// Menu 1: Lihat barang dengan sorting
// ============================================================
void lihat_barang() {
    int tampil, berdasarkan;
    cout << "\nTampilkan berdasarkan:\n";
    cout << "1. Stok\n";
    cout << "2. Harga\n";
    cout << "Pilihan: ";
    cin >> berdasarkan;

    switch (berdasarkan) {
    case 1: {
        cout << "1. Stok terbanyak\n";
        cout << "2. Stok tersedikit\n";
        cout << "Pilihan: ";
        cin >> tampil;
        if (tampil == 1) {
            cetakTerurut(1, false);
        } else if (tampil == 2) {
            cetakTerurut(1, true);
        } else {
            cout << "Pilihan tidak valid.\n";
        }
    } break;
    case 2: {
        cout << "1. Harga termahal\n";
        cout << "2. Harga termurah\n";
        cout << "Pilihan: ";
        cin >> tampil;
        if (tampil == 1) {
            cetakTerurut(2, false);
        } else if (tampil == 2) {
            cetakTerurut(2, true);
        } else {
            cout << "Pilihan tidak valid.\n";
        }
    } break;
    default:
        cout << "Pilihan tidak valid.\n";
        break;
    }
}

// ============================================================
// Menu 2: Cari barang (searching by name)
// ============================================================
void cari_barang(string nama) {
    stok* bantu = head;
    bool ketemu = false;

    while (bantu != NULL) {
        if (bantu->nama_barang == nama) {
            cout << "Barang ditemukan:\n";
            cetakHeader();
            cout << left
                 << setw(25) << bantu->nama_barang
                 << setw(12) << bantu->harga
                 << setw(10) << bantu->jumlah << "\n\n";
            ketemu = true;
            break;
        }
        bantu = bantu->next;
    }

    if (!ketemu) {
        cout << "Barang \"" << nama << "\" tidak ditemukan!\n";
    }
}

// ============================================================
// Menu 3: Tambah barang baru
// ============================================================
void tambah_barang(string nama, int harga, int jumlah) {
    // Simpan ke file
    market = fopen("projek.txt", "a");
    if (market == NULL) {
        cout << "Gagal membuka file!\n";
        return;
    }
    fprintf(market, "%s %d %d\n", nama.c_str(), harga, jumlah);
    fclose(market);

    // Masukkan ke linked list
    stok* nodeBaru = new stok;
    nodeBaru->nama_barang = nama;
    nodeBaru->harga = harga;
    nodeBaru->jumlah = jumlah;
    nodeBaru->next = NULL;
    nodeBaru->prev = NULL;

    if (head == NULL) {
        head = nodeBaru;
        tail = nodeBaru;
    } else {
        tail->next = nodeBaru;
        nodeBaru->prev = tail;
        tail = nodeBaru;
    }
    cout << "Barang \"" << nama << "\" berhasil ditambahkan.\n";
}

// ============================================================
// Menu 4: Hapus barang
// ============================================================
void hapus_barang(string nama) {
    stok* bantu = head;
    bool ketemu = false;

    while (bantu != NULL) {
        if (bantu->nama_barang == nama) {
            ketemu = true;
            // Putus sambungan node
            if (bantu->prev != NULL) bantu->prev->next = bantu->next;
            else head = bantu->next; // Node adalah head

            if (bantu->next != NULL) bantu->next->prev = bantu->prev;
            else tail = bantu->prev; // Node adalah tail

            delete bantu;
            simpan_semua(); // Update file
            cout << "Barang \"" << nama << "\" berhasil dihapus.\n";
            break;
        }
        bantu = bantu->next;
    }

    if (!ketemu) {
        cout << "Barang \"" << nama << "\" tidak ditemukan!\n";
    }
}

// ============================================================
// Menu 5: Tambah stok barang yang sudah ada
// ============================================================
void tambah_stok(string nama, int tambahan) {
    stok* bantu = head;
    bool ketemu = false;

    while (bantu != NULL) {
        if (bantu->nama_barang == nama) {
            bantu->jumlah += tambahan;
            simpan_semua();
            cout << "Stok \"" << nama << "\" berhasil ditambah. "
                 << "Stok sekarang: " << bantu->jumlah << "\n";
            ketemu = true;
            break;
        }
        bantu = bantu->next;
    }

    if (!ketemu) {
        cout << "Barang \"" << nama << "\" tidak ditemukan!\n";
    }
}

// ============================================================
// Menu 6: Kurangi stok barang
// ============================================================
void kurangi_stok(string nama, int kurang) {
    stok* bantu = head;
    bool ketemu = false;

    while (bantu != NULL) {
        if (bantu->nama_barang == nama) {
            if (kurang > bantu->jumlah) {
                cout << "Pengurangan melebihi stok yang tersedia ("
                     << bantu->jumlah << ")!\n";
            } else {
                bantu->jumlah -= kurang;
                simpan_semua();
                cout << "Stok \"" << nama << "\" berhasil dikurangi. "
                     << "Stok sekarang: " << bantu->jumlah << "\n";
            }
            ketemu = true;
            break;
        }
        bantu = bantu->next;
    }

    if (!ketemu) {
        cout << "Barang \"" << nama << "\" tidak ditemukan!\n";
    }
}

// ============================================================
// Muat data dari file ke linked list saat program dimulai
// ============================================================
void masuk_barang() {
    market = fopen("projek.txt", "r");
    if (market == NULL) return;

    char nama[100];
    int hrg, jml;

    while (fscanf(market, "%99s %d %d", nama, &hrg, &jml) == 3) {
        stok* nodeBaru = new stok;
        nodeBaru->nama_barang = nama;
        nodeBaru->harga = hrg;
        nodeBaru->jumlah = jml;
        nodeBaru->next = NULL;
        nodeBaru->prev = NULL;

        if (head == NULL) {
            head = nodeBaru;
            tail = nodeBaru;
        } else {
            tail->next = nodeBaru;
            nodeBaru->prev = tail;
            tail = nodeBaru;
        }
    }
    fclose(market);
}

// ============================================================
// MAIN
// ============================================================
int main() {
    masuk_barang();

    int menu;
    do {
        cout << "\n========= MENU STOK BARANG =========\n";
        cout << "1. Lihat Barang (Sorting)\n";
        cout << "2. Cari Barang (Searching)\n";
        cout << "3. Tambah Barang Baru\n";
        cout << "4. Hapus Barang\n";
        cout << "5. Tambah Stok\n";
        cout << "6. Kurangi Stok\n";
        cout << "0. Keluar\n";        // FIX: dulunya ada dua menu nomor 5
        cout << "=====================================\n";
        cout << "Pilih Menu: ";
        cin >> menu;
        cin.ignore(); // Bersihkan newline sebelum getline

        switch (menu) {
        case 1: {
            lihat_barang();
        } break;

        case 2: {
            string nama;
            cout << "Masukkan Nama Barang: ";
            getline(cin, nama); // FIX: getline agar bisa baca nama dengan spasi
            cari_barang(nama);
        } break;

        case 3: {
            string nama;
            int harga, jumlah;
            cout << "Masukkan Nama Barang  : ";
            getline(cin, nama); // FIX: getline
            cout << "Masukkan Harga Barang : ";
            cin >> harga;
            cout << "Masukkan Jumlah Barang: ";
            cin >> jumlah;
            cin.ignore();
            tambah_barang(nama, harga, jumlah);
        } break;

        case 4: {
            string nama;
            cout << "Masukkan Nama Barang yang akan dihapus: ";
            getline(cin, nama);
            hapus_barang(nama);
        } break;

        case 5: {
            string nama;
            int tambahan;
            cout << "Masukkan Nama Barang  : ";
            getline(cin, nama);
            cout << "Jumlah Stok Ditambah  : ";
            cin >> tambahan;
            cin.ignore();
            tambah_stok(nama, tambahan);
        } break;

        case 6: {
            string nama;
            int kurang;
            cout << "Masukkan Nama Barang  : ";
            getline(cin, nama);
            cout << "Jumlah Stok Dikurangi : ";
            cin >> kurang;
            cin.ignore();
            kurangi_stok(nama, kurang);
        } break;

        case 0:
            cout << "Terima kasih! Program selesai.\n";
            break;

        default:
            cout << "Pilihan tidak valid. Coba lagi.\n";
            break;
        }
    } while (menu != 0); // FIX: kondisi keluar disesuaikan dengan menu 0

    return 0;
}
