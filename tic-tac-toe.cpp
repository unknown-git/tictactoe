#include <iostream>
#include <stdlib.h>
using namespace std;

class Play
{
	struct node
	{
		node *prev;
		char data;
		int id;
		node *next;
	}*h;

	public:
		Play()
		{
			h=NULL;
		}
		
		~Play()
		{
			node *q;
			if( h == NULL )
				return;
			while( h != NULL )
			{
				q = h->next;
				delete h;
				h = q;
			}
		}
		
		int istie();			//checks for tie
		int validate(int);		//validates move
		void player(int);		//player move
		void create();			//creates grid
		void display();			//displays grid
		void result();			//displays result
		void start();			//starts 2 player game
		void startAI();			//starts game vs cpu
		void AImove();			//cpu move logic
};

void Play :: create()
{
	node *f,*s;
	int temp=0,i;
	f=new node;
	f->prev=NULL;
	f->data=' ';
	f->id=temp++;
	s=f;
	for(i=2;i<=9;i++)
	{
		s->next=new node;
		s->next->prev=s;
		s->id=temp++;
		s=s->next;
		s->data=' ';
	}
	s->id=temp;
	s->next=NULL;
	h=f;
}

void Play :: display()
{
	node *q;
	int i=0;
	cout<<"  +-----+-----+-----+\n";
	for(q=h;q!=NULL;q=q->next)
	{
		if(q->data!=' ')
			cout<<"  |  "<<q->data;
		else
			cout<<"  |  "<<q->id;
		i++;
		if(i%3==0)
		{
			
			cout<<"  |\n"<<"  +-----+-----+-----+"<<"\n";
		}
	}
}

void Play :: player(int p)
{
	int loc,i=1;
	node *t;
	display();
	
	if(p==1)
		cout<<"\n\nPlayer 1 Your move: ";
	else
	if(p==2)
		cout<<"\n\nPlayer 2 Your move: ";
	
	cin>>loc;
	
	if(validate(loc))
	{
		t=h;
	
		while(i)
		{
			if(loc==t->id)
			{
				if(p==1)	
					t->data='X';
				else
				if(p==2)
					t->data='O';
				i=0;
			}
			else
				t=t->next;
		}
		system("clear");	
	}
	else
	{
		system("clear");
		cout<<"INVALID LOCATION!\nTRY AGAIN!\n\n";
		player(p);
	}
}

int Play :: validate(int l)
{
	node *t;
	if(l<1 || l>9)
		return 0;
		
	for(t=h;t->id<l;t=t->next);				//Preventing overwrite at location l
	
	if(t->data!=' ')	
		return 0;
	else
		return 1;
}

void Play :: start()
{
	system("clear");
	while(1)
	{
		player(1);
		result();
		if(istie())
		{
			display();
			cout<<"\n\nIt's A Tie!!!\n\n";
			exit(EXIT_SUCCESS);
		}
		
		player(2);
		result();
		if(istie())
		{
			display();
			cout<<"\n\nIt's A Tie!!!\n\n";
			exit(EXIT_SUCCESS);
		}
	}
}

void Play :: startAI()
{
	system("clear");
	while(1)
	{
		player(1);
		result();
		if(istie())
		{
			display();
			cout<<"\n\nIt's A Tie!!!\n\n";
			exit(EXIT_SUCCESS);
		}
		
		AImove();
		result();
		if(istie())
		{
			display();
			cout<<"\n\nIt's A Tie!!!\n\n";
			exit(EXIT_SUCCESS);
		}
	}
}

void Play :: AImove()
{
	int ailoc,i=0,r1=0,r2=0,r3=0,c1=0,c2=0,c3=0,d1=0,d2=0,ch,flag=1,f2=0;		//flag ensures only one move at a time
	node *t,*p;
	
	for(ch=1;ch<10;ch++)
	{
		switch(ch)
		{	
			case 1: if(flag)
				{				
					for(i=1,t=h;i<4;t=t->next,i++)			//1st row
					{
						if(t->data==' ')
							ailoc=t->id;
						
						else
							r1=r1+t->data;
					}
	
					if(r1==176)
					{
						for(p=h;p->id<ailoc;p=p->next);
						p->data='O';
						flag=0;
					}
					else
						f2=1;	
							
				}break;
	
			case 2: if(flag)
				{
					for(;i<7;t=t->next,i++)				//2nd row
					{
						if(t->data==' ')
							ailoc=t->id;
						
						else
							r2=r2+t->data;
					}
	
					if(r2==176)
					{
						for(p=h;p->id<ailoc;p=p->next);
						p->data='O';
						flag=0;
					}
					
					else
						f2=1;
				}break;
	
			case 3: if(flag)
				{
					for(;i<10;t=t->next,i++)			//3rd row
					{
						if(t->data==' ')
							ailoc=t->id;
						
						else
							r3=r3+t->data;
					}
	
					if(r3==176)
					{
						for(p=h;p->id<ailoc;p=p->next);
						p->data='O';
						flag=0;
					}
					
					else
						f2=1;
				}break;

			case 4: if(flag)
				{
					for(t=h;t!=NULL;t=t->next)			//1st col
					{
						if(t->id==1 || t->id==4 || t->id==7)
						{
							if(t->data==' ')
								ailoc=t->id;
							
							else
								c1=c1+t->data;
						}
					}
	
					if(c1==176)
					{
						for(p=h;p->id<ailoc;p=p->next);
						p->data='O';
						flag=0;
					}
					
					else
						f2=1;
				}break;
	
			case 5: if(flag)
				{
					for(t=h;t!=NULL;t=t->next)			//2nd col
					{
						if(t->id==2 || t->id==5 || t->id==8)
						{
							if(t->data==' ')
								ailoc=t->id;
							
							else
								c2=c2+t->data;
						}
					}
	
					if(c2==176)
					{
						for(p=h;p->id<ailoc;p=p->next);
						p->data='O';
						flag=0;
					}
					
					else
						f2=1;
				}break;
	
			case 6: if(flag)
				{
					for(t=h;t!=NULL;t=t->next)			//3rd col
					{
						if(t->id==3 || t->id==6 || t->id==9)
						{
							if(t->data==' ')
								ailoc=t->id;
							
							else
								c3=c3+t->data;
						}
					}
	
					if(c3==176)
					{
						for(p=h;p->id<ailoc;p=p->next);
						p->data='O';
						flag=0;
					}
					
					else
						f2=1;
				}break;

			case 7: if(flag)
				{
					for(t=h;t!=NULL;t=t->next)			//1st dia
					{
						if(t->id==1 || t->id==5 || t->id==9)
						{
							if(t->data==' ')
								ailoc=t->id;
							
							else
								d1=d1+t->data;
						}
					}
	
					if(d1==176)
					{
						for(p=h;p->id<ailoc;p=p->next);
						p->data='O';
						flag=0;
					}
					
					else
						f2=1;
				}break;

			case 8: if(flag)
				{
					for(t=h;t!=NULL;t=t->next)			//2nd dia
					{
						if(t->id==3 || t->id==5 || t->id==7)
						{
							if(t->data==' ')
								ailoc=t->id;
							
							else
								d2=d2+t->data;
						}
					}
	
					if(d2==176)
					{
						for(p=h;p->id<ailoc;p=p->next);
						p->data='O';
						flag=0;
					}
					
					else
						f2=1;
				}break;
				
			case 9: if(f2 && flag)						//marks O at first blank location
				{
					for(p=h;p!=NULL;p=p->next)
					{
				  		if(p->data!=' ')
				  			continue;
				  		else
							p->data='O';
						break;
					}
					flag=0;
				}break;
		}	
	}
}

void Play :: result()
{
	node *t;
	int ch,i=0,j=0,r1=0,r2=0,r3=0,c1=0,c2=0,c3=0,d1=0,d2=0;
	
	for(ch=1;ch<9;ch++)
	{
		switch(ch)
		{
			case 1: for(i=0,t=h;i<3;t=t->next,i++)			//1st row
				{
					if(t->data!=' ')
						r1=r1+t->data;
				}

				if(r1==264)
				{
					display();
					cout<<"\n\nPlayer 1 Wins\n\n";
					exit(EXIT_SUCCESS);		
				}
				else
				if(r1==237)
				{
					display();
					cout<<"\n\nPlayer 2 Wins\n\n";
					exit(EXIT_SUCCESS);
				}
				break;
			
			case 2: for(;i<6;t=t->next,i++)				//2nd row
				{
					if(t->data!=' ')
						r2=r2+t->data;
				}

				if(r2==264)
				{
					display();
					cout<<"\n\nPlayer 1 Wins\n\n";
					exit(EXIT_SUCCESS);		
				}
				else
				if(r2==237)
				{
					display();
					cout<<"\n\nPlayer 2 Wins\n\n";
					exit(EXIT_SUCCESS);
				}
				break;
				
			case 3: for(;i<9;t=t->next,i++)				//3rd row
				{
					if(t->data!=' ')
						r3=r3+t->data;
				}

				if(r3==264)
				{
					display();
					cout<<"\n\nPlayer 1 Wins\n\n";
					exit(EXIT_SUCCESS);		
				}
				else
				if(r3==237)
				{
					display();
					cout<<"\n\nPlayer 2 Wins\n\n";
					exit(EXIT_SUCCESS);
				}
				break;		
			
			case 4: for(t=h;t!=NULL;t=t->next)			//1st col
				{
					if(t->id==1 || t->id==4 || t->id==7)
						if(t->data!=' ')
							c1=c1+t->data;
				}

				if(c1==264)
				{
					display();
					cout<<"\n\nPlayer 1 Wins\n\n";
					exit(EXIT_SUCCESS);		
				}
				else
				if(c1==237)
				{
					display();
					cout<<"\n\nPlayer 2 Wins\n\n";
					exit(EXIT_SUCCESS);
				}
				break;
			
			case 5: for(t=h;t!=NULL;t=t->next)			//2nd col
				{
					if(t->id==2 || t->id==5 || t->id==8)
						if(t->data!=' ')
							c2=c2+t->data;
				}

				if(c2==264)
				{
					display();
					cout<<"\n\nPlayer 1 Wins\n\n";
					exit(EXIT_SUCCESS);		
				}
				else
				if(c2==237)
				{
					display();
					cout<<"\n\nPlayer 2 Wins\n\n";
					exit(EXIT_SUCCESS);
				}
				break;
			
			case 6: for(j=0,t=h;j<9;t=t->next,j++)			//3rd col
				{
					if(t->id==3 || t->id==6 || t->id==9)
						if(t->data!=' ')
							c3=c3+t->data;
				}

				if(c3==264)
				{
					display();
					cout<<"\n\nPlayer 1 Wins\n\n";
					exit(EXIT_SUCCESS);		
				}
				else
				if(c3==237)
				{
					display();
					cout<<"\n\nPlayer 2 Wins\n\n";
					exit(EXIT_SUCCESS);
				}
				break;		
			
			case 7: for(t=h;t!=NULL;t=t->next)			//1st dia
				{
					if(t->id==1 || t->id==5 || t->id==9)
						if(t->data!=' ')
							d1=d1+t->data;
				}

				if(d1==264)
				{
					display();
					cout<<"\n\nPlayer 1 Wins\n\n";
					exit(EXIT_SUCCESS);		
				}
				else
				if(d1==237)
				{
					display();
					cout<<"\n\nPlayer 2 Wins\n\n";
					exit(EXIT_SUCCESS);
				}
				break;
			
			case 8: for(t=h;t!=NULL;t=t->next)			//2nd dia
				{
					if(t->id==3 || t->id==5 || t->id==7)
						if(t->data!=' ')
							d2=d2+t->data;
				}

				if(d2==264)
				{
					display();
					cout<<"\n\nPlayer 1 Wins\n\n";
					exit(EXIT_SUCCESS);		
				}
				else
				if(d2==237)
				{
					display();
					cout<<"\n\nPlayer 2 Wins\n\n";
					exit(EXIT_SUCCESS);
				}
				break;
		}	
	}
}

int Play :: istie()			//returns 1 if tie (grid is full)
{
	node *t;
	int i,flag=1;
	for(i=0,t=h;i<9;t=t->next,i++)
	{
		if(t->data==' ')
			flag=0;
	}
	return flag;
}

int main()
{
	Play board;
	int ch,i,itm,p,n,ele;
	board.create();

	system("clear");
	cout<<"\t\t\t*** Tic Tac Toe ***";
	do
	{
		cout << "\n\n1.Two Player\n2.Vs CPU\n3.Exit\n\nEnter Choice: " ;
		cin >> ch;
		switch(ch)
		{		
			case 1: board.start();break;
			case 2: board.startAI();break;
		}
	}while(ch!=3);
	return 0;
}
