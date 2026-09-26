
#include <iostream>
#include<string>
#include<cmath>
#include<cstdlib>

using namespace std;

enum enQuestionLevel { EasyLevel = 1 , MedLevel = 2 , HardLevel = 3 , MixLevel = 4 };
enum enOperationType { Add = 1 , Sub = 2 , Mult = 3 , Div = 4 , MixOp = 5 };

string GetOpTypeSymbol(enOperationType OpType)
{
    switch (OpType)
    {
    case enOperationType::Add:
        return " + ";
    case enOperationType::Sub:
        return " - ";
    case enOperationType::Mult:
        return " * ";
    case enOperationType::Div:
        return " / ";
    default:
        return " Mix ";
    }
}

string GetQuestionLevelText(enQuestionLevel QuestionLevel)
{
    string arrQuestionLevelText[4] = { " Easy " , " Med " , " Hard " , " Mix " };
    return arrQuestionLevelText[QuestionLevel - 1];
}

int RandomNumber(int From, int To)
{
    int randNum = rand() % (To - From + 1) + From;
    return randNum;
}

void SetScreenColor(bool Right)
{
    if (Right)
        system("color 2F");
    else
    {
        system("color 4F");
        cout << "\a";
    }
    

}

short ReadHowManyQuestions()
{
    short NumberOfQuestions;
    do
    {
        cout << " How many question do you want to answer ?";
        cin >> NumberOfQuestions;
    } while (NumberOfQuestions < 1 || NumberOfQuestions>10);

    return NumberOfQuestions;
}

enQuestionLevel ReadQuestionLevel()
{
    short QuestionLevel = 0;
    do
    { 
        cout << " Enter Question Level [1] Easy , [2] Med , [3] Hard , [4] Mix ?";
        cin >> QuestionLevel;
    } while (QuestionLevel < 1 || QuestionLevel>4);

    return enQuestionLevel(QuestionLevel);
}

enOperationType ReadOpType()
{
    short OpType ;
    do
    {
        cout << " Enter Operation Type [1] Add , [2] Sub , [3] Mult , [4] Div , [5] Mix ?";
        cin >> OpType;
    } while (OpType < 1 || OpType>5);

    return enOperationType(OpType);
}

struct stQuestion
{
    int Number1 = 0;
    int Number2 = 0;
    enQuestionLevel QuestionLevel;
    enOperationType OperationType;
    int CorrectAnswer = 0;
    int PlayerAnswer = 0;
    bool AnswerResult = false;
};

struct stQuizz
{
    stQuestion QuestionList[100];
    short NumberOfQuestions;
    enQuestionLevel QuestionLevel;
    enOperationType OpType;
    short NumberOfWrongAnswer = 0;
    short NumberOfCorrectAnswer = 0;
    bool isPass = false;
};

int SimpleCalculator(int Number1, int Number2, enOperationType OpType)
{
    switch (OpType)
    {
    case enOperationType::Add:
        return Number1 + Number2;
    case enOperationType::Sub:
        return Number1 - Number2;
    case enOperationType::Mult:
        return Number1 * Number2;
    case enOperationType::Div:
        return Number1 / Number2;
    default:
        return Number1 + Number2;
    }


}

enOperationType GetRandomOperationType()
{
    int Op = RandomNumber(1, 4);
    return enOperationType(Op);
}

stQuestion GenerateQuestion(enQuestionLevel QuestionLevel, enOperationType OpType)
{
    stQuestion Question;
    if (QuestionLevel == enQuestionLevel::MixLevel)
    {
        QuestionLevel = enQuestionLevel(RandomNumber(1, 3));
    }
    if(OpType==enOperationType::MixOp)
    {
        OpType = GetRandomOperationType();
    }

    Question.OperationType = OpType;

    switch (QuestionLevel)
    {
    case enQuestionLevel::EasyLevel:
        Question.Number1 = RandomNumber(1, 10);
        Question.Number2 = RandomNumber(1, 10);
        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);

        Question.QuestionLevel = QuestionLevel;
        return Question;


    case enQuestionLevel::MedLevel:
        Question.Number1 = RandomNumber(10, 50);
        Question.Number2 = RandomNumber(10, 50);
        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);

        Question.QuestionLevel = QuestionLevel;
        return Question;


    case enQuestionLevel::HardLevel:
        Question.Number1 = RandomNumber(50, 100);
        Question.Number2 = RandomNumber(50, 100);
        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);

        Question.QuestionLevel = QuestionLevel;
        return Question;

    }

    return Question;
}

void GenerateQuizzQuestions(stQuizz& Quizz)
{
    for (short Question = 0;Question < Quizz.NumberOfQuestions;Question++)
    {
        Quizz.QuestionList[Question] = GenerateQuestion(Quizz.QuestionLevel, Quizz.OpType);
    }
}

int ReadQuestionAnswer()
{
    int Answer = 0;
    cin >> Answer;
    return Answer;
}

void PrintTheQuestion(stQuizz& Quizz, short QuestionNumber)
{
    cout << "\n";
    cout << " Question [" << QuestionNumber + 1 << "/" << Quizz.NumberOfQuestions << "]\n\n";
    cout << Quizz.QuestionList[QuestionNumber].Number1;
    cout << GetOpTypeSymbol(Quizz.QuestionList[QuestionNumber].OperationType);
    cout << Quizz.QuestionList[QuestionNumber].Number2;
    cout << "\n_______________________________________________" << endl;
}

void CorrectTheQuestionAnswer(stQuizz& Quizz, short QuestionNumber)
{
    if (Quizz.QuestionList[QuestionNumber].PlayerAnswer != Quizz.QuestionList[QuestionNumber].CorrectAnswer)
    {
        Quizz.QuestionList[QuestionNumber].AnswerResult = false;
        Quizz.NumberOfWrongAnswer++;

        cout << "Wrong Answer :-(\n";
        cout << "The Right Answer is : ";
        cout << Quizz.QuestionList[QuestionNumber].CorrectAnswer;
        cout << "\n";
    }
    else
    {
        Quizz.QuestionList[QuestionNumber].AnswerResult = true;
        Quizz.NumberOfCorrectAnswer++;
        cout << "Right Answer :-) \n";
    }

    cout << endl;

    SetScreenColor(Quizz.QuestionList[QuestionNumber].AnswerResult);
}

void AskAndCorrectQuestionListAnswer(stQuizz& Quizz)
{
    for (short QuestionNumber = 0;QuestionNumber < Quizz.NumberOfQuestions;QuestionNumber++)
    {
        PrintTheQuestion(Quizz, QuestionNumber);
        Quizz.QuestionList[QuestionNumber].PlayerAnswer = ReadQuestionAnswer();
        CorrectTheQuestionAnswer(Quizz, QuestionNumber);
    }

    Quizz.isPass = (Quizz.NumberOfCorrectAnswer >= Quizz.NumberOfWrongAnswer);

   
   /* if (Quizz.NumberOfCorrectAnswer > Quizz.NumberOfWrongAnswer)
        Quizz.isPass = true;
    else
        Quizz.isPass = false;
    */
}

string GetFinalResultsText(bool Pass)
{
    if (Pass)
        return " PASS :-)";
    else
        return " Fail :-(";
}

void PrintQuizzResults(stQuizz Quizz)
{
    cout << "\n";
    cout << "_____________________________________\n\n";

    cout << " Final Results is " << GetFinalResultsText(Quizz.isPass);
    cout << "\n______________________________________\n\n";
    cout << " Number of Questions : " << Quizz.NumberOfQuestions << endl;
    cout << " Question Level  : " << GetQuestionLevelText(Quizz.QuestionLevel) << endl;
    cout << " Op Type  : " << GetOpTypeSymbol(Quizz.OpType) << endl;
    cout << " Number of Right Answers : " << Quizz.NumberOfCorrectAnswer << endl;
    cout << " Number of Wrong Answers : " << Quizz.NumberOfWrongAnswer << endl;
    cout << "_______________________________________________\n";

}

void PlayMathGame()
{
    stQuizz Quizz;

    Quizz.NumberOfQuestions = ReadHowManyQuestions();
    Quizz.QuestionLevel = ReadQuestionLevel();
    Quizz.OpType = ReadOpType();

    GenerateQuizzQuestions(Quizz);
    AskAndCorrectQuestionListAnswer(Quizz);
    PrintQuizzResults(Quizz);

}

void ResetScreen()
{
    system("cls");
    system("color 0F");
}

void StartGame()
{
    char PlayAgain = 'Y';
    do
    {
        ResetScreen();
        PlayMathGame();
        cout << endl << " Do you want to play again? Y/N?";
        cin >> PlayAgain;
    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
    srand((unsigned)time(NULL));
    
    StartGame();
    
    return 0;


    
}

