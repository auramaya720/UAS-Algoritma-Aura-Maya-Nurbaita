int main() {
    Node* root = NULL;

    bacaCSV(root);

    cout << "Mahasiswa Lulus:\n";
    tampilkanMahasiswaLulus(root, 75);

    cout << "\nRata-rata keseluruhan: "
         << hitungRataNilai(root) << endl;

    return 0;
}
