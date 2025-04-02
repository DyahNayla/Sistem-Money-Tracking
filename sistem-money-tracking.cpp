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
