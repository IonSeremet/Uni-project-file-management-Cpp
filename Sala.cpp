
#include "Sala.h"

static inline void rtrim(std::string &s) {
    s.erase(find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

Sala ::Sala(string line) {

    istringstream f(line);
    string s;
    int counter_word = 0;
    while (getline(f, s, ',')) {

        switch (counter_word) {
            case 0:
                id = stoi(s);
                break;
            case 1:
                name = string (s);
//                    sala.name = malloc(strlen(s) + 1);
//                s.copy(name, sizeof s);
                break;
            case 2:
                capacity = stoi(s);
                break;
            case 3:
                isReserved = stoi(s);
                break;
            case 4:
                wifi = stoi(s);
                break;
            case 5:
                parking = stoi(s);
                break;
            case 6:
//                    sala.reservedDate = malloc(strlen(token) + 1);
                rtrim(s);
                reservedDate = string (s);
//                s.copy(reservedDate, sizeof s);
                break;
            default:
                break;

        }
        counter_word++;

    }
}
ostream & operator << (ostream &os, const Sala &s){
    os  << s.id << ' ' << s.name;
    return os;
}
bool operator !=(const Sala& s1,const Sala& s2){
    return s1.id != s2.id;
}
