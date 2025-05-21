#include <iostream>
using namespace std;

const int MAX_CHAR = 100;

struct pesanan{
    char nama[MAX_CHAR];
    char jenis_roti[MAX_CHAR];
    float total_harga;
    pesanan* next;
};

pesanan* awalAntrean = NULL;
pesanan* ekorAntrean = NULL;

pesanan* awalRiwayat = NULL;
pesanan* ekorRiwayat = NULL;

void opsilain() {
    cout << "========================================  " << endl;
    cout << "  Pilihan tidak Valid, silakan coba lagi  " << endl;
    cout << "========================================  " << endl;
}
void berhenti() {
    char pilihan;
    cout << "Apakah Anda Ingin Kembali ke Menu Awal? (y/n): ";
    cin >> pilihan;
    if (pilihan == 'y' || pilihan == 'Y'){
        system("cls");
    } else if (pilihan == 'n' || pilihan == 'N') {
        cout << "Program selesai.\n";
        exit(0);
    } else {
        opsilain();
        berhenti();
    }
}
void tampilanmenu(int &menu) {
    cout << "\n====================== Menu ======================\n";
    cout << "|1. Tambah Pesanan                               |" << endl;
    cout << "|2. Layani Pembeli (simpan pesanan dalam Riwayat)|" << endl;
    cout << "|3. Tampilkan Daftar Pesanan dalam Antrean       |" << endl;
    cout << "|4. Batalkan Pesanan terakhir                    |" << endl;
    cout << "|5. Tampilkan Riwayat Pesanan                    | " << endl;
    cout << "|6. Exit                                         |" << endl;
    cout << "==================================================\n";
    cout << "\nPilih menu: ";
    cin >> menu;
}

// menggunakan proses enqueue yaitu menambahkan data
void tambahPesanan() {
    int jumlah;
    cout << "Mau pesan berapa? ";
    cin >> jumlah;
    cin.ignore(); 

    for (int i = 0; i < jumlah; i++) {
        pesanan* baru = new pesanan;

        cout << "\nNama Pemesan: ";
        cin.getline(baru->nama, MAX_CHAR);
        cout << "Jenis Roti: ";
        cin.getline(baru->jenis_roti, MAX_CHAR);
        cout << "Total Harga: Rp";
        cin >> baru->total_harga;
        cin.ignore();

        baru->next = nullptr;

        if (awalAntrean == nullptr) {
            awalAntrean = ekorAntrean = baru;
        } else {
            ekorAntrean->next = baru;
            ekorAntrean = baru;
        }

        cout << "Pesanan ditambahkan ke antrean.\n";
    }
}

// menggunakan proses dequeue yaitu memindahkan pesanan pertama ke riwayat
void simpanPesanan(){
    if (awalAntrean == NULL) {
        cout << "Antrean kosong!\n";
        return;
    }

    pesanan* pesananSelesai = awalAntrean;
    awalAntrean = awalAntrean->next;
    if (awalAntrean == nullptr) {
        ekorAntrean = nullptr;
    }

    // Tambah ke riwayat
    pesananSelesai->next = NULL;

    if (awalRiwayat == NULL) {
        awalRiwayat = ekorRiwayat = pesananSelesai;
    } else {
        ekorRiwayat->next = pesananSelesai;
        ekorRiwayat = pesananSelesai;
    }

    cout << "Pesanan dari " << pesananSelesai->nama << " telah dilayani.\n";

}

// menampilkan daftar pesanan dari antrean
void tampilkanAntrean() {
    if (awalAntrean == NULL) {
        cout << "Antrean kosong.\n";
        return;
    }

    cout << "\n=========== Daftar Antrean ===========\n";
    pesanan* bantu = awalAntrean;
    int no = 1;
    while (bantu != NULL) {
        cout << no++ << ". Nama       : " << bantu->nama << endl;
        cout << "   Jenis Roti : " << bantu->jenis_roti << endl;
        cout << "   Total Harga: Rp" << bantu->total_harga << endl;
        cout << "--------------------------------------\n";
        bantu = bantu->next;
    }
}

//menghapus pesanan dari antrean paling belakang menggunakan linked list
void batalkanPesanan() {
    if (awalAntrean == NULL) {
        cout << "Antrean kosong.\n";
        return;
    }

    // Jika antrean hanya satu pesanan
    if (awalAntrean == ekorAntrean) {
        cout << "Pesanan dari " << awalAntrean->nama << " dibatalkan.\n";
        delete awalAntrean;
        awalAntrean = ekorAntrean = NULL;
        return;
    }

    // Cari node sebelum ekorAntrean
    pesanan* bantu = awalAntrean;
    while (bantu->next != ekorAntrean) {
        bantu = bantu->next;
    }

    cout << "Pesanan dari " << ekorAntrean->nama << " dibatalkan.\n";
    delete ekorAntrean;
    ekorAntrean = bantu;
    ekorAntrean->next = NULL;
}

// Menampilkan daftar pesanan yang sudah selesai diproses (pesananSelesai), yang sebelumnya disimpan dalam antrean atau history pesanan
void tampilkanRiwayat() {
    if (awalRiwayat == NULL) {
        cout << "Riwayat kosong.\n";
        return;
    }

    pesanan* bantu = awalRiwayat;
    int no = 1;

    cout << "\nRiwayat Pesanan yang Telah Dilayani:\n";
    cout << "=======================================\n";

    while (bantu != NULL) {
        cout << no++ << ". Nama        : " << bantu->nama << endl;
        cout << "   Jenis Roti  : " << bantu->jenis_roti << endl;
        cout << "   Total Harga : Rp" << bantu->total_harga << endl;
        cout << "---------------------------------------\n";
        bantu = bantu->next;
    }
}

int main() {
    int pilihan;
    do {
        tampilanmenu(pilihan);
        switch (pilihan) {
            case 1: tambahPesanan();    break;
            case 2: simpanPesanan();    break;
            case 3: tampilkanAntrean(); break;
            case 4: batalkanPesanan();  break;
            case 5: tampilkanRiwayat(); break;
            case 6: 
                    cout << "\nTerima kasih telah memesan di Toko Roti 'Manis Lezat'\n";
                    cout <<"-----------------Datanglah Kembali--------------------\n\n";
                    break;
            default: 
                    opsilain();
                    berhenti();
        }
        berhenti();
    } while (pilihan != 6);
    return 0;
}