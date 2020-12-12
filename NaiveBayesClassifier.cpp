#include<iostream>
#include<fstream>
using namespace std;

struct Person//tuple from the data set
{
    char attributes[16];
    char party[20];
};

Person people[500];//all people from the data set
int peopleCnt;//number of people in the data set

void readFile(const char* fileName)
{
    ifstream file;
    file.open(fileName);
    if(!file.is_open())
    {
        cout<<"File did not opened!"<<endl;
        return;
    }

    peopleCnt = 0;
    int attr = 0;

    char c;
    while(file.get(c))
    {
        if(c == '\n') //we've done reading the current person, start reading the next
        {
            peopleCnt++;//add new person
            attr = 0;//start attributes from beginning
        }
        else if((c >= 'a' && c <= 'z') || c == '?')
        {
            if(c == 'y'||c == 'n'||c == '?')
            {
                people[peopleCnt].attributes[attr] = c;
                attr++;//going to next attribute
            }
            else//read the party name (class name)
            {
                int i=0;
                while(c != ',')
                {
                    people[peopleCnt].party[i] = c;
                    i++;
                    file.get(c);
                }
                people[peopleCnt].party[i] = '\0';//put an end to the party name
            }
        }

    }
}


void solve()
{


}
int main()
{
    readFile("votes.txt");
    return 0;
}
