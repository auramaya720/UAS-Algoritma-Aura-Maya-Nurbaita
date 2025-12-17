#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

/* ================== STRUCT ================== */
struct Mahasiswa {
    int student_id;
    string gender;
    int math_score;
    int reading_score;
    int writing_score;
};

struct Node {
    Mahasiswa data;
    Node* left;
    Node* right;
};

/* ================== FUNGSI 1 ================== */
/* tambahDataMahasiswa */
Node* tambahDataMahasiswa(Node* root, Mahasiswa data) {
    if (root == NULL) {
        Node* nodeBaru = new Node;
        nodeBaru->data = data;
        nodeBaru->left = NULL;
        nodeBaru->right = NULL;
        return nodeBaru;
    }

    if (data.student_id < root->data.student_id) {
        root->left = tambahDataMahasiswa(root->left, data);
    } else if (data.student_id > root->data.student_id) {
        root->right = tambahDataMahasiswa(root->right, data);
    }

    return root;
}

/* ================== FUNGSI 2 ================== */
/* cariMahasiswa */
Node* cariMahasiswa(Node* root, int student_id) {
    if (root == NULL || root->data.student_id == student_id)
        return root;

    if (student_id < root->data.student_id)
        return cariMahasiswa(root->left, student_id);
    else
        return cariMahasiswa(root->right, student_id);
}

/* ================== FUNGSI 3 ================== */
/* tampilkanMahasiswaLulus */
void tampilkanMahasiswaLulus(Node* root, float batas) {
    if (root == NULL) return;

    tampilkanMahasiswaLulus(root->left, batas);

    float rata = (root->data.math_score +
                  root->data.reading_score +
                  root->data.writing_score) / 3.0;

    if (rata >= batas) {
        cout << "ID: " << root->data.student_id
             << " | Gender: " << root->data.gender
             << " | Rata-rata: " << rata << endl;
    }

    tampilkanMahasiswaLulus(root->right, batas);
}

/* ================== FUNGSI 4 ================== */
/* hitungRataNilai */
void hitungTotal(Node* root, int &total, int &jumlah) {
    if (root == NULL) return;

    hitungTotal(root->left, total, jumlah);

    total += root->data.math_score +
             root->data.reading_score +
             root->data.writing_score;
    jumlah += 3;

    hitungTotal(root->right, total, jumlah);
}

float hitungRataNilai(Node* root) {
    int total = 0, jumlah = 0;
    hitungTotal(root, total, jumlah);

    if (jumlah == 0) return 0;
    return (float) total / jumlah;
}

/* ================== FUNGSI 5 ================== */
/* hapusMahasiswa */
Node* cariMin(Node* root) {
    while (root->left != NULL)
        root = root->left;
    return root;
}

Node* hapusMahasiswa(Node* root, int student_id) {
    if (root == NULL) return root;

    if (student_id < root->data.student_id) {
        root->left = hapusMahasiswa(root->left, student_id);
    }
    else if (student_id > root->data.student_id) {
        root->right = hapusMahasiswa(root->right, student_id);
    }
    else {
        if (root->left == NULL) {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == NULL) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        Node* temp = cariMin(root->right);
        root->data = temp->data;
        root->right = hapusMahasiswa(root->right, temp->data.student_id);
    }

    return root;
}

/* ================== BACA DATASET CSV ================== */
void bacaCSV(Node* &root) {
    ifstream file("StudentsPerformance.csv");
    string line, temp;
    int id = 1;

    getline(file, line); // skip header

    while (getline(file, line)) {
        stringstream ss(line);

        Mahasiswa m;
        m.student_id = id++;

        getline(ss, m.gender, ','); // gender
        getline(ss, temp, ','); // race (skip)
        getline(ss, temp, ','); // parental (skip)
        getline(ss, temp, ','); // lunch (skip)
        getline(ss, temp, ','); // prep (skip)

        getline(ss, temp, ',');
        m.math_score = stoi(temp);

        getline(ss, temp, ',');
        m.reading_score = stoi(temp);

        getline(ss, temp, ',');
        m.writing_score = stoi(temp);

        root = tambahDataMahasiswa(root, m);
    }

    file.close();
}

/* ================== MAIN ================== */
int main() {
    Node* root = NULL;

    bacaCSV(root);

    cout << "Mahasiswa Lulus:\n";
    tampilkanMahasiswaLulus(root, 75);

    cout << "\nRata-rata keseluruhan: "
         << hitungRataNilai(root) << endl;

    return 0;
}

