// =================================================================
//
// File: main.cpp
// Author: DIEGO ITURBE BRAVO
// Date: 30/NOV/2022
//
// =================================================================
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <string>
#include "exception.h"
#include "hash.h"
#include <sstream>
using namespace std;

void openFile(ifstream& inFile,string fname){
	inFile.open(fname);
	if (inFile.is_open()){
		// cout << "Successfully opened file"<<endl;
	}
	else{
		cout << "Failed to open file" << endl;
		exit(-1);
	}
}

vector<string> processFile(ifstream& inFile,int i, int limit){
	//read line by line
	vector<string> content;
	string line;
	int cont=0;
	
	while (!inFile.eof() && i < limit){
		i++;
		getline(inFile,line);
		// bool found = line.find('.');
		//found == 1 == No se encontro punto
		if(inFile.good()){
			content.push_back(line);
			
		}
		cont++;

	} 
	return content;
}

unsigned int myHash1(const string s) {
	unsigned int acum = 0;
	for (unsigned int i = 0; i < s.size(); i++) {
		acum += (int) s[i];
	}
	return acum;
}

int toKey(string word){
	int  hash = 0;
	int index;
	for (int i = 0; i < word.length(); i++)	{
		hash = hash + (int)word[i];
	}
	// index = hash % size;
	return index;
}

int main(int argc, char* argv[]) {
	ifstream inFile;
	openFile(inFile,"input1.txt");
	//obtener linea 1
	vector<string> linea1 = processFile(inFile,0,1);
	string linea, lineaP, lineaD;
	char delimiter= ' ';
	vector<string> linea1separada;
	for (int i = 0; i < linea1.size(); i++){
		stringstream x(linea1[i]);
		while (getline(x, linea, delimiter)) {
        linea1separada.push_back(linea);
		}
	}
	int numDesc,numPalabras;
	stringstream nP(linea1separada[0]);
	stringstream nD(linea1separada[1]);
	nP >> numPalabras;
	nD >> numDesc;
	// cout << numPalabras<< endl;
	// cout << numDesc<< endl;

	// obtener lineas Palabras
    vector<string> p1 = processFile(inFile,1,numPalabras+1);
	vector<string> lineaPseparada, valoresP;
	for (int i = 0; i < p1.size() ; i++){
		stringstream y(p1[i]);
		int cont=0;
		while (getline(y, lineaP, delimiter)) {
			if (cont % 2 == 0){ 
				//palabra(key)
				lineaPseparada.push_back(lineaP);
			}
			else{
				//valor
				valoresP.push_back(lineaP);
			}
			cont++;
		} 
	}

	// obtener lineas Descripciones
	int nums= numPalabras + 2;
	int nums2= numPalabras + ( numDesc*2 + 100) ;
	vector<string> d1 = processFile(inFile,nums,nums2);
	vector<string> lineaDseparada;
	for (int i = 0; i < d1.size(); i++){
		stringstream z(d1[i]);
		while (getline(z, lineaD, delimiter)) {
        lineaDseparada.push_back(lineaD);
		}
	}

	//inicializar la tabla con tamaño
	HashTable<string, int> hash(1001, string("empty"), myHash1);
	int value;
	for (int i = 0; i < p1.size(); i++){
		stringstream val(valoresP[i]);
		val >> value;
		hash.put(string(lineaPseparada[i]), value);
	}

	// cout << hash.toString() << "\n\n";

	int suma =0;
	for (int i = 0; i < lineaDseparada.size(); i++){
		bool found = lineaDseparada[i].find('.');
		//found == 1 == No se encontro punto
		if (found == 0){
			cout<< suma<< endl;
			suma = 0;
		}
		int val = hash.get(lineaDseparada[i]);
		if (val != 0){
			suma = suma + val;
		}
	}
	cout<< suma<< endl;

	return 0;
}
