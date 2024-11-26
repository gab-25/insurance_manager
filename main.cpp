#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <limits>

#include "client.cpp"

using namespace std;

void load_file(vector<Client> &clients) {
    ifstream file("data.csv");
    if (!file.is_open()) {
        cerr << "failed to open file!" << endl;
        return;
    }
    string line;
    int count_line = 0;
    while(getline(file, line)) {
        if (count_line > 0) {
            stringstream ss(line);
            string name, surname, email;
            getline(ss, name, ';');
            getline(ss, surname, ';');
            getline(ss, email);
            Client c(count_line);
            c.name = name;
            c.surname = surname;
            c.email = email;
            clients.push_back(c);
        }
        count_line++;
    }
    file.close();
}

void save_file(vector<Client> &clients) {
    ofstream file("data.csv");
    if(!file.is_open()) {
        cerr << "failed to open file!" << endl;
        return;
    }
    file << "name;surname;email\n";
    for(Client& client : clients) {
        file << client.name << ";" << client.surname << ";" << client.email << "\n";
    }
    file.close();
}

void add_client(vector<Client> &clients) {
    Client client(clients.size()+1);
    client.edit();
    clients.push_back(client);
    save_file(clients);
    cout << "cliente inserito!" << endl;
}

void list_clients(vector<Client> &clients) {
    cout << "Clienti:" << endl;
    if (clients.size() == 0) {
        cout << "nessun cliente!" << endl;
        return;
    }
    for(Client& client : clients) {
        client.print();
    }
}

void edit_client(vector<Client> &clients) {
    cout << "ID Cliente: ";
    int id_client;
    cin >> id_client;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    if (id_client == 0) {
        cout << "valore non valido!" << endl;
        return;
    }
    clients[id_client-1].edit();
    save_file(clients);
}

void delete_client(vector<Client> &clients) {
    cout << "ID Cliente: ";
    int id_client;
    cin >> id_client;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    if (id_client == 0) {
        cout << "valore non valido!" << endl;
        return;
    }
    clients.erase(clients.begin()+id_client);
    save_file(clients);
}

void search_client(vector<Client> &clients) {
}

void menu() {
    cout << "\nMenu:" << endl;
    cout << "1. Aggiungi cliente" << endl;
    cout << "2. Visualizza clienti" << endl;
    cout << "3. Modifica cliente" << endl;
    cout << "4. Elimina cliente" << endl;
    cout << "5. Ricerca cliente" << endl;
    cout << "6. Gestione delle interazioni" << endl;
    cout << "0. Esci" << endl;
    cout << "Scelta: ";
}

int main() {
    vector<Client> clients;
    load_file(clients);

    while (true) {
        menu();
        int selected;
        cin >> selected;
        switch (selected) {
            case 1:
                add_client(clients);
                break;
            case 2:
                list_clients(clients);
                break;
            case 3:
                edit_client(clients);
                break;
            case 4:
                delete_client(clients);
                break;
            case 5:
                break;
            case 6:
                break;
            case 0:
                return 0;
        }
    }
}
