#include<iostrema>
#include<fstream>
using namespace std;

struct Person
{
    char attributes[16];
    char party[20];
}

Person people[500];
int peopleCnt;

void readFile(const char* fileName)
{
    ifstream file;
    file.open("fileName");
    if(!file.is_open())
    {
        cout<<"File did not opened!"<<endl;
        return;
    }

    peopleCnt = 0;

    char c;
    while(file.get(c))
    {


    }

}


int main()
{

    return 0;
}
