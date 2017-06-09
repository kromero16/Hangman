/* 
 * File:   main.cpp
 * Author: Kevin Romero
 * Purpose: Hangman Game in C++
 * Created on April 27, 2017, 2:47 PM
 */

//System Libraries
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
using namespace std;

//User Libraries
#include "LinkedList.h"

//Function Prototypes
void pushWords(fstream &,vector<string>&);
void testGuess(string &,char &,LinkedList<char>&,int&,string&,LinkedList<char>&,int&);
string getWord(vector<string>&);
string hideString(string&);

//Begin Execution
int main(int argc, char** argv) {
    
    //set random number seed
    srand(static_cast<unsigned int>(time(0)));
    
    //Declare variables 
    char usrGuess;              //holds user guess
    int crGuess=0;              //counts correct guess
    int bdGuess=0;              //counts bad guess
    string rndWord;             //hold random word 
    string hiddenW;             //hold hidden string in _
    vector<string> wrdVec;      //Holds possible words
    fstream wrdFile;  
    LinkedList<char> list;      //hold current guess
    LinkedList<char> wrongG;    //holds incorrect words
    LinkedList<char> correctG;  //holds correct words
    
    //push file content to vector
    pushWords(wrdFile,wrdVec);
    
    //Set random word to be used
    rndWord=getWord(wrdVec);
    
    //Store word in hidden form
    hiddenW=hideString(rndWord);
    

    
    //Prompt User
    cout<<"***********Welcome To HangMan!***********\n\n";
    cout<<hiddenW<<"\n";
    
    do{
     
    //Prompt user for guess    
    cout<<"Enter Your Guess: \n";
    cin>>usrGuess;
    
    //output guess and current letters guessed
    cout<<"\n\n You Entered: "<<usrGuess<<"\n";
    list.push_back(usrGuess);
    cout<<"Current Guesses: ";
    list.printList();
    
    //test user guess
    testGuess(rndWord,usrGuess,correctG,crGuess,hiddenW,wrongG,bdGuess);

    //test winning case
    if(crGuess==rndWord.length()){
        cout<<"You Won! Congratulations!\n";
        cout<<"The Word Was: "<<rndWord<<"\n";;
       
      break;
    }
    
   //Different hangman figure states
    if(bdGuess==1){
        cout<<endl<<endl
           <<"   +----+  "<<endl
           <<"   |    |  "<<endl
           <<"   |       "<<endl
           <<"   |       "<<endl
           <<"   |       "<<endl
           <<"   |       "<<endl
          <<" Looks like the Guillotine "
         <<"Is being set up! "<<endl
           <<"  ============="<<endl<<endl;
    }

    if(bdGuess==2){
        cout<<endl<<endl
           <<"   +----+  "<<endl
           <<"   |    |  "<<endl
           <<"   |    O  "<<endl
           <<"   |    |  "<<endl
           <<"   |       "<<endl
           <<"   |       "<<endl
          <<" The figure's head is on the guillotine! "<<endl
           <<"  ============="<<endl<<endl;
    }

    if(bdGuess==3){
        cout<<endl<<endl
           <<"   +----+  "<<endl
           <<"   |    |  "<<endl
           <<"   |    O  "<<endl
           <<"   |   /|  "<<endl
           <<"   |       "<<endl
           <<"   |       "<<endl
          <<" You have 3 more tries! "<<endl
           <<"  ============="<<endl<<endl;
    }

    if(bdGuess==4){
        cout<<endl<<endl
         <<"   +----+  "<<endl
         <<"   |    |  "<<endl
         <<"   |    O  "<<endl
         <<"   |   /|\\ "<<endl
         <<"   |       "<<endl
         <<"   |       "<<endl
        <<" 2 More Chances! "<<endl
         <<"  ============="<<endl<<endl;
    }

    if(bdGuess==5){
        cout<<endl<<endl
           <<"   +----+  "<<endl
           <<"   |    |  "<<endl
           <<"   |    O  "<<endl
           <<"   |   /|\\ "<<endl
           <<"   |     \\ "<<endl
           <<"   |       "<<endl
           <<"   Be Careful he is near death "<<endl
           <<"  ============"<<endl<<endl;
    }

    if(bdGuess==6){
        cout<<endl<<endl
          <<"   +----+     "<<endl
          <<"   |    |     "<<endl
          <<"   |    O     "<<endl
          <<"   |   /|\\   "<<endl
          <<"   |   / \\   "<<endl
          <<"   |You Died "<<endl
         <<" Better Luck Next Time! "<<endl
          <<"  ============"<<endl<<endl;
    }
    
    }while(bdGuess<6);
        
    

    //Exit Program
    return 0;
}

//test user's guess
void testGuess(string &rw,char &ug,LinkedList<char> &cg,
        int &crg,string &hw,LinkedList<char> &wg,int &bg){
        
    //position is index of user guess in string
    int pos=rw.find(ug);
    
    //If pos found guess is correct
    if(pos!=-1){
        //store correct guess
        cg.push_back(ug);
        cout<<"\n\n*******Correct Guess*********** \n\n";
        cout<<"Correct Letters: ";
        
        //Print correct guesses
        cg.printList();
        
        //Print Wrong Guesses
        if(bg>=1){
        cout<<"\n\n*********Incorrect Guesses: ************\n\n";
        wg.printList();
        }
        //increment correct guesses
        crg++;
        
    //replace user guess with position in hidden word
    while(pos!=-1){
        hw.replace(pos,1,1,ug);
        pos=rw.find(ug,pos+1);
        cout<<hw<<"\n";
    }
    }else{
        //if not found guess is wrong
        wg.push_back(ug);
        cout<<"\n\n************Incorrect Guess ***********\n\n";
        cout<<"Current Wrong Guesses: ";
        wg.printList();
        cout<<"Current Right Guesses: ";
        cg.printList();
        cout<<hw<<"\n";
        
        //increment bad guesses
        bg++;
        if(bg==6){
            cout<<"\n\n The Word Was: "<<rw<<"\n";
        }
    }
}

//Return a string of _ with given string
string hideString(string& str){
    string out="";
    for(int i=0;i<str.length();i++){
        out.append("_");
    }
        return out;
}

//Return a random string from vector
string getWord(vector<string>& v){
    int n=rand()%v.size();
    return v.at(n);
}

//Push words from file into vector
void pushWords(fstream &f,vector<string>& v){
    string fl;  //holds file input
    
    //open file for read in
    f.open("words.dat",ios::in);
    
    //if opened successfully
    if(f){
        for(fl;getline(f,fl);)
            v.push_back(fl);    //push to vector
           f.close();           //close file
    }else{
        cout<<"could not open the file \n";
    }
}

