// Purpose.  Strategy design pattern lab.
//
// Problem.  Data entry validation is lumped in one function with a large
// monolithic case statement.  In a more sophisticated application there
// might be multiple parallel case statements and the validation code
// could easily become several pages in length.  If new validation
// requirements surface, the situation is exacerbated.
//
// Strategy.  "Abtract out" the validation mechanism into its own class
// hierarchy - interface in a base class, implementation in derived classes.
//
// Assignment.
// o Create a Validation base class that can serve as an umbrella for the
//   three different validation requirements
// o Move the interface of the validate() method to the Validation hierarchy
// o Move each part of the "case" statement in validate() to its own derived
//   class
// o In DataEntry, replace the "type" attribute and the validate() method
//   with a Validation* attribute
// o Initialize the Validation* member, inside setValidationType()
// o In interact(), delegate the validation to the Validation* member
// o main() will stay the same

#include <iostream>
#include <cstring>
using namespace std;

int isdigit( char ch )
{
    return (ch >= '0' && ch <= '9') ? 1 : 0;
}
int isupper( char ch )
{
    return (ch >= 'A' && ch <= 'Z') ? 1 : 0;
}
int islower( char ch )
{
    return (ch >= 'a' && ch <= 'z') ? 1 : 0;
}

class Validataion
{
public:
    virtual int validate(char*)=0;
};

class NumValidation:public Validataion
{
public:
    int validate(char* input)
    {
        for (int i=0; i < strlen(input); i++)
            if ( ! isdigit( input[i] ) )
                return  0;
        return 1;
    }
};

class UpperValidation:public Validataion
{
public:
    int validate(char* input)
    {
        for (int i=0; i < strlen(input); i++)
            if ( ! isupper( input[i] ) )
                return  0;
        return 1;
    }
};

class LowerValidation:public Validataion
{
public:
    int validate(char* input)
    {
        for (int i=0; i < strlen(input); i++)
            if ( ! islower( input[i] ) )
                return  0;
        return 1;
    }
};






class DataEntry
{
public:
    void setValidationType( char ch )
    {
        if(ch=='n')
            pValidation=new NumValidation;
        else if(ch=='u')
            pValidation=new UpperValidation;
        else if(ch=='l')
            pValidation=new LowerValidation;
    }
    void interact();
private:
    Validataion* pValidation;
    int  validate( char* );
};

void DataEntry::interact()
{
    char  answer[20];
    cout << "Prompt: ";
    cin >> answer;
    while (strcmp( answer, "quit" ))
    {
        if (validate( answer )) cout << "*** good ***" << endl;
        else                    cout << "*** bad ***" << endl;
        cout << "Prompt: ";
        cin >> answer;
    }
}

int DataEntry::validate( char* input )
{
    return pValidation->validate(input);
}

int main()
{
    DataEntry  dialog;
    char       answer;

    cout << "Input type [ (n)umber, (u)pper, (l)ower, e(x)it ]: ";
    cin >> answer;
    while (answer != 'x')
    {
        dialog.setValidationType(answer);
        dialog.interact();
        cout << "Input type [ (n)umber, (u)pper, (l)ower, e(x)it ]: ";
        cin >> answer;
    }
    return 1;
}

// Input type [ (n)umber, (u)pper, (l)ower, e(x)it ]: n
// Prompt: sdf
// *** bad ***
// Prompt: 234
// *** good ***
// Prompt: quit
// Input type [ (n)umber, (u)pper, (l)ower, e(x)it ]: u
// Prompt: sdf
// *** bad ***
// Prompt: 234
// *** bad ***
// Prompt: GHJ
// *** good ***
// Prompt: quit
// Input type [ (n)umber, (u)pper, (l)ower, e(x)it ]: x
