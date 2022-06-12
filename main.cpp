#include "Sala.h"
#include <iostream>
#include <string>
//#include <list>
//#include <iterator>
//#include <set>
#include "vector"
#include <algorithm>
#include <ctime>

#define RED     "\033[31m"
#define RESET   "\033[0m"
#define GREEN   "\033[32m"

using namespace std;

static inline void rtrim(string &s) {
    s.erase(find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !isspace(ch);
    }).base(), s.end());
}

bool dateInTheFuture(string date ) {
    string strday,strmonth,stryear;
    strday += date[0];
    strday +=date[1];
    strmonth += date[3];
    strmonth +=date[4];
    stryear += date[6];
    stryear +=date[7];
    stryear += date[8];
    stryear +=date[9];
    int dd,mm,yy;
    dd = stoi(strday);
    mm = stoi(strmonth);
    yy = stoi(stryear);

    time_t timeNow,newTime;
    time(&timeNow);
    time(&newTime);
    tm* newTimeTm = localtime(&newTime);
    newTimeTm->tm_mday = dd;
    newTimeTm->tm_mon = mm - 1;
    newTimeTm->tm_year = yy - 1900;
    newTime = mktime(newTimeTm);
    if (difftime(timeNow, newTime) < 0) {
        return true;
    } else {
        cout << RED << "Nu poti alege o data in trecut\n" << RESET << endl;
        return false;
    }
}

vector<Sala> read_file() {
    ifstream myfile("sali.csv");
    vector<Sala> sali;

    int counter_line = 0;
    while (!myfile.eof()) {
        if (counter_line == 0) {
            string temp;
            getline(myfile,temp);
            counter_line++;
            continue;
        }
        string line;
        getline(myfile,line);
        Sala sala(line);
        sali.push_back (sala);
        counter_line++;
    }
    myfile.close();
    return sali;
}

void write_file(vector<Sala> sali){
    ofstream myfile("sali.csv");
    string strTemp;
    strTemp+="id,name,capacity,isReserved,wifi,parking,reservedDate\n";
    int mar = sali.size();

    for(auto i : sali){
        strTemp+= to_string(i.Get_Id());
        strTemp+=",";
        strTemp+=i.Get_Name();
        strTemp+=",";
        strTemp+= to_string(i.Get_capacity());
        strTemp+=",";
        strTemp+= to_string(i.Get_isReserved());
        strTemp+=",";
        strTemp+= to_string(i.Get_Wifi());
        strTemp+=",";
        strTemp+= to_string(i.Get_Parking());
        strTemp+=",";
        strTemp+= i.Get_reservedDate();

        // stergem ultimul "new line" din strTemp pentru a nu pune o linie in plus in file
        if (i != sali[mar-1]){
            strTemp+="\n";
        }
    }
    myfile << strTemp;
    myfile.close();
}

bool Date_check(string date){
    string strday,strmonth,stryear;
    strday += date[0];
    strday +=date[1];
    strmonth += date[3];
    strmonth +=date[4];
    stryear += date[6];
    stryear +=date[7];
    stryear += date[8];
    stryear +=date[9];

    int day,month,year;
    day = stoi(strday);
    month = stoi(strmonth);
    year = stoi(stryear);

    if(year >=2022)
    {
        if ((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) &&
            day > 0 && day <= 31)
        return true;
        else if (month == 4 || month == 6 || month == 9 || month == 11 && day > 0 && day <= 30)
            return true;
        else if (month == 2) {
            if ((year % 400 == 0 || (year % 100 != 0 && year % 4 == 0)) && day > 0 && day <= 29)
            return true;
            else if (day > 0 && day <= 28)
                return true;
            else
                return false;
        } else
            return false;
    }
    else
        return false;

}

int main() {
    string fileName = "sali.csv";

    printf("%s", "Salut :D\n");
    while (true) {
        cout << "1.Arata salile valabile" << endl
        << "2.Incepe sa alegi o sala" << endl
        << "3.Vezi sala rezervata" << endl
        << "4.Anuleaza sala rezervata" << endl
        << "5.Iesire" << endl
        << "Ce vrei sa alegi? : " << endl;

        int alegere;
        cin >> alegere;
        cout << endl;

        vector <Sala> sali_disponibile;

        if (alegere == 1){
            vector <Sala> sali = read_file();
            cout << "Iata salile valabile:" << endl;

            //adaugam salile disponibile intr-un vector nou
            for (auto & i : sali) {
                if(i.Get_isReserved() == 0){
                    sali_disponibile.push_back(i);
                }
            }
            // cu ajutorul supraincarcarii operatorului "<<" facem output la salile disponibile
            for(const auto& i : sali_disponibile){
                cout << i << endl;
            }
            cout << endl << endl;
        }
        if (alegere == 2) {
            vector <Sala> sali = read_file();
            string varianta_full ;
            cout <<"\nCe varianta alegi? (Introdu numarul corespunzator):";
            int varianta_aleasa;
            cin >> varianta_aleasa;
            varianta_aleasa--;
            if(sali[varianta_aleasa].Get_isReserved() == 0) {


                cout << "\nCati invitati vei avea?(maxim 150):";
                int optiunea_invitati;
                cin >> optiunea_invitati;
                if (optiunea_invitati > 0 && optiunea_invitati <= 150) {

                        cout << "Sa fie cu wifi?\n Introduceti 1 pentru DA\nSi 0 pentru NU:\n";
                        int optiunea_wifi;
                        cin >> optiunea_wifi;
                        if (optiunea_wifi == 0 || optiunea_wifi == 1) {

                            cout << "Sa fie cu parcare?\n Introduceti 1 pentru DA\nSi 0 pentru NU:\n";
                            int optiunea_parking;
                            cin >> optiunea_parking;
                            if(optiunea_parking == 0 || optiunea_parking == 1) {

                                cout << "\nPe ce data sa fie rezervarea? (in formatul dd/mm/yyyy)";
                                string optiunea_reservedDate;
                                cin >> optiunea_reservedDate;
                                if (optiunea_reservedDate.length() == 10) {
                                    if (Date_check(optiunea_reservedDate)) {
                                        if(dateInTheFuture(optiunea_reservedDate)) {

//                                            vector<Sala> sali = read_file();

                                            sali[varianta_aleasa].Set_Capacity(optiunea_invitati);
                                            sali[varianta_aleasa].Set_Wifi(optiunea_wifi);
                                            sali[varianta_aleasa].Set_Parking(optiunea_parking);
                                            sali[varianta_aleasa].Set_isReserved(1);
                                            sali[varianta_aleasa].Set_ReservedDate(optiunea_reservedDate);
                                            write_file(sali);

                                            cout << GREEN << "Sala a fost rezervata!\n" << RESET << endl;
                                        }
                                    } else {
                                        cout << RED << "Data introdusa nu e corecta\n" << RESET << endl;
                                    }
                                } else {
                                    cout << RED << "Data introdusa nu e corecta\n" << RESET << endl;
                                }
                            }else{
                                cout << RED << "Nu ai ales corect optiunea de parcare\n" << RESET << endl;
                            }
                        }else{
                            cout << RED << "Nu ai ales corect optiunea de wifi\n" << RESET << endl;
                        }
                }else{
                    cout << RED << "Nu ai ales corect numarul invitati\n" << RESET << endl;
                }
            }
            else{
                cout << RED << "Sala este deja ocupata\n" << RESET;
            }
        }
        if (alegere == 3) {
            vector <Sala> sali = read_file();
            vector <Sala> sali_rezervate;

            for (int i = 0; i < sali.size()-1; i++) {
                if(sali[i].Get_isReserved() == 1){
                    sali_rezervate.push_back(sali[i]);
                }
            }

            for(auto i : sali_rezervate){
                cout << "Denumirea salii rezervate: " << i.Get_Name() << endl
                << "Capacitatea salii: " << i.Get_capacity() << endl;
                if (i.Get_Wifi() == 1) {
                    cout << GREEN <<"Sala are wifi \n" << RESET << endl;
                } else {
                    cout << RED << "Sala nu are wifi \n" << RESET << endl;
                }
                if (i.Get_Parking() == 1) {
                    cout << GREEN << "Sala are parcare \n" << RESET << endl;
                } else {
                   cout << RED << "Sala nu are parcare \n" << RESET << endl;
                }
                cout << GREEN << "E rezervata pe data de: " << RESET << i.Get_reservedDate() << endl << endl << endl;
            }
            cout << endl << endl;
        }
        if (alegere == 4) {
            vector<Sala> sali = read_file();
            //verificam daca la moment este vre-o sala ocupata
            int count = 0;
            for (auto & i : sali) {
                if(i.Get_isReserved() == 1){
                    count +=1;
                }
            }
            if (count == 0){
                cout << RED << "Nu este nici o sala rezervata\n\n" << RESET << endl;
            }
            else {
//                vector <Sala> sali = read_file();
                vector <Sala> sali_rezervate;
                cout << GREEN <<  "Iata salile rezervate:" << RESET << endl;

                for (auto & i : sali) {
                    if(i.Get_isReserved() == 1){
                        sali_rezervate.push_back(i);
                    }
                }
                // cu ajutorul supraincarcarii operatorului "<<" facem output la salile disponibile
                for(const auto& i : sali_rezervate){
                    cout << i << endl;
                }
                cout << endl << endl;

                cout << "Ce sala vrei sa anulezi?\nAlege indexul corespunzator";
                int index_anulare;
                cin >> index_anulare;

                index_anulare--;
                if (sali[index_anulare].Get_isReserved() == 0) {
                    cout << RED << "Aceasta sala nu a fost rezervata,incearca alta sala\n\n" << RESET << endl;
                } else {
                    sali[index_anulare].Set_Capacity(0);
                    sali[index_anulare].Set_Wifi(0);
                    sali[index_anulare].Set_Parking(0);
                    sali[index_anulare].Set_isReserved(0);
                    sali[index_anulare].Set_ReservedDate("00/00/0000");
                    write_file(sali);
                }
            }

        }
        if (alegere == 5) {
            break;
        }
    }
    return 0;
}