#include "./headers.h"

int chown_(int argc, char* argv[])
{
    struct stat file_exist;

    if (argc < 3) {
        printf("Error\n"); //���ڰ� 3�� �ԷµǾ�� �ϴµ� ���� �Էµ� ���.
        return -1;
    }
    if (stat(argv[2], &file_exist) == -1) {
        printf("Can't access to %s\n", argv[2]); //������ �������� ������ ����
        return -1;
    }


    char* k;
    int location;
    k = strchr(argv[1], ':'); // argv[1]���� :�� ã���� �� ��ġ�� �ּҰ� k�� �����.
    location = (int)(k - argv[1]); // ':'�� ��ġ�� �ּҿ��� argv[1]�� ���� �ּ� ���� ���° �ִ��� �� �� ����.
    int length = sizeof(argv[1]) / sizeof(argv[1][0]); //argv[1]�� ũ�� ���ϱ�
    char u_name[length];
    char g_name[length];

    for (int i = 0; i < location; i++) {
        u_name[i] = argv[1][i];
    }
    for (int j = location + 1; j < length; j++) {
        g_name[j - location - 1] = argv[1][j];
    }


    if (k == NULL) {    //:�� ���ٴ� ���̹Ƿ� user�� �����Ѵ�
        //�� ���Ͽ��� ������(user)�� ���� �Է��� �����ڷ� �����Ѵ�.
        if (chown(argv[2], argv[1], -1) == -1)
            printf("Fail");
    }

    else if (location == 0) {  //:�� ã�Ұ� ��� argv[1]�� 0��°��(�Ǿտ�) ��ġ. �� �׷츸 �����Ѵ�.
        //�� ���Ͽ��� �׷��� ���� �Է��� �׷����� �����Ѵ�.
        if (chown(argv[2], -1, g_name) == -1)
            printf("Fail");
    }
    else {   //user�� group ��� ����.
        //�� ���Ͽ��� �����ڿ� �׷��� ��� ���� �Է��Ѵ�� �����Ѵ�.
        if (chown(argv[2], u_name, g_name) == -1)
            printf("Fail");
    }

    return 0;
}
#pragma once
