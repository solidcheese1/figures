// drawingFigures.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "Figures.h"

//BOOL  PlotRect(HDC hDC, HPEN hPen, COORD BGN, COORD END);
//BOOL  PlotCirc(HDC hDC, HPEN hPen, COORD BGN, COORD END);
//BOOL PlotTriangle(HDC hDC, HPEN hPen, COORD firstPoint, COORD secondPoint, COORD thirdPoint);
//COORD setCordScale(COORD POS, RECT pRECT);

int main()
{
    HWND hWnd = GetForegroundWindow();
    HPEN    RPEN = getPen(PS_SOLID, 2, RED);
    HPEN    GPEN = getPen(PS_SOLID, 2, GRN);
    HPEN    BPEN = getPen(PS_SOLID, 2, BLU);
    HPEN    WPEN = getPen(PS_SOLID, 3, WHT);
    HPEN    BLACKPEN = getPen(PS_SOLID, 3, BLK);
    RECT    pRECT = { 0 };
    COORD   POS = { 0 };
    //COORD   BGN = setCordScale(POS, pRECT);
    GetWindowRect(hWnd, &pRECT);
    HDC hDC = GetWindowDC(hWnd);
    if (hDC)
    {
        SetBkMode(hDC, TRANSPARENT);

        HBRUSH hbrush1 = CreateSolidBrush(RGB(0, 0, 0));
        SelectObject(hDC, hbrush1);
        Rectangle(hDC, BeginAreaDefined.X, BeginAreaDefined.Y, EndAreaDefined.X, EndAreaDefined.Y);
        HBRUSH hbrush2 = CreateSolidBrush(RGB(255, 255, 255));
        SelectObject(hDC, hbrush2);
        

        Rectangles rectangle2(100, 200);
        rectangle2.plotFigure(hDC);
        rectangle2.move(hDC,100, 10);
        rectangle2.turnOnAngleFromStartPosition(hDC, 15);
        
        Ellipses ellipse(200,100);
        ellipse.plotFigure(hDC);
        ellipse.move(hDC,500,500);
        ellipse.clearFigure(hDC);
        ellipse.plotFigure(hDC);
        ellipse.move(hDC, 50, 50);
        ellipse.clearFigure(hDC);
        Rectangles rectangle(100,200);
        rectangle.plotFigure(hDC);
        rectangle.move(hDC,100,180);
        rectangle.resize(hDC,2.0);
    }
    system("pause");
    return 0;
}

//BOOL PlotRect(HDC hDC, HPEN hPen, COORD BGN, COORD END)
//{
//    SelectObject(hDC, hPen);
//    return Rectangle(hDC, BGN.X, BGN.Y, END.X, END.Y);
//}

//BOOL  PlotCirc(HDC hDC, HPEN hPen, COORD BGN, COORD END)
//{
//    SelectObject(hDC, hPen);
//    return Ellipse(hDC, BGN.X, BGN.Y, END.X, END.Y);
//}

//COORD setCordScale(COORD POS, RECT pRECT)
//{
//    if (POS.X == 0)
//        POS.X = 1;
//    if (POS.Y == 0)
//        POS.Y = 1;
//
//    int nROWS = 25;
//    int nCOLS = 80;
//
//    double CX = (pRECT.right - pRECT.left) / nCOLS;
//    double CY = (pRECT.bottom - pRECT.top) / nROWS;
//
//    POS.X *= CX;
//    POS.Y *= CY;
//
//    int xBORDER = GetSystemMetrics(SM_CXBORDER);
//    int yBORDER = GetSystemMetrics(SM_CYMENU);
//    int xDRAG = GetSystemMetrics(SM_CXDRAG); 
//    int yDRAG = GetSystemMetrics(SM_CYDRAG); 
//
//    POS.X += xBORDER + xDRAG;
//    POS.Y += yBORDER + yDRAG;
//    POS.X = 100;
//    POS.Y = 100;
//    return POS;
//}

//BOOL PlotTriangle(HDC hDC, HPEN hPen, COORD firstPoint, COORD secondPoint, COORD thirdPoint)
//{
//    SelectObject(hDC, hPen);
//    MoveToEx(hDC, firstPoint.X, firstPoint.Y, NULL);
//    LineTo(hDC, secondPoint.X, secondPoint.Y);
//    MoveToEx(hDC, secondPoint.X, secondPoint.Y, NULL);
//    LineTo(hDC, thirdPoint.X, thirdPoint.Y);
//    MoveToEx(hDC, firstPoint.X, firstPoint.Y, NULL);
//    LineTo(hDC, thirdPoint.X, thirdPoint.Y);
//    return LineTo(hDC, thirdPoint.X, thirdPoint.Y);
//}
// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.