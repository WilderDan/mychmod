/* $Id: main.c,v 1.2 2015/03/15 01:19:48 sentient Exp sentient $ 
 *
 * Author: Dan Wilder
 *
 * REVISION HISTORY
 *   $Log: main.c,v $
 *   Revision 1.2  2015/03/15 01:19:48  sentient
 *   Added fileCount
 *
 *   Revision 1.1  2015/03/15 00:48:29  sentient
 *   Initial revision
 *
 *
 */

#include <stdlib.h> 
#include <stdio.h>    
#include <ctype.h>    
#include <unistd.h>   
#include <sys/stat.h>
#include <string.h>

void DisplayUsage(char *);

/*****************************************************************************
 *    main()                                                                 *
 *****************************************************************************/

int main(int argc, char **argv) {

  int c;
  int i;
  int index;
  int fileCount = 0;

  char isFileError = 0;
  uid_t myUid = getuid();

  struct stat fileStat;
  mode_t addPermissions = 0;
  mode_t removePermissions = 0;

  opterr = 0; // prevents the default error messages of getopt() 

  while ((c = getopt (argc, argv, "u:g:o:U:G:O:")) != -1) { // Parse cli args
    switch (c) {
 
    case 'u':
      for (i=0; i<strlen(optarg); i++) {
        if (optarg[i] == 'r') 
          addPermissions |= S_IRUSR;
        else if (optarg[i] == 'w') 
          addPermissions |= S_IWUSR;
        else if (optarg[i] == 'x') 
          addPermissions |= S_IXUSR;
      }
      break;

    case 'g':
      for (i=0; i<strlen(optarg); i++) {
        if (optarg[i] == 'r') 
          addPermissions |= S_IRGRP;
        else if (optarg[i] == 'w') 
          addPermissions |= S_IWGRP;
        else if (optarg[i] == 'x') 
          addPermissions |= S_IXGRP;
      }
      break;

    case 'o':
      for (i=0; i<strlen(optarg); i++) {
        if (optarg[i] == 'r') 
          addPermissions |= S_IROTH;
        else if (optarg[i] == 'w') 
          addPermissions |= S_IWOTH;
        else if (optarg[i] == 'x') 
          addPermissions |= S_IXOTH;
      }
      break;

    case 'U':
      for (i=0; i<strlen(optarg); i++) {
        if (optarg[i] == 'r') 
          removePermissions |= S_IRUSR;
        else if (optarg[i] == 'w') 
          removePermissions |= S_IWUSR;
        else if (optarg[i] == 'x') 
          removePermissions |= S_IXUSR;
      }
      break;

    case 'G':
      for (i=0; i<strlen(optarg); i++) {
        if (optarg[i] == 'r') 
          removePermissions |= S_IRGRP;
        else if (optarg[i] == 'w') 
          removePermissions |= S_IWGRP;
        else if (optarg[i] == 'x') 
          removePermissions |= S_IXGRP;
      }
      break;

    case 'O':
      for (i=0; i<strlen(optarg); i++) {
        if (optarg[i] == 'r') 
          removePermissions |= S_IROTH;
        else if (optarg[i] == 'w') 
          removePermissions |= S_IWOTH;
        else if (optarg[i] == 'x') 
          removePermissions |= S_IXOTH;
      }
      break;

    case '?': // getopt detected invalid option character or missing target

      if (optopt == 'u' || optopt == 'g' || optopt == 'o' ||\
          optopt == 'U' || optopt == 'G' || optopt == 'O')
        fprintf (stderr, "\n\t***Option -%c requires an argument***\n", optopt);
      else if (isprint (optopt))
        fprintf (stderr, "\n\t***Unknown option `-%c'***\n", optopt);
      else
        fprintf (stderr, "\n\t***Unknown option character `\\x%x'***\n", optopt);

      DisplayUsage(argv[0]);

      printf("Exit status: 1\n");
      return 1; // Error!

    default:
      abort (); // Critical Error!
    }
  }

  if (argc == 1)
    DisplayUsage(argv[0]);

  else { // Change permission for each file

    for (index = optind; index < argc; index++) { 
      ++fileCount;
  
      if ( stat(argv[index], &fileStat) < 0) { // Check if file exists
        perror("Stat()");
        isFileError = 1; 
      }
  
      // Check if user owns file or if root
      else if (fileStat.st_uid != myUid && myUid != 0) { 
        fprintf(stderr, "UID ERROR: You do not own this file\n");
        isFileError = 1;
      }
      
      fileStat.st_mode |= addPermissions;
      fileStat.st_mode &= ~removePermissions;

      if ( chmod(argv[index], fileStat.st_mode) == -1) {
        perror(argv[index]);
        isFileError = 1;
      }
    }  
  }
  
  if (fileCount == 0) {
    printf("No file specified\nExit Status: 2\n");
    return 2;
  }

  if (isFileError) {
    printf("Exit status: 2\n");
    return 2;
  }
  else {
    printf("Exit status: 0\n");
    return 0;
  }
}

/*****************************************************************************
 *    DisplayUsage()                                                         *
 *****************************************************************************/

void DisplayUsage(char *programName) {
  fprintf(stderr, "\nSYNOPSIS\n    %s OPTION... PERMISSION... FILE...\n",\
          programName);
      
  fprintf(stderr, "\nDESCRIPTION\n    Uses unix system calls and functions");
  fprintf(stderr, " to change\n    the permissions on one or more files.\n");

  fprintf(stderr, "\nOPTIONS\n    \t-u\n\t    Add permissions for user.");
  fprintf(stderr, "\n\t-g\n\t    Add permissions for group.");
  fprintf(stderr, "\n\t-o\n\t    Add permissions for other.");
  fprintf(stderr, "\n\t-U\n\t    Remove permissions for user.");
  fprintf(stderr, "\n\t-G\n\t    Remove permissions for group.");
  fprintf(stderr, "\n\t-O\n\t    Remove permissions for group.\n");

  fprintf(stderr, "\nPERMISSIONS\n    \tr\n\t    READ");
  fprintf(stderr, "\n\tw\n\t    WRITE");
  fprintf(stderr, "\n\tx\n\t    EXECUTE\n");
}
