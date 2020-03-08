#ifndef SHELL_H
   
        char* display();
        int readInput();
        char** splitTokens(char* );
        int drama_Cd (int, char**);
        int drama_Pwd (int, char**);
        int drama_Echo (int, char**);
        int drama_Execute(int, char**);
        int drama_Check(char**);
        int drama_Proc(char**);
        int drama_Ls(int, char**);
        void drama_Pinfo(char **, int);
        //void newCmd(char* cmd);

        int argCount(char ** args);
        char ** argumentize(char* cmd);
        int checkBackgroud();

void truncateCommand(char **args,int index);
char* checkInputRedirection(char **args);
char* checkOutputRedirection(char **args);
char* checkAppendRedirection(char **args);

int pipeExec(char *cmd, char**);
int checkPipe(char *cmd);
char ** parsePipe(char* cmd);

     int drama_unsetenv(char **args);
     void drama_overkill();
     int drama_jobs(char **args);
     int drama_kjob(char **args);
     int drama_bg(char **args);
     int drama_fg(char **args);
     int drama_setenv(char **args);   
        
#endif