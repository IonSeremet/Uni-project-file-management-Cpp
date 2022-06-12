//
// Created by ABOBUS on 10.05.2022.
//
#include <sstream>
#include <iostream>
#include <vector>
#include <fstream>
#include "stdlib.h"
#include <string>
#include <algorithm>
using namespace std;

#ifndef UNTITLED1_SALA_H
#define UNTITLED1_SALA_H


class Sala {
private:
    int id;
    string name;
    int capacity;
    int isReserved;
    int wifi;
    int parking;
    string reservedDate;
public:
    Sala(string );
    friend ostream & operator << (ostream &, const Sala &);
    int Get_Id() const{
        return id;
    }
    string Get_Name()
    {
        return name;
    }
    int Get_capacity() const{
        return capacity;
    }
    int Get_isReserved() const{
        return isReserved;
    }
    int Get_Wifi() const{
        return wifi;
    }
    int Get_Parking() const{
        return parking;
    }
    string Get_reservedDate(){
        return reservedDate;
    }
    void Set_Capacity(int n)
    {
        capacity=n;
    }
    void Set_isReserved(int n){
        isReserved=n;
    }
    void Set_Wifi(int n){
        wifi=n;
    }
    void Set_Parking(int n){
        parking=n;
    }
    void Set_ReservedDate(string n){
        reservedDate=n;
    }
    friend bool operator !=(const Sala& s1,const Sala& s2);

};


#endif //UNTITLED1_SALA_H
