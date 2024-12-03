#include <string>

class Interaction
{
private:
    std::string type;
    std::string date;
    std::string description;

public:
    Interaction(std::string _tipo, std::string _date, std::string _descrizione)
        : type(_tipo), date(_date), description(_descrizione) {}

    std::string getType() const { return type; }
    std::string getDate() const { return date; }
    std::string getDescription() const { return description; }

    std::string toString() const
    {
        return "Tipo: " + type + ", Data: " + date + ", Descrizione: " + description;
    }
};
