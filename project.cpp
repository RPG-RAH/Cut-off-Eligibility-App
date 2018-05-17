//Header Files
#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <stdlib.h>

using namespace std;

//Macros
#define data_file "datafile.txt"
#define index_file "indexfile.txt"
#define LEN 150
#define MIN_GRADE 6.75

//Classes
class Student
{
	char usn[20],name[100],age[3],cgpa[5],buffd[LEN],buffi[LEN];
	void pack(),unpack();
	fstream fd,fi;

	public :
		int add(char[],char[],char[],char[]),del(char[]),search(char[]);
		int display();
		bool placementEligibility(char[]);
};


//Function Definition
void Student::pack()
{
	strcpy(buffd,usn);
	strcat(buffd,"|");
	strcat(buffd,name);
	strcat(buffd,"|");
	strcat(buffd,age);
	strcat(buffd,"|");
	strcat(buffd,cgpa);
	strcat(buffd,"\n");
}

void Student::unpack()
{
	strcpy(usn,strtok(buffd,"|"));
	strcpy(name,strtok(NULL,"|"));
	strcpy(age,strtok(NULL,"|"));
	strcpy(cgpa,strtok(NULL,"\n"));
}

int Student::add(char USN[],char Name[],char Age[], char CGPA[])
{
	fd.open(data_file,ios::out|ios::app);
	fi.open(index_file,ios::out|ios::app);
	if(fi.fail()||fd.fail())
		return 1;
	strcpy(usn,USN);
	strcpy(name,Name);
	strcpy(age,Age);
	strcpy(cgpa,CGPA);
	pack();
	sprintf(buffi,"%s|%d\n",usn,(int)fd.tellp());
	fd<<buffd;
	fi<<buffi;
	fi.close();
	fd.close();
	return 0;
}

int Student::display()
{
	fd.open(data_file,ios::in);
	int i=0;

	fstream file;
	file.open("displayOutput",ios::trunc|ios::out);
	file.close();

	file.open("displayOutput",ios::app|ios::out);
	if(fd.good())
	while(fd>>buffd)
	{
		unpack();
		file<<endl<<"USN : "<<usn<<endl<<"Name : "<<name<<endl<<"Age : "<<age<<endl<<"CGPA : "<<cgpa<<endl<<"\t\t-------\t\t"<<endl;
	}
	else return -1;
	file.close();
	fd.close();
	return 0;
}


int Student::search(char key[])
{
	char pos[6];
	int i=0;
	fstream file;
	file.open("displayOutput",ios::out|ios::trunc);
	file.close();

	fd.open(data_file,ios::in);
	fi.open(index_file,ios::in);
	file.open("displayOutput",ios::app|ios::out);
	if(fd.good()&&fi.good())
	while(fi>>buffi)
	{
		strcpy(usn,strtok(buffi,"|"));
		strcpy(pos,strtok(NULL,"\n"));
		if((strcmp(usn,key)==0))
		{
			fd.seekg(atoi(pos));
			fd>>buffd;
			unpack();
			file<<endl<<"USN : "<<usn<<endl<<"Name : "<<name<<endl<<"Age : "<<age<<endl
			<<"CGPA : "<<cgpa<<endl<<"\t\t-------\t\t"<<endl;
			fi.close();
			fd.close();
			file.close();
			return 0;
		}
	}

	else cout<<"Error!! :: file problem"<<endl;

	cout<<"No Record Found :-("<<endl;
	fi.close();
	fd.close();
	file.close();
	return -1;
}

int Student::del(char key[])
{
	char pos[6],prev_pos[6],buffi_copy[LEN];
	int i=0,flag=1;
	ostringstream is,ds;
	fd.open(data_file,ios::in);
	fi.open(index_file,ios::in);
	if(fd.good()&&fi.good())
	{
		while(fi>>buffi)
		{
			strcpy(buffi_copy,buffi);
			strcpy(usn,strtok(buffi_copy,"|"));
			strcpy(pos,strtok(NULL,"\n"));
			if(strcmp(usn,key)!=0)
			{
				fd.seekg(atoi(pos));
				fd>>buffd;
				ds<<buffd<<endl;
				if(flag==0)
				{
					//Next Record write on This Prev Pos
					strcpy(pos,prev_pos);
					sprintf(buffi,"%s|%s",usn,pos);
				}
				is<<buffi<<endl;
			}
			else
			{
				strcpy(prev_pos,pos);
				flag=0;
			}
		}
		fi.close();
		fd.close();
		if(flag==0)
		{
			fd.open(data_file,ios::out|ios::trunc);
			fi.open(index_file,ios::out|ios::trunc);
			fd<<ds.str();
			fi<<is.str();
			fi.close();
			fd.close();
		}
	}
	else 
		cout<<"Error !!: file problem"<<endl;
	return flag;
}

bool Student::placementEligibility(char key[])
{
	bool eligible=false;
	if(this->search(key)!=-1)
		if(atof(cgpa)>=MIN_GRADE)
			eligible=true;
	fstream file;
	file.open("displayOutput",ios::trunc|ios::out);
	file<<endl<<"USN : "<<usn<<endl<<"Name : "<<name<<endl<<"Age : "<<age<<endl
	<<"CGPA : "<<cgpa<<endl<<"\t\t-------\t\t"<<endl;
	file<<endl<<(eligible?"Student is Eligible":"Student is not Eligible")<<endl<<endl;
	file.close();
	return eligible;
}
