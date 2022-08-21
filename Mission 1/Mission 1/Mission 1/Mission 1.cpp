#include <iostream>
#include <string>
#include <cctype>

using namespace std;

//Function convert all symbols from string in lowercase letter   
string ConvertCapitalInLowercaseLetter(string &ConvertString)
{
    for (int i = 0; i < ConvertString.size(); ++i)
    {
        ConvertString.at(i) = tolower(ConvertString.at(i));
    }

    return ConvertString;
}

//Function creating and counting string with symbols ')' and '('
string CreateNewString(const string &CurrentString, string &NewString)
{
    for (int i = 0; i < CurrentString.size(); ++i)
    {
        int count_symbol = 0;

        for (int j = 0; j < CurrentString.size(); ++j)
        {
            if (CurrentString.at(i) == CurrentString.at(j))
            {
                count_symbol++;
            }
        }

        count_symbol <= 1 ? NewString.push_back('(') : NewString.push_back(')');
    }

    return NewString;
}

int main()
{
    string InitialString;
    string NewString;

    cout << "Enter any text: ";
    getline(cin, InitialString);

    ConvertCapitalInLowercaseLetter(InitialString);
    CreateNewString(InitialString, NewString);

    cout << "Result: ";
    cout << NewString;

    return 0;
}