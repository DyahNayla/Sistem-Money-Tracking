// Sistem-Money-Tracking
// Project akhir mata kuliah Praktikum Algoritma Pemrograman dan Struktur Data

#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <ctime>
using namespace std;

struct pemilik
{
    char nama[50], password[50], verifikasi[50];
    char datetime[100]; 
};
pemilik pmlk;

struct Node
{
    pemilik *info;
    Node *next;
};

// Sisip depan ke linked list
void sisipDepan(Node *&head, pemilik pmlk)
{
    pemilik *baru = new pemilik;
    *baru = pmlk;

    Node *nodeBaru = new Node;
    nodeBaru->info = baru; 
    nodeBaru->next = head;
    head = nodeBaru;
}

struct moneytrack
{
    char kategori[50], hari[50], metodetransaksi[50];
    int date, years, month, nilaiTransaksi;
};
moneytrack money[1000];

// properti money tracking ⬇️
int totalitem = 0;     
char loggedInUser[50]; // Variabel untuk menyimpan pengguna yang sedang login

void opsilain()
{
    cout << "=========================================  " << endl;
    cout << "  Pilihan tidak Valid, silakan coba lagi  " << endl;
    cout << "========================================= " << endl;
}

void berhenti()
{
    char pilihan;
    cout << "Apakah Anda Ingin Kembali ke Menu Awal? (y/n): ";
    cin >> pilihan;

    if (pilihan == 'y' || pilihan == 'Y')
    {
        system("cls");
    }
    else if (pilihan == 'n' || pilihan == 'N')
    {
        cout << "Program selesai.\n";
        exit(0);
    }
    else
    {
        opsilain();
        berhenti();
    }
}

void tampilmenu(int &pilih)
{
    cout << "===================================" << endl;
    cout << "|           Menu Utama            |" << endl;
    cout << "===================================" << endl;
    cout << "| 1. Daftar Akun                  | " << endl;
    cout << "| 2. Login Akun                   |" << endl;
    cout << "| 3. Hapus Akun                   |" << endl;
    cout << "| 4. Tampilkan Akun               |" << endl;
    cout << "| 5. Keluar Program               |" << endl;
    cout << "===================================" << endl;
    cout << "Pilih Menu[1-4] : ";
    cin >> pilih;
}

void daftar(int &jumlah, Node *&head)
{

    FILE *file;
    pemilik temp;
    file = fopen("akun.dat", "rb");
    jumlah = 0;

    while (fread(&temp, sizeof(pemilik), 1, file))
    {
        jumlah++;
    }
    fclose(file);

    file = fopen("akun.dat", "ab");

    if (!file)
    {
        cout << "Gagal membuka file untuk menulis!" << endl;
        return;
    }

    if (jumlah >= 1000)
    {
        cout << "\n[Error] Kapasitas akun penuh!" << endl;
        return;
    }

    cout << endl
         << endl;
    cout << "===== Menu Pendaftaran Pengguna Baru =====" << endl;
    cout << "\n                          Total Akun: " << jumlah << endl;
    cin.ignore();
    cout << "\nMasukan Nama        : ";
    cin.getline(pmlk.nama, 50);
    cout << "Masukkan Password   : ";
    cin.getline(pmlk.password, 50);
    cout << "Verifikasi Untuk Ganti Password (bebas) : ";
    cin.getline(pmlk.verifikasi, 50);
    time_t now = time(0);
    strftime(pmlk.datetime, sizeof(pmlk.datetime), "%A, %d %B %Y, %H:%M:%S", localtime(&now));
    sisipDepan(head, pmlk); 

    fwrite(&pmlk, sizeof(pemilik), 1, file);

    jumlah++;
    fclose(file);
    cout << "\nAkun Berhasil Didaftarkan!" << endl;
}

void catat()
{
    int input;
    char delimiter;
    char filename[100];

    if (strlen(loggedInUser) == 0)
    {
        cout << "[Error] Anda harus login terlebih dahulu!\n";
        return;
    }

    strcpy(filename, loggedInUser);     
    strcat(filename, "_transaksi.dat"); 
    FILE *file;
    moneytrack temp;
    file = fopen(filename, "rb");
    totalitem = 0;

    while (fread(&temp, sizeof(moneytrack), 1, file))
    {
        totalitem++;
    }
    fclose(file);

    file = fopen(filename, "ab");
    if (!file)
    {
        cout << "Gagal membuka file untuk menulis!" << endl;
        return;
    }

    int startIndex = totalitem; 

    cout << "=======================================================================" << endl;
    cout << "                           Catat Keuangan" << endl;
    cout << "=======================================================================" << endl;
    cout << " Berapa Yang Ingin Anda Input : ";
    cin >> input;
    cout << endl;

    for (int i = 0; i < input; i++)
    {
        cout << " Masukkan Data Ke-" << totalitem + 1 << endl;
        cin.ignore();
        cout << " 1. Kategori                                  : ";
        cin.getline(money[totalitem].kategori, 50);
        cout << " 2. Hari                                      : ";
        cin.getline(money[totalitem].hari, 50);
        cout << " 3. Tanggal-Bulan-Tahun (example: dd-mm-yyyy) : ";
        cin >> money[totalitem].date >> delimiter >> money[totalitem].month >> delimiter >> money[totalitem].years;
        cout << " 4. Nilai Transaksi                           : Rp - ";
        cin >> money[totalitem].nilaiTransaksi;
        cin.ignore();
        cout << " 5. Metode Transaksi (Cash / Debit / Kredit)  : ";
        cin.getline(money[totalitem].metodetransaksi, 50);
        cout << endl;
        totalitem++;
    }
    for (int i = startIndex; i < totalitem; i++)
    {
        fwrite(&money[i], sizeof(moneytrack), 1, file);
    }

    fclose(file);
    cout << "Data berhasil disimpan!" << endl;
}

void tampil()
{
    char filename[100];
    int i = 0;
    moneytrack temp;

    if (strlen(loggedInUser) == 0)
    {
        cout << "[Error] Anda harus login terlebih dahulu!\n";
        return;
    }
    strcpy(filename, loggedInUser);     
    strcat(filename, "_transaksi.dat"); 
    FILE *file = fopen(filename, "rb");
    if (!file)
    {
        cout << "Belum ada data tersimpan atau gagal membuka file." << endl;
        return;
    }
    totalitem = 0;
    while (fread(&temp, sizeof(moneytrack), 1, file))
    {
        totalitem++;
    }
    rewind(file);
    cout << "=======================================================================" << endl;
    cout << "                           Riwayat Keuangan" << endl;
    cout << "=======================================================================" << endl;
    if (totalitem == 0)
    {
        cout << " Tidak ada transaksi yang tercatat.\n";
        return;
    }
    else
    {
        cout << "Membuka file: " << filename << endl;

        while (fread(&temp, sizeof(moneytrack), 1, file))
        {
            cout << " Data Ke-" << i + 1 << endl;
            cout << " 1. Kategori                                  : " << temp.kategori << endl;
            cout << " 2. Hari                                      : " << temp.hari << endl;
            cout << " 3. Tanggal-Bulan-Tahun                       : " << temp.date << "-" << temp.month << "-" << temp.years << endl;
            cout << " 4. Nilai Transaksi                           : Rp - " << temp.nilaiTransaksi << endl;
            cout << " 5. Metode Transaksi                          : " << temp.metodetransaksi << endl;
            cout << endl;
            i++;
        }
        cout << "Data Sukses Ditampilkan\n";
    }
    fclose(file);
}

void bubblesort()
{
    for (int i = 0; i < totalitem - 1; i++)
    {
        for (int j = 0; j < totalitem - i - 1; j++)
        {
            if (strcmp(money[j].kategori, money[j + 1].kategori) > 0)
            {
                swap(money[j], money[j + 1]);
            }
        }
    }
}

void sorting()
{
    char filename[100];

    if (strlen(loggedInUser) == 0)
    {
        cout << "[Error] Anda harus login terlebih dahulu!\n";
        return;
    }

    strcpy(filename, loggedInUser);     
    strcat(filename, "_transaksi.dat"); 
    FILE *file = fopen(filename, "rb");
    if (!file)
    {
        cout << "Gagal membuka file untuk menulis!" << endl;
        return;
    }
    totalitem = 0;
    while (fread(&money[totalitem], sizeof(moneytrack), 1, file))
    {
        totalitem++;
    }
    bubblesort();
    cout << "=======================================================================" << endl;
    cout << "               Riwayat Keuangan (Sorted by Category)" << endl;
    cout << "=======================================================================" << endl;
    for (int i = 0; i < totalitem; i++)
    {
        cout << " Data Ke-" << i + 1 << endl;
        cout << " 1. Kategori                                  : " << money[i].kategori << endl;
        cout << " 3. Tanggal-Bulan-Tahun                       : " << money[i].date << "-" << money[i].month << "-" << money[i].years << endl;
        cout << " 3. Hari                                      : " << money[i].hari << endl;
        cout << " 4. Nilai Transaksi                           : Rp - " << money[i].nilaiTransaksi << endl;
        cout << " 5. Metode Transaksi                          : " << money[i].metodetransaksi << endl;
        cout << endl;
    }
    cout << "Data Sukses Ditampilkan\n";
    fclose(file);
}

void searching()
{
    char filename[100];

    if (strlen(loggedInUser) == 0)
    {
        cout << "[Error] Anda harus login terlebih dahulu!\n";
        return;
    }

    strcpy(filename, loggedInUser);     // Menggunakan nama pengguna yang login
    strcat(filename, "_transaksi.dat"); // Menambahkan akhiran untuk file transaksi pengguna

    FILE *file = fopen(filename, "rb");
    if (!file)
    {
        cout << "Gagal membuka file untuk menulis!" << endl;
        return;
    }
    totalitem = 0;
    while (fread(&money[totalitem], sizeof(moneytrack), 1, file))
    {
        totalitem++;
    }

    bubblesort();
    char cari[50];
    bool found = false;
    int awal = 0, akhir = totalitem - 1, tengah;

    cout << "=============================================" << endl;
    cout << "         PENCARIAN BERDASARKAN KATEGORI       " << endl;
    cout << "=============================================" << endl;
    cout << "Masukkan kategori yang akan dicari: ";
    cin.ignore();
    cin.getline(cari, 50);
    system("cls");
    cout << endl << endl;

    while (awal <= akhir)
    {
        tengah = (awal + akhir) / 2;

        if ((strcmp(money[tengah].kategori, cari) == 0))
        {
            found = true;
            cout << "=======================================================================" << endl;
            cout << "                           Data Ditemukan" << endl;
            cout << "=======================================================================" << endl;
            cout << "Kategori: " << money[tengah].kategori << endl;
            cout << "Tahun: " << money[tengah].years << endl;
            cout << "Hari: " << money[tengah].hari << endl;
            cout << "Nilai Transaksi: Rp - " << money[tengah].nilaiTransaksi << endl;
            cout << "Metode Transaksi: " << money[tengah].metodetransaksi << endl;
            cout << "=======================================================================" << endl;
            break;
        }

        else if (strcmp(money[tengah].kategori, cari) > 0)
        {
            akhir = tengah - 1;
        }
        else
        {
            awal = tengah + 1;
        }
    }

    if (!found)
    {
        cout << "=============================================" << endl;
        cout << "  Data dengan kategori " << cari << " tidak ditemukan.  " << endl;
        cout << "=============================================" << endl;
    }
    fclose(file);
}

void statistik()
{
    if (strlen(loggedInUser) == 0)
    {
        cout << "[Error] Anda harus login terlebih dahulu!\n";
        return;
    }

    char filename[100];
    strcpy(filename, loggedInUser);
    strcat(filename, "_transaksi.dat");

    FILE *file = fopen(filename, "rb");
    if (!file)
    {
        cout << "Belum ada data tersimpan atau gagal membuka file." << endl;
        return;
    }

    int totalPengeluaran = 0;
    int jumlahTransaksi = 0;
    moneytrack temp;

    // Membaca semua transaksi dari file
    while (fread(&temp, sizeof(moneytrack), 1, file))
    {
        totalPengeluaran += temp.nilaiTransaksi; // Berisi nilai transaksi dari data yang baru saja dibaca
        jumlahTransaksi++;
    }
    fclose(file);

    // Menampilkan hasil statistik
    cout << "=======================================================================" << endl;
    cout << "                           Statistik Keuangan" << endl;
    cout << "=======================================================================" << endl;
    cout << " Total Transaksi: " << jumlahTransaksi << endl;
    cout << " Total Pengeluaran: Rp - " << totalPengeluaran << endl;
    cout << "=======================================================================" << endl;
}

void login(Node *head)
{
    char nama[1000], password[1000];
    int angka;
    pemilik temp;
    bool found = false;
    FILE *file = NULL;
    do
    {
        cout << "=================================" << endl;
        cout << "|       Pilih Tujuan Anda       |" << endl;
        cout << "---------------------------------" << endl;
        cout << "| 1. Login System Money Tracking|" << endl;
        cout << "| 2. Reset Password             |" << endl;
        cout << "| 3. Kembali                    |" << endl;
        cout << "=================================" << endl;
        cout << "Pilih [1-3] : ";
        cin >> angka;
        system("cls");

        switch (angka)
        {
        case 1:
            cout << "\n===== Login System Money Tracking =====" << endl;
            cout << "Masukkan Nama    : ";
            cin.ignore();
            cin.getline(nama, 50);
            cout << "Masukkan Password: ";
            cin.getline(password, 50);
            system("cls");
            found = false;

            file = fopen("akun.dat", "rb");
            if (file != NULL)
            {

                while (fread(&temp, sizeof(pemilik), 1, file))
                { 
                    if (strcmp(temp.nama, nama) == 0 && strcmp(temp.password, password) == 0)
                    {
                        found = true;
                        break;
                    }
                }
                fclose(file);
            }

            if (found)
            {
                strcpy(loggedInUser, nama); 
                int pilihan;
                do
                {
                    cout << "===================================" << endl;
                    cout << "|      Sistem Money Tracking      |" << endl;
                    cout << "===================================" << endl;
                    cout << "| 1. Catat Transaksi              | " << endl;
                    cout << "| 2. Tampilkan Riwayat Transaksi  |" << endl;
                    cout << "| 3. Sorting                      |" << endl;
                    cout << "| 4. Search Riwayat Transaksi     |" << endl;
                    cout << "| 5. Statistik Data               |" << endl;
                    cout << "| 6. Hapus Data                   |" << endl;
                    cout << "| 7. Kembali                      |" << endl;
                    cout << "===================================" << endl;
                    cout << "Pilih Menu[1-7] : ";
                    cin >> pilihan;
                    system("cls");

                    switch (pilihan)
                    {
                    case 1:
                        catat();
                        berhenti();
                        break;

                    case 2:
                        tampil();
                        berhenti();
                        break;

                    case 3:
                        sorting();
                        berhenti();
                        break;

                    case 4:
                        searching();
                        berhenti();
                        break;

                    case 5:
                        statistik();
                        berhenti();
                        break;

                    case 6:
                        hapusdata();
                        berhenti();
                        break;

                    case 7:
                        strcpy(loggedInUser, ""); 
                        break;

                    default:
                        opsilain();
                        berhenti();
                        break;
                    }
                } while (pilihan != 7);
            }
            else
            {
                cout << "\n[Error] Nama atau Password salah!" << endl;
            }
            berhenti();
            break;

        case 2:
        {
            char nama_login[50], verifikasi_login[50], password_baru[50];
            bool ditemukan = false;
            pemilik temp[1000];
            int total = 0;

            cout << "\n                     Reset Password" << endl;
            cout << "==========================================================" << endl;
            cin.ignore();
            cout << "\nMasukkan Nama Akun Yang Akan Direset : ";
            cin.getline(nama_login, 50);

            Node *bantu = head;
            while (bantu != nullptr)
            {
                if (strcmp(nama_login, bantu->info->nama) == 0)
                {
                    cout << "\nSelamat Datang " << bantu->info->nama << endl;
                    cout << "Masukkan Verifikasi Pengenal Anda : ";
                    cin.getline(verifikasi_login, 50);

                    if (strcmp(verifikasi_login, bantu->info->verifikasi) == 0)
                    {
                        cout << "Silakan Masukkan Password Baru Anda : ";
                        cin.getline(password_baru, 50);

                        if (strcmp(password_baru, bantu->info->password) == 0)
                        {
                            cout << "Password baru tidak boleh sama dengan password sebelumnya." << endl;
                            berhenti();
                            return;
                        }

                        strcpy(bantu->info->password, password_baru);
                        ditemukan = true;

                        FILE *file = fopen("akun.dat", "wb");
                        if (!file)
                        {
                            cout << "Gagal membuka file untuk menulis ulang." << endl;
                            berhenti();
                            return;
                        }

                        Node *tulis = head;
                        while (tulis != nullptr)
                        {
                            fwrite(tulis->info, sizeof(pemilik), 1, file);
                            tulis = tulis->next;
                        }
                        fclose(file);

                        cout << "Password berhasil direset." << endl;
                        berhenti();
                        return;
                    }
                    else
                    {
                        cout << "Verifikasi salah." << endl;
                        berhenti();
                        return;
                    }
                }
                bantu = bantu->next;
            }

            if (!ditemukan)
            {
                cout << "Akun tidak ditemukan." << endl;
                berhenti();
            }
        }

        case 3:
            break;

        default:
            opsilain();
            berhenti();
            break;
        }
    } while (angka != 3);
}

void deleteakun(Node *&head)
{
    char nama_login[50], password[50], filename[100];
    bool ditemukan = false;
    int total = 0;

    Node *bantu = head;
    Node *previous = nullptr;

    cout << "\n                     Hapus Akun" << endl;
    cout << "==========================================================" << endl;
    cin.ignore();
    cout << "\nMasukkan Nama Akun Yang Akan Dihapus : ";
    cin.getline(nama_login, 50);
    cout << "Password                             : ";
    cin.getline(password, 50);

    while (bantu != nullptr)
    {
        if (strcmp(nama_login, bantu->info->nama) == 0 && strcmp(password, bantu->info->password) == 0)
        {
            ditemukan = true;

            sprintf(filename, "%s_transaksi.dat", nama_login);
            if (remove(filename) != 0)
            {
                perror("Gagal menghapus file transaksi");
            }
            else
            {
                cout << "File transaksi berhasil dihapus." << endl;
            }

            if (previous == nullptr)
            {
                head = bantu->next; 
            }
            else
            {
                previous->next = bantu->next; 
            }

            delete bantu; 
            cout << "Akun berhasil dihapus." << endl;

            FILE *file = fopen("akun.dat", "wb");
            if (file)
            {
                Node *temp = head;
                while (temp != nullptr)
                {
                    fwrite(temp->info, sizeof(pemilik), 1, file);
                    temp = temp->next;
                }
                fclose(file);
            }
            else
            {
                cout << "Gagal menulis ulang file akun." << endl;
            }

            break; 
        }

        previous = bantu;
        bantu = bantu->next;
    }

    if (!ditemukan)
    {
        cout << "Akun tidak ditemukan atau password salah." << endl;
    }
}

void tampilkanakun(int &jumlah, Node *head)
{
    int i = 0;
    FILE *file = fopen("akun.dat", "rb");
    pemilik temp;
    if (!file)
    {
        cout << "Belum ada data tersimpan atau gagal membuka file." << endl;
        return;
    }
    jumlah = 0;
    while (fread(&temp, sizeof(pemilik), 1, file))
    {

        jumlah++;
    }
    cout << "=======================================================================" << endl;
    cout << "                           Daftar Akun" << endl;
    cout << "=======================================================================" << endl;
    if (jumlah == 0)
    {
        cout << " Tidak ada akun yang tercatat.\n";
        return;
    }
    else
    {
        while (head != nullptr)
        {
            pemilik *p = head->info; 
            cout << " Akun Ke-" << i + 1 << endl;
            cout << " " << p->nama << endl;
            cout << " Tanggal Pendaftaran: " << p->datetime << endl;
            cout << endl;
            i++;
            head = head->next;
        }
        cout << endl;
        cout << "Data Sukses Ditampilkan\n";
    }
    fclose(file);
}

void bacadataakun(Node *&head)
{
    FILE *file = fopen("akun.dat", "rb");
    pemilik temp;
    if (!file)
    {
        cout << "Belum ada data tersimpan atau gagal membuka file." << endl;
        return;
    }
    while (fread(&temp, sizeof(pemilik), 1, file))
    {
        sisipDepan(head, temp);
    }

    fclose(file);
}

int main()
{

    Node *head = nullptr;
    bacadataakun(head);
    int pilih, jumlah = 0;
    do
    {
        tampilmenu(pilih);
        system("cls");

        switch (pilih)
        {
        case 1:
            daftar(jumlah, head);
            berhenti();
            break;

        case 2:
            login(head);
            berhenti();
            break;

        case 3:
            deleteakun(head);
            berhenti();
            break;

        case 4:
            tampilkanakun(jumlah, head);
            berhenti();
            break;

        case 5:
            exit(0);
            break;

        default:
            opsilain();
            berhenti();
            break;
        }
    } while (pilih != 5);
    return 0;
}
