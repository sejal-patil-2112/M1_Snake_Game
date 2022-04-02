void Move()//This function is used to move the snake//
{
    int a,i;

    do
    {

        Food();
        fflush(stdin);

        len=0;

        for(i=0; i<30; i++)

        {

            body[i].x=0;

            body[i].y=0;

            if(i==length)

                break;

        }

        Delay(length);

        Boarder();

        if(head.direction==RIGHT)

            Right();

        else if(head.direction==LEFT)

            Left();

        else if(head.direction==DOWN)

            Down();

        else if(head.direction==UP)

            Up();

        ExitGame();

    }
    while(!kbhit());

    a=getch();

    if(a==27)

    {

        system("cls");

        exit(0);

    }
    key=getch();

    if((key==RIGHT&&head.direction!=LEFT&&head.direction!=RIGHT)||(key==LEFT&&head.direction!=RIGHT&&head.direction!=LEFT)||(key==UP&&head.direction!=DOWN&&head.direction!=UP)||(key==DOWN&&head.direction!=UP&&head.direction!=DOWN))

    {

        bend_no++;

        bend[bend_no]=head;

        head.direction=key;

        if(key==UP)

            head.y--;

        if(key==DOWN)

            head.y++;

        if(key==RIGHT)

            head.x++;

        if(key==LEFT)

            head.x--;

        Move();

    }

    else if(key==27)

    {

        system("cls");

        exit(0);

    }

    else

    {

        printf("\a");

        Move();

    }
}

void gotoxy(int x, int y)// This function allows you to print text in any place of screen.//
{

    COORD coord;

    coord.X = x;

    coord.Y = y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

}

void GotoXY(int x, int y)// This function allows you to print text in any place of screen.//
{
    HANDLE a;
    COORD b;
    fflush(stdout);
    b.X = x;
    b.Y = y;
    a = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(a,b);
}

void load()//This function is called before start the game//
{
    int row,col,r,c,q;
    gotoxy(36,14);
    printf("Loading...");
    gotoxy(30,15);
    for(r=1; r<=20; r++)
    {
        for(q=0; q<=100000000; q++); //to display the character slowly
        printf("%c",177);
    }
    getch();
}

void Down()//This function is used to go downward//
{
    int i;
    for(i=0; i<=(head.y-bend[bend_no].y)&&len<length; i++)
    {
        GotoXY(head.x,head.y-i);
        {
            if(len==0)
                printf("[]");
            else
                printf("[]");
        }
        body[len].x=head.x;
        body[len].y=head.y-i;
        len++;
    }
    Bend();
    if(!kbhit())
        head.y++;
}

void Delay(long double k)//This function delays the execution.//
{
    Score();
    long double i;
    for(i=0; i<=(10000000); i++);
}

void ExitGame()//This function exit the game//
{
    int i,check=0;
    for(i=4; i<length; i++) //starts with 4 because it needs minimum 4 element to touch its own body
    {
        if(body[0].x==body[i].x&&body[0].y==body[i].y)
        {
            check++;    //check's value increases as the coordinates of head is equal to any other body coordinate
        }
        if(i==length||check!=0)
            break;
    }
    if(head.x<=10||head.x>=70||head.y<=10||head.y>=30||check!=0)
    {
        life--;
        if(life>=0)
        {
            head.x=25;
            head.y=20;
            bend_no=0;
            head.direction=RIGHT;
            Move();
        }
        else
        {
            system("cls");
            printf("All Lives Completed\nBetter Luck Next Time!!!\nPress Any Key To Quit The Game\n");
            record();
            exit(0);
        }
    }
}

void Food()
{
    if(head.x==food.x&&head.y==food.y)
    {
        length++;
        time_t a;
        a=time(0);
        srand(a);
        food.x=rand()%70;
        if(food.x<=10)
            food.x+=11;
        food.y=rand()%30;
        if(food.y<=10)

            food.y+=11;
    }
    else if(food.x==0)/*to create food for the first time coz global variable are initialized with 0*/
    {
        food.x=rand()%70;
        if(food.x<=10)
            food.x+=11;
        food.y=rand()%30;
        if(food.y<=10)
            food.y+=11;
    }
}
void Left()//this function is used to move the snake to left//
{
    int i;
    for(i=0; i<=(bend[bend_no].x-head.x)&&len<length; i++)
    {
        GotoXY((head.x+i),head.y);
        {
            if(len==0)
                printf("[]");
            else
                printf("[]");
        }
        body[len].x=head.x+i;
        body[len].y=head.y;
        len++;
    }
    Bend();
    if(!kbhit())
        head.x--;

}

void Right()//this function is used to move the snake to right//
{
    int i;
    for(i=0; i<=(head.x-bend[bend_no].x)&&len<length; i++)
    {
        //GotoXY((head.x-i),head.y);
        body[len].x=head.x-i;
        body[len].y=head.y;
        GotoXY(body[len].x,body[len].y);
        {
            if(len==0)
                printf("[]");
            else
                printf("[]");
        }

void Boarder()
{
    system("cls");
    int i;
    GotoXY(food.x,food.y);   /*displaying food*/
    printf("F");
    for(i=10; i<71; i++)
    {
        GotoXY(i,10);
        printf("*");
        GotoXY(i,30);
        printf("*");
    }
    for(i=10; i<31; i++)
    {
        GotoXY(10,i);
        printf("*");
        GotoXY(70,i);
        printf("*");
    }
}

int Scoreonly()
{
    int score=Score();
    system("cls");
    return score;
}

int Score()//this function is used to check the score//
{
    int score;
    GotoXY(20,8);
    score=length-5;
    printf("SCORE : %d",(length-5));
    score=length-5;
    GotoXY(50,8);
    printf("Life : %d",life);
    return score;
}