#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#define _POSIX_SOURSE

int file_rename(const char* fn, const char* nfn);
char* connect_str_int(const char* c1, int num);
int align_scanf_s(char* cp, const char* c);

int main(void){
  DIR* dir;
  struct dirent *ds;
  char path[128]; //DirectoryのPath
  char new_fn[32];
  int fnum_count = 0;
  align_scanf_s(path, "path");
  align_scanf_s(new_fn, "new file name");
  dir = opendir(path);
  chdir(path);  //カレントディレクトリ変更
  while((ds = readdir(dir)) != NULL){ //すべてのfileを読み込む
    if(ds->d_name[0] == '.'){ //隠しファイルはrename()しない
      continue;
    }
    file_rename(ds->d_name, connect_str_int(new_fn, fnum_count));
    fnum_count++;
  }
  closedir(dir);
  return 0;
}

//rename()安全版
int file_rename(const char* fn, const char* nfn){
  if(access(nfn, F_OK) != 0){
    if(rename(fn, nfn) != 0){
      return 1;
    }
  }else{
    return 0;
  }
}

//文字列と数値を連結
char* connect_str_int(const char* c1, int num){
  char* c;
  sprintf(c, "%s%X", c1, num);
  return c;
}

//〇〇 : の形でscanf
int align_scanf_s(char* cp, const char* c){
  printf("%s : ", c);
  if(scanf("%s", cp) == EOF){
    printf("error\n");
    return 1;
  }else{
    return 0;
  }
}
