#pragma once
#include "pch.h"
#include <iostream>
#include <deque>
#include <regex>
#include <cmath>
#include <numeric>
#include <fstream>
using namespace std;

struct LastAns {
    bool exists;
    double lastans;
};

class MathInterpter {
public: 

      deque<int> PowerIndecies;
      deque<int> MultiplayIndecies;
      deque<int> DivisionIndecies;
      deque<int> AdditionIndecies;
      deque<int> SubstractIndecies;
      string myMathStr = "";
      LastAns last_ans_ = { false,0 };

      enum Opert { power, multiplication, division, addition, substraction };
    
    

      void FetchString(char asckey) {
          myMathStr += asckey;
      }

      void InterptmyMath()
      {
          PowerIndecies.clear();
          MultiplayIndecies.clear();
          DivisionIndecies.clear();
          AdditionIndecies.clear();
          SubstractIndecies.clear();

          /*int tempPowerIndex=0;
         int tempMUltiIndex=0;
         int tempDivideIndex=0;
         int tempADDIndex=0;
         int tempMinutsIndex=0;


         /*do{


             if(tempPowerIndex!=0 && string::npos != tempPowerIndex){
                 PowerIndecies.push_back(tempPowerIndex);
             }


             if(tempMUltiIndex!=0 && string::npos != tempMUltiIndex){

                 MultiplayIndecies.push_back(tempMUltiIndex);
             }

             if(tempDivideIndex!=0 && string::npos != tempDivideIndex){

                 DivisionIndecies.push_back(tempDivideIndex);


             }
             if(tempADDIndex!=0 && string::npos != tempADDIndex){

                 AdditionIndecies.push_back(tempADDIndex);


             }
             if(tempMinutsIndex!=0 && string::npos != tempMinutsIndex){

                 SubstractIndecies.push_back(tempMinutsIndex);


             }



             tempPowerIndex = myMathStr.find('^',tempPowerIndex+1);
             tempMUltiIndex = myMathStr.find('*',tempMUltiIndex+1);
             tempDivideIndex = myMathStr.find('/',tempDivideIndex+1);
             tempADDIndex = myMathStr.find('+',tempADDIndex+1);
             tempMinutsIndex = myMathStr.find('-',tempMinutsIndex+1);





         } while (string::npos != tempPowerIndex || string::npos != tempMUltiIndex || string::npos != tempDivideIndex ||
                 string::npos != tempADDIndex || string::npos != tempMinutsIndex );*/



          int captureOperators = 0;
          for (int i = 0; i < myMathStr.length(); i++) {
              if (myMathStr[i] == '(') {
                  captureOperators++;
              }
              if (captureOperators != 0) {

                  if (myMathStr[i] == ')')
                      captureOperators--;
                  continue;
              }
              else if (i != 0) {

                  if (myMathStr[i] == '^') {
                      PowerIndecies.push_back(i);
                  }
                  else if (myMathStr[i] == '*') {
                      MultiplayIndecies.push_back(i);
                  }
                  else if (myMathStr[i] == '/') {
                      DivisionIndecies.push_back(i);
                  }
                  else if (myMathStr[i] == '+') {
                      AdditionIndecies.push_back(i);
                  }
                  else if (myMathStr[i] == '-') {
                      SubstractIndecies.push_back(i);
                  }
              }


          }




      }

      bool FetchOperatorSides(int mainIndex, int typeOfOperation) {
          if (myMathStr[0] == '+' || myMathStr[0] == '-' || myMathStr[0] == '*' || myMathStr[0] == '/' || myMathStr[0] == '^'
              || myMathStr[myMathStr.length() - 1] == '+' || myMathStr[myMathStr.length() - 1] == '-' ||
              myMathStr[myMathStr.length() - 1] == '*' || myMathStr[myMathStr.length() - 1] == '/' || myMathStr[myMathStr.length() - 1] == '^') {
              \
                  //Enter name Function
                  return false;

          }


          string LHS, RHS;
          /*int arr[5];
                  arr[0]= myMathStr.find('^',mainIndex+1);
                  arr[1] = myMathStr.find('*',mainIndex+1);
                  arr[2]  = myMathStr.find('/',mainIndex+1);
                  arr[3]  = myMathStr.find('+',mainIndex+1);
                  arr[4] = myMathStr.find('-',mainIndex+1);

                      int minIndex=1000000;
                      for(int i=1; i<5; i++){
                          if(arr[i] !=string ::npos&& arr[i]< minIndex)
                              minIndex = arr[i];

                      }*/
          int minIndex = 1000000;
          for (int i = 0; i < PowerIndecies.size(); i++) {
              if (PowerIndecies[i] > mainIndex && PowerIndecies[i] < minIndex) {
                  minIndex = PowerIndecies[i];
              }
          }
          for (int i = 0; i < MultiplayIndecies.size(); i++) {
              if (MultiplayIndecies[i] > mainIndex && MultiplayIndecies[i] < minIndex) {
                  minIndex = MultiplayIndecies[i];
              }
          }
          for (int i = 0; i < DivisionIndecies.size(); i++) {
              if (DivisionIndecies[i] > mainIndex && DivisionIndecies[i] < minIndex) {
                  minIndex = DivisionIndecies[i];
              }
          }
          for (int i = 0; i < AdditionIndecies.size(); i++) {
              if (AdditionIndecies[i] > mainIndex && AdditionIndecies[i] < minIndex) {
                  minIndex = AdditionIndecies[i];
              }
          }
          for (int i = 0; i < SubstractIndecies.size(); i++) {
              if (SubstractIndecies[i] > mainIndex && SubstractIndecies[i] < minIndex) {
                  minIndex = SubstractIndecies[i];
              }
          }

          if (minIndex == 1000000) {
              RHS = myMathStr.substr(mainIndex + 1, myMathStr.length() - (mainIndex + 1));

          }
          else {

              RHS = myMathStr.substr(mainIndex + 1, minIndex - mainIndex - 1);

          }

          //LHS reversed the array and did the same operations to reduce effort in catching the LHS equation
          string reverseStr = myMathStr;

          for (int i = 0; i < reverseStr.length() / 2; i++) {
              swap(reverseStr[i], reverseStr[reverseStr.length() - i - 1]);
          }

          int newMainIndex = reverseStr.length() - mainIndex - 1;
          /*int arr[5];
      arr[0]= reverseStr.find('^',newMainIndex+1);
      arr[1] = reverseStr.find('*',newMainIndex+1);
      arr[2]  = reverseStr.find('/',newMainIndex+1);
      arr[3]  = reverseStr.find('+',newMainIndex+1);
      arr[4] = reverseStr.find('-',newMainIndex+1);


      int minIndexLHS=1000000;
      for(int i=1; i<5; i++) {
          if (arr[i] != string::npos && arr[i] < minIndexLHS) {
              minIndexLHS = arr[i];
          }



      }*/
          int minIndexLHS = 1000000;
          for (int i = 0; i < PowerIndecies.size(); i++) {
              if (reverseStr.length() - PowerIndecies[i] - 1 > newMainIndex && reverseStr.length() - PowerIndecies[i] - 1 < minIndexLHS) {
                  minIndexLHS = reverseStr.length() - PowerIndecies[i] - 1;
              }
          }
          for (int i = 0; i < MultiplayIndecies.size(); i++) {
              if (reverseStr.length() - MultiplayIndecies[i] - 1 > newMainIndex && reverseStr.length() - MultiplayIndecies[i] - 1 < minIndexLHS) {
                  minIndexLHS = reverseStr.length() - MultiplayIndecies[i] - 1;
              }
          }
          for (int i = 0; i < DivisionIndecies.size(); i++) {
              if (reverseStr.length() - DivisionIndecies[i] - 1 > newMainIndex && reverseStr.length() - DivisionIndecies[i] - 1 < minIndexLHS) {
                  minIndexLHS = reverseStr.length() - DivisionIndecies[i] - 1;
              }
          }
          for (int i = 0; i < AdditionIndecies.size(); i++) {
              if (reverseStr.length() - AdditionIndecies[i] - 1 > newMainIndex && reverseStr.length() - AdditionIndecies[i] - 1 < minIndexLHS) {
                  minIndexLHS = reverseStr.length() - AdditionIndecies[i] - 1;
              }
          }
          for (int i = 0; i < SubstractIndecies.size(); i++) {
              if (reverseStr.length() - SubstractIndecies[i] - 1 > newMainIndex && reverseStr.length() - SubstractIndecies[i] - 1 < minIndexLHS) {
                  minIndexLHS = reverseStr.length() - SubstractIndecies[i] - 1;
              }
          }


          if (minIndexLHS == 1000000) {

              LHS = reverseStr.substr(newMainIndex + 1, reverseStr.length() - (newMainIndex + 1));
          }
          else {

              LHS = reverseStr.substr(newMainIndex + 1, minIndexLHS - newMainIndex - 1);

          }

          for (int i = 0; i < LHS.length() / 2; i++) {
              swap(LHS[i], LHS[LHS.length() - i - 1]);
          }

          int leftPos = (minIndexLHS == 1000000) ? minIndexLHS : reverseStr.length() - minIndexLHS - 1;

          return CalcPortion(LHS, RHS, leftPos, minIndex, typeOfOperation);



      }

      bool CalcPortion(string LHS, string RHS, int leftPos, int rightPos, int typeOfOperation) {
          bool acceptedfourmela = true;
          double myLHS, myRHS;

          bool LHSValid = checkEquationRegex(LHS, myLHS);
          bool RHSValid = checkEquationRegex(RHS, myRHS);


          if (!LHSValid || !RHSValid) {

              return false;
          }
          string insertInString;
          switch (typeOfOperation) {
          case Opert::power: {
              long double output = pow(myLHS, myRHS);

              insertInString = to_string(output);
          }
                           break;
          case Opert::multiplication: {
              long double output = myLHS * myRHS;
              insertInString = to_string(output);

          }
                                    break;
          case Opert::division: {
              long double output = myLHS / myRHS;
              insertInString = to_string(output);

          }
                              break;
          case Opert::addition: {
              long double output = myLHS + myRHS;
              insertInString = to_string(output);

          }
                              break;
          case Opert::substraction: {
              long double output = myLHS - myRHS;
              insertInString = to_string(output);

          }
                                  break;

                              defualt: return false;

          }

          string oldStr = myMathStr;

          if (leftPos == 1000000 && rightPos == 1000000) {

              myMathStr = insertInString;

          }
          else if (leftPos == 1000000 && rightPos != 1000000) {
              string tempStr = insertInString;
              for (int i = rightPos; i < myMathStr.length(); i++) {
                  tempStr += myMathStr[i];
              }

              myMathStr = tempStr;


          }

          else if (rightPos == 1000000 && leftPos != 1000000) {

              myMathStr = myMathStr.substr(0, leftPos + 1) + insertInString;



          }

          else {
              string firstportion = myMathStr.substr(0, leftPos + 1);
              string secondportion = myMathStr.substr(rightPos, myMathStr.length() - rightPos);
              myMathStr = firstportion + insertInString + secondportion;

          };
          InterptmyMath();
          return true;
      }

      bool checkEquationRegex(string portion, double& output) {
          //unfortunately switch statemtns are only available for integers and chars, so yeah get ready for the ultimate:
          // if else if else if else if else if else......

          regex numOnlyRegex("(?:\\d+\\.?\\d*|\\.\\d+)");
          regex sinRegex("sin\\(.*\\)");
          regex cosRegex("cos\\(.*\\)");
          regex tanRegex("tan\\(.*\\)");
          regex factorRegex("\\d+!");
          regex logRegex("log\\[\\d+(\\.\\d+)?\\]\\(\\d+(\\.\\d+)?\\)");

          if (regex_match(portion, numOnlyRegex)) {
              output = stod(portion);
              return true;
          }

          if (regex_match(portion, sinRegex)) {
              regex sinNum("sin\\(\\s*(?:\\d+(?:\\.\\d+)?\\s*(?:/\\s*\\d+(?:\\.\\d+)?)?|\\d*(?:\\.\\d+)?\\s*/\\s*\\d+(?:\\.\\d+)?)\\s*\\)");
              if (regex_match(portion, sinNum)) {
                  output = stod(portion.substr(4, portion.length() - 5));
                  output = sin(output);
                  return true;
              }

              string holdRealStr = myMathStr;
              myMathStr = portion.substr(4, portion.length() - 5);

              double results;
              if (MainOperation(results)) {

                  output = sin(results);
                  myMathStr = holdRealStr;
                  return true;
              }

              return false;





          }

          if (regex_match(portion, cosRegex)) {
              regex cosNum("cos\\(\\s*(?:\\d+(?:\\.\\d+)?\\s*(?:/\\s*\\d+(?:\\.\\d+)?)?|\\d*(?:\\.\\d+)?\\s*/\\s*\\d+(?:\\.\\d+)?)\\s*\\)");
              if (regex_match(portion, cosNum)) {
                  output = stod(portion.substr(4, portion.length() - 5));
                  output = cos(output);
                  return true;
              }

              string holdRealStr = myMathStr;
              myMathStr = portion.substr(4, portion.length() - 5);

              double results;
              if (MainOperation(results)) {

                  output = cos(results);
                  myMathStr = holdRealStr;
                  return true;
              }




              return false;



          }

          if (regex_match(portion, tanRegex)) {
              regex tanNum("tan\\(\\s*(?:\\d+(?:\\.\\d+)?\\s*(?:/\\s*\\d+(?:\\.\\d+)?)?|\\d*(?:\\.\\d+)?\\s*/\\s*\\d+(?:\\.\\d+)?)\\s*\\)");
              if (regex_match(portion, tanNum)) {
                  output = stod(portion.substr(4, portion.length() - 5));
                  output = tan(output);
                  return true;
              }

              string holdRealStr = myMathStr;
              myMathStr = portion.substr(4, portion.length() - 5);

              double results;
              if (MainOperation(results)) {

                  output = tan(results);
                  myMathStr = holdRealStr;
                  return true;
              }

              return false;



          }

          if (regex_match(portion, factorRegex)) {
              output = stod(portion.substr(0, portion.length() - 1));

              output = tgamma(output + 1);
              return true;

          }

          if (regex_match(portion, logRegex)) {
              string baseStr, numberStr;
              int posOfBracket = portion.find(']', 3);
              baseStr = portion.substr(4, posOfBracket - 4);
              numberStr = portion.substr(posOfBracket + 2, portion.length() - posOfBracket - 3);
              double base = stod(baseStr), number = stod(numberStr);

              output = log(number) / log(base);
              return true;

          }

          if (portion[0] == '(' && portion[portion.length() - 1] == ')') {

              string holdRealStr = myMathStr;
              myMathStr = portion.substr(1, portion.length() - 2);

              double results;
              if (MainOperation(results)) {

                  output = results;
                  myMathStr = holdRealStr;
                  return true;
              }

              return false;



          }

          if (last_ans_.exists && portion == "ans") {
              output = last_ans_.lastans;
              return true;
          }



          return false;


      }

      double MainOperation(double& output) {

          transform(myMathStr.begin(), myMathStr.end(), myMathStr.begin(), ::tolower);
          InterptmyMath();
          unsigned int powerNum = PowerIndecies.size();
          unsigned int multNum = MultiplayIndecies.size();
          unsigned int divNum = DivisionIndecies.size();
          unsigned int addNum = AdditionIndecies.size();
          unsigned int subNum = SubstractIndecies.size();

          bool isCorrect;
          for (int i = 0; i < powerNum; i++) {
              isCorrect = FetchOperatorSides(PowerIndecies[PowerIndecies.size() - 1], Opert::power);
              if (!isCorrect)
                  return false;


          }
          for (int i = 0; i < multNum + divNum; i++) {
              if (MultiplayIndecies.size() > 0 && DivisionIndecies.size() == 0 || MultiplayIndecies.size() > 0
                  && MultiplayIndecies[0] < DivisionIndecies[0]) {
                  isCorrect = FetchOperatorSides(MultiplayIndecies[0], Opert::multiplication);
                  if (!isCorrect)
                      return false;
              }
              else {

                  isCorrect = FetchOperatorSides(DivisionIndecies[0], Opert::division);
                  if (!isCorrect)
                      return false;
              }
          }
          for (int i = 0; i < addNum + subNum; i++) {
              if (AdditionIndecies.size() > 0 && SubstractIndecies.size() == 0 || AdditionIndecies.size() > 0
                  && AdditionIndecies[0] < SubstractIndecies[0]) {
                  isCorrect = FetchOperatorSides(AdditionIndecies[0], Opert::addition);
                  if (!isCorrect)
                      return false;
              }
              else {

                  isCorrect = FetchOperatorSides(SubstractIndecies[0], Opert::substraction);
                  if (!isCorrect)
                      return false;

              }
          }


          try {
              regex factorRegex("\\d+!");
              if (regex_match(myMathStr, factorRegex)) {

                  throw "test";
              }

              output = stod(myMathStr);
              last_ans_.exists = true;
              last_ans_.lastans = output;
              return true;
          }

          catch (...) {
              double myOutput;
              bool its1argument = checkEquationRegex(myMathStr, myOutput);

              if (its1argument) {
                  output = myOutput;
                  return true;
              }

              return false;
          }

      }


      double MainOperation() {
          double output;
          transform(myMathStr.begin(), myMathStr.end(), myMathStr.begin(), ::tolower);
          InterptmyMath();
          unsigned int powerNum = PowerIndecies.size();
          unsigned int multNum = MultiplayIndecies.size();
          unsigned int divNum = DivisionIndecies.size();
          unsigned int addNum = AdditionIndecies.size();
          unsigned int subNum = SubstractIndecies.size();

          bool isCorrect;
          for (int i = 0; i < powerNum; i++) {
              isCorrect = FetchOperatorSides(PowerIndecies[PowerIndecies.size() - 1], Opert::power);
              if (!isCorrect)
                  return false;


          }
          for (int i = 0; i < multNum + divNum; i++) {
              if (MultiplayIndecies.size() > 0 && DivisionIndecies.size() == 0 || MultiplayIndecies.size() > 0
                  && MultiplayIndecies[0] < DivisionIndecies[0]) {
                  isCorrect = FetchOperatorSides(MultiplayIndecies[0], Opert::multiplication);
                  if (!isCorrect)
                      return false;
              }
              else {

                  isCorrect = FetchOperatorSides(DivisionIndecies[0], Opert::division);
                  if (!isCorrect)
                      return false;
              }
          }
          for (int i = 0; i < addNum + subNum; i++) {
              if (AdditionIndecies.size() > 0 && SubstractIndecies.size() == 0 || AdditionIndecies.size() > 0
                  && AdditionIndecies[0] < SubstractIndecies[0]) {
                  isCorrect = FetchOperatorSides(AdditionIndecies[0], Opert::addition);
                  if (!isCorrect)
                      return false;
              }
              else {

                  isCorrect = FetchOperatorSides(SubstractIndecies[0], Opert::substraction);
                  if (!isCorrect)
                      return false;

              }
          }


          try {
              regex factorRegex("\\d+!");
              if (regex_match(myMathStr, factorRegex)) {

                  throw "test";
              }

              output = stod(myMathStr);
              last_ans_.exists = true;
              last_ans_.lastans = output;
              return output;
          }

          catch (...) {
              double myOutput;
              bool its1argument = checkEquationRegex(myMathStr, myOutput);

              if (its1argument) {
                  output = myOutput;
                  return output;
              }

              return output;
          }

      }



     
};

extern "C" __declspec(dllexport) void* Create(int y) {
    MathInterpter* x = new MathInterpter();
    return (void*)x;
}
extern "C" __declspec(dllexport) void AddString(MathInterpter * ptr, char y) {
    ptr->FetchString(y);

}



extern "C" __declspec(dllexport) double returndouble(MathInterpter * ptr) {
 
    return  ptr->MainOperation();

}

