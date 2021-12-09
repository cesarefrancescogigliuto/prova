#ifndef GIOCATORE_H
#define GIOCATORE_H
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
using namespace std;


class Giocatore{
    string cognome, nome;
    int giocate,vinte,perse;

    public:
        Giocatore(string cognome, string nome, int giocate, int vinte, int perse);
        Giocatore();
        string getNome();
        string getCognome();
        int getGiocate();
        int getVinte();
        int getPerse();
        //double getMedia();

    friend istream& operator>>(istream& in, Giocatore &s) {
		string giocate_string,vinte_string,perse_string;
		getline(in, s.cognome, ';');
		getline(in, s.nome, ';');
		getline(in, giocate_string, ';');
		getline(in, vinte_string, ';');
		getline(in, perse_string, '\n');

		s.giocate = stoi(giocate_string);
		s.vinte = stoi(vinte_string);
		s.perse = stoi(perse_string);

		return in;

	}

	friend ostream& operator<<(ostream& out, const Giocatore& s) {

		out <<" " << s.cognome<< " " << s.nome << ", " << s.giocate << ", " << s.vinte << ", " << s.perse;
		return out;
	}


	//Confronto in base al numero di partite vinte per la classifica
    bool operator >(const Giocatore& s) const {
		return this->vinte > s.vinte;
	}

	bool operator <(const Giocatore& s) const {
		return this->vinte < s.vinte;
	}

	bool operator >=(const Giocatore& s) const {
		return this->vinte >= s.vinte;
	}

	bool operator <=(const Giocatore& s) const {
		return this->vinte <= s.vinte;
	}

	bool operator ==(const Giocatore& s) const {
		return this->vinte == s.vinte;
	}


};

#endif
