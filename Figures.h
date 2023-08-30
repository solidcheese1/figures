#pragma once
#include <windows.h>
#include <math.h>

// задаем цвета
#define RED RGB(255,0,0)
#define GRN RGB(0,255,0)
#define BLU RGB(0,0,255)

#define BLK RGB(0,0,0)
#define WHT RGB(255,255,255)

// задаем границы области, на которой происходит отрисовка фигур
static COORD BeginAreaDefined = { 50,50 };
static COORD EndAreaDefined = {550, 450};

HPEN  getPen(int iPEN_STYLE, int iPEN_SIZE, int iCOLORREF);
BOOL  SetPoint(HDC hDC, HPEN hPen, COORD PNT);
BOOL  PlotLine(HDC hDC, HPEN hPen, COORD BGN, COORD END);

class Figures {
	public:
		// левый верхний угол
		COORD BeginArea = BeginAreaDefined;
		// правый нижний угол
		COORD EndArea = EndAreaDefined;
		// отрисовка фигуры
		virtual BOOL plotFigure(HDC hDC) = 0;
		// сдвиг фигуры на (xMove, yMove), 
		// при достижении границы окрашиваем контур фигуры в красный цвет и дальше не сдвигаем
		virtual void move(HDC hDC, int xMove, int yMove) = 0;
		// увеличиваем размер фигуры в k раз,
		// при достижении границы окрашиваем контур фигуры в красный цвет и дальше не сдвигаем
		virtual void resize(HDC hDC, double k) = 0;
		// производим растяжение фигуры в k раз вдоль оси x,
		// при достижении границы окрашиваем контур фигуры в красный цвет и дальше не сдвигаем
		virtual void resizeX(HDC hDC, double k) = 0;
		// производим растяжение фигуры в k раз вдоль оси y,
		// при достижении границы окрашиваем контур фигуры в красный цвет и дальше не сдвигаем
		virtual void resizeY(HDC hDC, double k) = 0;
		// стираем фигуру
		virtual void clearFigure(HDC hDC) = 0;
		// устанавливаем цвет границы(не рекомендуется ставить красный,
		//красная граница устанавливается при выходе за границу области)
		virtual void setBoardColor(HPEN hPen) = 0;
};

class Ellipses : public Figures {
private:
	// "центр"
	COORD center;
	// полуоси эллипса
	size_t a;
	size_t b;
	// "цвет"
	HPEN hPen;
public:
	Ellipses(size_t a, size_t b);
	BOOL plotFigure(HDC hDC) override;
	//void TurnOnAngle(double angle);
	void move(HDC hDC, int xmove, int ymove) override;
	void resize(HDC hDC, double k) override;
	void resizeX(HDC hDC, double k) override;
	void resizeY(HDC hDC, double k) override;
	void clearFigure(HDC hDC) override;
	void setBoardColor(HPEN hPen) override;
	// меняем цвет границы при невозможности завершить операцию сдвига или растяжения 
	void changeColorIncorrectOperation(HDC hDC);
};

class Rectangles: public Figures {
private:
	// "центр"
	COORD center;
	// стороны
	size_t a;
	size_t b;
	// угол поворота в градусах от начального положения
	double angle;
	// "цвет"
	HPEN hPen;
public:
	Rectangles(size_t a, size_t b);
	BOOL plotFigure(HDC hDC) override;
	void move(HDC hDC, int xmove, int ymove) override;
	void resize(HDC hDC, double k) override;
	void clearFigure(HDC hDC) override;
	void resizeX(HDC hDC, double k) override;
	void resizeY(HDC hDC, double k) override;
	void setBoardColor(HPEN hPen) override;
	// производим поворот на угол angle в градусах по часовой стрелке
	bool turnOnAngleFromStartPosition(HDC hDC, double angle);
	// меняем цвет границы при невозможности завершить операцию сдвига или растяжения 
	void changeColorIncorrectOperation(HDC hDC);
};

class Squares : public Figures {
private:
	COORD center;
	// сторона
	size_t a;
	HPEN hPen;
public:
	Squares(size_t a);
	BOOL plotFigure(HDC hDC) override;
	void move(HDC hDC, int xmove, int ymove) override;
	void resize(HDC hDC, double k) override;
	void clearFigure(HDC hDC) override;
	void resizeX(HDC hDC, double k) override;
	void resizeY(HDC hDC, double k) override;
	void setBoardColor(HPEN hPen) override;
};

class Circles : public Figures {
private:
	COORD center;
	// радиус
	size_t r;
	HPEN hPen;
public:
	Circles(size_t r);
	BOOL plotFigure(HDC hDC) override;
	void move(HDC hDC, int xmove, int ymove) override;
	void resize(HDC hDC, double k) override;
	void clearFigure(HDC hDC) override;
	void resizeX(HDC hDC, double k) override;
	void resizeY(HDC hDC, double k) override;
	void setBoardColor(HPEN hPen) override;
};