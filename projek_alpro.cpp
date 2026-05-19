#include <cstdio>
#include <iostream>
#include <cstring>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

FILE* market;

struct stok{
	string nama_barang;
	int harga, jumlah;
	stok* next;
	stok* prev;
	}; stok barang;
stok* head = nullptr;
stok* tail = nullptr;

void cetakTerurut(int kriteria, bool ascending) {
    vector<stok*> daftar;
    for (stok* bantu = head; bantu != nullptr; bantu = bantu->next) {
        daftar.push_back(bantu);
    }
    if (daftar.empty()) {
        cout << "Tidak ada barang.\n";
        return;
    }
    sort(daftar.begin(), daftar.end(), [kriteria, ascending](stok* a, stok* b) {
        if (kriteria == 1) {
            return ascending ? a->jumlah < b->jumlah : a->jumlah > b->jumlah;
        }
        return ascending ? a->harga < b->harga : a->harga > b->harga;
    });
    for (stok* barang : daftar) {
        cout << left << setw(20) << barang->nama_barang
             << setw(10) << barang->harga
             << setw(10) << barang->jumlah << endl;
    }
}

void lihat_barang(){
	int tampil, berdasarkan;
	cout << "Tampilkan berdasarkan:\n";
	cout << "1. stok\n";
	cout << "2. harga\n";
	cin >> berdasarkan;
	switch(berdasarkan){
	case 1:{
		cout << "1. stok terbanyak\n";
		cout << "2. stok terdikit\n";
		cin >> tampil;
		if (tampil == 1) {
			cetakTerurut(1, false);
		} else if (tampil == 2) {
			cetakTerurut(1, true);
		} else {
			cout << "Menu tidak ditemukan\n\n";
		}
	} break;
	case 2:{
		cout << "1. harga termahal\n";
		cout << "2. harga termurah\n";
		cin >> tampil;
		if (tampil == 1) {
			cetakTerurut(2, false);
		} else if (tampil == 2) {
			cetakTerurut(2, true);
		} else {
			cout << "Menu tidak ditemukan\n\n";
		}
	} break;
	default: {
		cout << "Menu tidak ditemukan\n\n";
	} break;
	}
	stok* bantu = head;
	bool ketemu = false;
	
	while (bantu != NULL) {
		if(bantu->nama_barang == nama){
			cout << "Barang ditemukan:\n";
			cout << left << setw(20) << bantu->nama_barang
				 << setw(10) << bantu->harga
				 << setw(10) << bantu->jumlah << endl;
			ketemu = true;
			break;
		}
		bantu = bantu->next;
	}
	
	if (!ketemu) {
		cout << "Barang dengan nama '" << nama << "' tidak ditemukan!\n";
	}
}
//tambah barang
void tambah_barang(string nama, int harga, int jumlah){
	// 1. Simpan ke dalam file
	market = fopen("projek.txt", "a");
	fprintf(market, "%s %d %d\n", nama.c_str(), harga, jumlah);
	fclose(market);
	
	// 2. Masukkan ke dalam linked list agar data langsung terlihat
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
}
void masuk_barang(){
	market = fopen("projek.txt", "r");
	if (market == NULL) return; // Keluar jika file belum ada
	
	char nama[100];
	int hrg, jml;
	
	// Membaca file dengan format: string, int, int
	while (fscanf(market, "%99s %d %d", nama, &hrg, &jml) == 3) {
		// 1. Buat node baru
		stok* nodeBaru = new stok;
		nodeBaru->nama_barang = nama;
		nodeBaru->harga = hrg;
		nodeBaru->jumlah = jml;
		nodeBaru->next = NULL;
		nodeBaru->prev = NULL;
		
		// 2. Masukkan ke linked list (Insert Last)
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

int main(){	
	masuk_barang(); // Muat data dari file ke linked list

	int menu;
do{

cout << "=========Menu=======" << endl;
cout << "1. Lihat Barang (sorting)\n";
cout << "2. Cari Barang (searching)\n";	 
cout << "3. Tambah Barang \n";
cout << "4. Hapus Barang\n";
cout << "5. tambah stok\n";
cout << "6. kurangi stok\n";
cout << "5. keluar\n";
cout<< "=====================\n";
cout << "Buka Menu : ";
cin >> menu;
	switch (menu){
		case 1: {
			lihat_barang();
			}break;
		case 2:{
			string nama;
			cout << "Masukkan Nama Barang  : ";
			cin.ignore();
			cin >> nama;
			cari_barang(nama);
		} break;
		case 3: {
			string nama;
			int harga, jumlah;
			cout << "Masukkan Nama Barang"; cin >> nama;
			cout << "Masukkan Harga Barang"; cin >> harga;
			cout << "Masukkan Jumlah Barang"; cin >> jumlah;
			tambah_barang(nama, harga, jumlah);
		} break;
		}
}while(menu != 0);	
}
