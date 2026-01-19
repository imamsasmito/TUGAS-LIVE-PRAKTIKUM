#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstring>

using namespace std;

struct Siswa {
    string nama;
    int nim;
    float nilai[3];
};

// ===== SOAL 1 =====
// Fungsi untuk menampilkan menu
void tampilkanMenu() {
    cout << "\n=== SISTEM MANAJEMEN NILAI SISWA ===" << endl;
    cout << "1. Input Data Siswa" << endl;
    cout << "2. Tampilkan Data Siswa" << endl;
    cout << "3. Simpan Data ke File" << endl;
    cout << "4. Baca Data dari File" << endl;
    cout << "5. Keluar" << endl;
    cout << "Pilihan: ";
}

// Fungsi untuk menghitung rata-rata nilai (return value)
float hitungRataRata(float nilai1, float nilai2, float nilai3) {
    return (nilai1 + nilai2 + nilai3) / 3.0;
}

// Fungsi untuk input data siswa (void)
void inputData(Siswa arr[], int& jumlah) {
    cout << "\n--- Input Data Siswa ---" << endl;
    cout << "Nama: ";
    cin.ignore();
    getline(cin, arr[jumlah].nama);

    cout << "NIM: ";
    cin >> arr[jumlah].nim;

    cout << "Masukkan 3 nilai mata pelajaran:" << endl;
    for (int i = 0; i < 3; i++) {
        cout << "Nilai " << (i + 1) << ": ";
        cin >> arr[jumlah].nilai[i];
    }

    cout << "Data berhasil ditambahkan!" << endl;
    jumlah++;
}

// Fungsi untuk menampilkan daftar siswa (void)
void tampilkanDaftar(Siswa arr[], int jumlah) {
    if (jumlah == 0) {
        cout << "\nTidak ada data siswa!" << endl;
        return;
    }

    cout << "\n=== DAFTAR SISWA ===" << endl;
    cout << setw(20) << "Nama" << setw(15) << "NIM"
        << setw(12) << "Nilai 1" << setw(12) << "Nilai 2"
        << setw(12) << "Nilai 3" << setw(12) << "Rata-rata" << endl;
    cout << "=====================================================================" << endl;

    for (int i = 0; i < jumlah; i++) {
        float rataRata = hitungRataRata(arr[i].nilai[0], arr[i].nilai[1], arr[i].nilai[2]);
        cout << setw(20) << arr[i].nama << setw(15) << arr[i].nim
            << fixed << setprecision(2)
            << setw(12) << arr[i].nilai[0] << setw(12) << arr[i].nilai[1]
            << setw(12) << arr[i].nilai[2] << setw(12) << rataRata << endl;
    }
}

// ===== SOAL 2 =====
// Fungsi untuk simpan data ke file data_siswa.txt (void)
void simpanKeFile(Siswa arr[], int jumlah) {
    ofstream file("data_siswa.txt");

    if (!file.is_open()) {
        cout << "\nGagal membuka file!" << endl;
        return;
    }

    for (int i = 0; i < jumlah; i++) {
        file << arr[i].nama << ";" << arr[i].nim << ";";
        file << arr[i].nilai[0] << ";" << arr[i].nilai[1] << ";"
            << arr[i].nilai[2] << endl;
    }

    file.close();
    cout << "\nData berhasil disimpan ke file data_siswa.txt" << endl;
    cout << "Jumlah siswa: " << jumlah << endl;
}

// ===== SOAL 3 =====
// Fungsi untuk baca data dari file data_siswa.txt (void)
void bacaFromFile(Siswa arr[], int& jumlah) {
    ifstream file("data_siswa.txt");

    if (!file.is_open()) {
        cout << "\nFile tidak ditemukan atau gagal dibuka!" << endl;
        return;
    }

    jumlah = 0;
    string line;

    while (getline(file, line) && jumlah < 100) {
        int pos1 = line.find(';');
        int pos2 = line.find(';', pos1 + 1);
        int pos3 = line.find(';', pos2 + 1);
        int pos4 = line.find(';', pos3 + 1);

        arr[jumlah].nama = line.substr(0, pos1);
        arr[jumlah].nim = stoi(line.substr(pos1 + 1, pos2 - pos1 - 1));
        arr[jumlah].nilai[0] = stof(line.substr(pos2 + 1, pos3 - pos2 - 1));
        arr[jumlah].nilai[1] = stof(line.substr(pos3 + 1, pos4 - pos3 - 1));
        arr[jumlah].nilai[2] = stof(line.substr(pos4 + 1));

        jumlah++;
    }

    file.close();
    cout << "\nData berhasil dibaca dari file data_siswa.txt" << endl;
    cout << "Jumlah siswa: " << jumlah << endl;
}

int main() {
    Siswa arr[100];
    int jumlah = 0;
    int pilihan;

    while (true) {
        tampilkanMenu();
        cin >> pilihan;

        switch (pilihan) {
        case 1:
            if (jumlah < 100) {
                inputData(arr, jumlah);
            }
            else {
                cout << "\nKapasitas array sudah penuh!" << endl;
            }
            break;
        case 2:
            tampilkanDaftar(arr, jumlah);
            break;
        case 3:
            simpanKeFile(arr, jumlah);
            break;
        case 4:
            bacaFromFile(arr, jumlah);
            break;
        case 5:
            cout << "\n~ Selamat Mengerjakan ~" << endl;
            return 0;
        default:
            cout << "\nPilihan tidak valid!" << endl;
        }
    }

    return 0;
}