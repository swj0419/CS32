//
//  main.cpp
//  recursion
//
//  Created by Weijia Shi on 7/5/17.
//  Copyright © 2017 Weijia Shi. All rights reserved.
//

#include <iostream>
#include<string>
using namespace std;

// Returns the product of two positive integers, m and n,
// using only repeated addition.
int mult(unsigned int m, unsigned int n)
{
    if(n==1)
        return m;
    return mult(m,n-1)+m;  // This is incorrect.
}


// Returns the number of occurrences of digit in the decimal
// representation of num. digit is an int between 0 and 9
// inclusive.
//
// Pseudocode Example:
//    countDigit(18838, 8) => 3
//    countDigit(55555, 3) => 0
//    countDigit(0, 0)     => 0
int countDigit(int num, int digit)
{
    if(num==0)
        return 0;
    else if(num%10==digit)
        return 1+countDigit(num/10,digit);
    else
        return countDigit(num/10,digit);
}

// Returns a string where the same characters next each other in
// string n are separated by "++"
//
// Pseudocode Example:
//    pairPlus("goodbye") => "go++odbye"
//    pairPlus("yyuu")    => "y++yu++u"
//    pairPlus("aaaa")    => "a++a++a++a"
//ood="o"+d
string pairPlus(string n)
{
    if(n.size()==0)
        return "";
    if(n.size()==1)
        return n;
    if(n[n.size()-1]==n[n.size()-2])
        return pairPlus(n.substr(0, n.size()-1)).append("++").append(n, n.size()-1,1);
    else
       return pairPlus(n.substr(0, n.size()-1)).append(n, n.size()-1,1);
}


// str contains a single pair of parenthesis, return a new string
// made of only the parenthesis and whatever those parensthesis
// contain.
//
//  Pseudocode Example:
//     subParen("abc(ghj)789") => "(ghj)"
//     subParen("(x)7")        => "(x)"
//     subParen("4agh(y)")     => "(y)"
//
string subParen(string str)
{
    // base case: if string starts with "(" and ends with ")", return string
    // recursive case:
    // if string does not start with "(": str = str.substr(1, str.size()-1);
    // if string does not end with ")": str = str.substr(0, str.size()-2);
    // return subParen(str);
    if(str=="")
        return "";
    if(str[0] != '(')
        return subParen(str.substr(1, str.size()));
    else if(str[str.size()-1]!=')')
        return subParen(str.substr(0, str.size()-1));
    else
        return str;
}

// Return true if the sum of any combination of elements in the array
// a equals the value of the target.
//
//  Pseudocode Example:
//     sumCombination([2, 4, 8], 3, 10) => true
//     sumCombination([2, 4, 8], 3, 12) => true
//     sumCombination([2, 4, 8], 3, 11) => false
//     sumCombination([], 0, 0)         => true
//
bool sumCombination(const int a[], int size, int target)
{
    if(size==0 && target !=0)
        return false;
    else if (target==0)
        return true;
    else
        return sumCombination(a, size-1, target-a[size-1]) || sumCombination(a, size-1 , target);
    
}



//////////////////////maze
//recursive call: left: parthExists() || right: pathExists() || up: 
bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
    if(sr==er && sc==ec)
        return true;
    if (sr < 0 || sc < 0 || er < 0 || ec < 0
        || sr >= nRows || sc >= nCols || er >= nRows
        || ec >= nCols)
        return false;
    maze[sr][sc]='d';
    if(sr+1<nRows)
    {
        if(maze[sr+1][sc]=='.'&& pathExists(maze, nRows, nCols, sr+1, sc, er, ec)==true)
            return true;
    }
    
    if(sr-1>=0)
    {
        if(maze[sr-1][sc]=='.'&& pathExists(maze, nRows, nCols, sr-1, sc, er, ec)==true)
            return true;
    }
    if(sc+1<nCols)
    {
        if(maze[sr][sc+1]=='.'&& pathExists(maze, nRows, nCols, sr, sc+1, er, ec)==true)
        return true;
    }
    if(sc-1>=0)
    {
        if(maze[sr][sc-1]=='.'&& pathExists(maze, nRows, nCols, sr, sc-1, er, ec)==true)
        return true;
    }
        return false;
        
}
// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise

//int main()
//{
//    string maze[10] = {
//        "XXXXXXXXXX",
//        "X.......@X",
//        "XX@X@@.XXX",
//        "X..X.X...X",
//        "X..X...@.X",
//        "X....XXX.X",
//        "X@X....XXX",
//        "X..XX.XX.X",
//        "X...X....X",
//        "XXXXXXXXXX"
//    };
//    
//    if (pathExists(maze, 10,10, 6,4, 1,1))
//        cout << "Solvable!" << endl;
//    else
//        cout << "Out of luck!" << endl;
//}




