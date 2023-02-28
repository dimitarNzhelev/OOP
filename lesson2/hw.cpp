#include <iostream>

using namespace std;

class Theatre
{
    // Add fields:
    // Number of total tickets to stop and one
    // Number of sold tickets
    int totalTickets;
    int soldTickets;

public:
    /**
     * @brief Construct a new empty Parking object - 0 tickets, 0 taken
     *
     */
    Theatre()
    {
        this->totalTickets = 0;
        this->soldTickets = 0;
    };

    /**
     * @brief Construct a new Parking object with total tickets and 0 takne
     *
     * @param totalTickets
     */
    Theatre(int totalTickets)
    {
        if (totalTickets >= 0)
        {
            this->totalTickets = totalTickets;
            this->soldTickets = 0;
        }
    };

    /**
     * @brief Construct a new Parking object with total tickets and taken tickets
     *
     * @param totaltickets
     * @param soldTickets
     */
    Theatre(int totalTickets, int soldTickets)
    {
        if (totalTickets >= 0 && totalTickets >= soldTickets)
        {
            this->totalTickets = totalTickets;
            this->soldTickets = soldTickets;
        }
    };

    /**
     * @brief Get the total free tickets in the parking lot
     *
     */
    int getTotalAvailableTickets() const
    {
        return this->totalTickets - this->soldTickets;
    };
};

int main()
{
    // TODO remove this comment to test the functionalities
    Theatre p1;
    cout << "There should be 0 tickets, and there are: " << p1.getTotalAvailableTickets() << endl;

    Theatre p2(10);
    cout << "There should be 10 tickets, and there are: " << p2.getTotalAvailableTickets() << endl;

    Theatre p3(10, 5);
    cout << "There should be 5 tickets, and there are: " << p3.getTotalAvailableTickets() << endl;
}