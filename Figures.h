#pragma once
#include <windows.h>
#include <math.h>

// ������ �����
#define RED RGB(255,0,0)
#define GRN RGB(0,255,0)
#define BLU RGB(0,0,255)

#define BLK RGB(0,0,0)
#define WHT RGB(255,255,255)

// ������ ������� �������, �� ������� ���������� ��������� �����
static COORD BeginAreaDefined = { 50,50 };
static COORD EndAreaDefined = {550, 450};

HPEN  getPen(int iPEN_STYLE, int iPEN_SIZE, int iCOLORREF);
BOOL  SetPoint(HDC hDC, HPEN hPen, COORD PNT);
BOOL  PlotLine(HDC hDC, HPEN hPen, COORD BGN, COORD END);

class Figures {
	public:
		// ����� ������� ����
		COORD BeginArea = BeginAreaDefined;
		// ������ ������ ����
		COORD EndArea = EndAreaDefined;
		// ��������� ������
		virtual BOOL plotFigure(HDC hDC) = 0;
		// ����� ������ �� (xMove, yMove), 
		// ��� ���������� ������� ���������� ������ ������ � ������� ���� � ������ �� ��������
		virtual void move(HDC hDC, int xMove, int yMove) = 0;
		// ����������� ������ ������ � k ���,
		// ��� ���������� ������� ���������� ������ ������ � ������� ���� � ������ �� ��������
		virtual void resize(HDC hDC, double k) = 0;
		// ���������� ���������� ������ � k ��� ����� ��� x,
		// ��� ���������� ������� ���������� ������ ������ � ������� ���� � ������ �� ��������
		virtual void resizeX(HDC hDC, double k) = 0;
		// ���������� ���������� ������ � k ��� ����� ��� y,
		// ��� ���������� ������� ���������� ������ ������ � ������� ���� � ������ �� ��������
		virtual void resizeY(HDC hDC, double k) = 0;
		// ������� ������
		virtual void clearFigure(HDC hDC) = 0;
		// ������������� ���� �������(�� ������������� ������� �������,
		//������� ������� ��������������� ��� ������ �� ������� �������)
		virtual void setBoardColor(HPEN hPen) = 0;
};

class Ellipses : public Figures {
private:
	// "�����"
	COORD center;
	// ������� �������
	size_t a;
	size_t b;
	// "����"
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
	// ������ ���� ������� ��� ������������� ��������� �������� ������ ��� ���������� 
	void changeColorIncorrectOperation(HDC hDC);
};

class Rectangles: public Figures {
private:
	// "�����"
	COORD center;
	// �������
	size_t a;
	size_t b;
	// ���� �������� � �������� �� ���������� ���������
	double angle;
	// "����"
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
	// ���������� ������� �� ���� angle � �������� �� ������� �������
	bool turnOnAngleFromStartPosition(HDC hDC, double angle);
	// ������ ���� ������� ��� ������������� ��������� �������� ������ ��� ���������� 
	void changeColorIncorrectOperation(HDC hDC);
};

class Squares : public Figures {
private:
	COORD center;
	// �������
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
	// ������
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