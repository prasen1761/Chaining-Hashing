#include<iostream>
#include<vector>
#include<fstream>

using namespace std;

struct Node 
{
	int data;
	struct Node * next;
};

std::vector<struct Node *> table;

void init(int n)
{
	for(int i=0;i<n;i++)
		table.push_back(NULL);
}

struct Node * createNode(int value)
{
	struct Node * ptr=(struct Node * )malloc(sizeof(struct Node));
	ptr->data=value;
	ptr->next=NULL;
	return ptr;
}

bool putIntoTable(struct Node * nptr)
{
	int index=(nptr->data)%table.size();
	if(table[index]==NULL)
	{
		table[index]=nptr;
		return true;
	}
	else
		return false;
}

void chain(struct Node * nptr)
{
	int index=(nptr->data)%table.size();
	struct Node * p = table[index];
	while(p->next!=NULL)
	{
		p=p->next;
	}
	p->next=nptr;
}

void printHashTable()
{
	struct Node * p;
	for(int i=0;i<table.size();i++)
	{
		p=table[i];
		if(!p)
			cout<<"NULL";
		else
		{
			while(p)
			{
				cout<<p->data<<" ";
				p=p->next;
			}
		}
		cout<<endl;
	}
}

void printMenu()
{
	cout<<"Enter an option\n1-Insert\n2-Delete\n3-Search\n4-Print Table\n5-Store new hash table into data.txt\n6-Exit"<<endl;
}

void deleteFromTable(int value)
{
	int index=value%table.size();
	struct Node * p=table[index];
	struct Node * p_prev=NULL, * p_next;
	while(p)
	{
		if(p->data==value)
			break;
		p_prev=p;
		p=p->next;
	}
	if(p==NULL)
		cout<<"Node not found to delete"<<endl;
	else if(p_prev==NULL && p->data==value)
	{
		if(p->next==NULL)
		{
			table[index]=NULL;
			free(p);
		}
		else
		{
			table[index]=p->next;
			free(p);
		}
		cout<<"Node deleted"<<endl;
	}
	else
	{
		p_prev->next=p->next;
		free(p);
		cout<<"Node deleted ."<<endl;
    }
}

void search(int value)
{
	bool found=false;
	int count=1;
	int index=value%table.size();
	struct Node * p=table[index];
	while(p)
	{
		if(p->data==value)
		{
			found=true;
			cout<<"Value found at index "<<index<<" at position "<<count<<endl;
			break;
		}
		else
		{
			p=p->next;
			count++;
		}
	}
	if(found==false)
		cout<<"Value not found in the table"<<endl;
}

void putDataIntoFile()
{
	ofstream file;
	file.open("data.txt");
	if(file.is_open())
	{
		struct Node * p;
		for(int i=0;i<table.size();i++)
		{
			p=table[i];
			if(!p)
				file<<"NULL"<<endl;
			else
			{
				while(p)
				{
					file<<p->data<<endl;
					p=p->next;
				}
			}
		}
		cout<<"Data stored in the file"<<endl;
	}
	else
		cout<<"File not found"<<endl;
	file.close();
}

bool checkIfPresent(int value)
{
	int index=value%table.size();
	struct Node * p=table[index];
	while(p)
	{
		if(p->data==value)
			return true;
		p=p->next;
	}
	return false;
}

int main(int argc, char * argv[])
{
	cout<<"Enter the size of the table"<<endl;
	int n;
	cin>>n;
	init(n);
	int value;
	struct Node * nptr;
	string line;
	ifstream file(argv[1]);
	if(file.is_open())
	{
		while(getline(file,line))
		{
			if(!(line.compare("NULL")==0))
			{
				value=stoi(line);
				nptr=createNode(value);
				if(putIntoTable(nptr)==false)
				{
					//chain it
					cout<<"Collision oocured."<<endl;
					chain(nptr);
				}
			}
		}
		cout<<"Initial data loaded in the hash table"<<endl;		
	}
	else
		cout<<"File not found."<<endl;
	file.close();
	int opt,val;
	printMenu();
	cin>>opt;
	while(opt!=6)
	{
		switch(opt)
		{
			case 1: cout<<"Enter a value to insert"<<endl;
					cin>>val;
					if(checkIfPresent(val))
						cout<<"Value already present"<<endl;
					else
					{
						nptr=createNode(val);
						if(putIntoTable(nptr)==false)
						{
							//chain it
							chain(nptr);
						}
					}
					break;
			case 2: cout<<"Enter a value to be deleted"<<endl;
					cin>>val;
					deleteFromTable(val);
					break;
			case 3: cout<<"Enter a value to be deleted"<<endl;
					cin>>val;
					search(val);
					break;
			case 4: printHashTable();
					break;
			case 5: putDataIntoFile();
					break; 
		}
		printMenu();
		cin>>opt;
	}
	return 0;
}