// =================================================================
//
// File: main.cpp
// Author:
// Date:
//
// =================================================================
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

using namespace std;

void openFile(ifstream& inFile,string fname){
	inFile.open(fname);
	if (inFile.is_open()){
		cout << "Successfully opened file"<<endl;
	}
	else{
		cout << "Failed to open file" << endl;
		exit(-1);
	}
}

string processFile(ifstream& inFile,int i, int limit){
	//read line by line
	string line;
	vector<string> line2; 
	while (!inFile.eof() && i < limit){
		i++;
		getline(inFile,line);
		if(inFile.good()){
			cout<< line << endl;
		}
	} 
	return line;
}

int main(int argc, char* argv[]) {

	ifstream inFile;
	openFile(inFile,"input1.txt");
	string linea1 = processFile(inFile,0,1);
	stringstream linea2(linea1);
	string linea, lineaP;
	char delimiter= ' ';
	vector<string> linea1separada;
	while (getline(linea2, linea, delimiter)) {
        linea1separada.push_back(linea);
    }
	int numDesc,numPalabras;
	stringstream nP(linea1separada[0]);
	stringstream nD(linea1separada[1]);
	nP >> numPalabras;
	nD >> numDesc;
	cout << numPalabras<< endl;
	cout << numDesc<< endl;
	string p1 = processFile(inFile,1,numPalabras);
	stringstream palabras(p1);
	vector<string> lineaPseparada;
	while (getline(palabras, lineaP, delimiter)) {
        lineaPseparada.push_back(lineaP);
    }
for (int i = 0; i < lineaPseparada.size(); i++)
	{
		cout << lineaPseparada[i]<< endl; 
	}
	return 0;
}
