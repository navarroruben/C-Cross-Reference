/**********************/
// Date: Febuary 04, 2019
// Name: Ruben Navarro
// JC-Cross Reference
/**********************/

%{
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cctype>
#include <map>
#include <vector>
#include <string>

#define CHAR    256
#define NUM     257
#define IDENT   258
#define INVALID 259
#define COMMENT 260
#define STRING  261
#define NEWLINE 262
#define RESERVED 263
#define PREPROC 264
#define DEFAULTCHAR 265 

int character = 0;
int string = 0;
int comment = 0;
int lineNum = 1;

std::map<std::string, std::vector<int> > mymap; 

/* function proto */
void lexical_error(const std::string msg="");
%}

prepro   (#)
quote    \'
back     \\
ditto    \"
octal    [0-7]
octch    ({back}{octal}|{back}{octal}{octal}|{back}{octal}{octal}{octal})
digit    [0-9]
alpha    [a-zA-Z_]
schar    [^\'\"\n\\]
char     ({back}?({schar}|{ditto})|{back}{back}|{back}{quote}|{octch})
reserved  (register)|(int)|(if)|(auto)|(break)|(case)|(char)|(const)|(continue)|(default)|(do)|(double)|(else)|(extern)|(float)|(for)|(volatile)
reserved1 (goto)|(long)|(return)|(short)|(sizeof)|(signed)|(static)|(struct)|(switch)|(typedef)|(union)|(unsigned)|(void)|(while)|(enum)
defchar   (=)|(;)|(,)
%%
{quote}  { character = !character; }

"#include"[[:space:]]("<".*">"|{ditto}.*{ditto})"\n" { return PREPROC; }
{prepro}.*{schar} { return PREPROC; }

"/*".*"*/"                                                    { return COMMENT; }                                               
"//".*{schar}                                                 { return COMMENT; } 
{ditto}(\\.|[^"\\])*{ditto}                                   { return STRING; }
{quote}({alpha}|{digit}|{char}|{ditto}|{back}|{quote}){quote} { return CHAR; } 
"\n"                                                          { return NEWLINE; }
{reserved}                                                    { return RESERVED; }
{reserved1}                                                   { return RESERVED; }
{defchar}                                                     { return DEFAULTCHAR; }
{alpha}({alpha}|{digit})*                                     { if (!character) return IDENT; }
{digit}+                                                      { return NUM;  }
<<EOF>>                                                       { return EOF;  }
.                                                             { ; }
%%
/*******************/
/* c/c++ functions */
/*******************/

int main() {
    int tok;
    bool flag = false;
    std::vector<std::string> s;
    while ((tok = yylex()) != EOF) {

      switch(tok) {
      case IDENT: { std::cout << "Found ID token = " << yytext << std::endl;
        s.push_back(yytext);
         
        std::vector<std::string>::iterator sit = s.begin();
       
        for (; sit != s.end() - 1; ++sit)
 {
    if (yytext == *sit)
{
       std::cout << "FOUND\n"; 
       flag = true;
} 
 }

        if (!flag)
          mymap[yytext].push_back(lineNum);
         break;
}
      case NUM:  std::cout << "Found NUM token = " << yytext << std::endl;
         break;
      case CHAR:  std::cout << "Found CHAR token = " << yytext << std::endl;
         break;
      case COMMENT:  std::cout << "Found COMMENT token = " << yytext << std::endl;
         break;
      case STRING:  std::cout << "Found STRING token = " << yytext << std::endl;
         break;
      case NEWLINE: {  std::cout << "Found NEW LINE token = " << yytext << std::endl;                                                                                          s.clear();
         flag = false;
         ++lineNum;
         break;
}
      case RESERVED:  std::cout << "Found RESERVED token = " << yytext << std::endl;
         break;
      case PREPROC:  std::cout << "Found PREPROC token = " << yytext << std::endl;                                                                             
         break;
      case DEFAULTCHAR:  std::cout << "Found DEFAULT CHAR token = " << yytext << std::endl;
         break;     
      default:
              lexical_error("I don't know what this token is");
              exit(1);
      }
    }

for ( std::map<std::string,std::vector<int> >::iterator it = mymap.begin(); it != mymap.end(); ++it) {
std::cout << it->first << ": ";
  for ( std::vector<int>::iterator vectit = it->second.begin(); vectit != it->second.end(); ++vectit)
    {
      std::cout << *vectit << ", "; 
    } 
std::cout << "\n";
}
return 0;
}

int yywrap() {
   std::cout << "Bye Bye!\n";
   return 1;
}

void lexical_error(const std::string msg) {
  std::cout << msg << std::endl;
} 
