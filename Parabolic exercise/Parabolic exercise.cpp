#include <Windows.h>
#include <stdio.h>
#include <math.h>

#define BALL_SIZE 12      // 볼의 크기 상수를 정의
#define MOVE_STEP 3     // 볼의 이동 간격 상수를 정의
#define X_END     800     // x 좌표의 우측 경계 값 설정
#define Y_END     400     // y 좌표의 하단 경계 값 설정
#define PI 3.141592654   // PI 상수 값
#define G         9.8        // 중력 가속도 상수 값

int main(void)
{
    int x;       // 볼의 x,y 좌표
    int y;

    int v0 = 80;      // 초기 발사 속도 값
    int degree;     // 포물선의 발사 각도

    double t = 0.0;   // 시간 값
    double dt = 0.1;  // 시간 증가 값
    TCHAR str[50];  // 출력할 문자열을 저장할 배열

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
    Rectangle(hdc, 30, 40, 800 + BALL_SIZE + MOVE_STEP, 400 + BALL_SIZE + MOVE_STEP);

    // 발사대를 그린다. 
    Rectangle(hdc, 50, 380, 55, 410);

    TextOut(hdc, 350, 450, L"포물선 운동 시뮬레이션", 6); // 화면 아래에 문자열 출력

     // 초기 속도 값을 윈도우 창 하단에 출력한다. 
    wsprintf(str, TEXT("초기 속도 값=%d"), v0); // 속도 값을 출력하기 위해 문자열로 변환
    TextOut(hdc, 50, 440, str, lstrlen(str));  // 속도 값을 화면에 출력

    for (degree = 0; degree <= 90; degree += 5)  //포물선의 각도 값을 5도씩 증가시키며 계산
    {
        t = 0; // 시작 시간 값을 0으로 설정

        while (1)
        {
            // 그리는 펜의 테두리 색은 파란색, 채우는 색은 빨강색으로 설정
            SelectObject(hdc, CreatePen(PS_SOLID, 3, RGB(0, 0, 255)));
            SelectObject(hdc, CreateSolidBrush(RGB(255, 0, 0)));

            // 포물선 운동의 X,Y 좌표 계산
            x = 50 + (int)(v0 * cos((degree)*PI / 180) * t);                // x좌표의 계산
            y = 400 - (int)(v0 * sin((degree)*PI / 180) * t - 1.0 / 2.0 * G * t * t); // y좌표의 계산

             // 볼을 그린다. 
            Ellipse(hdc, x, y, x + BALL_SIZE, y + BALL_SIZE);

            Sleep(30); // 시간 지연

            // 그리는 펜의 색은 흰색, 채우는 색은 흰색
            SelectObject(hdc, CreatePen(PS_SOLID, 3, RGB(255, 255, 255)));
            SelectObject(hdc, CreateSolidBrush(RGB(255, 255, 255)));

            // 바탕색(흰색)으로 원을 그려서 원을 지운다. 
            Ellipse(hdc, x, y, x + BALL_SIZE, y + BALL_SIZE);

            // 그리는 펜의 색은 빨강색, 채우는 색은 흰색
            SelectObject(hdc, CreatePen(PS_SOLID, 3, RGB(255, 0, 0)));
            SelectObject(hdc, CreateSolidBrush(RGB(255, 255, 255)));

            // 작은 원으로 궤적을 그려둔다.  
            Ellipse(hdc, x, y, x + 1, y + 1);

            // 각도 값을 윈도우 창 하단에 출력한다. 
            wsprintf(str, TEXT(" %3d도"), degree);    // 각도 값을 출력하기 위해 문자열로 변환
            TextOut(hdc, x, 420, str, lstrlen(str)); // 각도 값을 화면에 출력

            // 시간 값을 증가
            t += dt;

            // 볼의 좌표가 x,y 한계 값에 도달했는지 검사하고 도달했으면 계산 중단
            if (x >= X_END) break; // 볼의 x좌표 값이 800을 넘어 가는 경우 중단
            if (y > Y_END) break; // 볼의 y좌표 값이 400을 넘어 가는 경우 중단 
        } //while
    }//for
    return 0;
}