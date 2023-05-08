#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

class Dress
{
    // brand -string , color - string, bust - double,  waist - double, hips - double,

public:
    string brand, color;
    double bust, waist, hips;
    // TODO empty strings and zero values
    Dress() : brand(""), color(""), bust(0), waist(0), hips(0){};

    // Checks if the dress fits and there should be 5% margin
    bool doesFit(double bust, double hips, double waist)
    {
        if (this->bust >= bust && this->bust <= bust * 1.05 && this->hips >= hips && this->hips <= hips * 1.05 && this->waist >= waist && this->waist <= waist * 1.05)
        {
            return true;
        }
        return false;
    };

    friend ostream &operator<<(ostream &out, const Dress &d)
    {
        out << d.brand << endl;
        out << d.color << endl;
        out << d.bust << " " << d.waist << " " << d.hips << endl;
        return out;
    };

    friend istream &operator>>(istream &in, Dress &d)
    {
        string color, brand;
        double bust, waist, hips;
        getline(in >> ws, brand);
        getline(in >> ws, color);
        in >> bust >> waist >> hips;
        d.color = color;
        d.brand = brand;
        d.bust = bust;
        d.hips = hips;
        d.waist = waist;
        return in;
    };
};

int main()
{
    vector<Dress> dresses;
    Dress p;
    fstream file;
    file.open("dress.txt", ios::in);
    while (file >> p)
    {
        dresses.push_back(p);
    }
    file.close();
    double bust, waist, hips;
    cout << "Enter your measurements: "; // - bust, waist, hips
    // TODO load the user's measurements from the console
    cin >> bust;
    cin >> waist;
    cin >> hips;

    // TODO print the dresses that fit the user in the console, and save them in a file
    file.open("output.txt", ios::out);
    for (Dress d : dresses)
    {
        if (d.doesFit(bust, hips, waist))
        {
            cout << d;
            file << d;
        }
    }
    file.close();
    return 0;
}