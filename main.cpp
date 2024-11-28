#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "client.cpp"
#include <limits>

class CRM
{
private:
    std::vector<Client> clients;
    const std::string FILE_PATH = "clients.csv";

public:
    void addClient()
    {
        std::string name, surname, email, telephone;
        std::cout << "Inserisci nome: ";
        std::getline(std::cin >> std::ws, name);
        std::cout << "Inserisci cognome: ";
        std::getline(std::cin, surname);
        std::cout << "Inserisci email: ";
        std::getline(std::cin, email);
        std::cout << "Inserisci telefono: ";
        std::getline(std::cin, telephone);

        clients.emplace_back(name, surname, email, telephone);
        std::cout << "Cliente aggiunto con successo!" << std::endl;
        saveToFile();
    }

    void listClients()
    {
        if (clients.empty())
        {
            std::cout << "Nessun cliente presente." << std::endl;
            return;
        }

        for (size_t i = 0; i < clients.size(); ++i)
        {
            std::cout << "Cliente " << i + 1 << ": " << clients[i].toString() << std::endl;
        }
    }

    void editClient()
    {
        listClients();
        if (clients.empty())
            return;

        int index;
        std::cout << "Inserisci il numero del cliente da modificare: ";
        std::cin >> index;

        if (index < 1 || index > static_cast<int>(clients.size()))
        {
            std::cout << "Indice non valido." << std::endl;
            return;
        }

        Client &client = clients[index - 1];
        int scelta;
        do
        {
            std::cout << "\nCosa vuoi modificare?\n";
            std::cout << "1. Nome\n";
            std::cout << "2. Cognome\n";
            std::cout << "3. Email\n";
            std::cout << "4. Telefono\n";
            std::cout << "5. Esci\n";
            std::cout << "Scelta: ";
            std::cin >> scelta;

            switch (scelta)
            {
            case 1:
            {
                std::string newName;
                std::cout << "Nuovo nome: ";
                std::cin >> newName;
                client.setName(newName);
                break;
            }
            case 2:
            {
                std::string newSurname;
                std::cout << "Nuovo cognome: ";
                std::cin >> newSurname;
                client.setSurname(newSurname);
                break;
            }
            case 3:
            {
                std::string newEmail;
                std::cout << "Nuova email: ";
                std::cin >> newEmail;
                client.setEmail(newEmail);
                break;
            }
            case 4:
            {
                std::string newTelephone;
                std::cout << "Nuovo telefono: ";
                std::cin >> newTelephone;
                client.setTelephone(newTelephone);
                break;
            }
            }
        } while (scelta != 5);
        saveToFile();
    }

    void removeClient()
    {
        listClients();
        if (clients.empty())
            return;

        int index;
        std::cout << "Inserisci il numero del cliente da eliminare: ";
        std::cin >> index;

        if (index < 1 || index > static_cast<int>(clients.size()))
        {
            std::cout << "Indice non valido." << std::endl;
            return;
        }

        clients.erase(clients.begin() + index - 1);
        std::cout << "Cliente eliminato con successo!" << std::endl;
        saveToFile();
    }

    void searchClient()
    {
        std::string search;
        std::cout << "Inserisci nome o cognome da cercare: ";
        std::cin >> search;

        bool finded = false;
        for (const auto &client : clients)
        {
            if (client.getName().find(search) != std::string::npos ||
                client.getSurname().find(search) != std::string::npos)
            {
                std::cout << client.toString() << std::endl;
                finded = true;
            }
        }

        if (!finded)
        {
            std::cout << "Nessun cliente trovato." << std::endl;
        }
    }

    void addInteraction()
    {
        listClients();
        if (clients.empty())
            return;

        int index;
        std::cout << "Inserisci il numero del cliente: ";
        std::cin >> index;

        if (index < 1 || index > static_cast<int>(clients.size()))
        {
            std::cout << "Indice non valido." << std::endl;
            return;
        }

        std::string type, data, description;
        std::cout << "Inserisci tipo di interazione: ";
        std::getline(std::cin >> std::ws, type);
        std::cout << "Inserisci data dell'interazione: ";
        std::getline(std::cin, data);
        std::cout << "Inserisci descrizione dell'interazione: ";
        std::getline(std::cin, description);

        clients[index - 1].addInteraction(Interaction(type, data, description));
        std::cout << "Interazione aggiunta con successo!" << std::endl;
        saveToFile();
    }

    void listInteractions()
    {
        listClients();
        if (clients.empty())
            return;

        int index;
        std::cout << "Inserisci il numero del cliente: ";
        std::cin >> index;

        if (index < 1 || index > static_cast<int>(clients.size()))
        {
            std::cout << "Indice non valido." << std::endl;
            return;
        }

        const Client &client = clients[index - 1];
        auto interactions = client.getInteractions();

        if (interactions.empty())
        {
            std::cout << "Nessuna interazione presente per questo cliente." << std::endl;
            return;
        }

        for (const auto &interaction : interactions)
        {
            std::cout << interaction.toString() << std::endl;
        }
    }

    void saveToFile()
    {
        std::ofstream file(FILE_PATH);
        if (!file)
        {
            std::cout << "Impossibile aprire il file per il salvataggio." << std::endl;
            return;
        }

        for (const auto &client : clients)
        {
            file << client.toCSV() << "\n";
            for (const auto &interaction : client.getInteractions())
            {
                file << client.getName() << "," << client.getSurname() << ","
                     << interaction.getTipo() << "," << interaction.getData() << ","
                     << interaction.getDescrizione() << "\n";
            }
        }

        file.close();
        std::cout << "Dati salvati con successo!" << std::endl;
    }

    void loadFromFile()
    {
        std::ifstream file(FILE_PATH);
        if (!file)
        {
            std::cout << "Nessun file di salvataggio trovato." << std::endl;
            return;
        }

        clients.clear();
        std::string row;
        while (std::getline(file, row))
        {
            std::istringstream ss(row);
            std::string name, surname, email, telephone, type, data, description;

            if (std::getline(ss, name, ',') &&
                std::getline(ss, surname, ',') &&
                std::getline(ss, email, ',') &&
                std::getline(ss, telephone))
            {
                if (std::getline(file, row))
                {
                    std::istringstream interaction_ss(row);

                    if (std::getline(interaction_ss, name, ',') &&
                        std::getline(interaction_ss, surname, ',') &&
                        std::getline(interaction_ss, type, ',') &&
                        std::getline(interaction_ss, data, ',') &&
                        std::getline(interaction_ss, description))
                    {

                        Client newClient(name, surname, email, telephone);
                        newClient.addInteraction(Interaction(type, data, description));
                        clients.push_back(newClient);
                    }
                }
            }
        }

        file.close();
        std::cout << "Dati caricati con successo!" << std::endl;
        listClients();
    }

    void menu()
    {
        int scelta;
        do
        {
            std::cout << "\n--- Sistema CRM ---\n";
            std::cout << "1. Aggiungi Cliente\n";
            std::cout << "2. Visualizza Clienti\n";
            std::cout << "3. Modifica Cliente\n";
            std::cout << "4. Elimina Cliente\n";
            std::cout << "5. Cerca Cliente\n";
            std::cout << "6. Aggiungi Interazione\n";
            std::cout << "7. Visualizza Interazioni\n";
            std::cout << "0. Esci\n";
            std::cout << "Scelta: ";
            std::cin >> scelta;

            // Pulisci il buffer di input
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            switch (scelta)
            {
            case 1:
                addClient();
                break;
            case 2:
                listClients();
                break;
            case 3:
                editClient();
                break;
            case 4:
                removeClient();
                break;
            case 5:
                searchClient();
                break;
            case 6:
                addInteraction();
                break;
            case 7:
                listInteractions();
                break;
            case 0:
                std::cout << "Uscita dal programma...\n";
                break;
            default:
                std::cout << "Scelta non valida.\n";
            }
        } while (scelta != 0);
    }
};

int main()
{
    CRM crm;
    crm.loadFromFile();
    crm.menu();
    return 0;
}