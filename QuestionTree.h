#ifndef QUESTIONTREE_H
#define QUESTIONTREE_H
#include <iostream>
#include <vector>

struct Question{
    std::string question;
    std::string position;
    Question *parent;
    Question *yesNode;
    Question *noNode;

    Question(){};
    Question(std::string in_question)
    {
        question = in_question;
    }
};
class QuestionTree
{
    public:
        QuestionTree();
        virtual ~QuestionTree();
        void addQuestion(std::string question, std::string pos);
        Question *getRoot();
        Question *getYes(Question *onQuestion);
        Question *getNo(Question *onQuestion);
        bool isNotEnd(Question *onQuestion);
        bool isGuess(Question *onQuestion);
        void updateQuestions(Question *onQuestion);
        void replaceQuestion(Question *onQuestion, Question *newQ, Question *newA);
        void changeQuestion(Question *node, std::string oldQuestion, std::string newQuestion);
        bool isFound();
        void setFound();
        bool found;
        void printQuestions(Question *node);
        void newQuestion(Question *runner, std::string newques,std::string prevques,std::string ans);
        void recordFile(Question *runner);
        std::vector<std::string> returnFile();
        void clearFile();
        void writeToFile();
    protected:
    private:
        Question *root;
        std::vector<std::string> filestuff;
};

#endif // QUESTIONTREE_H
