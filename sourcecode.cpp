#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#pragma warning(disable : 4996)
using namespace std;

/*/////////////////////////////////////////////
*************   CLASSES      **************
*********     DECLARATION      ***********
**********************************************
////////////////////////////////////////////
///////////////////////////////////////////*/

class Object;
class Date;
class facebook;
class socialuser;
class Page;
class Post;
class Comment;


/*/////////////////////////////////////////////
**************DEFINITION   OF **************
*********  OBJECT  CLASSS     ***********
**********************************************
////////////////////////////////////////////
///////////////////////////////////////////*/


class Object
{
	char* id;
public:
	Object();
	Object(string);
	virtual ~Object();

	//functions
	virtual void printname(){}
	virtual void Print() = 0;
	void setid(string);
	char* getid();
	bool strFind(const char*,const char*);
	
}; 

/*/////////////////////////////////////////////
**************DEFINITION   OF **************
*********  DATE   CLASSS     ***********
**********************************************
////////////////////////////////////////////
///////////////////////////////////////////*/

class Date
{
	int day;
	int month;
	int year;
public:
	Date();
	Date(int, int, int);
	Date(const Date&);


	void printdate();
	int getdate();
	int getmonth();
	int getyear();
	void setdate(int);
	void setmonth(int);
	void setyear(int);

	bool operator<=(Date&);              //for comparison of post date of a post and current date.
	Date& operator=(const Date&);
	static Date currentdate;                        //PURPOSE:  to set the current system date and then compare posts date to 
	                                                 //           current date for printing latest posts on HOMEPAGE.
	static void setcurrentdate(int,int,int);
};

/*/////////////////////////////////////////////
**************DEFINITION   OF **************
*********  SOCIALUSER  CLASSS     ***********
**********************************************
////////////////////////////////////////////
///////////////////////////////////////////*/

class socialuser :public Object
{
	static int totalusers;
	char* firstname;
	char* lname;
	int frndcount;
	socialuser** friendlist;
	int likedpagescount;
	Page** likedpages;
	int noofposts;
	Post** postsby_user;

public:
	socialuser();
	socialuser(string, string, string);
	~socialuser();


	static void settotalusers(int);
	static int gettotalusers();
	void setfriendcount(int);
	Post* getpost(int);
	void setlikepagescount(int);
	void Print();
	void printUserLatest();
	void viewHome();           //HOMEPAGE: latest posts of friends and pages 
	int getpost_count();
	void viewTimeline();          
	void printname();
	void viewfriendlist();
	void viewlikedpages();
	void addfriend(int, socialuser*);
	void allocatefriendlist(int);
	void allocatepagelist(int);
	void likepage(int, Page*);
	void addpost(Post*);
	void addnewpost(Post*);
	char* getf_name();
	char* getl_name();
	void searchstringinUsers(const char*);
	
};


/*/////////////////////////////////////////////
**************DEFINITION   OF **************
*********  PAGE   CLASSS     ***********
**********************************************
////////////////////////////////////////////
///////////////////////////////////////////*/


class Page :public Object
{
private:
	static int totalpage;
	char *pagetitle;
	int noofpost;
	Post** postsby_page;
public:
	Page();
	Page(string, string);
	~Page();


	static void settotalpage(int);
	static int gettotalpage();
	Post* getpost(int);
	int getpost_count();
	void printname();
	void Print();
	void printPageLatest();
	void printPageTimeline();
	void addpost(Post*);
	char* getPagetitle();
	void searchinPages(const char*);
	

};



/*/////////////////////////////////////////////
**************DEFINITION   OF **************
*********  ACTIVITY   CLASSS     ***********
**********************************************
////////////////////////////////////////////
///////////////////////////////////////////*/


class Activity
{
	char* type;
	char* value;
public:
	Activity();
	Activity(const Activity&);
	~Activity();


	void settype(int);
	void setvalue(string);
	void printactivity();
};


/*/////////////////////////////////////////////
**************DEFINITION   OF **************
*********  POST   CLASSS     ***********
**********************************************
////////////////////////////////////////////
///////////////////////////////////////////*/

class Post:public Object
{
	static int total_posts;
	Date post_date;
	char* description;
	int nooflikes;
	int coment_count;
	Object* post_by;
	Activity* activity;
	Object** likedby;
	Comment** cmnts;

public:
	Post();
	Post(Post&);      ////to make a copy of post when a user shares a post on his timeline
	~Post();



	static void settotalposts(int);
	static int gettotalposts();
	void Readpost(ifstream&);
	void Print();
	void printLikes();
	void setposted_by(string, Object*);
	void setpostdescription(string);
	void setlikedby(Object*);
	void add_like(Object*);
	void setdate(int, int, int);
	string setpostnewid();
	void add_comment(string,string,Object*);
	void addnew_comment(string, Object*);
	char* getdescription();
	void searchinPosts(const char*);
	bool datecheck();

	
};



/*/////////////////////////////////////////////
**************DEFINITION   OF **************
*********  COMMENT  CLASSS     ***********
**********************************************
////////////////////////////////////////////
///////////////////////////////////////////*/


class Comment
{
	static int totalcomments;
	char* comnt_id;
	char* cmnt_text;
	Object* comnted_by;

public:
	Comment();
	Comment(string,string);
	~Comment();


	void Print();
	void setnew_id();
	static void settotalcomments(int);
	static int gettotalcomments();
	void setdescription(string);
	void setcomnted_by(Object*);
	
};

/*/////////////////////////////////////////////
**************DEFINITION   OF **************
*********  FACEBOOK   CLASSS     ***********
**********************************************
////////////////////////////////////////////
///////////////////////////////////////////*/


class facebook
{
	socialuser** userlist;
	Page** pages;
	Post** posts;
	static socialuser* currentuser;


public:
	facebook();
	~facebook();

	void LoadAllDataforFacebook();
	void ReadUsersdata();
	void ReadpagesData();
	void ReadPosts();
	bool compare_ID(char*, const char*);
	int getinteger(string);
	int getpostinteger(string);
	void setCurrentUser(string);
	static socialuser* getcurrentuser();
	void socialrun();


	void viewPost(const char*);
	void viewLikeofAPost(const char*);
	void commentOnPost(const char*,string);
	void viewPage(const char*);
	void LikeaPost(const char*);
	void shareaPost(const char*);
	void SearchFacebook(const char*);
	
};


/*/////////////////////////////////////////////
**************      INITIALIZATION OF  ***********
**************   STATIC MEMBERS ***************
/*/////////////////////////////////////////////*/




int socialuser::totalusers = 0;
int Page::totalpage = 0;
int Post::total_posts = 0;
int Comment::totalcomments = 0;
Date Date::currentdate = Date();
socialuser* facebook::currentuser = nullptr;


/*/////////////////////////////////////////////
**************IMPLEMENTATION OF **************
*********  DATE     CLASSS        ***********

**********************************************
////////////////////////////////////////////
///////////////////////////////////////////*/

Date::Date()
{
	time_t now = time(0);
	tm *ltm = localtime(&now);
	day = ltm->tm_mday;
	month = ltm->tm_mon;
	year = ltm->tm_year + 1900;




}
Date::Date(int d, int m, int y)
{
	day = d;
	month = m;
	year = y;
}

void Date::setcurrentdate(int a,int b,int c)
{
	currentdate.day = a;
	currentdate.month = b;
	currentdate.year = c;
}

void Date::setdate(int d)
{
	day = d;
}

void Date::setmonth(int d)
{
	month = d;
}

void Date::setyear(int d)
{
	year = d;
}


Date::Date(const Date &d)
{
	this->year = d.year, this->month = d.month, this->day = d.day;

}


void Date::printdate()
{
	cout << day << "/" << month << "/" << year ;
}

int Date::getdate() {

	return day;
}

int Date::getmonth()
{
	return month;
}

int Date::getyear()
{
	return year;
}

bool Date::operator<=(Date& rhs)
{
	if (day == rhs.day || day == rhs.day - 1)
	{
		if (month == rhs.month)
		{
			if (year == rhs.year)
			{
				return true;
			}
		}
	}
	return false;
}

Date& Date::operator=(const Date& rd)
{
	if (this != &rd)
	{
		day = rd.day;
		month = rd.month;
		year = rd.year;
	}
	return *this;
}

/*/////////////////////////////////////////////
**************IMPLEMENTATION OF **************
*********  OBJECT     CLASSS        ***********

**********************************************
////////////////////////////////////////////
///////////////////////////////////////////*/



Object::Object()
{
	id = nullptr;
}

Object::Object(string s)
{
	id = new char[s.length() + 1];

	int i = 0;
	for (; s[i] != '\0'; i++)
	{
		id[i] = s[i];
	}
	id[i] = '\0';

}

void Object::setid(string s)
{
	id = new char[s.length() + 1];

	int i = 0;
	for (; s[i] != '\0'; i++)
	{
		id[i] = s[i];
	}
	id[i] = '\0';


}

char* Object::getid()
{
	return id;
}

bool Object::strFind(const char* Findin,const char* Find)
{
	int i = 0;
	bool flag = true;
	while (Findin[i] != '\0')
	{
		if (Findin[i] == Find[0])
		{
			
			for (int j = 0; Find[j] != '\0'; j++)
			{
				if (Findin[i] != Find[j])
				{
					flag = false;
					i++;                                       // loop to search word
					break;
				}
				else
				{
					i++;
				}
			}
			if (flag)
			{
				return true;
			}
			else
			{
				flag = true;
			}
		}
		i++;
	}
	return false;
}


Object::~Object()
{
	if (id != nullptr)
	{
		delete[] id;
	}
}



/*/////////////////////////////////////////////
**************IMPLEMENTATION OF **************
*********  USER     CLASSS        ***********

**********************************************
////////////////////////////////////////////
///////////////////////////////////////////*/



socialuser::socialuser() :Object()
{
	firstname = lname = 0;
	likedpagescount = frndcount = 0;
	friendlist = nullptr;
	likedpages = nullptr;
	noofposts = 0;
	postsby_user = nullptr;
}

socialuser::socialuser(string id, string fnam, string lnam) :Object(id)
{


	firstname = new char[fnam.length() + 1];

	int j = 0;
	for (; fnam[j] != '\0'; j++)
	{
		firstname[j] = fnam[j];
	}
	firstname[j] = '\0';

	lname = new char[lnam.length() + 1];

	int k = 0;
	for (; lnam[k] != '\0'; k++)
	{
		lname[k] = lnam[k];
	}
	lname[k] = '\0';
	friendlist = nullptr;
	likedpages = nullptr;
	frndcount = likedpagescount = 0;
	noofposts = 0;
	postsby_user = new Post*[10];
	for (int i = 0; i < 10; i++)
	{
		postsby_user[i] = nullptr;
	}
}

void socialuser::settotalusers(int a)
{
	totalusers = a;
}

int socialuser::gettotalusers()
{
	return totalusers;

}
void socialuser::printname()
{
	cout << firstname;
}

Post* socialuser::getpost(int i)
{
	if (i >= 0 || i < noofposts)
	{
		return postsby_user[i];
	}
}

void socialuser::setfriendcount(int a)
{
	frndcount = a;
}

void socialuser::setlikepagescount(int a)
{
	likedpagescount = a;
}


void socialuser::allocatefriendlist(int size)
{
	if (size == 0)
	{
		friendlist = nullptr;
	}
	else
	{
		friendlist = new socialuser*[size];
	}
}

void socialuser::allocatepagelist(int size)
{
	if (size == 0)
	{
		likedpages = nullptr;
	}
	else
	{
		likedpages = new Page*[size];
	}
}


void socialuser::addfriend(int index, socialuser* frnd)
{
	friendlist[index] = frnd;                /////ASSOCIATION between friends 
}


void socialuser::likepage(int index, Page* pg)
{
	likedpages[index] = pg;
}


void socialuser::Print()
{
	cout << getid() << "(" << firstname << " " << lname <<")"<< endl;
	
}


void socialuser::viewfriendlist()
{
	cout << "Frinds of " << firstname << " " << lname << " are: " << frndcount << endl;
	if (frndcount == 0)
	{
		cout << "Current user has 0 friends  \n";
	}
	else
	{
		for (int i = 0; i < frndcount; i++)
		{
			cout << i + 1 << ": "; friendlist[i]->Print(); 
		}
		cout << endl;
	}
}

void socialuser::viewlikedpages()
{
	cout << "pages liked by " << firstname << " " << lname << " are: " << likedpagescount << endl;

	if (likedpagescount == 0)
	{
		cout << "0 pages liked by current user. \n";
	}
	else
	{
		for (int i = 0; i < likedpagescount; i++)
		{
			cout << i + 1 << ": "; likedpages[i]->Print();
		}
		cout << endl;
	}
}

void socialuser::printUserLatest()
{
		for (int i = 0; i < noofposts; i++)
		{
			if (postsby_user[i]->datecheck())
			{
				postsby_user[i]->Print();
			}

		}
}


void socialuser::viewHome()
{
	
	cout << "||||||||||||||||||||||||||| HomePage of  " << firstname << " " << lname;
	cout<<" ||||||||||||||||||||||||||"<< endl << endl;
	
		for (int i = 0; i < frndcount; i++)
		{
			friendlist[i]->printUserLatest();
		}
	
		for (int i = 0; i < likedpagescount; i++)
		{
			likedpages[i]->printPageLatest();
		}
	
}


void socialuser::viewTimeline()
{
	
	cout << endl << "||||||||||||||||||||||||||||||||Timeline of  " << firstname << " ";
	cout << lname << "||||||||||||||||||||||||||||||||||" << endl << endl;
	
		for (int i = 0; i < noofposts; i++)
		{
			postsby_user[i]->Print();
		}

}


void socialuser::addpost(Post* ptr)
{
	if (noofposts  == 0)
	{
		postsby_user = new Post*[10];
		for (int i = 0; i < 10; i++)
		{
			postsby_user[i] = nullptr;
		}
		postsby_user[noofposts] = ptr;
		noofposts++;
	}
	else if (noofposts > 0 && noofposts < 10)
	{
		postsby_user[noofposts] = ptr;
		noofposts++;
	}
	else
	{
		cout << "ERROR: post limit reach \n";
	}
}

void socialuser::addnewpost(Post* ptr)
{

	if (noofposts == 0)
	{
		postsby_user = new Post*[10];
		for (int i = 0; i < 10; i++)
		{
			postsby_user[i] = nullptr;
		}
		postsby_user[noofposts] = new Post(*ptr);
		noofposts++;

	}
	else if (noofposts > 0 && noofposts < 10)
	{
		postsby_user[noofposts] = new Post(*ptr);
		noofposts++;
	}
	else
	{
		cout << "ERROR: post limit reach \n";
	}
}

int socialuser::getpost_count()
{
	return noofposts;
}


char* socialuser::getf_name()
{
	return firstname;
}

char* socialuser::getl_name()
{
	return lname;
}

void socialuser::searchstringinUsers(const char* word)
{
	if (strFind(getf_name(), word)  ||  strFind(getl_name(),word))
	{
		Print();
	}

}


socialuser::~socialuser()
{

	if (firstname)
	{
		delete[] firstname;
	}
	if (lname)
	{
		delete[] lname;

	}
	if (friendlist)
	{
		for (int i = 0; i < frndcount; i++)
		{
			friendlist[i] = nullptr;
		}
		delete[] friendlist;
	}
	
	if (likedpages)
	{
		
		for (int i = 0;i<likedpagescount ; i++)
		{
			likedpages[i] = nullptr;	
		}
		delete[] likedpages;
	}

	if (postsby_user)
	{
		for (int i = 0; i < noofposts; i++)
		{
			if (postsby_user[i])

				delete postsby_user[i];
			postsby_user[i] = nullptr;

		}

		delete[] postsby_user;
		postsby_user = nullptr;
	}


}


/*/////////////////////////////////////////////
**************IMPLEMENTATION OF **************
*********  POST    CLASSS        ***********

**********************************************
////////////////////////////////////////////
///////////////////////////////////////////*/



Post::Post():Object()
{
	description = 0;
	coment_count = 0;
	nooflikes = 0;
	cmnts = nullptr;
	likedby = nullptr;
	post_by = 0;
	activity = nullptr;
}

string Post::setpostnewid()
{
	int newid = Post::gettotalposts() + 1;
	ostringstream str1;
	str1 << newid;
	string id_ = str1.str();

	string new_id = "sharedpost";

	new_id[0] = 'p'; new_id[1] = 'o'; new_id[2] = 's'; new_id[3] = 't';
	int k = 4;
	for (int i = 0; id_[i] != '\0'; i++)
	{
		new_id[k] = id_[i];
		k++;
	}
	new_id[k] = '\0';


	return new_id;
}

Post::Post(Post& rhs)
{
	
	setid(setpostnewid());
	total_posts++;
	post_date = Date::currentdate;
	description = new char[strlen(rhs.description) + 1];
	int i = 0;
	for (; rhs.description[i] != '\0'; i++)
	{
		description[i] = rhs.description[i];
	}
	description[i] = '\0';
	nooflikes = 0;
	coment_count = 0;
	post_by = facebook::getcurrentuser();
	likedby = nullptr;
	cmnts = nullptr;
	activity = new Activity(*rhs.activity);

}


void Post::settotalposts(int a)
{
	total_posts = a;
}

void Post::add_comment(string id,string des,Object* obj)
{
	if (coment_count == 0)
	{
		cmnts = new Comment*[10];
		for (int i = 0; i < 10; i++)
		{
			cmnts[i] = nullptr;
		}
		cmnts[coment_count] = new Comment(id, des);
		cmnts[coment_count]->setcomnted_by( obj);
		coment_count++;
	}
	else if (coment_count > 0 && coment_count < 10)
	{
		cmnts[coment_count] = new Comment(id, des);
		cmnts[coment_count]->setcomnted_by( obj);
	    coment_count++;
	}
	else
	{
		cout << " ERROR: COMMENT LIMIT REACHED  \n";
	}
}

void Post::addnew_comment(string des, Object* obj)
{
	if (coment_count == 0)
	{
		cmnts = new Comment*[10];
		for (int i = 0; i < 10; i++)
		{
			cmnts[i] = nullptr;
		}
		cmnts[coment_count] = new Comment();
		cmnts[coment_count]->setnew_id();
        cmnts[coment_count]->setdescription(des);
		cmnts[coment_count]->setcomnted_by(obj);
		coment_count++;
	}
	else if (coment_count > 0 && coment_count < 10)
	{
		cmnts[coment_count] = new Comment();
		cmnts[coment_count]->setnew_id();
		cmnts[coment_count]->setdescription(des);
		cmnts[coment_count]->setcomnted_by(obj);
		coment_count++;
	}
	else
	{
		cout << " ERROR: COMMENT LIMIT REACHED  \n";
	}

}



void Post::setpostdescription(string txt)
{
	description = new char[txt.length() + 1];

	int i = 0;
	for (; txt[i] != '\0'; i++)
	{
		description[i] = txt[i];
	}
	description[i] = '\0';
}


void Post::setdate(int d, int m, int y)
{
	post_date.setdate(d);
	post_date.setmonth(m);
	post_date.setyear(y);
}

void Post::Readpost(ifstream& fin)
{

	string id;
	fin >> id;
	fin >> id;
	setid(id);
	int a, b, c;
	fin >> a >> b >> c;
	setdate(a, b, c);
	string text;
	getline(fin, text, '\n');
	getline(fin, text, '\n');
	setpostdescription(text);
	int n;
	fin >> n;
	if (n != 0)
	{
		activity = new Activity();
	}
	activity->settype(n);
	if (n != 0)
	{
		getline(fin, text, '\n');
		activity->setvalue(text);
	}
	if (n == 0)
	{
		getline(fin, text, '\n');
	}

}

void Post::Print()
{
	cout << "-------------------------------------\n";
	cout << "<<<<<<<" << getid() << ">>>>>>>";
	cout << "                                ";
	cout << "("; post_date.printdate(); cout << ")" << endl;
    post_by->Print();
	cout << description << endl;
	if (activity != nullptr)
	{
		activity->printactivity();
	}
	cout << endl;
	cout << "||||||Comments||||||  \n\n";
	if (coment_count == 0)
	{
		cout << "The post has no comments Yet  :(  \n";
	}
	for (int i = 0; i < coment_count; i++)
	{
		cmnts[i]->Print();
	}
	cout << endl;
}


void Post::setposted_by(string s, Object* t)
{
		post_by = t;	
}

char* Post::getdescription()
{
	return description;
}


void Post::searchinPosts(const char* post)
{
	if (strFind(getdescription(), post))
	{
		Print();
	}
}

int Post::gettotalposts()
{
	return total_posts;
}
void Post::add_like(Object* ptr)
{
	if (nooflikes < 10)
	{
		
			likedby[nooflikes] = ptr;
			nooflikes++;
		
	}
	else
	{
		cout << "ERROR: like limit reached  \n";
	}
}


void Post::setlikedby( Object* t)
{
	if (nooflikes ==0)
	{
		likedby = new Object*[10];
		for (int i = 0; i < 10; i++)
		{
			likedby[i] = nullptr;
		}
			likedby[nooflikes] = t;
			nooflikes++; 
	}
	else if (nooflikes > 0 && nooflikes < 10)
	{
		likedby[nooflikes] = t;
		nooflikes++;
	}
	else
	{
		cout << "ERROR: like limit reached  \n";
	}
}

void Post::printLikes()
{
	for (int i = 0; i < nooflikes; i++)
	{
		likedby[i]->Print();
	}

}


bool Post::datecheck()
{
	if (post_date <= Date::currentdate)
	{
		return true;
	}
	else
	{
		return false;
	}

}

Post::~Post()
{
	if (description)
	{
		delete[] description;
	}
	post_by = nullptr;
	if (activity)
	{
		delete activity;
	}
	if (likedby)
	{
		for (int i = 0; i < nooflikes; i++)
		{
			if (likedby[i])
				likedby[i] = nullptr;
		}
		delete[] likedby;
	}
	if (cmnts)
	{
		for (int i = 0; i < coment_count; i++)
		{
			if (cmnts[i])
			{
				delete cmnts[i];
			}
		}
		delete[] cmnts;
	}
}


/*/////////////////////////////////////////////
**************IMPLEMENTATION OF **************
********* FACEBOOK    CLASSS        ***********

**********************************************
////////////////////////////////////////////
///////////////////////////////////////////*/


facebook::facebook()
{
	userlist = 0;
	pages = 0;
	posts = 0;
}

bool facebook::compare_ID(char* par1,const char* par2)
{
	if (strlen(par1) == strlen(par2))
	{
		for (int i = 0; par2[i] != '\0'; i++)
		{
			if (par1[i] != par2[i])
			{
				return false;
			}
		}
		return true;
	}
	
	return false;
}

int facebook::getinteger(string s)
{
	char arr[10];
	int l = 1;
	for (int i = 0; s[l] != '\0'; i++)
	{
		arr[i] = s[l];
		l++;
	}
	arr[l - 1] = '\0';

	int num = atoi(arr);

	return num;
}





void facebook::ReadpagesData()
{
	ifstream fin("pagesss.txt");
	if (!fin)
	{
		cout << "file not found  \n";
	}
	else
	{

		int a;
		fin >> a;
		Page::settotalpage(a);

		pages = new Page*[a];

		for (int i = 0; i < a; i++)
		{
			string id, name;
			fin >> id;
			fin.ignore(1, ' ');
			getline(fin, name, '\n');

			pages[i] = new Page(id, name);

		}

	}


}

void facebook::setCurrentUser(string s)
{
	
	int num = getinteger(s);

	if (num<0 || num>socialuser::gettotalusers() + 1)
	{
		currentuser = nullptr;
	}
	else
	{
		currentuser = userlist[num - 1];
	}
}






void facebook::socialrun()
{
	setCurrentUser("u7");

	Date::setcurrentdate(14,11,2017);

	cout << "current date is successfully set as: "; Date::currentdate.printdate();
	cout << endl;

	if (currentuser != nullptr)
	{
		cout << "current user:  \n";
		currentuser->Print();
		cout << "---------------------------- \n";
		cout << "VIEWING FRIENDLIST OF CURRENT USER:  \n";

		currentuser->viewfriendlist();                 ////VIEWING FRIENDLIST OF CURRENT USER: 
		cout << "------------------------------- \n";
		cout << "PAGES LIKED BY CURRENT USER:  \n";

		currentuser->viewlikedpages();

		currentuser->viewHome();                 /////homepage includes posts(from last 24 hours) of frinds and liked pages.
		currentuser->viewTimeline();

		

		viewPost("post1");

		cout << "-------------------------------\n";
		viewLikeofAPost("post5");

		cout << "////////////Adding new comment///////////////////// \n\n";
		commentOnPost("post5", "new comment has been added to post 5");
		viewPost("post5");


		cout << "-----------------------------\n";
		
		viewPage("p5");

		
		LikeaPost("post5");
		viewLikeofAPost("post5");
		cout << "------------------------------- \n\n";

		shareaPost("post5");              ////share a post on new user's timeline as his new post


		currentuser->viewTimeline();

		

		SearchFacebook("Ali");
		SearchFacebook("home");
		
	}
	else
	{
		cout << "User doesn't exist in the list. \n";
	}
}


void facebook::ReadUsersdata()
{
	ifstream fin;

	fin.open("usersss.txt");
	if (!fin)
	{
		cout << "user not found  \n";
	}
	else
	{
		int a;
		fin >> a;
		socialuser::settotalusers(a);
		userlist = new socialuser*[a];
		int** frnds = new int*[a];
		int** pgs = new int*[a];
		for (int i = 0; i < a; i++)
		{
			frnds[i] = new int[10];
			pgs[i] = new int[10];
			string id, fnam, lnam;
			fin >> id >> fnam >> lnam;

			userlist[i] = new socialuser(id, fnam, lnam);          /////creating objects of users

			string usf;
			int fr = 0;
			while (usf != "-1")
			{
				fin >> usf;
				if (usf != "-1")
				{
					int t = getinteger(usf);
					frnds[i][fr] = t;
					fr++;

				}

			}
			frnds[i][fr] = -1;
			userlist[i]->setfriendcount(fr);

			userlist[i]->allocatefriendlist(fr);

			fr = 0;

			string page;
			int pg = 0;
			while (page != "-1")
			{
				fin >> page;
				if (page != "-1")
				{
					int pgn = getinteger(page);
					pgs[i][pg] = pgn;
					pg++;
				}

			}
			pgs[i][pg] = -1;
			userlist[i]->setlikepagescount(pg);

			userlist[i]->allocatepagelist(pg);

			pg = 0;

			int count = 0;

			for (int j = 0; pgs[i][j] != -1; j++)
			{
				userlist[i]->likepage(count, pages[pgs[i][j] - 1]);         /////....adding liked pages (association)
				count++;
			}


		}
		int c = 0;
		for (int i = 0; i < a; i++)
		{
			c = 0;
			for (int j = 0; frnds[i][j] != -1; j++)
			{
				userlist[i]->addfriend(c, userlist[frnds[i][j] - 1]);         /////....adding friends (association)
				c++;
			}
		}

		for (int i = 0; i < a; i++)
		{
			delete frnds[i];
			delete pgs[i];
		}
		delete[] frnds;
		delete[] pgs;
	}
}

int facebook::getpostinteger(string s)           ////for extracting post number e.g 4 from post 4
{
	char arr[10];
	int l = 4;
	for (int i = 0; s[l] != '\0'; i++)
	{
		arr[i] = s[l];
		l++;
	}
	arr[l - 1] = '\0';

	int num = atoi(arr);

	return num;
}

void facebook::ReadPosts()
{
	ifstream fin("postsss.txt");
	if (!fin)
	{
		cout << "file not found \n";
	}
	else
	{
		int a;
		fin >> a;
		Post::settotalposts(a);
		posts = new Post*[a];

		for (int i = 0; i < a; i++)
		{
			posts[i] = new Post();
			posts[i]->Readpost(fin);   ////read post until activity
			string us;
			fin >> us;
			int no = getinteger(us);
			if (us[0] == 'u')
			{
				posts[i]->setposted_by(us, userlist[no - 1]);
				userlist[no - 1]->addpost(posts[i]);
			}
			else if (us[0] == 'p')
			{
				posts[i]->setposted_by(us, pages[no - 1]);     //// set post* sharedby
				pages[no - 1]->addpost(posts[i]);            ////add post to post** in page
			}

			string like;
			while (like != "-1")
			{
				fin >> like;

				if (like != "-1")
				{
					no = getinteger(like);
					if (like[0] == 'u')
					{
						posts[i]->setlikedby(userlist[no - 1]);    /////...setting likes
					}
					else if (like[0] == 'p')
					{
						posts[i]->setlikedby(pages[no - 1]);
					}
				}
			}
			
		}
		fin.close();
	}

	ifstream file("commentsss.txt");
	if (!file)
	{
		cout << "file not found \n";
	}
	else
	{
		int a;
		file >> a;
		Comment::settotalcomments(a);
		for (int i = 0; i < a; i++)
		{
			string c_id;
			file >> c_id;
			string p_id;
			file >> p_id;
			string u_id;
			file >> u_id;
			string txt;
			file.ignore(1, ' ');
			getline(file, txt, '\n');
			int num = getpostinteger(p_id);
			int num2 = getinteger(u_id);
			if (u_id[0] == 'u')
			{
				posts[num - 1]->add_comment(c_id, txt, userlist[num2 - 1]); //add cmnt to the post which belongs to that commwnt
			}
			else if (u_id[0] == 'p')
			{
				posts[num - 1]->add_comment(c_id, txt, pages[num2 - 1]);
			}
		}

	}


}

socialuser* facebook::getcurrentuser()
{
	return currentuser;
}

void facebook::viewPost(const char* s)
{

	cout << "|||||||||||||||||||||||| Viewing Post by Viewpost()  function |||||||||||||||||||||||||||||||| \n\n";

	for (int i = 0; i < Post::gettotalposts(); i++)
	{
		if (compare_ID(posts[i]->getid(), s))
		{
			posts[i]->Print();
			break;
		}
	}
}

void facebook::viewLikeofAPost(const char* s)
{
	cout << "||||||||||||||||||||||||||Viewing likes of a "<<s<<" |||||||||||||||||||||||||||||||||||| \n\n";

	for (int i = 0; i < Post::gettotalposts(); i++)
	{
		if (compare_ID(posts[i]->getid(), s))
		{
			posts[i]->printLikes();
			break;
		}
	}
	
}

void facebook::commentOnPost(const char* s, string cmnt)
{
	
	for (int i = 0; i < Post::gettotalposts(); i++)
	{
		if (compare_ID(posts[i]->getid(), s))
		{
			posts[i]->addnew_comment(cmnt, facebook::getcurrentuser());
			break;
		}
	}
	
}


void facebook::viewPage(const char* s)
{
	
	cout << "|||||||||||||||||||||||||||| viewing timeline of " << s;
	cout << " with ViewPage() function ||||||||||||||||||||||||||||||||||||| \n\n";
	for (int i = 0; i<Page::gettotalpage(); i++)
	{
		if (compare_ID(pages[i]->getid(), s))
		{
			pages[i]->printPageTimeline();
			break;
		}
	}
	
}

void facebook::LikeaPost(const char* s)
{
	
	cout << "/////////adding a like to  "<<s<<" //////  \n";
	for (int i = 0; i < Post::gettotalposts(); i++)
	{
		if (compare_ID(posts[i]->getid(), s))
		{
			posts[i]->setlikedby(facebook::getcurrentuser());
			break;
		}
	}
	
}

void facebook::shareaPost(const char* s)
{
	
	if (currentuser->getpost_count() < 10)
	{
		for (int i = 0; i < Post::gettotalposts(); i++)
		{
			if (compare_ID(posts[i]->getid(), s))
			{
				currentuser->printname(); cout << " shared " << s << endl;
				currentuser->addnewpost(posts[i]);
				break;
			}

		}
		
	}

	else
	{
		cout << "ERROR: share limit reached  \n";
	}


}

void facebook::SearchFacebook(const char* word)
{
	cout << "|||||||||||||||   SEARCHING   ||||||||||||||| \n";
    currentuser->printname();cout<<" enter '" << word << "' to search  \n";

	
	cout << "Results of search '" << word << "' in Users:  \n\n";
	for (int i = 0; i < socialuser::gettotalusers(); i++)
	{
		userlist[i]->searchstringinUsers(word);

	}
	
	cout << "\nResults of search '" << word << "' in Pages:  \n\n";

	for (int i = 0; i<Page::gettotalpage(); i++)
	{
		pages[i]->searchinPages(word);
	}
	
	cout << "\nResults of search '" << word << "' in Posts:  \n\n";

	for (int i = 0; i < socialuser::gettotalusers(); i++)
	{
		for (int j = 0; j < userlist[i]->getpost_count(); j++)
		{
			userlist[i]->getpost(j)->searchinPosts(word);
		}
	}

	for (int i = 0; i < Page::gettotalpage(); i++)
	{
		for (int j = 0; j < pages[i]->getpost_count();j++)
		{
			pages[i]->getpost(j)->searchinPosts(word);
		}
	}

	cout << "-------------------------------------- \n";
}

void facebook::LoadAllDataforFacebook()
{
	ReadpagesData();
	ReadUsersdata();
	ReadPosts();
}


facebook::~facebook()
{
	

	if (pages)
	{
		for (int i = 0; i < Page::gettotalpage(); i++)
		{
			if (pages[i])
			{
				delete pages[i];
			}
		}
		delete[] pages;
	}


	if (userlist)
	{
		for (int i = 0; i < socialuser::gettotalusers(); i++)
		{
			if (userlist[i])
				delete userlist[i];
		}
		delete[] userlist;
	}

	currentuser = nullptr;

	if (posts)
	{
		delete[] posts;
	}

}


/*/////////////////////////////////////////////
**************IMPLEMENTATION OF **************
*********  PAGE     CLASSS        ***********

**********************************************
////////////////////////////////////////////
///////////////////////////////////////////*/


Page::Page() :Object()
{
	pagetitle = nullptr;
	noofpost = 0;
	postsby_page = nullptr;
}

void Page::settotalpage(int t)
{
	totalpage = t;

}
void Page::printname()
{
	cout << pagetitle;
}

Post* Page::getpost(int i)
{
	if (i >= 0 || i < noofpost)
	{
		return postsby_page[i];
	}
}


void Page::Print()
{
	cout << getid() << "(" << pagetitle <<")"<< endl;

}

void Page::printPageLatest()
{
	for (int i = 0; i < noofpost; i++)
	{
		if (postsby_page[i]->datecheck())
		{
			postsby_page[i]->Print();
		}

	}

}


Page::Page(string id, string title) :Object(id)
{

	pagetitle = new char[title.length() + 1];

	int j = 0;
	for (; title[j] != '\0'; j++)
	{
		pagetitle[j] = title[j];
	}
	pagetitle[j] = '\0';

	noofpost = 0;
	postsby_page = nullptr;
}

char* Page::getPagetitle()
{
	return pagetitle;
}

int Page::gettotalpage()
{
	return totalpage;
}

int Page::getpost_count()
{
	return noofpost;
}

void Page::addpost(Post* ptr)
{
	if (noofpost == 0)
	{
		postsby_page = new Post*[10];
		for (int i = 0; i < 10; i++)
		{
			postsby_page[i] = nullptr;
		}
		postsby_page[noofpost] = ptr;
		noofpost++;
	}
	else if (noofpost > 0 && noofpost < 10)
	{
		postsby_page[noofpost] = ptr;
		noofpost++;
	}
	else
	{
		cout << "Error: Post limit reached  \n";
	}
}

void Page::searchinPages(const char* word)
{
	if (strFind(getPagetitle(), word))
	{
		Print();
	}
}


void Page::printPageTimeline()
{
	for (int i = 0; i < noofpost; i++)
	{
		postsby_page[i]->Print();
	}

}

Page::~Page()
{
	if (pagetitle != nullptr)
	{
		delete[] pagetitle;
	}

	if (postsby_page)
	{
		for (int i = 0; i < noofpost; i++)
		{
			if (postsby_page[i])
				delete postsby_page[i];
		}
		delete[] postsby_page;
	}
}


/*/////////////////////////////////////////////
**************IMPLEMENTATION OF **************
*********  COMMENT    CLASSS        ***********

**********************************************
////////////////////////////////////////////
///////////////////////////////////////////*/

Comment::Comment()
{
	comnt_id = 0;
	cmnt_text = 0;
	comnted_by = 0;
}

Comment::Comment(string id, string text)
{
	comnt_id = new char[id.length() + 1];
	int i = 0;
	for (; id[i] != '\0'; i++)
	{
		comnt_id[i] = id[i];
	}
	comnt_id[i] = '\0';

	cmnt_text = new char[text.length() + 1];
	int j = 0;
	for (; text[j] != '\0'; j++)
	{
		cmnt_text[j] = text[j];
	}
	cmnt_text[j] = '\0';
	comnted_by = nullptr;
}

void Comment::setnew_id()
{
	int newid = Comment::gettotalcomments() + 1;
	totalcomments++;
	ostringstream str1;
	str1 << newid;
	string n = str1.str();

	comnt_id = new char[n.length() + 2];
	comnt_id[0] = 'c';
	int l = 1;
	for (int i = 0; n[i] != '\0'; i++)
	{
		comnt_id[l] = n[i];
		l++;
	}
	comnt_id[l] = '\0';

}


void Comment::settotalcomments(int a)
{
	totalcomments = a;
}

int Comment::gettotalcomments()
{
	return totalcomments;
}

void Comment::setdescription(string text)
{
	cmnt_text = new char[text.length() + 1];
	int j = 0;
	for (; text[j] != '\0'; j++)
	{
		cmnt_text[j] = text[j];
	}
	cmnt_text[j] = '\0';
}


void Comment::setcomnted_by(Object* ptr)
{

		comnted_by = ptr;
}




void Comment::Print()
{
	comnted_by->printname(); cout<< ":  " << cmnt_text << endl;
}


Comment::~Comment()
{
	if (cmnt_text)
	{
		delete[] cmnt_text;
	}

	if (comnt_id)
	{
		delete[] comnt_id;
	}

	comnted_by = nullptr;

}


/*/////////////////////////////////////////////
**************IMPLEMENTATION OF **************
*********  ACTIVITY     CLASSS        ***********

**********************************************
////////////////////////////////////////////
///////////////////////////////////////////*/


Activity::Activity()
{
	type = 0;
	value = 0;
}

Activity::Activity(const Activity& rhs)
{
	type = new char[strlen(rhs.type) + 1];

	int i = 0;
	for (; rhs.type[i] != '\0'; i++)
	{
		type[i] = rhs.type[i];
	}
	type[i] = '\0';

	value = new char[strlen(rhs.value) + 1];

	int j = 0;
	for (; rhs.value[j] != '\0'; j++)
	{
		value[j] = rhs.value[j];
	}
	value[j] = '\0';
}

void Activity::settype(int i)
{
    if (i == 1)
	{
		string t = "feeling";
		type = new char[t.length() + 1];
		int i = 0;
		for (; t[i] != '\0'; i++)
		{
			type[i] = t[i];
		}
		type[i] = '\0';
	}
	else if (i == 2)
	{
		string t = "thinking about";
		type = new char[t.length() + 1];
		int i = 0;
		for (; t[i] != '\0'; i++)
		{
			type[i] = t[i];
		}
		type[i] = '\0';
	}
	else if (i == 3)
	{
		string t = "making";
		type = new char[t.length() + 1];
		int i = 0;
		for (; t[i] != '\0'; i++)
		{
			type[i] = t[i];
		}
		type[i] = '\0';
	}
	else if (i == 4)
	{
		string t = "celebrating";
		type = new char[t.length() + 1];
		int i = 0;
		for (; t[i] != '\0'; i++)
		{
			type[i] = t[i];
		}
		type[i] = '\0';
	}
}

void Activity::setvalue(string val)
{
	value = new char[val.length() + 1];
	int i = 0;
	for (; val[i] != '\0'; i++)
	{
		value[i] = val[i];
	}
	value[i] = '\0';

}

void Activity::printactivity()
{
		cout << type << "  " << value << endl;
}

Activity::~Activity()
{
	if (type)
	{
		delete[] type;
	}

	if (value)
	{
		delete[] value;
	}
}


/*/////////////////////////////////////////////
**************                  **************
*********      MAIN FUNCTION      ***********

**********************************************
////////////////////////////////////////////
///////////////////////////////////////////*/



void main()
{
	facebook f1;
	f1.LoadAllDataforFacebook();
	f1.socialrun();


	system("PAUSE");
}



