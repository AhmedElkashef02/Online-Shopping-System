#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <stdlib.h>

using namespace std;
class ItemList;
class ItemNode {
public:
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
};
class File{
public:
  string NumperToString (int Number){
    stringstream ss;
    ss << Number;
    return ss.str();
  }
  void add_to_file(string br, string md, double pr){
      ofstream myfile("products.txt",ios::app);
      myfile << br << "," << md << "," << pr << "\n";
      myfile.close();

  }
  void delete_from_file(string brn, string mod){
    string b(brn), m(mod),line;
    ifstream in("products.txt");
    if( !in.is_open())
    {
        cout <<"Unable to open products.txt, please make sure file exists!"<<endl;
        return;
    }
    ofstream out("outfile.txt"); //temp file that will have our records with out the deleted line
        //Now our file (records.txt) is open lets loop through an find our customer name which wa
        //inputted just a ways up.
    while( getline(in,line) )
    {
         if ( ( line.find (b+','+m, 0)))
        //if last name is found delete the whole line
        out << line << "\n";
    }
    //close our files, because were done!
    in.close();
    out.close();
    // delete the original file
    remove("products.txt");
    // rename old to new
    rename("outfile.txt","products.txt");
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

  /*ItemList *reCreateDb() {
    ItemList *dB = new ItemList();

    //Reading File
    ifstream file1("products.txt");
    string temp;
    int lineCount=0;
    while(getline(file1,temp)){
      ++lineCount;
      }

    ifstream file2("products.txt");
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
      string *splitted = splitString(var);
      dB->addToTail(splitted[0],splitted[1],convertToDouble(splitted[2]));
    }
  return dB;

  }*/
};  
class ItemList{
private:
  ItemNode *head, *tail;

public:
  ItemList() {
    head = tail = 0;
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
      add.add_to_file(br, md, pr);

    } else {
      tail->next = new ItemNode(br, md, pr);
      tail = tail->next;
      add.add_to_file(br, md, pr);
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
      if (head == tail && ( br == head->brand && md == head->model) ) {
        if(remove( "products.txt" ) != 0)
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

        del.delete_from_file(br,md);
   
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
        del.delete_from_file(br,md);
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
};



int main() {
  remove("products.txt");
  ItemList *headPhones = new ItemList();
  headPhones->addToTail("yalahwi","3x01",1235.57);
  headPhones->addToTail("yala","3x01",19.3);
  headPhones->addToTail("yalahw","3x01",9.5);
  headPhones->addToTail("ya","3x01",35.54);
  headPhones->addToTail("yalah","3x01",75.8);
  headPhones->deleteNode("yalahwi","3x01");

  /*ItemList *x = reCreateDb();
	x->addToTail("yalahwi","3x01",1235.57);
  x->addToTail("yala","3x01",19.3);
  x->addToTail("yalahw","3x01",9.5);
  x->addToTail("ya","3x01",35.54);
  x->addToTail("yalah","3x01",75.8);
  //x->deleteNode("yalahwi","3x01",1235.57);*/
	headPhones->printAll();

  return 0;
}
