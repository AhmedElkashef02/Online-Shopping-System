//============================================================================
// Name        : linkedList.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <math.h>
using namespace std;
class Intnode{
public:
	int data;
	Intnode * next; //pointer to next node
	Intnode *sub;	//pointer to another list

	Intnode(int x, Intnode* ptr=0, Intnode* pt=0){
		data = x;
		next = ptr;
		sub = pt;
	}
};

class IntLlist{
private:
	Intnode *head,*tail;
public:


	IntLlist(){
		head = tail = 0;
	} 

	int isEmpty(){
		return head==0;
	}

	void addToHead(int d){
		head = new Intnode(d,head);
		if(tail == 0)
			tail = head;
	}

	void addToTail(int d){
		if(tail==0)
			head = tail = new Intnode(d);
		else{
			tail->next = new Intnode(d);
			tail = tail->next;
		}
	}

	//return deleted data
	int deleteFromHead(){
		int d = head->data;
		Intnode * tmp = head;
		if(head == tail)
			head = tail = 0;
		else
			head =head->next;
		delete tmp;
		return d;

	}

	int deleteFromTail(){
		int d = tail->data;
		if(head==tail){
			delete head;
			head = tail =0;
		}
		else{
			Intnode * tmp;
			for(tmp=head;tmp->next!=tail;tmp=tmp->next);

			delete tail;
			tail=tmp;
			tail->next = 0;
		}
		return d;

	}
	void deleteNode(int d){
		if(head!=0){
			if(head ==tail && d==head->data){
				delete head;
				head = tail = 0;
			}
			else if(d == head->data){
				//deleteFromHead();
				Intnode *tmp = head;
				head = head->next;
				delete tmp;
			}
			else{
				Intnode *p,*tmp;
				for(p=head,tmp=head->next; (tmp!=0 && tmp->data!=d);p=p->next,tmp=tmp->next);

				if(tmp!=0){
					p->next = tmp->next;
					if(tmp==tail)
						tail = p;
					delete tmp;
				}
			}
		}
	}

	bool isInList(int d) const{ //can't change any member state
		Intnode * tmp;
		for(tmp=head;tmp!=0&& tmp->data !=d;tmp=tmp->next);
		return tmp!=0;
	}

	void printAll(int d=0, int d1=0) const{
		Intnode * p;
		if(d == 0 && d1 == 0){
			for(p=head;p!=0;p=p->next){
				cout << p->data <<' ';
			}
			cout<<endl;
		}
		else if(d != 0 && d1 == 0){
			for(p=head;p!=0&& p->data !=d;p=p->next);
			if(p!=0 && p->data==d){
				for(p=p->sub;p!=0;p=p->next){
					cout << p->data <<' ';
				}
				cout<<endl;
			}
			else{
				cout<<"no list found\n";
			}	
		}
		else{
			for(p=head;p!=0&& p->data !=d;p=p->next);
				if(p!=0 && p->data==d){
					for(p=p->sub;p!=0&& p->data !=d1;p=p->next);
						if(p!=0 && p->data == d1){
							for(p=p->sub; p!=0; p=p->next){
								cout<<p->data<<' ';
							}
							cout<<endl;	
						}
						else{
							cout<<"no list\n";
						}
				}
				else{
					cout<<"no list\n";
				}
		}	
	}

	~IntLlist(){
			for(Intnode* p; !isEmpty();){
				p=head->next;
				delete head;
				head = p;
			}

		}


// creating two function to make a category list each category has a list of products and each product has a list of items


	void addlist(IntLlist* nlist, int d){ // add product lists to category list
		Intnode * tmp;
		for(tmp=head;tmp!=0&& tmp->data !=d;tmp=tmp->next);
		if(tmp!=0 && tmp->sub==0){
			tmp->sub = nlist->head;
		}
		else{
			cout<<"there already a list\n";
		}
	}

	void addsublist(IntLlist* nlist, int d1, int d2){ // add items lists to products lists
		Intnode *tmp;
		for(tmp=head;tmp!=0&& tmp->data !=d1;tmp=tmp->next);
			if(tmp!=0 && tmp->sub!=0){
				for(tmp=tmp->sub;tmp!=0 && tmp->data != d2; tmp = tmp->next);
					if(tmp!=0 && tmp->sub == 0)
						tmp->sub = nlist->head;
					else{
						cout<<"there is already a list\n";
					}
			}
			else{
				cout<<"there is no list to add on it, please add a list first\n";
			}			
	}
	
};


int main() {
	IntLlist *myList= new IntLlist();
	IntLlist *l1= new IntLlist();
	IntLlist *l2= new IntLlist();

	//cout<<myList->isEmpty()<<endl;

	myList->addToHead(5);
	myList->addToHead(3);
	myList->addToTail(10);
	myList->addToHead(1);
	myList->addToHead(-7);
	myList->addToTail(30);

	l1->addToHead(0);
	l1->addToHead(2);
	l1->addToTail(0);
	l1->addToHead(0);
	l1->addToHead(0);
	l1->addToTail(0);

	l2->addToHead(1);
	l2->addToHead(1);
	l2->addToTail(1);
	l2->addToHead(1);
	l2->addToHead(1);
	l2->addToTail(1);

	myList->addlist(l1,5);
	
	myList->addsublist(l2,5,2);

	cout<<endl;
	cout<<"category list\n"; myList->printAll(); cout<<"\n";
	cout<<"products list\n"; myList->printAll(5); cout<<"\n";
	cout<<"items list\n";    myList->printAll(5,2); cout<<"\n";


	return 0;
}
