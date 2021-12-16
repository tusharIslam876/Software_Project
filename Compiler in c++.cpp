#include<cstdio>
#include <iostream>

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
using namespace std;
bool isValidDelimiter(char ch)
{
    if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' ||
            ch == '/' || ch == ',' || ch == ';' || ch == '>' ||
            ch == '<' || ch == '=' || ch == '(' || ch == ')' ||
            ch == '[' || ch == ']' || ch == '{' || ch == '}')
        return (true);
    return (false);
}
bool isValidOperator(char ch)
{
    if (ch == '+' || ch == '-' || ch == '*' ||
            ch == '/' || ch == '>' || ch == '<' ||
            ch == '=')
        return (true);
    return (false);
}
// Returns 'true' if the string is a VALID IDENTIFIER.
bool isvalidIdentifier(char* str)
{
    if (str[0] == '0' || str[0] == '1' || str[0] == '2' ||
            str[0] == '3' || str[0] == '4' || str[0] == '5' ||
            str[0] == '6' || str[0] == '7' || str[0] == '8' ||
            str[0] == '9' || (str[0]>=33 && str[0]<=35) ||
            (str[0]>=37 && str[0]<=47) || (str[0]>=91 && str[0]<=96)
            || (str[0]>=123 && str[0]<=127) || isValidDelimiter(str[0]) == true)
        return (false);
    return (true);
}
bool isValidKeyword(char* str)
{
    if (!strcmp(str, "if") || !strcmp(str, "else") || !strcmp(str, "while") || !strcmp(str, "do") ||    !strcmp(str, "break") || !strcmp(str, "continue") || !strcmp(str, "int")
            || !strcmp(str, "double") || !strcmp(str, "float") || !strcmp(str, "return") || !strcmp(str,    "char") || !strcmp(str, "case") || !strcmp(str, "char")
            || !strcmp(str, "sizeof") || !strcmp(str, "long") || !strcmp(str, "short") || !strcmp(str, "typedef") || !strcmp(str, "switch") || !strcmp(str, "unsigned")
            || !strcmp(str, "void") || !strcmp(str, "static") || !strcmp(str, "struct") || !strcmp(str, "goto") || !strcmp(str, "main"))
        return (true);
    return (false);
}
bool isValidInteger(char* str)
{
    int i, len = strlen(str);
    if (len == 0)
        return (false);
    for (i = 0; i < len; i++)
    {
        if (str[i] != '0' && str[i] != '1' && str[i] != '2'&& str[i] != '3' && str[i] != '4' && str[i] != '5'
                && str[i] != '6' && str[i] != '7' && str[i] != '8' && str[i] != '9' || (str[i] == '-' && i > 0))
            return (false);
    }
    return (true);
}
bool isRealNumber(char* str)
{
    int i, len = strlen(str);
    bool hasDecimal = false;
    if (len == 0)
        return (false);
    for (i = 0; i < len; i++)
    {
        if (str[i] != '0' && str[i] != '1' && str[i] != '2' && str[i] != '3' && str[i] != '4' && str[i]       != '5' && str[i] != '6' && str[i] != '7' && str[i] != '8'
                && str[i] != '9' && str[i] != '.' || (str[i] == '-' && i > 0))
            return (false);
        if (str[i] == '.')
            hasDecimal = true;
    }
    return (hasDecimal);
}
char* subString(char* str, int left, int right)
{
    int i;
    char* subStr = (char*)malloc( sizeof(char) * (right - left + 2));
    for (i = left; i <= right; i++)
        subStr[i - left] = str[i];
    subStr[right - left + 1] = '\0';
    return (subStr);
}

string removeComments(string prgm)
{
    int n = prgm.length();
    string res;
    bool s_cmt = false;
    bool m_cmt = false;
    for (int i=0; i<n; i++)
    {

        if (s_cmt == true && prgm[i] == '\n')
            s_cmt = false;
        else if  (m_cmt == true && prgm[i] == '*' && prgm[i+1] == '/')
            m_cmt = false,  i++;
        else if (s_cmt || m_cmt)
            continue;
        else if (prgm[i] == '/' && prgm[i+1] == '/')
            s_cmt = true, i++;
        else if (prgm[i] == '/' && prgm[i+1] == '*')
        {
            for(int j=i+2;j<n;j++)
            {
                if(prgm[j] == '*' && prgm[j+1] == '/')
                {
                    m_cmt = true,  i++;
                }
            }
            if(m_cmt==false)
            {
                res += prgm[i];
            }
        }
        else  res += prgm[i];
    }
    return res;
}

void detectTokens(char* str)
{
    int left = 0, right = 0,j,i;
    char ch;
    int length = strlen(str);
    while (right <= length && left <= right)
    {
        if (isValidDelimiter(str[right]) == false)
            right++;
        if (isValidDelimiter(str[right]) == true && left == right)
        {
            if (isValidOperator(str[right]) == true)
                printf("Valid operator : '%c'\n", str[right]);
            right++;
            left = right;
        }
        else if (isValidDelimiter(str[right]) == true && left != right || (right == length && left !=       right))
        {
            char* subStr = subString(str, left, right - 1);
            if (isValidKeyword(subStr) == true)
                printf("Valid keyword : '%s'\n", subStr);
            else if (isValidInteger(subStr) == true)
                printf("Valid Integer : '%s'\n", subStr);
            else if (isRealNumber(subStr) == true)
                printf("Real Number : '%s'\n", subStr);
            else if (isvalidIdentifier(subStr) == true
                     && isValidDelimiter(str[right - 1]) == false)
                printf("Valid Identifier : '%s'\n", subStr);
            else if (isvalidIdentifier(subStr) == false
                     && isValidDelimiter(str[right - 1]) == false)
            {
                printf("Invalid Identifier : '%s'", subStr);
                char sub1[100];
                strcpy(sub1,subStr);
                for(i=0; subStr[i]!='\0'; i++)
                {
                    if((str[0]>=33 && str[0]<=35) ||
                            (str[0]>=37 && str[0]<=47) || (str[0]>=91 && str[0]<=96)
                            || (str[0]>=123 && str[0]<=127))
                    {
                        for(j=0; subStr[j]!='\0'; j++)
                        {
                            if(subStr[j+1]=='\0')
                            {
                                break;
                            }
                            subStr[j]=subStr[j+1];
                        }
                        subStr[j]='\0';
                    }
                    if(subStr[0]>=48 && subStr[0]<=57)
                {
                    ch=subStr[0];
                        for(j=0; subStr[j]!='\0'; j++)
                        {
                            if(subStr[j+1]=='\0')
                            {
                                break;
                            }
                            subStr[j]=subStr[j+1];
                        }
                        subStr[j]=ch;
                        subStr[j+1]='\0';
                    }
                    if((subStr[i]>=65 && subStr[i]<=90) || (subStr[i]>=97 && subStr[i]<=122) || subStr[i]==36)
                {
                    break;
                }

            }
            printf("\t(Suggested Identifier: %s, _%s)\n",subStr,sub1);
            }
            left = right;
        }
    }
    return;
}
int main()
{
    string prgm;
    string new_prgm;
    char str[1000];
    getline(std::cin,prgm,'^');
    cout << "\n\nModified Program \n";
    new_prgm = removeComments(prgm);
    cout << new_prgm;
    Israfil Hasan, [12/16/2021 11:39 PM]
for(int i=0;new_prgm[i]!='\0';i++)
    {
        if(new_prgm[i]=='\n')
        {
            str[i]=' ';
            continue;
        }
        str[i]=new_prgm[i];
    }

Israfil Hasan, [12/16/2021 11:39 PM]
printf("\n\nAll Tokens are : \n");
    detectTokens(str);


    return 0;
}
