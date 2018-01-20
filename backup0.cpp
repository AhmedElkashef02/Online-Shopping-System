/* modifications:
    1- create a File class has methods such as add to file, delete from file
       so our program works such that, if we adding a product to a linked list we use addtotail and that method in ItemList(linked list)
       class adding a node containing the info to the end of the linked list as well as adding to the file product.txt by calling
       fuction add to file in File class, and same if we want to delete a product 
*/
#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <stdlib.h>
#include <typeinfo>

using namespace std;
class ItemList;
class ItemNode {
public:
  string catprod;
  string brand;
  string model;
  double price;
  ItemNode *next; // pointer to next node

  ItemNode(string br, string md, double pr, ItemNode *ptr = 0) {
    brand = br;
    model = md;
    price = pr;
    next = ptr;
  }
  ItemNode(string notitems, ItemNode *ptr = 0){
    catprod = notitems;
    next = ptr;
  }
};
class File{
public:
  void add_to_file(string br, string md, double pr, string FileName){

      // open file product to write
      ofstream myfile(FileName.c_str(),ios::app);
      // adding the given brand, model and price values to the end of the file
      myfile << br << "," << md << "," << pr << "\n";
      myfile.close();
 
  }
  void delete_from_file(string brn, string mod, string FileName){
	    string b(brn), m(mod),line;
	    ifstream in(FileName.c_str());
	    if( !in.is_open())
	    {
	        cout <<"Unable to open products.txt, please make sure file exists!"<<endl;
	        return;
	    }
	    ofstream out("outfile.txt"); //temp file that will have our products with out the deleted line
	        //Now our file (products.txt) is open lets loop through an find our brand and model name which wa
	        //inputted just a ways up.
	    while( getline(in,line) )
	    {
	         if ( ( line.find (b+','+m, 0)))
	        //if brand and model is found delete the whole line
	        out << line << "\n";
	    }
	    //close our files, because were done!
	    in.close();
	    out.close();
	    // delete the original file
	    remove(FileName.c_str());
	    // rename old to new
	    rename("outfile.txt",FileName.c_str());
  }

  string *splitString(string str) {
    static string array[3];
    std::vector<std::string> strings;
     std::istringstream f(str);
     std::string s;
     int iterator = 0;
     while (std::getline(f, s, ',')) {
           array[iterator] = s;
           iterator++;
           strings.push_back(s);
     }
     return array;
  }

  double convertToDouble(string str) {
    double price = atof(str.c_str());
    return price;
  }


};  
class ItemList{
private:
  ItemNode *head, *tail;

public:
  string File_name;
  ItemList(string file) {
    File_name=file;
    head = tail = 0;
    ifstream check(file.c_str());
    if (check.good()){
      return;
    }
    else{
      ofstream create;
      create.open(file.c_str());
      create.close();
    }
  }
  int isEmpty() {
    return head == 0;
  }

  void addToHead(string br, string md, double pr) {
    head = new ItemNode(br, md, pr, head);
    if (tail == 0)
      tail = head;
  }

  void addToTail(string br, string md, double pr) {
    File add;
      if (tail == 0) {
        head = tail = new ItemNode(br, md, pr);
        //add.add_to_file(br, md, pr, File_name);

      } else {
        tail->next = new ItemNode(br, md, pr);
        tail = tail->next;
        //add.add_to_file(br, md, pr, File_name);
      }
  }

  void deleteFromHead() {
    ItemNode *tmp = head;
    if (head == tail)
      head = tail = 0;
    else
      head = head->next;
    delete tmp;
  }

  void deleteFromTail() {
    if (head == tail) {
      delete head;
      head = tail = 0;
    } else {
      ItemNode *tmp;
      for (tmp = head; tmp->next != tail; tmp = tmp->next)
        ;

      delete tail;
      tail = tmp;
      tail->next = 0;
    }
  }

  void deleteNode(string br, string md) {
    File del;
    if (head != 0) {
      // if the list has only one node as well as the file has only one line of info
      // so we can remove that file as well as the node 
      if (head == tail && ( br == head->brand && md == head->model) ) {
        if(remove( File_name.c_str() ) != 0)
          perror( "Error deleting file" );
        else
          puts( "File successfully deleted" );

        delete head;
        head = tail = 0;

      } else if (br == head->brand && md == head->model) {
        // deleteFromHead();
        ItemNode *tmp = head,*p;
        head = head->next;
        delete tmp;

        del.delete_from_file(br,md,File_name);
   
      } else {
        ItemNode *p, *tmp;
        for (p = head, tmp = head->next; (tmp != 0 && tmp->brand != br && tmp->model != md);
             p = p->next, tmp = tmp->next)
          ;

        if (tmp != 0) {
          p->next = tmp->next;
          if (tmp == tail)
            tail = p;
          delete tmp;
        }
        del.delete_from_file(br,md,File_name);
      }
    }
  }

  bool isInList(string br, string md, double pr) const { // can't change any member state
    ItemNode *tmp;
    for (tmp = head; tmp != 0 && tmp->brand != br && tmp->model != md && tmp->price != pr; tmp = tmp->next)
      ;
    return tmp != 0;
  }

  void printAll() const {
    ItemNode *p;
    for (p = head; p != 0; p = p->next) {
      cout << p->brand << "," << p->model << "," << p->price << endl;
    }
  }

  ~ItemList() {
    for (ItemNode *p; !isEmpty();) {
      p = head->next;
      delete head;
      head = p;
    }
  }

  void update(string file_name)
  {
    remove(file_name.c_str());
    ofstream indata;
    indata.open(file_name.c_str());
    ItemNode *temp;
    for(temp = head; temp != 0; temp = temp->next)
    {
      indata << temp->brand << "," << temp->model << "," << temp->price << endl;
    }

    indata.close();
  }


};
	ItemList *reCreateDb(string file) {
	  ItemList *dB = new ItemList(file);
	  File call;
	  //Reading File
	  ifstream file1(dB->File_name.c_str());
	  string temp;
	  int lineCount=0;
	  while(getline(file1,temp)){
	    ++lineCount;
	    }

	  ifstream file2(dB->File_name.c_str());
	  string lines[lineCount];
	  int lineIterator = 0;
	  string line;
	  while(getline(file2, line)){
	    lines[lineIterator] = line;
	    lineIterator++;
	  }

	  //recreate database from the readed file lines
	  for (int i = 0; i<lineCount;i++){
	    string var = lines[i];
	    string *splitted = call.splitString(var);
	    dB->addToTail(splitted[0],splitted[1],call.convertToDouble(splitted[2]));
	  }
	  return dB;

	}


int main() {

	string list_name;
	const char *a[] = {"mobiles", "laptops"};

			ItemList *mobile_list = reCreateDb(a[0]);

			//ItemList *laptop_list = reCreateDb(a[1]);


					// mobile_list->addToTail("yalahwi","3x01",1235.57);
					// mobile_list->addToTail("yala","3x01",19.3);
					// mobile_list->addToTail("yalahw","3x01",9.5);
					// mobile_list->addToTail("ya","3x01",35.54);
					// mobile_list->addToTail("yalah","3x01",75.8);
     //      mobile_list->update(a[0]);
					mobile_list->deleteNode("yalah","3x01");
          mobile_list->update(a[0]);
			mobile_list->printAll();
	
 //  remove("products.txt");
 //  ItemList *headPhones = new ItemList();
 //  headPhones->addToTail("yalahwi","3x01",1235.57);
 //  headPhones->addToTail("yala","3x01",19.3);
 //  headPhones->addToTail("yalahw","3x01",9.5);
 //  headPhones->addToTail("ya","3x01",35.54);
 //  headPhones->addToTail("yalah","3x01",75.8);
 //  headPhones->deleteNode("yalahwi","3x01");

	
	// headPhones->printAll();

  return 0;
}
