#include "QuestionTree.h"
#include <string.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdlib.h>

QuestionTree::QuestionTree()
{
    //ctor
}

QuestionTree::~QuestionTree()
{
    //dtor
}

/*
Function prototype:
void QuestionTree::addQuestion(string,string)

Function description:
This method adds a question to the binary search tree given it's position. This
sorts the questions by the string of their location, with y or n representing yes or no node branches.

Example:
QuestionTree *q;
q->addQuestion("Is it hard?, "ynyyn");

Preconditions:
There must be a proper sequence prior to where the new question is being added.
Adding location must be a NULL child of a parent and either be in the yes or no node location.

Post conditions:
Question node is added with NULL children and the updated parent. Parents child pointer is also
updated accordingly.
*/
void QuestionTree::addQuestion(std::string in_question, std::string pos)
{
    Question *temp=new Question;
    temp->question=in_question;
    temp->position=pos;
    if(root==NULL)
    {
        root = temp;
        root->parent = NULL;
        root->yesNode = NULL;
        root->noNode = NULL;
    }
    else
    {
        char posArray[pos.size()+1];
        strcpy(posArray,pos.c_str());
        Question *runner=root;
        Question *place=NULL;
        int i=0;
        char last;
        while(runner!=NULL)
        {
            place=runner;
            last=posArray[i];
            if(posArray[i]=='y')
                runner=runner->yesNode;
            else
                runner=runner->noNode;
            i++;
        }
        temp->parent=place;
        if(last=='y')
        {
            place->yesNode=temp;
            temp->yesNode=NULL;
            temp->noNode=NULL;
        }
        else
        {
            place->noNode=temp;
            temp->yesNode=NULL;
            temp->noNode=NULL;
        }
    }
}

/*
Function prototype:
Question* QuestionTree::getRoot()

Function description:
Getter method for the root of the tree.

Example:
QuestionTree *q;
q->getRoot();

Preconditions:
Tree must be built with at least one node (the root).

Post conditions:
Root is now accessible in main.
*/
Question* QuestionTree::getRoot()
{
    return root;
}

/*
Function prototype:
bool QuestionTree::isFound()

Function description:
Returns boolean status of whether a question/answer was found after being set.

Example:
QuestionTree *q;
q->isFound();

Preconditions:
Found must be set either by selecting find question or find answer.

Post conditions:
Found is returned;
*/
bool QuestionTree::isFound()
{
    return found;
}

/*
Function prototype:
void QuestionTree::setFound()

Function description:
Resets founds status to false for future searches.

Example:
QuestionTree *q;
q->setFound();

Preconditions:
Found must be set either by selecting find question or find answer.

Post conditions:
Found is reset to false for future searches.
*/
void QuestionTree::setFound()
{
    found=false;
}

/*
Function prototype:
Question* QuestionTree::getNo(Question*)

Function description:
Returns the noNode of a given node.

Example:
QuestionTree *q;
q->getNo(Question *node);

Preconditions:
Node location must be found and passed through. Tree must be built with both nodes.

Post conditions:
The noNode of the given node is returned.
*/
Question* QuestionTree::getNo(Question *onQuestion)
{
    return onQuestion->noNode;
}

/*
Function prototype:
Question* QuestionTree::getYes(Question*)

Function description:
Returns the yesNode of a given node.

Example:
QuestionTree *q;
q->getYes(Question *node);

Preconditions:
Node location must be found and passed through. Tree must be built with both nodes.

Post conditions:
The yesNode of the given node is returned.
*/
Question* QuestionTree::getYes(Question *onQuestion)
{
    return onQuestion->yesNode;
}

/*
Function prototype:
bool QuestionTree::isNotEnd(Question*)

Function description:
Determines if the given node's question is not at the end of the tree.

Example:
QuestionTree *q;
q->isNotEnd(Question *node);

Preconditions:
Node location must be found and passed through. Tree must be built with both nodes.

Post conditions:
Boolean is returned to determine if the question not at the end of the tree for dependent conditions.
*/
bool QuestionTree::isNotEnd(Question *onQuestion)
{
    if(onQuestion!=NULL)
        return true;
    else
        return false;
}

/*
Function prototype:
bool QuestionTree::isGuess(Question*)

Function description:
Determines if the given node's question is a final guess.

Example:
QuestionTree *q;
q->isGuess(Question *node);

Preconditions:
Node location must be found and passed through. Tree must be built with both nodes.

Post conditions:
Boolean is returned to determine if the question at the end of the tree for dependent conditions.
*/
bool QuestionTree::isGuess(Question *onQuestion)
{
    if(onQuestion->yesNode==NULL)
        return true;
    else
        return false;
}

/*
Function prototype:
void QuestionTree::updateQuestions(Question*)

Function description:
Expands the question base of the program using the user input. It is called after the computer loses.

Example:
QuestionTree *q;
q->updateQuestions(Question *node);

Preconditions:
Node location must be found and passed through. Tree must be built, game must be played,
and computer must have lost.

Post conditions:
User input is taken, the previous guess has been put in the right place of the user's new
question, and the user's new answer is also linked to the new question. Also the next function
is called to update the text file.
*/
void QuestionTree::updateQuestions(Question *onQuestion)
{
    std::string userAnswer;
    std::string userQuestion;
    std::string selection;
    std::cout<<"What were you thinking of?"<<std::endl//expects an answer with proper article
    std::cin.ignore();
    getline(std::cin,userAnswer);
    std::cout<<"What is a question to differentiate between "<<userAnswer<<" and "<<onQuestion->question<<"?"<<std::endl;//expects full question with question mark and proper capitalization
    getline(std::cin,userQuestion);
    std::cout<<"Would your answer be a yes or a no to this question (enter y or n)?"<<std::endl;//Determines where to put user's answer and the previous answer
    std::cin>>selection;

    Question *newQ=new Question;
    Question *newA=new Question;
    newQ->question=userQuestion;
    newQ->position=onQuestion->position;
    newA->question=userAnswer;
    newA->noNode=NULL;
    newA->yesNode=NULL;

    if(onQuestion==onQuestion->parent->yesNode)
        onQuestion->parent->yesNode=newQ;
    else
        onQuestion->parent->noNode=newQ;
    if(selection=="y")//Places user's answer and previous answer in the proper spots
    {
        newQ->noNode=onQuestion;
        onQuestion->position=onQuestion->position+"n";
        newQ->yesNode=newA;
        newA->position=newQ->position+"y";
    }
    else
    {
        newQ->yesNode=onQuestion;
        onQuestion->position=onQuestion->position+"y";
        newQ->noNode=newA;
        newA->position=newQ->position+"n";
    }
    onQuestion->parent=newQ;
    newA->parent=newQ;
    replaceQuestion(onQuestion,newQ,newA);//updates text file for future games
    std::cout<<"\nThank you for expanding my knowledge!\n"<<std::endl;
}

/*
Function prototype:
void QuestionTree::replaceQuestion(Question*,Question*,Question*)

Function description:
Updates the text file to include the users new question and answer as well as
the old answer's new location.

Example:
QuestionTree *q;
q->replaceQuestion(Question*,Question*,Question*);

Preconditions:
Node locations must be found and passed through. Text file must be present.

Post conditions:
Text file is rewritten for future games.
*/
void QuestionTree::replaceQuestion(Question *onQuestion, Question *newQ, Question *newA)
{
    std::ifstream filein;
    filein.open("QuestionFile.txt");
    std::ofstream fileout("temp.txt");
    while(true)//copies original file to temp, with modifications of the new question, answer, and the old answer's new position
    {
        std::string line,pos,ques;
        std::getline(filein,line);
        std::stringstream s(line);
        std::getline(s,pos,',');
        std::getline(s,ques,',');
        if(filein.eof())
            break;
        if(ques==onQuestion->question)
        {
            fileout<<newQ->position<<","<<newQ->question<<'\n';
        }
        else
        {
            fileout<<line<<'\n';
        }
    }
    fileout<<onQuestion->position<<","<<onQuestion->question<<'\n';
    fileout<<newA->position<<","<<newA->question;
    filein.close();
    fileout.close();

    std::ofstream file;
    std::ifstream infile;
    infile.open("temp.txt");
    file.open("QuestionFile.txt");
    while(!infile.eof())//writes over original file with temp
    {
        std::string line;
        std::getline(infile,line);
        file<<line<<'\n';
    }
    remove("temp.txt");
    file.close();
    infile.close();
}

/*
Function prototype:
void QuestionTree::changeQuestion(Question*,string,string)

Function description:
Allows the user to change a question or answer in the tree.

Example:
QuestionTree *q;
q->changeQuestion(Question*,string,string);

Preconditions:
Tree must be built with a root and the string of the question to be replaced
and what it is to be replaced with must be known.

Post conditions:
Question for the found node is changed to the user's specifications.
*/
void QuestionTree::changeQuestion(Question *runner, std::string oldQuestion, std::string newQuestion)
{
    if(runner->question==oldQuestion)
    {
        runner->question=newQuestion;
        found=true;
    }
    if(runner->noNode!=NULL)
    {
        changeQuestion(runner->noNode,oldQuestion,newQuestion);
    }
    if(runner->yesNode!=NULL)
    {
        changeQuestion(runner->yesNode,oldQuestion,newQuestion);
    }
}

/*
Function prototype:
void QuestionTree::printQuestions(Question*)

Function description:
Allows the user to see all the questions and answers in the tree.

Example:
QuestionTree *q;
q->printQuestions(Question*);

Preconditions:
Tree must be built with a root.

Post conditions:
Question tree is printed.
*/
void QuestionTree::printQuestions(Question *runner)
{
    if(isGuess(runner))
    {
        std::cout<<"Are you thinking of "<<runner->question<<"?"<<std::endl;
    }
    else
        std::cout<<runner->question<<std::endl;
    if(runner->yesNode!=NULL)
    {
        printQuestions(runner->yesNode);
    }
    if(runner->noNode!=NULL)
    {
        printQuestions(runner->noNode);
    }
}
