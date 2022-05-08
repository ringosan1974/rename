#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#define _POSIX_SOURSE

int fileIsBeing(const char *fn);
int dirIsBeing(const char *path, struct stat *stat_buf);
int rename_s(const char *fn, const char *newfn);
char *connectStrInt(const char *p, int num);
int ask(char *p, const char *c);

int main(void){
  DIR* dir;
  struct dirent *ds;
  struct stat stat_buf;
  char path[128]; //ディレクトリのパス
  char new_fn[32];
  int count = 0;

  ask(path, "path");
  dirIsBeing(path, &stat_buf);
  ask(new_fn, "new file name");

  dir = opendir(path);

  chdir(path);  //このプログラムのカレントディレクトリ変更
  while((ds = readdir(dir)) != NULL){
    if(ds->d_name[0] == '.'){ //隠しファイルはrename()しない
      continue;
    }
    rename_s(ds->d_name, connectStrInt(new_fn, count));
    count++;
  }

  closedir(dir);
  return 0;
}

//ファイルにアクセスできるか確かめる
//存在しなければ強制終了
int fileIsBeing(const char *fn) {
  if(access(fn, F_OK) != 0){
    printf("ファイルが存在しません\n");
    exit(1);
  }
  return 0;
}

//ディレクトリにアクセスできるか確かめる
int dirIsBeing(const char *path, struct stat *stat_buf) {
  if(stat(path, stat_buf) != 0){
    printf("そのディレクトリは存在しません\n");
    exit(1);
  }
  return 0;
}

int rename_s(const char *fn, const char *newfn){
  fileIsBeing(fn);
  rename(fn, newfn);
  return 0;
 }

//sprintfして文字列を返す
char *connectStrInt(const char *p, int num){
  char* c;
  sprintf(c, "%s%X", p, num);
  return c;
}

int ask(char *p, const char *c){
  printf("%s : ", c);
  if(scanf("%s", p) == EOF){
    printf("error\n");
    exit(1);
  }else{
    return 0;
  }
}
