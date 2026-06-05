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
        cout << "🍎 Apel   : " << p.apel << endl;
        cout << "🍖 Daging : " << p.daging << endl;
        cout << "🍞 Roti   : " << p.roti << endl;
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
    int pilih;
    cout << "=== PILIH MAKANAN ===" << endl;
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
        else{
            cout << "Apel habis!";
        }
    }
    else if (pilih == 2){
        if (p.daging > 0){
            p.daging--;
            p.lapar -= 15;
            TambahAktivitas(head, "Memberi daging");
            cout << "Berhasil memberi daging!\n";
            cout << "Lapar sekarang: " << p.lapar << endl;
        }
        else {
            cout << "Daging habis!";
        }
    }
    else if (pilih == 3){
        if (p.roti > 0){
            p.roti--;
            p.lapar -= 7;
            TambahAktivitas(head, "Memberi roti");
            cout << "Berhasil memberi roti!\n";
            cout << "Lapar sekarang: " << p.lapar << endl;
        }
        else {
            cout << "Roti habis!";
        }
    }
    else {
        cout << "Pilihan tidak valid!";
    }

    if (p.lapar < 0) p.lapar = 0;
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
        cout << "Skill Point tidak cukup!\n";
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

// fungsi Main
void Main(pet &p, aktivitas* &head, Skill* skillRoot) {
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
    cout << "2. Jalan-jalan (+20 koin, +20 bahagia, -15 energi)\n";
    cout << "3. Main lompat tinggi (+10 koin, +10 bahagia, -5 energi)\n";
    cout << "4. Kembali\n";
    pilih = ValidasiInput(1, 4, "Pilihan: ");

    if (pilih == 4) return;

    if (pilih == 1) {
        if (p.energi < 20) {
            cout << p.nama_pet << " terlalu lelah untuk bermain susun bola!\n";
            return;
        }

        gameSusunBola(p, head, skillRoot);
    }
    else if (pilih == 2) {
        if (p.energi < 15) {
            cout << p.nama_pet << " terlalu lelah untuk jalan-jalan!\n";
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

    if(peluang < 15) // 15%
    {
        cout << "\n " << p.nama_pet
            << " terkena flu!\n";

        p.kesehatan -= 10;

        TambahAktivitas(
            head,
            "Terkena flu setelah bermain"
        );
    }

    else if(peluang < 30) // 15%
    {
        cout << "\n " << p.nama_pet
            << " terluka saat bermain!\n";

        p.kesehatan -= 15;

        TambahAktivitas(
            head,
            "Terluka setelah bermain"
        );
    }
}

// Fungsi untuk update status pet setiap kali melakukan aktivitas
void UpdateStatus(pet &p) {

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

void TampilkanPetaLokasi()
{
    cout << "\n========== PETA KOTA ==========\n";
    cout << "🏠 Rumah <-> 🌳 Taman <-> 🏟 Arena <-> 🏥 Klinik <-> 🏪 Toko\n";
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

    if(p.energi < 10)
    {
        cout << "Energi tidak cukup untuk jalan-jalan!\n";
        return;
    }

        cout << "\n========== PETA KOTA ==========\n";
    cout << "🏠 Rumah <-> 🌳 Taman <-> 🏟 Arena <-> 🏥 Klinik <-> 🏪 Toko\n";
    cout << "================================\n";

    cout << "Keterangan Lokasi:\n";
    cout << "🏠 Rumah  : Tempat tidur pet\n";
    cout << "🌳 Taman  : Cari item dan eksplorasi\n";
    cout << "🏟 Arena  : Bermain mini game\n";
    cout << "🏥 Klinik : Mengobati pet\n";
    cout << "🏪 Toko   : Membeli makanan\n";
    cout << "================================\n";

    cout << "\n📍 Lokasi Saat Ini : "
        << namalokasi[posisi]
        << endl;

    cout << "\nTujuan tersedia:\n";

    for(int i = 0; i < jumlah_lokasi; i++)
    {
        if(adj[posisi][i] == 1)
        {
            jumlah++;

            cout << jumlah
                 << ". "
                 << namalokasi[i]
                 << endl;

            tujuan[jumlah] = i;
        }
    }

    int pilih =
        ValidasiInput(1, jumlah,
                      "Pilih tujuan: ");

    posisi = tujuan[pilih];

    p.energi -= 10;
    p.bahagia += 10;
    p.koin += 10;

    if(p.bahagia > 100)
        p.bahagia = 100;

    TambahAktivitas(
        head,
        "Jalan-jalan ke " + namalokasi[posisi]
    );

    cout << "\n📍 Sekarang berada di "
         << namalokasi[posisi]
         << endl;

    cout << "+10 Koin\n";
    cout << "+10 Bahagia\n";
    cout << "-10 Energi\n";

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

                cout << "\n📍 Sekarang berada di Toko\n";

                cout << "Gunakan menu Beli Makanan untuk berbelanja.\n";
            }
        }
    }
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
}


// fitur Main
int main() {
    pet myPet;
    int pilih_jenis_pet;
    aktivitas* head = NULL;
    transaksi* top = NULL;
    Skill* skillRoot = BuatSkillTree();
    int posisi = 0; // Lokasi awal: Rumah

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
        cout << "2. 🗺 Lihat Peta Kota\n";
        cout << "3. 🚶 Jalan-jalan\n";
        cout << "4. \U0001F37D  Makan\n";
        cout << "5. \U0001F6D2 Beli Makanan\n";
        cout << "6. \U0001F634 Tidur\n";
        cout << "7. \U0001F3BE Main\n";
        cout << "8. \U0001F4DC Lihat Aktivitas\n";
        cout << "9. 🌟 Skill Tree\n";

    if (CekStatusPenuh(myPet)) {
        cout << "10. Lepas ke alam bebas (Pet dalam keadaan terbaik!)\n";
        cout << "11. Keluar\n";
    }
    else {
        cout << "10. Keluar\n";
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
                cout << "⭐ Skill Point : " << myPet.skillPoint << endl;
                break;

            case 2:
            TampilkanPetaLokasi();
            break;

            case 3:
            jalanjalan(posisi, myPet, head);

            if(posisi == 1)
            {
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
                    cout << "Kamu harus berada di Toko untuk membeli makanan!\n";                        break;
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
                UpdateStatus(myPet);
                break;

            case 7:
            {
                if(posisi != 2)
                {
                    cout << "Kamu harus berada di Arena untuk bermain!\n";
                    break;
                }

                Main(myPet, head, skillRoot);

                Skill* kecerdasan = CariSkill(skillRoot, "Kecerdasan");

                if(kecerdasan != NULL && kecerdasan->terbuka)
                {
                    myPet.skillPoint++;
                    cout << "Bonus Kecerdasan: +1 Skill Point!\n";
                }

                UpdateStatus(myPet);
                break;
            }

            case 8:
                LihatAktivitas(head);
                break;

            case 9:
                cout << "\n=== SKILL TREE ===\n";

                TampilkanSkill(skillRoot);

                cout << "\nSkill Point: "
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

            case 10:
                if (CekStatusPenuh(myPet)){
                    char konfirmasi;
                    cout << "\nStatus pet sudah penuh, Apakah anda ingin melepas pet ke alam bebas? (y/n): ";
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
                        cout << "Pet tetap dirawat. Lanjutkan rawat pet-mu dengan baik ya!" << endl;
                    }
                }
                else {
                    jalan = false;
                    cout << "Anda telah keluar dari game. Terima kasih telah memainkan PawPal ^-^\n";
                }
                break;

            case 11: 
            jalan = false;
            cout << "Anda telah keluar dari game. Terima kasih telah memainkan PawPal ^-^\n";
            break;

            default:
                cout << "Pilihan tidak valid!\n";
        }
    }

    return 0;
}
