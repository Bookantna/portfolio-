#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int count_letters(string x);
int count_words(string x);
int count_sentences(string x);

float index = 0;
int countwords = 1;
int countsentences = 0;
int countletters = 0;

int main (void)
{
    string text = get_string("Text: ");
    
    int words = count_words(text);
    int sentences = count_sentences(text);
    int letters = count_letters(text);
    
    //printf("%i\n",words);
    //printf("%i\n",countsentences);
    //printf("%i\n",letters);
    
    index = round(0.0588 * (100 *(float) countletters / countwords) - 0.296 * (100 * (float)countsentences / countwords) - 15.8);
    if (index <= 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >=16)
    {
        printf("Grade 16+\n");
    }
    else 
    {
        printf("Grade %.0f\n",index);
    }
}
int count_words(string x)
{
    for(int i = 0; i < strlen(x);i++)
    {
        if (x[i] == ' ')
        {
            countwords++;
        }
    }
    return countwords;
}
int count_sentences(string x)
{
    for(int i = 0; i < strlen(x);i++)
    {
        if(x[i] == '!'||x[i] == '?'||x[i] == '.')
        {
            countsentences++;
        }
    }
    return countsentences;
}
int count_letters(string x)
{
    for(int i = 0; i < strlen(x);i++)
    {
        if((x[i] >= 'a' && x[i] <= 'z') || (x[i] >= 'A' && x[i] <= 'Z'))
        {
            countletters++;
        }
    }
    return countletters;
}
