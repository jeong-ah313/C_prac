#include <Windows.h>
#include <stdio.h>
#include <time.h>

#define BALL_SIZE 20     // 볼의 크기 상수를 정의
#define MOVE_STEP 5      // 볼의 이동 간격 상수를 정의

#define BALL_MAX 50      //볼의 최대 개수

int main(void)
{


    int i;
    int x[BALL_MAX];
    int y[BALL_MAX];
    int dx[BALL_MAX];
    int dy[BALL_MAX];

    for (i = 0; i < BALL_MAX;i++)
    {
        dx[i] = +5;
        dy[i] = +5;
    }




    HWND    hwnd = GetForegroundWindow(); // 현재 윈도우의  핸들을 구한다. 
    HDC hdc = GetWindowDC(hwnd);          // 윈도우의 디바이스 컨테스트(Device context)의 핸들을 구하여 윈도우에 접근한다. 

     // 배경을 흰색으로 설정
    SelectObject(hdc, CreatePen(PS_SOLID, 1, RGB(255, 255, 255)));
    SelectObject(hdc, CreateSolidBrush(RGB(255, 255, 255)));
    Rectangle(hdc, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));

    // 그리는 펜의 테두리 색은 파란색, 채우는 색은 흰색으로 설정
    SelectObject(hdc, CreatePen(PS_SOLID, 3, RGB(0, 0, 255)));
    SelectObject(hdc, CreateSolidBrush(RGB(255, 255, 255)));

    // 파란색 테두리를 갖는 사각형을 그린다. 바탕색은 흰색
    Rectangle(hdc, 30, 40, 500 + BALL_SIZE + MOVE_STEP, 400 + BALL_SIZE + MOVE_STEP);

    TextOut(hdc, 220, 450, L"50 Ball Simulation ", 15); // 화면 아래에 문자열 출력

    for (i = 0;i < BALL_MAX;i++)

    {

        x[i] = rand() % (500 + 1 - 30) + 30;
        y[i] = rand() % (400 + 1 - 40) + 40;
    }

    while (1)
    {

        // 그리는 펜의 테두리 색은 파란색, 채우는 색은 빨강색으로 설정
        SelectObject(hdc, CreatePen(PS_SOLID, 3, RGB(0, 0, 255)));
        SelectObject(hdc, CreateSolidBrush(RGB(255, 0, 0)));

        // 50개의 볼을 그린다. 
        for (i = 0;i < BALL_MAX;i++)
        {
            // 원을 그린다.
            Ellipse(hdc, x[i], y[i], x[i] + BALL_SIZE, y[i] + BALL_SIZE);
        }

        Sleep(40); // 시간 지연

  // 그리는 펜의 색은 흰색, 채우는 색은 흰색
        SelectObject(hdc, CreatePen(PS_SOLID, 3, RGB(255, 255, 255)));
        SelectObject(hdc, CreateSolidBrush(RGB(255, 255, 255)));

        // 50개의 볼을 그리고 다음 좌표 값으로 조정한다.
        for (i = 0; i < BALL_MAX; i++)
        {
            // 바탕색(흰색)으로 원을 그려서 원을 지운다.
            Ellipse(hdc, x[i], y[i], x[i] + BALL_SIZE, y[i] + BALL_SIZE);

            // 이동하는 위치의 x,y 좌표 값으로 변경하기 위해 좌표 값을 dx,dy만큼 이동
            x[i] += dx[i];
            y[i] += dy[i];

            if (x[i] >= 500) dx[i] = -MOVE_STEP;               // x 좌표 값의 우측 경계를 만난 경우 dx는 감소하는 방향으로
            if (x[i] <= 30 + MOVE_STEP) dx[i] = +MOVE_STEP;    // x 좌표 값의 좌측 경계를 만난 경우 dx는 증가하는 방향으로
            if (y[i] >= 400) dy[i] = -MOVE_STEP;               // y 좌표 값이 아래 경계를 만난 경우 dy는 감소하는 방향으로
            if (y[i] <= (40 + MOVE_STEP)) dy[i] = +MOVE_STEP;  // y 좌표 값이 위측 경계를 만난 경우 dy는 증가하는 방향으로
        }

    } //while

    return 0;
}