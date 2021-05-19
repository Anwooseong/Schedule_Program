#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

typedef struct _Schedule {
    int year;
    int month;
    int day;         //��¥
    int time;        //24�ð�(ex:��12�� = 0000, ��1�� = 1300)
    char content[10000];     //����
}Schedule;
Schedule p[1000];
void Run();

int main(void) {
    Run();
    return 0;
}

void AddSchedule();//�������� ������ �Է�
void RemoveSchedule();//�������� ������ ����
void FindSchedule();//���� �˻�
void ListSchedule();//��� ����
void QuickSort_year(Schedule* p, int left, int right); //�⵵�� ����
void setcolor(unsigned short text, unsigned short back)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text | (back << 4));  //������ text�ʹ� �ٸ��� text�� 16��� �޴´� (���� ��� text�� 2�� back�� 32�� ���� �����̴�.)
}
int len = 0;
void Run(void) {
    int key;
    int i = 0;
    while (1) {
        setcolor(12, 0);//������
        printf("������ ���� ���α׷� TabŰ 2ȸ ��Ÿ�� �����\n");
        setcolor(11, 0);//�þȻ�(CYAN)
        printf("��: �������� ������ �Է� ��: �������� ������ ���� ��: ���� �˻� ��: ��� ���� \n");
        setcolor(15, 0);//���
        if (key = getch()) {
            key = getch();
            if (key == 72)AddSchedule();
            else if (key == 75)RemoveSchedule();
            else if (key == 77)FindSchedule();
            else if (key == 80)ListSchedule();
            else if (key == 9) {
                printf("TabŰ 2ȸ �������Ƿ� �����մϴ�\n");
                break;
            }
            else printf("�߸� �����Ͽ����ϴ�.\n");
            QuickSort_year(p, 0, len - 1); //�⵵�� �ٲܼ�����
        }
    }
}

int IsAvailNum(int year, int month, int day);//��ȿ�� ��¥���� �Ǻ�(����� 30�� 28�� 31�� �Ǻ�)

void AddSchedule() { //���� �߰�
    int i;
    for (i = len; i < len + 1; i++) {
        printf("��¥ ���� ���� ����(ex:2020 01 28) : ");
        scanf("%d %d %d", &p[i].year, &p[i].month, &p[i].day);
        if (IsAvailNum(p[i].year, p[i].month, p[i].day) == 0)//��ȿ�� ��ȣ�� �ƴ� ��
        {
            printf("������ ������ϴ�.\n");
            return;
        }
        printf("�ð��Է�(ex:1400) : "); scanf("%d", &p[i].time);
        printf("�����Է� : "); scanf("%s", p[i].content);
    }
    printf("-----------------------------------------------------------------------------\n");

    len++;
}
void RemoveSchedule() {  //�׳����� �� ����
    int year, month, day;
    printf("������ ��¥ �Է�(���� : �� �� ���� �� ������) : "); scanf("%d %d %d", &year, &month, &day);
    for (int i = 0; i < len; i++) {
        if (year == p[i].year && month == p[i].month && day == p[i].day) {
            for (int j = i + 1; j < len; j++) {
                p[j] = p[j + 1];
            }
        }
    }
    len--;
    printf("�����Ϸ�\n");
    printf("-----------------------------------------------------------------------------\n\n\n");

}
void FindSchedule() {  //ã����� ���� ������
    int year, month, day;
    printf("ã�� ���� ��¥ �Է�(���� ����)(ex:2020 01 28) : "); scanf("%d %d %d", &year, &month, &day);
    for (int i = 0; i < len; i++) {
        if (year == p[i].year && month == p[i].month && day == p[i].day) {
            printf("%d�� %d�� %d�� %d�ð�\n���� : %s\n", p[i].year, p[i].month, p[i].day, p[i].time, p[i].content);
        }
    }
    printf("-----------------------------------------------------------------------------\n\n\n");
}
void ListSchedule() {  //��Ϻ���
    for (int i = 0; i < len; i++) {
        printf("%d�� %d�� %d�� %d�ð�\n���� : %s\n", p[i].year, p[i].month, p[i].day, p[i].time, p[i].content);
        if (i != len - 1) {
            if (p[i].year != p[i + 1].year) {  //�ٸ��⵵�и�
                printf("-------------------------------------------�ٸ� �⵵------------------------------\n");
            }
        }
    }
    printf("-----------------------------------------------------------------------------\n\n\n");
}

int IsAvailNum(int year, int month, int day) {  //�����Ǵ�
    if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)) {
        if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
            if ((day > 0) && (day <= 31)) return 1;
            return 0;
        }
        else if (month == 4 || month == 6 || month == 9 || month == 11) {
            if ((day > 0) && (day <= 30)) return 1;
            return 0;
        }
        else if (month == 2) {
            if ((day > 0) && (day <= 29)) return 1;
            return 0;
        }
        else return 0;
    }
    else {
        if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
            if ((day > 0) && (day <= 31)) return 1;
            return 0;
        }
        else if (month == 4 || month == 6 || month == 9 || month == 11) {
            if ((day > 0) && (day <= 30)) return 1;
            return 0;
        }
        else if (month == 2) {
            if ((day > 0) && (day <= 28)) return 1;
            return 0;
        }
        else return 0;
    }
}
void SWAP(Schedule* p, int a, int b) {
    Schedule temp;
    temp = p[a];
    p[a] = p[b];
    p[b] = temp;
}

void QuickSort_year(Schedule* p, int left, int right) {
    int pivot, i, j, temp = 0;
    if (left < right) {
        i = left; j = right + 1;
        pivot = p[left].year;
        do {
            do i++;
            while (p[i].year < pivot);
            do j--;
            while (p[j].year > pivot);
            if (i < j) {
                temp = p[i].year;
                p[i].year = p[j].year;
                p[j].year = temp;
                temp = 0;
            }
        } while (i < j);
        temp = p[left].year;
        p[left].year = p[j].year;
        p[j].year = temp;
        QuickSort_year(p, left, j - 1);
        QuickSort_year(p, j + 1, right);
    }
}