
#ifndef INPUT
#define INPUT

/* definitions */

void drawCurrMap();

void drawPixel(Pixel *pixel);

void drawTile(int tileX, int tileY);

void moveAndDrawEnemy(int x_offset, int y_offset, EnemyInfo *enemy);

void moveAndDrawMario(int x_offset, int y_offset, EnemyInfo *enemy);

void moveSpriteToCell(int x_offset, int y_offset, struct EnemyInfo *enemy, int spriteCode);


#endif
