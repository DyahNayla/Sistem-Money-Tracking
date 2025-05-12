//Sistem-Money-Tracking
//Project akhir mata kuliah Praktikum Algoritma Pemrograman dan Struktur Data

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
    char datetime[100]; // Menyimpan tanggal dan waktu pendaftaran
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
    nodeBaru->info = baru; // data sekarang bertipe pemilik*
    nodeBaru->next = head;
    head = nodeBaru;
}

// properti money tracking ⬇️
int totalitem = 0; // Jumlah transaksi yang tersimpan
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
    cout << "| 4. Keluar Program               |" << endl;
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

    cout << endl << endl;
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
    sisipDepan(head, pmlk); // ke linked list

    fwrite(&pmlk, sizeof(pemilik), 1, file);

    jumlah++;
    fclose(file);
    cout << "\nAkun Berhasil Didaftarkan!" << endl;
}

void login(Node *head)
{
    char nama[1000], password[1000];
    int angka;
    pemilik temp;
    bool found = false;
    FILE *file = NULL; // Inisialisasi di awal agar dikenali di semua case (untuk menghidari error di switch case)

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
                { // temp berfungsi sebagai variabel sementara untuk membaca data akun dari file
                  // program membuka file dan membaca akun satu per satu menggunakan fread lalu disimpan dalam temp
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
                strcpy(loggedInUser, nama); // Simpan nama pengguna yang berhasil login
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
                        //catat();
                        berhenti();
                        break;

                    case 2:
                        //tampil();
                        berhenti();
                        break;

                    case 3:
                        //sorting();
                        berhenti();
                        break;

                    case 4:
                        //searching();
                        berhenti();
                        break;

                    case 5:
                        //statistik();
                        berhenti();
                        break;

                    case 6:
                        //hapusdata();
                        berhenti();
                        break;

                    case 7:
                        strcpy(loggedInUser, ""); // Hapus informasi login saat keluar
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
            //resetpassword();

        case 3:
            break;

        default:
            opsilain();
            berhenti();
            break;
        }
    } while (angka != 3);
}

int main()
{

    Node *head = nullptr;
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
            //deleteakun(head);
            berhenti();
            break;

        case 4:
            //tampilkanakun(jumlah, head);
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
