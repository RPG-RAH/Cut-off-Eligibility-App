#include "./project.cpp"
//Main Program
int main(int argc,char* argv[])
{
	Student s1;
	int result=s1.search(*(argv+1));
	return result;
}//End of Main Program

