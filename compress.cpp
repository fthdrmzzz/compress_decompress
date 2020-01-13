#include <iostream>
#include "HashTable.h"
#include <fstream>
#include <sstream>
#include "DictionaryNode.h"
using namespace std;



string return_input() {								//thisfunction returns the string of the
													//given compin file.
	ifstream file;									
	string filename = "compin.txt", input;
	file.open(filename.c_str());
	char ch;
	while (file.get(ch)) {							//after this loop, all input is in 
		input += ch;								// the input string.
	}
	file.close();
	return input;
}

void make_output(string output) {					//creates the output,compout file.
	ofstream file;
	string filename = "compout.txt";
	file.open(filename.c_str());
	output = output.substr(0, output.length() - 1);
	file << output;
	file.close();
	}


void compress(const DictionaryNode &notfound) {
	HashTable<DictionaryNode> table(notfound);

	string input = return_input();
	string output;
	int index = 0;

	char x = 0;
	for (int i = 0; i < 256;i++) {
		DictionaryNode elem;
		elem.key = x;
		elem.code = i;
		table.insert(elem);
		x++;
	}


	while (index < input.length() && input.length()!=0)
	{
		//******************************
		string key = "";
		key += input[index];
		DictionaryNode element(key);
		//******************************

		if (table.find(element) == notfound) {		// if the letter itself is not inserted to table
			element.code = table.findPosAccessor(element);
			table.insert(element);					//insert it to table.
			output += to_string(element.code)+" ";		//add It's code to the output
 	
			index++;		}
		else {
			bool check = true;
			while (table.find(element) != notfound && index != input.length() - 1) {
				index++;
				element.key += input[index];
				check = false;
			}

			if (table.find(element) == notfound) {							//if the stringpiece is not found in the table,
				element.code = table.findPosAccessor(element);
				table.insert(element);							//insert it to the table.
				element.key = element.key.substr(0, element.key.length() - 1);
				output += to_string(table.findPosAccessor(element))+" ";		//output the known stringpiece. unknown one is excluded.
																//ýt will be inserted in next cycle of loop
			}
			else if(index==input.length()){	//element is found, but input has ended.
												// no need to insert. just output the code.
				if (check) { 
					element.code = table.findPosAccessor(element);
					index++; 
				}
				output += to_string(element.code)+" ";
				
			}

			/*element.key = element.key.substr(0, element.key.length() - 1);
			element.code = table.findPosAccessor(element);
			table.insert(element);
			output += element.code + " ";*/

		}
	}
		cout << output; 
	make_output(output);
}

using namespace std;
int main()
{
	DictionaryNode notfound("This object does not exist");
	compress(notfound);

	return 0;
}
