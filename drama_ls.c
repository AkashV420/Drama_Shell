#include "library.h"
#include "functions.h"
char home[1500];  
char prompt[1500];
char pwd[1500]; 
char* commands[26];


int drama_Ls(int argc, char **args){ //argc : argument count
  struct dirent *name;
  //how dirent is defined in c :
//   struct dirent {
//     ino_t          d_ino;       /* inode number */
//     off_t          d_off;       /* offset to the next dirent */
//     unsigned short d_reclen;    /* length of this record */
//     unsigned char  d_type;      /* type of file; not supported
//                                    by all file system types */
//     char           d_name[256]; /* filename */
// };
  DIR *curDir;//list directory contents.
  
   char fullpath[256];                                                     
   int err;
  struct stat fileStat;
  int flag_a = 0, flag_l = 0, cur_directory = 0, flag_la=0, no_directories=0, i=1;


  while (i < argc) 
  {
    
	        if (strcmp(args[i], "-a") == 0)
              flag_a = 1;
  
            else if (strcmp(args[i], "-l") == 0)
              flag_l = 1;
  
            else if (strcmp(args[i], "-al") == 0){
              flag_la = flag_l = flag_a = 1;
            }
  
            else if( strcmp(args[i], "-la") == 0)
            {
        
              flag_la = flag_l = flag_a=1;
            }

	        else{
	        	cur_directory=i; 
	        }    
     i+=1;
  	}


  no_directories = argc - flag_a - flag_l - flag_la - 1;
   //when only " ls " is entered.
   if(!cur_directory) 
  {
  	
  	no_directories=1;
  	args[1]=".";
  	err = 1;
  	cur_directory=1;
  
  }
  else // While listing the files and the sub-directories of the particular file i.e ls directory_name
  {
	  curDir=opendir(args[1]);
	if(curDir==NULL)
  	{
  		perror("Cannot find directory .. :(\n");
		  return 1;
  	}	
	while(name=readdir(curDir))
  		  printf("%s\n",name->d_name);
  }
  
  
  
  ///////////////////////////////////////////////////////////////////////////////////// ls -a -l 
  int zero = 0;
  for(int j=zero; j < (no_directories); ++j)
  {
  	//directory stream
	  curDir = opendir(args[cur_directory]); 
	
	if (!(curDir)){
		printf("%s: No such file or directory.. :(\n", args[cur_directory]);
		continue;
	}
	while((name = readdir(curDir)))
	{
      if (stat(name->d_name, &fileStat) != zero)
      {
        continue;
      }
      if(name->d_name[zero] == '.'){
	      if (!flag_a)  
    	  	continue;
      }
    
      strcpy (fullpath, args[cur_directory]);
	  strcat (fullpath, "/");
	  strcat (fullpath, name->d_name);
      
	  if (flag_a && !flag_l) 
	  {
        printf("%s\n", name->d_name);
      }
      
	  else if (!flag_a && !flag_l && name->d_name[0] != '.')
	  {
        printf("%s\n", name->d_name);
      }
      
	  else if (flag_l) 
	  {
		if (!stat(fullpath, &fileStat)) 
		{   
			   unsigned char date[140];
			   struct group* Grp = getgrgid(fileStat.st_gid);
			   struct passwd* Usr = getpwuid(fileStat.st_uid);
				
				time_t now;
				time(&now);
				int year = localtime(&now)->tm_year;
				struct tm* strtime = localtime(&fileStat.st_ctime);
				
				printf((S_ISDIR(fileStat.st_mode))  ? "d" : "-");
				printf((fileStat.st_mode & S_IRUSR) ? "r" : "-");
				printf((fileStat.st_mode & S_IWUSR) ? "w" : "-");
				printf((fileStat.st_mode & S_IXUSR) ? "x" : "-");
				printf((fileStat.st_mode & S_IRGRP) ? "r" : "-");
				printf((fileStat.st_mode & S_IWGRP) ? "w" : "-");
				printf((fileStat.st_mode & S_IXGRP) ? "x" : "-");
				printf((fileStat.st_mode & S_IROTH) ? "r" : "-");
				printf((fileStat.st_mode & S_IWOTH) ? "w" : "-");
				printf((fileStat.st_mode & S_IXOTH) ? "x" : "-");
				printf(" %d  ",(int) fileStat.st_nlink);
				printf(" %s", Usr->pw_name);
				printf(" %s", Grp->gr_name);
				printf(" %lld",(long long)fileStat.st_size);

				strftime(date, 100, "%h %d %H:%M", localtime(&(fileStat.st_ctime))); /* time of last status change */

				printf(" %s",date );                  
				printf(" %s\n",name->d_name);
			}
		else perror("Error in stat .. :(");
  	  	printf("\n");
		}
 
  	}
  --cur_directory;	
}
	closedir(curDir);
	return 0;
}


