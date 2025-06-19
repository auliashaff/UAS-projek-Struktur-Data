#include <iostream>
#include <string>
using namespace std;

struct Lagu {
    int id;
    string judul;
    string artis;
    int durasi;
    Lagu* next;
    Lagu* prev;
};

Lagu* head = NULL;
Lagu* tail = NULL;
Lagu* nowPlaying = NULL;

void tambahLagu() {
    Lagu* laguBaru = new Lagu;
    cout << "ID Lagu   : "; cin >> laguBaru->id;
    cin.ignore();
    cout << "Judul     : "; getline(cin, laguBaru->judul);
    cout << "Artis     : "; getline(cin, laguBaru->artis);
    cout << "Durasi(s) : "; cin >> laguBaru->durasi;

    laguBaru->next = NULL;
    laguBaru->prev = NULL;

    if (head == NULL) {
        head = tail = nowPlaying = laguBaru;
    } else {
        tail->next = laguBaru;
        laguBaru->prev = tail;
        tail = laguBaru;
    }
    cout << "Lagu berhasil ditambahkan!\n";
}

void tampilkanPlaylist() {
    Lagu* temp = head;
    cout << "\n=== Playlist ===\n";
    while (temp != NULL) {
        cout << "ID: " << temp->id
             << " | Judul: " << temp->judul
             << " | Artis: " << temp->artis
             << " | Durasi: " << temp->durasi << "s\n";
        temp = temp->next;
    }
}
void urutkanJudul() {
    if (head == NULL || head->next == NULL) {
        cout << "Tidak ada cukup lagu untuk diurutkan.\n";
        return;
    }

    bool swapped;
    do {
        swapped = false;
        Lagu* cur = head;
        while (cur->next != NULL) {
            if (cur->judul > cur->next->judul) {
                swap(cur->id, cur->next->id);
                swap(cur->judul, cur->next->judul);
                swap(cur->artis, cur->next->artis);
                swap(cur->durasi, cur->next->durasi);
                swapped = true;
            }
            cur = cur->next;
        }
    } while (swapped);
    cout << "Playlist berhasil diurutkan berdasarkan judul (A-Z).\n";
}
void cariLagu() {
    if (head == NULL) {
        cout << "Playlist kosong.\n";
        return;
    }

    int pilih;
    cout << "Cari berdasarkan:\n1. ID\n2. Judul\nPilih: ";
    cin >> pilih;
    cin.ignore();

    Lagu* temp = head;
    bool ditemukan = false;

    if (pilih == 1) {
        int idCari;
        cout << "Masukkan ID lagu: ";
        cin >> idCari;
        while (temp != NULL) {
            if (temp->id == idCari) {
                ditemukan = true;
                break;
            }
            temp = temp->next;
        }
    } else if (pilih == 2) {
        string judulCari;
        cout << "Masukkan Judul lagu: ";
        getline(cin, judulCari);
        while (temp != NULL) {
            if (temp->judul == judulCari) {
                ditemukan = true;
                break;
            }
            temp = temp->next;
        }
    } else {
        cout << "Pilihan tidak valid.\n";
        return;
    }

    if (ditemukan) {
        cout << "Ditemukan:\n";
        cout << "ID: " << temp->id
             << " | Judul: " << temp->judul
             << " | Artis: " << temp->artis
             << " | Durasi: " << temp->durasi << "s\n";
    } else {
        cout << "Lagu tidak ditemukan.\n";
    }
}

void mainkanLagu() {
    if (nowPlaying == NULL) {
        cout << "Playlist kosong!\n";
        return;
    }

    cout << "\nNow Playing: " << nowPlaying->judul << " - " << nowPlaying->artis << endl;
    cout << "1. Lagu Sebelumnya\n2. Lagu Selanjutnya\nPilih: ";
    int pilihan; cin >> pilihan;

    if (pilihan == 1 && nowPlaying->prev != NULL)
        nowPlaying = nowPlaying->prev;
    else if (pilihan == 2 && nowPlaying->next != NULL)
        nowPlaying = nowPlaying->next;
    else
        cout << "Tidak bisa berpindah lagu.\n";
}
void hapusLagu() {
    if (head == NULL) {
        cout << "Playlist kosong.\n";
        return;
    }

    int idHapus;
    cout << "Masukkan ID lagu yang ingin dihapus: ";
    cin >> idHapus;

    Lagu* cur = head;

    while (cur != NULL) {
        if (cur->id == idHapus) {
            if (cur == head && cur == tail) {
                head = tail = nowPlaying = NULL;
            }
            else if (cur == head) {
                head = head->next;
                head->prev = NULL;
            }
            else if (cur == tail) {
                tail = tail->prev;
                tail->next = NULL;
            }
            else {
                cur->prev->next = cur->next;
                cur->next->prev = cur->prev;
            }
                if (nowPlaying == cur) {
                nowPlaying = head;
            }

            delete cur;
            cout << "Lagu berhasil dihapus.\n";
            return;
        }
        cur = cur->next;
    }
    cout << "Lagu dengan ID tersebut tidak ditemukan.\n";
}

int main() {
    int pilih;
    do {
        cout << "\n========== MENU PLAYER ==========\n";
        cout << "1. Tambah Lagu\n";
        cout << "2. Tampilkan Playlist\n";
        cout << "3. Urutkan Lagu\n";
        cout << "4. Cari Lagu\n";
        cout << "5. Mainkan Lagu (Next/Prev)\n";
        cout << "6. Hapus Lagu (ID)\n";
        cout << "0. Keluar\n";
        cout << "Pilih: ";
        cin >> pilih;

        switch (pilih) {
            case 1: tambahLagu(); break;
            case 2: tampilkanPlaylist(); break;
            case 3: urutkanJudul(); break;
            case 4: cariLagu(); break;
            case 5: mainkanLagu(); break;
            case 6: hapusLagu(); break;
            case 0: cout << "Keluar.\n"; break;
            default: cout << "Pilihan tidak valid.\n";
        }
    } while (pilih != 0);

    return 0;
}

