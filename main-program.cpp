#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <ctime>
using namespace std;

const int jumlahTabung = 4; 
const int kapasitas = 3;

string tabung [jumlahTabung][kapasitas];
int top [jumlahTabung];

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
    int cooldownEvent;
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

struct transaksi{
    string namaMakanan;
    int jumlah;
    int totalHarga;
    transaksi* next;
};

struct teman{
    string nama;
    int friendship;
    int energi;
    int mainHariIni;

    teman* next;
};

struct RelasiTeman{
    string nama;
    string koneksi[5];
    int jumlahKoneksi;
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
baru-> pesan = keterangan;
baru -> next = head;
head = baru;
}

Skill* CariSkill(Skill* root, string nama);
string CekMood(pet &p);

void PushTransaksi(transaksi* &top, string makanan, int jumlah, int total){
    transaksi* baru = new transaksi;

    baru->namaMakanan = makanan;
    baru->jumlah = jumlah;
    baru->totalHarga = total;

    baru->next = top;
    top = baru;
}

void BeliMakanan(pet &p, aktivitas* &head, Skill* skillRoot, transaksi* &top){
    int pilih, jumlah;
    string namaMakanan;
    int harga = 0;
    Skill* berhitung =
    CariSkill(skillRoot,"Berhitung");

    int hargaApel = 5;
    int hargaDaging = 15;
    int hargaRoti = 7;

    if(berhitung != NULL &&
    berhitung->terbuka)
    {
        hargaApel = 4;
        hargaDaging = 12;
        hargaRoti = 5;
    }

    cout << "=== TOKO MAKANAN ===" << endl;
    cout << "1. Apel (Harga: "
        << hargaApel
        << ", Lapar -5)" << endl;

    cout << "2. Daging (Harga: "
        << hargaDaging
        << ", Lapar -15)" << endl;

    cout << "3. Roti (Harga: "
        << hargaRoti
        << ", Lapar -10)" << endl;
    cout << "4. Kembali" << endl;
    pilih = ValidasiInput(1,4, "Pilih makanan yang ingin dibeli(masukkan angka): ");

    if (pilih == 4) return;

    jumlah = ValidasiInput(1, 100, "Masukkan jumlah pembelian: ");    

    switch(pilih){
        case 1:
            namaMakanan = "Apel";
            harga = hargaApel;
            break;

        case 2:
            namaMakanan = "Daging";
            harga = hargaDaging;
            break;

        case 3:
            namaMakanan = "Roti";
            harga = hargaRoti;
            break;
}

    int totalHarga = harga * jumlah;

    if (p.koin >= totalHarga){
        p.koin -= totalHarga;

        if (pilih == 1)
            p.apel += jumlah;
        else if (pilih == 2)
            p.daging += jumlah;
        else 
            p.roti += jumlah;

        PushTransaksi(
            top,
            namaMakanan,
            jumlah,
            totalHarga
        );

        TambahAktivitas(
            head,
            "Membeli " + to_string(jumlah) + " " + namaMakanan
        );

        cout << "\nBerhasil membeli " << jumlah << " " << namaMakanan << "!\n";
        cout << "Total harga : " << totalHarga << endl;
        cout << "Sisa koin : " << p.koin << endl;

        cout << "\n=== STOK MAKANAN ===" << endl;
        cout << "\U0001F356 Apel   : " << p.apel << endl;
        cout << "\U0001F35E Daging : " << p.daging << endl;
        cout << "\U0001F35E Roti   : " << p.roti << endl;
    }
    else{
        cout << "Koin tidak cukup!\n";
    }
}

// Read
void LihatAktivitas(aktivitas* &head){
    cout << "\n======= \U0001F4DC RIWAYAT AKTIVITAS PET =======\n";
    aktivitas* temp = head;
    if (!temp) cout << "Belum ada aktivitas yang dilakukan" << endl;
    while (temp) {
        cout << "- " << temp->pesan << endl;
        temp = temp-> next;
    }
    cout << "==============================" << endl;
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
    return (p. lapar <= 0 && p.bahagia >= 100 && p.energi >= 100);
}

// update
void Makan(pet &p, aktivitas* &head){
    int pilih, jumlah;

    cout << "=== PILIH MAKANAN ===" << endl;
    cout << "1. 🍎 Apel     (stok: " << p.apel << ")" << endl;
    cout << "2. 🍖 Daging   (stok: " << p.daging << ")" << endl;
    cout << "3. 🍞 Roti     (stok: " << p.roti << ")" << endl;
    cout << "4. Kembali" << endl;

    pilih = ValidasiInput(
        1,
        4,
        "Pilih makanan: "
    );

    if (pilih == 4)
        return;

    jumlah = ValidasiInput(
        1,
        100,
        "Mau makan berapa banyak? "
    );

    if (pilih == 1){

        if (p.apel >= jumlah){

            p.apel -= jumlah;
            p.lapar -= (5 * jumlah);

            TambahAktivitas(
                head,
                "Memberi "
                + to_string(jumlah)
                + " apel"
            );

            cout << "Berhasil memberi "
                 << jumlah
                 << " apel!\n";

            cout << "Lapar sekarang: "
                 << p.lapar
                 << endl;
        }
        else{
            cout << "Stok apel tidak cukup!\n";
        }
    }

    else if (pilih == 2){

        if (p.daging >= jumlah){

            p.daging -= jumlah;
            p.lapar -= (15 * jumlah);

            TambahAktivitas(
                head,
                "Memberi "
                + to_string(jumlah)
                + " daging"
            );

            cout << "Berhasil memberi "
                 << jumlah
                 << " daging!\n";

            cout << "Lapar sekarang: "
                 << p.lapar
                 << endl;
        }
        else{
            cout << "Stok daging tidak cukup!\n";
        }
    }

    else if (pilih == 3){

        if (p.roti >= jumlah){

            p.roti -= jumlah;
            p.lapar -= (7 * jumlah);

            TambahAktivitas(
                head,
                "Memberi "
                + to_string(jumlah)
                + " roti"
            );

            cout << "Berhasil memberi "
                 << jumlah
                 << " roti!\n";

            cout << "Lapar sekarang: "
                 << p.lapar
                 << endl;
        }
        else{
            cout << "Stok roti tidak cukup!\n";
        }
    }

    if (p.lapar < 0)
        p.lapar = 0;
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

        if (pilih == 4) return; // Balik ke menu utama

        if (pilih == 1) { durasi = 5; energi_dapat = 15; }
        else if (pilih == 2) { durasi = 10; energi_dapat = 35; }
        else if (pilih == 3) { durasi = 15; energi_dapat = 50; }
        else {
            cout << "Pilihan tidak valid!\n";
            continue;
        }

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
        return; // Balik ke menu utama juga
    }
}

Skill* BuatSkill(string nama)
{
    Skill* baru = new Skill;

    baru->namaSkill = nama;
    baru->terbuka = false;

    baru->kiri = NULL;
    baru->kanan = NULL;

    return baru;
}

Skill* BuatSkillTree()
{
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

void TampilkanSkill(Skill* root, int level = 0)
{
    if(root == NULL)
        return;

    for(int i=0;i<level;i++)
        cout << "   ";

    cout << "- " << root->namaSkill;

    if(root->terbuka)
        cout << " [TERBUKA]";
    else
        cout << " [TERKUNCI]";

    cout << endl;

    TampilkanSkill(root->kiri, level + 1);
    TampilkanSkill(root->kanan, level + 1);
}

Skill* CariSkill(Skill* root, string nama)
{
    if(root == NULL)
        return NULL;

    if(root->namaSkill == nama)
        return root;

    Skill* kiri = CariSkill(root->kiri, nama);

    if(kiri != NULL)
        return kiri;

    return CariSkill(root->kanan, nama);
}

Skill* CariParent(Skill* root, Skill* target){

    if(root == NULL)
        return NULL;

    if(root->kiri == target || root->kanan == target)
        return root;

    Skill* kiri = CariParent(root->kiri, target);

    if(kiri != NULL)
        return kiri;

    return CariParent(root->kanan, target);
}

void UnlockSkill(Skill* root, string nama, pet &p)
{
    Skill* skill = CariSkill(root, nama);
    Skill* parent = CariParent(root, skill);

    if(skill == NULL){
        cout << "Skill tidak ditemukan!\n";
        return;
    }

    if(skill->terbuka){
        cout << "Skill sudah terbuka!\n";
        return;
    }

    if(p.skillPoint < 3){
        cout << "Skill Poin tidak cukup!\n";
        return;
    }

    if(parent != NULL && !parent->terbuka){
        cout << "Buka skill "
             << parent->namaSkill
             << " terlebih dahulu!\n";
        return;
    }

    p.skillPoint -= 3;
    skill->terbuka = true;

    // Bonus permanen saat unlock
    if(nama == "Kelincahan")
    {
        p.energi += 10;
    }
    else if(nama == "Sprint")
    {
        p.bahagia += 5;
    }
    else if(nama == "Atletis")
    {
        p.energi += 5;
        p.bahagia += 5;
    }
    else if(nama == "Kecerdasan")
    {
        p.skillPoint += 2;
    }
    else if(nama == "Puzzle")
    {
        p.bahagia += 10;
    }
    else if(nama == "Berhitung")
    {
        p.koin += 20;
    }

    if(p.energi > 100) p.energi = 100;
    if(p.bahagia > 100) p.bahagia = 100;

    cout << nama << " berhasil dibuka!\n";
    cout << "Bonus skill telah diterapkan!\n";
}

//game susun bola
void createStack()
{
    for (int i = 0; i < jumlahTabung; i++)
    {
        top[i] = -1;
    }
}

bool isEmpty(int i) 
{
    return top[i] == -1;
}

bool isFull(int i)
{
    return top[i] == kapasitas -1;
}

//push
void push(int i, string data)
{
    if(!isFull(i))
    {
        top[i]++;
        tabung[i][top[i]] = data;
    }
}

//pop
string pop(int i) 
{
    if (!isEmpty(i)) 
    {
        return tabung[i][top[i]--];
    }
    return "";
}

void isiAwal()
{
    createStack();
    push(0, "biru"); push(0, "kuning"); push(0, "hijau");
    push(1, "kuning"); push(1, "kuning"); push(1, "hijau");
    push(2, "hijau"); push(2, "biru"); push(2, "biru");
}

//display
void display() 
{
    cout << "Isi Tabung:" << endl;
    for (int i = 0; i < jumlahTabung; i++) 
    {
        cout << "Tabung " << i + 1<< ": ";
        for (int j = 0; j <= top[i]; j++) 
        {
            cout << tabung[i][j] << " ";
        }
        cout << endl;
    }
}

void pindah(int asal, int tujuan)
{
    if(isEmpty(asal))
    {
        cout << "Tabung asal kosong" << endl;
        return;
    }

    if(isFull(tujuan))
    {
        cout << "Tabung Tujuan penuh" << endl;
        return;
    }

    string warna = tabung[asal][top[asal]];

    pop(asal);
    push(tujuan, warna);

    cout << "Berhasil pindah" << endl;
}

bool cekMenang() {
    for (int i = 0; i < jumlahTabung; i++) {
        if (!isEmpty(i)) {
            if (top[i] != kapasitas - 1) {
                return false;
            }

            string warna = tabung[i][0];
            for (int j = 1; j <= top[i]; j++) {
                if (tabung[i][j] != warna) {
                    return false;
                }
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

            if(sprint != NULL && sprint->terbuka)
                bonusKoin += 5;

            if(puzzle != NULL && puzzle->terbuka)
                bonusKoin += 10;

            if(atletis != NULL && atletis->terbuka)
                bonusBahagia += 5;

            if(kelincahan != NULL && kelincahan->terbuka)
                energiHilang -= 2;

            p.koin += bonusKoin;
            p.bahagia += bonusBahagia;
            p.energi -= energiHilang;
            p.skillPoint++; 

        if (p.bahagia > 100) p.bahagia = 100;
        if (p.energi < 0) p.energi = 0;

        cout << "\n\U0001F389 Selamat Kamu Menang!\n";
        cout << "+" << bonusKoin << " Koin\n";
        cout << "+" << bonusBahagia << " Bahagia\n";
        cout << "-" << energiHilang << " Energi\n";
        cout << "+1 Skill Poin\n";

        cout << "\nStatus Setelah Bermain:\n";
        cout << "Energi sekarang    : " << p.energi << endl;
        cout << "Bahagia sekarang   : " << p.bahagia << endl;
        cout << "Koin sekarang      : " << p.koin << endl;

        TambahAktivitas(head, "Menang game susun bola");

        break;
    }
    while (true)
    {
        cout << "\n0 = Menyerah";
        cout << "\n-1 = Keluar";
        cout << "\nPilih Tabung Asal (-1 untuk keluar, 0 untuk menyerah): ";
        cin >> asal;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Input harus berupa angka!\n";
            continue;
        }

        if (asal == 0)
        {
            cout << "Kamu menyerah, tidak mendapat poin!\n";

            TambahAktivitas(head, "Menyerah pada game susun bola");
            return;
        }

        if (asal == -1)
        {
            return;
        }

        if (asal < 1 || asal > jumlahTabung)
        {
            cout << "Tabung asal hanya ada 1-4\n";
            continue;
        }
        break;
    }

    tujuan = ValidasiInput(1, jumlahTabung, "\nPilih tabung tujuan: ");

    if (asal == tujuan)
    {
        cout << "Tabung asal dan tujuan tidak boleh sama!";
        continue;
    }

    } while (true);
}

//game main bola
void gamePenaltyShoot(pet &p, aktivitas* &head)
{
    int gol = 0;

    cout << "\n=== PENALTY SHOOT ===\n";

    for(int ronde = 1; ronde <= 5; ronde++)
    {
        int tendangan;

        cout << "\n=== Tendangan ke-" << ronde << " ===\n";
        cout << "1. Kiri\n";
        cout << "2. Tengah\n";
        cout << "3. Kanan\n";

        while(true)
        {
            cout << "Pilih arah tendangan: ";
            cin >> tendangan;

            if(cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Input harus berupa angka!\n";
            }
            else if(tendangan < 1 || tendangan > 3)
            {
                cout << "Pilihan harus 1, 2, atau 3!\n";
            }
            else
            {
                break;
            }
        }

        int kiper = rand() % 3 + 1;

        cout << "\nKiper melompat ke ";

        if(kiper == 1)
            cout << "Kiri";
        else if(kiper == 2)
            cout << "Tengah";
        else
            cout << "Kanan";

        cout << "!\n";

        if(tendangan == kiper)
        {
            cout << "Bola ditangkap kiper!\n";
        }
        else
        {
            cout << "GOOOOL!\n";
            gol++;
        }
        tendangan = ValidasiInput(1, 5, "Pilihan: ");
    }

    int bonusKoin = gol * 10;
    int bonusBahagia = gol * 5;

    p.koin += bonusKoin;
    p.bahagia += bonusBahagia;
    p.energi -= 10;

    if(p.bahagia > 100)
        p.bahagia = 100;

    if(p.energi < 0)
        p.energi = 0;

    cout << "\n=====================\n";
    cout << "Total Gol : " << gol << "/5\n";

    cout << "\nReward:\n";
    cout << "+" << bonusKoin << " Koin\n";
    cout << "+" << bonusBahagia << " Bahagia\n";
    cout << "-10 Energi\n";

    TambahAktivitas(
        head,
        "Bermain Penalty Shoot (" +
        to_string(gol) +
        " gol)"
    );
}


//Fitur teman main
// Daftar teman (graph)
const int JUMLAH_TEMAN = 10;

string semuaTeman[JUMLAH_TEMAN] = {
    "Snow",
    "Choco",
    "Boba",
    "Luna",
    "Mochi",
    "Berry",
    "Luka",
    "Maple",
    "Peanut",
    "Oreo"
};

bool relasi[JUMLAH_TEMAN][JUMLAH_TEMAN] = {
 //Sn Ch Bo Lu Mo Be Lk Ma Pe Or
  {0,1,0,1,0,0,0,0,0,0}, // Snow
  {1,0,1,0,1,0,0,0,0,0}, // Choco
  {0,1,0,0,0,1,0,0,0,0}, // Boba
  {1,0,0,0,0,0,1,0,0,0}, // Luna
  {0,1,0,0,0,0,0,1,0,0}, // Mochi
  {0,0,1,0,0,0,1,1,0,0}, // Berry
  {0,0,0,1,0,1,0,0,1,0}, // Luka
  {0,0,0,0,1,1,0,0,0,1}, // Maple
  {0,0,0,0,0,0,1,0,0,1}, // Peanut
  {0,0,0,0,0,0,0,1,1,0}  // Oreo
};

// Cek apakah sudah berteman
bool SudahBerteman(teman* head, string nama){

    while (head){
        if (head->nama == nama)
            return true;

        head = head->next;
    }

    return false;
}

// Tambah teman
void TambahTeman(teman* &head, string nama){

    teman* baru = new teman;

    baru->nama = nama;
    baru->friendship = 0;
    baru->energi = 100;
    baru->mainHariIni = 0;

    baru->next = head;
    head = baru;
}

// Cari teman
void CariTeman(teman* &head){

    // Jika belum punya teman, hanya bisa ketemu starter
    if(head == NULL){

        string starter[3] = {
            "Snow",
            "Luka",
            "Choco"
        };

        int index = rand() % 3;

        cout << "\nKamu bertemu " << starter[index] << "!\n";
        cout << "1. Ajak Berteman\n";
        cout << "2. Kembali\n";

        int pilih = ValidasiInput(1,2,"Pilihan: ");

        if(pilih == 1){
            TambahTeman(head, starter[index]);
            cout << starter[index] << " sekarang menjadi temanmu!\n";
        }
        return;
    }

    string kandidat[JUMLAH_TEMAN];
    int jumlah = 0;

    teman* temp = head;

    while (temp){
        int idxTeman = -1;

        // Cari index teman di graph
        for (int i = 0; i < JUMLAH_TEMAN; i++){
            if (semuaTeman[i] == temp->nama){
                idxTeman = i;
                break;
            }
        }

        // Menambah semua relasi teman
        if(idxTeman != -1){
            for(int i = 0; i < JUMLAH_TEMAN; i++){
                if(relasi[idxTeman][i]){
                    if(!SudahBerteman(head, semuaTeman[i])){
                        bool sudahMasuk = false;

                        for (int j = 0; j < jumlah; j++){
                            if (kandidat[j] == semuaTeman[i]){
                                sudahMasuk = true;
                                break;
                            }
                        }

                        if (!sudahMasuk){
                            kandidat[jumlah] =
                                semuaTeman[i];

                            jumlah++;
                        }
                    }
                }
            }
        }
        temp = temp->next;
    }

    if(jumlah == 0){

        cout << "\nTidak ada teman baru yang bisa ditemukan.\n";
        return;
    }

    int index = rand() % jumlah;

    cout << "\nKamu bertemu " << kandidat[index] << "!\n";
    cout << "1. Ajak Berteman\n";
    cout << "2. Kembali\n";

    int pilih = ValidasiInput(1,2,"Pilihan: ");

    if( pilih == 1){
        TambahTeman(head, kandidat[index]);
        cout << kandidat[index] << " sekarang menjadi temanmu!\n";
    }
}

// Status friendship
string StatusFriendship(int friendship){

    if (friendship <= 25)
        return "Kenalan";

    if (friendship <= 50)
        return "Teman";

    if (friendship <= 75)
        return "Sahabat";

    return "Best Friend";
}

// Batasan bonus friendship per hari
int BonusFriendship(teman &t){

    if (t.mainHariIni == 0)
        return 3;

    if (t.mainHariIni == 1)
        return 2;

    if (t.mainHariIni == 2)
        return 1;

    return 0;
}

// Bonus bahagia
int BonusBahagiaTeman(int friendship){

    if (friendship <= 25)
        return 2;

    if (friendship <= 50)
        return 5;

    if (friendship <= 75)
        return 7;

    return 10;
}

void ResetMainHariIni(teman* head){

    while(head){
        head->mainHariIni = 0;
        head = head->next;
    }
}

// Lihat teman
void LihatTeman(teman* head){

    cout << "\n=== DAFTAR TEMAN ===\n";

    if (head == NULL){

        cout << "Belum memiliki teman.\n";
        return;
    }

    int nomor = 1;

    while (head){
        cout << nomor << ". " << head->nama << endl;
        cout << "   Friendship : " << head->friendship << endl;
        cout << "   Status     : " << StatusFriendship(head->friendship) << endl;
        cout << "   Energi     : " << head->energi << endl;
        cout << "---------------------\n";

        nomor++;
        head = head->next;
    }
}

// Reset energi teman saat pet tidur
void ResetEnergiTeman(teman* head){
    
    while (head){
        head->energi = 100;
        head = head->next;
    }
}

// Pilih teman
teman* PilihTeman(teman* head){

    if (head == NULL){
        cout << "Belum memiliki teman!\n";
        return NULL;
    }

    cout << "\n=== PILIH TEMAN ===\n";

    int nomor = 1;
    teman* temp = head;

    while (temp){
        cout << nomor << ". " << temp->nama << " (" << StatusFriendship(temp->friendship) << ")" << " | Energi: " << temp->energi;

if (temp->energi < 20)
    cout << " [LELAH]";

cout << endl;

        nomor++;
        temp = temp->next;
    }

    int pilih = ValidasiInput(1, nomor-1, "Pilih teman: ");

    temp = head;

    for (int i=1; i < pilih ;i++)
        temp = temp->next;

    return temp;
}

// Menu teman
void MenuTeman(teman* &daftarTeman){

    int pilih;

    do{

        cout << "\n=== MENU TEMAN ===\n";

        cout << "1. Lihat Teman\n";
        cout << "2. Cari Teman Baru\n";
        cout << "3. Kembali\n";

        pilih = ValidasiInput(1, 3, "Pilihan: ");

        switch(pilih){

            case 1:
                LihatTeman(daftarTeman);
                break;

            case 2:
                CariTeman(daftarTeman);
                break;
        }

    }
    while (pilih != 3);
}

// EVENT DENGAN TEMAN
// Event jatuh saat main
void EventTemanTerjatuh(teman* head){

    if (head == NULL)
        return;

    int jumlah = 0;
    teman* temp = head;

    while (temp){
        jumlah++;
        temp = temp->next;
    }

    int target = rand() % jumlah;

    temp = head;

    for (int i = 0; i < target; i++)
        temp = temp->next;

    cout << "\n\U000026A0 EVENT PERTEMANAN \U000026A0\n";
    cout << temp->nama << " terjatuh saat bermain!\n";

    cout << "1. Bantu dia\n";
    cout << "2. Abaikan\n";

    int pilih = ValidasiInput(1, 2, "Pilihan: ");

    if (pilih == 1){
        temp->friendship += 5;

        if (temp->friendship > 100)
            temp->friendship = 100;
        cout << "Kamu membantu " << temp->nama << endl;
        cout << "Friendship +5\n";
    }
    else {
        temp->friendship -= 5;

        if (temp->friendship < 0)
            temp->friendship = 0;

        cout << temp->nama << " kecewa padamu.\n";
        cout << "Friendship -5\n";
    }
}

// Event hadiah saat main
void EventHadiah(teman* head){

    if (head == NULL)
        return;

    int jumlah = 0;
    teman* temp = head;

    while (temp){
        jumlah++;
        temp = temp->next;
    }

    int target = rand() % jumlah;

    temp = head;

    for (int i = 0; i < target; i++)
        temp = temp->next;

    cout << "\n\U0001F381 EVENT PERTEMANAN \U0001F381\n";
    cout << temp->nama << " memberimu hadiah!\n";

    temp->friendship += 5;

    if (temp->friendship > 100)
        temp->friendship = 100;

    cout << "Friendship +5\n";
}

// Event teman meminta makan
void EventMintaMakanan(pet &p, teman* head){

    if (head == NULL)
        return;

    int jumlah = 0;
    teman* temp = head;

    while (temp){
        jumlah++;
        temp = temp->next;
    }

    int target = rand() % jumlah;

    temp = head;

    for (int i = 0; i < target; i++)
        temp = temp->next;

    cout << "\n\U0001F34E EVENT PERTEMANAN \U0001F34E\n";
    cout << temp->nama << " meminta makanan darimu.\n";

    cout << "\n=== STOK MAKANAN ===\n";
    cout << "\U0001F34E Apel   : " << p.apel << endl;
    cout << "\U0001F356 Daging : " << p.daging << endl;
    cout << "\U0001F35E Roti   : " << p.roti << endl;
    cout << "\n1. Beri makanan\n";
    cout << "2. Tolak\n";

    int pilih = ValidasiInput(1, 2, "Pilihan: ");

    if (pilih == 1){
        cout << "\n=== PILIH MAKANAN ===\n";
        cout << "1. \U0001F34E Apel (+3 Friendship)\n";
        cout << "2. \U0001F356 Daging (+8 Friendship)\n";
        cout << "3. \U0001F35E Roti (+5 Friendship)\n";

        int makanan = ValidasiInput(1, 3, "Pilihan: ");

        if (makanan == 1){
            if(p.apel <= 0){
                cout << "Apel habis!\n";
                return;
            }
            p.apel--;

            temp->friendship += 3;

            cout << "Kamu memberikan apel kepada " << temp->nama << endl;
            cout << "Friendship +3\n";
        }
        else if (makanan == 2){
            if (p.daging <= 0){
                cout << "Daging habis!\n";
                return;
            }
            p.daging--;

            temp->friendship += 8;

            cout << "Kamu memberikan daging kepada " << temp->nama << endl;
            cout << "Friendship +8\n";
        }
        else if (makanan == 3){
            if (p.roti <= 0){
                cout << "Roti habis!\n";
                return;
            }
            p.roti--;

            temp->friendship += 5;

            cout << "Kamu memberikan roti kepada " << temp->nama << endl;
            cout << "Friendship +5\n";
        }
        if (temp->friendship > 100)
            temp->friendship = 100;
    }
    else {
        temp->friendship -= 3;

        if (temp->friendship < 0)
            temp->friendship = 0;

        cout << temp->nama << " terlihat kecewa.\n";
        cout << "Friendship -3\n";
    }
}

// Event teman mengajak main
void EventAjakBermain(pet &p, teman* head){

    if (head == NULL)
        return;

    int jumlah = 0;
    teman* temp = head;

    while (temp){
        jumlah++;
        temp = temp->next;
    }

    int target = rand() % jumlah;

    temp = head;

    for (int i = 0; i < target; i++)
        temp = temp->next;

    cout << "\n\U0001F3BE EVENT PERTEMANAN \U0001F3BE\n";
    cout << temp->nama << " mengajakmu bermain.\n";

    cout << "\n=== STATUS ENERGI ===\n";
    cout << "Energi Pet : " << p.energi << endl;
    cout << "Biaya Bermain : 10 Energi\n\n";
    cout << "1. Terima ajakan\n";
    cout << "2. Tolak\n";

    int pilih = ValidasiInput(1, 2, "Pilihan: ");

    if (pilih == 1){
        if (p.energi < 10){
            cout << "Energi tidak cukup untuk bermain!\n";
            return;
        }
        p.energi -= 10;
        p.bahagia += 5;

        temp->friendship += 7;

        if (temp->friendship > 100)
            temp->friendship = 100;
        cout << "Kalian bermain bersama!\n";
        cout << "Friendship +7\n";
        cout << "Bahagia +5\n";
        cout << "Energi -10\n";
    }
    else {
        temp->friendship -= 1;

        if (temp->friendship < 0)
            temp->friendship = 0;

        cout << temp->nama << " terlihat sedikit sedih.\n";
        cout << "Friendship -2\n";
    }
}

// Event mengenalkan ke teman baru
void EventKenalanTeman(teman* &head){

    if(head == NULL)
        return;

    int jumlahTeman = 0;
    teman* temp = head;

    while (temp){
        jumlahTeman++;
        temp = temp->next;
    }

    int target = rand() % jumlahTeman;

    temp = head;

    for (int i = 0; i < target; i++)
        temp = temp->next;

    // cari index teman di graph
    int idx = -1;

    for (int i = 0; i < JUMLAH_TEMAN; i++){
        if (semuaTeman[i] == temp->nama){
            idx = i;
            break;
        }
    }

    if (idx == -1)
        return;

    // cari kandidat yang belum berteman
    string kandidat[10];
    int jumlah = 0;

    for (int i = 0; i < JUMLAH_TEMAN; i++){

        if (relasi[idx][i] && !SudahBerteman(head, semuaTeman[i])){
            kandidat[jumlah++] = semuaTeman[i];
        }
    }

    if (jumlah == 0)
        return;

    int pilihTeman = rand() % jumlah;

    cout << "\n=== EVENT PERTEMANAN ===\n";
    cout << temp->nama << " mengenalkanmu kepada " << kandidat[pilihTeman] << "!\n";

    cout << "1. Berkenalan\n";
    cout << "2. Tolak\n";

    int pilih = ValidasiInput(1,2,"Pilihan: ");

    if (pilih == 1){
        TambahTeman(head, kandidat[pilihTeman]);
        cout << kandidat[pilihTeman] << " sekarang menjadi temanmu!\n";
    }
    else {
        temp->friendship -= 2;

        if (temp->friendship < 0)
            temp->friendship = 0;
        cout << temp->nama << " sedikit kecewa.\n";
    }
}

// Fungsi cek event acak setiap main
void CekEventTeman(pet &p, teman* &head){

    if(head == NULL)
        return;

    p.cooldownEvent++;

    if(p.cooldownEvent < 3)
        return;

    p.cooldownEvent = 0;

    int event = rand() % 5;

    switch (event){

        case 0:
            EventTemanTerjatuh(head);
            break;

        case 1:
            EventHadiah(head);
            break;

        case 2:
            EventMintaMakanan(p, head);
            break;

        case 3:
            EventAjakBermain(p, head);
            break;

        case 4:
            EventKenalanTeman(head);
            break;
    }
}

// fungsi Bermain
void Main(pet &p, aktivitas* &head, Skill* skillRoot,  teman* daftarTeman){
    int pilih;
    Skill* kelincahan = CariSkill(skillRoot,"Kelincahan");
    Skill* sprint = CariSkill(skillRoot,"Sprint");
    Skill* atletis = CariSkill(skillRoot,"Atletis");
    Skill* puzzle = CariSkill(skillRoot,"Puzzle");

    if (p.energi <= 0) {
    cout << p.nama_pet << " terlalu lelah untuk bermain!\n";
    return;
    }

    cout << "\n=== PILIH AKTIVITAS MAIN ===\n";
    cout << "Energi saat ini: " << p.energi << endl;
    cout << "1. Main susun bola (+50 koin, +35 bahagia, -20 energi)\n";
    cout << "2. Main bola (+20 koin, +20 bahagia, -7 energi)\n";
    cout << "3. Main lompat tinggi (+10 koin, +10 bahagia, -5 energi)\n";
    cout << "4. Kembali\n";
    pilih = ValidasiInput(1, 4, "Pilihan: ");

    if (pilih == 4) return;

    char ajakTeman;

    cout << "\nAjak teman bermain? (y/n): ";
    cin >> ajakTeman;

    teman* temanDipilih = NULL;

    if (ajakTeman == 'y' || ajakTeman == 'Y'){

    temanDipilih = PilihTeman(daftarTeman);

    if (temanDipilih == NULL){
        cout << "Tidak jadi mengajak teman. Bermain sendiri.\n";
    }
    else if (temanDipilih->energi < 20){
        cout << temanDipilih->nama << " terlalu lelah bermain.\n";
        cout << p.nama_pet << " bermain sendiri.\n";

        temanDipilih = NULL;
    }
}

    if (pilih == 1) {
        if (p.energi < 20) {
            cout << p.nama_pet << " terlalu lelah untuk bermain susun bola!\n";
            return;
        }

        gameSusunBola(p, head, skillRoot);
    }
    else if (pilih == 2) {
        if (p.energi < 15) {
            cout << p.nama_pet << " terlalu lelah untuk bermain bola!\n";
            return;
        }
        p.koin += 20;
        p.energi -= 15;
        p.bahagia +=15;
        TambahAktivitas(head, "Jalan-jalan");
        cout << "Selesai bermain!\n";
        cout << "Bahagia sekarang   : " << p.bahagia << endl;
        cout << "Koin sekarang      : " << p.koin << endl;
    }
    else if (pilih == 3) {
        if (p.energi < 5) {
            cout << p.nama_pet << " terlalu lelah untuk main lompat tinggi!\n";
            return;
        }
        p.koin += 10;
        p.energi -= 5;
        p.bahagia +=10;
        TambahAktivitas(head, "Main lompat tinggi");
        cout << "Selesai bermain!\n";
        cout << "Bahagia sekarang   : " << p.bahagia << endl;
        cout << "Koin sekarang      : " << p.koin << endl;
    }
    else {
        cout << "Pilihan tidak valid!\n";
        return;
    }

    // Efek tambahan
    p.lapar += 5;

    // Batas maksimum & minimum
    if (p.bahagia > 100) p.bahagia = 100;
    if (p.energi < 0) p.energi = 0;
    if (p.lapar > 100) p.lapar = 100;

    cout << p.nama_pet << " selesai bermain!\n";

    int peluang = rand() % 100;

    if (peluang < 15) // 15%
    {
        cout << "\n " << p.nama_pet
            << " terkena flu!\n";

        p.kesehatan -= 10;

        TambahAktivitas(
            head,
            "Terkena flu setelah bermain"
        );
    }

    else if (peluang < 30) // 15%
    {
        cout << "\n " << p.nama_pet
            << " terluka saat bermain!\n";

        p.kesehatan -= 15;

        TambahAktivitas(
            head,
            "Terluka setelah bermain"
        );
    }

    if (temanDipilih != NULL){

    int bonusBahagia = BonusBahagiaTeman(temanDipilih->friendship);
    int bonusFriend = BonusFriendship(*temanDipilih);

    temanDipilih->friendship += bonusFriend;

    if (temanDipilih->friendship > 100)
        temanDipilih->friendship = 100;

    temanDipilih->mainHariIni++;

    temanDipilih->energi -= 15;

    if (temanDipilih->energi < 0)
        temanDipilih->energi = 0;

    p.bahagia += bonusBahagia;

    if (p.bahagia > 100)
        p.bahagia = 100;

    cout << "\n" << temanDipilih->nama << " bermain bersamamu!\n";

    if (bonusFriend > 0){
        cout << "Friendship +" << bonusFriend << endl;
    }
    else {
        cout << "Bonus friendship harian sudah habis.\n";
    }

    cout << "Bonus Bahagia +" << bonusBahagia << endl;

    cout << "Energi " << temanDipilih->nama << " sekarang: " << temanDipilih->energi << "/100\n";

    if (temanDipilih->energi <= 30){
        cout << "\U000026A0 " << temanDipilih->nama << " mulai kelelahan.\n";
    }
}
}

// Fungsi untuk update status pet setiap kali melakukan aktivitas
void UpdateStatus(pet &p){

    if (p.lapar < 100) {
        p.lapar += 1;
    }

    if (p.energi > 0) {
        p.energi -= 1;
    }

    if (p.bahagia > 0) {
        p.bahagia -= 1;
    }

    if (p.lapar > 100) p.lapar = 100;
    if (p.energi < 0) p.energi = 0;
    if (p.bahagia < 0) p.bahagia = 0;

    if (p.lapar >= 80 && p.energi <= 20) {
        p.kesehatan -= 5;
    }

    if (p.kesehatan < 0) p.kesehatan = 0;
}

string CekMood(pet &p){
    if (p.kesehatan < 40)   return "Sakit";
    if (p.lapar >= 80)      return "Sangat Lapar";
    if (p.energi < 20)      return "Mengantuk";
    if (p.lapar > 70)       return "Lapar";
    if (p.bahagia < 30)     return "Sedih";
    if (p.bahagia >= 80)    return "Sangat Bahagia";
    return "Senang";
}

void InisialisasiPetBaru(pet &p) {
    int pilih_jenis_pet;

    cout << "\n=== PILIH PET BARU ===\n";
    cout << "1. Kucing\n";
    cout << "2. Hamster\n";
    cout << "3. Kura-kura\n";
    cout << "4. Kelinci\n";
    cout << "5. Bunglon\n";
    cout << "Pilihanmu: ";
    cin >> pilih_jenis_pet;

    if (pilih_jenis_pet == 1)
        p.jenis = "Kucing";
    else if (pilih_jenis_pet == 2)
        p.jenis = "Hamster";
    else if (pilih_jenis_pet == 3)
        p.jenis = "Kura-kura";
    else if (pilih_jenis_pet == 4)
        p.jenis = "Kelinci";
    else if (pilih_jenis_pet == 5)
        p.jenis = "Bunglon";
    else
        p.jenis = "Tidak diketahui";

    cout << "Masukan nama pet: ";
    cin >> p.nama_pet;

    // Reset status (random lagi)
    p.lapar = rand() % 21 + 40;
    p.bahagia = rand() % 21 + 40;
    p.energi = rand() % 21 + 40;
    p.kesehatan = 100;

    // Reset inventory
    p.apel = 0;
    p.daging = 0;
    p.roti = 0;
    p.cooldownEvent = 0;

    cout << "Pet baru berhasil dibuat!\n";
    cout << "Koin kamu tetap: " << p.koin << endl;
}

const int jumlah_lokasi = 5;

string namalokasi[jumlah_lokasi] =
{"Rumah", "Taman", "Arena", "Klinik", "Toko"};

int adj[jumlah_lokasi][jumlah_lokasi] = 
{
    {0, 1, 0, 0, 0}, // Rumah
    {1, 0, 1, 0, 0}, // Taman
    {0, 1, 0, 1, 0}, // Arena
    {0, 0, 1, 0, 1}, // klinik
    {0, 0, 0, 1, 0}  // Toko
}; 

int cost[jumlah_lokasi][jumlah_lokasi] = 
{
    {0, 5, 0, 0, 0}, // Rumah
    {5, 0, 8, 0, 0}, // Taman
    {0, 8, 0, 10, 0}, // Arena
    {0, 0, 10, 0, 6}, // klinik
    {0, 0, 0, 6, 0}  // Toko
}; 

void TampilkanPetaLokasi()
{
    cout << "\n========== PETA KOTA ==========\n";
    cout << "\U0001F3E0 Rumah <-> \U0001F333 Taman <-> \U0001F3DF Arena <-> \U0001F3E5 Klinik <-> \U0001F3EA Toko\n";
    cout << "================================\n";

    cout << "\nRepresentasi Graph:\n";

    for (int i = 0; i < jumlah_lokasi; i++)
    {
        cout << namalokasi[i] << "-> ";
        bool pertama = true;

        for (int j = 0; j < jumlah_lokasi; j++)
        {
            if (adj[i][j] == 1)
            {
                if (!pertama) cout << ", ";

                cout << namalokasi[j];
                pertama = false;
            }
        }
        cout << endl;
    }
    cout << "==============================\n";
}

void Klinik(pet &p, aktivitas* &head)
{
    if(p.koin < 20)
    {
        cout << "Koin tidak cukup!\n";
        return;
    }

    p.koin -= 20;
    p.kesehatan += 30;

    if(p.kesehatan > 100)
        p.kesehatan = 100;

    TambahAktivitas(head,"Berobat ke klinik");

    cout << "\nPet berhasil diobati!\n";
    cout << "-20 Koin\n";
    cout << "+30 Kesehatan\n";
}

void jalanjalan(int &posisi, pet &p, aktivitas* &head)
{
    int tujuan[10];
    int jumlah = 0;

        cout << "\n========== PETA KOTA ==========\n";
    cout << "\U0001F3E0 Rumah <-> \U0001F333 Taman <-> \U0001F3DF Arena <-> \U0001F3E5 Klinik <-> \U0001F3EA Toko\n";
    cout << "================================\n";

    cout << "Keterangan Lokasi:\n";
    cout << "\U0001F3E0 Rumah  : Tempat tidur pet\n";
    cout << "\U0001F333 Taman  : Cari item dan eksplorasi\n";
    cout << "\U0001F3DF Arena  : Bermain mini game\n";
    cout << "\U0001F3E5 Klinik : Mengobati pet\n";
    cout << "\U0001F3EA Toko   : Membeli makanan\n";
    cout << "================================\n";

    cout << "\n\U0001F4CD Lokasi Saat Ini : "
        << namalokasi[posisi]
        << endl;

    cout << "\nTujuan tersedia:\n";

    // menampilkan tujuan yang bisa dijangkau dari lokasi saat ini
    for(int i = 0; i < jumlah_lokasi; i++)
    {
        if(adj[posisi][i] == 1)
        {
            jumlah++;

            cout << jumlah << ". "
                 << namalokasi[i]
                 << " (Biaya: " << cost[posisi][i] << " energi)"
                 << endl;

            tujuan[jumlah] = i;
        }
    }

    // kalau tidak ada jalan sama sekali
    if(jumlah == 0)
    {
        cout << "Tidak ada jalan dari lokasi ini!\n";
        return;
    }

    int pilih = ValidasiInput(1, jumlah, "Pilih tujuan: ");

    int tujuanDipilih = tujuan[pilih];
    int biaya = cost[posisi][tujuanDipilih];

    // energi di cek dulu dan menghindari soft lock
    if(p.energi < biaya)
    {
        cout << "Energi tidak cukup untuk ke lokasi tersebut!\n";

        bool bisaJalan = false;

        for(int i = 0; i < jumlah_lokasi; i++)
        {
            if(adj[posisi][i] == 1 && p.energi >= cost[posisi][i])
            {
                bisaJalan = true;
                break;
            }
        }

        if(!bisaJalan)
        {
            cout << "Pet kelelahan dan tidak bisa bergerak...\n";
            cout << "Pet pingsan dan dibawa kembali ke rumah.\n";

            posisi = 0;
            p.energi = 5;
        }

        return;
    }

    // pindah lokasi
    posisi = tujuanDipilih;

    // kurangi energi sesuai cost
    p.energi -= biaya;

    // reward
    p.bahagia += 10;
    p.koin += 10;

    if(p.bahagia > 100)
        p.bahagia = 100;

    TambahAktivitas(
        head,
        "Jalan-jalan ke " + namalokasi[posisi]
    );

    cout << "\n\U0001F4CD Sekarang berada di "
         << namalokasi[posisi]
         << endl;

    cout << "+10 Koin\n";
    cout << "+10 Bahagia\n";
    cout << "-" << biaya << " Energi\n";

    // kegiatan di klinik
    if(namalokasi[posisi] == "Klinik")
    {
        char pilih;

        cout << "\nMasuk ke Klinik? (y/n): ";
        cin >> pilih;

        if(pilih == 'y' || pilih == 'Y')
        {
            Klinik(p, head);

            cout << "\nLanjut ke Toko? (y/n): ";
            cin >> pilih;

            if(pilih == 'y' || pilih == 'Y')
            {
                posisi = 4;

                cout << "\n\U0001F4CD Sekarang berada di Toko\n";

                cout << "Gunakan menu Beli Makanan untuk berbelanja.\n";
            }
        }
    }

    // ini loop back jika energi habis stelah jalan-jalan (menghindari soft lock)
    if(p.energi <= 0)
    {
        cout << "Pet kelelahan dan pingsan...\n";
        cout << "Pet dibawa kembali ke rumah.\n";

        posisi = 0;
        p.energi = 5;
    }
}

// kegiatan di Taman
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
}


// fitur Main
int main() {
    pet myPet;
    int pilih_jenis_pet;
    aktivitas* head = NULL;
    transaksi* top = NULL;
    Skill* skillRoot = BuatSkillTree();
    int posisi = 0; // Lokasi awal: Rumah
    teman* daftarTeman = NULL;

    srand(time(0)); // Random poin awal pet

    cout << "====== \U0001F3AE PawPal ======\n";

    cout << "Masukan jenis pet: " << endl;
    cout << "1. Kucing" << endl;
    cout << "2. Hamster" << endl;
    cout << "3. Kura-kura" << endl;
    cout << "4. Kelinci" << endl;
    cout << "5. Bunglon" << endl;
    pilih_jenis_pet = ValidasiInput(1,5, "Pilihanmu: ");
    
    string jenisPet[5] = {
        "Kucing", "Hamster", "Kura-kura", "Kelinci", "Bunglon"
    };
    myPet.jenis = jenisPet[pilih_jenis_pet - 1];

    cout << "Masukan nama pet: ";
    cin >> myPet.nama_pet;

    // Random poin awal pet (rentang 40–60)
    myPet.lapar = rand() % 21 + 40;
    myPet.bahagia = rand() % 21 + 40;
    myPet.energi = rand() % 21 + 40;
    myPet.kesehatan = 100;

    myPet.skillPoint = 0;
    myPet.koin = 50;

    myPet.apel = 0;
    myPet.daging = 0;
    myPet.roti = 0;

    myPet.cooldownEvent = 0;

    cout << "\nPet memiliki kondisi awal acak!\n";
    cout << "====================" << endl;
    cout << "Nama    : " << myPet.nama_pet << endl;
    cout << "Jenis   : " << myPet.jenis << endl;


    int pilihan;
    bool jalan = true;

    while (jalan) {
        cout << "\n=================================\n";
        cout << "         \U0001F3AE PawPal        \n";
        cout << "=================================\n";
        cout << "1. \U0001F4CA Lihat Status\n";
        cout << "2. \U0001F5FA Lihat Peta Kota\n";
        cout << "3. \U0001F6B6 Jalan-jalan\n";
        cout << "4. \U0001F37D  Makan\n";
        cout << "5. \U0001F6D2 Beli Makanan\n";
        cout << "6. \U0001F634 Tidur\n";
        cout << "7. \U0001F3BE Main\n";
        cout << "8. \U0001F4DC Lihat Aktivitas\n";
        cout << "9. \U0001F465 Teman\n";
        cout << "10. \U0001F31F Skill\n";

    if (CekStatusPenuh(myPet)) {
        cout << "11. Lepas ke alam bebas (Pet dalam keadaan terbaik!)\n";
        cout << "12. Keluar\n";
    }
    else {
        cout << "11. Keluar\n";
    }

    cout << "Pilihan: ";
    cin >> pilihan;

        switch (pilihan) {
            case 1:
                cout << "\n=== STATUS ===\n";
                cout << "\n========== STATUS PET ==========\n";
                cout << "Nama    : " << myPet.nama_pet << endl;
                cout << "Jenis   : " << myPet.jenis << endl;
                cout << "--------------------------------\n";
                cout << "\U0001F356 Lapar   : " << myPet.lapar << endl;
                cout << "\U0001F60A Bahagia : " << myPet.bahagia << endl;
                cout << "\U000026A1 Energi  : " << myPet.energi << endl;
                cout << "\U0001F4B0 Koin    : " << myPet.koin << endl;
                cout << "\U0001F489 Kesehatan : " << myPet.kesehatan << endl;
                cout << "\U0001F31F Skill Poin : " << myPet.skillPoint << endl;
                cout << "Mood : " << CekMood(myPet) << endl;
                break;

            case 2:
            TampilkanPetaLokasi();
            break;

            case 3:
            jalanjalan(posisi, myPet, head);

            if(posisi == 1){
                CariItem(myPet, head);
            }

            UpdateStatus(myPet);
            break;

            case 4:
                Makan(myPet, head);
                UpdateStatus(myPet);
                break;


            case 5:
                if(posisi != 4)
                {
                    cout << "Kamu harus berada di Toko untuk membeli makanan!\n";                        
                    break;
                }

                BeliMakanan(myPet, head, skillRoot, top);
                UpdateStatus(myPet);
                break;

            case 6:
                if(posisi != 0)
                {
                    cout << "Kamu harus berada di Rumah untuk tidur!\n";
                    break;
                }

                Tidur(myPet, head);
                ResetEnergiTeman(daftarTeman);
                ResetMainHariIni(daftarTeman);
                break;

            case 7:
            {
                if(posisi != 2)
                {
                    cout << "Kamu harus berada di Arena untuk bermain!\n";
                    break;
                }

                Main(myPet, head, skillRoot, daftarTeman);

                Skill* kecerdasan = CariSkill(skillRoot, "Kecerdasan");

                if(kecerdasan != NULL && kecerdasan->terbuka)
                {
                    myPet.skillPoint++;
                    cout << "Bonus Kecerdasan: +1 Skill Point!\n";
                }

                CekEventTeman(myPet, daftarTeman);
                UpdateStatus(myPet);
                break;
            }

            case 8:
                LihatAktivitas(head);
                break;

            case 9:
                MenuTeman(daftarTeman);
                break;

            case 10:
                cout << "\n=== SKILL TREE ===\n";

                TampilkanSkill(skillRoot);

                cout << "\nSkill Poin: "
                    << myPet.skillPoint << endl;

                cout << "\n1. Kelincahan\n";
                cout << "2. Sprint\n";
                cout << "3. Atletis\n";
                cout << "4. Kecerdasan\n";
                cout << "5. Puzzle\n";
                cout << "6. Berhitung\n";
                cout << "7. Kembali\n";

                int pilihSkill;

                pilihSkill =
                    ValidasiInput(1,7,"Pilihan: ");

                if(pilihSkill == 1)
                    UnlockSkill(skillRoot,"Kelincahan",myPet);

                else if(pilihSkill == 2)
                    UnlockSkill(skillRoot,"Sprint",myPet);

                else if(pilihSkill == 3)
                    UnlockSkill(skillRoot,"Atletis",myPet);

                else if(pilihSkill == 4)
                    UnlockSkill(skillRoot,"Kecerdasan",myPet);

                else if(pilihSkill == 5)
                    UnlockSkill(skillRoot,"Puzzle",myPet);

                else if(pilihSkill == 6)
                    UnlockSkill(skillRoot,"Berhitung",myPet);

                break;

            case 11:
                if (CekStatusPenuh(myPet)){
                    char konfirmasi;
                    cout << "\nStatus pet sudah penuh, apakah Anda ingin melepas pet ke alam bebas? (y/n): ";
                    cin >> konfirmasi;

                    if (konfirmasi == 'y' || konfirmasi == 'Y'){
                        int reward = 50;
                        myPet.koin += reward;

                        cout << "Pet berhasil dilepaskan ke alam bebas!" << endl;
                        cout << "Anda mendapatkan reward sebanyak " << reward << " Koin!" << endl;

                        HapusAktivitas(head);

                        InisialisasiPetBaru(myPet);
                    }
                    else {
                        cout << "Pet tetap dirawat. Lanjutkan merawat pet-mu dengan baik ya!" << endl;
                    }
                }
                else {
                    jalan = false;
                    cout << "Anda telah keluar dari game. Terima kasih telah memainkan PawPal ^-^\n";
                }
                break;

            case 12: 
            jalan = false;
            cout << "Anda telah keluar dari game. Terima kasih telah memainkan PawPal ^-^\n";
            break;

            default:
                cout << "Pilihan tidak valid!\n";
        }
    }

    return 0;
}
