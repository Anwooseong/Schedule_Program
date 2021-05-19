#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

typedef struct _Schedule {
    int year;
    int month;
    int day;         //날짜
    int time;        //24시간(ex:밤12시 = 0000, 낮1시 = 1300)
    char content[10000];     //내용
}Schedule;
Schedule p[1000];
void Run();

int main(void) {
    Run();
    return 0;
}

void AddSchedule();//일정관리 데이터 입력
void RemoveSchedule();//일정관리 데이터 삭제
void FindSchedule();//내용 검색
void ListSchedule();//목록 보기
void QuickSort_year(Schedule* p, int left, int right); //년도순 정렬
void setcolor(unsigned short text, unsigned short back)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text | (back << 4));  //배경색은 text와는 다르게 text의 16배로 받는다 (예를 들어 text의 2랑 back의 32는 같은 색깔이다.)
}
int len = 0;
void Run(void) {
    int key;
    int i = 0;
    while (1) {
        setcolor(12, 0);//빨간색
        printf("※일정 관리 프로그램 Tab키 2회 연타시 종료※\n");
        setcolor(11, 0);//시안색(CYAN)
        printf("↑: 일정관리 데이터 입력 ←: 일정관리 데이터 삭제 →: 내용 검색 ↓: 목록 보기 \n");
        setcolor(15, 0);//흰색
        if (key = getch()) {
            key = getch();
            if (key == 72)AddSchedule();
            else if (key == 75)RemoveSchedule();
            else if (key == 77)FindSchedule();
            else if (key == 80)ListSchedule();
            else if (key == 9) {
                printf("Tab키 2회 눌렀으므로 종료합니다\n");
                break;
            }
            else printf("잘못 선택하였습니다.\n");
            QuickSort_year(p, 0, len - 1); //년도만 바꿀수있음
        }
    }
}

int IsAvailNum(int year, int month, int day);//유효한 날짜인지 판별(윤년과 30일 28일 31일 판별)

void AddSchedule() { //일정 추가
    int i;
    for (i = len; i < len + 1; i++) {
        printf("날짜 사이 간격 띄우기(ex:2020 01 28) : ");
        scanf("%d %d %d", &p[i].year, &p[i].month, &p[i].day);
        if (IsAvailNum(p[i].year, p[i].month, p[i].day) == 0)//유효한 번호가 아닐 때
        {
            printf("범위를 벗어났습니다.\n");
            return;
        }
        printf("시간입력(ex:1400) : "); scanf("%d", &p[i].time);
        printf("내용입력 : "); scanf("%s", p[i].content);
    }
    printf("-----------------------------------------------------------------------------\n");

    len++;
}
void RemoveSchedule() {  //그날일정 다 삭제
    int year, month, day;
    printf("삭제할 날짜 입력(주위 : 그 날 일정 다 지워짐) : "); scanf("%d %d %d", &year, &month, &day);
    for (int i = 0; i < len; i++) {
        if (year == p[i].year && month == p[i].month && day == p[i].day) {
            for (int j = i + 1; j < len; j++) {
                p[j] = p[j + 1];
            }
        }
    }
    len--;
    printf("삭제완료\n");
    printf("-----------------------------------------------------------------------------\n\n\n");

}
void FindSchedule() {  //찾고싶은 날의 스케줄
    int year, month, day;
    printf("찾고 싶은 날짜 입력(사이 띄우기)(ex:2020 01 28) : "); scanf("%d %d %d", &year, &month, &day);
    for (int i = 0; i < len; i++) {
        if (year == p[i].year && month == p[i].month && day == p[i].day) {
            printf("%d년 %d월 %d일 %d시간\n내용 : %s\n", p[i].year, p[i].month, p[i].day, p[i].time, p[i].content);
        }
    }
    printf("-----------------------------------------------------------------------------\n\n\n");
}
void ListSchedule() {  //목록보기
    for (int i = 0; i < len; i++) {
        printf("%d년 %d월 %d일 %d시간\n내용 : %s\n", p[i].year, p[i].month, p[i].day, p[i].time, p[i].content);
        if (i != len - 1) {
            if (p[i].year != p[i + 1].year) {  //다른년도분리
                printf("-------------------------------------------다른 년도------------------------------\n");
            }
        }
    }
    printf("-----------------------------------------------------------------------------\n\n\n");
}

int IsAvailNum(int year, int month, int day) {  //윤년판단
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