#include <string>
#include <vector>
#include "interaction.cpp"

class Client
{
private:
    std::string name;
    std::string surname;
    std::string email;
    std::string telephone;
    std::vector<Interaction> interactions;

public:
    Client(std::string _name, std::string _surname, std::string _email, std::string _telephone)
        : name(_name), surname(_surname), email(_email), telephone(_telephone) {}

    void addInteraction(const Interaction &interaction)
    {
        interactions.push_back(interaction);
    }

    // Getter e setter
    std::string getName() const { return name; }
    std::string getSurname() const { return surname; }
    std::string getEmail() const { return email; }
    std::string getTelephone() const { return telephone; }
    std::vector<Interaction> getInteractions() const { return interactions; }

    void setName(const std::string &_name) { name = _name; }
    void setSurname(const std::string &_surname) { surname = _surname; }
    void setEmail(const std::string &_email) { email = _email; }
    void setTelephone(const std::string &_telephone) { telephone = _telephone; }

    std::string toString() const
    {
        return "Nome: " + name + " " + surname + ", Email: " + email + ", Telefono: " + telephone;
    }

    std::string toCSV() const
    {
        std::string result = "";
        for (const Interaction &interaction : interactions)
        {
            result += name + "," + surname + "," + email + "," + telephone + "," + interaction.getType() + "," + interaction.getDate() + "," + interaction.getDescription() + "\n";
        }
        return result;
    }
};
