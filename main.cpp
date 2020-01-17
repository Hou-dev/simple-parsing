#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <fstream>
#include <istream>
#include <string>
#include <queue>
#include <vector>
#include <sstream>
#include <algorithm>
#include <semaphore.h>
#include <map>
using namespace std;

queue<string>myqueue; //read from commands file
queue<string>commands; //seperates commands from myqueue
queue<string>glbvarintvar; //puts unique vars p's into queue
queue<string>vars; //puts unique var a-i into queue
queue<int>commandloc; //locations of commands to use for caculator.
vector<string> Ays; //A vector containing just a-i in order of read.
vector<string> Pys; //A vector containing just p's in order of read.
vector<string> Cmds; //A vector of command + - * /
int glbcounter;
int noOfvar;//counter of number of a-i
int noOfintvar;// counter for p's
int Acounter;

//These are the varibles
int a;
int b;
int c;
int d;
int e;
int f;
int g;
int h;
int i;
int j;



int Cal(int &nds, string gba, int &gbc); //calculator
void readstdin(string myfile); //reading data
void readcommands(string commandsfile); //reading commands
void parsecommands(); //function to parse commands
void completedSeries();//parent and fork with calculation
void internationalvars(string gothim); //convert data and reads into process
void trim(string& s);//trims white space

#define PIPE_RD 0
#define PIPE_WR 1

int main(int argc, char* argv[]){
    int p0;
    readstdin(argv[2]);
    readcommands(argv[1]);
    parsecommands();
    completedSeries();
    return 0;
}

int Cal(int &nds, string gba, int &gbc){
    //checks computation and returns to fork
    if(gba=="N"){
        gbc = nds;
    }
    else if(gba=="+"){
        gbc = gbc+nds;
    }
    else if(gba == "-"){
        gbc = gbc - nds;
    }
    else if(gba == "*"){
        gbc = gbc * nds;
    }
    else if(gba == "/"){
        gbc = gbc / nds;
    }
    return gbc;
}

void readstdin(string myfile){
    //reads file and place into process.
    queue<int> makeQ;
    string fileint;
    ifstream inpfile;
    string a;//this string is used when data file is sent
    //int varcount;
    inpfile.open(myfile.c_str());

    getline(inpfile,fileint);
    replace(fileint.begin(), fileint.end(), ' ', ',');//replaces any white space with comma
    istringstream ss(fileint);
    //put data into function
    while(getline(ss,a,',')){
        internationalvars(a);
    }
    inpfile.close();
}

void readcommands(string commandsfile){
    //reads from commands txt
    ifstream commands;
    commands.open(commandsfile.c_str());
    string inp;
    string token;
    //skips first input then counts no of vars.
    commands>>inp;
    if (inp == "input_var"){
        ;
    }
    getline(commands,inp);
    istringstream ss(inp);
    while(getline(ss,token, ',')){
        if (token != ";"){
            noOfvar++;
        }

    }
    //skips second line and counts p vars
    commands>>inp;
    if (inp == "internal_var"){
        ;
    }
    getline(commands,inp);
    istringstream sp(inp);
    while(getline(sp,token, ',')){
        if(token != ";"){
            noOfintvar++;
        }

    }

    //read all commands with whitespace in front
    while(!commands.eof()){
        getline(commands,inp);
        istringstream sj(inp);
        while(getline(sj,token,';')){
            if (token == ";"){
                //cout<<token;
            }
            else{
                myqueue.push(token);
            }
        }

    }
    commands.close();

}

void parsecommands(){
    int loc = 0;
    int p = myqueue.size();
    //reads commands aritmetic commands queue
    for(int k = 0;k<p-1;k++){

        istringstream iss(myqueue.front());
        string s;

        while ( getline( iss, s, ' ') ) {


            trim(s);

            if(s=="+" || s == "-" || s=="*"|| s=="/"){

                commands.push(s);
                commandloc.push(loc);
            }

            else{
                //push intergetrs to glbvarintvar queue.
                if(s !=  "->"){
                    glbvarintvar.push(s);

                }

            }

        }
        loc++;
        myqueue.pop();

    }



    while(!glbvarintvar.empty()){

        vars.push(glbvarintvar.front());
        glbvarintvar.pop();
        if(glbvarintvar.front() == "->"){
            glbvarintvar.pop();
        }
    }
    //pushes a-i p's read to a var to be calculated later.
    int sizeofvars = vars.size()/2;
    for(int s = 0; s<sizeofvars; s++){
        Ays.push_back(vars.front());
        vars.pop();
        Pys.push_back(vars.front());
        vars.pop();
    }
    //pushes all variables to a vector.
    for(int ge = 0; ge<sizeofvars; ge++){
        if(commandloc.front() == ge){
            commandloc.pop();
            Cmds.push_back(commands.front());
            commands.pop();
        }
        //pushes N if there is no arithmetic.
        else{
            Cmds.push_back("N");

        }

    }
    //this counts the number of times a-i appears.
    std::vector<string>::iterator ItA = Ays.begin();
    for(int t=0;t<Ays.size();t++){
        if(*ItA=="a"||*ItA=="b"||*ItA=="c"||*ItA=="d"||*ItA=="e"||*ItA=="f"||*ItA=="g"||*ItA=="h"||*ItA=="i"){
            Acounter++;
        }
        *ItA++;
    }
}

void completedSeries(){
    //inint internal vars.
    int p0;
    int p1;
    int p2;
    int p3;
    int p4;
    int p5;
    int p6;
    int p7;
    int p8;
    int p9;
    //vectors containing a-i,arithmetic and p0-p9
    std::vector<string>::iterator ItA = Ays.begin();
    std::vector<string>::iterator  ItB = Cmds.begin();
    std::vector<string>::iterator ItC = Pys.begin();

    //mapping vector of p0-p9 in order they came in
    map<int,int>writePs;
    for(int mappedPs=0; mappedPs<Pys.size();mappedPs++){
        if(*ItC == "p0"){
            writePs.insert(pair <int,int>(mappedPs,p0));
        }
        if (*ItC == "p1"){
            writePs.insert(pair <int,int>(mappedPs,p1));
        }
        if (*ItC == "p2"){
            writePs.insert(pair <int,int>(mappedPs,p2));
        }
        if (*ItC == "p3"){
            writePs.insert(pair <int,int>(mappedPs,p3));
        }
        if (*ItC == "p4"){
            writePs.insert(pair <int,int>(mappedPs,p4));
        }
        if (*ItC == "p5"){
            writePs.insert(pair <int,int>(mappedPs,p5));
        }
        if (*ItC == "p6"){
            writePs.insert(pair <int,int>(mappedPs,p6));
        }
        if (*ItC == "p7"){
            writePs.insert(pair <int,int>(mappedPs,p7));
        }
        if (*ItC == "p8"){
            writePs.insert(pair <int,int>(mappedPs,p8));
        }
        if (*ItC == "p9"){
            writePs.insert(pair <int,int>(mappedPs,p9));
        }
        *ItC++;
    }
    //mapping the a-i in the order they came in
    map<int,int>writeAs;

    for(int mappedAs=0; mappedAs<Ays.size();mappedAs++){
        if(*ItA == "a"){

            writeAs.insert(pair <int,int>(mappedAs,a));
        }
        if (*ItA == "b"){

            writeAs.insert(pair <int,int>(mappedAs,b));
        }
        if (*ItA == "c"){

            writeAs.insert(pair <int,int>(mappedAs,c));
        }
        if (*ItA == "d"){

            writeAs.insert(pair <int,int>(mappedAs,d));
        }
        if(*ItA == "e"){

            writeAs.insert(pair <int,int>(mappedAs,e));
        }
        if (*ItA == "f"){

            writeAs.insert(pair <int,int>(mappedAs,f));
        }
        if (*ItA == "g"){

            writeAs.insert(pair <int,int>(mappedAs,g));
        }
        if (*ItA == "h"){

            writeAs.insert(pair <int,int>(mappedAs,h));
        }
        if (*ItA == "i"){

            writeAs.insert(pair <int,int>(mappedAs,i));
        }
        if(*ItA == "p0"){
            writeAs.insert(pair <int,int>(mappedAs,p0));
        }
        if (*ItA == "p1"){
            writeAs.insert(pair <int,int>(mappedAs,p1));
        }
        if (*ItA == "p2"){
            writeAs.insert(pair <int,int>(mappedAs,p2));
        }
        if (*ItA == "p3"){
            writeAs.insert(pair <int,int>(mappedAs,p3));
        }
        if(*ItA == "p4"){
            writeAs.insert(pair <int,int>(mappedAs,p4));
        }
        if (*ItA == "p5"){
            writeAs.insert(pair <int,int>(mappedAs,p5));
        }
        if (*ItA == "p6"){
            writeAs.insert(pair <int,int>(mappedAs,p6));
        }
        if (*ItA == "p7"){
            writeAs.insert(pair <int,int>(mappedAs,p7));
        }
        if (*ItA == "p8"){
            writeAs.insert(pair <int,int>(mappedAs,p8));
        }
        if (*ItA == "p9"){
            writeAs.insert(pair <int,int>(mappedAs,p9));
        }
        *ItA++;
    }
    //mapping all the arithmetic in the order they came in.
    map <int,string> commander;
        for(int mapper=0; mapper<Cmds.size();mapper++){
        if(*ItB == "+"){
            commander.insert(pair <int,string>(mapper,"+"));
        }
        if (*ItB == "-"){
            commander.insert(pair <int,string>(mapper,"-"));
        }
        if (*ItB == "*"){
            commander.insert(pair <int,string>(mapper,"*"));
        }
        if (*ItB == "/"){
            commander.insert(pair <int,string>(mapper,"/"));
        }
        if (*ItB == "N"){
            commander.insert(pair <int,string>(mapper,"="));
        }
        *ItB++;
    }

    //this test what type of string is need and makes the pipe for the process
    map<int,string> testmap;
    testmap.insert(pair <int,string>(0,"p0"));
    testmap.insert(pair <int,string>(1,"p1"));
    testmap.insert(pair <int,string>(2,"p2"));
    testmap.insert(pair <int,string>(3,"p3"));
    testmap.insert(pair <int,string>(4,"p4"));
    testmap.insert(pair <int,string>(5,"p5"));
    testmap.insert(pair <int,string>(6,"p6"));
    testmap.insert(pair <int,string>(7,"p7"));
    testmap.insert(pair <int,string>(8,"p8"));
    testmap.insert(pair <int,string>(9,"p9"));

    //init processes
    pid_t pids[8];
    int i;

    //init the pipes
    int n = 8;
    int fd[9][2];
    pipe(fd[0]);
    pipe(fd[1]);
    pipe(fd[2]);
    pipe(fd[3]);
    pipe(fd[4]);
    pipe(fd[5]);
    pipe(fd[6]);
    pipe(fd[7]);
    pipe(fd[8]);

    //the acounter determines the number of a-i and writes to pipe, it then contines in the
    //other section to help direct the p's for the final calculation.
    int f = Acounter/2;
    for(int r =0; r<f;r++){
        write(fd[r][1],&writeAs[2*r],sizeof(int));
        write(fd[r][1],&writeAs[2*r+1],sizeof(int));
        write(fd[r][1],&commander[2*r+1],sizeof(string));
    }

    /*write(fd[0][1],&writeAs[0],sizeof(int));
    write(fd[0][1],&writeAs[1],sizeof(int));
    write(fd[0][1],&commander[1],sizeof(string));

    write(fd[1][1],&writeAs[2],sizeof(int));
    write(fd[1][1],&writeAs[3],sizeof(int));
    write(fd[1][1],&commander[3],sizeof(string));

    write(fd[2][1],&writeAs[4],sizeof(int));
    write(fd[2][1],&writeAs[5],sizeof(int));
    write(fd[2][1],&commander[5],sizeof(string));*/



    //this is where all the forks happens, it is determined by f, the number of a-i
    int child_status;
    for (i = 0; i < f; i++) {
        if ((pids[i] = fork()) < 0) {
            perror("fork");
            abort();
        }
        if (pids[i] == 0) {
            int k,l,m,kl;
            string ps;
            //pipes are read here
            read(fd[i][0],&k,sizeof(k));
            read(fd[i][0],&l,sizeof(l));
            read(fd[i][0],&ps,sizeof(ps));
            //computation is done here
            if(ps == "-"){
                kl = k-l;
            }
            if(ps == "+"){
                kl = k+l;
            }
            if(ps=="*"){
                kl = k*l;
            }
            if(ps=="/"){
                kl = k/l;
            }
            if(ps=="="){
                kl = l;
            }
            //computation results are piped to the parent
            write(fd[i][1],&kl,sizeof(kl));
            exit(0);
        }
        else{
            //parent waits for the child process to finsih
            wait(NULL);
            //check which variable to read to
            if(testmap[i] == "p0"){
                read(fd[i][0],&p0,sizeof(int));
            }
            if(testmap[i] == "p1"){
                read(fd[i][0],&p1,sizeof(int));
            }
            if(testmap[i] == "p2"){
                read(fd[i][0],&p2,sizeof(int));
            }
            if(testmap[i] == "p3"){
                read(fd[i][0],&p3,sizeof(int));
            }
            if(testmap[i] == "p4"){
                read(fd[i][0],&p4,sizeof(int));
            }
            if(testmap[i] == "p5"){
                read(fd[i][0],&p5,sizeof(int));
            }
            if(testmap[i] == "p6"){
                read(fd[i][0],&p6,sizeof(int));
            }
            if(testmap[i] == "p7"){
                read(fd[i][0],&p7,sizeof(int));
            }
            if(testmap[i] == "p8"){
                read(fd[i][0],&p8,sizeof(int));
            }
            if(testmap[i] == "p9"){
                read(fd[i][0],&p9,sizeof(int));
            }
        }

    }
    //this is the final fork that determines p3;
    write(fd[f][1],&p0,sizeof(int));
    write(fd[f][1],&p1,sizeof(int));
    write(fd[f][1],&p2,sizeof(int));
    write(fd[f][1],&commander[7],sizeof(string));
    write(fd[f][1],&commander[8],sizeof(string));
        for (i = 3; i < f+1; i++) {
        if ((pids[i] = fork()) < 0) {
            perror("fork");
            abort();
        }
        if (pids[i] == 0) {
            int k,l,m,kl;
            string ps,gs;
            //read the pipes for computaion
            read(fd[i][0],&k,sizeof(k));
            read(fd[i][0],&l,sizeof(l));
            read(fd[i][0],&m,sizeof(m));
            read(fd[i][0],&ps,sizeof(ps));
            read(fd[i][0],&gs,sizeof(gs));
            //cout<<"Child Process: "<<k<<" "<<l<<" "<<m<<endl;
            //caculator
            if(ps == "-"){
                kl = k-l;
            }
            if(ps == "+"){
                kl = k+l;
            }
            if(ps=="*"){
                kl = k*l;
            }
            if(ps=="/"){
                kl = k/l;
            }
            if(ps=="="){
                kl = l;
            }

            if(gs == "-"){
                kl = kl-m;
            }
            if(gs == "+"){
                kl = kl+m;
            }
            if(gs=="*"){
                kl = kl*m;
            }
            if(gs=="/"){
                kl = kl/m;
            }
            if(gs=="="){
                kl = m;
            }
            //cout<<"Child Process: "<<kl<<endl;
            //writes the final results to pipe.
            write(fd[i][1],&kl,sizeof(kl));
            exit(0);
        }
        else{
            //waits for child process
            wait(NULL);
            //check which variable to read to.
            if(testmap[i] == "p0"){
                read(fd[i][0],&p0,sizeof(int));
            }
            if(testmap[i] == "p1"){
                read(fd[i][0],&p1,sizeof(int));
            }
            if(testmap[i] == "p2"){
                read(fd[i][0],&p2,sizeof(int));
            }
            if(testmap[i] == "p3"){
                read(fd[i][0],&p3,sizeof(int));
            }
            if(testmap[i] == "p4"){
                read(fd[i][0],&p4,sizeof(int));
            }
            if(testmap[i] == "p5"){
                read(fd[i][0],&p5,sizeof(int));
            }
            if(testmap[i] == "p6"){
                read(fd[i][0],&p6,sizeof(int));
            }
            if(testmap[i] == "p7"){
                read(fd[i][0],&p7,sizeof(int));
            }
            if(testmap[i] == "p8"){
                read(fd[i][0],&p8,sizeof(int));
            }
            //read(fd[i][0],&writePs[i],sizeof(int));
            //pid_t tpid = wait(&child_status);

        }

    }
    //determine what variables to print determine from parsing in the txt file.
    if(noOfvar == 1){
        cout<<"Parent Process a: "<<a<<endl;

    }
    if(noOfvar == 2){
        cout<<"Parent Process a: "<<a<<endl;
        cout<<"Parent Process b: "<<b<<endl;
    }

    if(noOfvar == 3){
        cout<<"Parent Process a: "<<a<<endl;
        cout<<"Parent Process b: "<<b<<endl;
        cout<<"Parent Process c: "<<c<<endl;
    }
    if(noOfvar == 4){
        cout<<"Parent Process a: "<<a<<endl;
        cout<<"Parent Process b: "<<b<<endl;
        cout<<"Parent Process c: "<<c<<endl;
        cout<<"Parent Process d: "<<d<<endl;
    }
    if(noOfvar == 5){
        cout<<"Parent Process a: "<<a<<endl;
        cout<<"Parent Process b: "<<b<<endl;
        cout<<"Parent Process c: "<<c<<endl;
        cout<<"Parent Process d: "<<d<<endl;
        cout<<"Parent Process e: "<<e<<endl;
    }
    if(noOfvar == 6){
        cout<<"Parent Process a: "<<a<<endl;
        cout<<"Parent Process b: "<<b<<endl;
        cout<<"Parent Process c: "<<c<<endl;
        cout<<"Parent Process d: "<<d<<endl;
        cout<<"Parent Process e: "<<e<<endl;
        cout<<"Parent Process f: "<<f<<endl;
    }
    if(noOfvar == 7){
        cout<<"Parent Process a: "<<a<<endl;
        cout<<"Parent Process b: "<<b<<endl;
        cout<<"Parent Process c: "<<c<<endl;
        cout<<"Parent Process d: "<<d<<endl;
        cout<<"Parent Process e: "<<e<<endl;
        cout<<"Parent Process f: "<<f<<endl;
        cout<<"Parent Process g: "<<g<<endl;
    }
    if(noOfvar == 8){
        cout<<"Parent Process a: "<<a<<endl;
        cout<<"Parent Process b: "<<b<<endl;
        cout<<"Parent Process c: "<<c<<endl;
        cout<<"Parent Process d: "<<d<<endl;
        cout<<"Parent Process e: "<<e<<endl;
        cout<<"Parent Process f: "<<f<<endl;
        cout<<"Parent Process g: "<<g<<endl;
        cout<<"Parent Process h: "<<h<<endl;

    }
    if(noOfvar == 9){
        cout<<"Parent Process a: "<<a<<endl;
        cout<<"Parent Process b: "<<b<<endl;
        cout<<"Parent Process c: "<<c<<endl;
        cout<<"Parent Process d: "<<d<<endl;
        cout<<"Parent Process e: "<<e<<endl;
        cout<<"Parent Process f: "<<f<<endl;
        cout<<"Parent Process g: "<<g<<endl;
        cout<<"Parent Process h: "<<h<<endl;
        cout<<"Parent Process i: "<<i<<endl;
    }
    if(noOfintvar == 1){
        cout<<"Parent Process p0: "<<p0<<endl;

    }
    if(noOfintvar == 2){
        cout<<"Parent Process p0: "<<p0<<endl;
        cout<<"Parent Process p1: "<<p1<<endl;
    }

    if(noOfintvar == 3){
        cout<<"Parent Process p0: "<<p0<<endl;
        cout<<"Parent Process p1: "<<p1<<endl;
        cout<<"Parent Process p2: "<<p2<<endl;
    }
    if(noOfintvar == 4){
        cout<<"Parent Process p0: "<<p0<<endl;
        cout<<"Parent Process p1: "<<p1<<endl;
        cout<<"Parent Process p2: "<<p2<<endl;
        cout<<"Parent Process p3: "<<p3<<endl;
    }
    if(noOfintvar == 5){
        cout<<"Parent Process p0: "<<p0<<endl;
        cout<<"Parent Process p1: "<<p1<<endl;
        cout<<"Parent Process p2: "<<p2<<endl;
        cout<<"Parent Process p3: "<<p3<<endl;
        cout<<"Parent Process p4: "<<p4<<endl;
    }
    if(noOfintvar == 6){
        cout<<"Parent Process p0: "<<p0<<endl;
        cout<<"Parent Process p1: "<<p1<<endl;
        cout<<"Parent Process p2: "<<p2<<endl;
        cout<<"Parent Process p3: "<<p3<<endl;
        cout<<"Parent Process p4: "<<p4<<endl;
        cout<<"Parent Process p5: "<<p5<<endl;
    }
    if(noOfintvar == 7){
        cout<<"Parent Process p0: "<<p0<<endl;
        cout<<"Parent Process p1: "<<p1<<endl;
        cout<<"Parent Process p2: "<<p2<<endl;
        cout<<"Parent Process p3: "<<p3<<endl;
        cout<<"Parent Process p4: "<<p4<<endl;
        cout<<"Parent Process p5: "<<p5<<endl;
        cout<<"Parent Process p6: "<<p6<<endl;
    }
    if(noOfintvar == 8){
        cout<<"Parent Process p0: "<<p0<<endl;
        cout<<"Parent Process p1: "<<p1<<endl;
        cout<<"Parent Process p2: "<<p2<<endl;
        cout<<"Parent Process p3: "<<p3<<endl;
        cout<<"Parent Process p4: "<<p4<<endl;
        cout<<"Parent Process p5: "<<p5<<endl;
        cout<<"Parent Process p6: "<<p6<<endl;
        cout<<"Parent Process p7: "<<p7<<endl;

    }
    if(noOfintvar == 9){
        cout<<"Parent Process p0: "<<p0<<endl;
        cout<<"Parent Process p1: "<<p1<<endl;
        cout<<"Parent Process p2: "<<p2<<endl;
        cout<<"Parent Process p3: "<<p3<<endl;
        cout<<"Parent Process p4: "<<p4<<endl;
        cout<<"Parent Process p5: "<<p5<<endl;
        cout<<"Parent Process p6: "<<p6<<endl;
        cout<<"Parent Process p7: "<<p7<<endl;
        cout<<"Parent Process p8: "<<p8<<endl;
    }
    //cout<<p0<<" "<<p1<<" "<<p2<<" ";
    //p3 = p0*p1+p2;
    //cout<<p3;
    //cout<<writePs[1];
}



void internationalvars(string gothim){
    //this function reads file and converts it into int.
    if(glbcounter ==0){
        a = atoi(gothim.c_str());
    }
    if(glbcounter ==1){
        b = atoi(gothim.c_str());
    }
    if(glbcounter ==2){
        c = atoi(gothim.c_str());
    }
    if(glbcounter ==3){
        d = atoi(gothim.c_str());
    }
    if(glbcounter ==4){
        e = atoi(gothim.c_str());
    }
    if(glbcounter ==5){
        f = atoi(gothim.c_str());
    }
    if(glbcounter ==6){
        g = atoi(gothim.c_str());
    }
    if(glbcounter ==7){
        h = atoi(gothim.c_str());
    }
    if(glbcounter ==8){
        i = atoi(gothim.c_str());
    }
    if(glbcounter ==9){
        j = atoi(gothim.c_str());
    }
    glbcounter++;
}

void trim(string& s){
    //this function removes any white space.
    size_t p = s.find_first_not_of(" \t");
    s.erase(0, p);

    p = s.find_last_not_of(" \t");
    if (string::npos != p)
        s.erase(p+1);
}


