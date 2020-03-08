#ifndef SHELL_H
   
        char* display();
        int readInput();
        char** splitTokens(char* );
        int drama_Cd (int, char**);
        int drama_Pwd (int, char**);
        int drama_Echo (int, char**);
        int drama_Execute(int, char**, int);
        int drama_Check(char**);
        int drama_Proc(char**, int);
        int drama_Ls(int, char**);
        void drama_Pinfo(char **, int);
        void newCmd(char* cmd);
        void listHistory();
        
#endif