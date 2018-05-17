#include "./project.cpp"
//Main Program
int main(int argc,char* argv[])
{
	Student s1;
	bool result=s1.placementEligibility(*(argv+1));
	return result?0:-1;
}//End of Main Program

