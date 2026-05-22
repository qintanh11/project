#include <iostream>
#include <iomanip>
using namespace std;

FILE *market;

struct stok {
    string nama_barang;
    int harga, jumlah;
    stok* next;
    stok* prev;
};

stok* head = NULL;
stok* tail = NULL;


// Fungsi manual untuk menukar data
void tukarData(stok* a, stok* b) {
    string tukarnama = a->nama_barang;
    a->nama_barang = b->nama_barang;
    b->nama_barang = tukarnama;

    int tukarharga = a->harga;
    a->harga = b->harga;
    b->harga = tukarharga;

    int tukarjumlah = a->jumlah;
    a->jumlah = b->jumlah;
    b->jumlah = tukarjumlah;
}


// Fungsi bantu untuk menyalin Linked List
stok* buatlinkedlist() {
    if (head == NULL) return NULL;
    
    stok* newHead = NULL;
    stok* newTail = NULL;
    stok* bantu = head;
    
    while (bantu != NULL) {
        stok* barangbaru = new stok;
        barangbaru->nama_barang = bantu->nama_barang;
        barangbaru->harga = bantu->harga;
        barangbaru->jumlah = bantu->jumlah;
        barangbaru->next = NULL;
        barangbaru->prev = NULL;
        
        if (newHead == NULL) {
            newHead = barangbaru;
            newTail = barangbaru;
        } else {
            newTail->next = barangbaru;
            barangbaru->prev = newTail;
            newTail = barangbaru;
        }
        bantu = bantu->next;
    }
    return newHead;
}

// Fungsi bantu untuk menghapus list salinan dari memori
void hapusListSalinan(stok* h) {
    while (h != NULL) {
        stok* temp = h;
        h = h->next;
        delete temp;
    }
}

// Cetak data terurut berdasarkan kriteria (Bubble Sort Manual)
void cetakTerurut(int kriteria, bool ascending) {
    if (head == NULL) {
        cout << "Tidak ada barang dalam daftar.\n";
        return;
    }

    stok* listSalinan = buatlinkedlist();
    bool swapped;
    stok* ptr1;
    stok* lptr = NULL;

    do {
        swapped = false;
        ptr1 = listSalinan;

        while (ptr1->next != lptr) {
            bool kondisiTukar = false;
            
            if (kriteria == 1) { // Berdasarkan Stok
                if (ascending) {
                    if (ptr1->jumlah > ptr1->next->jumlah) kondisiTukar = true;
                } else {
                    if (ptr1->jumlah < ptr1->next->jumlah) kondisiTukar = true;
                }
            } else { // Berdasarkan Harga
                if (ascending) {
                    if (ptr1->harga > ptr1->next->harga) kondisiTukar = true;
                } else {
                    if (ptr1->harga < ptr1->next->harga) kondisiTukar = true;
                }
            }

            if (kondisiTukar) {
                tukarData(ptr1, ptr1->next);
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);

     cout << "\n" << left
         << setw(25) << "Nama Barang"
         << setw(12) << "Harga (Rp)"
         << setw(10) << "Stok" << "\n";
    cout << "-----------------------------------------------\n";

    stok* bantu = listSalinan;
    while (bantu != NULL) {
        cout << left
             << setw(25) << bantu->nama_barang
             << setw(12) << bantu->harga
             << setw(10) << bantu->jumlah << "\n";
        bantu = bantu->next;
    }
    cout << "\n";

    hapusListSalinan(listSalinan);
}


// Menu 1: Lihat barang dengan sorting
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
        if (tampil == 1) cetakTerurut(1, false);
        else if (tampil == 2) cetakTerurut(1, true);
        else cout << "Pilihan tidak valid.\n";
    } break;
    case 2: {
        cout << "1. Harga termahal\n";
        cout << "2. Harga termurah\n";
        cout << "Pilihan: ";
        cin >> tampil;
        if (tampil == 1) cetakTerurut(2, false);
        else if (tampil == 2) cetakTerurut(2, true);
        else cout << "Pilihan tidak valid.\n";
    } break;
    default:
        cout << "Pilihan tidak valid.\n";
        break;
    }
}

// Menu 2: Cari barang (searching by name)
void cari_barang(string nama) {
    stok* bantu = head;
    bool ketemu = false;

    while (bantu != NULL) {
        if (bantu->nama_barang == nama) {
            cout << "Barang ditemukan:\n";

        cout << "\n" << left
         << setw(25) << "Nama Barang"
         << setw(12) << "Harga (Rp)"
         << setw(10) << "Stok" << "\n";
    cout << "-----------------------------------------------\n";

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

// Menu 3: Tambah barang baru
void tambah_barang(string nama, int harga, int jumlah, bool dariFile = false) {
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
    
    if (!dariFile) {
        cout << "Barang \"" << nama << "\" berhasil ditambahkan.\n";
    }
}

// Menu 4: Hapus barang
void hapus_barang(string nama) {
    stok* bantu = head;
    bool ketemu = false;

    while (bantu != NULL) {
        if (bantu->nama_barang == nama) {
            ketemu = true;
            if (bantu->prev != NULL) bantu->prev->next = bantu->next;
            else head = bantu->next;

            if (bantu->next != NULL) bantu->next->prev = bantu->prev;
            else tail = bantu->prev;

            delete bantu;
            cout << "Barang \"" << nama << "\" berhasil dihapus.\n";
            break;
        }
        bantu = bantu->next;
    }

    if (!ketemu) {
        cout << "Barang \"" << nama << "\" tidak ditemukan!\n";
    }
}

// Menu 5: Tambah stok barang yang sudah ada
void tambah_stok(string nama, int tambahan) {
    stok* bantu = head;
    bool ketemu = false;

    while (bantu != NULL) {
        if (bantu->nama_barang == nama) {
            bantu->jumlah += tambahan;
            cout << "Stok \"" << nama << "\" berhasil ditambah. Stok sekarang: " << bantu->jumlah << "\n";
            ketemu = true;
            break;
        }
        bantu = bantu->next;
    }

    if (!ketemu) {
        cout << "Barang \"" << nama << "\" tidak ditemukan!\n";
    }
}

// Menu 6: Kurangi stok barang
void kurangi_stok(string nama, int kurang) {
    stok* bantu = head;
    bool ketemu = false;

    while (bantu != NULL) {
        if (bantu->nama_barang == nama) {
            if (kurang > bantu->jumlah) {
                cout << "Pengurangan melebihi stok yang tersedia (" << bantu->jumlah << ")!\n";
            } else {
                bantu->jumlah -= kurang;
                cout << "Stok \"" << nama << "\" berhasil dikurangi. Stok sekarang: " << bantu->jumlah << "\n";
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

// Simpan data ke file
void simpan_ke_file() {
    market = fopen("database_market.txt", "w");
    if (market == NULL) {
        cout << "Gagal membuka file untuk menyimpan data!\n";
        return;
    }

    stok* bantu = head;
    while (bantu != NULL) {
        // Kita cetak per baris agar aman dari gangguan spasi pada nama barang
        fprintf(market, "%s\n%d\n%d\n", bantu->nama_barang.c_str(), bantu->harga, bantu->jumlah);
        bantu = bantu->next;
    }

    fclose(market);
    cout << "Data berhasil disimpan ke file 'database_market.txt'.\n";
}

// Simpan file ke linked list
void buka_file() {
    market = fopen("database_market.txt", "r");
    if (market == NULL) {
        cout << "Belum ada file database. Membuat data baru di memori...\n";
        return;
    }

    char temp_nama[100];
    int harga, jumlah;

    while (fscanf(market, " %[^\n]", temp_nama) == 1) {
        if (fscanf(market, "%d %d", &harga, &jumlah) == 2) {
            tambah_barang(string(temp_nama), harga, jumlah, true);
        }
    }

    fclose(market);
    cout << "Database berhasil dimuat dari file.\n";
}

// MAIN
int main() {
    market = fopen("database_market.txt", "r");
    char temp_nama[100];
    int harga, jumlah;
    while (fscanf(market, " %[^\n]", temp_nama) == 1) {
        if (fscanf(market, "%d %d", &harga, &jumlah) == 2) {
            tambah_barang(string(temp_nama), harga, jumlah, true);
        }
    }
    fclose(market);
    int menu;
    
    do {
        cout << "\n========= MENU STOK BARANG =========\n";
        cout << "1. Lihat Barang (Sorting)\n";
        cout << "2. Cari Barang (Searching)\n";
        cout << "3. Tambah Barang Baru\n";
        cout << "4. Hapus Barang\n";
        cout << "5. Tambah Stok\n";
        cout << "6. Kurangi Stok\n";
        cout << "0. Keluar\n";
        cout << "=====================================\n";
        cout << "Pilih Menu: ";
        cin >> menu;
        cin.ignore(); 

        switch (menu) {
        case 1:
            lihat_barang();
            break;

        case 2: {
            string nama;
            cout << "Masukkan Nama Barang: ";
            getline(cin, nama);
            cari_barang(nama);
        } break;

        case 3: {
            string nama;
            int harga, jumlah;
            cout << "Masukkan Nama Barang  : ";
            getline(cin, nama);
            cout << "Masukkan Harga Barang : ";
            cin >> harga;
            cout << "Masukkan Jumlah Barang: ";
            cin >> jumlah;
            cin.ignore();
            tambah_barang(nama, harga, jumlah);
            simpan_ke_file();
        } break;

        case 4: {
            string nama;
            cout << "Masukkan Nama Barang yang akan dihapus: ";
            getline(cin, nama);
            hapus_barang(nama);
             simpan_ke_file();

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
             simpan_ke_file();

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
             simpan_ke_file();
        } break;

        case 0:
            cout << "Terima kasih! Datang kembali.\n";
            break;

        default:
            cout << "Pilihan tidak valid. Coba lagi.\n";
            break;
        }
    } while (menu != 0);

    // Hapus seluruh linked list utama dari memori sebelum keluar program
    hapusListSalinan(head);

    return 0;
}
