#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

int rmdirs(const char *path) {
     DIR * dir_ptr = NULL;
     struct dirent *file = NULL;
     struct stat buf;
     char filename[1024]; /* ����� ���� ���丮������ DIR *�� return �޽��ϴ�. */
     if((dir_ptr = opendir(path)) == NULL)
     { /* path�� ���丮�� �ƴ϶�� �����ϰ� �����մϴ�. */
        return unlink(path);
     }
      /* ���丮�� ó������ ���� �Ǵ� ���丮���� ������� �Ѱ��� �н��ϴ�. */
    while((file = readdir(dir_ptr)) != NULL) {
        // readdir ������ ���ϸ� �߿� ���� ���丮�� ��Ÿ�״� . �� ���ԵǾ� �����Ƿ� // ���� �ݺ��� ������ �������� ���ϸ��� . �̸� skip �ؾ� ��
        if(strcmp(file->d_name, ".") == 0 || strcmp(file->d_name, "..") == 0) {
            continue;
        }
        sprintf(filename, "%s/%s", path, file->d_name);
        /* ������ �Ӽ�(������ ����, ũ��, ����/���� �ð� ���� ��� ���Ͽ� */
        if(stat(filename, &buf) == -1)
        {
            continue;
        }
        if(S_ISDIR(buf.st_mode)) {
            // �˻��� �̸��� �Ӽ��� ���丮�̸� /* �˻��� ������ directory�̸� ���ȣ��� ���� ���丮�� �ٽ� �˻� */
            if(rmdirs(filename) == -1) {
                return -1;
            }
        }
        else if(S_ISREG(buf.st_mode)) {
            // �Ϲ����� �Ǵ� symbolic link �̸�
            if(unlink(filename) == -1) {
                return -1;
            }
        }
    }
    closedir(dir_ptr);
    return rmdir(path);
 }



void rm(char* (*argv)[])
{
    DIR *dir;
    struct dirent *entry;
    int rmResult, checked;

    dir = opendir(".");
    if (strcmp((*argv)[1], "-r") == 0){
        rmdirs((*argv)[2]);

    }
    else if (strcmp((*argv)[1], "-f") == 0){
        unlink((*argv)[2]);
    }
    else if (strcmp((*argv)[1], "-rf") == 0){
        rmdirs((*argv)[2]);
    }
    else {
        while((entry = readdir(dir))!=NULL)
        {
            if(strcmp(entry->d_name, (*argv)[1]) == 0){
                //if(entry->d_type == DT_DIR){
                    rmResult = rmdir((*argv)[1]);
                    if (rmResult == -1) {
                        perror("cannot remove this directory");
                    }
                }
                else {
                    unlink((*argv)[1]);
                //}
                return;
            }
        }
        printf("cannot remove: undefined\n");

    closedir(dir);
}
}
