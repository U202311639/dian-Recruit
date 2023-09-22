#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int NUM;
int NUM1;
int size = 10;
int table[10] = { 0 };
int waiting[10] = { 0 };
int arriving[10] = { 0 };

int min(int arr[], int size);
int max(int arr[], int size);
int judge(int elevator_now, int min_passenger, int max_passenger, int ret1);
//判断电梯运行方向
int sum(int arr1[], int size);
//通过sum函数来判断是否有人在等电梯
void suspend(int passenger[], int elevator_now, int elevator_target[], int staging[], int size);
//电梯在楼层停留时的操作
void add(int arr[], int x, int size);
//添加电梯的目标楼层
void element_remove(int arr[], int size, int x);
//乘客离开电梯，删除该目的楼层
void keyfloor(int elevator_now, int TIME);
//关键楼层时，用来判断是否打印数据
int start(int elevator_now, int size);
int quality(int elevator_now, int arr[]);

int main() {
    int elevator_now;
    int passenger[10] = { 0 };
    int elevator_target[11] = { 0 };
    int staging[10] = { 0 };
    int SUM = 0;
    int TIME = 0;
    int NUMBER = 0;

    printf("Please enter the number of passengers:");
    scanf("%d", &NUMBER);
    printf("Please enter the floor where the elevator is:");
    scanf("%d", &elevator_now);
    printf("Please enter your floor where you are and where you want to go: \n");

    int i = 0;
    int x, y;
    while (i < NUMBER) {
        scanf("%d %d", &x, &y);
        table[i] = x;
        passenger[x] = 1;
        waiting[i] = x;
        staging[x] = y;
        i++;
    }

    int min_passenger;
    int max_passenger;
    int ret1 = start(elevator_now, size);
    SUM = sum(table, NUMBER);
    NUM = 0;
    NUM1 = 0;
    printf("%d %d %d\n", elevator_now, TIME, NUM);

    while (SUM != 0) {
        min_passenger = min(table, size);
        max_passenger = max(table, size);

        int direction = judge(elevator_now, min_passenger, max_passenger, ret1);

        if (direction == 1) {
            while (elevator_now < max_passenger) {
                elevator_now++;
                suspend(passenger, elevator_now, elevator_target, staging, size);
                TIME++;
                keyfloor(elevator_now, TIME);
            }
        }
        else if (direction == -1) {
            while (elevator_now > min_passenger) {
                elevator_now--;
                suspend(passenger, elevator_now, elevator_target, staging, size);
                TIME++;
                keyfloor(elevator_now, TIME);
            }
        }
        else if (direction == 0) {
            passenger[elevator_now] = 0;
            elevator_target[staging[elevator_now]] = 1;
            add(arriving, staging[elevator_now], size);
            add(table, staging[elevator_now], size);
            element_remove(table, size, elevator_now);
            NUM++;
            printf("%d %d %d\n", elevator_now, TIME, NUM);
            ret1 = 1;
        }
        SUM = sum(table, NUMBER);
    }
    return 0;
}

int min(int arr[], int size) {
    int min = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] < min && arr[i]>0) {
            min = arr[i];
        }
    }

    return min;
}

int max(int arr[], int size) {
    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    return max;
}

int judge(int elevator_now, int min_passenger, int max_passenger, int ret1) {
    int ret = 2;
    if (elevator_now > min_passenger && min_passenger != 0) {
        ret = -1;
    }
    else if (elevator_now < max_passenger) {
        ret = 1;
    }

    if (ret1 == 0) {
        ret = 0;
    }
    return ret;
}

int sum(int arr1[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum = sum + arr1[i];
    }
    return sum;
}

void suspend(int passenger[], int elevator_now, int elevator_target[], int staging[], int size) {
    if (elevator_target[elevator_now] == 1) {
        int qual = quality(elevator_now, arriving);
        NUM = NUM - qual;
        element_remove(arriving, size, elevator_now);
        elevator_target[elevator_now] = 0;
    }

    if (passenger[elevator_now] == 1) {
        int qual = quality(elevator_now, waiting);
        NUM = NUM + qual;
        element_remove(waiting, size, elevator_now);
        passenger[elevator_now] = 0;
        elevator_target[staging[elevator_now]] = 1;
        add(arriving, staging[elevator_now], size);
        add(table, staging[elevator_now], size);
    }

    element_remove(table, size, elevator_now);
}

void add(int arr[], int x, int size) {
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == 0)
        {
            arr[i] = x;
            break;
        }
    }

}

void element_remove(int arr[], int size, int x) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == x) {
            arr[i] = 0;
        }
    }
}

void keyfloor(int elevator_now, int TIME) {
    if (NUM != NUM1) {
        printf("%d %d %d\n", elevator_now, TIME, NUM);
    }
    NUM1 = NUM;
}

int start(int elevator_now, int size) {
    int ret1 = 1;
    for (int i = 0; i < size; i++) {
        if (table[i] == elevator_now)
            ret1 = 0;
    }
    return ret1;
}

int quality(int elevator_now, int arr[]) {
    int qual = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] == elevator_now)
            qual++;
    }
    return qual;
}