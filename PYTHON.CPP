#include<conio.h>
#include<graphics.h>
#include<dos.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<iomanip.h>
#include<fstream.h>
int driver=DETECT,mode,c=5,o=0,z=75,w=0,vq=0,qv=0,rm=10,xm,ym,t=0,s=0;
union REGS in,out;
char name[30]="Player";
int SETDIFFICULTY(int cas,int text);/*this function is for selecting the difficulty level*/
int MAIN();/*this function displays the start screen*/
int powda(int);/*this function generates a suitable value for the sound needed in the 'MAIN' function*/
int HIGH();/*this function is for displaying the high scores of a particular difficulty level, gives the option of deleting that datafile and calls the 'search' function*/
int NAME();/*this function reads the name of the user and accordingly calls 'SETDIFFICULTY' function*/
void search(int CASE);/*this function is for searching user's highest score from datafile*/
void file(int a);/*this function is for inserting scores in a sorted datafile*/
void INSTRUCTIONS(void);/*this function displays the instructions*/
void clrbuf(int);/*this function clears the keyboard buffer*/
void SILIPYTH(int,int,int,int,int);/*this function runs the main game*/
fstream ein,min,hin,fo;
class hscore
{
	char name[30];
	char time[9];
	char date[9];
	int score;
	int diff;

	public:

	void indata(char* n="Player",int s=0)
	{
		_strtime(time);
		_strdate(date);
		score=s;
		diff=::t;
		strcpy(name,n);

	}
	void output(int a=1)
	{
		setcolor(YELLOW);
		settextstyle(0,0,0);
		settextjustify(LEFT_TEXT,CENTER_TEXT);
		outtextxy(72,152+(a*16),"|");
		gotoxy(13,10+a);
		cout<<name;
		outtextxy(312,152+(a*16),"|");
		gotoxy(44,10+a);
		cout<<score;
		outtextxy(384,152+(a*16),"|");
		gotoxy(51,10+a);
		cout<<time;
		outtextxy(472,152+(a*16),"|");
		gotoxy(62,10+a);
		cout<<date;
		outtextxy(560,152+(a*16),"|");
	}
	int getscore()
	{
		return score;
	}
	void putdiff(int d)
	{
		diff=d;
	}
	char* getname()
	{
		return name;
	}
	char* gettime()
	{
		return time;
	}
	char* getdate()
	{
		return date;
	}
}hs;
hscore s1;
void clrbuf(int it)
{
	for(int i=0;i<=it;i++)
	{
		if(kbhit())
		{
			getch();
		}
	}
}
void INSTRUCTIONS(void)
{
	clrscr();
	cleardevice();
	int e=72;
	rm=10;
	setbkcolor(BLACK);
	while(e!=13)
	{
		in.x.ax=3;
		int86(51,&in,&out);
		if(out.x.bx==1)
		{
			if(rm!=0)
			{
				cout<<" ";
			}
			else
			{
				e=13;
			}
		}
		if(rm!=0)
		{
			rm--;
		}
		setcolor(RED);
		settextstyle(4,0,9);
		settextjustify(CENTER_TEXT,CENTER_TEXT);
		outtextxy(getmaxx()/2,50,"PYTHON");
		if(kbhit())
		{
			e=getch();
		}
		setcolor(WHITE);
		settextstyle(0,0,0);
		settextjustify(LEFT_TEXT,CENTER_TEXT);
		outtextxy(0,150,"   The PYTHON is controlled by ARROW KEYS");
		outtextxy(0,180,"   The USER will get 1 point for each egg the PYTHON engulfs");
		outtextxy(0,210,"   Every 5th egg is a BONUS EGG for which the USER will get a maximum of");
		outtextxy(0,230,"   10 points which will decrease with time accordingly");
		outtextxy(0,260,"   If in any case the egg is NOT VISIBLE, patiently wait as the egg could be");
		outtextxy(0,280,"   somewhere beneath the PYTHON");
		outtextxy(0,310,"   To UNLOCK medium & hard levels, SCORE 200 in easy & 100 in medium level");
		outtextxy(0,340,"   PYTHON has 3 LIVES");
		outtextxy(0,390,"   This PROJECT is registered under the name of GHAPLACORP RTM");
		outtextxy(0,410,"   Any ILLEGAL OPERATION or attempt to SABOTAGE the data will be dealt ");
		outtextxy(0,430,"   strictly and the user will be liable to CRIMINAL PROSECUTION");
		outtextxy(0,458,"                                         T.Kapilesh");
		setcolor(RED);
		outtextxy(0,150," *");
		outtextxy(0,180," *");
		outtextxy(0,210," *");
		outtextxy(0,260," *");
		outtextxy(0,310," *");
		outtextxy(0,340," *");
		setcolor(BLUE);
		rectangle(10,360,getmaxx()-10,getmaxy()-8);
		setcolor(YELLOW);
		outtextxy(0,458,"                            Designed By:");
		settextstyle(0,0,0);
		settextjustify(CENTER_TEXT,CENTER_TEXT);
		outtextxy(getmaxx()/2,370,"ABOUT");
	}
}
int powda(int da)
{
	return 2*da*da*da*da*da+da;
}
int MAIN()
{
	clrscr();
	cleardevice();
	int d=77,s=20,p=5,c=0;
	setbkcolor(BLACK);
	setcolor(RED);
	settextstyle(4,0,10);
	settextjustify(CENTER_TEXT,CENTER_TEXT);
	outtextxy(getmaxx()/2,getmaxy()/2,"PYTHON");
	int x[20]={50,40,30,20,10};
	int y[20]={10,10,10,10,10};
	while(p!=400)
	{
		p++;
		sound(1000+4*powda(p));
		setcolor(YELLOW);
		setfillstyle(SOLID_FILL,RED);
		for(int i=0;i<s;i++)
		{
			circle(x[i],y[i],5);
			floodfill(x[i],y[i],YELLOW);
		}
		setfillstyle(CLOSE_DOT_FILL,RED);
		circle(x[0],y[0],5);
		floodfill(x[0],y[0],YELLOW);
		delay(15);
		setfillstyle(SOLID_FILL,BLACK);
		floodfill(x[s-1],y[s-1],YELLOW);
		setfillstyle(SOLID_FILL,BLACK);
		floodfill(0,0,BLACK);
		setcolor(BLACK);
		circle(x[s-1],y[s-1],5);
		for(i=s-1;i>0;i--)
		{
			x[i]=x[i-1];
			y[i]=y[i-1];
		}
		if(p%8==0)
		{
			if(d==77)
			{
				d=80;
			}
			else
			{
				d=77;
			}
		}
		switch(d)
		{
			case 77:
			x[0]+=10;
			break;

			case 80:
			y[0]+=10;
			break;
		}
		if((d==77)&&(x[0]==getmaxx()-9))
		{
			x[0]=10;
		}
		if((d==80)&&(y[0]==getmaxy()-9))
		{
			y[0]=10;
		}
		if((d==77)&&(x[0]==50)&&((y[0]>=210)&&(y[0]<=getmaxy()-139)))
		{
			x[0]=getmaxx()-49;
		}
		if((d==80)&&(y[0]==210)&&((x[0]>=50)&&(x[0]<=getmaxx()-49)))
		{
			y[0]=getmaxy()-139;
		}
	}
	clrscr();
	cleardevice();
	nosound();
	settextjustify(CENTER_TEXT,CENTER_TEXT);
	setcolor(DARKGRAY);
	rectangle(208,getmaxy()-100,getmaxx()-229,getmaxy()-86);
	settextstyle(2,0,10);
	for(int i=0;i<5;i++)
	{
		setcolor(BLACK);
		outtextxy(getmaxx()/2,getmaxy()/2,"Loading...");
		c++;
		setcolor(RED);
		setfillstyle(SOLID_FILL,RED);
		rectangle(200+(c*10),getmaxy()-98,208+(c*10),getmaxy()-88);
		floodfill(201+(c*10),getmaxy()-97,RED);
		delay(100);
		setcolor(DARKGRAY);
		outtextxy(getmaxx()/2,getmaxy()/2,"Loading...");
		delay(100);
		setcolor(LIGHTGRAY);
		outtextxy(getmaxx()/2,getmaxy()/2,"Loading...");
		c++;
		setcolor(RED);
		setfillstyle(SOLID_FILL,RED);
		rectangle(200+(c*10),getmaxy()-98,208+(c*10),getmaxy()-88);
		floodfill(201+(c*10),getmaxy()-97,RED);
		delay(100);
		setcolor(WHITE);
		outtextxy(getmaxx()/2,getmaxy()/2,"Loading...");
		delay(100);
		setcolor(LIGHTGRAY);
		outtextxy(getmaxx()/2,getmaxy()/2,"Loading...");
		c++;
		setcolor(RED);
		setfillstyle(SOLID_FILL,RED);
		rectangle(200+(c*10),getmaxy()-98,208+(c*10),getmaxy()-88);
		floodfill(201+(c*10),getmaxy()-97,RED);
		delay(100);
		setcolor(DARKGRAY);
		outtextxy(getmaxx()/2,getmaxy()/2,"Loading...");
		delay(100);
		setcolor(BLACK);
		outtextxy(getmaxx()/2,getmaxy()/2,"Loading...");
		c++;
		setcolor(RED);
		setfillstyle(SOLID_FILL,RED);
		rectangle(200+(c*10),getmaxy()-98,208+(c*10),getmaxy()-88);
		floodfill(201+(c*10),getmaxy()-97,RED);
		delay(100);
	}
	nosound();
	clrscr();
	cleardevice();
	clrbuf(500);
	return 0;
}
void search(int CASE)
{
	int found=0;
	switch(CASE)
	{
		case 0:
		ein.open("Easy.GDC",ios::in);
		gotoxy(1,23);
		cout<<"Enter Your NAME to search your highest score :"<<endl;
		gets(::name);
		ein.seekg(0);
		ein.read((char*)&hs,sizeof(hs));
		while(!ein.eof()&&hs.getscore()!=0)
		{
			if(strcmpi(::name,hs.getname())==0)
			{
				found=1;
				break;
			}
			else
				found=0;
			ein.read((char*)&hs,sizeof(hs));
		}
		if(found==1)
		{
			cout<<"Name : "<<hs.getname()<<endl;
			cout<<"Score : "<<hs.getscore()<<endl;
			cout<<"Date : "<<hs.getdate()<<endl;
			cout<<"Time : "<<hs.gettime()<<endl;
		}
		else
		{
			cout<<endl<<"You have not yet played this Difficulty level!!"<<endl;
		}
		ein.close();
		break;

		case 1:
		min.open("Med.GDC",ios::in);
		gotoxy(1,23);
		cout<<"Enter Your NAME to search your highest score :"<<endl;
		gets(::name);
		min.seekg(0);
		min.read((char*)&hs,sizeof(hs));
		while(!min.eof()&&hs.getscore()!=0)
		{
			if(strcmpi(::name,hs.getname())==0)
			{
				found=1;
				break;
			}
			else
				found=0;
			min.read((char*)&hs,sizeof(hs));
		}
		if(found==1)
		{
			cout<<"Name : "<<hs.getname()<<endl;
			cout<<"Score : "<<hs.getscore()<<endl;
			cout<<"Date : "<<hs.getdate()<<endl;
			cout<<"Time : "<<hs.gettime()<<endl;
		}
		else
		{
			cout<<endl<<"You have not yet played this Difficulty level!!"<<endl;
		}
		min.close();
		break;

		case 2:
		hin.open("Hard.GDC",ios::in);
		gotoxy(1,23);
		cout<<"Enter Your NAME to search your highest score :"<<endl;
		gets(::name);
		hin.seekg(0);
		hin.read((char*)&hs,sizeof(hs));
		while(!hin.eof()&&hs.getscore()!=0)
		{
			if(strcmpi(::name,hs.getname())==0)
			{
				found=1;
				break;
			}
			else
				found=0;
			hin.read((char*)&hs,sizeof(hs));
		}
		if(found==1)
		{
			cout<<"Name : "<<hs.getname()<<endl;
			cout<<"Score : "<<hs.getscore()<<endl;
			cout<<"Date : "<<hs.getdate()<<endl;
			cout<<"Time : "<<hs.gettime()<<endl;
		}
		else
		{
			cout<<endl<<"You have not yet played this Difficulty level!!"<<endl;
		}
		hin.close();
		break;
	}
	getch();
}
int HIGH()
{
	start1:
	::t=SETDIFFICULTY(2,2);
	clrscr();
	cleardevice();
	start2:
	int c=1,found=0,key=77,xu,yu;
	setcolor(RED);
	settextstyle(4,0,9);
	settextjustify(CENTER_TEXT,CENTER_TEXT);
	outtextxy(getmaxx()/2,50,"PYTHON");
	setcolor(LIGHTBLUE);
	settextstyle(0,0,0);
	settextjustify(LEFT_TEXT,CENTER_TEXT);
	outtextxy(72,152,"|                             |");
	setcolor(LIGHTBLUE);
	outtextxy(384,152,"|");
	outtextxy(472,152,"|");
	outtextxy(560,152,"|");
	setcolor(CYAN);
	outtextxy(180,152,"Name");
	outtextxy(332,152,"Score");
	outtextxy(416,152,"Time");
	outtextxy(504,152,"Date");
	setcolor(BROWN);
	setlinestyle(DASHED_LINE,0,1);
	line(70,157,568,157);
	gotoxy(35,9);
	cout<<" HIGH SCORES ";
	switch(::t)
	{
		case 0:
		ein.open("Easy.GDC",ios::in);
		c=1;
		ein.seekg(0);
		ein.read((char*)&s1,sizeof(s1));
		while((!ein.eof())&&(c!=11)&&(s1.getscore()!=0))
		{
			s1.output(c);
			c++;
			ein.read((char*)&s1,sizeof(s1));
		}
		setlinestyle(SOLID_LINE,0,1);
		setcolor(DARKGRAY);
		rectangle(70,136,568,152+((c*16)+10));
		setcolor(LIGHTGRAY);
		rectangle(69,135,569,152+((c*16)+11));
		setcolor(DARKGRAY);
		rectangle(68,134,570,152+((c*16)+12));
		gotoxy(35,9);
		cout<<" HIGH SCORES ";
		ein.close();
		setcolor(LIGHTBLUE);
		outtextxy(1,getmaxy()-116,"Press DELETE to        the existing scores");
		outtextxy(1,getmaxy()-100,"Press F4 to        your highest score from the existing scores");
		outtextxy(1,getmaxy()-84,"Press HOME to exit to");
		setcolor(DARKGRAY);
		outtextxy(1,getmaxy()-116,"                DELETE");
		outtextxy(1,getmaxy()-100,"            SEARCH");
		outtextxy(1,getmaxy()-84,"                      PREVIOUS MENU");
		int gu;
		while(key==77)
		{
			in.x.ax=3;
			int86(51,&in,&out);
			xu=out.x.cx;
			yu=out.x.dx;
			gu=0;
			if((xu>=126)&&(xu<=178)&&(yu>=getmaxy()-123)&&(yu<=getmaxy()-111))
			{
				if(out.x.bx==1)
				{
					key=83;
					goto ju;
				}
				setcolor(WHITE);
				outtextxy(1,getmaxy()-116,"                DELETE");
				gu=1;
			}
			if(gu==0)
			{
				setcolor(DARKGRAY);
				outtextxy(1,getmaxy()-116,"                DELETE");
			}
			gu=0;
			if((xu>=94)&&(xu<=146)&&(yu>=getmaxy()-107)&&(yu<=getmaxy()-95))
			{
				if(out.x.bx==1)
				{
					key=62;
					goto ju;
				}
				setcolor(WHITE);
				outtextxy(1,getmaxy()-100,"            SEARCH");
				gu=1;
			}
			if(gu==0)
			{
				setcolor(DARKGRAY);
				outtextxy(1,getmaxy()-100,"            SEARCH");
			}
			gu=0;
			if((xu>=174)&&(xu<=282)&&(yu>=getmaxy()-91)&&(yu<=getmaxy()-71))
			{
				if(out.x.bx)
				{
					key=71;
					goto ju;
				}
				setcolor(WHITE);
				outtextxy(1,getmaxy()-84,"                      PREVIOUS MENU");
				gu=1;
			}
			if(gu==0)
			{
				setcolor(DARKGRAY);
				outtextxy(1,getmaxy()-84,"                      PREVIOUS MENU");
			}
			if(kbhit())
			{
				key=getch();
			}
		}
		key=getch();
		ju:
		if(key==83)
		{
			ein.open("Easy.GDC",ios::in);
			ein.read((char*)&hs,sizeof(hs));
			while(!ein.eof())
			{
				if(hs.getscore()==0)
				{
					found=1;
					break;
				}
				else
					found=0;
				ein.read((char*)&s,sizeof(s));
			}
			if(found==0)
			{
				ein.close();
				remove("Easy.GDC");
				ein.open("Easy.GDC",ios::out);
				hs.indata();
				ein.write((char*)&hs,sizeof(hs));
				setcolor(BROWN);
				settextjustify(CENTER_TEXT,CENTER_TEXT);
				outtextxy(getmaxx()/2,getmaxy()-52,"DELETED SUCCESSFULLY");
				delay(1000);
				setcolor(BLACK);
				outtextxy(getmaxx()/2,getmaxy()-52,"DELETED SUCCESSFULLY");
				ein.close();
				clrscr();
				cleardevice();
				goto start2;
			}
			else if(found==1)
			{
				ein.close();
				setcolor(BROWN);
				settextjustify(CENTER_TEXT,CENTER_TEXT);
				outtextxy(getmaxx()/2,getmaxy()-52,"NOTHING TO DELETE");
				delay(1000);
				outtextxy(getmaxx()/2,getmaxy()-52,"NOTHING TO DELETE");
				clrscr();
				cleardevice();
				goto start2;
			}
		}
		else if(key==62)
		{
			setcolor(BLACK);
			outtextxy(1,getmaxy()-116,"Press DELETE to DELETE the existing scores");
			outtextxy(1,getmaxy()-100,"Press F4 to SEARCH your highest score from the existing scores");
			outtextxy(1,getmaxy()-84,"Press HOME to exit to PREVIOUS MENU");
			search(0);
			clrscr();
			cleardevice();
			goto start2;
		}
		else if(key==71)
		{
			goto start1;
		}
		break;

		case 1:
		c=1;
		min.open("Med.GDC",ios::in);
		min.seekg(0);
		min.read((char*)&s1,sizeof(s1));
		while((!min.eof())&&(c!=11)&&(s1.getscore()!=0))
		{
			s1.output(c);
			c++;
			min.read((char*)&s1,sizeof(s1));
		}
		setlinestyle(SOLID_LINE,0,1);
		setcolor(DARKGRAY);
		rectangle(70,136,568,152+((c*16)+10));
		setcolor(LIGHTGRAY);
		rectangle(69,135,569,152+((c*16)+11));
		setcolor(DARKGRAY);
		rectangle(68,134,570,152+((c*16)+12));
		gotoxy(35,9);
		cout<<" HIGH SCORES ";
		min.close();
		setcolor(LIGHTBLUE);
		outtextxy(1,getmaxy()-116,"Press DELETE to        the existing scores");
		outtextxy(1,getmaxy()-100,"Press F4 to        your highest score from the existing scores");
		outtextxy(1,getmaxy()-84,"Press HOME to exit to");
		setcolor(DARKGRAY);
		outtextxy(1,getmaxy()-116,"                DELETE");
		outtextxy(1,getmaxy()-100,"            SEARCH");
		outtextxy(1,getmaxy()-84,"                      PREVIOUS MENU");
		while(key==77)
		{
			in.x.ax=3;
			int86(51,&in,&out);
			xu=out.x.cx;
			yu=out.x.dx;
			gu=0;
			if((xu>=126)&&(xu<=178)&&(yu>=getmaxy()-123)&&(yu<=getmaxy()-111))
			{
				if(out.x.bx==1)
				{
					key=83;
					goto ku;
				}
				setcolor(WHITE);
				outtextxy(1,getmaxy()-116,"                DELETE");
				gu=1;
			}
			if(gu==0)
			{
				setcolor(DARKGRAY);
				outtextxy(1,getmaxy()-116,"                DELETE");
			}
			gu=0;
			if((xu>=94)&&(xu<=146)&&(yu>=getmaxy()-107)&&(yu<=getmaxy()-95))
			{
				if(out.x.bx==1)
				{
					key=62;
					goto ku;
				}
				setcolor(WHITE);
				outtextxy(1,getmaxy()-100,"            SEARCH");
				gu=1;
			}
			if(gu==0)
			{
				setcolor(DARKGRAY);
				outtextxy(1,getmaxy()-100,"            SEARCH");
			}
			gu=0;
			if((xu>=174)&&(xu<=282)&&(yu>=getmaxy()-91)&&(yu<=getmaxy()-71))
			{
				if(out.x.bx)
				{
					key=71;
					goto ku;
				}
				setcolor(WHITE);
				outtextxy(1,getmaxy()-84,"                      PREVIOUS MENU");
				gu=1;
			}
			if(gu==0)
			{
				setcolor(DARKGRAY);
				outtextxy(1,getmaxy()-84,"                      PREVIOUS MENU");
			}
			if(kbhit())
			{
				key=getch();
			}
		}
		key=getch();
		ku:
		if(key==83)
		{
			min.open("Med.GDC",ios::in);
			min.read((char*)&hs,sizeof(hs));
			while(!min.eof())
			{
				if(hs.getscore()==0)
				{
					found=1;
					break;
				}
				else
					found=0;
				min.read((char*)&s,sizeof(s));
			}
			if(found==0)
			{
				min.close();
				remove("Med.GDC");
				min.open("Med.GDC",ios::out);
				hs.indata();
				min.write((char*)&hs,sizeof(hs));
				setcolor(BROWN);
				settextjustify(CENTER_TEXT,CENTER_TEXT);
				outtextxy(getmaxx()/2,getmaxy()-52,"DELETED SUCCESSFULLY");
				delay(1000);
				setcolor(BLACK);
				outtextxy(getmaxx()/2,getmaxy()-52,"DELETED SUCCESSFULLY");
				min.close();
				clrscr();
				cleardevice();
				goto start2;
			}
			else if(found==1)
			{
				min.close();
				setcolor(BROWN);
				settextjustify(CENTER_TEXT,CENTER_TEXT);
				outtextxy(getmaxx()/2,getmaxy()-52,"NOTHING TO DELETE");
				delay(1000);
				outtextxy(getmaxx()/2,getmaxy()-52,"NOTHING TO DELETE");
				clrscr();
				cleardevice();
				goto start2;
			}
		}
		else if(key==62)
		{
			setcolor(BLACK);
			outtextxy(1,getmaxy()-116,"Press DELETE to DELETE the existing scores");
			outtextxy(1,getmaxy()-100,"Press F4 to SEARCH your highest score from the existing scores");
			outtextxy(1,getmaxy()-84,"Press HOME to exit to PREVIOUS MENU");
			search(1);
			clrscr();
			cleardevice();
			goto start2;
		}
		else if(key==71)
		{
			goto start1;
		}
		break;

		case 2:
		c=1;
		hin.open("Hard.GDC",ios::in);
		hin.seekg(0);
		hin.read((char*)&s1,sizeof(s1));
		while((!hin.eof())&&(c!=11)&&(s1.getscore()!=0))
		{
			s1.output(c);
			c++;
			hin.read((char*)&s1,sizeof(s1));
		}
		setlinestyle(SOLID_LINE,0,1);
		setcolor(DARKGRAY);
		rectangle(70,136,568,152+((c*16)+10));
		setcolor(LIGHTGRAY);
		rectangle(69,135,569,152+((c*16)+11));
		setcolor(DARKGRAY);
		rectangle(68,134,570,152+((c*16)+12));
		gotoxy(35,9);
		cout<<" HIGH SCORES ";
		hin.close();
		setcolor(LIGHTBLUE);
		outtextxy(1,getmaxy()-116,"Press DELETE to        the existing scores");
		outtextxy(1,getmaxy()-100,"Press F4 to        your highest score from the existing scores");
		outtextxy(1,getmaxy()-84,"Press HOME to exit to");
		setcolor(DARKGRAY);
		outtextxy(1,getmaxy()-116,"                DELETE");
		outtextxy(1,getmaxy()-100,"            SEARCH");
		outtextxy(1,getmaxy()-84,"                      PREVIOUS MENU");
		while(key==77)
		{
			in.x.ax=3;
			int86(51,&in,&out);
			xu=out.x.cx;
			yu=out.x.dx;
			gu=0;
			if((xu>=126)&&(xu<=178)&&(yu>=getmaxy()-123)&&(yu<=getmaxy()-111))
			{
				if(out.x.bx==1)
				{
					key=83;
					goto lu;
				}
				setcolor(WHITE);
				outtextxy(1,getmaxy()-116,"                DELETE");
				gu=1;
			}
			if(gu==0)
			{
				setcolor(DARKGRAY);
				outtextxy(1,getmaxy()-116,"                DELETE");
			}
			gu=0;
			if((xu>=94)&&(xu<=146)&&(yu>=getmaxy()-107)&&(yu<=getmaxy()-95))
			{
				if(out.x.bx==1)
				{
					key=62;
					goto lu;
				}
				setcolor(WHITE);
				outtextxy(1,getmaxy()-100,"            SEARCH");
				gu=1;
			}
			if(gu==0)
			{
				setcolor(DARKGRAY);
				outtextxy(1,getmaxy()-100,"            SEARCH");
			}
			gu=0;
			if((xu>=174)&&(xu<=282)&&(yu>=getmaxy()-91)&&(yu<=getmaxy()-71))
			{
				if(out.x.bx)
				{
					key=71;
					goto lu;
				}
				setcolor(WHITE);
				outtextxy(1,getmaxy()-84,"                      PREVIOUS MENU");
				gu=1;
			}
			if(gu==0)
			{
				setcolor(DARKGRAY);
				outtextxy(1,getmaxy()-84,"                      PREVIOUS MENU");
			}
			if(kbhit())
			{
				key=getch();
			}
		}
		key=getch();
		lu:
		if(key==83)
		{
			hin.open("Hard.GDC",ios::in);
			hin.read((char*)&hs,sizeof(hs));
			while(!hin.eof())
			{
				if(hs.getscore()==0)
				{
					found=1;
					break;
				}
				else
					found=0;
				hin.read((char*)&s,sizeof(s));
			}
			if(found==0)
			{
				hin.close();
				remove("Hard.GDC");
				hin.open("Hard.GDC",ios::out);
				hs.indata();
				hin.write((char*)&hs,sizeof(hs));
				setcolor(BROWN);
				settextjustify(CENTER_TEXT,CENTER_TEXT);
				outtextxy(getmaxx()/2,getmaxy()-52,"DELETED SUCCESSFULLY");
				delay(1000);
				setcolor(BLACK);
				outtextxy(getmaxx()/2,getmaxy()-52,"DELETED SUCCESSFULLY");
				hin.close();
				clrscr();
				cleardevice();
				goto start2;
			}
			else if(found==1)
			{
				hin.close();
				setcolor(BROWN);
				settextjustify(CENTER_TEXT,CENTER_TEXT);
				outtextxy(getmaxx()/2,getmaxy()-52,"NOTHING TO DELETE");
				delay(1000);
				outtextxy(getmaxx()/2,getmaxy()-52,"NOTHING TO DELETE");
				clrscr();
				cleardevice();
				goto start2;
			}
		}
		else if(key==62)
		{
			setcolor(BLACK);
			outtextxy(1,getmaxy()-116,"Press DELETE to DELETE the existing scores");
			outtextxy(1,getmaxy()-100,"Press F4 to SEARCH your highest score from the existing scores");
			outtextxy(1,getmaxy()-84,"Press HOME to exit to PREVIOUS MENU");
			search(2);
			clrscr();
			cleardevice();
			goto start2;
		}
		else if(key==71)
		{
			goto start1;
		}
		break;

		case 3:
		settextjustify(CENTER_TEXT,CENTER_TEXT);
		setlinestyle(SOLID_LINE,0,1);
		return 0;
	}
	getch();
	settextjustify(CENTER_TEXT,CENTER_TEXT);
	setlinestyle(SOLID_LINE,0,1);
	clrscr();
	cleardevice();
	return 0;
}
int NAME()
{
	clrscr();
	cleardevice();
	int found=0,foundm=0;
	hscore s;
	setbkcolor(BLACK);
	settextjustify(CENTER_TEXT,CENTER_TEXT);
	setcolor(RED);
	cout<<setw(912)<<"Max 26 characters : ";
	settextstyle(4,0,9);
	outtextxy(getmaxx()/2,50,"PYTHON");
	setcolor(BROWN);
	settextstyle(5,0,5);
	outtextxy(getmaxx()/2,130,"Enter Your Name");
	gets(::name);
	if(::name[0]=='\0')
	{
		strcpy(::name,"Player");
	}
	ein.open("Easy.GDC",ios::in|ios::binary);
	min.open("Med.GDC",ios::in|ios::binary);
	ein.seekg(0);
	min.seekg(0);
	ein.read((char*)&s1,sizeof(s1));
	while(!ein.eof())
	{
		if(stricmp(::name,s1.getname())==0)
		{
			found=1;
			break;
		}
		else
			found=0;
		ein.read((char*)&s1,sizeof(s1));
	}
	if(found==1)
	{
		if(s1.getscore()>199)
		{
			min.read((char*)&s,sizeof(s));
			while(!min.eof())
			{
				if(stricmp(::name,s.getname())==0)
				{
					foundm=1;
					break;
				}
				else
					foundm=0;
				min.read((char*)&s,sizeof(s));
			}
			if(foundm==1)
			{
				if(s.getscore()>99)
				{
					::t=SETDIFFICULTY(2,1);
				}
				else
				{
					::t=SETDIFFICULTY(1,1);
				}
			}
			else if(foundm==0)
			{
				::t=SETDIFFICULTY(1,1);
			}
		}
		else
		{
			::t=SETDIFFICULTY(0,1);
		}
	}
	else if(found==0)
	{
		::t=SETDIFFICULTY(0,1);
	}
	ein.close();
	min.close();
	return 0;
}
int SETDIFFICULTY(int cas=0,int text=1)
{
	clrscr();
	cleardevice();
	int e=72,f=1;
	rm=10;
	in.x.ax=0;
	int86(51,&in,&out);
	in.x.ax=4;
	in.x.bx=2;
	in.x.cx=xm;
	in.x.dx=ym;
	int86(51,&in,&out);
	setbkcolor(BLACK);
	switch(text)
	{
		case 1:
		switch(cas)
		{
			case 0:
			while(e!=79)
			{
				in.x.ax=0;
				int86(55,&in,&out);
				in.x.ax=1;
				int86(51,&in,&out);
				in.x.ax=3;
				int86(51,&in,&out);
				xm=out.x.cx;
				ym=out.x.dx;
				if(rm!=0)
				{
					rm--;
				}
				setcolor(RED);
				settextstyle(4,0,9);
				settextjustify(CENTER_TEXT,CENTER_TEXT);
				outtextxy(getmaxx()/2,50,"PYTHON");
				setcolor(BROWN);
				settextstyle(5,0,5);
				settextjustify(CENTER_TEXT,CENTER_TEXT);
				outtextxy(getmaxx()/2,140,"Set Difficulty Level");
				if(kbhit())
				{
					e=getch();
					if((e==72)&&(f==4))
					{
						e=0;
						f=1;
					}
					if((e==80)&&(f==1))
					{
						e=0;
						f=4;
					}
				}
				setcolor(BLUE);
				if((((e==72)&&(f==4))||(f==1))||((xm>=170)&&(xm<=460)&&(ym>=185)&&(ym<=230)))
				{
					if((xm>=170)&&(xm<=460)&&(ym>=185)&&(ym<=230))
					{
						if(out.x.bx==1)
						{
							if(rm!=0)
							{
								cout<<" ";
							}
							else
							{
								e=13;
							}
						}
						if(e!=13)
						{
							e=0;
							f=1;
						}
					}
					if(e==13)
					{
						return 0;
					}
					setcolor(GREEN);
					circle(50,210,5);
					circle(getmaxx()-50,210,5);
					setcolor(BLACK);
					settextstyle(3,0,5);
					outtextxy(getmaxx()/2,200,"Easy");
					setcolor(BLUE);
					settextstyle(3,0,6);
				}
				else
				{
					setcolor(BLACK);
					circle(50,210,5);
					circle(getmaxx()-50,210,5);
					setcolor(BLACK);
					settextstyle(3,0,6);
					outtextxy(getmaxx()/2,200,"Easy");
					setcolor(DARKGRAY);
					settextstyle(3,0,5);
				}
				outtextxy(getmaxx()/2,200,"Easy");
				setcolor(DARKGRAY);
				settextstyle(3,0,5);
				outtextxy(getmaxx()/2,275,"Medium");
				setcolor(DARKGRAY);
				settextstyle(3,0,5);
				outtextxy(getmaxx()/2,350,"Hard");
				if((((e==80)&&(f==1))||(f==4))||((xm>=170)&&(xm<=460)&&(ym>=410)&&(ym<=455)))
				{
					if((xm>=170)&&(xm<=460)&&(ym>=410)&&(ym<=455))
					{
						if(out.x.bx==1)
						{
							if(rm!=0)
							{
								cout<<" ";
							}
							else
							{
								e=13;
							}
						}
						if(e!=13)
						{
							e=0;
							f=4;
						}
					}
					if(e==13)
					{
						return 3;
					}
					setcolor(GREEN);
					circle(50,435,5);
					circle(getmaxx()-50,435,5);
					setcolor(BLACK);
					settextstyle(3,0,5);
					outtextxy(getmaxx()/2,425,"Previous Menu");
					setcolor(WHITE);
					settextstyle(3,0,6);
				}
				else
				{
					setcolor(BLACK);
					circle(50,435,5);
					circle(getmaxx()-50,435,5);
					setcolor(BLACK);
					settextstyle(3,0,6);
					outtextxy(getmaxx()/2,425,"Previous Menu");
					setcolor(LIGHTGRAY);
					settextstyle(3,0,5);
				}
				outtextxy(getmaxx()/2,425,"Previous Menu");
			}
			break;

			case 1:
			while(e!=79)
			{
				in.x.ax=0;
				int86(55,&in,&out);
				in.x.ax=1;
				int86(51,&in,&out);
				in.x.ax=3;
				int86(51,&in,&out);
				xm=out.x.cx;
				ym=out.x.dx;
				if(rm!=0)
				{
					rm--;
				}
				setcolor(RED);
				settextstyle(4,0,9);
				settextjustify(CENTER_TEXT,CENTER_TEXT);
				outtextxy(getmaxx()/2,50,"PYTHON");
				setcolor(BROWN);
				settextstyle(5,0,5);
				settextjustify(CENTER_TEXT,CENTER_TEXT);
				outtextxy(getmaxx()/2,140,"Set Difficulty Level");
				if(kbhit())
				{
					e=getch();
					if((e==72)&&(f==2))
					{
						e=0;
						f=1;
					}
					if(((e==80)&&(f==1))||((e==72)&&(f==4)))
					{
						e=0;
						f=2;
					}
					if((e==80)&&(f==2))
					{
						e=0;
						f=4;
					}
				}
				setcolor(BLUE);
				if((((e==72)&&(f==2))||(f==1))||((xm>=170)&&(xm<=460)&&(ym>=185)&&(ym<=230)))
				{
					if((xm>=170)&&(xm<=460)&&(ym>=185)&&(ym<=230))
					{
						if(out.x.bx==1)
						{
							if(rm!=0)
							{
								cout<<" ";
							}
							else
							{
								e=13;
							}
						}
						if(e!=13)
						{
							e=0;
							f=1;
						}
					}
					if(e==13)
					{
						return 0;
					}
					setcolor(GREEN);
					circle(50,210,5);
					circle(getmaxx()-50,210,5);
					setcolor(BLACK);
					settextstyle(3,0,5);
					outtextxy(getmaxx()/2,200,"Easy");
					setcolor(BLUE);
					settextstyle(3,0,6);
				}
				else
				{
					setcolor(BLACK);
					circle(50,210,5);
					circle(getmaxx()-50,210,5);
					setcolor(BLACK);
					settextstyle(3,0,6);
					outtextxy(getmaxx()/2,200,"Easy");
					setcolor(DARKGRAY);
					settextstyle(3,0,5);
				}
				outtextxy(getmaxx()/2,200,"Easy");
				if((((e==80)&&(f==1))||((e==72)&&(f==4))||(f==2))||((xm>=170)&&(xm<=460)&&(ym>=260)&&(ym<=315)))
				{
					if((xm>=170)&&(xm<=460)&&(ym>=260)&&(ym<=315))
					{
						if(out.x.bx==1)
						{
							if(rm!=0)
							{
								cout<<" ";
							}
							else
							{
								e=13;
							}
						}
						if(e!=13)
						{
							e=0;
							f=2;
						}
					}
					if(e==13)
					{
						return 1;
					}
					setcolor(GREEN);
					circle(50,285,5);
					circle(getmaxx()-50,285,5);
					setcolor(BLACK);
					settextstyle(3,0,5);
					outtextxy(getmaxx()/2,275,"Medium");
					setcolor(BLUE);
					settextstyle(3,0,6);
				}
				else
				{
					setcolor(BLACK);
					circle(50,285,5);
					circle(getmaxx()-50,285,5);
					setcolor(BLACK);
					settextstyle(3,0,6);
					outtextxy(getmaxx()/2,275,"Medium");
					setcolor(DARKGRAY);
					settextstyle(3,0,5);
				}
				outtextxy(getmaxx()/2,275,"Medium");
				setcolor(DARKGRAY);
				settextstyle(3,0,5);
				outtextxy(getmaxx()/2,350,"Hard");
				if((((e==80)&&(f==2))||(f==4))||((xm>=170)&&(xm<=460)&&(ym>=410)&&(ym<=455)))
				{
					if((xm>=170)&&(xm<=460)&&(ym>=410)&&(ym<=455))
					{
						if(out.x.bx==1)
						{
							if(rm!=0)
							{
								cout<<" ";
							}
							else
							{
								e=13;
							}
						}
						if(e!=13)
						{
							e=0;
							f=4;
						}
					}
					if(e==13)
					{
						return 3;
					}
					setcolor(GREEN);
					circle(50,435,5);
					circle(getmaxx()-50,435,5);
					setcolor(BLACK);
					settextstyle(3,0,5);
					outtextxy(getmaxx()/2,425,"Previous Menu");
					setcolor(WHITE);
					settextstyle(3,0,6);
				}
				else
				{
					setcolor(BLACK);
					circle(50,435,5);
					circle(getmaxx()-50,435,5);
					setcolor(BLACK);
					settextstyle(3,0,6);
					outtextxy(getmaxx()/2,425,"Previous Menu");
					setcolor(LIGHTGRAY);
					settextstyle(3,0,5);
				}
				outtextxy(getmaxx()/2,425,"Previous Menu");
			}
			break;

			case 2:
			while(e!=79)
			{
				in.x.ax=0;
				int86(55,&in,&out);
				in.x.ax=1;
				int86(51,&in,&out);
				in.x.ax=3;
				int86(51,&in,&out);
				xm=out.x.cx;
				ym=out.x.dx;
				if(rm!=0)
				{
					rm--;
				}
				setcolor(RED);
				settextstyle(4,0,9);
				settextjustify(CENTER_TEXT,CENTER_TEXT);
				outtextxy(getmaxx()/2,50,"PYTHON");
				setcolor(BROWN);
				settextstyle(5,0,5);
				settextjustify(CENTER_TEXT,CENTER_TEXT);
				outtextxy(getmaxx()/2,140,"Set Difficulty Level");
				if(kbhit())
				{
					e=getch();
					if((e==72)&&(f==2))
					{
						e=0;
						f=1;
					}
					if(((e==80)&&(f==1))||((e==72)&&(f==3)))
					{
						e=0;
						f=2;
					}
					if(((e==80)&&(f==2))||((e==72)&&(f==4)))
					{
						e=0;
						f=3;
					}
					if((e==80)&&(f==3))
					{
						e=0;
						f=4;
					}
				}
				setcolor(BLUE);
				if((((e==72)&&(f==2))||(f==1))||((xm>=170)&&(xm<=460)&&(ym>=185)&&(ym<=230)))
				{
					if((xm>=170)&&(xm<=460)&&(ym>=185)&&(ym<=230))
					{
						if(out.x.bx==1)
						{
							if(rm!=0)
							{
								cout<<" ";
							}
							else
							{
								e=13;
							}
						}
						if(e!=13)
						{
							e=0;
							f=1;
						}
					}
					if(e==13)
					{
						return 0;
					}
					setcolor(GREEN);
					circle(50,210,5);
					circle(getmaxx()-50,210,5);
					setcolor(BLACK);
					settextstyle(3,0,5);
					outtextxy(getmaxx()/2,200,"Easy");
					setcolor(BLUE);
					settextstyle(3,0,6);
				}
				else
				{
					setcolor(BLACK);
					circle(50,210,5);
					circle(getmaxx()-50,210,5);
					setcolor(BLACK);
					settextstyle(3,0,6);
					outtextxy(getmaxx()/2,200,"Easy");
					setcolor(DARKGRAY);
					settextstyle(3,0,5);
				}
				outtextxy(getmaxx()/2,200,"Easy");
				if((((e==80)&&(f==1))||((e==72)&&(f==3))||(f==2))||((xm>=170)&&(xm<=460)&&(ym>=260)&&(ym<=315)))
				{
					if((xm>=170)&&(xm<=460)&&(ym>=260)&&(ym<=315))
					{
						if(out.x.bx==1)
						{
							if(rm!=0)
							{
								cout<<" ";
							}
							else
							{
								e=13;
							}
						}
						if(e!=13)
						{
							e=0;
							f=2;
						}
					}
					if(e==13)
					{
						return 1;
					}
					setcolor(GREEN);
					circle(50,285,5);
					circle(getmaxx()-50,285,5);
					setcolor(BLACK);
					settextstyle(3,0,5);
					outtextxy(getmaxx()/2,275,"Medium");
					setcolor(BLUE);
					settextstyle(3,0,6);
				}
				else
				{
					setcolor(BLACK);
					circle(50,285,5);
					circle(getmaxx()-50,285,5);
					setcolor(BLACK);
					settextstyle(3,0,6);
					outtextxy(getmaxx()/2,275,"Medium");
					setcolor(DARKGRAY);
					settextstyle(3,0,5);
				}
				outtextxy(getmaxx()/2,275,"Medium");
				if((((e==80)&&(f==2))||((e==72)&&(f==4))||(f==3))||((xm>=170)&&(xm<=460)&&(ym>=335)&&(ym<=380)))
				{
					if((xm>=170)&&(xm<=460)&&(ym>=335)&&(ym<=380))
					{
						if(out.x.bx==1)
						{
							if(rm!=0)
							{
								cout<<" ";
							}
							else
							{
								e=13;
							}
						}
						if(e!=13)
						{
							e=0;
							f=3;
						}
					}
					if(e==13)
					{
						return 2;
					}
					setcolor(GREEN);
					circle(50,360,5);
					circle(getmaxx()-50,360,5);
					setcolor(BLACK);
					settextstyle(3,0,5);
					outtextxy(getmaxx()/2,350,"Hard");
					setcolor(BLUE);
					settextstyle(3,0,6);
				}
				else
				{
					setcolor(BLACK);
					circle(50,360,5);
					circle(getmaxx()-50,360,5);
					setcolor(BLACK);
					settextstyle(3,0,6);
					outtextxy(getmaxx()/2,350,"Hard");
					setcolor(DARKGRAY);
					settextstyle(3,0,5);
				}
				outtextxy(getmaxx()/2,350,"Hard");
				if((((e==80)&&(f==3))||(f==4))||((xm>=170)&&(xm<=460)&&(ym>=410)&&(ym<=455)))
				{
					if((xm>=170)&&(xm<=460)&&(ym>=410)&&(ym<=455))
					{
						if(out.x.bx==1)
						{
							if(rm!=0)
							{
								cout<<" ";
							}
							else
							{
								e=13;
							}
						}
						if(e!=13)
						{
							e=0;
							f=4;
						}
					}
					if(e==13)
					{
						return 3;
					}
					setcolor(GREEN);
					circle(50,435,5);
					circle(getmaxx()-50,435,5);
					setcolor(BLACK);
					settextstyle(3,0,5);
					outtextxy(getmaxx()/2,425,"Previous Menu");
					setcolor(WHITE);
					settextstyle(3,0,6);
				}
				else
				{
					setcolor(BLACK);
					circle(50,435,5);
					circle(getmaxx()-50,435,5);
					setcolor(BLACK);
					settextstyle(3,0,6);
					outtextxy(getmaxx()/2,425,"Previous Menu");
					setcolor(LIGHTGRAY);
					settextstyle(3,0,5);
				}
				outtextxy(getmaxx()/2,425,"Previous Menu");
			}
			break;
		}
		break;

		case 2:
		switch(cas)
		{
			case 0:
			while(e!=79)
			{
				in.x.ax=0;
				int86(55,&in,&out);
				in.x.ax=1;
				int86(51,&in,&out);
				in.x.ax=3;
				int86(51,&in,&out);
				xm=out.x.cx;
				ym=out.x.dx;
				if(rm!=0)
				{
					rm--;
				}
				setcolor(RED);
				settextstyle(4,0,9);
				settextjustify(CENTER_TEXT,CENTER_TEXT);
				outtextxy(getmaxx()/2,50,"PYTHON");
				setcolor(BROWN);
				settextstyle(5,0,5);
				settextjustify(CENTER_TEXT,CENTER_TEXT);
				outtextxy(getmaxx()/2,140,"Specify Difficulty Level");
				if(kbhit())
				{
					e=getch();
					if((e==72)&&(f==4))
					{
						e=0;
						f=1;
					}
					if((e==80)&&(f==1))
					{
						e=0;
						f=4;
					}
				}
				setcolor(BLUE);
				if((((e==72)&&(f==4))||(f==1))||((xm>=170)&&(xm<=460)&&(ym>=185)&&(ym<=230)))
				{
					if((xm>=170)&&(xm<=460)&&(ym>=185)&&(ym<=230))
					{
						if(out.x.bx==1)
						{
							if(rm!=0)
							{
								cout<<" ";
							}
							else
							{
								e=13;
							}
						}
						if(e!=13)
						{
							e=0;
							f=1;
						}
					}
					if(e==13)
					{
						return 0;
					}
					setcolor(GREEN);
					circle(50,210,5);
					circle(getmaxx()-50,210,5);
					setcolor(BLACK);
					settextstyle(3,0,5);
					outtextxy(getmaxx()/2,200,"Easy");
					setcolor(BLUE);
					settextstyle(3,0,6);
				}
				else
				{
					setcolor(BLACK);
					circle(50,210,5);
					circle(getmaxx()-50,210,5);
					setcolor(BLACK);
					settextstyle(3,0,6);
					outtextxy(getmaxx()/2,200,"Easy");
					setcolor(DARKGRAY);
					settextstyle(3,0,5);
				}
				outtextxy(getmaxx()/2,200,"Easy");
				setcolor(DARKGRAY);
				settextstyle(3,0,5);
				outtextxy(getmaxx()/2,275,"Medium");
				setcolor(DARKGRAY);
				settextstyle(3,0,5);
				outtextxy(getmaxx()/2,350,"Hard");
				if((((e==80)&&(f==1))||(f==4))||((xm>=170)&&(xm<=460)&&(ym>=410)&&(ym<=455)))
				{
					if((xm>=170)&&(xm<=460)&&(ym>=410)&&(ym<=455))
					{
						if(out.x.bx==1)
						{
							if(rm!=0)
							{
								cout<<" ";
							}
							else
							{
								e=13;
							}
						}
						if(e!=13)
						{
							e=0;
							f=4;
						}
					}
					if(e==13)
					{
						return 3;
					}
					setcolor(GREEN);
					circle(50,435,5);
					circle(getmaxx()-50,435,5);
					setcolor(BLACK);
					settextstyle(3,0,5);
					outtextxy(getmaxx()/2,425,"Previous Menu");
					setcolor(WHITE);
					settextstyle(3,0,6);
				}
				else
				{
					setcolor(BLACK);
					circle(50,435,5);
					circle(getmaxx()-50,435,5);
					setcolor(BLACK);
					settextstyle(3,0,6);
					outtextxy(getmaxx()/2,425,"Previous Menu");
					setcolor(LIGHTGRAY);
					settextstyle(3,0,5);
				}
				outtextxy(getmaxx()/2,425,"Previous Menu");
			}
			break;

			case 1:
			while(e!=79)
			{
				in.x.ax=0;
				int86(55,&in,&out);
				in.x.ax=1;
				int86(51,&in,&out);
				in.x.ax=3;
				int86(51,&in,&out);
				xm=out.x.cx;
				ym=out.x.dx;
				if(rm!=0)
				{
					rm--;
				}
				setcolor(RED);
				settextstyle(4,0,9);
				settextjustify(CENTER_TEXT,CENTER_TEXT);
				outtextxy(getmaxx()/2,50,"PYTHON");
				setcolor(BROWN);
				settextstyle(5,0,5);
				settextjustify(CENTER_TEXT,CENTER_TEXT);
				outtextxy(getmaxx()/2,140,"Specify Difficulty Level");
				if(kbhit())
				{
					e=getch();
					if((e==72)&&(f==2))
					{
						e=0;
						f=1;
					}
					if(((e==80)&&(f==1))||((e==72)&&(f==4)))
					{
						e=0;
						f=2;
					}
					if((e==80)&&(f==2))
					{
						e=0;
						f=4;
					}
				}
				setcolor(BLUE);
				if((((e==72)&&(f==2))||(f==1))||((xm>=170)&&(xm<=460)&&(ym>=185)&&(ym<=230)))
				{
					if((xm>=170)&&(xm<=460)&&(ym>=185)&&(ym<=230))
					{
						if(out.x.bx==1)
						{
							if(rm!=0)
							{
								cout<<" ";
							}
							else
							{
								e=13;
							}
						}
						if(e!=13)
						{
							e=0;
							f=1;
						}
					}
					if(e==13)
					{
						return 0;
					}
					setcolor(GREEN);
					circle(50,210,5);
					circle(getmaxx()-50,210,5);
					setcolor(BLACK);
					settextstyle(3,0,5);
					outtextxy(getmaxx()/2,200,"Easy");
					setcolor(BLUE);
					settextstyle(3,0,6);
				}
				else
				{
					setcolor(BLACK);
					circle(50,210,5);
					circle(getmaxx()-50,210,5);
					setcolor(BLACK);
					settextstyle(3,0,6);
					outtextxy(getmaxx()/2,200,"Easy");
					setcolor(DARKGRAY);
					settextstyle(3,0,5);
				}
				outtextxy(getmaxx()/2,200,"Easy");
				if((((e==80)&&(f==1))||((e==72)&&(f==4))||(f==2))||((xm>=170)&&(xm<=460)&&(ym>=260)&&(ym<=315)))
				{
					if((xm>=170)&&(xm<=460)&&(ym>=260)&&(ym<=315))
					{
						if(out.x.bx==1)
						{
							if(rm!=0)
							{
								cout<<" ";
							}
							else
							{
								e=13;
							}
						}
						if(e!=13)
						{
							e=0;
							f=2;
						}
					}
					if(e==13)
					{
						return 1;
					}
					setcolor(GREEN);
					circle(50,285,5);
					circle(getmaxx()-50,285,5);
					setcolor(BLACK);
					settextstyle(3,0,5);
					outtextxy(getmaxx()/2,275,"Medium");
					setcolor(BLUE);
					settextstyle(3,0,6);
				}
				else
				{
					setcolor(BLACK);
					circle(50,285,5);
					circle(getmaxx()-50,285,5);
					setcolor(BLACK);
					settextstyle(3,0,6);
					outtextxy(getmaxx()/2,275,"Medium");
					setcolor(DARKGRAY);
					settextstyle(3,0,5);
				}
				outtextxy(getmaxx()/2,275,"Medium");
				setcolor(DARKGRAY);
				settextstyle(3,0,5);
				outtextxy(getmaxx()/2,350,"Hard");
				if((((e==80)&&(f==2))||(f==4))||((xm>=170)&&(xm<=460)&&(ym>=410)&&(ym<=455)))
				{
					if((xm>=170)&&(xm<=460)&&(ym>=410)&&(ym<=455))
					{
						if(out.x.bx==1)
						{
							if(rm!=0)
							{
								cout<<" ";
							}
							else
							{
								e=13;
							}
						}
						if(e!=13)
						{
							e=0;
							f=4;
						}
					}
					if(e==13)
					{
						return 3;
					}
					setcolor(GREEN);
					circle(50,435,5);
					circle(getmaxx()-50,435,5);
					setcolor(BLACK);
					settextstyle(3,0,5);
					outtextxy(getmaxx()/2,425,"Previous Menu");
					setcolor(WHITE);
					settextstyle(3,0,6);
				}
				else
				{
					setcolor(BLACK);
					circle(50,435,5);
					circle(getmaxx()-50,435,5);
					setcolor(BLACK);
					settextstyle(3,0,6);
					outtextxy(getmaxx()/2,425,"Previous Menu");
					setcolor(LIGHTGRAY);
					settextstyle(3,0,5);
				}
				outtextxy(getmaxx()/2,425,"Previous Menu");
			}
			break;

			case 2:
			while(e!=79)
			{
				in.x.ax=0;
				int86(55,&in,&out);
				in.x.ax=1;
				int86(51,&in,&out);
				in.x.ax=3;
				int86(51,&in,&out);
				xm=out.x.cx;
				ym=out.x.dx;
				if(rm!=0)
				{
					rm--;
				}
				setcolor(RED);
				settextstyle(4,0,9);
				settextjustify(CENTER_TEXT,CENTER_TEXT);
				outtextxy(getmaxx()/2,50,"PYTHON");
				setcolor(BROWN);
				settextstyle(5,0,5);
				settextjustify(CENTER_TEXT,CENTER_TEXT);
				outtextxy(getmaxx()/2,140,"Specify Difficulty Level");
				if(kbhit())
				{
					e=getch();
					if((e==72)&&(f==2))
					{
						e=0;
						f=1;
					}
					if(((e==80)&&(f==1))||((e==72)&&(f==3)))
					{
						e=0;
						f=2;
					}
					if(((e==80)&&(f==2))||((e==72)&&(f==4)))
					{
						e=0;
						f=3;
					}
					if((e==80)&&(f==3))
					{
						e=0;
						f=4;
					}
				}
				setcolor(BLUE);
				if((((e==72)&&(f==2))||(f==1))||((xm>=170)&&(xm<=460)&&(ym>=185)&&(ym<=230)))
				{
					if((xm>=170)&&(xm<=460)&&(ym>=185)&&(ym<=230))
					{
						if(out.x.bx==1)
						{
							if(rm!=0)
							{
								cout<<" ";
							}
							else
							{
								e=13;
							}
						}
						if(e!=13)
						{
							e=0;
							f=1;
						}
					}
					if(e==13)
					{
						return 0;
					}
					setcolor(GREEN);
					circle(50,210,5);
					circle(getmaxx()-50,210,5);
					setcolor(BLACK);
					settextstyle(3,0,5);
					outtextxy(getmaxx()/2,200,"Easy");
					setcolor(BLUE);
					settextstyle(3,0,6);
				}
				else
				{
					setcolor(BLACK);
					circle(50,210,5);
					circle(getmaxx()-50,210,5);
					setcolor(BLACK);
					settextstyle(3,0,6);
					outtextxy(getmaxx()/2,200,"Easy");
					setcolor(DARKGRAY);
					settextstyle(3,0,5);
				}
				outtextxy(getmaxx()/2,200,"Easy");
				if((((e==80)&&(f==1))||((e==72)&&(f==3))||(f==2))||((xm>=170)&&(xm<=460)&&(ym>=260)&&(ym<=315)))
				{
					if((xm>=170)&&(xm<=460)&&(ym>=260)&&(ym<=315))
					{
						if(out.x.bx==1)
						{
							if(rm!=0)
							{
								cout<<" ";
							}
							else
							{
								e=13;
							}
						}
						if(e!=13)
						{
							e=0;
							f=2;
						}
					}
					if(e==13)
					{
						return 1;
					}
					setcolor(GREEN);
					circle(50,285,5);
					circle(getmaxx()-50,285,5);
					setcolor(BLACK);
					settextstyle(3,0,5);
					outtextxy(getmaxx()/2,275,"Medium");
					setcolor(BLUE);
					settextstyle(3,0,6);
				}
				else
				{
					setcolor(BLACK);
					circle(50,285,5);
					circle(getmaxx()-50,285,5);
					setcolor(BLACK);
					settextstyle(3,0,6);
					outtextxy(getmaxx()/2,275,"Medium");
					setcolor(DARKGRAY);
					settextstyle(3,0,5);
				}
				outtextxy(getmaxx()/2,275,"Medium");
				if((((e==80)&&(f==2))||((e==72)&&(f==4))||(f==3))||((xm>=170)&&(xm<=460)&&(ym>=335)&&(ym<=380)))
				{
					if((xm>=170)&&(xm<=460)&&(ym>=335)&&(ym<=380))
					{
						if(out.x.bx==1)
						{
							if(rm!=0)
							{
								cout<<" ";
							}
							else
							{
								e=13;
							}
						}
						if(e!=13)
						{
							e=0;
							f=3;
						}
					}
					if(e==13)
					{
						return 2;
					}
					setcolor(GREEN);
					circle(50,360,5);
					circle(getmaxx()-50,360,5);
					setcolor(BLACK);
					settextstyle(3,0,5);
					outtextxy(getmaxx()/2,350,"Hard");
					setcolor(BLUE);
					settextstyle(3,0,6);
				}
				else
				{
					setcolor(BLACK);
					circle(50,360,5);
					circle(getmaxx()-50,360,5);
					setcolor(BLACK);
					settextstyle(3,0,6);
					outtextxy(getmaxx()/2,350,"Hard");
					setcolor(DARKGRAY);
					settextstyle(3,0,5);
				}
				outtextxy(getmaxx()/2,350,"Hard");
				if((((e==80)&&(f==3))||(f==4))||((xm>=170)&&(xm<=460)&&(ym>=410)&&(ym<=455)))
				{
					if((xm>=170)&&(xm<=460)&&(ym>=410)&&(ym<=455))
					{
						if(out.x.bx==1)
						{
							if(rm!=0)
							{
								cout<<" ";
							}
							else
							{
								e=13;
							}
						}
						if(e!=13)
						{
							e=0;
							f=4;
						}
					}
					if(e==13)
					{
						return 3;
					}
					setcolor(GREEN);
					circle(50,435,5);
					circle(getmaxx()-50,435,5);
					setcolor(BLACK);
					settextstyle(3,0,5);
					outtextxy(getmaxx()/2,425,"Previous Menu");
					setcolor(WHITE);
					settextstyle(3,0,6);
				}
				else
				{
					setcolor(BLACK);
					circle(50,435,5);
					circle(getmaxx()-50,435,5);
					setcolor(BLACK);
					settextstyle(3,0,6);
					outtextxy(getmaxx()/2,425,"Previous Menu");
					setcolor(LIGHTGRAY);
					settextstyle(3,0,5);
				}
				outtextxy(getmaxx()/2,425,"Previous Menu");
			}
			break;
		}
		break;
	}
	return 5;
}
void SILIPYTH(int l, int s, int m, int t, int h)
{
	in.x.ax=2;
	int86(51,&in,&out);
	clrscr();
	cleardevice();
	randomize();
	int d=77,u=0,ct=0,cr=0,aa=1000,bb=1000,pt=0,pr=0,ha=0,hb=0,hc=0,hd=0,td=10,p;
	setbkcolor(BLACK);
	setcolor(WHITE);
	settextstyle(0,0,0);
	settextjustify(CENTER_TEXT,CENTER_TEXT);
	outtextxy(getmaxx()/2,50,"PRESS END TO EXIT TO MAIN MENU");
	settextjustify(LEFT_TEXT,CENTER_TEXT);
	cout<<"            "<<h;
	outtextxy(0,8,"Lives Left:");
	switch(l)
	{
		case 0:
		rectangle(100,100,getmaxx()-100,getmaxy()-100);
		break;

		case 1:
		rectangle(100,100,getmaxx()-100,getmaxy()-100);
		rectangle(95,95,getmaxx()-95,getmaxy()-95);
		break;

		case 2:
		rectangle(100,100,getmaxx()-100,getmaxy()-100);
		rectangle(95,95,getmaxx()-95,getmaxy()-95);
		rectangle(getmaxx()/2,100,getmaxx()/2+2,180);
		rectangle(getmaxx()/2,getmaxy()-180,getmaxx()/2+2,getmaxy()-100);
		rectangle(100,getmaxy()/2,220,getmaxy()/2+2);
		rectangle(getmaxx()-220,getmaxy()/2,getmaxx()-100,getmaxy()/2+2);
		break;
	}
	int x[500]={150,140,130,120,110};
	int y[500]={110,110,110,110,110};
	r:
	int a=110+10*(random(43));
	int b=110+10*(random(27));
	if(l==2)
	{
		if(((a==320)&&((b<=180)||(b>=300)))||((b==240)&&((a<=220)||(a>=420))))
		{
			goto r;
		}
	}
	while(d!=79)
	{
		for(int i=0;i<=100;i++)
		{
			if((x[i]==0)&&(y[i]==0))
			{
				x[i]=1000;
				y[i]=1000;
			}
		}
		ha++;
		hb++;
		hc++;
		hd++;
		if(u==0)
		{
			cout<<"\n            "<<m;
			outtextxy(0,24,"Your Score:");
			u++;
		}
		if(ct==4)
		{
			if(cr==0)
			{
				ua:
				aa=110+10*(random(43));
				bb=110+10*(random(27));
				if(l==2)
				{
					if(((aa==320)&&((bb<=180)||(bb>=300)))||((bb==240)&&((aa<=220)||(aa>=420))))
					{
						goto ua;
					}
				}
				cr++;
			}
			switch(t)
			{
				case 55:
				if(ha==18)
				{
					td--;
				}
				break;

				case 50:
				if(hb==20)
				{
					td--;
				}
				break;

				case 30:
				if(hc==33)
				{
					td--;
				}
				break;

				case 25:
				if(hd==40)
				{
					td--;
				}
				break;
			}
			setcolor(WHITE);
			settextstyle(0,0,0);
			settextjustify(LEFT_TEXT,CENTER_TEXT);
			gotoxy(13,4);
			cout<<"  ";
			gotoxy(13,4);
			cout<<td;
			outtextxy(0,56,"Ball Timer:");
			setcolor(GREEN);
			circle(a,b,5);
			setcolor(RED);
			circle(aa,bb,5);
			setfillstyle(SOLID_FILL,BLUE);
			floodfill(aa,bb,RED);
		}
		else
		{
			cr=0;
			if(ct!=5)
			{
				if((pt==4)&&(pr==0))
				{
					uc:
					a=110+10*(random(43));
					b=110+10*(random(27));
					if(l==2)
					{
						if(((a==320)&&((b<=180)||(b>=300)))||((b==240)&&((a<=220)||(a>=420))))
						{
							goto uc;
						}
					}
					pr++;
				}
				setcolor(GREEN);
				circle(a,b,5);
			}
			if(ct==5)
			{
				switch(t)
				{
					case 55:
					if(ha==18)
					{
						td--;
					}
					break;

					case 50:
					if(hb==20)
					{
						td--;
					}
					break;

					case 30:
					if(hc==33)
					{
						td--;
					}
					break;

					case 25:
					if(hd==40)
					{
						td--;
					}
					break;
				}
				setcolor(WHITE);
				settextstyle(0,0,0);
				settextjustify(LEFT_TEXT,CENTER_TEXT);
				gotoxy(13,4);
				cout<<"  ";
				gotoxy(13,4);
				cout<<td;
				outtextxy(0,56,"Ball Timer:");
				a=1000;
				b=1000;
				setcolor(RED);
				circle(aa,bb,5);
				setfillstyle(SOLID_FILL,BLUE);
				floodfill(aa,bb,RED);
			}
		}
		setcolor(YELLOW);
		setfillstyle(SOLID_FILL,RED);
		for(i=1;i<s;i++)
		{
			circle(x[i],y[i],5);
			floodfill(x[i],y[i],YELLOW);
		}
		setfillstyle(CLOSE_DOT_FILL,RED);
		circle(x[0],y[0],5);
		floodfill(x[0],y[0],YELLOW);
		delay(t);
		setfillstyle(SOLID_FILL,BLACK);
		floodfill(x[s-1],y[s-1],YELLOW);
		setcolor(BLACK);
		circle(x[s-1],y[s-1],5);
		if(ha==18)
		{
			ha=0;
		}
		if(hb==20)
		{
			hb=0;
		}
		if(hc==33)
		{
			hc=0;
		}
		if(hd==40)
		{
			hd=0;
		}
		if((x[0]==a)&&(y[0]==b))
		{
			if(t>=30)
			{
				t-=5;
			}
			sound(5000);
			delay(25);
			nosound();
			s++;
			m++;
			pt=ct;
			ct++;
			gotoxy(13,2);
			cout<<m;
			u:
			a=110+10*(random(43));
			b=110+10*(random(27));
			if(l==2)
			{
				if(((a==320)&&((b<=180)||(b>=300)))||((b==240)&&((a<=220)||(a>=420))))
				{
					goto u;
				}
			}
		}
		if(td==0)
		{
			if(t!=25)
			{
				t+=5;
			}
			s--;
			setfillstyle(SOLID_FILL,BLACK);
			floodfill(aa,bb,BLACK);
			goto tc;
		}
		if((x[0]==aa)&&(y[0]==bb))
		{
			tc:
			setcolor(BLACK);
			settextstyle(0,0,0);
			settextjustify(LEFT_TEXT,CENTER_TEXT);
			outtextxy(0,56,"Ball Timer:");
			if(t>=30)
			{
				t-=5;
			}
			if(td!=0)
			{
				sound(5000);
				delay(5);
				sound(6000);
				delay(5);
				sound(7000);
				delay(5);
				sound(8000);
				delay(5);
				sound(9000);
				delay(5);
				nosound();
			}
			else
			{
				sound(250);
				delay(25);
				nosound();
			}
			s++;
			m+=td;
			if(ct==5)
			{
				pr=0;
			}
			ct=0;
			aa=1000;
			bb=1000;
			gotoxy(13,4);
			cout<<"  ";
			gotoxy(13,2);
			cout<<m;
			td=10;
		}
		for(i=s-1;i>0;i--)
		{
			x[i]=x[i-1];
			y[i]=y[i-1];
		}
		p=d;
		if(kbhit())
		{
			d=getch();
			if(d==0)
			{
				d=getch();
			}
			if((d!=79)&&(d!=72)&&(d!=75)&&(d!=77)&&(d!=80))
			{
				d=p;
			}
		}
		switch(d)
		{
			case 79:
			w=1;
			break;

			case 75:
			if(p==77)
			{
				x[0]+=10;
				d=p;
			}
			else
			{
				x[0]-=10;
			}
			break;

			case 72:
			if(p==80)
			{
				y[0]+=10;
				d=p;
			}
			else
			{
				y[0]-=10;
			}
			break;

			case 77:
			if(p==75)
			{
				x[0]-=10;
				d=p;
			}
			else
			{
				x[0]+=10;
			}
			break;

			case 80:
			if(p==72)
			{
				y[0]-=10;
				d=p;
			}
			else
			{
				y[0]+=10;
			}
			break;
		}
		if((d==75)&&(x[0]==100))
		{
			x[0]=530;
			if(l!=0)
			{
				goto g;
			}
		}
		if((d==72)&&(y[0]==100))
		{
			y[0]=370;
			if(l!=0)
			{
				goto g;
			}
		}
		if((d==77)&&(x[0]==540))
		{
			x[0]=110;
			if(l!=0)
			{
				goto g;
			}
		}
		if((d==80)&&(y[0]==380))
		{
			y[0]=110;
			if(l!=0)
			{
				goto g;
			}
		}
		if(l==2)
		{
			if((((d==77)||(d==75)||(d==72))&&(y[0]<=180)&&(x[0]==320))||(((d==77)||(d==75)||(d==80))&&(y[0]>=300)&&(x[0]==320))||(((d==80)||(d==72)||(d==75))&&(x[0]<=220)&&(y[0]==240))||(((d==80)||(d==72)||(d==77))&&(x[0]>=420)&&(y[0]==240)))
			{
				goto g;
			}
		}
		for(i=3;i<s;i++)
		{
			if((x[0]==x[i])&&(y[0]==y[i]))
			{
				goto g;
			}
		}
	}
	g:
	if((h!=1)&&(w!=1))
	{
		setcolor(BLUE);
		settextstyle(8,0,9);
		settextjustify(CENTER_TEXT,CENTER_TEXT);
		outtextxy(getmaxx()/2,getmaxy()/2,"LIFE LOST !!");
		sound(100);
		delay(1000);
		nosound();
	}
	c=s;
	::o=m;
	z=t;
	clrscr();
	cleardevice();
	setbkcolor(BLACK);
}
void file(int a)
{
	char last='y';
	switch(a)
	{
		case 0:
		ein.open("easy.GDC",ios::in);
		fo.open("temp.GDC",ios::out);
		ein.seekg(0);
		ein.read((char*)&s1,sizeof(s1));
		while(!ein.eof())
		{
			if(hs.getscore()>=s1.getscore())
			{
				fo.write((char*)&hs,sizeof(hs));
				fo.write((char*)&s1,sizeof(s1));
				last='n';
				break;
			}
			else
			{
				fo.write((char*)&s1,sizeof(s1));
			}
			ein.read((char*)&s1,sizeof(s1));
		}
		if(last=='y')
		{
			fo.write((char*)&hs,sizeof(hs));
		}
		else if(!ein.eof())
		{
			ein.read((char*)&s1,sizeof(s1));
			while(!ein.eof())
			{
				fo.write((char*)&s1,sizeof(s1));
				ein.read((char*)&s1,sizeof(s1));
			}
		}
		ein.close();
		fo.close();
		remove("Easy.GDC");
		rename("temp.GDC","Easy.GDC");
		break;

		case 1:
		min.open("Med.GDC",ios::in);
		fo.open("temp.GDC",ios::out);
		min.seekg(0);
		min.read((char*)&s1,sizeof(s1));
		while(!min.eof())
		{
			if(hs.getscore()>=s1.getscore())
			{
				fo.write((char*)&hs,sizeof(hs));
				fo.write((char*)&s1,sizeof(s1));
				last='n';
				break;
			}
			else
				fo.write((char*)&s1,sizeof(s1));
			min.read((char*)&s1,sizeof(s1));
		}
		if(last=='y')
		{
			fo.write((char*)&hs,sizeof(hs));
		}
		else if(!min.eof())
		{
			min.read((char*)&s1,sizeof(s1));
			while(!min.eof())
			{
				fo.write((char*)&s1,sizeof(s1));
				min.read((char*)&s1,sizeof(s1));
			}
		}
		min.close();
		fo.close();
		remove("Med.GDC");
		rename("temp.GDC","Med.GDC");
		break;

		case 2:
		hin.open("Hard.GDC",ios::in);
		fo.open("temp.GDC",ios::out);
		hin.seekg(0);
		hin.read((char*)&s1,sizeof(s1));
		while(!hin.eof())
		{
			if(hs.getscore()>=s1.getscore())
			{
				fo.write((char*)&hs,sizeof(hs));
				fo.write((char*)&s1,sizeof(s1));
				last='n';
				break;
			}
			else
				fo.write((char*)&s1,sizeof(s1));
			hin.read((char*)&s1,sizeof(s1));
		}
		if(last=='y')
		{
			fo.write((char*)&hs,sizeof(hs));
		}
		else if(!hin.eof())
		{
			hin.read((char*)&s1,sizeof(s1));
			while(!hin.eof())
			{
				fo.write((char*)&s1,sizeof(s1));
				hin.read((char*)&s1,sizeof(s1));
			}
		}
		hin.close();
		fo.close();
		remove("Hard.GDC");
		rename("temp.GDC","Hard.GDC");
		break;
	}
}
void main()
{
	int e=72,f=1,q;
	initgraph(&driver,&mode,"..//BGI");
	MAIN();
	in.x.ax=0;
	ein.open("Easy.GDC",ios::out|ios::app);
	min.open("Med.GDC",ios::out|ios::app);
	hin.open("Hard.GDC",ios::out|ios::app);
	hs.indata();
	ein.write((char*)&hs,sizeof(hs));
	min.write((char*)&hs,sizeof(hs));
	hin.write((char*)&hs,sizeof(hs));
	ein.close();
	min.close();
	hin.close();
	int86(51,&in,&out);
	setbkcolor(BLACK);
	while(e!=79)
	{
		in.x.ax=0;
		int86(55,&in,&out);
		in.x.ax=1;
		int86(51,&in,&out);
		in.x.ax=3;
		int86(51,&in,&out);
		xm=out.x.cx;
		ym=out.x.dx;
		if(rm!=0)
		{
			rm--;
		}
		setcolor(RED);
		settextstyle(4,0,9);
		settextjustify(CENTER_TEXT,CENTER_TEXT);
		outtextxy(getmaxx()/2,50,"PYTHON");
		if(kbhit())
		{
			e=getch();
			if((e==72)&&(f==2))
			{
				e=0;
				f=1;
			}
			if(((e==80)&&(f==1))||((e==72)&&(f==3)))
			{
				e=0;
				f=2;
			}
			if(((e==80)&&(f==2))||((e==72)&&(f==4)))
			{
				e=0;
				f=3;
			}
			if((e==80)&&(f==3))
			{
				e=0;
				f=4;
			}
		}
		setcolor(BLUE);
		if((((e==72)&&(f==2))||(f==1))||((xm>=170)&&(xm<=460)&&(ym>=185)&&(ym<=230)))
		{
			if((xm>=170)&&(xm<=460)&&(ym>=185)&&(ym<=230))
			{
				if(out.x.bx==1)
				{
					if(rm!=0)
					{
						cout<<" ";
					}
					else
					{
						e=13;
					}
				}
				if(e!=13)
				{
					e=0;
					f=1;
				}
			}
			if(e==13)
			{
				NAME();
				q=::t;
				rm=10;
				if(q!=3)
				{
					SILIPYTH(q,c,::o,z,3);
					clrbuf(50);
					if(w!=1)
					{
						SILIPYTH(q,c,::o,z,2);
						clrbuf(50);
					}
					if(w!=1)
					{
						SILIPYTH(q,c,::o,z,1);
						clrbuf(50);
					}
					clrscr();
					cleardevice();
					setbkcolor(RED);
					setcolor(WHITE);
					settextstyle(0,0,0);
					settextjustify(CENTER_TEXT,CENTER_TEXT);
					cout<<"\n"<<setw(46)<<" ";
					outtextxy(getmaxx()/2,24,"Your Score is:  ");
					gotoxy(48,2);
					cout<<::o;
					settextstyle(4,0,9);
					setcolor(YELLOW);
					outtextxy(getmaxx()/2,getmaxy()/2,"GAME OVER");
					in.x.ax=0;
					int86(51,&in,&out);
					hs.indata(::name,::o);
					file(q);
					for(int i=2500;i>=150;i--)
					{
						sound(i);
						delay(1);
					}
					nosound();
				}
				clrbuf(50);
				clrscr();
				cleardevice();
				setbkcolor(BLACK);
				e=72;
				c=5;
				::o=0;
				z=75;
				w=0;
				xm=200;
				ym=200;
			}
			setcolor(GREEN);
			circle(50,210,5);
			circle(getmaxx()-50,210,5);
			setcolor(BLACK);
			settextstyle(3,0,5);
			outtextxy(getmaxx()/2,200,"New Game");
			setcolor(BLUE);
			settextstyle(3,0,6);
		}
		else
		{
			setcolor(BLACK);
			circle(50,210,5);
			circle(getmaxx()-50,210,5);
			setcolor(BLACK);
			settextstyle(3,0,6);
			outtextxy(getmaxx()/2,200,"New Game");
			setcolor(BLUE);
			settextstyle(3,0,5);
		}
		outtextxy(getmaxx()/2,200,"New Game");
		if((((e==80)&&(f==1))||((e==72)&&(f==3))||(f==2))||((xm>=170)&&(xm<=460)&&(ym>=260)&&(ym<=315)))
		{
			if((xm>=170)&&(xm<=460)&&(ym>=260)&&(ym<=315))
			{
				if(out.x.bx==1)
				{
					if(rm!=0)
					{
						cout<<" ";
					}
					else
					{
						e=13;
					}
				}
				if(e!=13)
				{
					e=0;
					f=2;
				}
			}
			if(e==13)
			{
				HIGH();
				rm=10;
				setcolor(BLACK);
				clrscr();
				cleardevice();
				e=77;
			}
			setcolor(GREEN);
			circle(50,285,5);
			circle(getmaxx()-50,285,5);
			setcolor(BLACK);
			settextstyle(3,0,5);
			outtextxy(getmaxx()/2,275,"High Scores");
			setcolor(BLUE);
			settextstyle(3,0,6);
		}
		else
		{
			setcolor(BLACK);
			circle(50,285,5);
			circle(getmaxx()-50,285,5);
			setcolor(BLACK);
			settextstyle(3,0,6);
			outtextxy(getmaxx()/2,275,"High Scores");
			setcolor(BLUE);
			settextstyle(3,0,5);
		}
		outtextxy(getmaxx()/2,275,"High Scores");
		if((((e==80)&&(f==2))||((e==72)&&(f==4))||(f==3))||((xm>=170)&&(xm<=460)&&(ym>=335)&&(ym<=380)))
		{
			if((xm>=170)&&(xm<=460)&&(ym>=335)&&(ym<=380))
			{
				if(out.x.bx==1)
				{
					if(rm!=0)
					{
						cout<<" ";
					}
					else
					{
						e=13;
					}
				}
				if(e!=13)
				{
					e=0;
					f=3;
				}
			}
			if(e==13)
			{
				INSTRUCTIONS();
				rm=10;
				setcolor(BLACK);
				clrscr();
				cleardevice();
				e=77;
			}
			setcolor(GREEN);
			circle(50,360,5);
			circle(getmaxx()-50,360,5);
			setcolor(BLACK);
			settextstyle(3,0,5);
			outtextxy(getmaxx()/2,350,"Instructions");
			setcolor(BLUE);
			settextstyle(3,0,6);
		}
		else
		{
			setcolor(BLACK);
			circle(50,360,5);
			circle(getmaxx()-50,360,5);
			setcolor(BLACK);
			settextstyle(3,0,6);
			outtextxy(getmaxx()/2,350,"Instructions");
			setcolor(BLUE);
			settextstyle(3,0,5);
		}
		outtextxy(getmaxx()/2,350,"Instructions");
		if((((e==80)&&(f==3))||(f==4))||((xm>=170)&&(xm<=460)&&(ym>=410)&&(ym<=455)))
		{
			if((xm>=170)&&(xm<=460)&&(ym>=410)&&(ym<=455))
			{
				if(out.x.bx==1)
				{
					if(rm!=0)
					{
						cout<<" ";
					}
					else
					{
						e=13;
					}
				}
				if(e!=13)
				{
					e=0;
					f=4;
				}
			}
			if(e==13)
			{
				e=79;
			}
			setcolor(GREEN);
			circle(50,435,5);
			circle(getmaxx()-50,435,5);
			setcolor(BLACK);
			settextstyle(3,0,5);
			outtextxy(getmaxx()/2,425,"Exit");
			setcolor(BLUE);
			settextstyle(3,0,6);
		}
		else
		{
			setcolor(BLACK);
			circle(50,435,5);
			circle(getmaxx()-50,435,5);
			setcolor(BLACK);
			settextstyle(3,0,6);
			outtextxy(getmaxx()/2,425,"Exit");
			setcolor(BLUE);
			settextstyle(3,0,5);
		}
		outtextxy(getmaxx()/2,425,"Exit");
	}
	closegraph();
}