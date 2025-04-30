//Sistem-Money-Tracking
//Project akhir mata kuliah Praktikum Algoritma Pemrograman dan Struktur Data

#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <cstring>
#include <cstdio>
using namespace std;

struct pemilik
{
    char nama[50], password[50], verifikasi[50];
}; pemilik pmlk[1000];


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

void daftar(int &jumlah)
{
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
    cin.getline(pmlk[jumlah].nama, 50);
    cout << "Masukkan Password   : ";
    cin.getline(pmlk[jumlah].password, 50);
    cout << "Verifikasi Untuk Ganti Password (bebas) : ";
    cin.getline(pmlk[jumlah].verifikasi, 50);

    FILE *file = fopen("akun.dat", "ab");
    if (!file)
    {
        cout << "Gagal membuka file untuk menulis!" << endl;
        return;
    }
    else
    {
        fwrite(&pmlk[jumlah], sizeof(pemilik), 1, file);
        fclose(file);
        cout << "\nAkun Berhasil Didaftarkan!" << endl;
    }
    jumlah++;
}

void login(){
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
            // login system money tracking
            cout << "\n===== Login System Money Tracking =====" << endl;
            cout << "Masukkan Nama    : ";
            cin.ignore();
            cin.getline(nama, 50);
            cout << "Masukkan Password: ";
            cin.getline(password, 50);
            system("cls");

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
                        // catat();
                        berhenti();
                        break;

                    case 2:
                        // tampil();
                        berhenti();
                        break;

                    case 3:
                        // sorting();
                        berhenti();
                        break;

                    case 4:
                        // searching();
                        berhenti();
                        break;

                    case 5:
                        // statistik();
                        berhenti();
                        break;

                    case 6:
                        // hapusdata();
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
            // reset password

        case 3:
            break;

        default:
            opsilain();
            berhenti();
        }
    } while (angka != 3);
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

int main()
{
    int pilih, jumlah = 0;
    do
    {
        tampilmenu(pilih);
        system("cls");

        switch (pilih)
        {
        case 1:
            daftar(jumlah);
            berhenti();
            break;

        case 2:
            login();
            berhenti();
            break;

        case 3:
            //deleteakun();
            //berhenti();
            break;

        case 4:
            exit(0);
            break;

        default:
            opsilain();
            berhenti();
            break;
        }
    } while (pilih != 4);
    return 0;
}
