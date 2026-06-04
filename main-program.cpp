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
    int makanan;
    int apel;
    int daging;
    int roti;
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
baru-> pesan = keterangan;
baru -> next = head;
head = baru;
}

void BeliMakanan(pet &p, aktivitas* &head){
    int pilih;

    cout << "=== TOKO MAKANAN ===" << endl;
    cout << "1. Apel (Harga: 5, Lapar -5)" << endl;
    cout << "2. Daging (Harga: 15, Lapar -15)" << endl;
    cout << "3. Roti (Harga: 7, Lapar: -10)" << endl;
    cout << "4. Kembali" << endl;
    pilih = ValidasiInput(1,4, "Pilih makanan yang ingin dibeli(masukkan angka): ");

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
        else cout << "Koin tidak cukup!";
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
        } else cout << "Koin tidak cukup!\n";
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
        } else cout << "Koin tidak cukup!\n";
    }
    else {
        cout << "Makanan tidak tersedia!\n";
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

void gameSusunBola (pet &p, aktivitas* &head){
        isiAwal();

    int asal, tujuan;

    do {
        display();

            if (cekMenang()) {

        p.koin += 50;
        p.bahagia += 20;
        p.energi -= 10;

        if (p.bahagia > 100) p.bahagia = 100;
        if (p.energi < 0) p.energi = 0;

        cout << "\n🎉 Selamat Kamu Menang!\n";
        cout << "+50 Koin\n";
        cout << "+20 Bahagia\n";
        cout << "-10 Energi\n";

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

        if (asal == 0)
        {
            cout << "Kamu menyerah, tidak mendapat poin!\n";  

            TambahAktivitas(head, "Menyerah pada game susun bola");
            return;
        }

        if (asal == -1) break;

        cout << "\nPilih tabung tujuan: ";
        cin >> tujuan;

        asal--;
        tujuan--;

        if (asal < 0 || asal >= jumlahTabung || tujuan < 0 || tujuan >= jumlahTabung) {
            cout << "Input tabung tidak valid!\n";
            continue;
        }

        pindah(asal, tujuan);

    } while (true);
}

// fungsi Main
void Main(pet &p, aktivitas* &head) {
    int pilih;

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

        gameSusunBola(p, head);
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
}

// Fungsi untuk update status pet setiap kali melakukan aktivitas
void UpdateStatus(pet &p) {

    // Lapar (naik tiap pilih menu kalau belum 0)
    if (p.lapar > 0) {
        p.lapar += 1;
    }

    // Energi (turun tiap pilih menu kalau belum 100)
    if (p.energi < 100) {
        p.energi -= 1;
    }

    // Bahagia (turun tiap pilih menu kalau belum 100)
    if (p.bahagia < 100) {
        p.bahagia -= 1;
    }

    // Batas
    if (p.lapar > 100) p.lapar = 100;
    if (p.energi < 0) p.energi = 0;
    if (p.bahagia < 0) p.bahagia = 0;
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

    // Reset inventory
    p.apel = 0;
    p.daging = 0;
    p.roti = 0;

    cout << "Pet baru berhasil dibuat!\n";
    cout << "Koin kamu tetap: " << p.koin << endl;
}

// fitur Main
int main() {
    pet myPet;
    int pilih_jenis_pet;
    aktivitas* head = NULL;

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
        cout << "2. \U0001F37D  Makan\n";
        cout << "3. \U0001F6D2 Beli Makanan\n";
        cout << "4. \U0001F634 Tidur\n";
        cout << "5. \U0001F3BE Main\n";
        cout << "6. \U0001F4DC Lihat Aktivitas\n";

    if (CekStatusPenuh(myPet)) {
        cout << "7. Lepas ke alam bebas (Pet dalam keadaan terbaik!)\n";
        cout << "8. Keluar\n";
    }
    else {
        cout << "7. Keluar\n";
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
                break;

            case 2:
                Makan(myPet, head);
                UpdateStatus(myPet);
                break;

            case 3:
                BeliMakanan(myPet, head);
                UpdateStatus(myPet);
                break;

            case 4:
                Tidur(myPet, head);
                UpdateStatus(myPet);
                break;

            case 5:
                Main(myPet, head);
                UpdateStatus(myPet);
                break;

            case 6:
                LihatAktivitas(head);
                break;

            case 7:
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

            case 8: 
            jalan = false;
            cout << "Anda telah keluar dari game. Terima kasih telah memainkan PawPal ^-^\n";
            break;

            default:
                cout << "Pilihan tidak valid!\n";
        }
    }

    return 0;
}
