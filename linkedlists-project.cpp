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

using namespace std;
//class ItemList;
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
  void add_to_file(string br, string md, double pr){
      // open file product to write
      ofstream myfile("products.txt",ios::app);
      // adding the given brand, model and price values to the end of the file
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
    remove("products.txt");
    // rename old to new
    rename("outfile.txt","products.txt");
  }


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


  void deleteNode(string br, string md) {
    File del;
    if (head != 0) {
      // if the list has only one node as well as the file has only one line of info
      // so we can remove that file as well as the node 
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

  void update(char* file_name)
  {

    remove(file_name);
    ofstream indata;
    indata.open(file_name);
    ItemNode *temp;
    for(temp = head; temp != 0; temp = temp->next)
    {
      indata << temp->brand << "," << temp->model << "," << temp->price << endl;
    }

    indata.close();
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
  char Mobile_phones[] = "Mobile_Phones.txt";
  string Headphones = "Headphones.txt";
  string Laptops = "Laptops.txt";
  string Power_banks = "Power_Banks.txt";
  string Chargers = "Chargers.txt";

  ItemList *mobiles = reCreateDb(Mobile_phones);

  //mobiles->addToTail("LG","Stylus 2", 899.99);
  // mobiles->addToTail("Samsung","Galaxy S2",1200.99);
  mobiles->addToTail("OnePlus","3T",560.99);
 //  mobiles->addToTail("Blackberry","Z",14399.99);
   //mobiles->addToTail("Samsung","Note 2", 1226.99);
  mobiles->deleteNode("LG","Stylus 2", 899.99);
  //mobiles->deleteNode("Samsung","Note 2", 1226.99);
  mobiles->update(Mobile_phones);
  mobiles->printAll();

  cout<<endl;

  ItemList *laptops = reCreateDb(Laptops);
  laptops->addToTail("HP","Pavilion",1235.999);
  laptops->addToTail("HP","Envy",1245.68);
  // laptops->addToTail("Lenovo","YOGA 300", 1244.98);
  // laptops->addToTail("Apple","Mack Book Pro",99999.99);
  laptops->printAll();
  return 0;
}
