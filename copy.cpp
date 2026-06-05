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

// Deklarasi fungsi pausegame
void pausegame();

const int jumlahTabung = 4; 
const int kapasitas = 3;

string tabung[jumlahTabung][kapasitas];
int topTabung[jumlahTabung]; 

struct pet{
    string jenis;
    string nama_pet;
    int lapar;
    int bahagia;
    int energi;
    int koin;
    int skillPoint;
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

struct Skill{
    string namaSkill;
    bool terbuka;

    Skill* kiri;
    Skill* kanan;
};

// Validasi input + pembersihan buffer otomatis agar Enter tidak dobel
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
            cin.ignore(1000, '\n'); // Membersihkan sisa enter di buffer
            return input;
        }
    }
}

// Fungsi jeda game
void pausegame() {
    cout << "\nTekan enter untuk melanjutkan...";
    cin.get();
}

// Create Linked List
void TambahAktivitas(aktivitas* &head, string keterangan){
    aktivitas* baru = new aktivitas;
    baru-> pesan = keterangan;
    baru -> next = head;
    head = baru;
}

Skill* CariSkill(Skill* root, string nama);

void BeliMakanan(pet &p, aktivitas* &head, Skill* skillRoot){
    int pilih;
    Skill* berhitung = CariSkill(skillRoot,"Berhitung");

    int hargaApel = 5;
    int hargaDaging = 15;
    int hargaRoti = 7;

    if(berhitung != NULL && berhitung->terbuka)
    {
        hargaApel = 4;
        hargaDaging = 12;
        hargaRoti = 5;
    }

    cout << "\n=== TOKO MAKANAN ===" << endl;
    cout << "1. Apel (Harga: " << hargaApel << ", Lapar -5)" << endl;
    cout << "2. Daging (Harga: " << hargaDaging << ", Lapar -15)" << endl;
    cout << "3. Roti (Harga: " << hargaRoti << ", Lapar -10)" << endl;
    cout << "4. Kembali" << endl;
    pilih = ValidasiInput(1,4, "Pilih makanan yang ingin dibeli(masukkan angka): ");

    if (pilih == 4) return;

    if (pilih == 1){
        if (p.koin >= hargaApel){
            p.koin -= hargaApel;
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
        else cout << "Koin tidak cukup!";
    }
    else if (pilih == 2){
        if (p.koin >= hargaDaging){
            p.koin -= hargaDaging;
            p.daging++;
            TambahAktivitas(head, "Membeli daging");
            cout << "Berhasil membeli daging!\n";
            cout << "====================" << endl;
            cout << "Sisa koin: " << p.koin << endl;

            cout << "=== STOK MAKANAN ===" << endl;
            cout << "\U0001F34E Apel   : " << p.apel << endl;
            cout << "\U0001F356 Daging : " << p.daging << endl;
            cout << "\U0001F35E Roti   : " << p.roti << endl;
        } else cout << "Koin tidak cukup!\n";
    }
    else if (pilih == 3){
        if (p.koin >= hargaRoti){
            p.koin -= hargaRoti;
            p.roti++;
            TambahAktivitas(head, "Membeli roti");
            cout << "Berhasil membeli roti!\n";
            cout << "====================" << endl;
            cout << "Sisa koin: " << p.koin << endl;

            cout << "=== STOK MAKANAN ===" << endl;
            cout << "\U0001F34E Apel   : " << p.apel << endl;
            cout << "\U0001F356 Daging : " << p.daging << endl;
            cout << "\U0001F35E Roti   : " << p.roti << endl;
        } else cout << "Koin tidak cukup!\n";
    }
    else {
        cout << "Makanan tidak tersedia!\n";
    }
    pausegame();
}

// Read Linked List
void LihatAktivitas(aktivitas* &head){
    cout << "\n======= \U0001F4DC RIWAYAT AKTIVITAS PET =======\n";
    aktivitas* temp = head;
    if (!temp) cout << "Belum ada aktivitas yang dilakukan" << endl;
    while (temp) {
        cout << "- " << temp->pesan << endl;
        temp = temp-> next;
    }
    cout << "==============================" << endl;
    pausegame();
}

// Delete Linked List
void HapusAktivitas(aktivitas* &head){
    aktivitas* temp;
    while (head != NULL){
        temp = head; 
        head = head->next;
        delete temp;
    }
}

// Cek status penuh
bool CekStatusPenuh(pet &p){
    return (p. lapar <= 0 && p.bahagia >= 100 && p.energi >= 100);
}

// Interaksi Makan
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
        else cout << "Apel habis!";
    }
    else if (pilih == 2){
        if (p.daging > 0){
            p.daging--;
            p.lapar -= 15;
            TambahAktivitas(head, "Memberi daging");
            cout << "Berhasil memberi daging!\n";
            cout << "Lapar sekarang: " << p.lapar << endl;
        }
        else cout << "Daging habis!";
    }
    else if (pilih == 3){
        if (p.roti > 0){
            p.roti--;
            p.lapar -= 7;
            TambahAktivitas(head, "Memberi roti");
            cout << "Berhasil memberi roti!\n";
            cout << "Lapar sekarang: " << p.lapar << endl;
        }
        else cout << "Roti habis!";
    }
    else {
        cout << "Pilihan tidak valid!";
    }

    if (p.lapar < 0) p.lapar = 0;
    pausegame();
}

// Interaksi Tidur
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
        else { cout << "Pilihan tidak valid!\n"; continue; }

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

// Pengelompokan Interaksi Rumah (Makan & Tidur)
void MenuRumah(pet &p, aktivitas* &head) {
    int pilih;
    while(true) {
        cout << "\n=== INTERAKSI DI RUMAH ===\n";
        cout << "1. \U0001F37D Makan\n";
        cout << "2. \U0001F634 Tidur\n";
        cout << "3. Kembali ke Menu Utama\n";
        pilih = ValidasiInput(1, 3, "Pilihan: ");
        
        if (pilih == 1) Makan(p, head);
        else if (pilih == 2) Tidur(p, head);
        else break;
    }
}

// Fitur Tree
Skill* BuatSkill(string nama) {
    Skill* baru = new Skill;
    baru->namaSkill = nama;
    baru->terbuka = false;
    baru->kiri = NULL;
    baru->kanan = NULL;
    return baru;
}

Skill* BuatSkillTree() {
    Skill* root = BuatSkill("Dasar");
    root->terbuka = true;

    root->kiri = BuatSkill("Kelincahan");
    root->kanan = BuatSkill("Kecerdasan");

    root->kiri->kiri = BuatSkill("Sprint");
    root->kiri->kanan = BuatSkill("Atletis");

    root->kanan->kiri = BuatSkill("Puzzle");
    root->kanan->kanan = BuatSkill("Berhitung");

    return root;
}

void TampilkanSkill(Skill* root, int level = 0) {
    if(root == NULL) return;
    for(int i=0;i<level;i++) cout << "   ";
    cout << "- " << root->namaSkill;
    if(root->terbuka) cout << " [TERBUKA]";
    else cout << " [TERKUNCI]";
    cout << endl;

    TampilkanSkill(root->kiri, level + 1);
    TampilkanSkill(root->kanan, level + 1);
}

Skill* CariSkill(Skill* root, string nama) {
    if(root == NULL) return NULL;
    if(root->namaSkill == nama) return root;

    Skill* kiri = CariSkill(root->kiri, nama);
    if(kiri != NULL) return kiri;

    return CariSkill(root->kanan, nama);
}

Skill* CariParent(Skill* root, Skill* target) {
    if(root == NULL) return NULL;
    if(root->kiri == target || root->kanan == target) return root;

    Skill* kiri = CariParent(root->kiri, target);
    if(kiri != NULL) return kiri;

    return CariParent(root->kanan, target);
}

void UnlockSkill(Skill* root, string nama, pet &p) {
    Skill* skill = CariSkill(root, nama);
    Skill* parent = CariParent(root, skill);

    if(skill == NULL){ cout << "Skill tidak ditemukan!\n"; return; }
    if(skill->terbuka){ cout << "Skill sudah terbuka!\n"; return; }
    if(p.skillPoint < 3){ cout << "Skill Point tidak cukup!\n"; return; }
    if(parent != NULL && !parent->terbuka){
        cout << "Buka skill " << parent->namaSkill << " terlebih dahulu!\n"; return;
    }

    p.skillPoint -= 3;
    skill->terbuka = true;

    // Bonus permanen saat unlock
    if(nama == "Kelincahan") { p.energi += 10; }
    else if(nama == "Sprint") { p.bahagia += 5; }
    else if(nama == "Atletis") { p.energi += 5; p.bahagia += 5; }
    else if(nama == "Kecerdasan") { p.skillPoint += 2; }
    else if(nama == "Puzzle") { p.bahagia += 10; }
    else if(nama == "Berhitung") { p.koin += 20; }

    if(p.energi > 100) p.energi = 100;
    if(p.bahagia > 100) p.bahagia = 100;

    cout << nama << " berhasil dibuka!\n";
    cout << "Bonus skill telah diterapkan!\n";
}

// Fitur Stack (game susun bola)
void createStack() {
    for (int i = 0; i < jumlahTabung; i++) topTabung[i] = -1;
}

bool isEmpty(int i) { return topTabung[i] == -1; }
bool isFull(int i) { return topTabung[i] == kapasitas -1; }

void push(int i, string data) {
    if(!isFull(i)) {
        topTabung[i]++;
        tabung[i][topTabung[i]] = data;
    }
}

string pop(int i) {
    if (!isEmpty(i)) return tabung[i][topTabung[i]--];
    return "";
}

void isiAwal() {
    createStack();
    push(0, "biru"); push(0, "kuning"); push(0, "hijau");
    push(1, "kuning"); push(1, "kuning"); push(1, "hijau");
    push(2, "hijau"); push(2, "biru"); push(2, "biru");
}

void display() {
    cout << "Isi Tabung:" << endl;
    for (int i = 0; i < jumlahTabung; i++) {
        cout << "Tabung " << i + 1<< ": ";
        for (int j = 0; j <= topTabung[i]; j++) cout << tabung[i][j] << " ";
        cout << endl;
    }
}

void pindah(int asal, int tujuan) {
    if(isEmpty(asal)){ cout << "Tabung asal kosong" << endl; return; }
    if(isFull(tujuan)){ cout << "Tabung Tujuan penuh" << endl; return; }

    string warna = tabung[asal][topTabung[asal]];
    pop(asal);
    push(tujuan, warna);

    cout << "Berhasil pindah" << endl;
}

bool cekMenang() {
    for (int i = 0; i < jumlahTabung; i++) {
        if (!isEmpty(i)) {
            if (topTabung[i] != kapasitas - 1) return false;
            string warna = tabung[i][0];
            for (int j = 1; j <= topTabung[i]; j++) {
                if (tabung[i][j] != warna) return false;
            }
        }
    }
    return true;
}

void gameSusunBola (pet &p, aktivitas* &head, Skill* skillRoot){
    isiAwal();
    Skill* kelincahan = CariSkill(skillRoot,"Kelincahan");
    Skill* sprint = CariSkill(skillRoot,"Sprint");
    Skill* atletis = CariSkill(skillRoot,"Atletis");
    Skill* puzzle = CariSkill(skillRoot,"Puzzle");

    int asal, tujuan;

    do {
        display();

        if (cekMenang()) {
            int bonusKoin = 50;
            int bonusBahagia = 20;
            int energiHilang = 10;

            if(sprint != NULL && sprint->terbuka) bonusKoin += 5;
            if(puzzle != NULL && puzzle->terbuka) bonusKoin += 10;
            if(atletis != NULL && atletis->terbuka) bonusBahagia += 5;
            if(kelincahan != NULL && kelincahan->terbuka) energiHilang -= 2;

            p.koin += bonusKoin;
            p.bahagia += bonusBahagia;
            p.energi -= energiHilang;
            p.skillPoint++; 

            if (p.bahagia > 100) p.bahagia = 100;
            if (p.energi < 0) p.energi = 0;

            cout << "\n🎉 Selamat Kamu Menang!\n";
            cout << "+" << bonusKoin << " Koin\n";
            cout << "+" << bonusBahagia << " Bahagia\n";
            cout << "-" << energiHilang << " Energi\n";
            cout << "+1 Skill Point\n";

            cout << "\nStatus Setelah Bermain:\n";
            cout << "Energi sekarang    : " << p.energi << endl;
            cout << "Bahagia sekarang   : " << p.bahagia << endl;
            cout << "Koin sekarang      : " << p.koin << endl;

            TambahAktivitas(head, "Menang game susun bola");
            break;
        }

        cout << "\n0 = Menyerah";
        cout << "\n-1 = Keluar";
        cout << "\nPilih tabung asal (-1 untuk keluar, 0 untuk menyerah): ";
        cin >> asal;
        cin.ignore(1000, '\n');

        if (asal == 0) {
            cout << "Kamu menyerah, tidak mendapat poin!\n";  
            TambahAktivitas(head, "Menyerah pada game susun bola");
            return;
        }
        if (asal == -1) break;

        cout << "Pilih tabung tujuan: ";
        cin >> tujuan;
        cin.ignore(1000, '\n');

        asal--; tujuan--;

        if (asal < 0 || asal >= jumlahTabung || tujuan < 0 || tujuan >= jumlahTabung) {
            cout << "Input tabung tidak valid!\n";
            continue;
        }

        pindah(asal, tujuan);
    } while (true);
}

// Interaksi Arena Bermain
void Main(pet &p, aktivitas* &head, Skill* skillRoot) {
    int pilih;
    Skill* kecerdasan = CariSkill(skillRoot, "Kecerdasan");

    if (p.energi <= 0) {
        cout << p.nama_pet << " terlalu lelah untuk bermain!\n";
        pausegame();
        return;
    }

    cout << "\n=== PILIH AKTIVITAS MAIN ===\n";
    cout << "Energi saat ini: " << p.energi << endl;
    cout << "1. Main susun bola (+50 koin, +35 bahagia, -20 energi)\n";
    cout << "2. Jalan-jalan (+20 koin, +20 bahagia, -15 energi)\n";
    cout << "3. Main lompat tinggi (+10 koin, +10 bahagia, -5 energi)\n";
    cout << "4. Kembali\n";
    pilih = ValidasiInput(1, 4, "Pilihan: ");

    if (pilih == 4) return;

    if (pilih == 1) {
        if (p.energi < 20) { cout << p.nama_pet << " terlalu lelah untuk bermain susun bola!\n"; pausegame(); return; }
        gameSusunBola(p, head, skillRoot);
    }
    else if (pilih == 2) {
        if (p.energi < 15) { cout << p.nama_pet << " terlalu lelah untuk jalan-jalan!\n"; pausegame(); return; }
        p.koin += 20; p.energi -= 15; p.bahagia +=15;
        TambahAktivitas(head, "Jalan-jalan");
        cout << "Selesai bermain!\n";
        cout << "Bahagia sekarang   : " << p.bahagia << endl;
        cout << "Koin sekarang      : " << p.koin << endl;
    }
    else if (pilih == 3) {
        if (p.energi < 5) { cout << p.nama_pet << " terlalu lelah untuk main lompat tinggi!\n"; pausegame(); return; }
        p.koin += 10; p.energi -= 5; p.bahagia +=10;
        TambahAktivitas(head, "Main lompat tinggi");
        cout << "Selesai bermain!\n";
        cout << "Bahagia sekarang   : " << p.bahagia << endl;
        cout << "Koin sekarang      : " << p.koin << endl;
    }

    if (kecerdasan != NULL && kecerdasan->terbuka) {
        p.skillPoint++;
        cout << "Bonus Kecerdasan: +1 Skill Point!\n";
    }

    p.lapar += 5;

    if (p.bahagia > 100) p.bahagia = 100;
    if (p.energi < 0) p.energi = 0;
    if (p.lapar > 100) p.lapar = 100;

    cout << p.nama_pet << " selesai bermain!\n";
    pausegame();
}

// Fitur Graph (Lokasi)
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

void jalanjalan(int &posisi) {
    int tujuan[10];
    int jumlah = 0;

    cout << "\nLokasi Saat Ini : " << namalokasi[posisi] << endl;
    cout << "Tujuan tersedia:\n";

    for(int i = 0; i < Jumlah_lokasi; i++) {
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

// Interaksi Taman
void CariItem(pet &p, aktivitas* &head) {
    int hadiah = rand() % 3;
    cout << "\n=== EKSPLORASI TAMAN ===\n";

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

// Interaksi Klinik
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
            if(p.koin < 20) { cout << "Koin tidak cukup\n"; pausegame(); break; }
            if(p.kesehatan >= 100) { cout << "Status kesehatan pet penuh!\n"; pausegame(); break; }

            p.koin -= 20; p.kesehatan += 30;
            if(p.kesehatan > 100) p.kesehatan = 100;

            TambahAktivitas(head,"Berobat di klinik");
            cout << "Pet berhasil diobati!\n";
            pausegame();
            break;
    }
}

// Update Status Otomatis
void UpdateStatus(pet &p) {
    if (p.lapar > 0) p.lapar += 1;
    if (p.energi < 100) p.energi -= 1;
    if (p.bahagia < 100) p.bahagia -= 1;

    if (p.lapar > 100) p.lapar = 100;
    if (p.energi < 0) p.energi = 0;
    if (p.bahagia < 0) p.bahagia = 0;

    if(p.lapar >= 80 && p.energi <= 20) p.kesehatan -= 5;
    if(p.kesehatan < 0) p.kesehatan = 0;
}

void InisialisasiPetBaru(pet &p) {
    int pilih_jenis_pet;

    cout << "\n=== PILIH PET BARU ===\n";
    cout << "1. Kucing\n2. Hamster\n3. Kura-kura\n4. Kelinci\n5. Bunglon\n";
    pilih_jenis_pet = ValidasiInput(1, 5, "Pilihanmu: ");

    if (pilih_jenis_pet == 1) p.jenis = "Kucing";
    else if (pilih_jenis_pet == 2) p.jenis = "Hamster";
    else if (pilih_jenis_pet == 3) p.jenis = "Kura-kura";
    else if (pilih_jenis_pet == 4) p.jenis = "Kelinci";
    else if (pilih_jenis_pet == 5) p.jenis = "Bunglon";
    else p.jenis = "Tidak diketahui";

    cout << "Masukan nama pet: ";
    cin >> p.nama_pet;
    cin.ignore(1000, '\n');

    p.lapar = rand() % 21 + 40; p.bahagia = rand() % 21 + 40; p.energi = rand() % 21 + 40;
    p.apel = 0; p.daging = 0; p.roti = 0; p.kesehatan = 100;

    cout << "Pet baru berhasil dibuat!\n";
    cout << "Koin kamu tetap: " << p.koin << endl;
    pausegame();
}

int main() {
    pet myPet;
    int pilih_jenis_pet;
    aktivitas* head = NULL;
    Skill* skillRoot = BuatSkillTree();

    srand(time(0)); 

    cout << "====== \U0001F3AE PawPal ======\n";
    cout << "Masukan jenis pet: \n";
    cout << "1. Kucing\n2. Hamster\n3. Kura-kura\n4. Kelinci\n5. Bunglon\n";
    pilih_jenis_pet = ValidasiInput(1,5, "Pilihanmu: ");
    
    string jenisPet[5] = {"Kucing", "Hamster", "Kura-kura", "Kelinci", "Bunglon"};
    myPet.jenis = jenisPet[pilih_jenis_pet - 1];

    cout << "Masukan nama pet: ";
    cin >> myPet.nama_pet;
    cin.ignore(1000, '\n');

    myPet.lapar = rand() % 21 + 40; myPet.bahagia = rand() % 21 + 40; myPet.energi = rand() % 21 + 40;
    myPet.kesehatan = 100; myPet.skillPoint = 0; myPet.koin = 50;
    myPet.apel = 0; myPet.daging = 0; myPet.roti = 0;

    cout << "\nPet memiliki kondisi awal acak!\n";
    cout << "====================" << endl;
    cout << "Nama    : " << myPet.nama_pet << endl;
    cout << "Jenis   : " << myPet.jenis << endl;
    pausegame();

    int pilihan;
    int posisi = 0; // Memulai dari indeks 0 (Rumah)
    bool jalan = true;

    // MENU GLOBAL (SISTEM POU)
    while (jalan) {
        cout << "\n=================================\n";
        cout << "         \U0001F3AE PawPal        \n";
        cout << "=================================\n";

        if (myPet.kesehatan <= 30) {
            cout << "\n PERINGATAN!\n";
            cout << myPet.nama_pet << " sedang sakit! Segera ke klinik!\n";
        }

        cout << "\n Lokasi saat ini: " << namalokasi[posisi] << endl;
        cout << "1. \U0001F4CA Lihat Status\n";
        cout << "2. \U0001F6B6 Jalan-jalan (Pindah Lokasi)\n";
        cout << "3. \U0001F3AF Interaksi di " << namalokasi[posisi] << "\n";
        cout << "4. 🌟 Skill Tree\n";
        cout << "5. \U0001F4DC Lihat Aktivitas\n";

        int opsiLepas = 0;
        int maxOpsi = 6;
        if (CekStatusPenuh(myPet)) {
            cout << "6. Lepas ke alam bebas (Pet dalam keadaan terbaik!)\n";
            cout << "7. Keluar\n";
            opsiLepas = 6;
            maxOpsi = 7;
        } else {
            cout << "6. Keluar\n";
        }

        pilihan = ValidasiInput(1, maxOpsi, "Pilihan: ");

        if (pilihan == 1) {
            cout << "\n=== STATUS ===\n";
            cout << "\n========== STATUS PET ==========\n";
            cout << "Nama    : " << myPet.nama_pet << endl;
            cout << "Jenis   : " << myPet.jenis << endl;
            cout << "--------------------------------\n";
            cout << "\U0001F356 Lapar   : " << myPet.lapar << endl;
            cout << "\U0001F60A Bahagia : " << myPet.bahagia << endl;
            cout << "\U000026A1 Energi  : " << myPet.energi << endl;
            cout << "\U0001F4B0 Koin    : " << myPet.koin << endl;
            cout << "⭐ Skill Point : " << myPet.skillPoint << endl;
            cout << "Kesehatan  : " << myPet.kesehatan;
            if(myPet.kesehatan <= 30) cout << " (Sedang sakit!)\n" << endl;
            else cout << endl;
            pausegame();
        }
        else if (pilihan == 2) {
            jalanjalan(posisi);
            UpdateStatus(myPet);
        }
        else if (pilihan == 3) {
            // Interaksi berdasarkan posisi saat ini
            if (posisi == 0) MenuRumah(myPet, head);
            else if (posisi == 1) CariItem(myPet, head);
            else if (posisi == 2) Main(myPet, head, skillRoot); // Memanggil fungsi Arena 
            else if (posisi == 3) Klinik(myPet, head);
            else if (posisi == 4) BeliMakanan(myPet, head, skillRoot);
            
            UpdateStatus(myPet); // Update status setelah interaksi selesai
        }
        else if (pilihan == 4) {
            cout << "\n=== SKILL TREE ===\n";
            TampilkanSkill(skillRoot);
            cout << "\nSkill Point: " << myPet.skillPoint << endl;

            cout << "\n1. Kelincahan\n2. Sprint\n3. Atletis\n4. Kecerdasan\n5. Puzzle\n6. Berhitung\n7. Kembali\n";
            int pilihSkill = ValidasiInput(1,7,"Pilihan: ");

            if(pilihSkill == 1) UnlockSkill(skillRoot,"Kelincahan",myPet);
            else if(pilihSkill == 2) UnlockSkill(skillRoot,"Sprint",myPet);
            else if(pilihSkill == 3) UnlockSkill(skillRoot,"Atletis",myPet);
            else if(pilihSkill == 4) UnlockSkill(skillRoot,"Kecerdasan",myPet);
            else if(pilihSkill == 5) UnlockSkill(skillRoot,"Puzzle",myPet);
            else if(pilihSkill == 6) UnlockSkill(skillRoot,"Berhitung",myPet);

            pausegame();
        }
        else if (pilihan == 5) {
            LihatAktivitas(head);
        }
        else if (pilihan == opsiLepas && opsiLepas == 6) {
            char konfirmasi;
            cout << "\nStatus pet sudah penuh, Apakah anda ingin melepas pet ke alam bebas? (y/n): ";
            cin >> konfirmasi;
            cin.ignore(1000, '\n');

            if (konfirmasi == 'y' || konfirmasi == 'Y'){
                int reward = 50;
                myPet.koin += reward;
                cout << "Pet berhasil dilepaskan ke alam bebas!" << endl;
                cout << "Anda mendapatkan reward sebanyak " << reward << " Koin!" << endl;
                HapusAktivitas(head);
                InisialisasiPetBaru(myPet);
            }
            else {
                cout << "Pet tetap dirawat. Lanjutkan rawat pet-mu dengan baik ya!" << endl;
                pausegame();
            }
        }
        else if (pilihan == maxOpsi) {
            jalan = false;
            cout << "Anda telah keluar dari game. Terima kasih telah memainkan PawPal ^-^\n";
        }
    }

    return 0;
}