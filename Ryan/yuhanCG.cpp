#include "yuhanCG.h"

// 보노보노 그리기
void DrawBonobono(HWND hWnd, HDC hdc, BOOL EyeType) {   // EyeType = 0 : 0o0, 1 : >o<
    RECT rect;
    GetClientRect(hWnd, &rect);

    
        // 박스 그리기
        HBRUSH hBrush = CreateSolidBrush(RGB(127, 200, 255)); // 파란색
        SelectObject(hdc, hBrush);
        Ellipse(hdc, 240, 120, 560, 400);
        // 파란 너구리의 입을 그리기 위해 색을 핑크색으로 바꿈
        hBrush = CreateSolidBrush(RGB(255, 150, 255));      // 핑크 맞음
        SelectObject(hdc, hBrush);
        Ellipse(hdc, 380, 270, 420, 330);
        // 눈뜨기 눈감기 구현
        // 눈 그리기                            /// >< 눈감은거 구현해야함
        if (!EyeType)
        {
            // 눈떠
            hBrush = CreateSolidBrush(RGB(0, 0, 0)); // black
            SelectObject(hdc, hBrush);
            Ellipse(hdc, 270, 240, 280, 260);
            Ellipse(hdc, 520, 240, 530, 260);

            hBrush = CreateSolidBrush(RGB(255, 255, 255)); // white
            SelectObject(hdc, hBrush);
            Ellipse(hdc, 272, 242, 278, 250);
            Ellipse(hdc, 522, 242, 528, 250);
        }
        else
        {
            //보노보노 폐사시키는 코드
            //hBrush = CreateSolidBrush(RGB(0, 0, 0)); // black
            //SelectObject(hdc, hBrush);
            //MoveToEx(hdc, 270, 240, NULL);
            //LineTo(hdc, 285, 250);
            //MoveToEx(hdc, 270, 250, NULL);
            //LineTo(hdc, 285, 240);

            //MoveToEx(hdc, 515, 240, NULL);
            //LineTo(hdc, 530, 250);
            //MoveToEx(hdc, 515, 250, NULL);
            //LineTo(hdc, 530, 240);
            hBrush = CreateSolidBrush(RGB(0, 0, 0)); // black
            SelectObject(hdc, hBrush);
            MoveToEx(hdc, 270, 240, NULL);
            LineTo(hdc, 285, 245);
            MoveToEx(hdc, 270, 250, NULL);
            LineTo(hdc, 285, 245);

            MoveToEx(hdc, 515, 245, NULL);
            LineTo(hdc, 530, 240);
            MoveToEx(hdc, 515, 245, NULL);
            LineTo(hdc, 530, 250);

        }
        // 보노보노의 귀여운 주둥이
        hBrush = CreateSolidBrush(RGB(255, 255, 255)); // white
        SelectObject(hdc, hBrush);
        Ellipse(hdc, 350, 255, 400, 300);
        Ellipse(hdc, 400, 255, 450, 300);
        // 수염
        hBrush = CreateSolidBrush(RGB(0, 0, 0)); // black
        SelectObject(hdc, hBrush);
        MoveToEx(hdc, 330, 260, NULL);      // 시작점 찍기
        LineTo(hdc, 370, 270);              // 끝점 찍고 줄 잇기

        MoveToEx(hdc, 330, 290, NULL);
        LineTo(hdc, 370, 280);

        MoveToEx(hdc, 430, 270, NULL);
        LineTo(hdc, 470, 260);

        MoveToEx(hdc, 430, 280, NULL);
        LineTo(hdc, 470, 290);
        // 노즈
        hBrush = CreateSolidBrush(RGB(0, 0, 0)); // black
        SelectObject(hdc, hBrush);
        Ellipse(hdc, 380, 240, 420, 275);

        //DeleteObject(hBrush);
    }

// made in china 짭라이언
void DrawRyan(HWND hWnd, HDC hdc, int left, int top, int right, int bottom) {
    RECT rect;
    GetClientRect(hWnd, &rect);

    // 카카오의 들짐승
        int a, b, c, d;
        a = left;
        b = top;
        c = right;
        d = bottom;
        // 거꾸리안되게
        if (left > right) {
            a = left;
            left = right;
            right = a;
        }
        if (top > bottom) {
            b = top;
            top = bottom;
            bottom = b;
        }
        // 드로잉 영역 밖에서 안그려지게
        if (left != 0 && left <= 24) {
            left = 24;
        }
        if (top != 0 && top <= 104) {
            top = 104;
        }
        if (right >= 768) {
            right = 768;
        }
        if (bottom >= 440) {
            bottom = 440;
        }
        POINT center;
        center.x = (right + left) / 2;
        center.y = (bottom + top) / 2;

        int nwidth = (right - left) / 8;
        int nheight = (bottom - top) / 8;
        // 라이언 귀
        HBRUSH hBrush = CreateSolidBrush(RGB(255, 200, 15));    // 주황색
        SelectObject(hdc, hBrush);

        Ellipse(hdc, left - nwidth * 0.7, top - nheight * 0.7, left + nwidth * 2.2, top + nheight * 2.2);
        Ellipse(hdc, right - nwidth * 2.2, top - nheight * 0.7, right + nwidth * 0.7, top + nheight * 2.2);
        // 라이언 몸체
        SelectObject(hdc, hBrush);
        Ellipse(hdc, left, top, right, bottom);
        //Ellipse(hdc, 285, 140, 515, 360);

        // 라이언 눈
        hBrush = CreateSolidBrush(RGB(0, 0, 0));           // black
        SelectObject(hdc, hBrush);
        int eye_width = (right - left) / 3;
        int eye_height = (bottom - top) / 3;
        int eye_width_size = eye_width / 10;
        int eye_height_size = eye_height / 10;
        Ellipse(hdc, left + eye_width * 1.1 - eye_width_size * 2,
            top + eye_height + eye_height_size * 1,
            left + eye_width * 1.1 - eye_width_size * 1,
            top + eye_height + eye_height_size * 3);
        Ellipse(hdc, right - eye_width * 1.1 + eye_width_size * 2,
            top + eye_height + eye_height_size * 1,
            right - eye_width * 1.1 + eye_width_size * 3,
            top + eye_height + eye_height_size * 3);
        // 라이언 눈썹 줄짝대기
        SelectObject(hdc, hBrush);
        //좌측 눈썹
        MoveToEx(hdc, left + eye_width * 1.1 - eye_width_size * 3,
            top + eye_height + eye_height_size * 0, NULL);
        LineTo(hdc, left + eye_width * 1.1 - eye_width_size * 0, top + eye_height + eye_height_size * 0);

        MoveToEx(hdc, left + eye_width * 1.1 - eye_width_size * 3,
            top + eye_height + eye_height_size * 0, NULL);
        LineTo(hdc, left + eye_width * 1.1 - eye_width_size * 0, top + eye_height + eye_height_size * 0);

        MoveToEx(hdc, left + eye_width * 1.1 - eye_width_size * 3,
            top + eye_height + eye_height_size * 0.4, NULL);
        LineTo(hdc, left + eye_width * 1.1 - eye_width_size * 0, top + eye_height + eye_height_size * 0.4);

        MoveToEx(hdc, left + eye_width * 1.1 - eye_width_size * 3,
            top + eye_height + eye_height_size * 0.4, NULL);
        LineTo(hdc, left + eye_width * 1.1 - eye_width_size * 0, top + eye_height + eye_height_size * 0.4);

        //----- 우측 눈썹
        MoveToEx(hdc, right - eye_width * 1.1 + eye_width_size * 3,
            top + eye_height + eye_height_size * 0, NULL);
        LineTo(hdc, right - eye_width * 1.1 - eye_width_size * 0, top + eye_height + eye_height_size * 0);

        MoveToEx(hdc, right - eye_width * 1.1 + eye_width_size * 3,
            top + eye_height + eye_height_size * 0, NULL);
        LineTo(hdc, right - eye_width * 1.1 - eye_width_size * 0, top + eye_height + eye_height_size * 0);

        MoveToEx(hdc, right - eye_width * 1.1 + eye_width_size * 3,
            top + eye_height + eye_height_size * 0.4, NULL);
        LineTo(hdc, right - eye_width * 1.1 - eye_width_size * 0, top + eye_height + eye_height_size * 0.4);

        MoveToEx(hdc, right - eye_width * 1.1 + eye_width_size * 3,
            top + eye_height + eye_height_size * 0.4, NULL);
        LineTo(hdc, right - eye_width * 1.1 - eye_width_size * 0, top + eye_height + eye_height_size * 0.4);
        // 라이언의 코
        int nose_width = (right - left) / 7;
        int nose_height = (bottom - top) / 7;
        hBrush = CreateSolidBrush(RGB(255, 255, 255)); // white
        SelectObject(hdc, hBrush);
        Ellipse(hdc, center.x - nose_width, center.y, center.x, center.y + nose_height);
        Ellipse(hdc, center.x, center.y, center.x + nose_width, center.y + nose_height);


        //DeleteObject(hBrush);
    }