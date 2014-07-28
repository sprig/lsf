/* (C)opyright 2014 Konstantin Kliakhandler <kosta slumpy org>
 * See LICENSE file for license details.
 */

#include <limits.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

int listdir(const char*, const char*);

int
main(int argc, char *argv[]) {
  char* dirname;


  if(argc == 1)
    exit(EXIT_FAILURE);

  if((argc > 1) && !strncmp(argv[1], "-v", 3)) {
    fputs("lsx-"VERSION", (C)opyright 2014 Konstantin Kliakhandler\n", stdout);
    exit(EXIT_SUCCESS);
  }

  if ((dirname = getcwd(NULL,0)) != NULL) {
    listdir(dirname, argv[1]);
    free(dirname);
  }
  return 0;
};

int listdir(const char* dirname, const char* filename) {
  struct dirent *dp;
  struct stat s;
  DIR *dir;
  char* path;

  if(dir = opendir(dirname)) {
    fchdir(dirfd(dir));
    do
      if ((dp = readdir(dir))
          && (stat(dp->d_name, &s) != -1))
        if (S_ISREG (s.st_mode)
            && (strcasestr(dp->d_name, filename) != NULL)) {
          path = realpath(dp->d_name, NULL);
          puts(path);
          free(path);
        }
        else if (S_ISDIR (s.st_mode)
                 && strcmp(dp->d_name, ".")
                 && strcmp(dp->d_name, ".."))
          listdir(dp->d_name, filename);
    while(dp);
    closedir(dir);
  }

  chdir("..");
  return 0;
};
