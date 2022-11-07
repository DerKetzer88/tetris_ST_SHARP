#ifndef TETRIS_H
#define TETRIS_H
typedef struct{
	unsigned int x; //координата X верхнего левого угла
	unsigned int y; //координата Y верхнего левого угла
	unsigned int xp; //место на поле по горизонтали
	unsigned int yp; //место на поле по вертикали
}BRICK;
int tr_moveUp(void);
int tr_moveDown(void);
int tr_moveLeft(void);
int tr_moveRight(void);
unsigned int tr_findFullLine(void);
unsigned int tr_rotateCollision(BRICK* br);
void updateField(void);
#endif