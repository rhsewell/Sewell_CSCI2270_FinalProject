#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include "QuestionTree.h"

using namespace std;

int main()
{
    cout<<"Welcome to the ever-learning guessing game!"<<
            "\nThink of something and I will try to guess it."<<
            "\nBut remember the more you play, the better I get."<<
            "\nGood Luck!\n"<<
            "\nInstructions:"<<
            "\nChoose from the menu below, entering the number of your choice."<<
            "\nWhile playing, answering by entering y for yes or n for no."<<
            "\nWhen adding to my question base please adhere to the same format"<<
            "\nas the other questions.\n"<<endl;

    //Reads in the file and creates the file portion of the tree
    string in_question;
    string position;
    QuestionTree *q=new QuestionTree();
    string f="QuestionFile.txt";
    ifstream file;
    file.open(f.c_str());
    while(!file.eof())
    {
        string line;
        getline(file,line);
        stringstream s(line);
        getline(s,position,',');
        getline(s,in_question,',');
        q->addQuestion(in_question,position);
    }
    file.close();

    //Main program loop
    int option;
    string ques,newques;
    while(option!=5)
    {
        option=0;
        cout<<"=============Main Menu============"<<endl;
        cout<<"1. Play Game"<<endl;
        cout<<"2. Change a Question"<<endl;
        cout<<"3. Change an Answer"<<endl;
        cout<<"4. Print Question and Answer Base"<<endl;
        cout<<"5. Quit"<<endl;
        cin>>option;
        if(option==1)
        {
            string selection;
            cout<<"Starting new game:\n"<<endl;
            Question *onQuestion=q->getRoot();
            while(q->isNotEnd(onQuestion))
            {
                if(q->isGuess(onQuestion))//Changes output format for a guess
                {
                    cout<<"Are you thinking of "<<onQuestion->question<<"?"<<endl;
                    cin>>selection;
                    if(selection == "y")
                    {
                        cout<<"I win!\n"<<endl;
                        break;
                    }
                    else if(selection == "n")
                    {
                        cout<<"You win!\n"<<endl;
                        q->updateQuestions(onQuestion);
                        break;
                    }
                    else
                        cout<<"Invalid selection, please either choose a y for yes or n for no.\n"<<endl;
                }
                else//states question
                {
                    cout<<onQuestion->question<<endl;
                    cin>>selection;
                    if(selection == "y")
                        onQuestion=q->getYes(onQuestion);
                    else if(selection == "n")
                        onQuestion=q->getNo(onQuestion);
                    else
                        cout<<"Invalid selection, please either choose a y for yes or n for no.\n"<<endl;
                }
            }
        }
        if(option==2)
        {
            cout<<"Enter the question to be changed?"<<endl;
            cin.ignore();
            getline(cin,ques);
            cout<<"What should it be changed to?"<<endl;
            getline(cin,newques);
            q->changeQuestion(q->getRoot(),ques,newques);
            if(q->isFound()){
                cout<<"Question found and changed.\n"<<endl;
                q->setFound();
            }
            else
                cout<<"Question not found.\n"<<endl;
        }
        if(option==3)
        {
            cout<<"Enter the answer to be changed be changed?"<<endl;
            cin.ignore();
            getline(cin,ques);
            cout<<"What should it be changed to?"<<endl;
            getline(cin,newques);
            q->changeQuestion(q->getRoot(),ques,newques);
            if(q->isFound()){
                cout<<"Answer found and changed.\n"<<endl;
                q->setFound();
            }
            else
                cout<<"Answer not found.\n"<<endl;
        }
        if(option==4)
        {
            cout<<"\n";
            q->printQuestions(q->getRoot());
            cout<<"\n";
        }
    }
    cout<<"Goodbye!"<<endl;
    delete q;
    return 0;
}
