#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

enum enQuestionLevel { Easy = 1, Med = 2, Hard = 3, Mix = 4 };
enum enOperationType { Add = 1, Sub = 2, Mul = 3, Div = 4, MixOp = 5 };

int RandomNumber(int From, int To)
{
    int RandNum = rand() % (To - From + 1) + From;

    return RandNum;
}

short ReadHowManyQuestions()
{
    short NumberOfQuestions = 0;

    do
    {
        cout << "How Many Questions do you want in quiz ? ";
        cin >> NumberOfQuestions;

    } while (NumberOfQuestions < 1 || NumberOfQuestions>10);

    return NumberOfQuestions;
}

enQuestionLevel ReadQuestionLevel()
{
    short QuestionLevel = 0;

    do
    {
        cout << "Enter Question Level [1]:Easy, [2]:Med, [3]:Hard, [4]:Mix ? ";
        cin >> QuestionLevel;

    } while (QuestionLevel < 1 || QuestionLevel>4);

    return (enQuestionLevel)QuestionLevel;
}

enOperationType ReadOperationType()
{
    short OperationType = 0;

    do
    {
        cout << "Enter Operation Type [1]:Add, [2]:Sub, [3]:Mul, [4]:Div, [5]:Mix ? ";
        cin >> OperationType;

    } while (OperationType < 1 || OperationType>5);

    return (enOperationType)OperationType;
}

struct stQuestion
{
    int Number1 = 0;
    int Number2 = 0;
    enOperationType OperationType;
    enQuestionLevel QuestionLevel;
    int CorrectAnswer = 0;
    int PlayerAnswer = 0;
    bool AnswerResult = false;
};

struct stQuiz
{
    stQuestion QuestionList[100];
    short NumberOfQuestion;
    enQuestionLevel QuestionLevel;
    enOperationType OperationType;
    short NumberOfWrongAnswer = 0;
    short NumberOfRightAnswer = 0;
    bool IsPass = false;
};

int SimpleCalculator(int Number1, int Number2, enOperationType OperationType)
{
    switch (OperationType)
    {
    case enOperationType::Add:
        return Number1 + Number2;
    case enOperationType::Sub:
        return Number1 - Number2;
    case enOperationType::Mul:
        return Number1 * Number2;
    case enOperationType::Div:
        return Number1 / Number2;
    default:
        return Number1 + Number2;
    }
}

stQuestion GenerateQuestion(enQuestionLevel QuestionLevel, enOperationType OperationTpe)
{
    stQuestion Question;

    if (QuestionLevel == enQuestionLevel::Mix)
        QuestionLevel = (enQuestionLevel)RandomNumber(1, 3);

    if (OperationTpe == enOperationType::MixOp)
        OperationTpe = (enOperationType)RandomNumber(1, 4);

    Question.OperationType = OperationTpe;

    switch (QuestionLevel)
    {
    case enQuestionLevel::Easy:
        Question.Number1 = RandomNumber(1, 10);
        Question.Number2 = RandomNumber(1, 10);
        break;
    case enQuestionLevel::Med:
        Question.Number1 = RandomNumber(10, 50);
        Question.Number2 = RandomNumber(10, 50);
        break;
    case enQuestionLevel::Hard:
        Question.Number2 = RandomNumber(50, 100);
        Question.Number2 = RandomNumber(50, 100);
        break;
    }

    Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, OperationTpe);
    Question.QuestionLevel = QuestionLevel;

    return Question;
}

void GenerateQuizQuestion(stQuiz& Quiz)
{
    for (short Question = 0;Question < Quiz.NumberOfQuestion;Question++)
    {
        Quiz.QuestionList[Question] = GenerateQuestion(Quiz.QuestionLevel, Quiz.OperationType);
    }
}

void PlayGame()
{
    stQuiz Quiz;

    Quiz.NumberOfQuestion = ReadHowManyQuestions();
    Quiz.QuestionLevel = ReadQuestionLevel();
    Quiz.OperationType = ReadOperationType();

    GenerateQuizQuestion(Quiz);
}

int main()
{
    srand((unsigned)time(NULL));
    PlayGame();

    return 0;

}