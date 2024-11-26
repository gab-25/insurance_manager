#include <string>

using namespace std;

class Client {
    private:
        int id;
    public:
        string name;
        string surname;
        string email;
        
        Client(int x) {
            id = x;
        };

        void edit() {
            cout << "Inserire nome: ";
            cin >> name;
            cout << "Inserire cognome: ";
            cin >> surname;
            cout << "Inserire email: ";
            cin >> email;
        };

        void print() {
            cout << "cliente ID: " << id << endl;
            cout << "nome: " << name << endl;
            cout << "cognome: " << surname << endl;
            cout << "email: " << email << endl;
        };
};
