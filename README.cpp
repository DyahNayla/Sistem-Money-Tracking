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
            //berhenti();
            break;

        case 2:
            //login();
            //berhenti();
            break;

        case 3:
            //deleteakun();
            //berhenti();
            break;

        case 4:
            exit(0);
            break;

        default:
            //opsilain();
            //berhenti();
            break;
        }
    } while (pilih != 4);
    return 0;
}
