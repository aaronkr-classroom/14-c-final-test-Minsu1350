// linked_list.c (slide 62)
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>


struct People {
    char name[20];
    float Korean;
    float English;
    float Math;
};
typedef struct People Person;

typedef struct Node {
    Person person;         
    struct Node* p_next; // 다음 노드를 가리킬 포인터
} Node;

void AddStudent(Node** pp_head, Node** pp_tail, Person data) {
    if (*pp_head != NULL) {
        (*pp_tail)->p_next = (Node*)malloc(sizeof(Node)); // 새 노드를 할당
        *pp_tail = (*pp_tail)->p_next; // p_tail(*pp_tail)에 새 노드의 주소 값을 저장
    }
    else {
        // *p_head 값이 NULL이라서 첫 노드가 추가됨. p_head 값에 직접 대입함
        *pp_head = (Node*)malloc(sizeof(Node));
        *pp_tail = *pp_head; // 새 노드의 주소 값을 p_tail(*pp_tail)에 저장
    }
    (*pp_tail)->person = data; // 새 노드의 number에 data 값을 저장
    (*pp_tail)->p_next = NULL; // 다음 노드가 없음을 명시함
}

int main(void) {
    // 노드의 시작과 끝을 기억할 포인터
    Node* p_head = NULL, * p_tail = NULL, * p;
    int temp; 

    // 무한 루프: 중간에 5를 누르면 종료함
    while (1) {
        printf("[Menu]\n1.dat 파일에서 데이터 읽기\n2.추가 학생 정보 입력\n3.dat 파일 저장\n4.성적 확인(평균 계산 등)\n5.종료");
        printf("\n----------------------------------");
        printf("\n선택(1~5): ");
        scanf_s("%d", &temp);

        if (temp == 5) break;

        if (temp == 1) {
            FILE* fp;
            fopen_s(&fp, "students.dat", "rb");
            if (fp == NULL) {
                printf("students.dat 파일을 열 수 없습니다.\n\n");
            }
            else {
                Person student;
                while (fread(&student, sizeof(Person), 1, fp) == 1) {
                    AddStudent(&p_head, &p_tail, student);
                }
                fclose(fp);
                printf("students.dat 파일에서 데이터를 읽었습니다.\n\n");
            }
        }
        else if (temp == 2) {
            Person student;
            printf("이름: "); scanf_s("%s", student.name, (unsigned)_countof(student.name));
            printf("국어 점수: "); scanf_s("%f", &student.Korean);
            printf("영어 점수: "); scanf_s("%f", &student.English);
            printf("수학 점수: "); scanf_s("%f", &student.Math);
            AddStudent(&p_head, &p_tail, student);
        }
        else if (temp == 3) {
            FILE* fp;
            fopen_s(&fp, "students.dat", "wb");
            if (fp == NULL) {
                printf("students.dat 파일을 저장할 수 없습니다.\n\n");
            }
            else {
                p = p_head;
                while (p) {
                    fwrite(&(p->person), sizeof(Person), 1, fp);
                    p = p->p_next;
                }
                fclose(fp);
                printf("students.dat 파일에 저장했습니다.\n\n");
            }
        }
        else if (temp == 4) {
            p = p_head;
            int count = 0;
            float sumKorean = 0, sumEnglish = 0, sumMath = 0;
            while (p) {
                printf("%s: 국어 %.1f, 영어 %.1f, 수학 %.1f\n",
                    p->person.name, p->person.Korean, p->person.English, p->person.Math);
                sumKorean += p->person.Korean;
                sumEnglish += p->person.English;
                sumMath += p->person.Math;
                count++;
                p = p->p_next; // 다음 노드로 이동
            }
            if (count > 0) {
                printf("평균은 국어 %.1f, 영어 %.1f, 수학 %.1f 입니다.\n\n",
                    sumKorean / count, 
                    sumEnglish / count, 
                    sumMath / count);
            }
        }
    }
    // 사용한 모든 노드를 삭제합니다. 
    while (p_head != NULL) {
        p = p_head; // 현재 노드를 삭제하기 위해 p 변수에 노드 주소 값을 저장
        p_head = p_head->p_next; //시작 위치를 다음 노드로 이동
        free(p); //기억했던 주소를 사용하여 노드를 삭제함
    }
    p_tail = p_head; // 반복문을 나오면 p_head 값은 NULL. p_tail 값도 NULL로 변경

    return 0;
}