/*
 * Nama   : Lina Lisnawati
 * NIM    : 2507427
 * Kelas  : 2B
 * Program: Virtual Pet Simulator (PawPal)
 */

#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <ctime>
using namespace std;

// Deklarasi fungsi pausegame agar bisa dipanggil oleh fungsi lain di atasnya
void pausegame();

struct pet{
    string jenis;
    string nama_pet;
    int lapar;
    int bahagia;
    int energi;
    int koin;
    int makanan;
    int apel;
    int daging;
    int roti;
    int kesehatan;
};

struct aktivitas{
    string pesan;
    aktivitas* next;
};

int ValidasiInput(int min, int max, string pesan) {
    int input;
    while (true) {
        cout << pesan;
        cin >> input;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Pilihan tidak valid! Input harus berupa angka! \n";
        }
        else if (input < min || input > max) {
            cout << "Pilihan tidak valid! \n";
        }
        else{
            return input;
        }
    }
}

// Create
void TambahAktivitas(aktivitas* &head, string keterangan){
    aktivitas* baru = new aktivitas;
    baru->pesan = keterangan;
    baru->next = head;
    head = baru;
}

void BeliMakanan(pet &p, aktivitas* &head){
    int pilih;

    cout << "\n=== TOKO MAKANAN ===" << endl;
    cout << "1. Apel (Harga: 5, Lapar -5)" << endl;
    cout << "2. Daging (Harga: 15, Lapar -15)" << endl;
    cout << "3. Roti (Harga: 7, Lapar: -10)" << endl;
    cout << "4. Kembali" << endl;
    pilih = ValidasiInput(1,4, "Pilih makanan yang ingin dibeli (masukkan angka): ");

    if (pilih == 4) return;

    if (pilih == 1){
        if (p.koin >= 5){
            p.koin -= 5;
            p.apel++;
            TambahAktivitas(head, "Membeli apel");
            cout << "Berhasil membeli apel!\n";
            cout << "====================" << endl;
            cout << "Sisa koin: " << p.koin << endl;
            cout << "=== STOK MAKANAN ===" << endl;
            cout << "\U0001F34E Apel   : " << p.apel << endl;
            cout << "\U0001F356 Daging : " << p.daging << endl;
            cout << "\U0001F35E Roti   : " << p.roti << endl;
        } 
        else cout << "Koin tidak cukup!\n";
    }
    else if (pilih == 2){
        if (p.koin >= 15){
            p.koin -= 15;
            p.daging++;
            TambahAktivitas(head, "Membeli daging");
            cout << "Berhasil membeli daging!\n";
            cout << "====================" << endl;
            cout << "Sisa koin: " << p.koin << endl;
            cout << "=== STOK MAKANAN ===" << endl;
            cout << "\U0001F34E Apel   : " << p.apel << endl;
            cout << "\U0001F356 Daging : " << p.daging << endl;
            cout << "\U0001F35E Roti   : " << p.roti << endl;
        } 
        else cout << "Koin tidak cukup!\n";
    }
    else if (pilih == 3){
        if (p.koin >= 7){
            p.koin -= 7;
            p.roti++;
            TambahAktivitas(head, "Membeli roti");
            cout << "Berhasil membeli roti!\n";
            cout << "====================" << endl;
            cout << "Sisa koin: " << p.koin << endl;
            cout << "=== STOK MAKANAN ===" << endl;
            cout << "\U0001F34E Apel   : " << p.apel << endl;
            cout << "\U0001F356 Daging : " << p.daging << endl;
            cout << "\U0001F35E Roti   : " << p.roti << endl;
        } 
        else cout << "Koin tidak cukup!\n";
    }

    pausegame();
}

// Read
void LihatAktivitas(aktivitas* &head){
    cout << "\n======= \U0001F4DC RIWAYAT AKTIVITAS PET =======\n";
    aktivitas* temp = head;
    
    if (!temp) {
        cout << "Belum ada aktivitas yang dilakukan\n";
    } else {
        while (temp) {
            cout << "- " << temp->pesan << endl;
            temp = temp->next;
        }
    }
    cout << "===============================================\n";
    pausegame();
}

// Delete riwayat aktivitas (jika status pet penuh)
void HapusAktivitas(aktivitas* &head){
    aktivitas* temp;
    while (head != NULL){
        temp = head; 
        head = head->next;
        delete temp;
    }
}

// Cek apakah status pet sudah penuh (Lapar, Bahagia, energi)
bool CekStatusPenuh(pet &p){
    return (p.lapar <= 0 && p.bahagia >= 100 && p.energi >= 100);
}

// update
void Makan(pet &p, aktivitas* &head){
    int pilih;
    cout << "\n=== PILIH MAKANAN ===" << endl;
    cout << "1. \U0001F34E Apel     (stok: " << p.apel << ")" << endl;
    cout << "2. \U0001F356 Daging   (stok: " << p.daging << ")" << endl;
    cout << "3. \U0001F35E Roti     (stok: " << p.roti<< ")" << endl;
    cout << "4. Kembali" << endl;
    pilih = ValidasiInput(1, 4, "Pilih makanan: ");

    if (pilih == 4) return;

    if (pilih == 1){
        if (p.apel > 0){
            p.apel--;
            p.lapar -= 5;
            TambahAktivitas(head, "Memberi apel");
            cout << "Berhasil memberi apel!\n";
            cout << "Lapar sekarang: " << p.lapar << endl;
        }
        else cout << "Apel habis!\n";
    }
    else if (pilih == 2){
        if (p.daging > 0){
            p.daging--;
            p.lapar -= 15;
            TambahAktivitas(head, "Memberi daging");
            cout << "Berhasil memberi daging!\n";
            cout << "Lapar sekarang: " << p.lapar << endl;
        }
        else cout << "Daging habis!\n";
    }
    else if (pilih == 3){
        if (p.roti > 0){
            p.roti--;
            p.lapar -= 7;
            TambahAktivitas(head, "Memberi roti");
            cout << "Berhasil memberi roti!\n";
            cout << "Lapar sekarang: " << p.lapar << endl;
        }
        else cout << "Roti habis!\n";
    }

    if (p.lapar < 0) p.lapar = 0;
    
    pausegame();
}

// Fungsi Tidur
void Tidur(pet &p, aktivitas* &head) {
    int pilih;

    while (true) {
        cout << "\n=== PILIH WAKTU TIDUR ===\n";
        cout << "1. 5 detik (15 energi)\n";
        cout << "2. 10 detik (35 energi)\n";
        cout << "3. 15 detik (50 energi)\n";
        cout << "4. Kembali\n";
        pilih = ValidasiInput(1, 4, "Pilihan: ");

        int durasi = 0, energi_dapat = 0;

        if (pilih == 4) return;

        if (pilih == 1) { durasi = 5; energi_dapat = 15; }
        else if (pilih == 2) { durasi = 10; energi_dapat = 35; }
        else if (pilih == 3) { durasi = 15; energi_dapat = 50; }

        cout << p.nama_pet << " sedang tidur...\n";

        for (int i = durasi; i > 0; i--) {
            cout << "Sisa waktu: " << i << " detik\r";
            cout.flush();
            this_thread::sleep_for(chrono::seconds(1));
        }

        p.energi += energi_dapat;
        if (p.energi > 100) p.energi = 100;

        TambahAktivitas(head, "Tidur " + to_string(durasi) + " detik");

        cout << "\nSelesai tidur!\n";
        cout << "Energi sekarang: " << p.energi << endl;
        pausegame();
        return; 
    }
}

const int Jumlah_lokasi = 5;

string namalokasi[Jumlah_lokasi] = {"Rumah", "Taman", "Arena", "Klinik", "Toko"};

int adj[Jumlah_lokasi][Jumlah_lokasi] = 
{
    {0, 1, 0, 0, 0}, // Rumah
    {1, 0, 1, 0, 0}, // Taman
    {0, 1, 0, 1, 0}, // Arena
    {0, 0, 1, 0, 1}, // klinik
    {0, 0, 0, 1, 0}  // Toko
}; 

void Main(pet &p, aktivitas* &head) {
    int pilih;

    if (p.energi <= 0) {
        cout << p.nama_pet << " terlalu lelah untuk bermain!\n";
        pausegame();
        return;
    }

    cout << "\n=== PILIH AKTIVITAS MAIN ===\n";
    cout << "Energi saat ini: " << p.energi << endl;
    cout << "1. Main bola (+15 koin, +15 bahagia, -10 energi)\n";
    cout << "2. Jalan-jalan (+20 koin, +20 bahagia, -15 energi)\n";
    cout << "3. Main lompat tinggi (+10 koin, +10 bahagia, -5 energi)\n";
    cout << "4. Kembali\n";
    pilih = ValidasiInput(1, 4, "Pilihan: ");

    if (pilih == 4) return;

    if (pilih == 1) {
        if (p.energi < 10) {
            cout << p.nama_pet << " terlalu lelah untuk bermain bola!\n";
            pausegame();
            return;
        }
        p.koin += 15;
        p.energi -= 10;
        p.bahagia += 10;
        TambahAktivitas(head, "Main bola");
    }
    else if (pilih == 2) {
        if (p.energi < 15) {
            cout << p.nama_pet << " terlalu lelah untuk jalan-jalan!\n";
            pausegame();
            return;
        }
        p.koin += 20;
        p.energi -= 15;
        p.bahagia += 15;
        TambahAktivitas(head, "Jalan-jalan");
    }
    else if (pilih == 3) {
        if (p.energi < 5) {
            cout << p.nama_pet << " terlalu lelah untuk main lompat tinggi!\n";
            pausegame();
            return;
        }
        p.koin += 10;
        p.energi -= 5;
        p.bahagia += 10;
        TambahAktivitas(head, "Main lompat tinggi");
    }

    // Efek tambahan
    p.lapar += 5;

    // Batas maksimum & minimum
    if (p.bahagia > 100) p.bahagia = 100;
    if (p.energi < 0) p.energi = 0;
    if (p.lapar > 100) p.lapar = 100;

    cout << "\nSelesai bermain!\n";
    cout << "Bahagia sekarang   : " << p.bahagia << endl;
    cout << "Koin sekarang      : " << p.koin << endl;
    pausegame();
}

// Fungsi untuk update status pet setiap kali melakukan aktivitas
void UpdateStatus(pet &p) {
    if (p.lapar > 0) p.lapar += 1;
    if (p.energi < 100) p.energi -= 1;
    if (p.bahagia < 100) p.bahagia -= 1;

    // Batas
    if (p.lapar > 100) p.lapar = 100;
    if (p.energi < 0) p.energi = 0;
    if (p.bahagia < 0) p.bahagia = 0;

    // Pengaruh sakit (jika kelaparan dan lelah)
    if(p.lapar >= 80 && p.energi <= 20) {
        p.kesehatan -= 5;
    }

    if(p.kesehatan < 0) p.kesehatan = 0;
}

void pausegame() {
    cout << "\nTekan enter untuk melanjutkan...";
    cin.ignore(1000, '\n');
    if (cin.peek() == '\n') cin.get();
}

void InisialisasiPetBaru(pet &p) {
    int pilih_jenis_pet;

    cout << "\n=== PILIH PET BARU ===\n";
    cout << "1. Kucing\n";
    cout << "2. Hamster\n";
    cout << "3. Kura-kura\n";
    cout << "4. Kelinci\n";
    cout << "5. Bunglon\n";
    pilih_jenis_pet = ValidasiInput(1, 5, "Pilihanmu: ");

    if (pilih_jenis_pet == 1) p.jenis = "Kucing";
    else if (pilih_jenis_pet == 2) p.jenis = "Hamster";
    else if (pilih_jenis_pet == 3) p.jenis = "Kura-kura";
    else if (pilih_jenis_pet == 4) p.jenis = "Kelinci";
    else if (pilih_jenis_pet == 5) p.jenis = "Bunglon";
    else p.jenis = "Tidak diketahui";

    cout << "Masukan nama pet: ";
    cin >> p.nama_pet;

    // Reset status
    p.lapar = rand() % 21 + 40;
    p.bahagia = rand() % 21 + 40;
    p.energi = rand() % 21 + 40;
    p.apel = 0;
    p.daging = 0;
    p.roti = 0;
    p.kesehatan = 100;

    cout << "\nPet baru berhasil dibuat!\n";
    cout << "Koin kamu tetap: " << p.koin << endl;
    pausegame();
}

// fungsi klinik di fitur lokasi
void Klinik(pet &p, aktivitas* &head) {
    int pilih;

    cout << "\n=== KLINIK HEWAN ===\n";
    cout << "1. Periksa kesehatan pet\n";
    cout << "2. Berobat (-20 Koin)\n";
    cout << "3. Kembali\n";
    pilih = ValidasiInput(1, 3, "Pilihan: ");

    switch(pilih) {
        case 1: 
            cout << "\nKesehatan saat ini: " << p.kesehatan << endl;
            if(p.kesehatan >= 80) cout << "Pet sangat sehat!\n";
            else if(p.kesehatan >= 50) cout << "Pet cukup sehat!\n";
            else cout << "Pet harus segera berobat!\n";
            pausegame();
            break;

        case 2:
            if(p.koin < 20) {
                cout << "Koin tidak cukup\n";
                pausegame();
                break;
            }

            if(p.kesehatan >= 100) {
                cout << "Status kesehatan pet penuh!\n";
                pausegame();
                break;
            }

            p.koin -= 20;
            p.kesehatan += 30;

            if(p.kesehatan > 100) p.kesehatan = 100;

            TambahAktivitas(head,"Berobat di klinik");
            cout << "Pet berhasil diobati!\n";
            pausegame();
            break;
    }
}

void jalanjalan(int &posisi) {
    int tujuan[10];
    int jumlah = 0;

    cout << "\nLokasi Saat Ini : " << namalokasi[posisi] << endl;
    cout << "Tujuan tersedia:\n";

    for(int i = 0; i < 4; i++) {
        if(adj[posisi][i] == 1) {
            jumlah++;
            cout << jumlah << ". " << namalokasi[i] << endl;
            tujuan[jumlah] = i;
        }
    }
    
    int pilih = ValidasiInput(1, jumlah, "Pilih tujuan: ");
    posisi = tujuan[pilih];
    
    cout << "\n\U0001F4CD Sekarang berada di " << namalokasi[posisi] << endl;
    pausegame();
}

void CariItem(pet &p, aktivitas* &head) {
    int hadiah = rand() % 3;

    if(hadiah == 0) {
        p.apel++;
        cout << "Kamu menemukan sebuah apel!\n";
        TambahAktivitas(head, "Menemukan apel di taman");  
    }
    else if(hadiah == 1) {
        p.roti++;
        cout << "Kamu menemukan sebuah roti!\n";
        TambahAktivitas(head, "Menemukan roti di taman");
    }
    else {
        p.koin += 10;
        cout << "Menemukan 10 koin!!\n";
        TambahAktivitas(head, "Menemukan koin di taman");
    }
    pausegame();
}

int main() {
    pet myPet;
    int pilih_jenis_pet;
    aktivitas* head = NULL;

    srand(time(0)); 

    cout << "====== \U0001F3AE PawPal ======\n";
    cout << "Pilih jenis pet awalmu: \n";
    cout << "1. Kucing\n";
    cout << "2. Hamster\n";
    cout << "3. Kura-kura\n";
    cout << "4. Kelinci\n";
    cout << "5. Bunglon\n";
    pilih_jenis_pet = ValidasiInput(1, 5, "Pilihanmu: ");
    
    string jenisPet[5] = {"Kucing", "Hamster", "Kura-kura", "Kelinci", "Bunglon"};
    myPet.jenis = jenisPet[pilih_jenis_pet - 1];

    cout << "Masukan nama pet: ";
    cin >> myPet.nama_pet;

    myPet.lapar = rand() % 21 + 40;
    myPet.bahagia = rand() % 21 + 40;
    myPet.energi = rand() % 21 + 40;
    myPet.kesehatan = 100;
    myPet.koin = 50;
    myPet.apel = 0;
    myPet.daging = 0;
    myPet.roti = 0;

    cout << "\nPet memiliki kondisi awal acak!\n";
    cout << "==============================\n";
    cout << "Nama       : " << myPet.nama_pet << endl;
    cout << "Jenis      : " << myPet.jenis << endl;
    pausegame();

    int pilihan;
    int posisi = 0;
    bool jalan = true;

    while (jalan) {
        cout << "\n=================================\n";
        cout << "         \U0001F3AE PawPal        \n";
        cout << "=================================\n";

        if (myPet.kesehatan <= 30) {
            cout << "\n \U000026A0 PERINGATAN!\n";
            cout << myPet.nama_pet << " sedang sakit! Segera ke klinik!\n";
        }

        cout << "\n Lokasi saat ini: " << namalokasi[posisi] << endl;
        cout << "1. \U0001F4CA Lihat Status\n";
        cout << "2. \U0001F37D Jalan-jalan\n";
        cout << "3. \U0001F37D Makan\n";
        cout << "4. \U0001F6D2 Beli Makanan\n";
        cout << "5. \U0001F634 Tidur\n";
        cout << "6. \U0001F3BE Main\n";
        cout << "7. \U0001F4DC Lihat Aktivitas\n";

        if (CekStatusPenuh(myPet)) {
            cout << "8. Lepas ke alam bebas (Pet dalam keadaan terbaik!)\n";
            cout << "9. Keluar\n";
        } else {
            cout << "8. Keluar\n";
        }

        pilihan = ValidasiInput(1, 9, "Pilihan: ");

        switch (pilihan) {
            case 1:
                cout << "\n========== STATUS PET ==========\n";
                cout << "Nama       : " << myPet.nama_pet << endl;
                cout << "Jenis      : " << myPet.jenis << endl;
                cout << "--------------------------------\n";
                cout << "\U0001F356 Lapar      : " << myPet.lapar << endl;
                cout << "\U0001F60A Bahagia    : " << myPet.bahagia << endl;
                cout << "\U000026A1 Energi     : " << myPet.energi << endl;
                cout << "\U0001F4B0 Koin       : " << myPet.koin << endl;
                cout << "\U0001F496 Kesehatan  : " << myPet.kesehatan;

                if(myPet.kesehatan <= 30) cout << " (Sedang sakit!)\n";
                else cout << endl;
                
                pausegame();
                break;

            case 2:
                jalanjalan(posisi);
                if (posisi == 1) CariItem(myPet, head);
                else if (posisi == 3) Klinik(myPet, head);
                break;

            case 3:
                if (namalokasi[posisi] != "Rumah") {
                    cout << "Pet harus berada di rumah untuk makan!\n";
                    pausegame();
                    break;
                }
                Makan(myPet, head);
                UpdateStatus(myPet);
                break;

            case 4:
                if (namalokasi[posisi] != "Toko") {
                    cout << "Pet harus berada di toko untuk membeli makanan!\n";
                    pausegame();
                    break;
                }
                BeliMakanan(myPet, head);
                UpdateStatus(myPet);
                break;

            case 5:
                if (namalokasi[posisi] != "Rumah") {
                    cout << "Pet harus berada di rumah untuk tidur!\n";
                    pausegame();
                    break;
                }
                Tidur(myPet, head);
                UpdateStatus(myPet);
                break;

            case 6:
                if (namalokasi[posisi] != "Arena") {
                    cout << "Pet harus berada di arena untuk bermain!\n";
                    pausegame();
                    break;
                }
                Main(myPet, head);
                UpdateStatus(myPet);
                break;

            case 7:
                LihatAktivitas(head);
                break;

            case 8:
                if (CekStatusPenuh(myPet)) {
                    char konfirmasi;
                    cout << "\nStatus pet sudah penuh! Apakah anda ingin melepas pet ke alam bebas? (y/n): ";
                    cin >> konfirmasi;

                    if (konfirmasi == 'y' || konfirmasi == 'Y') {
                        int reward = 50;
                        myPet.koin += reward;

                        cout << "Pet berhasil dilepaskan ke alam bebas!\n";
                        cout << "Anda mendapatkan reward sebanyak " << reward << " Koin!\n";

                        HapusAktivitas(head);
                        InisialisasiPetBaru(myPet);
                    } else {
                        cout << "Pet tetap dirawat. Lanjutkan rawat pet-mu dengan baik ya!\n";
                        pausegame();
                    }
                } else {
                    jalan = false;
                    cout << "\nAnda telah keluar dari game. Terima kasih telah memainkan PawPal ^-^\n";
                }
                break;

            case 9:
                if (CekStatusPenuh(myPet)) {
                    jalan = false;
                    cout << "\nAnda telah keluar dari game. Terima kasih telah memainkan PawPal ^-^\n";
                } else {
                    cout << "Pilihan tidak valid!\n";
                    pausegame();
                }
                break;

            default:
                cout << "Pilihan tidak valid!\n";
                pausegame();
        }
    }

    return 0;
}