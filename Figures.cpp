#include "Figures.h"
#include <iostream>

HPEN getPen(int iPEN_STYLE, int iPEN_SIZE, int iCOLORREF)
{
    return CreatePen(iPEN_STYLE, iPEN_SIZE, iCOLORREF);
}

BOOL SetPoint(HDC hDC, HPEN hPen, COORD PNT)
{
    EXTLOGPEN pINFO;
    GetObject(hPen, sizeof(EXTLOGPEN), &pINFO);
    SelectObject(hDC, hPen);
    return Ellipse
    (
        hDC,
        PNT.X - pINFO.elpWidth,
        PNT.Y + pINFO.elpWidth,
        PNT.X + pINFO.elpWidth,
        PNT.Y - pINFO.elpWidth
    );
}

BOOL PlotLine(HDC hDC, HPEN hPen, COORD BGN, COORD END)
{
    SelectObject(hDC, hPen);
    MoveToEx(hDC, BGN.X, BGN.Y, NULL);
    return LineTo(hDC, END.X, END.Y);
}

Ellipses::Ellipses(size_t a, size_t b)
{
    hPen = getPen(PS_SOLID, 2, BLU);
    this->a = a;
    this->b = b;
    center.X = BeginArea.X + a;
    center.Y = BeginArea.Y + b;
    if ((center.X + a) > EndArea.X) {

    }
}

BOOL Ellipses::plotFigure(HDC hDC)
{
    int left = center.X - a;
    int top = center.Y - b;
    int right = center.X + a;
    int bottom = center.Y + b;
    SelectObject(hDC, hPen);
    return Ellipse(hDC, left, top, right, bottom);
}

void Ellipses::move(HDC hDC, int xMove, int yMove)
{
    clearFigure(hDC);
    center.X += xMove;
    center.Y += yMove;
    // при выходе за границы рабочей области происходит сдвиг фигуры только до границы
    // окрашиваем границу фигуры при некорректной операции
    bool flagIncorrect = false;
    if ((center.X + this->a) > EndArea.X) {
        center.X = EndArea.X - this->a;
        flagIncorrect = true;
    }
    if (static_cast<int>(center.X - this->a) < BeginArea.X) {
        center.X = BeginArea.X + this->a;
        flagIncorrect = true;
    }

    if ((center.Y + this->b) > EndArea.Y) {
        center.Y = EndArea.Y - this->b;
        flagIncorrect = true;
    }
    if (static_cast<int>(center.Y - this->b) < BeginArea.Y) {
        center.Y = BeginArea.Y + this->b;
        flagIncorrect = true;
    }
    if (!flagIncorrect) {
        plotFigure(hDC);
    }
    else {
        changeColorIncorrectOperation(hDC);
    }
    //plotFigure(hDC);
}

void Ellipses::resize(HDC hDC, double k)
{
    clearFigure(hDC);
    a *= k;
    b *= k;
    plotFigure(hDC);
}

void Ellipses::resizeX(HDC hDC, double k)
{
    clearFigure(hDC);
    a *= k;
    plotFigure(hDC);
}

void Ellipses::resizeY(HDC hDC, double k)
{
    clearFigure(hDC);
    b *= k;
    plotFigure(hDC);
}

void Ellipses::clearFigure(HDC hDC)
{
    HBRUSH hbrush = CreateSolidBrush(RGB(0, 0, 0));
    HPEN BLACKPEN = getPen(PS_SOLID, 3, BLK);

    int left = center.X - a;
    int top = center.Y - b;
    int right = center.X + a;
    int bottom = center.Y + b;

    SelectObject(hDC, BLACKPEN);
    Ellipse(hDC, left, top, right, bottom);
    SelectObject(hDC, hbrush);
    Ellipse(hDC, left, top, right, bottom);
    HBRUSH hbrush2 = CreateSolidBrush(RGB(255, 255, 255));
    SelectObject(hDC, hbrush2);
}

void Ellipses::setBoardColor(HPEN hPen)
{
    this->hPen = hPen;
}

void Ellipses::changeColorIncorrectOperation(HDC hDC)
{
    HPEN before = hPen;
    hPen = getPen(PS_SOLID, 3, RED);
    plotFigure(hDC);
    hPen = before;
}

//Figures::Figures(HDC hDC)
//{
//    HBRUSH hbrush = CreateSolidBrush(RGB(0, 0, 0));
//    SelectObject(hDC, hbrush);
//    Rectangle(hDC, BeginArea.X, BeginArea.Y, EndArea.X, EndArea.Y);
//}

Rectangles::Rectangles(size_t a, size_t b)
{
    this->a = a;
    this->b = b;
    bool flagIncorrect = false;
    if (a > (EndArea.X - BeginArea.X)) {
        this->a = (EndArea.X - BeginArea.X);
        flagIncorrect = true;
    }
    if (b > (EndArea.Y - BeginArea.Y)) {
        this->b = (EndArea.Y - BeginArea.Y);
        flagIncorrect = true;
    }
    center.X = BeginArea.X + this->a / 2;
    center.Y = BeginArea.Y + this->b / 2;
    if (flagIncorrect) {
        hPen = getPen(PS_SOLID, 2, RED);
    }
    else {
        hPen = getPen(PS_SOLID, 2, BLU);
    }
}

BOOL Rectangles::plotFigure(HDC hDC)
{
    bool flag = true;
    COORD leftTop = center;
    leftTop.X -= a / 2;
    leftTop.Y += b / 2;
    COORD rightTop = leftTop;
    rightTop.X += a;
    COORD rightBottom = rightTop;
    rightBottom.Y -= b;
    COORD leftBottom = leftTop;
    leftBottom.Y -= b;
    SelectObject(hDC, hPen);
    MoveToEx(hDC, leftTop.X, leftTop.Y, NULL);
    flag = flag && LineTo(hDC, rightTop.X, rightTop.Y);

    MoveToEx(hDC, rightTop.X, rightTop.Y, NULL);
    flag = flag && LineTo(hDC, rightBottom.X, rightBottom.Y);

    MoveToEx(hDC, rightBottom.X, rightBottom.Y, NULL);
    flag = flag && LineTo(hDC, leftBottom.X, leftBottom.Y);

    MoveToEx(hDC, leftBottom.X, leftBottom.Y, NULL);
    flag = flag && LineTo(hDC, leftTop.X, leftTop.Y);
    return flag;
}

void Rectangles::move(HDC hDC, int xMove, int yMove)
{
    clearFigure(hDC);
    center.X += xMove;
    center.Y += yMove;
    // при выходе за границы рабочей области происходит сдвиг фигуры только до границы
    // окрашиваем границу фигуры при некорректной операции
    bool flagIncorrect = false;
    if ((center.X + this->a/2) > EndArea.X) {
        center.X = EndArea.X - this->a / 2;
        flagIncorrect = true;
    }
    if (static_cast<int>(center.X - this->a / 2) < BeginArea.X) {
        center.X = BeginArea.X + this->a / 2;
        flagIncorrect = true;
    }

    if ((center.Y + this->b / 2) > EndArea.Y) {
        center.Y = EndArea.Y - this->b / 2;
        flagIncorrect = true;
    }
    if (static_cast<int>(center.Y - this->b / 2) < BeginArea.Y) {
        center.Y = BeginArea.Y + this->b / 2;
        flagIncorrect = true;
    }
    if (!flagIncorrect) {
        plotFigure(hDC);
    }
    else {
        changeColorIncorrectOperation(hDC);
    }
}

void Rectangles::resize(HDC hDC, double k)
{
    clearFigure(hDC);
    bool flagIncorrect = false;
    a *= k;
    b *= k;
    if ((a/2 + center.X) > EndArea.X) {
        a = (EndArea.X - center.X) * 2;
        flagIncorrect = true;
    }
    if (static_cast<int>(center.X - a/2) < BeginArea.X) {
        a = (center.X - BeginArea.X) * 2;
        flagIncorrect = true;
    }

    if ((b / 2 + center.Y) > EndArea.Y) {
        b = (EndArea.Y - center.Y) * 2;
        flagIncorrect = true;
    }
    if (static_cast<int>(center.Y - b / 2) < BeginArea.Y) {
        b = (center.Y - BeginArea.Y) * 2;
        flagIncorrect = true;
    }

    if (!flagIncorrect) {
        plotFigure(hDC);
    }
    else {
        changeColorIncorrectOperation(hDC);
    }
}

void Rectangles::clearFigure(HDC hDC)
{
    HPEN before = hPen;
    hPen = getPen(PS_SOLID, 3, BLK);
    plotFigure(hDC);
    hPen = before;
}

void Rectangles::resizeX(HDC hDC, double k)
{
    clearFigure(hDC);
    bool flagIncorrect = false;
    a *= k;
    if ((a / 2 + center.X) > EndArea.X) {
        a = (EndArea.X - center.X) * 2;
        flagIncorrect = true;
    }
    if (static_cast<int>(center.X - a / 2) < BeginArea.X) {
        a = (center.X - BeginArea.X) * 2;
        flagIncorrect = true;
    }
    if (!flagIncorrect) {
        plotFigure(hDC);
    }
    else {
        changeColorIncorrectOperation(hDC);
    }
}

void Rectangles::resizeY(HDC hDC, double k)
{
    clearFigure(hDC);
    bool flagIncorrect = false;
    b *= k;

    if ((b / 2 + center.Y) > EndArea.Y) {
        b = (EndArea.Y - center.Y) * 2;
        flagIncorrect = true;
    }
    if (static_cast<int>(center.Y - b / 2) < BeginArea.Y) {
        b = (center.Y - BeginArea.Y) * 2;
        flagIncorrect = true;
    }

    if (!flagIncorrect) {
        plotFigure(hDC);
    }
    else {
        changeColorIncorrectOperation(hDC);
    }
}

void Rectangles::setBoardColor(HPEN hPen)
{
    this->hPen = hPen;
}

bool Rectangles::turnOnAngleFromStartPosition(HDC hDC, double angle)
{
    clearFigure(hDC);
    bool flag = true;
    double l = sqrt(a*a + b*b)/2;
    double pi = 3.14;
    COORD first = center;
    double phi = 180 * atan(b/a) / pi;
    double firstAngle = 180 - phi + angle;
    first.X += l * cos(pi * firstAngle/180.0);
    first.Y += l * sin(pi * firstAngle / 180.0);

    COORD second = center;
    double secondAngle = phi + angle;
    second.X += l * cos(pi * secondAngle / 180.0);
    second.Y += l * sin(pi * secondAngle / 180.0);

    COORD third = center;
    double thirdAngle = -phi + angle;
    third.X += l * cos(pi * thirdAngle / 180.0);
    third.Y += l * sin(pi * thirdAngle / 180.0);

    COORD fourth = center;
    double fourthAngle = -180 + phi + angle;
    fourth.X += l * cos(pi * fourthAngle / 180.0);
    fourth.Y += l * sin(pi * fourthAngle / 180.0);

    SelectObject(hDC, hPen);
    MoveToEx(hDC, first.X, first.Y, NULL);
    flag = flag && LineTo(hDC, second.X, second.Y);

    SelectObject(hDC, hPen);
    MoveToEx(hDC, second.X, second.Y, NULL);
    flag = flag && LineTo(hDC, third.X, third.Y);

    SelectObject(hDC, hPen);
    MoveToEx(hDC, third.X, third.Y, NULL);
    flag = flag && LineTo(hDC, fourth.X, fourth.Y);

    SelectObject(hDC, hPen);
    MoveToEx(hDC, fourth.X, fourth.Y, NULL);
    flag = flag && LineTo(hDC, first.X, first.Y);

    return flag;
}

void Rectangles::changeColorIncorrectOperation(HDC hDC)
{
    HPEN before = hPen;
    hPen = getPen(PS_SOLID, 3, RED);
    plotFigure(hDC);
    hPen = before;
}

Squares::Squares(size_t a)
{
    this->a = a;
    center.X = BeginArea.X + a / 2;
    center.Y = BeginArea.Y + a / 2;
    hPen = getPen(PS_SOLID, 2, BLU);
}

BOOL Squares::plotFigure(HDC hDC)
{
    bool flag = true;
    COORD leftTop = center;
    leftTop.X -= a / 2;
    leftTop.Y += a / 2;
    COORD rightTop = leftTop;
    rightTop.X += a;
    COORD rightBottom = rightTop;
    rightBottom.Y -= a;
    COORD leftBottom = leftTop;
    leftBottom.Y -= a;
    SelectObject(hDC, hPen);
    MoveToEx(hDC, leftTop.X, leftTop.Y, NULL);
    flag = flag && LineTo(hDC, rightTop.X, rightTop.Y);

    MoveToEx(hDC, rightTop.X, rightTop.Y, NULL);
    flag = flag && LineTo(hDC, rightBottom.X, rightBottom.Y);

    MoveToEx(hDC, rightBottom.X, rightBottom.Y, NULL);
    flag = flag && LineTo(hDC, leftBottom.X, leftBottom.Y);

    MoveToEx(hDC, leftBottom.X, leftBottom.Y, NULL);
    flag = flag && LineTo(hDC, leftTop.X, leftTop.Y);
    return flag;
}

void Squares::move(HDC hDC, int xMove, int yMove)
{
    clearFigure(hDC);
    center.X += xMove;
    center.Y += yMove;
    plotFigure(hDC);
}

void Squares::resize(HDC hDC, double k)
{
    clearFigure(hDC);
    a *= k;
    plotFigure(hDC);
}

void Squares::clearFigure(HDC hDC)
{
    HPEN before = hPen;
    hPen = getPen(PS_SOLID, 3, BLK);
    plotFigure(hDC);
    hPen = before;
}

void Squares::resizeX(HDC hDC, double k)
{
    std::cout << "square can't be resized in this way" << std::endl;
}

void Squares::resizeY(HDC hDC, double k)
{
    std::cout << "square can't be resized in this way" << std::endl;
}

void Squares::setBoardColor(HPEN hPen)
{
    this->hPen = hPen;
}

Circles::Circles(size_t r)
{
    this->r = r;
    center.X = BeginArea.X + r / 2;
    center.Y = BeginArea.Y + r / 2;
    hPen = getPen(PS_SOLID, 2, BLU);
}

BOOL Circles::plotFigure(HDC hDC)
{
    int left = center.X - r;
    int top = center.Y - r;
    int right = center.X + r;
    int bottom = center.Y + r;
    SelectObject(hDC, hPen);
    return Ellipse(hDC, left, top, right, bottom);
}

void Circles::move(HDC hDC, int xMove, int yMove)
{
    clearFigure(hDC);
    center.X += xMove;
    center.Y += yMove;
    plotFigure(hDC);
}

void Circles::resize(HDC hDC, double k)
{
    clearFigure(hDC);
    r *= k;
    plotFigure(hDC);
}

void Circles::clearFigure(HDC hDC)
{
    HPEN before = hPen;
    hPen = getPen(PS_SOLID, 3, BLK);
    plotFigure(hDC);
    hPen = before;
}

void Circles::resizeX(HDC hDC, double k)
{
    std::cout << "circle can't be resized in this way" << std::endl;
}

void Circles::resizeY(HDC hDC, double k)
{
    std::cout << "circle can't be resized in this way" << std::endl;
}

void Circles::setBoardColor(HPEN hPen)
{
    this->hPen = hPen;
}
