#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
//#include "stdint.h"
//#include <stdbool.h>
#include <conio.h>
#include <string.h>
#include <math.h>

#define WANTRANDS 28
#define WANTROWS 35

typedef unsigned char      uint8_t;
typedef signed char        int8_t;
//游戏区域
//墙起始的X坐标
#define WALL_X_BEGIN 0
//墙结束的X坐标
#define WALL_X_END WANTRANDS + 1

//墙起始的Y坐标
#define WALL_Y_BEGIN 0
//墙结束的Y坐标
#define WALL_Y_END WANTROWS + 1

//边界区域，(游戏区域位于边界内)
#define MAX_RANDS 29
#define MAX_ROWS 50

//限制模式的最大生成食物数
#define limitFood_MAX 10
//限制模式下的最大游戏时间,一分钟
#define limitTime_MAX 60


typedef struct SnakeNode *SnakePoint;
//蛇的数据结构
typedef struct SnakeNode{
    //纵坐标为x即为行，横坐标为y即为列
    int pos_X;
    int pos_Y;
    //用于构造双向循环链表的指针
    SnakePoint next;
    SnakePoint previous;
}SnakeNode;

typedef struct FoodNode *FoodPoint;
//食物的数据结构
typedef struct FoodNode{
    //纵坐标为x即为行
    int pos_X;
    //横坐标为y即为列
    int pos_Y;
    //用于构造单向循环链表的指针
    FoodPoint next;
    //产生食物开始时间
    clock_t food_CreateBeginTime;
}FoodNode;

//蛇头指针
SnakePoint snakeHeadPoint = NULL;
//食物头指针
FoodPoint  foodHeadPoint = NULL;

//暂停游戏,默认为否
bool Pause = false;

//控制台坐标变量
COORD position;
//控制句柄
HANDLE myHandle;

//地图元素所代表的值
enum {Wall, Empty, SnakeHead, SnakeBody, Food} MapElem;
//各个方向所代表的值
enum {Up, Down, Left, Right} Direct;

//地图map[行][列]
int map[WANTRANDS + 2][WANTROWS + 2] = {Wall};

//游戏结束标记
bool GameOver;
//蛇的长度
unsigned snakeLength;
unsigned Score;
//游戏等级
int Level;
//前进速度
float Speed = 0.0;
//定义刷新频率数组,并赋默认值
int fps[11] = {0};


//要清空位置的坐标
int lastSnakeBody_X;
int lastSnakeBody_Y;
//是否要进行清空默认为是
bool isErase = true;
//吃到食物标记
bool isEatFood = false;
//对连续没吃到食物进行记数，超过规定个数GameOver
uint8_t dontEatCount = 0;
//最大生命数
uint8_t Live = 0;

//记录限制模式，当前地图总食物的数量
uint8_t limitFood_Count = 0;

//计时标记
//用于计时速度的时间区间
clock_t speed_BeginMarkTime;
clock_t speed_EndMarkTime;

//记录Pause操作所消耗的时间
clock_t pause_BeginMarkTime = 0;
clock_t pause_EndMarkTime = 0;
clock_t PauseWasteTime = 0;

//限制模式下的游戏开始时间标记
clock_t limitGame_BeginMarkTime = 0;
//限制模式下的当前游戏时间,为int类型因为不超过30秒。
int8_t limit_CurrentTime = 0;

//函数声明
void gameInit();
void mapInit();
void prepareGame();
void creatFood();
bool isCreatFood(clock_t currentTime, float liveTime);
bool isCreatFood_FoodCount();

void gotoxy(int x, int y);
void keyDownControl(int key);
void move1(const SnakePoint tmpSnakeHeadPoint, int oldHead_X, int oldHead_Y);
void move2(const SnakePoint tmpSnakeHeadPoint, int oldHead_X, int oldHead_Y);
void move(const SnakePoint tmpSnakeHeadPoint);
void moved_procces();
void changSnake(int oldHeadPos_X, int oldHeadPos_Y);
void isGameOver();
void isTimeOver();
void gainScore();
int setLevel();
void setFps();
void raiseLevel();
void speedCaclate();

void putOne();
void prepareShow();
void showFood();
void showSnake();
void showWall();
void showInfoBorder();
void showGameOver();
void showInvariableInfo();
void showVariableInfo();
void showLimitCurrentTime();
void show();

void releseSnake();
void startGame();
void game();

void mainMenuAndGameEnter();
void normalGame();
void limitTimeGame();
void perfectGame();
void crazyGame();
void showHelp();
void gameEnter(int);


//游戏初始化
void gameInit()
{
    //光标信息
    CONSOLE_CURSOR_INFO console_Info = {1, false};
    //获取控制台输出句柄
    myHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    //设置光标掩藏
    SetConsoleCursorInfo(myHandle, &console_Info);
    //设置控制台标题
    SetConsoleTitleA("贪吃蛇");
    //设置控制台文本属性
    SetConsoleTextAttribute(myHandle, 0x7);

    /*
        注意:如果设置窗口的大小大于屏幕缓冲区大小的话，设置窗口大小失败。
        COORD 的X和Y成员都是SHORT理论上他们的设置数值范围是0-32767，实际
        并非如此。X的范围是80到32766，Y的范围是25到32766，不在这个范围的
        话设置就失败了,rc设置为比XY小1，不然就设置失败了
    */

    //以下为设置窗口大小，以及位置
    //获取缓冲区信息
    COORD size = {100, 31};
    SMALL_RECT rc = {0, 0, 100 - 1, 31 - 1};
    //设置窗口缓冲区大小
    SetConsoleScreenBufferSize(myHandle, size);
    //设置窗口大小
    SetConsoleWindowInfo(myHandle, 1, &rc);

    //新建蛇链表头节点
    snakeHeadPoint = (SnakePoint)malloc(sizeof(SnakeNode));
    //新建食物链表头节点
    foodHeadPoint = (FoodPoint)malloc(sizeof(FoodNode));
}

//初始化地图,游戏区域置空,以及进行初始化打印，显示地图背景色
void mapInit()
{
    for(int i = WALL_X_BEGIN + 1; i < WALL_X_END; ++i)
    {
        for(int j = WALL_Y_BEGIN + 1; j < WALL_Y_END; ++j)
        {
            map[i][j] = Empty;
            //已一个字符为单位打印
            //putOne(i, j, map[i][j]);
        }
        //以一行为单位打印
        gotoxy(i, 1);
        SetConsoleTextAttribute(myHandle, 0x[[濮撳悕宸茶劚鏁廬宸茶劚鏁廬);
        printf("%70s", " ");
    }
}

//游戏开始之前的准备工作
void prepareGame()
{
    //初始化地图
    mapInit();
    //初始蛇运行方向为向左
    Direct = Left;
    //游戏开关为开
    GameOver = false;
    //蛇的初始长度
    snakeLength = 2;
    //分数清零
    Score = 0;
    //速度重置
    Speed = 0.0;
    //等级重置
    Level = 0;
    //最大生命数
    Live = 3;
    //初始化限制模式的食物总数
    limitFood_Count = 0;
    //初始化限制模式下的当前游戏时间
    limit_CurrentTime = 0;

    //初始化蛇头出现的坐标
    srand((unsigned)time(NULL));
    snakeHeadPoint->pos_X = (WALL_X_END - WALL_X_BEGIN) / 2 - 2 + rand() % 5;
    snakeHeadPoint->pos_Y = (WALL_Y_END - WALL_Y_BEGIN) / 2 - 4 + rand() % 9;
    //在地图上标记此坐标为蛇头位置
    map[snakeHeadPoint->pos_X][snakeHeadPoint->pos_Y] = SnakeHead;
    //生成第一节蛇身
    SnakePoint snakeBodyPoint = (SnakePoint)malloc(sizeof(SnakeNode));
    //根据蛇的初始运动方向，在蛇头位置的后一个位置加一个蛇身节点
    snakeBodyPoint->pos_X = snakeHeadPoint->pos_X;
    snakeBodyPoint->pos_Y = snakeHeadPoint->pos_Y + 1;
    //在地图上标记此坐标为蛇身位置
    map[snakeBodyPoint->pos_X][snakeBodyPoint->pos_Y] = SnakeBody;

    //将蛇头与蛇身链接为一条长度为2的蛇
    snakeHeadPoint->next = snakeBodyPoint;
    snakeHeadPoint->previous = snakeBodyPoint;
    snakeBodyPoint->next = snakeHeadPoint;
    snakeBodyPoint->previous = snakeHeadPoint;
    //生成食物
    creatFood();
}

//创造食物
void creatFood()
{
    //创造食物，食物必须出现在没有被占用的坐标
    do{
        //限定出现的坐标只能在墙的范围内
        foodHeadPoint->pos_X = rand() % (WALL_X_END - WALL_X_BEGIN - 1) + (WALL_X_BEGIN + 1);
        foodHeadPoint->pos_Y = rand() % (WALL_Y_END - WALL_Y_BEGIN - 1) + (WALL_Y_BEGIN + 1);
    }while(map[foodHeadPoint->pos_X][foodHeadPoint->pos_Y] != Empty);
    //在地图将此坐标进行标记
    map[foodHeadPoint->pos_X][foodHeadPoint->pos_Y] = Food;
    //记录产生苹果的时间
    foodHeadPoint->food_CreateBeginTime = clock();

    //食物数加1
    ++limitFood_Count;
}

//定位坐标
void gotoxy(int x, int y)
{
    //将控制台系统坐标，与map[行][列]坐标相对应
    position.X = 2 * y;
    position.Y = x;
    SetConsoleCursorPosition(myHandle, position);
}

//定位坐标以及根据数组的值输出该元素
void putOne(int x, int y, int mapElem)
{
    switch(mapElem)
    {
        //为空
        case Empty:
            gotoxy(x, y);
            SetConsoleTextAttribute(myHandle, 0x[[濮撳悕宸茶劚鏁廬宸茶劚鏁廬);
            printf("%2s", " ");break;
        //蛇头节点
        case SnakeHead:
            gotoxy(x, y);
            SetConsoleTextAttribute(myHandle, 0x2C);
            printf("■");break;
        //蛇身
        case SnakeBody:
            gotoxy(x, y);
            SetConsoleTextAttribute(myHandle, 0x29);
            printf("■");break;
        //食物
        case Food:
            gotoxy(x, y);
            SetConsoleTextAttribute(myHandle, 0x2E);
            printf("○");break;
        //墙
        case Wall:
            gotoxy(x, y);
            SetConsoleTextAttribute(myHandle, 0xD);
            printf("□");break;
    }
}

//限制模式所用的移动函数

//移动函数，确定采用哪种移动算法
void move(const SnakePoint tmpSnakeHeadPoint)
{
    int key = -1; //设为-1，不需要处理的数
    //有键按下,处理按键
    while(kbhit())
    {
        //同时按下多个键，取最后一个
        key = getch();
    }

    /*
    while(kbhit)
        keyDownControl(key);
        如果采用这种方式，在同时按下运行方向不在同一方向(不相同和不相反)
        和相反方向时回出现GameOver现象，如，向上前进，同时按下左，和按下
        下，因为时间很短所以kbhit返回1，按照循环接收这两个按键，如果先接
        收向左的按键，那么前进方向改为，向左，然后接收向右。注意原本接收相
        反按键是不进行操作的，而有了前一个步骤，这里实际上是往相反方向运动
        而自然蛇头之后即为蛇身，它遇到了自身，通过碰撞检测，判定为GameOver
    */

    keyDownControl(key);
    //如果暂停状态必须不能进行一切除了处理暂停的处理
    if(Pause)
    {
        return;
    }
    //先记录蛇头节点坐标，因为之后要进行更改
    int oldHead_X = tmpSnakeHeadPoint->pos_X;
    int oldHead_Y = tmpSnakeHeadPoint->pos_Y;
    //按方向进行移动处理
    switch(Direct){
        //向上移动
        case Up:
            --tmpSnakeHeadPoint->pos_X;break;
        //向下移动
        case Down:
            ++tmpSnakeHeadPoint->pos_X;break;
        //向左移动
        case Left:
            --tmpSnakeHeadPoint->pos_Y;break;
        //向右移动
        case Right:
            ++tmpSnakeHeadPoint->pos_Y;break;
        }

        //碰撞检测
        isGameOver();
        if(GameOver)
            return;

        //随着蛇长度的增加，判断用哪个移动算法
        if(snakeLength <= [[濮撳悕宸茶劚鏁廬宸茶劚鏁廬)
        {
            move1(tmpSnakeHeadPoint, oldHead_X, oldHead_Y);
        }
        else{
            move2(tmpSnakeHeadPoint, oldHead_X, oldHead_Y);
        }

        //标记为蛇头
        map[tmpSnakeHeadPoint->pos_X][tmpSnakeHeadPoint->pos_Y] = SnakeHead;
}

void moved_procces()
{
    //如果暂停状态必须不能进行一切除了处理暂停的处理
    if(Pause)
    {
        return;
    }

    //计算合理的食物存在时间，从地图对角线需要移动的次数除以当前单位时间移动,加0.2秒校正误差
    float suitLiveFoodTime = sqrtf((float)(WANTROWS * WANTROWS + WANTRANDS * WANTRANDS))
                                / Speed * 10 + 0.1;
    if(isEatFood)
    {
        //产生新食物
        creatFood();
        //吃到食物将记数清零
        dontEatCount = 0;
        //总食物数减1
        --limitFood_Count;
    }

    else if(isCreatFood(clock(), suitLiveFoodTime))
    {
        //将此食物擦除
        map[foodHeadPoint->pos_X][foodHeadPoint->pos_Y] = Empty;
        putOne(foodHeadPoint->pos_X, foodHeadPoint->pos_Y,
                map[foodHeadPoint->pos_X][foodHeadPoint->pos_Y]);
        creatFood();

        ++dontEatCount;
        //记数超过三个游戏结束
        if(dontEatCount > Live)
        {
            dontEatCount = 0;
            GameOver = true;
        }
    }
}

//限制模式下的移动后处理
void moved_procces_Limit()
{
    //如果暂停状态必须不能进行一切除了处理暂停的处理
    if(Pause)
    {
        return;
    }

    if(isEatFood)
    {
        //产生新食物
        creatFood();
        //吃到食物将记数清零
        dontEatCount = 0;
        //总食物数减1
        --limitFood_Count;
    }
    else if(isCreatFood_FoodCount())
    {
        creatFood();
    }
}

//根据当前食物总数确认是否产生食物,用于限制模式
bool isCreatFood_FoodCount()
{
    if(limitFood_Count < limitFood_MAX)
        return true;
    return false;
}

//根据当前时间以及生存时间判断是否产生食物
bool isCreatFood(clock_t currentTime, float liveTime)
{
    //食物只存在一定的时间,减去暂停时期所消耗的时间，来修正暂停时食物存留时间不合理的问题
    bool result = (((currentTime - foodHeadPoint->food_CreateBeginTime - PauseWasteTime) /
                        (float)CLOCKS_PER_SEC) > liveTime);
    return result;
}

//另一种移动算法，每次通过增加节点以及删除最后一个节点来来实现移动
//如果吃到食物则不进行删除操作
void move2(const SnakePoint tmpSnakeHeadPoint, int oldHead_X, int oldHead_Y)
{
    SnakePoint newSnakeBody = (SnakePoint)malloc(sizeof(SnakeNode));
    //定义其坐标
    newSnakeBody->pos_X = oldHead_X;
    newSnakeBody->pos_Y = oldHead_Y;

    //将它链入蛇的双向链表中
    tmpSnakeHeadPoint->next->previous = newSnakeBody;
    newSnakeBody->next = tmpSnakeHeadPoint->next;
    tmpSnakeHeadPoint->next = newSnakeBody;
    newSnakeBody->previous = tmpSnakeHeadPoint;
    //标记它的位置为蛇身
    map[newSnakeBody->pos_X][newSnakeBody->pos_Y] = SnakeBody;

    //如果没有吃到食物删除最后一个节点
    if(map[tmpSnakeHeadPoint->pos_X][tmpSnakeHeadPoint->pos_Y] != Food)
    {
        SnakePoint tmpLastSnake = tmpSnakeHeadPoint->previous;

        //记录需要擦除的坐标
        lastSnakeBody_X = tmpLastSnake->pos_X;
        lastSnakeBody_Y = tmpLastSnake->pos_Y;
        //更改此位置标记
        map[tmpLastSnake->pos_X][tmpLastSnake->pos_Y] = Empty;

        //在删除节点之前改变蛇头节点的前驱，以及倒数第二个节点的后继
        tmpSnakeHeadPoint->previous = tmpLastSnake->previous;
        tmpLastSnake->previous->next = tmpLastSnake->next;
        //释放掉最后一个节点
        free(tmpLastSnake);

        //进行应有的标记
        isEatFood = false;
        //擦除标记
        isErase = true;
    }
    //吃到食物进行应有的标记
    else{
        //蛇的长度加1
        ++snakeLength;
        //不进行擦除
        isErase = false;
        //吃到食物
        isEatFood = true;
    }
}

//进行移动所做的操作
void move1(const SnakePoint tmpSnakeHeadPoint, int oldHead_X, int oldHead_Y)
{
        //如果吃到食物，通过在蛇头之后插入一个节点实现蛇节点增加，其他节点不做操作
        if(map[tmpSnakeHeadPoint->pos_X][tmpSnakeHeadPoint->pos_Y] == Food)
        {
            //建立新节点
            SnakePoint newSnakeBody = (SnakePoint)malloc(sizeof(SnakeNode));
            //定义其坐标
            newSnakeBody->pos_X = oldHead_X;
            newSnakeBody->pos_Y = oldHead_Y;
            //将它链入蛇的双向链表中
            tmpSnakeHeadPoint->next->previous = newSnakeBody;
            newSnakeBody->next = tmpSnakeHeadPoint->next;
            tmpSnakeHeadPoint->next = newSnakeBody;
            newSnakeBody->previous = tmpSnakeHeadPoint;
            //标记它的位置为蛇身
            map[newSnakeBody->pos_X][newSnakeBody->pos_Y] = SnakeBody;

            //蛇的长度加1
            ++snakeLength;
            //不进行擦除
            isErase = false;
            //吃到食物
            isEatFood = true;
        }

        else
        {
            //没吃到食物不增加和删除节点，通过改变各节点的坐标来实现移动
            changSnake(oldHead_X, oldHead_Y);
            isEatFood = false;
        }
}

//依次更改蛇链表中各节点的坐标，除了蛇头
void changSnake(int oldHeadPos_X, int oldHeadPos_Y)
{
    //创建一个临时头指针
    SnakePoint lastSnakeBody = snakeHeadPoint->previous;
    /*在改变最后一个蛇身节点的坐标时，先用此坐标将此位置
      标记为空，标记为空还是不够的，因为在这个坐标之前已
      经被打印出来了。而没有清屏所以它一直显示之前打印的
      标记，所以要重新将它清空，通过打印此坐标现有标记实
      现，因为此节点要往前移，通过更改坐标实现
    */

    //记录最后一个节点的坐标，因为待会要通过这个坐标进行清空此位置标记
    lastSnakeBody_X = lastSnakeBody->pos_X;
    lastSnakeBody_Y = lastSnakeBody->pos_Y;
    map[lastSnakeBody->pos_X][lastSnakeBody->pos_Y] = Empty;
    //因为吃到食物仅一次，需要重新标记清除状态
    isErase = true;
    //这里进行清空的话会造成蛇尾闪烁
    //putOne(lastSnakeBody_X, lastSnakeBody_Y, map[lastSnakeBody_X][lastSnakeBody_Y]);

    //从最后一个依次向前将其坐标置为前一个坐标,直到第一个蛇身节点(不是蛇头)
    while(lastSnakeBody != snakeHeadPoint->next)
    {
        //尾巴节点
        lastSnakeBody->pos_X = lastSnakeBody->previous->pos_X;
        lastSnakeBody->pos_Y = lastSnakeBody->previous->pos_Y;
        lastSnakeBody = lastSnakeBody->previous;
    }

    //改变第二个节点即第一个蛇身节点的坐标为旧蛇头坐标
    snakeHeadPoint->next->pos_X = oldHeadPos_X;
    snakeHeadPoint->next->pos_Y = oldHeadPos_Y;
    //标记为蛇身
    map[oldHeadPos_X][oldHeadPos_Y] = SnakeBody;
}

//处理键盘事件
void keyDownControl(int key)
{
    //暂停/解除暂停注：(int)'P' = 80冲突
    if(key == 'p')
    {
        /*
            因为暂停操作比较特殊，按下暂停，如果想继续游戏的话必须再按一次解除
            当前状态，所以当开始标记时间不为初始值时必定按下了暂停键，而进行判断
            开始时间必须为零的时刻，程序必定处于再次按下暂停键的状态。对标记时间
            赋值的先后顺序很重要，也许会造成一定的时间误差，但并不值得注意
        */
        Pause = !Pause;
        if(pause_BeginMarkTime != 0)
        {
            pause_EndMarkTime = clock();
            PauseWasteTime = pause_EndMarkTime - pause_BeginMarkTime;
            //将两个时间标记重新初始化
            pause_BeginMarkTime = pause_EndMarkTime = 0;
        }
        else
            pause_BeginMarkTime = clock();
    }

    //记录当前前进方向
    int currentDirect = Direct;
    //根据按键定义前进方向
    switch(key){
        case 'w':
        case 'W':
        case '8':
        case  72:
            if(currentDirect == Down)
                break;
            Direct = Up;break;
        case 's':
        case 'S':
        case '2':
        case  80:
            if(currentDirect == Up)
                break;
            Direct = Down;break;
        case 'a':
        case 'A':
        case '4':
        case  75:
            if(currentDirect == Right)
                break;
            Direct = Left;break;
        case 'd':
        case 'D':
        case '6':
        case  77:
            if(currentDirect == Left)
                break;
            Direct = Right;break;
        default:
            break;
    }
}

//碰撞检测
void isGameOver()
{
    //当蛇头碰到墙及自身时游戏标记为结束
    if(snakeHeadPoint->pos_X == WALL_X_BEGIN ||
       snakeHeadPoint->pos_X == WALL_X_END   ||
       snakeHeadPoint->pos_Y == WALL_Y_BEGIN ||
       snakeHeadPoint->pos_Y == WALL_Y_END   ||
       map[snakeHeadPoint->pos_X][snakeHeadPoint->pos_Y] == SnakeBody)
        GameOver = true;
}

//限制模式下判断时间是否用完了
void isTimeOver()
{
    //判断是否为第一次时间校验，只允许一次
    static bool oneTimeCheck = false;

    //如果为暂停则跳出计时处理，之后在减去暂停时间消耗
    if(Pause)
    {
        //当暂停时将一次时间校验设为否，因为每暂停一次，就需要校验一次
        oneTimeCheck = false;
        return;
    }
    if(!oneTimeCheck)
    {
        //一次时间校验,通过在一次暂停操作后修正开始时间来消除暂停对计时的影响
        limitGame_BeginMarkTime += PauseWasteTime;
        oneTimeCheck = true;
    }
    //一次时间校验后以正常计时模式
    limit_CurrentTime = (int8_t)((clock() - limitGame_BeginMarkTime) / (float)CLOCKS_PER_SEC);

    //当达到限定时间时，游戏结束
    if(limit_CurrentTime > limitTime_MAX)
    {
        limit_CurrentTime = 0;
        GameOver = true;
    }
}

//评分机制,随便定的，也许并不合理
void gainScore()
{
    //根据蛇长度的增加给予相应的分数
    if(snakeLength % 5 == 0)
    {
        switch(snakeLength / 5)
        {
            case 0:
                Score += 0;break;
            case 1:
            case 2:
            case 3:
                Score += 50;break;
            case 4:
            case 5:
            case 6:
                Score += 100;break;
            case 7:
            case 8:
                Score += 150;break;
            case 10:
            case 12:
                Score += 400;break;
            case 14:
            case 16:
                Score += 700;break;
            case 18:
                Score += 1100;break;
            case [[濮撳悕宸茶劚鏁廬宸茶劚鏁廬:
                Score += 1500;break;
            default:
                Score += 3000;
        }
    }
    //不符合以上条件时，每吃一个食物加等级10倍分数
    else{
        Score = Score + (Level + 1) * 10;
    }
}


void speedCaclate()
{
    //目的是用于统计一秒钟内程序刷新的次数
    static int count = 0;
    //当开始计数和重新开始计数时，记录当前时间为开始时间
    if(!count)
        speed_BeginMarkTime = clock();
    ++count;
    speed_EndMarkTime = clock();
    if((speed_EndMarkTime - speed_BeginMarkTime - setLevel()) >= 1.0 * CLOCKS_PER_SEC )
    {
        //为了好看，在次数上*10
        Speed = (float)count * 10.0;
        count = 0;
    }
}

//提升等级，共0~10级
void raiseLevel()
{
    //当蛇长度小于50时，每隔10个升一级，当大于五十时每隔8个升一级
    if(snakeLength <= 50)
    {
        if((snakeLength % 10 == 0) && (snakeLength / 10 != 0))
            ++Level;
    }
    else if(snakeLength <= 90)
    {
        if(((snakeLength - 50) % 8 == 0) && ((snakeLength - 50) / 8 != 0))
            ++Level;
    }

    else
    {

    }
}

//根据用户输入设置刷新频率的大小
void setFps()
{
    system("cls");
    int Fps = 0;
    gotoxy((MAX_RANDS - WALL_X_BEGIN) / 2 - 1, (MAX_ROWS - WALL_Y_BEGIN) / 2 - 4);
    SetConsoleTextAttribute(myHandle, 0xC);
    printf("输入游戏速度：(100 - 600)(越低越快)");
    gotoxy((MAX_RANDS - WALL_X_BEGIN) / 2, (MAX_ROWS - WALL_Y_BEGIN) / 2 - 7);
    printf("配置比较低的机器，尽量选低些，此选择可用于适应机器");
    gotoxy((MAX_RANDS - WALL_X_BEGIN) / 2 + 1, (MAX_ROWS - WALL_Y_BEGIN) / 2 - 4);
    printf("Input:  ");
    scanf("%d", &Fps);
    //清空输入缓冲区
    fflush(stdin);
    //清空界面
    system("cls");

    if(Fps < [[濮撳悕宸茶劚鏁廬宸茶劚鏁廬0)
    {
        int tmpFps[11] = {110, 100, 90, 80, 70, 60, 50, 40, 30, [[濮撳悕宸茶劚鏁廬宸茶劚鏁廬, 15};
        //数组拷贝
        memcpy(fps, tmpFps, sizeof(int)*11);
    }
    else if( Fps < 300)
    {
        int tmpFps[11] = {[[濮撳悕宸茶劚鏁廬宸茶劚鏁廬0, 170, 150, 130, 110, 100, 80, 70, 60, 50, [[濮撳悕宸茶劚鏁廬宸茶劚鏁廬};
        //数组拷贝
        memcpy(fps, tmpFps, sizeof(int)*11);
    }
    else if(Fps < 400)
    {
        int tmpFps[11] = {300, 250, [[濮撳悕宸茶劚鏁廬宸茶劚鏁廬0, 150, 1[[濮撳悕宸茶劚鏁廬宸茶劚鏁廬, 110, 100, 90, 80, 70, 40};
        memcpy(fps, tmpFps, sizeof(int)*11);
    }
    else if(Fps < 500)
    {
        int tmpFps[11] = {400, 300, 250, [[濮撳悕宸茶劚鏁廬宸茶劚鏁廬0, 150, 130, 1[[濮撳悕宸茶劚鏁廬宸茶劚鏁廬, 110, 90, 80, 60};
        memcpy(fps, tmpFps, sizeof(int)*11);
    }
    else if(Fps < 600)
    {
        int tmpFps[11] = {500, 400, 300, [[濮撳悕宸茶劚鏁廬宸茶劚鏁廬0, 180, 160, 140, 1[[濮撳悕宸茶劚鏁廬宸茶劚鏁廬, 110, 100, 70};
        memcpy(fps, tmpFps, sizeof(int)*11);
    }
    else if(Fps < 700)
    {
        int tmpFps[11] = {600, 5[[濮撳悕宸茶劚鏁廬宸茶劚鏁廬, 450, 360, 300, 2[[濮撳悕宸茶劚鏁廬宸茶劚鏁廬, 180, 150, 130, 110, 90};
        memcpy(fps, tmpFps, sizeof(int)*11);
    }
    else
    {
        //默认
        int tmpFps[11] = {110, 100, 90, 80, 70, 60, 50, 40, 30, [[濮撳悕宸茶劚鏁廬宸茶劚鏁廬, 10};
        //数组拷贝
        memcpy(fps, tmpFps, sizeof(int)*11);
    }
}

//游戏等级设置,返回系统睡眠时间
int setLevel()
{
    switch(Level)
    {
        case 0:
            return fps[0];
        case 1:
            return fps[1];
        case 2:
            return fps[2];
        case 3:
            return fps[3];
        case 4:
            return fps[4];
        case 5:
            return fps[5];
        case 6:
            return fps[6];
        case 7:
            return fps[7];
        case 8:
            return fps[8];
        case 9:
            return fps[9];
        case 10:
            return fps[9];
        default:
            return 0;
    }
}

//显示蛇
void showSnake()
{
    /*
        蛇每次移动只改变的只有蛇头节点，和第一个蛇身节点，而蛇尾节点由擦除函数进行处理
        所以每次只需要将这几个节点更新显示即可
    */

    //临时头节点，为了不改变头节点的指向
    SnakePoint tmpSnakeHeadPoint = snakeHeadPoint;
    //先显示头节点
    putOne(snakeHeadPoint->pos_X, snakeHeadPoint->pos_Y,
           map[snakeHeadPoint->pos_X][snakeHeadPoint->pos_Y]);
    //在显示蛇头后面的一个蛇身节点
    putOne(snakeHeadPoint->next->pos_X, snakeHeadPoint->next->pos_Y,
           map[snakeHeadPoint->next->pos_X][snakeHeadPoint->next->pos_Y]);


    //如果每次更新显示所有节点，那么移动速度会随着蛇长度的增加而减慢，
    //原因是打印整条蛇需要花一定的时间
    /*
    //然后依次显示其他节点
    while(tmpSnakeHeadPoint->next != snakeHeadPoint)
    {
        putOne(tmpSnakeHeadPoint->next->pos_X, tmpSnakeHeadPoint->next->pos_Y,
           map[tmpSnakeHeadPoint->next->pos_X][tmpSnakeHeadPoint->next->pos_Y]);
        tmpSnakeHeadPoint = tmpSnakeHeadPoint->next;
    }
    */
}

//每次移动后，擦出地图上已不是蛇身节点的标记
void eraseSnakeBody()
{
    putOne(lastSnakeBody_X, lastSnakeBody_Y, map[lastSnakeBody_X][lastSnakeBody_Y]);
}

//显示食物
void showFood()
{
    static unsigned downCount = 6;
    //实现闪烁效果,如果不需要闪烁的话，去掉后两句即可
    putOne(foodHeadPoint->pos_X, foodHeadPoint->pos_Y,
           map[foodHeadPoint->pos_X][foodHeadPoint->pos_Y]);

    for(int i = 0; i < downCount; ++i)
        putOne(foodHeadPoint->pos_X, foodHeadPoint->pos_Y, Empty);
    putOne(foodHeadPoint->pos_X, foodHeadPoint->pos_Y,
           map[foodHeadPoint->pos_X][foodHeadPoint->pos_Y]);
}

//显示墙
void showWall()
{
    //显示上下两面墙
    for(int j = WALL_Y_BEGIN; j <= WALL_Y_END; ++j)
    {
        putOne(WALL_X_BEGIN, j, map[WALL_X_BEGIN][j]);
        putOne(WALL_X_END, j, map[WALL_X_END][j]);
    }
   //显示左右两面墙
    for(int i = WALL_X_BEGIN; i <= WALL_X_END; ++i)
    {
        putOne(i, WALL_Y_BEGIN, map[i][WALL_Y_BEGIN]);
        putOne(i, WALL_Y_END, map[i][WALL_Y_END]);
    }

}

//显示游戏结束信息
void showGameOver()
{
    for(int i = WALL_X_BEGIN + 1; i < WALL_X_END; ++i)
        for(int j = WALL_Y_BEGIN + 1; j < WALL_Y_END; ++j)
            putOne(i, j, Wall);
    gotoxy((WALL_X_END - WALL_X_BEGIN) / 2 - 1, (WALL_Y_END - WALL_Y_BEGIN) / 2 - 4);
    SetConsoleTextAttribute(myHandle, 0xC);
    printf("Game Over!");
    gotoxy((WALL_X_END - WALL_X_BEGIN) / 2 + 1, (WALL_Y_END - WALL_Y_BEGIN) / 2 - 5);
    printf("重新开始？(Y/N)Y");

    //清除输入缓冲区
    while(kbhit())
        getch();
}

//显示信息框
void showInfoBorder()
{
    //第一个框
    //显示上下边界
    for(int j = WALL_Y_END + 2; j <= MAX_ROWS - 2; ++j)
    {
        putOne(WALL_X_BEGIN +2, j, Wall);
        putOne(WALL_X_BEGIN +2 + 5, j, Wall);
    }
   //显示左右边界
    for(int i = WALL_X_BEGIN +2; i <= WALL_X_BEGIN + 2 + 5; ++i)
    {
        putOne(i, WALL_Y_END + 2, Wall);
        putOne(i, MAX_ROWS - 2, Wall);
    }

    //第二个框
    //显示上下边界
    for(j = WALL_Y_END + 2; j <= MAX_ROWS - 2; ++j)
    {
        putOne(WALL_X_BEGIN +2 * 2 + 5, j, Wall);
        putOne(WALL_X_BEGIN +2 * 2 + 5 * 2, j, Wall);
    }
   //显示左右边界D
    for(i = WALL_X_BEGIN + 2 * 2 + 5; i <= WALL_X_BEGIN + 2 * 2 + 5 * 2; ++i)
    {
        putOne(i, WALL_Y_END + 2, Wall);
        putOne(i, MAX_ROWS - 2, Wall);
    }

    //第三个框
    //显示上下边界
    for(j = WALL_Y_END + 2; j <= MAX_ROWS - 2; ++j)
    {
        putOne(WALL_X_BEGIN +2 * 3 + 5 * 2, j, Wall);
        putOne(WALL_X_BEGIN +2 * 3 + 5 * 3, j, Wall);
    }
   //显示左右边界
    for(i = WALL_X_BEGIN + 2 * 3 + 5 * 2; i <= WALL_X_BEGIN + 2 * 3 + 5 * 3; ++i)
    {
        putOne(i, WALL_Y_END + 2, Wall);
        putOne(i, MAX_ROWS - 2, Wall);
    }

    //第四个框
    //显示上下边界
    for(j = WALL_Y_END + 2; j <= MAX_ROWS - 2; ++j)
    {
        putOne(WALL_X_BEGIN +2 * 4 + 5 * 3, j, Wall);
        putOne(WALL_X_BEGIN +2 * 4 + 5 * 4, j, Wall);
    }
   //显示左右边界D
    for(i = WALL_X_BEGIN + 2 * 4 + 5 * 3; i <= WALL_X_BEGIN + 2 * 4 + 5 * 4; ++i)
    {
        putOne(i, WALL_Y_END + 2, Wall);
        putOne(i, MAX_ROWS - 2, Wall);
    }
}

//显示时刻改变的信息
void showVariableInfo()
{
    //显示分数信息
    gotoxy(WALL_X_BEGIN + 2 + 2, WALL_Y_END + 2 + 2);
    SetConsoleTextAttribute(myHandle, 0xE);
    printf("SCORE: %d", Score);
    gotoxy(WALL_X_BEGIN + 2 + 4, WALL_Y_END + 2 + 2);
    printf("SPEED: %7.3f", Speed);

    //显示蛇的长度
    gotoxy(WALL_X_BEGIN +2 * 2 + 5 + 1, WALL_Y_END + 2 + 2);
    SetConsoleTextAttribute(myHandle, 0xE);
    printf("LENGTH: %d", snakeLength);
    //显示连续每吃到食物的记数
    gotoxy(WALL_X_BEGIN +2 * 2 + 5 + 2, WALL_Y_END + 2 + 2);
    printf("死亡记数: %d", dontEatCount);
    //显示等级
    gotoxy(WALL_X_BEGIN +2 * 2 + 5 + 3, WALL_Y_END + 2 + 2);
    printf("Level: %d", Level);
    gotoxy(WALL_X_BEGIN +2 * 2 + 5 + 4, WALL_Y_END + 2 + 2);
    printf("FPS: %d  ", fps[Level]);
}

//显示限制模式当前游戏时间
void showLimitCurrentTime()
{
    gotoxy(WALL_X_BEGIN + 2 + 3, WALL_Y_END + 2 + 2);
    SetConsoleTextAttribute(myHandle, 0xE);
    printf("Time: %d", limit_CurrentTime);
}

void showInvariableInfo()
{
    //显示帮助信息
    gotoxy(WALL_X_BEGIN +2 * 3 + 5 * 2 + 1, WALL_Y_END + 2 + 1);
    SetConsoleTextAttribute(myHandle, 0xA);
    printf("控制：");
    printf("向上: ↑/W/8");
    gotoxy(WALL_X_BEGIN +2 * 3 + 5 * 2 + 2, WALL_Y_END + 2 + 2);
    printf("向下: ↓/s/2");
    gotoxy(WALL_X_BEGIN +2 * 3 + 5 * 2 + 3, WALL_Y_END + 2 + 2);
    printf("向左: ←/A/4");
    gotoxy(WALL_X_BEGIN +2 * 3 + 5 * 2 + 4, WALL_Y_END + 2 + 1);
    printf("向右: →/D/6 暂停P");

    //显示其他信息
    gotoxy(WALL_X_BEGIN +2 * 4 + 5 * 3 + 1, WALL_Y_END + 2 + 1);
    SetConsoleTextAttribute(myHandle, 0xC);
    printf("说明：死亡记数超过");
    gotoxy(WALL_X_BEGIN +2 * 4 + 5 * 3 + 2, WALL_Y_END + 2 + 2);
    printf("%d GameOver !", Live);
    gotoxy(WALL_X_BEGIN +2 * 4 + 5 * 3 + 3, WALL_Y_END + 2 + 2);
    SetConsoleTextAttribute(myHandle, 0xA);
    printf("BY : WOA");
    gotoxy(WALL_X_BEGIN +2 * 4 + 5 * 3 + 4, WALL_Y_END + 2 + 2);
    printf("Version : 1.1");
}

//只有每次重新游戏时进行显示即可
void prepareShow()
{
    showWall();
    showInfoBorder();
    showInvariableInfo();
}

void show()
{
    showSnake();
    //再蛇显示之后再进行擦除，可以保证蛇尾不闪烁
    if(isErase && !Pause)
        eraseSnakeBody();
    showFood();
    showVariableInfo();
}

//注意，这里为暴力删除，如果要进行删除一个节点的操作的话请不要参考此方法
void releseSnake()
{
    SnakePoint tmpSnakeLast = snakeHeadPoint->previous;
    while(tmpSnakeLast != snakeHeadPoint)
    {
        //记录此节点
        SnakePoint tmpSnakeBody = tmpSnakeLast;
        //记录此节点的前驱，用于前移，并没有进行修正指向操作
        tmpSnakeLast = tmpSnakeLast->previous;
        //释放当前节点
        free(tmpSnakeBody);
    }
    //初始化蛇头指针
    snakeHeadPoint->previous = snakeHeadPoint->next = NULL;
}

//开始游戏
void startGame()
{
    do{
        show();
        Sleep(setLevel());
        move(snakeHeadPoint);
        moved_procces();
        speedCaclate();
        if(isEatFood && !Pause)
        {
            gainScore();
            raiseLevel();
        }

        if(GameOver)
            showGameOver();
    }while(!GameOver);
}

//显示主菜单的功能选项
void mainMenuAndGameEnter()
{
    system("cls");
    //清空输入缓冲
    fflush(stdin);
    //所选择的选项代表的值
    static int press = 1;
    //记录是否按下确认键
    bool enterGame = false;
    //主菜单
    gotoxy((MAX_RANDS - WALL_X_BEGIN) / 2 - 6, (MAX_ROWS - WALL_Y_BEGIN) / 2 - 4);
    SetConsoleTextAttribute(myHandle, 0xE);
    printf("*   MENU   *");
    gotoxy((MAX_RANDS - WALL_X_BEGIN) / 2 - 4, (MAX_ROWS - WALL_Y_BEGIN) / 2 - 3);
    printf(" 正常模式");
    gotoxy((MAX_RANDS - WALL_X_BEGIN) / 2 - 2, (MAX_ROWS - WALL_Y_BEGIN) / 2 - 3);
    printf(" 限时模式");
    gotoxy((MAX_RANDS - WALL_X_BEGIN) / 2 - 0, (MAX_ROWS - WALL_Y_BEGIN) / 2 - 3);
    printf(" 完美模式");
    gotoxy((MAX_RANDS - WALL_X_BEGIN) / 2 + 2, (MAX_ROWS - WALL_Y_BEGIN) / 2 - 3);
    printf(" 暴走模式");
    gotoxy((MAX_RANDS - WALL_X_BEGIN) / 2 + 4, (MAX_ROWS - WALL_Y_BEGIN) / 2 - 3);
    printf(" 游戏帮助");
    gotoxy((MAX_RANDS - WALL_X_BEGIN) / 2 + 6, (MAX_ROWS - WALL_Y_BEGIN) / 2 - 3);
    printf(" 退出游戏");

    //先进行第一次显示,即在没有按下键时先显示当前选项，之后并交给处理是否按下键的程序段处理
    switch(press)
    {
        case 1:
            SetConsoleTextAttribute(myHandle, 0xC);
            gotoxy((MAX_RANDS - WALL_X_BEGIN) / 2 - 4, (MAX_ROWS - WALL_Y_BEGIN) / 2 - 3);
            printf("*正常模式");
            break;
            case 2:
                SetConsoleTextAttribute(myHandle, 0xC);
                gotoxy((MAX_RANDS - WALL_X_BEGIN) / 2 - 2, (MAX_ROWS - WALL_Y_BEGIN) / 2 - 3);
                printf("*限时模式");
                break;
            case 3:
                SetConsoleTextAttribute(myHandle, 0xC);
                gotoxy((MAX_RANDS - WALL_X_BEGIN) / 2 - 0, (MAX_ROWS - WALL_Y_BEGIN) / 2 - 3);
                printf("*完美模式");
                break;
            case 4:
                SetConsoleTextAttribute(myHandle, 0xC);
                gotoxy((MAX_RANDS - WALL_X_BEGIN) / 2 + 2, (MAX_ROWS - WALL_Y_BEGIN) / 2 - 3);
                printf("*暴走模式");
                break;
            case 5:
                SetConsoleTextAttribute(myHandle, 0xC);
                gotoxy((MAX_RANDS - WALL_X_BEGIN) / 2 + 4, (MAX_ROWS - WALL_Y_BEGIN) / 2 - 3);
                printf("*游戏帮助");
                break;
            case 6:
                SetConsoleTextAttribute(myHandle, 0xC);
                gotoxy((MAX_RANDS - WALL_X_BEGIN) / 2 + 6, (MAX_ROWS - WALL_Y_BEGIN) / 2 - 3);
                printf("*退出游戏");
                break;
            default:
                break;
    }


    do{
        //当没有输入时，默认为-1不做处理,press为1~6代表6个不同的功能选项
        int key = -1;
        //记录菜单的移动方向
        int direct = 0;
        //记录是否有键按下
        bool isPress = false;

        while(kbhit())
        {
            key = getch();
            isPress = true;
        }
        switch(key){
            case 'w':
            case 'W':
            case '8':
            case  72:
                if(press == 1)
                    press = 6;
                else
                    --press;
                direct = 0;
                break;
            case 's':
            case 'S':
            case '2':
            case  80:
                if(press == 6)
                    press = 1;
                else
                    ++press;
                direct = 1;
                break;
            //当按下enter键或右方向键时，确认选择
            case   13:
            case   77:
                enterGame = true;
            default:
                break;
        }

        switch(press)
        {
            case 1:
                //还原前一次选择的输出的颜色为菜单颜色，根据direct来判断哪个为前一次用户的选择，
                //只有在按下键时才进行更新显示,用于避免闪烁，和实现选择的选项颜色的变化下同
                if(isPress)
                {
                    if(direct)
                    {
                        //如果向下,还原其上一个选项的输出颜色,即case 6下同
                        SetConsoleTextAttribute(myHandle, 0xE);
                        gotoxy((MAX_RANDS - WALL_X_BEGIN) / 2 + 6, (MAX_ROWS - WALL_Y_BEGIN) / 2 - 3);
                        printf(" 退出游戏");
                    }
                    else
                    {
                        //如果向上,还原其下一个选项的输出颜色，即case 2下同
                        SetConsoleTextAttribute(myHandle, 0xE);
                        gotoxy((MAX_RANDS - WALL_X_BEGIN) / 2 - 2, (MAX_ROWS - WALL_Y_BEGIN) / 2 - 3);
                        printf(" 限时模式");
                    }
                    SetConsoleTextAttribute(myHandle, 0xB);
                    gotoxy((MAX_RANDS - WALL_X_BEGIN) / 2 - 4, (MAX_ROWS - WALL_Y_BEGIN) / 2 - 3);
                    printf("*正常模式");
                }
                break;
            case 2:
                if(isPress)
                {
                    if(direct)
                    {
                        SetConsoleTextAttribute(myHandle, 0xE);
                        gotoxy((MAX_RANDS - WALL_X_BEGIN) / 2 - 4, (MAX_ROWS - WALL_Y_BEGIN) / 2 - 3);
                        printf(" 正常模式");
                    }
                    else
                    {
                        SetConsoleTextAttribute(myHandle, 0xE);
                        gotoxy((MAX_RANDS - WALL_X_BEGIN) / 2 - 0, (MAX_ROWS - WALL_Y_BEGIN) / 2 - 3);
                        printf(" 完美模式");
                    }
                    SetConsoleTextAttribute(myHandle, 0xB);
                    gotoxy((MAX_RANDS - WALL_X_BEGIN) / 2 - 2, (MAX_ROWS - WALL_Y_BEGIN) / 2 - 3);
                    printf("*限时模式");
                }
                break;
            case 3:
                if(isPress)
                {
                    if(direct)
                    {
                        SetConsoleTextAttribute(myHandle, 0xE);
                        gotoxy((MAX_RANDS - WALL_X_BEGIN) / 2 - 2, (MAX_ROWS - WALL_Y_BEGIN) / 2 - 3);
                        printf(" 限时模式");
                    }
                    else
                    {
                        SetConsoleTextAttribute(myHandle, 0xE);
                        gotoxy((MAX_RANDS - WALL_X_BEGIN) / 2 + 2, (MAX_ROWS - WALL_Y_BEGIN) / 2 - 3);
                        printf(" 暴走模式");
                    }
                    SetConsoleTextAttribute(myHandle, 0xB);
                    gotoxy((MAX_RANDS - WALL_X_BEGIN) / 2 - 0, (MAX_ROWS - WALL_Y_BEGIN) / 2 - 3);
                    printf("*完美模式");
                }
                break;
            case 4:
                if(isPress)
                {
                    if(direct)
                    {
                        SetConsoleTextAttribute(myHandle, 0xE);
                        gotoxy((MAX_RANDS - WALL_X_BEGIN) / 2 - 0, (MAX_ROWS - WALL_Y_BEGIN) / 2 - 3);
                        printf(" 完美模式");
                    }
                    else
                    {
                        SetConsoleTextAttribute(myHandle, 0xE);
                        gotoxy((MAX_RANDS - WALL_X_BEGIN) / 2 + 4, (MAX_ROWS - WALL_Y_BEGIN) / 2 - 3);
                        printf(" 游戏帮助");
                    }
                    SetConsoleTextAttribute(myHandle, 0xB);
                    gotoxy((MAX_RANDS - WALL_X_BEGIN) / 2 + 2, (MAX_ROWS - WALL_Y_BEGIN) / 2 - 3);
                    printf("*暴走模式");
                }
                break;
            case 5:
                if(isPress)
                {
                    if(direct)
                    {
                        SetConsoleTextAttribute(myHandle, 0xE);
                        gotoxy((MAX_RANDS - WALL_X_BEGIN) / 2 + 2, (MAX_ROWS - WALL_Y_BEGIN) / 2 - 3);
                        printf(" 暴走模式");
                    }
                    else
                    {
                        SetConsoleTextAttribute(myHandle, 0xE);
                        gotoxy((MAX_RANDS - WALL_X_BEGIN) / 2 + 6, (MAX_ROWS - WALL_Y_BEGIN) / 2 - 3);
                        printf(" 退出游戏");
                    }

                    SetConsoleTextAttribute(myHandle, 0xB);
                    gotoxy((MAX_RANDS - WALL_X_BEGIN) / 2 + 4, (MAX_ROWS - WALL_Y_BEGIN) / 2 - 3);
                    printf("*游戏帮助");
                }

                break;

                //如果放在这里可以制造一点闪烁效果
                /*
                SetConsoleTextAttribute(myHandle, 0xB);
                gotoxy((MAX_RANDS - WALL_X_BEGIN) / 2 + 4, (MAX_ROWS - WALL_Y_BEGIN) / 2 - 3);
                printf("*游戏帮助");break;
                */
            case 6:
                if(isPress)
                {
                    if(direct)
                    {
                        SetConsoleTextAttribute(myHandle, 0xE);
                        gotoxy((MAX_RANDS - WALL_X_BEGIN) / 2 + 4, (MAX_ROWS - WALL_Y_BEGIN) / 2 - 3);
                        printf(" 游戏帮助");
                    }
                    else
                    {
                        SetConsoleTextAttribute(myHandle, 0xE);
                        gotoxy((MAX_RANDS - WALL_X_BEGIN) / 2 - 4, (MAX_ROWS - WALL_Y_BEGIN) / 2 - 3);
                        printf(" 正常模式");
                    }
                    SetConsoleTextAttribute(myHandle, 0xB);
                    gotoxy((MAX_RANDS - WALL_X_BEGIN) / 2 + 6, (MAX_ROWS - WALL_Y_BEGIN) / 2 - 3);
                    printf("*退出游戏");
                }
                break;
            default:
                break;
        }

        //清空输入缓冲区
        fflush(stdin);
    }while(!enterGame);

    //以上为菜单的输出处理
    //而此处为执行菜单中的选项
    gameEnter(press);
}

void gameEnter(int press)
{
    switch(press)
    {
        case 1:
            normalGame();
            //退出后返回主菜单
            break;
        case 2:
            limitTimeGame();
            break;
        case 3:
            perfectGame();
            break;
        case 4:
            crazyGame();
            break;
        case 5:
            //显示一次帮助信息，之后进入循环，按Q退出
            showHelp();
            while(getch() != 'Q');
            //退出后重新返回主菜单
            break;
        case 6:
            //退出游戏
            exit(0);break;
    }
}

//正常模式
void normalGame()
{
    //正常模式先设置地图刷新频率,下同
    setFps();
    do{
        system("cls");
        prepareGame();
        prepareShow();
        startGame();
        releseSnake();
    }while(getch()!= 'N');
}

//根据已写的各功能函数根据具体情况作更改
//限制模式,需要更改startGame里的移动后函数，其他不做更改，规则，
//在给定的速度(在等级9下)和时间下进行游戏，不进行等级提升
void limitTimeGame()
{
    setFps();
    do{
        system("cls");
        prepareGame();
        prepareShow();

        //设置等级为9
        Level = 9;

        //限制模式下的时间标记
        limitGame_BeginMarkTime = clock();
        do{
            show();
            showLimitCurrentTime();
            Sleep(setLevel());
            move(snakeHeadPoint);
            moved_procces_Limit();
            speedCaclate();
            isTimeOver();
            if(isEatFood && !Pause)
            {
                gainScore();
            }

            if(GameOver)
                showGameOver();
        }while(!GameOver);
        releseSnake();
    }while(getch()!= 'N');
}

//完美模式，限制最大生命数，即没吃到食物的次数
void perfectGame()
{
    setFps();
    int tmpLive = 0;
    //由用户选择难易度
    system("cls");
    gotoxy((WALL_X_END - WALL_X_BEGIN) / 2 - 1, (WALL_Y_END - WALL_Y_BEGIN) / 2 - 6);
    SetConsoleTextAttribute(myHandle, 0xA);
    printf("Easy or Hard？(E/H)E");
    gotoxy((WALL_X_END - WALL_X_BEGIN) / 2 - 1, (WALL_Y_END - WALL_Y_BEGIN) / 2 - 6);
    printf("Input: ");
    //默认为Easy
    if(getch() != 'H')
        tmpLive = 1;
    else
        tmpLive = 0;

    //清除输入缓冲
    fflush(stdin);

    do{
        system("cls");
        prepareGame();
        //设置最大生命数
        Live = tmpLive;
        prepareShow();
        startGame();
        releseSnake();
    }while(getch()!= 'N');
}

//暴走模式，设置最大速度(以最大速度为起点)，等级提升以很小的步长
void crazyGame()
{
    //设置刷新频率
    setFps();
    //初始化步长
    int tmpFps[11] = {fps[10], fps[10] - 1, fps[10] - 2, fps[10] - 3, fps[10] - 4,
                      fps[10] - 5, fps[10] - 6, fps[10] - 7, fps[10] - 8, fps[10] - 9, fps[10] - 10};
        //数组拷贝
    memcpy(fps, tmpFps, sizeof(int)*11);

    do{
        system("cls");
        prepareGame();
        prepareShow();
        startGame();
        releseSnake();
    }while(getch()!= 'N');
    /*
    //旧策略以最大速度游戏，去掉升级功能
    do{
        system("cls");
        prepareGame();
        //设置等级为10
        Level = 10;
        prepareShow();
        //暴走模式仅仅只将等级设为10，替代掉startGame,去掉升级功能
        do{
            show();
            Sleep(setLevel());
            move(snakeHeadPoint);
            speedCaclate();
        if(isEatFood && !Pause)
        {
            gainScore();
        }

        if(GameOver)
            showGameOver();
    }while(!GameOver);

        releseSnake();
    }while(getch()!= 'N');
    */
}

//显示帮助信息
void showHelp()
{
    system("cls");
    SetConsoleTextAttribute(myHandle, 0xB);
    gotoxy(0, 0);
    printf("Help:");

    gotoxy(1, 1);
    printf("正常模式：");
    gotoxy(2, 2);
    printf("正常模式，为此游戏的标准模式，其它模式的游戏规则是基于此模式的");

    gotoxy(4, 1);
    printf("限时模式:");
    gotoxy(5, 2);
    printf("限时模式为在规定的时间内，以设定的速度，以及不碰到墙与自身的情");
    gotoxy(6, 2);
    printf("况下，比较得分的多少!");

    gotoxy(8, 1);
    printf("完美模式:");
    gotoxy(9, 2);
    printf("完美模式为在正常模式下，设置最大连续没吃到食物数的大小，在难的");
    gotoxy(10, 2);
    printf("模式下，必须要一个不漏的吃到食物");

    gotoxy(12, 1);
    printf("暴走模式:");
    gotoxy(13, 2);
    printf("暴走模式为在正常模式下，以最高速度进行游戏，挑战速度与激情!");
    gotoxy(MAX_RANDS, 0);
    printf("按Q返回主菜单");
}

//主函数
int main(void)
{
    gameInit();
    //一直进行循环除非在菜单选项中选择退出游戏
    do{
        //一次循环只进入一次主菜单
        mainMenuAndGameEnter();
    }while(true);
    return 0;
}
