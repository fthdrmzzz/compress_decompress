#include "HashTable.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "DictionaryNode.h"

// I Will not write comments for hash table because 
// ý found It from Internet and manipulated IT a little
//(cemal hoca gave permission abi valla)

//Compout read reads thegiven input "compout.txt"
//and returns it as a string
string compout_read() {
	ifstream file;
	string filename = "compout.txt";
	file.open(filename.c_str());
	string compout="";
	char ch;
	while (file.get(ch)) {
		compout += ch;
	}
	return compout;
}

//decompress function takes notfound as a parameter
//and creates a hashtable inside the function to 
//decompress the given codelist.
void decompress(DictionaryNode notfound) {
	string compout =compout_read(),output;
	istringstream input(compout);				//I will use this to get codes
												//one by one.

	HashTable<DictionaryNode> table(notfound);	// when ý search in my hashtable,
												//It will return notfound object if it
												//is not found.

	//*********************************************************************************
	char x = 0;
	for (int i = 0; i < 256;i++) {				//here initially I add all of the Ascii
		DictionaryNode elem;					//characters to the hashtable.
		elem.key = x;
		elem.code = i;
		table.insert(elem);
		x++;
	}
	//*********************************************************************************

	int code,prev,index_counter=256;
	string add;

	//*********************************************************************************
	input >> prev;
	output += table.GiveElement(prev).key;	//adding first code to the output.
	while(!input.eof())						// under this loop I do all deciphering.
	{
		input >> code;						//taking a new code as input.
		if(!table.isPositionExist(code)){	//If It is not inserted before.
			add = table.GiveElement(prev).key+ table.GiveElement(prev).key.at(0); //ADD = next inserted key
		}
		//***************
		//give element gives the element at the given index.
		//ý created it in the hash table.
		//***************
		else {								//if code does not appear 
											//for the first time;
			add = table.GiveElement(prev).key + table.GiveElement(code).key.at(0); //ADD = next inserted key
		}									    
		DictionaryNode element(add, index_counter); //creates the element to be added.
		table.insert(element);						//inserts the element.
		output += table.GiveElement(code).key;		//outputs the current key.
		prev = code;
		index_counter++;
	}
	//*********************************************************************************

	ofstream decompout;
	string filename= "decompout.txt";
	decompout.open(filename.c_str());
	decompout << output;

	//cout << output;
}

int main() {
	DictionaryNode notfound("not found ýt yeeeeeeeeeeeee");
	decompress(notfound);


	return 0; 

}