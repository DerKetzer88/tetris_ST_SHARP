#include "tetris.h"
/*игровое поле  1 - клетка занята. 0 - клетка свободна
*/
unsigned char field[10][20]; //[X][Y]
BRICK b0,b1,b2,b3;
BRICK shb0, shb1, shb2, shb3;
#define XS	10
#define YS	10
#define DX0 (0 + XS)
#define DX1	(8 + XS)
#define DX2	(16 + XS)
#define DX3	(24 + XS)
#define DX4	(32 + XS)
#define DX5	(40 + XS)
#define DX6	(48 + XS)
#define DX7	(56 + XS)
#define DX8	(64 + XS)
#define DX9 (72 + XS)
#define DY0	(0 + YS)
#define DY1 (8 + YS)
#define DY2	(16 + YS)
#define DY3 (24 + YS)
#define DY4 (32 + YS)
#define	DY5	(40 + YS)
#define DY6 (48 + YS)
#define DY7 (56 + YS)
#define DY8 (64 + YS)
#define DY9 (72 + YS)
#define DY10 (80 + YS)
#define DY11 (88 + YS)
#define DY12 (96 + YS)
#define DY13 (104 + YS)
#define DY14 (112 + YS)
#define DY15 (120 + YS)
#define DY16 (128 + YS)
#define DY17 (136 + YS)
#define DY18 (144 + YS)
#define DY19 (152 + YS)
#define DY20 (160 + YS)

typedef enum{
	LINE = 1,
	QUADRAT,
	L,
	mL,
	Z,
	mZ,
	T
}FIGURE;

void tr_createFig(unsigned int type)
{
	/*
	type 1 - line;
	type 2 - quadr;
	type 3 - L;
	type 4 - _|;
	type 5 - lz;
	type 6 - rz
	type 7 - T 
	*/
	switch(type){
		case 1: //LINE
			b1.x = DX3;	b1.y = DY0;	b2.x = DX4;	b2.y = DY0;	b0.x = DX5;	b0.y = DY0;	b3.x = DX6;	b3.y = DY0;
			break;
		case 2: //quadrat
			b0.x = DX3; b0.y = DY0; b1.x = DX4; b1.y = DY0; b2.x = DX3; b2.y = DY1; b3.x = DX4; b3.y = DY1;
			break;
		case 3: //L
			b1.x = DX3;	b0.y = DY1;	b0.x = DX4;	b0.y = DY1;	b2.x = DX5;	b2.y = DY1; b3.x = DX5; b3.y = DY0;
			break;
		case 4: //mL
			b3.x = DX3;	b3.y = DY0;	b2.x = DX3;	b2.y = DY1;	b0.x = DX4;	b0.y = DY1; b1.x = DX5; b1.y = DY1;
			break;
		case 5: //Z
			b1.x = DX3;	b1.y = DY0;	b0.x = DX4;	b0.y = DY0; b2.x = DX4;	b2.y = DY1; b3.x = DX5; b3.y = DY1;
			break;
		case 6: //mZ
			b3.x = DX3;	b3.y = DY1;	b2.x = DX4;	b2.y = DY1; b0.x = DX4;	b0.y = DY0; b1.x = DX5; b1.y = DY0;
			break;
		case 7: //T
			b1.x = DX3;	b1.y = DY1;	b0.x = DX4;	b0.y = DY1; b3.x = DX4;	b3.y = DY0; b2.x = DX5; b2.y = DY1;
		break;
		default:
			break;
	}
}
int tr_moveLeft()
{
	if(!b0.x || !b1.x || !b2.x || !b3.x) return 0;
	if( field[ ((b0.x-XS)>>3)-1][ (b0.y-YS)>>3]) return 0;
	b0.x -=1;
	b1.x -= 1;
	b2.x -= 1;
	b3.x -= 1;
	return 0;
}
int tr_moveRight()
{
	if( (b0.x == DX9) || (b1.x == DX9) || (b2.x == DX9) || (b3.x == DX9)) return 0;
	if( field[ ((b0.x-XS)>>3) + 1][ (b0.y-YS)>>3]) return 0;
	if(1){ //функция колизий слева
		b0.x +=1;
		b1.x += 1;
		b2.x += 1;
		b3.x += 1;
	}
	return 0;
}
int tr_moveDown()
{
	if( (b0.y == DY19) || (b1.y == DY19) || (b2.y == DY19) || (b3.y == DY19) ) return 0;
	if( field[ (b0.x-XS)>>3][ ((b0.y-YS)>>3) + 1]) return 0;
	b0.y +=1;
	b1.y += 1;
	b2.y += 1;
	b3.y += 1;
	return 1;
}
int tr_moveUp()
{
	if(!b0.y || !b1.y || !b2.y || !b3.y) return 0;
	if(1){ //функция колизий вверху
		b0.y -=1;
		b1.y -= 1;
		b2.y -= 1;
		b3.y -= 1;
	}
	return 0;
}
unsigned int tr_findFullLine()
{
	unsigned int line = 0;
	int y;
	for(y = 0; y < 20; y++){
		if (field[y][0] + field[y][1] + field[y][2] + field[y][3] + field[y][4] + field[y][5] + 
		field[y][6] + field[y][7] + field[y][8] + field[y][9] == 10)
		{
			line |= 1 << y;
		}
	}
	return (line);
}
int tr_rotateLeft(unsigned int type, unsigned int deg)
{
	shb0 = b0;
	shb1 = b1;
	shb2 = b2;
	shb3 = b3;
	unsigned int shtype;
	unsigned int cls = 0;
	switch(type){
		case LINE:
			//получим новые координаты для 4х теневых кирпичей. отправим в функцию проверки на коллизии
			//если будет колизия то фигура не поворачивается
		shtype = type;
		if (shtype == 0) shtype = 1;
		else shtype = 0;
		if (type == 1){
				shb1.x +=2; 
				shb1.y -=2;
				cls = tr_rotateCollision(&shb1);
				shb2.x +=1;
				shb2.y -=1;
				cls += tr_rotateCollision(&shb2);
				shb3.x -=1;
				shb3.y +=1;
				cls += tr_rotateCollision(&shb3);
			}
		else{
				shb1.x -=2; 
				shb1.y +=2;			
				shb2.x -=1;
				shb2.y +=1;				
				shb3.x +=1;
				shb3.y -=1;
				cls += tr_rotateCollision(&shb1);
				cls = tr_rotateCollision(&shb2);
				cls += tr_rotateCollision(&shb3);
		}
			if(!cls){ //поворот возможен
				//обновить field надо.
				updateField();
				b1 = shb1; b2 = shb2; b3 = shb3; type  = shtype;
				
				return 1;
			}
			break;
		case QUADRAT:
			break;
		case L:
		shtype = type;
		shtype++;
		if (shtype == 4) shtype = 0;
		switch(shtype){
			case 0:
				shb1.x = shb0.x - 1;
				shb1.y = shb0.y;
				shb2.x = shb0.x + 1;
				shb2.y = shb0.y;
				shb3.x = shb0.x + 1;
				shb3.y = shb0.y - 1;
			break;
			case 1:
				shb1.x = shb0.x;
				shb1.y = shb0.y + 1;
				shb2.x = shb0.x;
				shb2.y = shb0.y - 1;
				shb3.x = shb0.x - 1;
				shb3.y = shb0.y - 1;
				break;
			case 2:
				shb1.x = shb0.x + 1;
				shb1.y = shb0.y;
				shb2.x = shb0.x - 1;
				shb2.y = shb0.y;
				shb3.x = shb0.x - 1;
				shb3.y = shb0.y + 1;
				break;
			case 3:
				shb1.x = shb0.x;
				shb1.y = shb0.y - 1;
				shb2.x = shb0.x;
				shb2.y = shb0.y + 1;
				shb3.x = shb0.x + 1;
				shb3.y = shb0.y + 1;
				break;
			default:
				break;
		}
		cls = tr_rotateCollision(&shb1);
		cls += tr_rotateCollision(&shb2);
		cls += tr_rotateCollision(&shb3);
		if(!cls){
				b1 = shb1; b2 = shb2; b3 = shb3; type  = shtype;
				return 1;
		}
		break;
		
		case mL:
		shtype = type;
		shtype++;
		if (shtype == 4) shtype = 0;
		switch(shtype){
			case 0:
				shb1.x = shb0.x + 1;
				shb1.y = shb0.y;
				shb2.x = shb0.x - 1;
				shb2.y = shb0.y;
				shb3.x = shb0.x - 1;
				shb3.y = shb0.y - 1;	
			break;
			case 1:
				shb1.x = shb0.x;
				shb1.y = shb0.y - 1;
				shb2.x = shb0.x;
				shb2.y = shb0.y + 1;
				shb3.x = shb0.x - 1;
				shb3.y = shb0.y + 1;
			break;
			case 2:
				shb1.x = shb0.x - 1;
				shb1.y = shb0.y;
				shb2.x = shb0.x + 1;
				shb2.y = shb0.y;
				shb3.x = shb0.x + 1;
				shb3.y = shb0.y + 1;
			break;
			case 3:
				shb1.x = shb0.x;
				shb1.y = shb0.y + 1;
				shb2.x = shb0.x;
				shb2.y = shb0.y - 1;
				shb3.x = shb0.x + 1;
				shb3.y = shb0.y - 1;
			break;
			default:
			break;
		cls = tr_rotateCollision(&shb1);	
		cls += tr_rotateCollision(&shb2);
		cls += tr_rotateCollision(&shb3);
		if(!cls){
				b1 = shb1; b2 = shb2; b3 = shb3; type  = shtype;
				return 1;
		}
		}					
		break;
		
		case Z:
			shtype = type;
		if(shtype == 0){
			shtype = 1;
			shb1.x = shb0.x;
			shb1.y = shb0.y + 1;
			shb2.x = shb0.x + 1;
			shb2.y = shb0.y;
			shb3.x = shb0.x + 1;
			shb3.y = shb0.y - 1;
			
		}
		else {
			shtype = 0;
			shb1.x = shb0.x - 1;
			shb1.y = shb0.y;
			shb2.x = shb0.x;
			shb2.y = shb0.y + 1;
			shb3.x = shb0.x + 1;
			shb3.y = shb0.y + 1;
		}
		cls = tr_rotateCollision(&shb1);	
		cls += tr_rotateCollision(&shb2);
		cls += tr_rotateCollision(&shb3);
		if(!cls){
				b1 = shb1; b2 = shb2; b3 = shb3; type  = shtype;
				return 1;
		}
		break;
		
		case mZ:
		shtype = type;
		if(shtype == 0){
			shtype = 1;
			shb1.x = shb0.x + 1;
			shb1.y = shb0.y;
			shb2.x = shb0.x;
			shb2.y = shb0.y + 1;
			shb3.x = shb0.x - 1;
			shb3.y = shb0.y + 1;		
		}
		else {
			shtype = 0;
			shb1.x = shb0.x;
			shb1.y = shb0.y + 1;
			shb2.x = shb0.x + 1;
			shb2.y = shb0.y;
			shb3.x = shb0.x + 1;
			shb3.y = shb0.y + 1;
		}
		cls = tr_rotateCollision(&shb1);	
		cls += tr_rotateCollision(&shb2);
		cls += tr_rotateCollision(&shb3);
		if(!cls){
				b1 = shb1; b2 = shb2; b3 = shb3; type  = shtype;
				return 1;
		}
		break;
		
		case T:
		shtype = type;
		shtype++;
		if (shtype == 4) shtype = 0;
		switch(shtype){
			case 0:
				shb1.x = shb0.x + 1;
				shb1.y = shb0.y;
				shb2.x = shb0.x - 1;
				shb2.y = shb0.y;
				shb3.x = shb0.x - 1;
				shb3.y = shb0.y - 1;	
			break;
			case 1:
				shb1.x = shb0.x;
				shb1.y = shb0.y - 1;
				shb2.x = shb0.x;
				shb2.y = shb0.y + 1;
				shb3.x = shb0.x - 1;
				shb3.y = shb0.y + 1;
			break;
			case 2:
				shb1.x = shb0.x - 1;
				shb1.y = shb0.y;
				shb2.x = shb0.x + 1;
				shb2.y = shb0.y;
				shb3.x = shb0.x + 1;
				shb3.y = shb0.y + 1;
			break;
			case 3:
				shb1.x = shb0.x;
				shb1.y = shb0.y + 1;
				shb2.x = shb0.x;
				shb2.y = shb0.y - 1;
				shb3.x = shb0.x + 1;
				shb3.y = shb0.y - 1;
			break;
			default:
			break;
		cls = tr_rotateCollision(&shb1);	
		cls += tr_rotateCollision(&shb2);
		cls += tr_rotateCollision(&shb3);
		if(!cls){
				b1 = shb1; b2 = shb2; b3 = shb3; type  = shtype;
				return 1;
		}
		}	
		break;
		default:
			break;
	}
	
}
int tr_rotateRight((unsigned int type, unsigned int deg))
{
}
unsigned int tr_rotateCollision(BRICK* br)
{
	if ( br->x > (XS + 10 - 1)) return (1);
	if (br->x < XS ) return (1);
	if (br->y > (YS + 20 - 1)) return (1);
	if (br->y < YS) return (1);
	if (field[br->x][br->y] == 1) return (1);
	
}
void updateField()
{
	field[b1.x][b1.y] = 0;
	field[b2.x][b2.y] = 0;
	field[b3.x][b3.y] = 0;
	field[shb1.x][b1.y] = 0;
	field[shb2.x][b2.y] = 0;
	field[shb3.x][b3.y] = 0;
	
}
