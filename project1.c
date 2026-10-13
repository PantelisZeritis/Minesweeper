/*Pantelehmwn Zeritis
AM: 2022202200053
dit22053@go.uop.gr

Anastasios Tsilikounas
AM: 2022202200217
dit22217@go.uop.gr*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX 50
#define MIN 2
#define DIFFI 4

int** nmarray();
int** apppeararray();
int perin(int** pin, int nr , int mc);
void appear(int **apar, int** pin);
void aptest(int **apar, int** pin);
void randoml(int **apar, int** pin, int x , int y);
int sod();
int text(char* str);
void open(char* str, int** pin, int** apar);
void mark(char* str, int** pin, int** apar);
void cheat(char* str, int** pin, int** apar);
int anad(int** pin, int** apar, int x, int y);
int win(int** pin, int** apar);
int counter(int** apar);

int n, m, lvl = 0, rounds = 0;

int main(void)
{
    int i, j, x, y, **pin, **apar, dif, mtext;
    char str[50];
    
    
    printf("Give size\nRaws: ");
    scanf("%d", &n);
    if(n > MAX || n < MIN)
    do
    {
        printf("Give raws within parameters: ");
        scanf("%d", &n);
    } while (n > MAX || n < MIN);

    printf("Columns: ");
    scanf("%d", &m);
    if(m > MAX || m < MIN)
    do
    {
        printf("Give columns within parameters: ");
        scanf("%d", &m);
    } while (m > MAX || m < MIN);

    printf("Give level of difficulty[1-4]: ");
    scanf("%d", &lvl);
    if(lvl > 4 || lvl < 1)
    do
    {
        printf("I said [1-4] -_- : ");
        scanf("%d", &lvl);
    }while(lvl > 4 || lvl < 1);

    for(;;)
    {
        rounds++;

        printf("Choose your first coordinates\nGive x:");
        scanf("%d", &x);
        if(x <= 0 || x > n)
        do
        {
            printf("Give x within parameters: ");
            scanf("%d", &x);
        } while (x <= 0 || x > n);

        printf("Give y:");
        scanf("%d", &y);
        if(y <= 0 || y > m)
        do
        {
            printf("Give y within parameters: ");
            scanf("%d", &y);
        } while (y <= 0 || y > m);

        printf("\n\n");

        x--;
        y--;

        pin = nmarray();
        apar = apppeararray();

        randoml(apar, pin, x, y);

        anad(pin, apar, x, y);

        apar[x][y]++;
        appear(apar, pin);

        //aptest(apar, pin);

        printf("\n\n\t\t***Choose***\n\n1.open(x,y)\n2.mark(x,y)\n3.cheat(x,y)\n4.exit\n\n");

        for(;;)
        {
            if(!win(pin, apar))
            {
                printf("\t\t***Congrats you won!***\n\nNext round:");
                break;
            }
            
            fgets(str, 50, stdin);
            str[strcspn(str, "\n")] = '\0';

            mtext = text(str);

            if(mtext == 1)
                open(str, pin, apar);
            else if(mtext == 2)
                mark(str, pin , apar);
            else if(mtext == 3)
                cheat(str, pin, apar);
            else if(mtext == 4)
                exit(0);
            else
            {
                if(str[0] == '\0')
                    continue;
                printf("\t\t***Incorrect command***\nPlease choose:\n\n1.open(x,y)\n2.mark(x,y)\n3.cheat(x,y)\n4.exit\n\n");
                continue;
            }                

            if(!win(pin, apar))
            {
                printf("\t\t***Congrats you won!***\n\nNext round:");
                break;
            }

        }
        for(i = 0; i < n; i++)
            free(pin[i]);
        free(pin);

        for(i = 0; i < n; i++)
            free(apar[i]);
        free(apar);
        
        n += 5;
        m += 5;

        if(n >= MAX || m >= MAX)
        {
            printf("\n\n\t\t***You finished the game!!!***You are now officially old\n\n\n");
            exit(0);
        }       
    }

}

int** nmarray()
{
    int i, j, **pin;

    pin = (int**) malloc(n * sizeof(int*));
    if(pin == NULL)
    {
        printf("Error : not available memory\n");
        exit(EXIT_FAILURE);
    }
    
    for(i = 0; i < n; i++)
    {
        pin[i] = (int*) malloc(m * sizeof(int));
        if(pin[i] == NULL)
        {
            printf("Error : not available memory\n");
            exit(EXIT_FAILURE);
        }
    }

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
            pin[i][j] = 0;
    }
    return pin;
}

int** apppeararray()
{
    int i, j, **apar;

    apar = (int**) malloc(n * sizeof(int*));
    if(apar == NULL)
    {
        printf("Error : not available memory\n");
        exit(EXIT_FAILURE);
    }
    
    for(i = 0; i < n; i++)
    {
        apar[i] = (int*) malloc(m * sizeof(int));
        if(apar[i] == NULL)
        {
            printf("Error : not available memory\n");
            exit(EXIT_FAILURE);
        }
    }

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
            apar[i][j] = 0;
    }
    return apar;
}

void randoml(int ** apar, int** pin, int x, int y)
{
    int i, j, r1, r2;

    srand(time(NULL));
    for(i = 0; i < sod() + 1; i++)
    {
        do
        {
            r1 = rand() % n;
            r2 = rand() % m;    
        } while (pin[r1][r2] == '@' || (r1 == x && r2 == y));

        pin[r1][r2] = '@';
    }

    for(i = n - 1; i >= 0; i--)
    {
        for(j = m; j >= 0; j--)
        {
            if(pin[i][j] != '@')
                pin[i][j] = perin(pin, i, j);
        }        
    }
}

int sod()
{
    switch (lvl)
    {
    case 1:
        return (n*m*0.1);
    break;
    
    case 2:
        return (n*m*0.15);
    break;

    case 3:
        return (n*m*0.2);
    break;

    case 4:
        return (n*m*0.25);
    break;
    }
}

void appear(int **apar, int** pin)
{
    int i, j;

    printf("\n\n\n");

    for(i = 0; i < m; i++)
    {
        if(!i)
            printf("   ");
        printf(" %2d", i+1);
    }
    printf("\n");

    for(i = 0; i < m * 3 + 3; i++)
        printf("-");
    printf("\n");
    
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
        {
            if(!j)
                printf("%2d|", i+1);
            if((!apar[i][j]))
                printf("  #");
            else if((pin[i][j] == '@' && apar[i][j]) || (apar[i][j] == '@'))
                printf("  @");
            else if(pin[i][j] && apar[i][j] && pin[i][j] != 14)
                printf("%3d", pin[i][j]);
            else if((!pin[i][j]) && apar[i][j])
                printf("  .");
            else if(pin[i][j] == 14)
                printf("  .");
        }
        printf("\n");
    }
    printf("\n");


    printf("%d blocks are open.\n\nMake your move(s): \n\n", counter(apar));
}


void aptest(int **apar, int** pin)
{
    int i, j;

    for(i = 0; i < m; i++)
    {
        if(!i)
            printf("   ");
        printf(" %2d", i+1);
    }
    printf("\n");

    for(i = 0; i < m * 3 + 3; i++)
        printf("-");
    printf("\n");

    
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
        {
            if(!j)
                printf("%2d|", i+1);
            printf("%3d", pin[i][j]);
        }
        printf("\n");
    }
    printf("\n");


    printf("%d block(s) are open.\nMake your move(s): \n", counter(apar));
}

int perin(int** pin, int nr , int mc)
{
    int numbombs = 0;

    
    if((nr - 1) >= 0 && (mc - 1) >= 0)
        if(pin[nr - 1][mc - 1] == '@')
            numbombs++;

    if((nr - 1) >= 0)
        if(pin[nr - 1][mc] == '@')
            numbombs++;

    if((nr - 1) >= 0 && (mc + 1) < m)
       if(pin[nr - 1][mc + 1] == '@')
            numbombs++;

    if((mc - 1) >= 0)
        if(pin[nr][mc - 1] == '@')
            numbombs++;

    if((mc + 1) < m)
        if(pin[nr][mc + 1] == '@')
            numbombs++;

    if((nr + 1) < n && (mc - 1) >= 0)
        if(pin[nr + 1][mc - 1] == '@')
            numbombs++;

    if((nr + 1) < n)
        if(pin[nr + 1][mc] == '@')
            numbombs++;

    if((nr + 1) < n && (mc + 1) < m)
        if(pin[nr + 1][mc + 1] == '@')
            numbombs++;


    return numbombs;
}

int text(char* str)
{
    int mtext, i, j, count = 0;

    
    if(strncmp(str, "open(", 4) == 0)
            mtext = 1;
    else if(strncmp(str, "mark(", 4) == 0) 
        mtext = 2;
    else if(strncmp(str, "cheat(", 5) == 0)
        mtext = 3;
    else if(strncmp(str, "exit(", 4) == 0)
        mtext = 4;
    else
        mtext = 5;

        return mtext;   
}

void open(char* str, int** pin, int** apar)
{
    int i, j, count;

    count = sscanf(str, "open(%d,%d)", &i, &j);

    i--;
    j--;

    if(i < 0 || i >= n)
        {
            do
            {
                printf("Give x within parameters: ");
                scanf("%d", &i);
                i--;
            } while (i < 0 || i >= n);
        }
    
    if(j < 0 || j >= m)
        {
            do
            {
                printf("Give y within parameters: ");
                scanf("%d", &j);
                j--;
            } while (j < 0 || j >= m);
        }

    if(apar[i][j] && apar[i][j] != '@')
    {
    START:
        printf("You have opened this  square, give other coordinates:\nX:");
        scanf("%d", &i);
        i--;
        if(i < 0 || i >= n)
        do
        {
            printf("Give x within parameters: ");
            scanf("%d", &i);
            i--;
        } while (i < 0 || i >= n);
        printf("Y:");
        scanf("%d", &j);
        j--;
        if(j < 0 || j >= m)
        do
        {
            printf("Give y within parameters: ");
            scanf("%d", &j);
            j--;
        } while (j < 0 || j >= m);
        if(pin[i][j] == '@')
        {
            printf("\t\t***  Oups! You lost!  ***\n\nFinal score:\nLevel: %d\nRound: %d\nBlock(s) opened: %d\nSize of array: %dx%d(%d squares)\n\n", lvl, rounds,counter(apar), n, m, (n*m));
            exit(0);
        }
        if(apar[i][j])
            goto START;
        apar[i][j]++;
        appear(apar, pin);
        
    }
    else
    {
        if(pin[i][j] == '@')
        {
            printf("\t\t***  Oups! You lost!  ***\n\nFinal score:\nLevel: %d\nRound: %d\nBlock(s) opened: %d\nSize of array: %dx%d(%d squares)\n\n", lvl, rounds,counter(apar), n, m, (n*m));
            exit(0);
        }
        else if(pin[i][j] == 0)
        {
            anad(pin, apar, i, j);
            appear(apar, pin);
        }        
        else
        {
            apar[i][j]++;
            appear(apar, pin);
        }
    }
}

void mark(char* str, int** pin, int** apar)
{
    int i, j, count;
   
    count = sscanf(str, "mark(%d,%d)", &i, &j);

    i--;
    j--;

    if(i < 0 || i >= n)
        {
            do
            {
                printf("Give x within parameters: ");
                scanf("%d", &i);
                i--;
            } while (i < 0 || i >= n);
        }
    
    if(j < 0 || j >= m)
        {
            do
            {
                printf("Give y within parameters: ");
                scanf("%d", &j);
                j--;
            } while (j < 0 || j >= m);
        } 

    if(apar[i][j])
    {
    START1:
        printf("You have opened this square, give other coordinates:\nX:");
        scanf("%d", &i);
        i--;
        if(i < 0 || i >= n)
        do
        {
            printf("Give x within parameters: ");
            scanf("%d", &i);
            i--;
        } while (i < 0 || i >= n);
        printf("Y:");
        scanf("%d", &j);
        j--;
        if(j < 0 || j >= m)
        do
        {
            printf("Give y within parameters: ");
            scanf("%d", &j);
            j--;
        } while (j < 0 || j >= m);
        apar[i][j]++;
        if(apar[i][j])
            goto START1;
        appear(apar, pin);
    }
    else
    {
        apar[i][j] = '@';
        appear(apar, pin);
    }
}

void cheat(char* str, int** pin, int** apar)
{
    int i, j, count;

    count = sscanf(str, "cheat(%d,%d)", &i, &j);

    i--;
    j--;

    if(i < 0 || i >= n)
        {
            do
            {
                printf("Give x within parameters: ");
                scanf("%d", &i);
            } while (i <= 0 || i > n);
            i--;
        }
    
    if(j < 0 || j >= m)
        {
            do
            {
                printf("Give y within parameters: ");
                scanf("%d", &j);
            } while (j <= 0 || j > m);
            j--;
        }

    if(pin[i][j] == '@')
        printf("This square has: @\n\n");
    else if(pin[i][j] == 0)
        printf("This square has: .\n\n");
    else
        printf("This square has the number: %d\n\n", pin[i][j]);    
}

int anad(int** pin, int** apar, int x, int y)
{
    if(x < 0 || x >= n || y < 0 || y >= m)
        return 0;
    
    if(pin[x][y] > 0 && pin[x][y] <= 9)
    {
        if(!apar[x][y])
        apar[x][y]++;
        return 0;
    }
    
    if(pin[x][y] != 0)
        return 1;

    apar[x][y]++;
    pin[x][y] = 14;

    if((anad(pin, apar, (x-1), (y-1))) == 1)
        apar[x][y]++;

    if((anad(pin, apar, (x-1), y)) == 1)
        apar[x][y]++;

    if((anad(pin, apar, (x-1), (y+1))) == 1)
        apar[x][y]++;

    if((anad(pin, apar, x, (y-1))) == 1)
        apar[x][y]++;

    if((anad(pin, apar, x, (y+1))) == 1)
        apar[x][y]++;

    if((anad(pin, apar, (x+1), (y+1))) == 1)
        apar[x][y]++;

    if((anad(pin, apar, (x+1), y)) == 1)
        apar[x][y]++;

    if((anad(pin, apar, (x+1), (y+1))) == 1)
        apar[x][y]++;

}

int win(int** pin, int** apar)
{
    int i, j;

    for(i = 0; i < n; i++)
    {
        for(j =0 ; j < m; j++)
        {
            if(!apar[i][j] && pin[i][j] != '@')
                return 1;
            else
                continue;
        }
    }
    return 0;
}

int counter(int** apar)
{
    int i, j, sum = 0;

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
        {
            if(apar[i][j] && apar[i][j] != '@')
                sum++;
        }
    }
    return sum;
}