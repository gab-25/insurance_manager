#include <string>

class Interaction
{
private:
    std::string type;
    std::string data;
    std::string description;

public:
    Interaction(std::string _tipo, std::string _data, std::string _descrizione)
        : type(_tipo), data(_data), description(_descrizione) {}

    std::string getTipo() const { return type; }
    std::string getData() const { return data; }
    std::string getDescrizione() const { return description; }

    std::string toString() const
    {
        return "Tipo: " + type + ", Data: " + data + ", Descrizione: " + description;
    }
};
