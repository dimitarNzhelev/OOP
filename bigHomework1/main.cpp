#include <iostream>
#include <cstring>
#include <ctime>
using namespace std;

// tova e enum za durjavi
enum Country
{
    BULGARIA,
    SERBIA,
    HUNGARY,
    ITALY,
    SPAIN,
    SWEDEN
};

// tova e enum za gradove
enum City
{
    SOFIA,
    BELGRADE,
    BUDAPEST,
    ROME,
    MADRID,
    STOCKHOLM,
    SUNNY_BEACH,
    PIROT,
    MILAN
};

// funkciq za proverqvane dali imaeto e validno qpredi da se sloji v toursit klasa
bool isValidNameGlobal(char const *name)
{
    if (isupper(*name))
    {

        for (size_t i = 1; i < strlen(name); i++)
        {
            if (!islower(name[i]))
            {
                cout << "The name is not formated correctly !" << endl;
                return false;
            }
        }
        return true;
    }
    else
    {
        cout << "The name is not formated correctly!" << endl;
        return false;
    }
}

// bazov klas ticket
class Ticket
{
    char *ticketNumber;
    float price;
    time_t date;
    char const *vehicleNumber;
    enum Country countryOfRegion;
    char *firstName;
    char *lastName;
    bool active;
    size_t id;

protected:
    static size_t numberOfTickets;

public:
    Ticket()
    {
        ticketNumber = strdup("0");
        price = 0.00;
        date = time(nullptr);
        vehicleNumber = strdup("a00");
        countryOfRegion = BULGARIA;
        firstName = strdup("None");
        lastName = strdup("None");
        active = true;
        numberOfTickets += 1;
        id = numberOfTickets;
    }

    virtual ~Ticket()
    {
        free(ticketNumber);
        free(firstName);
        free(lastName);
        numberOfTickets--;
    }

    Ticket(char *ticketNumber, float price, time_t date, const char *vehicleNumber, enum Country countryOfRegion, char *firstName, char *lastName)
        : date(date), countryOfRegion(countryOfRegion), vehicleNumber(strdup(vehicleNumber))
    {
        if (this->isValidName(firstName) && this->isValidName(lastName) && this->isValidVehicleNumber(this->vehicleNumber) && isValidPrice(price))
        {
            this->ticketNumber = strdup(ticketNumber);
            this->firstName = strdup(firstName);
            this->lastName = strdup(lastName);
            this->active = true;
            numberOfTickets += 1;
            this->price = price;
            this->id = numberOfTickets;
        }
    }

    Ticket(Ticket &other) : countryOfRegion(other.countryOfRegion), price(other.price)
    {
        this->ticketNumber = strdup(other.ticketNumber);
        this->firstName = strdup(other.firstName);
        this->lastName = strdup(other.lastName);
        this->vehicleNumber = strdup(other.vehicleNumber);
        numberOfTickets += 1;
        this->id = numberOfTickets;
    }

    virtual void updateTicket(char *ticketNumber, time_t date, const char *vehicleNumber, Country countryOfOrigin, const char *firstName, const char *lastName) = 0;

    bool isValidVehicleNumber(const char *vehicleNumber) const
    {
        if (strlen(vehicleNumber) <= 0)
            throw invalid_argument("Vehicle number must not be empty!");
        if (strlen(vehicleNumber) > 5)
            throw invalid_argument("Vehicle number must not be longer than 5 characters!");
        size_t letters = 0;
        size_t digits = 0;
        for (size_t i = 0; i < strlen(vehicleNumber); i++)
        {
            if (isalpha(vehicleNumber[i]))
                letters += 1;
            if (isdigit(vehicleNumber[i]))
                digits += 1;
        }
        if (letters >= 1 && digits >= 2)
            return true;
        else
            throw invalid_argument("Vehicle number must have at least two digits and one letter!");
        return false;
    }

    bool isValidName(char const *name) const
    {
        if (isupper(*name))
        {
            for (size_t i = 1; i < strlen(name); i++)
            {
                if (!islower(name[i]))
                {
                    throw invalid_argument("The name is not formated correctly !");
                    return false;
                }
            }
            return true;
        }
        else
        {
            throw invalid_argument("The name is not formated correctly!");
            return false;
        }
    }

    bool isValidPrice(float const price) const
    {
        if (price >= 0)
        {
            return true;
        }
        else
        {
            throw invalid_argument("Price must be higher than 0!");
            return false;
        }
    }

    virtual void printTicketInfo()
    {

        char buffer[80];

        strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M", gmtime(&this->date));
        string dateStr2(buffer);

        cout << "firstName: " << this->firstName << ", ";
        cout << "lastName: " << this->lastName << ", ";
        cout << "id: " << this->id << ", ";
        cout << "ticketNumber: " << this->ticketNumber << ", ";
        cout << "price: " << this->price << ", ";
        cout << "date: " << dateStr2 << ", ";
        cout << "vechicleNumber: " << this->vehicleNumber << ", ";

        switch (this->countryOfRegion)
        {
        case 0:
            cout << "countryOfRegion: "
                 << "BULGARIA"
                 << ", ";
            break;
        case 1:
            cout << "countryOfRegion: "
                 << "SERBIA"
                 << ", ";
            break;
        case 2:
            cout << "countryOfRegion: "
                 << "HUNGARY"
                 << ", ";
            break;
        case 3:
            cout << "countryOfRegion: "
                 << "ITALY"
                 << ", ";
            break;
        case 4:
            cout << "countryOfRegion: "
                 << "SPAIN"
                 << ", ";
            break;
        case 5:
            cout << "countryOfRegion: "
                 << "SWEDEN"
                 << ", ";
            break;
        default:
            break;
        }

        cout << "active: " << this->active << ", ";
    }

    void cancelTrip()
    {
        if (this->active != false)
        {
            this->active = false;
        }
        else
        {
            throw invalid_argument("This ticket is already not active.");
        }
    }

    char *getTicketNumber() const
    {
        return ticketNumber;
    }

    size_t getId() const
    {
        return this->id;
    }

    float getPrice() const
    {
        return price;
    }

    time_t getDate() const
    {
        return date;
    }

    char const *getVehicleNumber() const
    {
        return vehicleNumber;
    }

    enum Country getCountryOfRegion() const
    {
        return countryOfRegion;
    }

    char *getFirstName() const
    {
        return firstName;
    }

    char *getLastName() const
    {
        return lastName;
    }

    bool isActive() const
    {
        return active;
    }

    void setTicketNumber(char *ticketNumber)
    {
        this->ticketNumber = strdup(ticketNumber);
    }

    void setPrice(float price)
    {
        this->price = price;
    }

    void setDate(time_t date)
    {
        this->date = date;
    }

    void setVehicleNumber(char const *vehicleNumber)
    {
        this->vehicleNumber = strdup(vehicleNumber);
    }

    void setCountryOfRegion(enum Country countryOfRegion)
    {
        this->countryOfRegion = countryOfRegion;
    }

    void setFirstName(const char *firstName)
    {
        this->firstName = strdup(firstName);
    }

    void setLastName(const char *lastName)
    {
        this->lastName = strdup(lastName);
    }

    void setActive(bool active)
    {
        this->active = active;
    }
};

size_t Ticket::numberOfTickets = 0;

class FlightTicket : public Ticket
{
    enum Country destinationCountry;
    char *travelingClass; // Business, Economy, FirstClass

public:
    void updateTicket(char *ticketNumber, time_t date, const char *vehicleNumber, Country countryOfOrigin, const char *firstName, const char *lastName)
    {
        if (this->isValidName(firstName) && this->isValidName(lastName) && this->isValidVehicleNumber(vehicleNumber))
        {
            this->setTicketNumber(ticketNumber);
            this->setDate(date);
            this->setVehicleNumber(vehicleNumber);
            this->setCountryOfRegion(countryOfOrigin);
            this->setFirstName(firstName);
            this->setLastName(lastName);
        }
    }

    FlightTicket()
    {

        this->destinationCountry = BULGARIA;
        this->travelingClass = strdup("Business");
    };

    ~FlightTicket()
    {
        Ticket::~Ticket();
        delete[] travelingClass;
    }

    FlightTicket(char *ticketNumber, float price, time_t date, const char *vehicleNumber, enum Country countryOfRegion, char *firstName, char *lastName, enum Country destinationCountry, char *travelingClass)
        : Ticket(ticketNumber, price, date, vehicleNumber, countryOfRegion, firstName, lastName)
    {
        if (strcmp(travelingClass, "Business") || strcmp(travelingClass, "Economy") || strcmp(travelingClass, "FirstClass"))
        {
            this->destinationCountry = destinationCountry;
            this->travelingClass = strdup(travelingClass);
        }
        else
        {
            throw invalid_argument("TravelingClass is not valid");
        }
    };

    FlightTicket(FlightTicket &other) : Ticket(other)
    {
        if (this != &other)
        {
            this->destinationCountry = other.destinationCountry;
            this->travelingClass = other.travelingClass;
        }
    };

    FlightTicket &operator=(const FlightTicket &other)
    {
        if (this != &other)
        {
            this->setTicketNumber(other.getTicketNumber());
            this->setPrice(other.getPrice());
            this->setDate(other.getDate());
            this->setVehicleNumber(other.getVehicleNumber());
            this->setCountryOfRegion(other.getCountryOfRegion());
            this->setFirstName(other.getFirstName());
            this->setLastName(other.getLastName());
            this->destinationCountry = other.destinationCountry;
            this->travelingClass = other.travelingClass;
        }
        return *this;
    }

    void printTicketInfo()
    {
        Ticket::printTicketInfo();
        switch (this->destinationCountry)
        {
        case 0:
            cout << "DestinationCountry: "
                 << "BULGARIA"
                 << ", ";
            break;
        case 1:
            cout << "DestinationCountry: "
                 << "SERBIA"
                 << ", ";
            break;
        case 2:
            cout << "DestinationCountry: "
                 << "HUNGARY"
                 << ", ";
            break;
        case 3:
            cout << "DestinationCountry: "
                 << "ITALY"
                 << ", ";
            break;
        case 4:
            cout << "DestinationCountry: "
                 << "SPAIN"
                 << ", ";
            break;
        case 5:
            cout << "DestinationCountry: "
                 << "SWEDEN"
                 << ", ";
            break;
        default:
            break;
        }
        cout << "Traveling Class: " << this->travelingClass << endl;
    }
};

class TrainTicket : public Ticket
{
    enum City from;
    enum City to;
    char *travelingClass; // Business, Economy, FirstClass

public:
    void updateTicket(char *ticketNumber, time_t date, const char *vehicleNumber, Country countryOfOrigin, const char *firstName, const char *lastName)
    {
        if (this->isValidName(firstName) && this->isValidName(lastName) && this->isValidVehicleNumber(vehicleNumber))
        {
            this->setTicketNumber(ticketNumber);
            this->setDate(date);
            this->setVehicleNumber(vehicleNumber);
            this->setCountryOfRegion(countryOfOrigin);
            this->setFirstName(firstName);
            this->setLastName(lastName);
        }
    }

    TrainTicket()
    {
        this->from = SOFIA;
        this->to = MILAN;
        this->travelingClass = strdup("Business");
    }

    ~TrainTicket()
    {

        delete[] this->travelingClass;
    }

    TrainTicket(char *ticketNumber, float price, time_t date, const char *vehicleNumber, enum Country countryOfRegion, char *firstName, char *lastName, enum City from, enum City to, char *travelingClass)
        : Ticket(ticketNumber, price, date, vehicleNumber, countryOfRegion, firstName, lastName), from(from), to(to)
    {
        if (strcmp(travelingClass, "Business") || strcmp(travelingClass, "Economy") || strcmp(travelingClass, "FirstClass"))
        {
            this->travelingClass = strdup(travelingClass);
        }
        else
            throw invalid_argument("TravelingClass is not valid!");
    }

    TrainTicket(TrainTicket &other) : Ticket(other.getTicketNumber(), other.getPrice(), other.getDate(), other.getVehicleNumber(), other.getCountryOfRegion(), other.getFirstName(), other.getLastName())
    {
        if (this != &other)
        {
            this->from = other.from;
            this->to = other.to;
            this->travelingClass = strdup(other.travelingClass);
        }
    }

    TrainTicket &operator=(const TrainTicket &other)
    {
        if (this != &other)
        {
            this->setTicketNumber(other.getTicketNumber());
            this->setPrice(other.getPrice());
            this->setDate(other.getDate());
            this->setVehicleNumber(other.getVehicleNumber());
            this->setCountryOfRegion(other.getCountryOfRegion());
            this->setFirstName(other.getFirstName());
            this->setLastName(other.getLastName());
            this->from = other.from;
            this->to = other.to;
            this->travelingClass = strdup(other.travelingClass);
        }
        return *this;
    }

    void printTicketInfo()
    {
        Ticket::printTicketInfo();
        switch (this->from)
        {
        case 0:
            cout << "from: "
                 << "SOFIA"
                 << ", ";
            break;
        case 1:
            cout << "from: "
                 << "BELGRADE"
                 << ", ";
            break;
        case 2:
            cout << "from: "
                 << "BUDAPEST"
                 << ", ";
            break;
        case 3:
            cout << "from: "
                 << "ROME"
                 << ", ";
            break;
        case 4:
            cout << "from: "
                 << "MADRID"
                 << ", ";
            break;
        case 5:
            cout << "from: "
                 << "STOCKHOLM"
                 << ", ";
            break;
        case 6:
            cout << "from: "
                 << "SUNNY_BEACH"
                 << ", ";
            break;
        case 7:
            cout << "from: "
                 << "PIROT"
                 << ", ";
            break;
        case 8:
            cout << "from: "
                 << "MILAN"
                 << ", ";
            break;
        default:
            break;
        }

        switch (this->to)
        {
        case 0:
            cout << "to: "
                 << "SOFIA"
                 << ", ";
            break;
        case 1:
            cout << "to: "
                 << "BELGRADE"
                 << ", ";
            break;
        case 2:
            cout << "to: "
                 << "BUDAPEST"
                 << ", ";
            break;
        case 3:
            cout << "to: "
                 << "ROME"
                 << ", ";
            break;
        case 4:
            cout << "to: "
                 << "MADRID"
                 << ", ";
            break;
        case 5:
            cout << "to: "
                 << "STOCKHOLM"
                 << ", ";
            break;
        case 6:
            cout << "to: "
                 << "SUNNY_BEACH"
                 << ", ";
            break;
        case 7:
            cout << "to: "
                 << "PIROT"
                 << ", ";
            break;
        case 8:
            cout << "to: "
                 << "MILAN"
                 << ", ";
            break;
        default:
            break;
        }
        cout << "Traveling Class: " << this->travelingClass << endl;
    }
};

class BusTicket : public Ticket
{
    enum City from;
    enum City to;

public:
    void updateTicket(char *ticketNumber, time_t date, const char *vehicleNumber, Country countryOfOrigin, const char *firstName, const char *lastName)
    {
        if (this->isValidName(firstName) && this->isValidName(lastName) && this->isValidVehicleNumber(vehicleNumber))
        {
            this->setTicketNumber(ticketNumber);
            this->setDate(date);
            this->setVehicleNumber(vehicleNumber);
            this->setCountryOfRegion(countryOfOrigin);
            this->setFirstName(firstName);
            this->setLastName(lastName);
        }
    }

    BusTicket()
    {
        this->from = MADRID;
        this->to = ROME;
    }

    BusTicket(char *ticketNumber, float price, time_t date, const char *vehicleNumber, enum Country countryOfRegion, char *firstName, char *lastName, enum City from, enum City to)
        : Ticket(ticketNumber, price, date, vehicleNumber, countryOfRegion, firstName, lastName),
          from(from), to(to)
    {
    }

    BusTicket(BusTicket &other) : Ticket(other.getTicketNumber(), other.getPrice(), other.getDate(), other.getVehicleNumber(), other.getCountryOfRegion(), other.getFirstName(), other.getLastName())
    {
        if (this != &other)
        {
            this->from = other.from;
            this->to = other.to;
        }
    }

    BusTicket &operator=(const BusTicket &other)
    {
        if (this != &other)
        {
            this->setTicketNumber(other.getTicketNumber());
            this->setPrice(other.getPrice());
            this->setDate(other.getDate());
            this->setVehicleNumber(other.getVehicleNumber());
            this->setCountryOfRegion(other.getCountryOfRegion());
            this->setFirstName(other.getFirstName());
            this->setLastName(other.getLastName());
            this->from = other.from;
            this->to = other.to;
        }
        return *this;
    }

    void printTicketInfo()
    {
        Ticket::printTicketInfo();

        switch (this->from)
        {
        case 0:
            cout << "from: "
                 << "SOFIA"
                 << ", ";
            break;
        case 1:
            cout << "from: "
                 << "BELGRADE"
                 << ", ";
            break;
        case 2:
            cout << "from: "
                 << "BUDAPEST"
                 << ", ";
            break;
        case 3:
            cout << "from: "
                 << "ROME"
                 << ", ";
            break;
        case 4:
            cout << "from: "
                 << "MADRID"
                 << ", ";
            break;
        case 5:
            cout << "from: "
                 << "STOCKHOLM"
                 << ", ";
            break;
        case 6:
            cout << "from: "
                 << "SUNNY_BEACH"
                 << ", ";
            break;
        case 7:
            cout << "from: "
                 << "PIROT"
                 << ", ";
            break;
        case 8:
            cout << "from: "
                 << "MILAN"
                 << ", ";
            break;
        default:
            break;
        }

        switch (this->to)
        {
        case 0:
            cout << "to: "
                 << "SOFIA" << endl;
            break;
        case 1:
            cout << "to: "
                 << "BELGRADE" << endl;
            break;
        case 2:
            cout << "to: "
                 << "BUDAPEST" << endl;
            break;
        case 3:
            cout << "to: "
                 << "ROME" << endl;
            break;
        case 4:
            cout << "to: "
                 << "MADRID" << endl;
            break;
        case 5:
            cout << "to: "
                 << "STOCKHOLM" << endl;
            break;
        case 6:
            cout << "to: "
                 << "SUNNY_BEACH" << endl;
            break;
        case 7:
            cout << "to: "
                 << "PIROT" << endl;
            break;
        case 8:
            cout << "to: "
                 << "MILAN" << endl;
            break;
        default:
            break;
        }
    }
};

class Tourist
{
    char *firstName;
    char *lastName;
    float amount;
    size_t size;
    size_t capacity;
    Ticket **tripHistory;

public:
    Tourist(char *firstName, char *lastName, float amount)
    {

        this->firstName = strdup(firstName);
        this->lastName = strdup(lastName);
        this->amount = amount;
        this->size = 0;
        this->capacity = 2;
        this->tripHistory = new Ticket *[capacity];
    }

    Tourist(Tourist &other)
    {
        this->firstName = strdup(other.firstName);
        this->lastName = strdup(other.lastName);
        this->amount = other.amount;
        this->capacity = other.capacity;
        this->size = other.size;
    }

    Tourist &operator=(const Tourist &other)
    {
        if (this != &other)
        {
            this->size = other.size;
            this->capacity = other.capacity;
            free(this->firstName);
            free(this->lastName);
            this->firstName = strdup(other.firstName);
            this->lastName = strdup(other.lastName);
            this->amount = other.amount;
            delete[] this->tripHistory;
            this->tripHistory = new Ticket *[other.size];
            for (int i = 0; i < other.size; i++)
            {
                this->tripHistory[i] = other.tripHistory[i];
            }
        }
        return *this;
    }

    bool isValidPrice(float const price)
    {
        if (price >= 0)
        {
            return true;
        }
        else
        {
            cout << "Price must be higher than 0!" << endl;
            return false;
        }
    }

    bool isValidVehicleNumber(const char *vehicleNumber)
    {
        if (strlen(vehicleNumber) <= 0)
        {
            cout << "Vehicle number must not be empty!" << endl;
            return false;
        }
        if (strlen(vehicleNumber) > 5)
        {
            cout << "Vehicle number must not be longer than 5 characters!" << endl;
            return false;
        }
        size_t letters = 0;
        size_t digits = 0;
        for (size_t i = 0; i < strlen(vehicleNumber); i++)
        {
            if (isalpha(vehicleNumber[i]))
                letters += 1;
            if (isdigit(vehicleNumber[i]))
                digits += 1;
        }
        if (letters >= 1 && digits >= 2)
            return true;
        else
            cout << "Vehicle number must have at least two digits and one letter!" << endl;
        return false;
    }

    void getTicketInfo(char *ticketNumber, char *vehicleNumber, float *price, time_t *date, Country *countryOfOrigin)
    {
        char input[256];
        string dateStr;

        cout << endl;
        cout << "Enter ticket number: ";
        cin >> ticketNumber;

        do
        {
            cout << "Enter vehicle number: ";
            cin >> vehicleNumber;
        } while (!isValidVehicleNumber(vehicleNumber));

        do
        {
            cout << "Enter price: ";
            cin >> *price;
        } while (!isValidPrice(*price));
        cin.ignore();
        cout << "Enter date (format: 01-01-2023 19:12): ";
        getline(cin, dateStr);

        struct tm tm = {};
        strptime(dateStr.c_str(), "%d-%m-%Y %H:%M", &tm);
        *date = timegm(&tm);

        while (true)
        {
            cout << "Enter country of origin - one of BULGARIA, SERBIA, HUNGARY, ITALY, SPAIN, SWEDEN: ";
            cin >> input;

            if (strcmp(input, "BULGARIA") == 0)
            {
                *countryOfOrigin = BULGARIA;
                break;
            }
            else if (strcmp(input, "SERBIA") == 0)
            {
                *countryOfOrigin = SERBIA;
                break;
            }
            else if (strcmp(input, "HUNGARY") == 0)
            {
                *countryOfOrigin = HUNGARY;
                break;
            }
            else if (strcmp(input, "ITALY") == 0)
            {
                *countryOfOrigin = ITALY;
                break;
            }
            else if (strcmp(input, "SPAIN") == 0)
            {
                *countryOfOrigin = SPAIN;
                break;
            }
            else if (strcmp(input, "SWEDEN") == 0)
            {
                *countryOfOrigin = SWEDEN;
                break;
            }
            else
            {
                cout << "Invalid country entered." << endl;
            }
        }
    }

    void useTheTrain()
    {
        char travelingClass[256], input[256], ticketNumber[256], vehicleNumber[256];
        float price;
        Country countryOfOrigin;
        City from, to;
        time_t date;

        getTicketInfo(ticketNumber, vehicleNumber, &price, &date, &countryOfOrigin);

        while (true)
        {
            cout << "Enter from city - one of SOFIA, BELGRADE, BUDAPEST, ROME, MADRID, STOCKHOLM, SUNNY BEACH, PIROT, MILAN: ";
            cin >> input;

            if (strcmp(input, "SOFIA") == 0)
            {
                from = SOFIA;
                break;
            }
            else if (strcmp(input, "BELGRADE") == 0)
            {
                from = BELGRADE;
                break;
            }
            else if (strcmp(input, "BUDAPEST") == 0)
            {
                from = BUDAPEST;
                break;
            }
            else if (strcmp(input, "ROME") == 0)
            {
                from = ROME;
                break;
            }
            else if (strcmp(input, "MADRID") == 0)
            {
                from = MADRID;
                break;
            }
            else if (strcmp(input, "STOCKHOLM") == 0)
            {
                from = STOCKHOLM;
                break;
            }
            else if (strcmp(input, "SUNNY_BEACH") == 0)
            {
                from = SUNNY_BEACH;
                break;
            }
            else if (strcmp(input, "PIROT") == 0)
            {
                from = PIROT;
                break;
            }
            else if (strcmp(input, "MILAN") == 0)
            {
                from = MILAN;
                break;
            }
            else
            {
                cout << "Invalid city entered." << endl;
            }
        }

        while (true)
        {
            cout << "Enter to city - one of SOFIA, BELGRADE, BUDAPEST, ROME, MADRID, STOCKHOLM, SUNNY BEACH, PIROT, MILAN: ";
            cin >> input;

            if (strcmp(input, "SOFIA") == 0)
            {
                to = SOFIA;
                break;
            }
            else if (strcmp(input, "BELGRADE") == 0)
            {
                to = BELGRADE;
                break;
            }
            else if (strcmp(input, "BUDAPEST") == 0)
            {
                to = BUDAPEST;
                break;
            }
            else if (strcmp(input, "ROME") == 0)
            {
                to = ROME;
                break;
            }
            else if (strcmp(input, "MADRID") == 0)
            {
                to = MADRID;
                break;
            }
            else if (strcmp(input, "STOCKHOLM") == 0)
            {
                to = STOCKHOLM;
                break;
            }
            else if (strcmp(input, "SUNNY_BEACH") == 0)
            {
                to = SUNNY_BEACH;
                break;
            }
            else if (strcmp(input, "PIROT") == 0)
            {
                to = PIROT;
                break;
            }
            else if (strcmp(input, "MILAN") == 0)
            {
                to = MILAN;
                break;
            }
            else
            {
                cout << "Invalid city entered." << endl;
            }
        }

        while (true)
        {
            cout << "Enter traveling class - one of Business, Economy, FirstClass: ";
            cin >> travelingClass;
            if (strcmp(travelingClass, "Business") == 0 || strcmp(travelingClass, "Economy") == 0 || strcmp(travelingClass, "FirstClass") == 0)
            {
                break;
            }
            cout << "Invalid travel class entered." << endl;
        }

        if (size == capacity)
        {
            this->resize();
        }

        if (this->amount - price >= 0)
        {
            tripHistory[size++] = new TrainTicket(ticketNumber, price, date, vehicleNumber, countryOfOrigin, firstName, lastName, from, to, travelingClass);
            this->amount = this->amount - price;
        }
        else
        {
            cout << "Not enough balance to buy this ticket" << endl;
        }
    }

    void useTheBus()
    {
        char ticketNumber[256], vehicleNumber[256], input[256];
        float price;
        time_t date;
        Country countryOfOrigin;
        City from, to;

        getTicketInfo(ticketNumber, vehicleNumber, &price, &date, &countryOfOrigin);

        while (true)
        {
            cout << "Enter from city - one of SOFIA, BELGRADE, BUDAPEST, ROME, MADRID, STOCKHOLM, SUNNY BEACH, PIROT, MILAN: ";
            cin >> input;

            if (strcmp(input, "SOFIA") == 0)
            {
                from = SOFIA;
                break;
            }
            else if (strcmp(input, "BELGRADE") == 0)
            {
                from = BELGRADE;
                break;
            }
            else if (strcmp(input, "BUDAPEST") == 0)
            {
                from = BUDAPEST;
                break;
            }
            else if (strcmp(input, "ROME") == 0)
            {
                from = ROME;
                break;
            }
            else if (strcmp(input, "MADRID") == 0)
            {
                from = MADRID;
                break;
            }
            else if (strcmp(input, "STOCKHOLM") == 0)
            {
                from = STOCKHOLM;
                break;
            }
            else if (strcmp(input, "SUNNY_BEACH") == 0)
            {
                from = SUNNY_BEACH;
                break;
            }
            else if (strcmp(input, "PIROT") == 0)
            {
                from = PIROT;
                break;
            }
            else if (strcmp(input, "MILAN") == 0)
            {
                from = MILAN;
                break;
            }
            else
            {
                cout << "Invalid city entered." << endl;
            }
        }

        while (true)
        {
            cout << "Enter to city - one of SOFIA, BELGRADE, BUDAPEST, ROME, MADRID, STOCKHOLM, SUNNY BEACH, PIROT, MILAN: ";
            cin >> input;

            if (strcmp(input, "SOFIA") == 0)
            {
                to = SOFIA;
                break;
            }
            else if (strcmp(input, "BELGRADE") == 0)
            {
                to = BELGRADE;
                break;
            }
            else if (strcmp(input, "BUDAPEST") == 0)
            {
                to = BUDAPEST;
                break;
            }
            else if (strcmp(input, "ROME") == 0)
            {
                to = ROME;
                break;
            }
            else if (strcmp(input, "MADRID") == 0)
            {
                to = MADRID;
                break;
            }
            else if (strcmp(input, "STOCKHOLM") == 0)
            {
                to = STOCKHOLM;
                break;
            }
            else if (strcmp(input, "SUNNY_BEACH") == 0)
            {
                to = SUNNY_BEACH;
                break;
            }
            else if (strcmp(input, "PIROT") == 0)
            {
                to = PIROT;
                break;
            }
            else if (strcmp(input, "MILAN") == 0)
            {
                to = MILAN;
                break;
            }
            else
            {
                cout << "Invalid city entered." << endl;
            }
        }

        if (size == capacity)
        {
            this->resize();
        }

        if (this->amount - price >= 0)
        {
            tripHistory[size++] = new BusTicket(ticketNumber, price, date, vehicleNumber, countryOfOrigin, firstName, lastName, from, to);
            this->amount = this->amount - price;
        }
        else
        {
            cout << "Not enough balance available to buy this ticket." << endl;
        }
    }

    void bookAFlight()
    {
        char ticketNumber[256], vehicleNumber[256], travelingClass[256], inputCountry[256];
        float price;
        time_t date;
        Country countryOfOrigin, destinationCountry;

        getTicketInfo(ticketNumber, vehicleNumber, &price, &date, &countryOfOrigin);

        while (true)
        {
            cout << "Enter destination country - one of BULGARIA, SERBIA, HUNGARY, ITALY, SPAIN, SWEDEN: ";
            cin >> inputCountry;

            if (strcmp(inputCountry, "BULGARIA") == 0)
            {
                destinationCountry = BULGARIA;
                break;
            }
            else if (strcmp(inputCountry, "SERBIA") == 0)
            {
                destinationCountry = SERBIA;
                break;
            }
            else if (strcmp(inputCountry, "HUNGARY") == 0)
            {
                destinationCountry = HUNGARY;
                break;
            }
            else if (strcmp(inputCountry, "ITALY") == 0)
            {
                destinationCountry = ITALY;
                break;
            }
            else if (strcmp(inputCountry, "SPAIN") == 0)
            {
                destinationCountry = SPAIN;
                break;
            }
            else if (strcmp(inputCountry, "SWEDEN") == 0)
            {
                destinationCountry = SWEDEN;
                break;
            }
            else
            {
                cout << "Invalid country entered." << endl;
            }
        }

        while (true)
        {
            cout << "Enter traveling class - one of Business, Economy, FirstClass: ";
            cin >> travelingClass;
            if (strcmp(travelingClass, "Business") == 0 || strcmp(travelingClass, "Economy") == 0 || strcmp(travelingClass, "FirstClass") == 0)
            {
                break;
            }
            cout << "Invalid travel class entered." << endl;
        }

        if (size == capacity)
        {
            this->resize();
        }

        if (this->amount - price >= 0)
        {
            tripHistory[size++] = new FlightTicket(ticketNumber, price, date, vehicleNumber, countryOfOrigin, this->firstName, this->lastName, destinationCountry, travelingClass);
            this->amount = this->amount - price;
        }
        else
        {
            cout << "Not enough balance to buy this ticket" << endl;
        }
    }

    void resize()
    {
        this->capacity = capacity * 2;

        Ticket **clone = new Ticket *[capacity];
        for (int i = 0; i < this->size; i++)
        {
            clone[i] = this->tripHistory[i];
        }

        delete[] this->tripHistory;
        this->tripHistory = clone;
    };

    void updateTicketByID()
    {
        char ticketNumber[256], vehicleNumber[256];
        Country countryOfOrigin;
        time_t date;
        size_t ticketid;
        float price;

        cout << endl
             << "5.Update ticket:" << endl
             << "Enter ticket id: ";
        cin >> ticketid;

        this->getTicketInfo(ticketNumber, vehicleNumber, &price, &date, &countryOfOrigin);
        for (int i = 0; i < size; i++)
        {
            if (this->tripHistory[i]->getId() == ticketid)
            {
                this->tripHistory[i]->updateTicket(ticketNumber, date, vehicleNumber, countryOfOrigin, this->firstName, this->lastName);
            }
        }
    }

    void cancelTicketByID()
    {
        size_t ticketid;
        cout << endl
             << "6.Cancel ticket:" << endl
             << "Enter ticket id: ";

        cin >> ticketid;
        for (int i = 0; i < size; i++)
        {
            if (this->tripHistory[i]->getId() == ticketid)
            {
                this->tripHistory[i]->cancelTrip();
            }
        }
    }

    void printTickets()
    {
        cout << "Tickets: " << endl;
        for (int i = 0; i < size; i++)
        {
            this->tripHistory[i]->printTicketInfo();
        }
    }
};

int main()
{
    char firstname[256], lastname[256];
    size_t input;
    bool state = true;
    float budget;

    do
    {
        cout << "Enter firstName: ";
        cin >> firstname;
    } while (!isValidNameGlobal(firstname));

    do
    {
        cout << "Enter lastname: ";
        cin >> lastname;
    } while (!isValidNameGlobal(lastname));

    do
    {
        cout << "Enter budget:";
        cin >> budget;
    } while (budget < 0);

    Tourist t = Tourist(firstname, lastname, budget);

    while (state)
    {
        cout << endl;
        cout << "Please choose one of the following:" << endl
             << "1.Use Plane" << endl
             << "2.Use Bus" << endl
             << "3.Use Train" << endl
             << "4.List tickets history" << endl
             << "5.Update ticket by ID"
             << endl
             << "6.Cancel ticket by ID" << endl
             << "7.Quit" << endl;
        cin >> input;

        switch (input)
        {
        case 1:
            t.bookAFlight();
            break;
        case 2:
            t.useTheBus();
            break;
        case 3:
            t.useTheTrain();
            break;
        case 4:
            t.printTickets();
            break;
        case 5:
            t.updateTicketByID();
            break;
        case 6:
            t.cancelTicketByID();
            break;
        case 7:
            state = false;
            break;
        }
    }

    return 0;
}