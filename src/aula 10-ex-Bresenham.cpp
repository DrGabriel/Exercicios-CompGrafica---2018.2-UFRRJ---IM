#include <stdio.h>

desenharPonto(int x, int y)
{
    printf("(%d), (%d)\n", x, y);
}

int main (void)
{

    int x1,
        y1,
        x2,
        y2,
        p,
        deltaX,
        deltaY,
        incrementoX,
        incrementoY;

    printf("Informe as extremidades da linha, x1 e y1 respectivamente: ");
    scanf("%d %d", &x1, &y1);
    printf("Informe as extremidades da linha, x2 e y2 respectivamente: ");
    scanf("%d %d", &x2, &y2);

    deltaX = x2-x1;
    deltaY = y2-y1;

    incrementoY = 2*deltaY;
    incrementoX = 2*deltaX;

    desenharPonto(x1,y1);

    p = (incrementoY)-deltaX;

    while(x1<x2)
    {
        if(p<0)
        {
            p +=  incrementoY;
            x1 += 1;
        }
        else
        {
            p += (incrementoY - incrementoX);
            x1 += 1;
            y1 += 1;
        }
        desenharPonto(x1,y1);
    }
    return 0;
}
