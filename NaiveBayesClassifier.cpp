#include<iostream>
#include<fstream>
#include<string.h>
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
    int testingSetSize = peopleCnt / 10;
    double sumAccuracy = 0.0;

    for(int i = 0 ; i < 10; i++)
    {
        int startingPosition = i*testingSetSize;
        int endingPosition = startingPosition + testingSetSize;

        int cntDemocrats = 0;
        int cntRepublicans = 0;

        //counting number of republicans and democrats outside the testing set
        for(int j = 0; j<peopleCnt; j++)
        {
            if(j<startingPosition || j > endingPosition)
            {
                if(strcmp(people[j].party,"democrat") == 0)
                    cntDemocrats++;
                if(strcmp(people[j].party,"republican") == 0)
                    cntRepublicans++;
            }
        }
        //cout<<"Num of democrats: "<<cntDemocrats<<endl;
        //cout<<"Num of republicans: "<<cntRepublicans<<endl;
        double democratProbability = (double)cntDemocrats / cntDemocrats + cntRepublicans;
        double republicanProbability = (double)cntRepublicans / cntDemocrats + cntRepublicans;

        double attrProbDemocrats[16][2];
        double attrProbRepublicans[16][2];

        for(int attr = 0; attr<16; attr++)
        {
            int yDem = 0;
            int nDem = 0;
            int yRep = 0;
            int nRep = 0;
            for(int k = 0; k<peopleCnt; k++)
            {
                if(k<startingPosition || k>endingPosition)
                {
                    char ch = people[k].attributes[attr];
                    if(strcmp(people[k].party,"democrat") == 0)
                    {
                        if(ch == 'y')
                        {
                            yDem++;
                        }
                        else if(ch == 'n')
                        {
                            nDem++;
                        }
                    }
                    else if(strcmp(people[k].party,"republican") == 0)
                    {
                        if(ch == 'y')
                        {
                            yRep++;
                        }
                        else if(ch == 'n')
                        {
                            nRep++;
                        }
                    }
                }
            }

            attrProbDemocrats[attr][0] = (double)yDem / (double)cntDemocrats;
            attrProbDemocrats[attr][1] = (double)nDem / (double)cntDemocrats;
            attrProbRepublicans[attr][0] = (double)yRep / (double)cntRepublicans;
            attrProbRepublicans[attr][1] = (double)nRep / (double)cntRepublicans;
        }


        int cntRightClassifications = 0;
        for(int p = startingPosition; p<= endingPosition; p++)
        {
            double probToBeDemocrat = democratProbability;
            double probToBeRepublican = republicanProbability;

            for(int attr = 0; attr<16; attr++)
            {
                if(people[p].attributes[attr] == 'y')
                {
                    probToBeDemocrat *= attrProbDemocrats[attr][0];
                    probToBeRepublican *= attrProbRepublicans[attr][0];
                }
                else if(people[p].attributes[attr] == 'n')
                {
                    probToBeDemocrat *= attrProbDemocrats[attr][1];
                    probToBeRepublican *= attrProbRepublicans[attr][1];
                }
            }

            if(probToBeDemocrat > probToBeRepublican)
            {
                if(strcmp(people[p].party,"democrat") == 0)
                    cntRightClassifications++;
            }
            else
            {
                if(strcmp(people[p].party,"republican") == 0)
                    cntRightClassifications++;
            }
        }
        double accuracy = (double)cntRightClassifications / (double)(endingPosition - startingPosition + 1);
        sumAccuracy+=accuracy;
        cout<<"Accuracy for "<<i+1<<" set is: "<<accuracy<<endl;
    }
    cout<<endl;
    cout<<"Average Accuracy is: "<<sumAccuracy/10<<endl;
}

int main()
{
    readFile("votes.txt");
    solve();
    return 0;
}
