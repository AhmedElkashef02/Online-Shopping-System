#include <iostream>
#include <fstream>
using namespace std;
void delet(string b, string a){
string h(b),j(a);
//Ask the user who they want to delete
	string line;
	//cout <<"Enter the Last Name of the person you want to delete." <<endl;
	//cin >>last_name;
	//Lets open our file that holds our records (records.txt), if it does not open show error
	ifstream in("example.txt");
	if( !in.is_open())
	{
	    cout <<"Unable to open record.txt, please make sure file exists!"<<endl;
	}
	ofstream out("outfile.txt"); //temp file that will have our records with out the deleted line
	    //Now our file (records.txt) is open lets loop through an find our customer name which wa
	    //inputted just a ways up.
	while( getline(in,line) )
	{
       if ( ( line.find (h+','+j, 0)))
	    //if last name is found delete the whole line
	    out << line << "\n";
	}
	//close our files, because were done!
	in.close();
	out.close();
	// delete the original file
	remove("example.txt");
	// rename old to new
	rename("outfile.txt","example.txt");
}
int main(){    
	//string a,b;
	// a = "youssef";
	// b = "elmasry";
	// cout<<a.append(b);
	delet("youssef","elmasry");
    return 0;
}    
