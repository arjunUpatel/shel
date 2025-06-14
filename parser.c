#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "parser.h"

InputParse *parseInput(char *input)
{
  if (strlen(input) == 0)
    return NULL;
  bool allSpaces = true;
  unsigned long long len = 1;
  unsigned long long idx = 0;
  char **parsedInputTemp = malloc(len * sizeof(char *));
  unsigned long long inputLen = strlen(input);
  for (unsigned long long i = 0; i < inputLen; i++)
  {
    if (isspace(input[i]))
      continue;

    unsigned long long strLen = 1;
    unsigned long long strIdx = 0;
    char *strTemp = malloc(strLen * sizeof(char));
    unsigned long long j = i;

    while (j < inputLen && input[j] != ' ')
    {
      allSpaces = false;
      strTemp[strIdx] = input[j];
      strIdx++;
      if (strIdx == strLen)
      {
        strLen *= 2;
        strTemp = realloc(strTemp, strLen * sizeof(char));
      }
      j++;
    }
    strTemp[strIdx] = '\0';
    strIdx++;
    char *str = malloc(strIdx * sizeof(char));
    for (unsigned long long l = 0; l < strIdx; l++)
      str[l] = strTemp[l];
    free(strTemp);
    parsedInputTemp[idx] = str;
    idx++;
    if (idx == len)
    {
      len *= 2;
      parsedInputTemp = realloc(parsedInputTemp, len * sizeof(char *));
    }
    i = j;
  }
  if (allSpaces)
  {
    free(parsedInputTemp);
    return NULL;
  }
  bool ampersandPresent = false;
  if (parsedInputTemp[idx - 1][strlen(parsedInputTemp[idx - 1]) - 1] == '&')
    ampersandPresent = true;

  if (ampersandPresent && strlen(parsedInputTemp[idx - 1]) == 1)
  {
    free(parsedInputTemp[idx - 1]);
    parsedInputTemp[idx - 1] = NULL;
  }
  else
  {
    if (ampersandPresent)
    {
      unsigned long long newStrLen = strlen(parsedInputTemp[idx - 1]);
      char *newStr = malloc(newStrLen * sizeof(char));
      for (unsigned long long l = 0; l < newStrLen; l++)
        newStr[l] = parsedInputTemp[idx - 1][l];
      newStr[newStrLen - 1] = '\0';
      free(parsedInputTemp[idx - 1]);
      parsedInputTemp[idx - 1] = newStr;
    }
    parsedInputTemp[idx] = NULL;
    idx++;
  }
  char **parsedInput = malloc(idx * sizeof(char *));
  for (unsigned long long l = 0; l < idx; l++)
    parsedInput[l] = parsedInputTemp[l];
  free(parsedInputTemp);

  InputParse *inputParse = malloc(sizeof(InputParse));
  inputParse->parsedInput = parsedInput;
  inputParse->ampersandPresent = ampersandPresent;
  inputParse->parseLen = idx;
  return inputParse;
}

void freeInputParse(InputParse *inputParse)
{
  for (unsigned long long i = 0; inputParse->parsedInput[i] != NULL; i++)
    free(inputParse->parsedInput[i]);
  free(inputParse->parsedInput);
  free(inputParse);
}

void printParsedInput(InputParse *inputParse)
{
  for (unsigned long long i = 0; i < inputParse->parseLen; i++)
    printf("%lld: %s\n", i, inputParse->parsedInput[i]);
  printf("ampersandPresent: %s\n\n", inputParse->ampersandPresent ? "true" : "false");
}
