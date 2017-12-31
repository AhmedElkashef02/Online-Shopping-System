#include <iostream>
#include <string>

using namespace std;

class Intnode {
public:
	string brand;
	string model;
	double price;
  int data;
  Intnode *next; // pointer to next node

  Intnode(string br, string md, double pr, int x, Intnode *ptr = 0) {
		brand = br;
		model = md;
		price = pr;
    data = x;
    next = ptr;
  }
};

class IntLlist {
private:
  Intnode *head, *tail;

public:
  IntLlist() {
		head = tail = 0;
	}

  int isEmpty() {
		return head == 0;
	}

  void addToHead(int d) {
    head = new Intnode(d, head);
    if (tail == 0)
      tail = head;
  }

  void addToTail(int d) {
    if (tail == 0)
      head = tail = new Intnode(d);
    else {
      tail->next = new Intnode(d);
      tail = tail->next;
    }
  }

  void deleteFromHead() {
    Intnode *tmp = head;
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
      Intnode *tmp;
      for (tmp = head; tmp->next != tail; tmp = tmp->next)
        ;

      delete tail;
      tail = tmp;
      tail->next = 0;
    }
  }

  void deleteNode(string br, string md, double pr) {
    if (head != 0) {
      if (head == tail && ( br == head->brand && md == head->model && pr == head->price ) ) {
        delete head;
        head = tail = 0;
      } else if (br == head->brand && md == head->model && pr == head->price) {
        // deleteFromHead();
        Intnode *tmp = head;
        head = head->next;
        delete tmp;
      } else {
        Intnode *p, *tmp;
        for (p = head, tmp = head->next; (tmp != 0 && tmp->data != d);
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

  bool isInList(int d) const { // can't change any member state
    Intnode *tmp;
    for (tmp = head; tmp != 0 && tmp->data != d; tmp = tmp->next)
      ;
    return tmp != 0;
  }

  void printAll() const {
    Intnode *p;
    for (p = head; p != 0; p = p->next) {
      cout << p->data << endl;
    }
  }

  ~IntLlist() {
    for (Intnode *p; !isEmpty();) {
      p = head->next;
      delete head;
      head = p;
    }
  }
};

int main() {
  IntLlist *myList = new IntLlist();

  myList->addToTail(30);

  return 0;
}
