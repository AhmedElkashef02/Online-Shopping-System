#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <stdlib.h>
#include "md5.h"

using namespace std;

class ItemNode {
public:
  string username;
  string password;
  ItemNode *next; // pointer to next node

  ItemNode(string un, string pwd, ItemNode *ptr = 0) {
    username = un;
    password = pwd;
    next = ptr;
  }
};

class ItemList {
private:
  ItemNode *head, *tail;

public:
  ItemList() {
    head = tail = 0;
  }

  int isEmpty() {
    return head == 0;
  }

  void addToHead(string un, string pwd) {
    head = new ItemNode(un, pwd, head);
    if (tail == 0)
      tail = head;
  }

  void addToTail(string un, string pwd) {
    string secure_pwd = md5(pwd);
    if (tail == 0) {
      head = tail = new ItemNode(un, secure_pwd);
      ofstream myfile;
      myfile.open("users.txt");
      myfile << un << "," << secure_pwd << "\n";
      myfile.close();
    } else {
      tail->next = new ItemNode(un, secure_pwd);
      tail = tail->next;
      ofstream myfile;
      myfile.open("users.txt",ios::app);
      myfile << un << "," << secure_pwd << "\n";
      myfile.close();
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

  void deleteNode(string un, string pwd) {
    if (head != 0) {
      if (head == tail && ( un == head->username && pwd == head->password ) ) {
        delete head;
        head = tail = 0;
      } else if (un == head->username && pwd == head->password) {
        // deleteFromHead();
        ItemNode *tmp = head;
        head = head->next;
        delete tmp;
      } else {
        ItemNode *p, *tmp;
        for (p = head, tmp = head->next; (tmp != 0 && tmp->username != un && tmp->password != pwd);
             p = p->next, tmp = tmp->next)
          ;

        if (tmp != 0) {
          p->next = tmp->next;
          if (tmp == tail)
            tail = p;
          delete tmp;
        }
      }
    }
  }

  bool isInList(string un, string pwd) const { // can't change any member state
    ItemNode *tmp;
    for (tmp = head; tmp != 0 && tmp->username != un && tmp->password != pwd; tmp = tmp->next)
      ;
    return tmp != 0;
  }

  void printAll() const {
    ItemNode *p;
    for (p = head; p != 0; p = p->next) {
      cout << p->username << "," << p->password << endl;
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

ItemList *reCreateDb() {
  ItemList *dB = new ItemList();

  //Reading File
  ifstream file1("users.txt");
	string temp;
	int lineCount=0;
	while(getline(file1,temp)){
		++lineCount;
		}

	ifstream file2("users.txt");
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
    dB->addToTail(splitted[0],splitted[1]);
  }
	return dB;

}

int main() {

  ItemList *headPhones = new ItemList();

  ItemList *x = reCreateDb();
	x->addToTail("OmarGaber","omamomam");
	x->printAll();

  return 0;
}
