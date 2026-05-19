#include <cstdio>
#include <iostream>
#include <cstring>
#include <iomanip>
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

//sorting barang dari urutan kecil ke besar
void urutKecil(){
	stok* bantu = head;
	while (bantu != NULL) {
        cout << left << setw(20) << bantu->nama_barang
             << setw(10) << bantu->harga
             << setw(10) << bantu->jumlah << endl;
        bantu = bantu->next;
    }
}
//sorting barang dari urutan besar ke kecil	
void urutBesar(){
	stok* bantu = tail;
	while(bantu != NULL){
		cout << left << setw(20) << bantu-> nama_barang
		<< setw(10) << bantu -> harga
		<< setw(10) << bantu -> jumlah << endl;
		bantu = bantu-> prev;
	}
}

void lihat_barang(){
	market=fopen("projek.txt", "r");
	int tampil, berdasarkan;
	cout << "tampil kan harga berdasarkan:\n";
	cout << "1. stok\n";
	cout << "2. harga\n";
	cin >> berdasarkan;
	switch(berdasarkan){
	case 1:{
		cout << "1. stok terbanyak\n";
		cout << "2. stok terdikit\n";
		cin>>tampil;
		switch(tampil){
			case 1:{
				urutBesar();
				}break;
			case 2:{
				urutKecil();
				}break;
			default: {cout << "menu tidak ditemukan\n\n";}	
			}		
		}break;	
	case 2:{
		cout << "1. harga termahal\n";
		cout << "2. harga termurah\n";
		cin>>tampil;
		switch(tampil){
			case 1:{
				urutBesar();
				}break;
			case 2:{
				urutKecil();
				}break;
			default: {cout << "menu tidak ditemukan\n\n";}	
			}	
		}break;	
	}
	fclose(market);
}

//menu 2 (cari/searching)
void cari_barang(string nama){
market = fopen("projek.txt", "r");
stok* bantu=head;
while (bantu != NULL)
{
	if(bantu->nama_barang==nama){
		cout << left << setw(20) << bantu->nama_barang
			 << setw(10) << bantu->harga
			 << setw(10) << bantu->jumlah << endl;
		break;
	}else{
		bantu = bantu->next;
	}
}

fclose(market);
}
//tambah barang
void tambah_barang(string nama, int harga, int jumlah){
	// 1. Simpan ke dalam file
	market = fopen("projek.txt", "a");
	fprintf(market, "%s %d %d\n", nama.c_str(), harga, jumlah);
	fclose(market);
	
	// 2. Masukkan ke dalam linked list agar data langsung terlihat
	// stok* nodeBaru = new stok;
	// nodeBaru->nama_barang = nama;
	// nodeBaru->harga = harga;
	// nodeBaru->jumlah = jumlah;
	// nodeBaru->next = NULL;
	// nodeBaru->prev = NULL;
	
	// if (head == NULL) {
	// 	head = nodeBaru;
	// 	tail = nodeBaru;
	// } else {
	// 	tail->next = nodeBaru;
	// 	nodeBaru->prev = tail;
	// 	tail = nodeBaru;
	// }
}
void masuk_barang(){
	market = fopen("projek.txt", "r");
	if (market!=NULL){
		
	}
	// if (market == NULL) return; // Keluar jika file belum ada
	
	// char nama[100];
	// int hrg, jml;
	
	// // Membaca file dengan format: string, int, int
	// while (fscanf(market, "%99s %d %d", nama, &hrg, &jml) == 3) {
	// 	// 1. Buat node baru
	// 	stok* nodeBaru = new stok;
	// 	nodeBaru->nama_barang = nama;
	// 	nodeBaru->harga = hrg;
	// 	nodeBaru->jumlah = jml;
	// 	nodeBaru->next = NULL;
	// 	nodeBaru->prev = NULL;
		
	// 	// 2. Masukkan ke linked list (Insert Last)
	// 	if (head == NULL) {
	// 		head = nodeBaru;
	// 		tail = nodeBaru;
	// 	} else {
	// 		tail->next = nodeBaru;
	// 		nodeBaru->prev = tail;
	// 		tail = nodeBaru;
	// 	}
	// }
	// fclose(market);
}

int main(){	
	int menu;
do{

cout << "=========Menu=======" << endl;
cout << "1. Lihat Barang (sorting)\n";
cout << "2. Cari Barang (searching)\n";	
cout << "3. Tambah Barang \n";
cout << "4. Hapus Barang\n";
cout << "5. keluar\n";
cout<< "=====================\n";
cout << "Buka Menu : ";
cin >> menu;
	switch (menu){
		case 1: {
			lihat_barang();
			}break;
		case 2:{
			int harga; 
		string nama;
			cout << "Masukkan Nama Barang  : ";
			cin.ignore();
			cin >> nama;
			cari_barang(nama);
			}
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
