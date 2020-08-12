#include <bits/stdc++.h>
#include <windows.h>
#include <ctime>
#include "conio.h"
using namespace std;

#define upspace 3
#define leftspace 4
#define getrand(a,b) (rand()%b+a)//获取随机数 

void go(int,int);//设置光标位置(一个单位为2个英文字符 也就是一个"■") 
bool goout(int,int);//判断该坐标是否越界 
void color(int);//设置输出的文本颜色 
void printmap();//打印空白地图(房间)  
void printright(); //在屏幕右侧打印玩家当前属性数值 
void printpet();//打印宠物 

int shengming();//计算玩家现在的生命值并返回 
int tili();//计算玩家现在的体力值并返回 
int shanghai();//计算玩家现在的伤害值并返回 
int mianshang(int);//计算玩家对于不同怪物的免伤率并返回（1为骷弓，2为僵尸，3为蜘蛛） 
int baoji();//计算玩家现在的暴击率并返回 
int shanbi();//计算玩家现在的闪避率并返回 


void startgame();//开始界面 
void choose(); //选择职业界面 
void gaming();//游戏进行函数
	void room1();//玩家在第一个房间(整装房间)时 
		void home();//玩家进入"家"建筑物时 
		void fangshop();//玩家进入"防"建筑物时 
		void wushop();//玩家进入"武"建筑物时
		void petshop();//玩家进入"宠"建筑物时
		void hospital();//玩家进入"医"建筑物时
	void room2();//玩家在第二个房间(打怪房间)时
		void monmove(int);//怪物的移动 
		void fight(int);//玩家与怪物遇见 
			void ffight(int n);//玩家与怪物遇见后选择战斗
			void frun(); //玩家与怪物遇见后选择逃跑
			
void win();//胜利界面 
		

void openbag();//检测并打开背包 
	void sell(int n);//卖出背包内的第n项物品 



int slept=0;//玩家在这一波是否睡过觉 
int plx=10,ply=8;//玩家坐标 
int plzhiye;//玩家的职业 
int baoshi=200;//宝石数量 
int maxsm;//生命值上限 

int petx,pety;//玩家携带的宠物的坐标 

int boci=1;//怪物当前波次 

int nowwu=-1;//玩家现在所装备的武器 
struct snowfang//玩家现在所装备的防具 
{
	int dun;
	int ku;
	int jia;
}nowfang={-1,-1,-1};
int nowpet=-1;//玩家现在所携带的宠物 

int wubag[10];//武器背包 
int fangbag[10];//防具背包 
int petbag[10];//宠物背包 


struct szhiye
{
	string name;
	int shengming;
	int tili;
	int shanghai;
	int mianshang;
	int baoji;
	int shanbi;
	string pic;
}zhiye[5]=
{
	{},
	{"射手",200,155,30,16,20,15,"射"},
	{"战士",200,110,20,22,30,10,"战"},
	{"武士",300, 75,15,30,25, 5,"武"},
	{"刺客",160,155,20,20,40,25,"刺"},
};

struct swuqi
{
	string name;
	int shanghai;
	int much; 
	int have;
	int zhiye;
}wuqi[13]=
{
	{}, 
	{"竹箭",25, 70,0,1},
	{"铁箭",35,130,0,1},
	{"火箭",55,220,0,1},
	
	{"木剑",25, 70,0,2},
	{"铁剑",35,130,0,2},
	{"钻剑",55,220,0,2},
	
	{"木刀",25, 70,0,3},
	{"铁刀",35,130,0,3},
	{"钻刀",55,220,0,3},
	
	{"铁匕",25, 65,0,1},
	{"钻匕",35,125,0,1},
	{"毒匕",55,230,0,1},
};

struct sfangju
{
	string name;
	int fangku;
	int fangzhu;
	int fangjiang;
	int much;
	int have;
	int type;
}fangju[6]=
{
	{}, 
	{"木盾",11,10, 6,80,0,1},
	
	{"铁裤", 7,11, 5,90,0,2},
	{"钻裤",12,16, 6,175,0,2},
	
	{"铁甲",11, 5,12,120,0,3},
	{"钻甲",16, 6,17,200,0,3},	
};

struct shosp
{
	string name;
	int shengming;
	int tili;
	int much;
}hosp[4]=
{
	{}, 
	{"治疗",20, 1,20},
	{"治疗",40,20,50},
	{"治疗", 0,110,50},
}; 

struct spet
{
	string pic;
	int mianshang;
	int shanghai;
	int baoji;
	int shanbi;	
	int much;
	int have; 
}pet[7]=
{
	{},
	{"熊",15, 0, 0, 0,200,0}, 
	{"犬", 0,15, 0, 0,200,0},
	{"猫", 0, 0, 0,10,200,0},
	{"豹", 0, 0,15, 0,220,0},
	{"龙", 0, 0,50, 0,440,0},
	{"凤", 0, 0, 0,50,460,0},
};

string monpic[4]={"","骷","僵","蛛"}; 
struct smonster
{
	string name;
	int type;
	int drop;
	int baoshi;
	int shanghai;
	int mianshang;
	int baoji;
	int shanbi;
	int x;
	int y;
	int alive;
	int shengming;
}mon[8][5]=
{
	{}, 
	{
		{}, 
		{"竹箭骷弓", 1/*种类*/, 5/*掉落*/,30/*宝石*/,10/*伤害*/,10/*免伤*/,10/*暴击*/,10/*闪避*/, 5, 5,1,200/*生命*/},
		{"普通僵尸", 2, 0,25, 5,10,10,10, 5,10,1,180},
		{"普通蜘蛛", 3, 0,30, 5,10,10,10,10, 5,1,160}, 
		{"蜘蛛首领", 3, 0,45,15,15,10,10, 5, 5,2,310}
	},
	{
		{},
		{"竹箭骷弓", 1, 5,45,25,15,15,15,10, 9,2,220},
		{"铁甲僵尸", 2, 1,35,20,25,10,10, 5, 5,2,210},
		{"普通蜘蛛", 3, 0,40,25,15,10,15,15, 9,2,200}, 
		{"僵尸首领", 2, 0,65,40,15,20,10, 6, 6,2,320}
	},
	{
		{}, 
		{"铁箭骷弓", 1/*种类*/, 6/*掉落*/,55/*宝石*/,40/*伤害*/,10/*免伤*/,15/*暴击*/,15/*闪避*/, 7, 5,2,210/*生命*/},
		{"竹箭骷弓", 1/*种类*/, 5/*掉落*/,50/*宝石*/,30/*伤害*/,15/*免伤*/,10/*暴击*/,15/*闪避*/, 3, 3,2,230/*生命*/},
		{"普通蜘蛛", 3/*种类*/, 0/*掉落*/,50/*宝石*/,25/*伤害*/,20/*免伤*/,20/*暴击*/,10/*闪避*/,10,10,2,230/*生命*/},
		{"骷弓首领", 1/*种类*/, 5/*掉落*/,70/*宝石*/,50/*伤害*/,20/*免伤*/,20/*暴击*/,20/*闪避*/, 5, 5,2,330/*生命*/},
	},
	{
		{}, 
		{"蜘蛛精兵", 3/*种类*/, 0/*掉落*/,50/*宝石*/,45/*伤害*/,20/*免伤*/,10/*暴击*/,20/*闪避*/, 7, 3,2,255/*生命*/},
		{"钻甲僵尸", 2/*种类*/, 3/*掉落*/,55/*宝石*/,45/*伤害*/,35/*免伤*/,15/*暴击*/,15/*闪避*/, 3, 5,2,245/*生命*/},
		{"蜘蛛精兵", 3/*种类*/, 0/*掉落*/,55/*宝石*/,50/*伤害*/,20/*免伤*/,15/*暴击*/,15/*闪避*/,10,10,2,250/*生命*/},
		{"蜘蛛首领", 3/*种类*/, 0/*掉落*/,75/*宝石*/,60/*伤害*/,25/*免伤*/,20/*暴击*/,20/*闪避*/, 6, 5,2,350/*生命*/},
	},	
	{
		{}, 
		{"钻裤僵尸", 2/*种类*/, 4/*掉落*/,50/*宝石*/,50/*伤害*/,40/*免伤*/,10/*暴击*/,10/*闪避*/, 7, 3,2,255/*生命*/},
		{"僵尸精兵", 2/*种类*/, 0/*掉落*/,55/*宝石*/,45/*伤害*/,25/*免伤*/,15/*暴击*/,20/*闪避*/, 3, 5,2,250/*生命*/},
		{"火箭骷弓", 1/*种类*/, 7/*掉落*/,50/*宝石*/,50/*伤害*/,20/*免伤*/,15/*暴击*/,15/*闪避*/,10, 8,2,250/*生命*/},
		{"僵尸首领", 2/*种类*/, 0/*掉落*/,80/*宝石*/,65/*伤害*/,30/*免伤*/,20/*暴击*/,20/*闪避*/, 6, 5,2,355/*生命*/},
	},
	{
		{}, 
		{"钻甲僵尸", 2/*种类*/, 3/*掉落*/,55/*宝石*/,50/*伤害*/,40/*免伤*/,15/*暴击*/,10/*闪避*/, 7, 3,2,265/*生命*/},
		{"蜘蛛精兵", 3/*种类*/, 0/*掉落*/,45/*宝石*/,45/*伤害*/,25/*免伤*/,15/*暴击*/,25/*闪避*/, 3, 5,2,265/*生命*/},
		{"火箭骷弓", 1/*种类*/, 7/*掉落*/,50/*宝石*/,65/*伤害*/,20/*免伤*/,15/*暴击*/,10/*闪避*/,10,10,2,265/*生命*/},
		{"骷弓首领", 1/*种类*/, 0/*掉落*/,145/*宝石*/,70/*伤害*/,30/*免伤*/,20/*暴击*/,20/*闪避*/, 6, 5,2,400/*生命*/},
	},
	{
		{}, 
		{"铁箭骷弓", 1/*种类*/, 6/*掉落*/,66/*宝石*/,35/*伤害*/,10/*免伤*/,15/*暴击*/,10/*闪避*/, 7, 5,2,250/*生命*/},
		{"铁甲僵尸", 2/*种类*/, 1/*掉落*/,66/*宝石*/,25/*伤害*/,15/*免伤*/,10/*暴击*/,10/*闪避*/, 3, 3,2,250/*生命*/},
		{"普通蜘蛛", 3/*种类*/, 0/*掉落*/,66/*宝石*/,25/*伤害*/,10/*免伤*/,20/*暴击*/,10/*闪避*/,10,10,2,250/*生命*/},
		{"蜘蛛首领", 3/*种类*/, 0/*掉落*/,666/*宝石*/,86/*伤害*/,36/*免伤*/,26/*暴击*/,26/*闪避*/, 6, 6,2,666/*生命*/},	
	}	
}; 

string chenghao[9]=
{"","见习","新手","初级","中级","高级","Pro级","顶级","超级"}; 


int main()
{
//	boci=6; 
//	baoshi=2000;
//	mon[6][1].alive=0;
//	mon[6][2].alive=0;
//	mon[6][3].alive=0;//////////////////////////////////////////////////////////////
	
	system("mode con cols=90 lines=28");

	unsigned seed;
    seed = time(0);
    srand(seed);
    
	CONSOLE_CURSOR_INFO cursor_info={1,0};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);//隐藏光标 
	system("color 0F");
	while(!kbhit())
	{
		Sleep(10);
	}Sleep(250);
	startgame();
	choose();
	gaming();
	
	return 0;
} 

void go(int x,int y)  //光标移动函数，X表示横坐标，Y表示纵坐标。
{
    COORD coord;         //使用头文件自带的坐标结构
    coord.X=(x+leftspace)*2;            //这里将int类型值传给short,不过程序中涉及的坐标值均不会超过short范围
    coord.Y=y+upspace;
    HANDLE a=GetStdHandle(STD_OUTPUT_HANDLE);  //获得标准输出句柄
    SetConsoleCursorPosition(a,coord);         //以标准输出的句柄为参数设置控制台光标坐标
}

bool goout(int x,int y)
{
	if(x<1||x>18||y<1||y>13)return 1;
	return 0;
}

void color(int a)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),a);
}
void printmap()
{
	system("color 0F");
	go(0,15);
	color(8);
	printf("作者：bilibili  @阳光下的树叶TREEYEAH");
	color(15);
	for(int i=0;i<20;i++)
	{
		for(int j=0;j<15;j++)
		{
			go(i,j);
			if(i==0||i==19||j==0||j==14)
			{
				printf("■");
			}
			else
			{
				printf("  ");
			}
		}
	}
}

void startgame()
{
	int gamename[12][40]=
	{
		{ 1,-1,-1,-1, 9,-1,14,15,16,-1,23,-1,-1,-1,32,-1,36,45,46,47,48,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{ 2, 6,-1, 8,10,-1,-1,17,-1,-1,24,28,-1,-1,33,-1,37,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{ 3,-1, 7,-1,11,-1,-1,18,-1,-1,25,-1,29,-1,34,-1,38,49,50,51,52,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{ 4,-1,-1,-1,12,-1,-1,19,-1,-1,26,-1,-1,30,35,-1,39,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{ 5,-1,-1,-1,13,-1,20,21,22,-1,27,-1,-1,-1,31,-1,40,41,42,43,44,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{53,-1,-1,-1,61,-1,66,67,68,-1,-1,78,77,76,75,-1,-1,101,100,99,98,-1,111,112,113,-1,-1,122,121,132,-1,-1,133,-1,-1,-1,142,-1,-1,-1},
		{54,58,-1,60,62,-1,-1,69,-1,-1,79,-1,-1,-1,-1,-1,102,-1,-1,-1,-1,-1,-1,114,-1,-1,123,-1,-1,-1,131,-1,134,138,-1,-1,143,-1,-1,-1},
		{55,-1,59,-1,63,-1,-1,70,-1,-1,-1,80,81,82,-1,-1,-1,103,104,105,-1,-1,-1,115,-1,-1,124,-1,-1,-1,130,-1,135,-1,139,-1,144,-1,-1,-1},
		{56,-1,-1,-1,64,-1,-1,71,-1,-1,-1,-1,-1,-1,83,-1,-1,-1,-1,-1,106,-1,-1,116,-1,-1,125,-1,-1,-1,129,-1,136,-1,-1,140,145,-1,-1,-1},
		{57,-1,-1,-1,65,-1,72,73,74,-1,97,86,85,84,-1,-1,110,109,108,107,-1,-1,117,119,120,-1,-1,126,127,128,-1,-1,137,-1,-1,-1,141,-1,-1,-1},
	};
	for(int k=1;k<=145;k++)
	{
		for(int i=0;i<=11;i++)
		{
			for(int j=0;j<=39;j++)
			{
				if(gamename[i][j]==k)
				{
					go(i<=6?j+6:j,i);
					color(143);
					printf("■");
					Sleep(50);
				}
			}
		}
	}
	color(15);
	Sleep(1000);
	go(2,14);
	cout<<endl<<endl<<"请确保您的输入法已调成英文"<<endl; 
	Sleep(100);
	system("pause");
	system("cls");
	go(0,0);
	printmap();
	int key=0;
	go(plx,ply);
	color(240);printf("你");
	color(15);
	go(20,8);printf("开");
	go(20,9);printf("始");
	go(20,10);printf("游");
	go(20,11);printf("戏");
	go(19,10);printf("→");
	
	go(0,15);printf("操作方法：                                       "); 
	go(2,16);printf("A、D键左右移动角色  W、S键上下移动角色/选择选项");
	go(2,17);printf("Enter键确认/购买/装备/取消装备");
	go(2,18);printf("Tab键打开背包");
	go(2,19);printf("背包中Backspace键卖出物品");
	go(2,20);printf("Esc键可以退出任何不是村庄界面(战斗界面除外)的界面");
	go(2,21);printf("走到建筑物/怪物位置上可以进入相应界面");
	
	
	while(plx!=20||ply!=10)
	{
		if(kbhit)
		{
			key=getch();
			if((key=='W'||key=='w')&&!goout(plx,ply-1))
			{
				go(plx,ply);
				color(15);printf("  ");
				ply--;
			}
			if((key=='S'||key=='s')&&!goout(plx,ply+1))
			{
				go(plx,ply);
				color(15);printf("  ");
				ply++;
			}
			if((key=='A'||key=='a')&&!goout(plx-1,ply))
			{
				go(plx,ply);
				color(15);printf("  ");
				plx--;
			}	
			if((key=='D'||key=='d'))
			{
				if(!goout(plx+1,ply)||ply==10)
				{
					go(plx,ply);
					color(15);printf("  ");
					plx++;
				}
			}
			color(15);
			go(19,10);printf("→");
			if(plx!=20||ply!=10)
			{
				go(plx,ply);
				color(240);printf("你");
			}
			
		}
		Sleep(100);
	}
}
void choose()
{
	system("cls");
	system("color 0F");
	go(0,0);
	printf("请选择你的职业：");
	go(2,1);
	printf("职业  生命值  体力值  伤害值  免伤率(%) 暴击率(%) 闪避率(%) 图标");	
	for(int i=1;i<=4;i++)
	{
		go(2,1+i);
		cout<<zhiye[i].name;
		go(5,1+i);
		cout<<zhiye[i].shengming;
		go(9,1+i);
		cout<<zhiye[i].tili;
		go(13,1+i);
		cout<<zhiye[i].shanghai;
		go(17,1+i);
		cout<<zhiye[i].mianshang;
		go(22,1+i);
		cout<<zhiye[i].baoji;
		go(27,1+i);
		cout<<zhiye[i].shanbi;
		go(32,1+i);
		cout<<zhiye[i].pic;
	}
	plzhiye=1;
	go(0,2);
	printf(">>");
	int key=0;
	while(key!=13)
	{
		if(kbhit())
		{
			key=getch();
			if(key=='w'||key=='W')
			{
				go(0,1+plzhiye);
				printf("  ");
				plzhiye--;
			}
			if(key=='s'||key=='S')
			{
				go(0,1+plzhiye);
				printf("  ");
				plzhiye++;
			}
			if(plzhiye>4)plzhiye-=4;
			if(plzhiye<1)plzhiye+=4;
			go(0,1+plzhiye);
			printf(">>");
		}
	}
	maxsm=zhiye[plzhiye].shengming; 
}
void gaming()
{
	system("cls");

	printmap();
	string pic=zhiye[plzhiye].pic;
	plx=1;ply=8;
	int key=0;
	
	go(22,0);cout<<"职业："<<zhiye[plzhiye].name;
	go(22,1);cout<<"生命值："<<zhiye[plzhiye].shengming;
	go(22,2);cout<<"体力值："<<zhiye[plzhiye].tili;
	go(22,4);cout<<"伤害值："<<zhiye[plzhiye].shanghai;
	go(22,5);cout<<"免伤率："<<zhiye[plzhiye].mianshang;
	go(22,6);cout<<"暴击率："<<zhiye[plzhiye].baoji;
	go(22,7);cout<<"闪避率："<<zhiye[plzhiye].shanbi;
	go(22,9);cout<<"宝石："<<baoshi;
	while(1)
	{	
		room1();
		
		plx=1;ply=10;
		go(plx,ply);color(240);cout<<pic;
		
		if(mon[boci][1].alive+mon[boci][2].alive+mon[boci][3].alive==6)
		{
			mon[boci][1].alive=1;
			mon[boci][2].alive=1;
			mon[boci][3].alive=1;
		}
		if(mon[boci][1].alive+mon[boci][2].alive+mon[boci][3].alive==0&&mon[boci][4].alive==2)
		{
			mon[boci][4].alive=1;
		}

		room2();
		
		plx=18;ply=10;	

	}
}

void home()
{
	system("cls");
	system("color 0F");
	go(9,0);printf("家"); 
	go(2,2);cout<<"按【Enter】睡觉（补充120体力值和5生命值）"; 
	int key=getch();
	if(key==13)
	{
		if(slept==0)
		{
			go(2,3);
			for(int i=1;i<=12;i++)cout<<".",Sleep(200);
			slept=1;
			zhiye[plzhiye].tili+=120;
			zhiye[plzhiye].shengming+=5;
			go(2,3);
			printf("体力值+120,生命值+%d                          ",shengming()>maxsm?(maxsm-shengming()+5):5);
			if(shengming()>maxsm)
			{
				zhiye[plzhiye].shengming=maxsm;
				go(2,4);printf("（生命值已达上限）");
			}
		}
		else
		{
			go(2,3);
			cout<<"每波只能睡觉一次";
		}
		Sleep(1000);
		return;
	}
	else if(key==27) 
	{
		return;
	}
	else
	{
		home();
	}
}

void fangshop()
{
	system("cls");
	system("color 0F");
	go(7,0);printf("防具商店"); 
	go(2,2);
	printf("名称  防骷  防僵  防蛛  买价  卖价");
	for(int i=1;i<=5;i++)
	{
		go(2,2+i);cout<<fangju[i].name;
		go(5,2+i);cout<<fangju[i].fangku;
		go(8,2+i);cout<<fangju[i].fangjiang;
		go(11,2+i);cout<<fangju[i].fangzhu;
		go(14,2+i);cout<<fangju[i].much;
		go(17,2+i);cout<<fangju[i].much/2;
	}
	
	int key=0;
	int a=1;
	while(key!=27)
	{
		color(15);
		go(0,2+a);printf(">>");
		key=getch();
		if(key==13)
		{
			if(baoshi>=fangju[a].much)
			{
				if(fangju[a].have==0)
				{
					baoshi-=fangju[a].much;
					fangju[a].have=1;
					fangbag[++fangbag[0]]=a;
					go(2,9);printf("购买成功！还有%d个宝石 ",baoshi);
					if(nowpet!=-1)nowpet++;
				}
				else 
				{
					go(2,9);printf("您已经拥有该物品了        ");
				}
			}
			else
			{
				go(2,9);printf("宝石不足！               ");
			}
		}
		else if(key=='W'||key=='w')
		{
			go(0,2+a);printf("  "); 
			a--;
			if(a<1)a+=5;
		}
		else if(key=='S'||key=='s')
		{
			go(0,2+a);printf("  "); 
			a++;
			if(a>5)a-=5;
		}
		else if(key==27)
		{
			return;
		}
		else
		{
			fangshop();
			return;
		}
	}
}

void wushop()
{
	system("cls");
	system("color 0F");
	go(9,0);printf("武器商店"); 
	go(2,2);
	printf("名称  伤害值  买价  卖价");	
	for(int i=1;i<=3;i++)
	{
		go(2,2+i);cout<<wuqi[(plzhiye-1)*3+i].name;
		go(5,2+i);cout<<wuqi[(plzhiye-1)*3+i].shanghai;
		go(9,2+i);cout<<wuqi[(plzhiye-1)*3+i].much;
		go(12,2+i);cout<<wuqi[(plzhiye-1)*3+i].much/2;
	}
	
	int key=0;int a=1;
	while(key!=27)
	{
		color(15);
		go(0,2+a);printf(">>");
		key=getch();
		if(key==13)
		{
			if(baoshi>=wuqi[(plzhiye-1)*3+a].much)
			{
				if(wuqi[a].have==0)
				{
					baoshi-=wuqi[(plzhiye-1)*3+a].much;
					wuqi[a].have=1;
					wubag[++wubag[0]]=(plzhiye-1)*3+a;
					go(2,7);printf("购买成功！还有%d个宝石 ",baoshi);
					if(nowpet!=-1)nowpet++;
					if(nowfang.dun!=-1)nowfang.dun++;
					if(nowfang.jia!=-1)nowfang.jia++;
					if(nowfang.ku!=-1)nowfang.ku++;
				}
				else
				{
					go(2,7);printf("您已经拥有该物品了        ");
				}
			}
			else
			{
				go(2,7);printf("宝石不足                 ");
			}
		}
		else if(key=='W'||key=='w')
		{
			go(0,2+a);printf("  "); 
			a--;
			if(a<1)a+=3;
		}
		else if(key=='S'||key=='s')
		{
			go(0,2+a);printf("  "); 
			a++;
			if(a>3)a-=3;
		}
		else if(key==27)
		{
			return;
		}
		else
		{
			wushop();
			return;
		}
	}
}

void petshop()
{
	system("cls");
	system("color 0F");
	go(9,0);printf("宠物商店"); 
	go(2,2);
	printf("图标  伤害值  免伤率(%) 暴击率(%) 闪避率(%) 买价  卖价");
	for(int i=1;i<=6;i++)
	{
		go(2,2+i);cout<<pet[i].pic;
		go(5,2+i);cout<<pet[i].shanghai;
		go(9,2+i);cout<<pet[i].mianshang;
		go(14,2+i);cout<<pet[i].baoji;
		go(19,2+i);cout<<pet[i].shanbi;
		go(24,2+i);cout<<pet[i].much;
		go(27,2+i);cout<<pet[i].much/2;	
	}
	int key=0;int a=1;
	while(key!=27)
	{
		color(15);
		go(0,2+a);printf(">>");
		key=getch();
		if(key==13)
		{
			if(baoshi>=pet[a].much)
			{
				if(pet[a].have==0)
				{
					baoshi-=pet[a].much;
					petbag[++petbag[0]]=a;
					pet[a].have=1;
					go(2,9);printf("购买成功！还有%d个宝石 ",baoshi);
				}
				else
				{
					go(2,9);printf("您已经拥有该物品了        ");
				}
			}
			else
			{
				go(2,9);printf("宝石不足                 ");
			}
		}
		else if(key=='W'||key=='w')
		{
			go(0,2+a);printf("  "); 
			a--;
			if(a<1)a+=6;
		}
		else if(key=='S'||key=='s')
		{
			go(0,2+a);printf("  "); 
			a++;
			if(a>6)a-=6;
		}
		else if(key==27)
		{
			return;
		}
		else
		{
			petshop();
			return;
		}
		
	}
}

void hospital()
{
	system("cls");
	system("color 0F");
	go(9,0);
	printf("医院");
	go(2,2);
	printf("名称  恢复生命值  恢复体力值  费用");
	for(int i=1;i<=3;i++)
	{
		go(2,2+i);cout<<hosp[i].name;
		go(5,2+i);cout<<hosp[i].shengming;
		go(11,2+i);cout<<hosp[i].tili;
		go(17,2+i);cout<<hosp[i].much;
	}
	int key=0;int a=1;
	while(key!=27)
	{
		color(15);
		go(0,2+a);printf(">>");
		key=getch();
		if(key==13)	
		{
			if(baoshi>=hosp[a].much)
			{
				baoshi-=hosp[a].much;
				zhiye[plzhiye].shengming+=hosp[a].shengming;
				if(shengming()>maxsm)
				{
					zhiye[plzhiye].shengming=maxsm;
					go(2,8);printf("（生命值已达上限）");
				}
				zhiye[plzhiye].tili+=hosp[a].tili;
				
				go(2,7);printf("治疗成功！还有%d个宝石  生命值%d 体力值%d     ",baoshi,shengming(),tili());
			}
			else
			{
				go(2,7);printf("宝石不足                                       ",baoshi);
			}
		}
		else if(key=='W'||key=='w')
		{
			go(0,2+a);printf("  "); 
			a--;
			if(a<1)a+=3;
		}
		else if(key=='S'||key=='s')
		{
			go(0,2+a);printf("  "); 
			a++;
			if(a>3)a-=3;
		}
		else if(key==27)
		{
			return;
		}
		else
		{
			hospital();
			return;
		}
	}
}



void printright()
{
	go(22,0);cout<<"职业："<<zhiye[plzhiye].name;
	go(22,1);cout<<"生命值："<<shengming()<<"/"<<maxsm<<"   ";
	go(22,2);cout<<"体力值："<<tili()<<"   ";
	go(22,4);cout<<"伤害值："<<shanghai()<<"   ";
	go(22,5);cout<<"免伤率："<<mianshang(1)<<"%/"<<mianshang(2)<<"%/"<<mianshang(3)<<"%   ";
	go(22,6);cout<<"暴击率："<<baoji()<<"%   ";
	go(22,7);cout<<"闪避率："<<shanbi()<<"%   ";
	go(22,8);cout<<"称号："<<chenghao[boci]<<zhiye[plzhiye].name<<"  ";
	go(22,10);cout<<"宝石："<<baoshi<<"   ";
}

void room1()
{
	int key=0;
	string pic=zhiye[plzhiye].pic;
	
	system("color 0F");
	system("cls");
	printmap();
	
	go(19,10);printf("门");
	go(plx,ply);color(240);cout<<pic; 
	go( 5, 3);color(15);cout<<"家";
	go(10, 3);color(15);cout<<"医";
	go( 5,11);color(15);cout<<"宠";
	go(10,11);color(15);cout<<"防";
	go(15,11);color(15);cout<<"武";
	
	printright();
	
	go(8,-1);printf("村庄中心");

	while(plx!=20||ply!=10)									//整装房间 
	{
		if(kbhit)
		{
			key=getch();
			if((key=='W'||key=='w')&&!goout(plx,ply-1))
			{
				go(plx,ply);
				color(15);printpet();
				ply--;
			}
			if((key=='S'||key=='s')&&!goout(plx,ply+1))
			{
				go(plx,ply);
				color(15);printpet();
				ply++;
			}
			if((key=='A'||key=='a')&&!goout(plx-1,ply))
			{
				go(plx,ply);
				color(15);printpet();
				plx--;
			}	
			if((key=='D'||key=='d'))
			{
				if(!goout(plx+1,ply)||ply==10)
				{
					go(plx,ply);
					color(15);printpet();
					plx++;
				}
			}
			if(key==9)
			{
				openbag();
				room1();
				return;
			}
			
			
			go(19,10);
			color(15);printf("门");	
			go( 5, 3);color(15);cout<<"家";
			go(10, 3);color(15);cout<<"医";
			go( 5,11);color(15);cout<<"宠";
			go(10,11);color(15);cout<<"防";
			go(15,11);color(15);cout<<"武";
			
			if(plx!=20||ply!=10)
			{
				go(plx,ply);color(240);cout<<pic;
			}
				
			if(plx==5&&ply==3)
			{
				home();
				ply++;
				room1();
				return;
			}
			if(plx==10&&ply==3)
			{
				hospital();
				ply++;
				room1();
				return;
			}
			if(plx==10&&ply==11)
			{
				fangshop();
				ply--;
				room1();
				return;
			}
			if(plx==15&&ply==11)
			{
				wushop();
				ply--;
				room1();
				return;
			}
			if(plx== 5&&ply==11)
			{
				petshop();
				ply--;
				room1();
				return;
			}
		}
		Sleep(125);
	}
}

void room2()
{
	int key=0;
	string pic=zhiye[plzhiye].pic;
	
	system("color 0F");
	system("cls");
	printmap();
	
	printright();
		
	go( 0,10);printf("门");
	go( 8,-1);printf("村庄边境");
	
	go(plx,ply);color(240);cout<<pic; 
	
		
	while(plx!=-1||ply!=10)								//打怪房间 
	{
		for(int i=1;i<=4;i++) monmove(i);
		if(kbhit)
		{
			key=getch();
			if((key=='W'||key=='w')&&!goout(plx,ply-1))
			{
				go(plx,ply);
				color(15);printpet();
				ply--;
			}
			if((key=='S'||key=='s')&&!goout(plx,ply+1))
			{
				go(plx,ply);
				color(15);printpet();
				ply++;
			}
			if((key=='D'||key=='d')&&!goout(plx+1,ply))
			{
				go(plx,ply);
				color(15);printpet();
				plx++;
			}	
			if((key=='A'||key=='a'))
			{
				if(!goout(plx-1,ply)||ply==10&&plx>=0)
				{
					go(plx,ply);
					color(15);printpet();
					plx--;
				}
			}
			go( 0,10);
			color(15);printf("门");	
			if(plx==-1&&ply==10)return;
			if(key==9)
			{
				openbag();
				room2();
				return;
			}
			
			
			if(plx!=-1||ply!=10)
			{
				go(plx,ply);color(240);cout<<pic;
			}
		}
		
		Sleep(125);
	}
}


void openbag()
{
	system("color 0F");
	system("cls");
	
	go(8,-1);
	printf("背包");
	go(2,1);
	color(15);
	printf("物品名称  物品卖价  物品状态"); 
	for(int i=1;i<=wubag[0]+fangbag[0]+petbag[0];i++)
	{
		if(i<=wubag[0])
		{
			go( 2,i+1);cout<<wuqi[wubag[i]].name;
			go( 7,i+1);cout<<wuqi[wubag[i]].much/2;
			go(12,i+1);if(nowwu==i)printf("已装备");else printf("未装备");
		}
		else if(i<=wubag[0]+fangbag[0])
		{
			go( 2,i+1);cout<<fangju[fangbag[i-wubag[0]]].name;
			go( 7,i+1);cout<<fangju[fangbag[i-wubag[0]]].much/2;
			go(12,i+1);
			if(fangju[fangbag[i-wubag[0]]].type==1)
			{
				if(nowfang.dun==i)
				{
					printf("已装备");
				}
				else
				{
					printf("未装备");
				}
			}
			if(fangju[fangbag[i-wubag[0]]].type==2)
			{
				if(nowfang.ku==i)
				{
					printf("已装备");
				}
				else
				{
					printf("未装备");
				}					
			}
			if(fangju[fangbag[i-wubag[0]]].type==3)
			{
				if(nowfang.jia==i)
				{
					printf("已装备");
				}
				else
				{
					printf("未装备");
				}					
			}				
		}
		else
		{
			go( 2,i+1);cout<<pet[petbag[i-wubag[0]-fangbag[0]]].pic;
			go( 7,i+1);cout<<pet[petbag[i-wubag[0]-fangbag[0]]].much/2;
			go(12,i+1);if(nowpet==i)printf("已装备");else printf("未装备");
		}
	}
	printright();
	int a=1;
	go(0,a+1);printf(">>");
	int key=0;
	while(key!=27)
	{
		key=getch();
		if((key=='W'||key=='w')&&wubag[0]+fangbag[0]+petbag[0]>0)
		{
			go(0,a+1);printf("  ");
			a--;
			if(a<1)
			{
				a+=wubag[0]+fangbag[0]+petbag[0];
			}
		}
		else if((key=='S'||key=='s')&&wubag[0]+fangbag[0]+petbag[0]>0)
		{
			go(0,a+1);printf("  ");
			a++;
			if(a>wubag[0]+fangbag[0]+petbag[0])
			{
				a-=wubag[0]+fangbag[0]+petbag[0];
			}			
		}
		else if(key==13&&wubag[0]+fangbag[0]+petbag[0]>0)
		{
			if(a<=wubag[0])
			{
				if(nowwu!=a)
				{
					if(nowwu!=-1)
					{
						go(12,nowwu+1);
						printf("未装备");
					}
					nowwu=a;
					go(12,nowwu+1);
					printf("已装备");					
				}
				else
				{
					go(12,nowwu+1);printf("未装备");nowwu=-1;
				}
			}
			else if(a<=wubag[0]+fangbag[0])
			{
				if(fangju[fangbag[a-wubag[0]]].type==1)
				{
					if(nowfang.dun!=a)
					{
						if(nowfang.dun!=-1)
						{
							go(12,nowfang.dun+1);
							printf("未装备");
						}
						nowfang.dun=a;
						go(12,nowfang.dun+1);
						printf("已装备");
					}
					else
					{
						go(12,nowfang.dun+1);printf("未装备");nowfang.dun=-1;
					}
				}
				else if(fangju[fangbag[a-wubag[0]]].type==2)
				{
					if(nowfang.ku!=a)
					{
						if(nowfang.ku!=-1)
						{
							go(12,nowfang.ku+1);
							printf("未装备");
						}
						nowfang.ku=a;
						go(12,nowfang.ku+1);
						printf("已装备");
					}
					else
					{
						go(12,nowfang.ku+1);printf("未装备");nowfang.ku=-1;
					}					
				}
				else if(fangju[fangbag[a-wubag[0]]].type==3)
				{
					if(nowfang.jia!=a)
					{
						if(nowfang.jia!=-1)
						{
							go(12,nowfang.jia+1);
							printf("未装备");
						}
						nowfang.jia=a;
						go(12,nowfang.jia+1);
						printf("已装备");
					}
					else
					{
						go(12,nowfang.jia+1);printf("未装备");nowfang.jia=-1;
					}			
				}
			}
			else if(a<=wubag[0]+fangbag[0]+petbag[0])
			{
				if(nowpet!=a)
				{
					if(nowpet!=-1)
					{
						go(12,nowpet+1);
						printf("未装备");
					}
					nowpet=a;
					go(12,nowpet+1);
					printf("已装备");					
				}
				else
				{
					go(12,nowpet+1);printf("未装备");nowpet=-1;
				}				
			}
		}
		else if(key==27)
		{
			return;
		}
		else if(key==8&&wubag[0]+fangbag[0]+petbag[0]>0)
		{
			sell(a);
			openbag();
			return;
		}
		go(0,a+1);printf(">>");
		
		printright();
	}
}

void sell(int n)
{
	if(n<=wubag[0])
	{
		baoshi+=wuqi[wubag[n]].much/2;
		wuqi[wubag[n]].have=0;
		wubag[n]=0;
		wubag[0]--;
		for(int i=n;i<=wubag[0];i++)
		{
			wubag[i]=wubag[i+1];
		}
		if(nowwu==n)nowwu=-1;
		if(nowwu>n)nowwu--;
		
		if(nowpet!=-1)nowpet--;
		if(nowfang.dun!=-1)nowfang.dun--;
		if(nowfang.jia!=-1)nowfang.jia--;
		if(nowfang.ku!=-1)nowfang.ku--;			
	}
	else if(n<=wubag[0]+fangbag[0])
	{
		baoshi+=fangju[fangbag[n-wubag[0]]].much/2;
		fangju[fangbag[n-wubag[0]]].have=0;
		fangbag[n-wubag[0]]=0;
		fangbag[0]--;
		for(int i=n-wubag[0];i<=fangbag[0];i++)
		{
			fangbag[i]=fangbag[i+1];
		}
		if(nowfang.dun==n)nowfang.dun=-1;
		if(nowfang.ku==n)nowfang.ku=-1;
		if(nowfang.jia==n)nowfang.jia=-1;
		
		if(nowfang.dun>n)nowfang.dun--;
		if(nowfang.ku>n)nowfang.ku--;
		if(nowfang.jia>n)nowfang.jia--;
		
		if(nowpet!=-1)nowpet--;
	}
	else
	{
		baoshi+=pet[petbag[n-wubag[0]-fangbag[0]]].much/2;
		pet[petbag[n-wubag[0]-fangbag[0]]].have=0;
		petbag[n-wubag[0]-fangbag[0]]=0;
		petbag[0]--;
		for(int i=n-wubag[0]-fangbag[0];i<=petbag[0];i++)
		{
			petbag[i]=petbag[i+1];
		}
		if(nowpet==n)nowpet=-1;
		if(nowpet>n)nowpet--;

	}
}


int shengming()
{
	int k=zhiye[plzhiye].shengming;
	return k;
}
int tili()
{
	int k=zhiye[plzhiye].tili;
	return k;
}
int shanghai()
{
	int k=zhiye[plzhiye].shanghai;
	k+=wuqi[wubag[nowwu]].shanghai;
	if(nowpet!=-1)k+=pet[petbag[nowpet-wubag[0]-fangbag[0]]].shanghai;
	return k;
}
int mianshang(int m)
{
	int k=zhiye[plzhiye].mianshang;
	if(m==2)
	{
		if(nowfang.dun!=-1)
		{
			k+=fangju[fangbag[nowfang.dun-wubag[0]]].fangjiang;
		}
		if(nowfang.jia!=-1)
		{
			k+=fangju[fangbag[nowfang.jia-wubag[0]]].fangjiang;
		}
		if(nowfang.ku!=-1)
		{
			k+=fangju[fangbag[nowfang.ku-wubag[0]]].fangjiang;
		}
	}
	if(m==1)
	{
		if(nowfang.dun!=-1)
		{
			k+=fangju[fangbag[nowfang.dun-wubag[0]]].fangku;
		}
		if(nowfang.jia!=-1)
		{
			k+=fangju[fangbag[nowfang.jia-wubag[0]]].fangku;
		}
		if(nowfang.ku!=-1)
		{
			k+=fangju[fangbag[nowfang.ku-wubag[0]]].fangku;
		}		
	}
	if(m==3)
	{
		if(nowfang.dun!=-1)
		{
			k+=fangju[fangbag[nowfang.dun-wubag[0]]].fangzhu;
		}
		if(nowfang.jia!=-1)
		{
			k+=fangju[fangbag[nowfang.jia-wubag[0]]].fangzhu;
		}
		if(nowfang.ku!=-1)
		{
			k+=fangju[fangbag[nowfang.ku-wubag[0]]].fangzhu;
		}
	}
	if(nowpet!=-1)k+=pet[petbag[nowpet-wubag[0]-fangbag[0]]].mianshang;
	return k;
}
int baoji()
{
	int k=zhiye[plzhiye].baoji;
	if(nowpet!=-1)k+=pet[petbag[nowpet-wubag[0]-fangbag[0]]].baoji;
	return k;
}
int shanbi()
{
	int k=zhiye[plzhiye].shanbi;
	if(nowpet!=-1)k+=pet[petbag[nowpet-wubag[0]-fangbag[0]]].shanbi;
	return k;
}
void printpet()
{
	if(nowpet!=-1)
	{
		color(15);
		cout<<pet[petbag[nowpet-wubag[0]-fangbag[0]]].pic;
		if(petx==0&&pety==0) petx=plx,pety=ply;
		else 
		{
			go(petx,pety);
			if(petx==19||petx==0) printf("■");
			else printf("  ");
			petx=plx,pety=ply;
		}
	}
	else
	{
		printf("  ");
	}
}

void monmove(int n)
{
	if(mon[boci][n].alive!=1)
	{
		return;
	}
	if(plx==mon[boci][n].x&&ply==mon[boci][n].y)
	{
		fight(n);
		return;
	}
	color(15);
	int m[8][2]=
	{
		{},
		{ 0, 1},
		{ 1, 0},
		{-1, 0},
		{ 0,-1},
		{ 0, 0},
		{ 0, 0},
		{ 0, 0}
	};
	int r=getrand(1,7);
	while(goout(mon[boci][n].x+m[r][0],mon[boci][n].y+m[r][1]))
	{
		r=getrand(1,7);
	}
	go(mon[boci][n].x,mon[boci][n].y);
	if(plx!=mon[boci][n].x||ply!=mon[boci][n].y)cout<<"  ";
	mon[boci][n].x+=m[r][0];
	mon[boci][n].y+=m[r][1];
	go(mon[boci][n].x,mon[boci][n].y);
	if(mon[boci][n].type==-1)color(240);
	cout<<monpic[mon[boci][n].type];
	
	if(plx==mon[boci][n].x&&ply==mon[boci][n].y)
	{
		fight(n);
	}
}

void fight(int n)
{
	system("color 0F");
	system("cls");
	
	go(4,2);printf("战斗");
	go(4,4);printf("逃跑（消耗10体力值）");
	go(2,2);printf(">>");
	go(4,7);printf("对手：");cout<<mon[boci][n].name;
	go(4,9);printf("生命值：");cout<<mon[boci][n].shengming;
	go(4,10);printf("伤害值：");cout<<mon[boci][n].shanghai;
	go(4,11);printf("免伤率：");cout<<mon[boci][n].mianshang;
	go(4,12);printf("暴击率：");cout<<mon[boci][n].baoji;
	go(4,13);printf("闪避率：");cout<<mon[boci][n].shanbi;
	
	go(4,14);printf("掉落宝石:");cout<<mon[boci][n].baoshi;
	 
	int key=0;
	int a=1;
	while(key!=13)
	{
		key=getch();
		if(key=='w'||key=='W'||key=='s'||key=='S')
		{
			go(2,a*2);printf("  ");
			a=3-a;
			go(2,a*2);printf(">>");
		}
	}
	if(a==1)
	{
		ffight(n);
	}
	else if(a==2)
	{
		frun();
	}
	
	
	int m[7][2]=
	{
		{ 0, 0},
		{ 0, 2},
		{ 2, 0},
		{-2, 0},
		{ 0,-2},
		{ 1, 1},
		{-1,-1}
	};
	int r=getrand(1,6);
	while(goout(plx+m[r][0],ply+m[r][1]))
	{
		r=getrand(1,6);
	}
	plx+=m[r][0];
	ply+=m[r][1];
	room2(); 
}

void ffight(int n)
{
	system("cls");system("color 0F");
	go(3,1);cout<<zhiye[plzhiye].name;	
	go(12,1);cout<<mon[boci][n].name;
	
	go(2,3);cout<<"生命值："<<shengming();	
	go(11,3);cout<<"生命值："<<mon[boci][n].shengming;
	go(2,4);cout<<"体力值："<<tili();
	go(2,5);cout<<"伤害值："<<shanghai();
	go(11,5);cout<<"伤害值："<<mon[boci][n].shanghai;	
	go(2,6);cout<<"免伤率："<<mianshang(mon[boci][n].type)<<"%";
	go(11,6);cout<<"免伤率："<<mon[boci][n].mianshang<<"%";
	go(2,7);cout<<"暴击率："<<baoji()<<"%";
	go(11,7);cout<<"暴击率："<<mon[boci][n].baoji<<"%";
	go(2,8);cout<<"闪避率："<<shanbi()<<"%";
	go(11,8);cout<<"闪避率："<<mon[boci][n].shanbi<<"%";
	
	go(4,10);printf("轻轻攻击（伤害值25，消耗2体力值）");
	go(4,11);printf("普通攻击（伤害值80，消耗8体力值）");
	go(4,12);printf("大力攻击（伤害值160，消耗20体力值）");
	go(4,13);printf("退出");
	int a=1;
	int key=0;
	go(2,9+a);printf(">>");
	while(key!=13)
	{
		key=getch();
		go(2,9+a);printf("  ");
		if(key=='w'||key=='W')
		{
			a--;
			if(a<1)a+=4;
		}
		else if(key=='s'||key=='S')
		{
			a++;
			if(a>4)a-=4;
		}
		go(2,9+a);printf(">>");
	} 
	if(a==4)
	{
		fight(n);return;
	}
	if(a==1)
	{
		if(getrand(1,100)>mon[boci][n].shanbi)
		{
			float b=(shanghai()+25)*(100-mon[boci][n].mianshang)/100;
			if(getrand(1,100)<baoji())
			{
				b*=1.5;
				go(1,2);printf("(暴击)");  Sleep(500);
			}
			mon[boci][n].shengming-=b;
		}
		else
		{
			go(13,2);printf("(闪避)");  Sleep(500);
		} 
		zhiye[plzhiye].tili-=2; 
		if(tili()<=0)
		{
			system("cls");
			system("color 0F");
			go(6,6);printf("你累死了。");
			baoshi=-999999999;
			Sleep(10000);	
		}
	}
	if(a==2)
	{
		if(getrand(1,100)>mon[boci][n].shanbi)
		{
			float b=(shanghai()+80)*(100-mon[boci][n].mianshang)/100;
			if(getrand(1,100)<baoji())
			{
				b*=1.5;
				go(1,2);printf("(暴击)");  Sleep(500);
			}
			mon[boci][n].shengming-=b;
		}
		else
		{
			go(13,2);printf("(闪避)");  Sleep(500);
		} 
		zhiye[plzhiye].tili-=8; 
		if(tili()<=0)
		{
			system("cls");
			system("color 0F");
			go(6,6);printf("你累死了。");
			baoshi=-999999999;	
			Sleep(10000);
		}
	}
	if(a==3)
	{
		if(getrand(1,100)>mon[boci][n].shanbi)
		{
			float b=(shanghai()+160)*(100-mon[boci][n].mianshang)/100;
			if(getrand(1,100)<baoji())
			{
				b*=1.5;
				go(1,2);printf("(暴击)"); Sleep(500);
			}
			mon[boci][n].shengming-=b;
		}
		else
		{
			go(13,2);printf("(闪避)");  Sleep(500);
		} 
		zhiye[plzhiye].tili-=20;
		if(tili()<=0)
		{
			system("cls");
			system("color 0F");
			go(6,6);printf("你累死了。");
			baoshi=-999999999;	
			Sleep(10000);
		} 

	}
	
	if(getrand(1,100)>shanbi())
	{
		float c=mon[boci][n].shanghai*(100-mianshang(mon[boci][n].type))/100;
		if(getrand(1,100)<mon[boci][n].baoji)
		{
			c*=1.5;
			go(10,2);printf("(暴击)"); Sleep(500);
		}
		zhiye[plzhiye].shengming-=c;
	}
	else
	{
		go(4,2);printf("(闪避)");  Sleep(500);
	} 
	if(mon[boci][n].shengming>0&&shengming()>0&&tili()>0) 
	{
		ffight(n);
		return; 
	}
	if(mon[boci][n].shengming<=0)
	{
		mon[boci][n].alive=0;
		system("cls");
		system("color 0F");
		go(6,6);printf("怪物被打败了！获得%d个宝石！",mon[boci][n].baoshi);
		baoshi+=mon[boci][n].baoshi; 
		if(mon[boci][n].drop==1&&getrand(1,100)<40)
		{
			if(fangju[4].have==0)
			{
				fangbag[++fangbag[0]]=4;
				fangju[4].have=1; 
				go(6,7);printf("获得战利品：铁甲！");
				if(nowpet!=-1)nowpet++;
			}
			else
			{
				baoshi+=fangju[4].much/2;
				go(6,7);printf("获得战利品：铁甲！（已转换为宝石）");
			}
		}
		if(mon[boci][n].drop==2&&getrand(1,100)<45)
		{
			if(fangju[2].have==0)
			{
				fangbag[++fangbag[0]]=2;
				fangju[2].have=1; 
				go(6,7);printf("获得战利品：铁裤！");
				if(nowpet!=-1)nowpet++;
			}
			else
			{
				baoshi+=fangju[2].much/2;
				go(6,7);printf("获得战利品：铁裤！（已转换为宝石）");
			}
		}
		if(mon[boci][n].drop==3&&getrand(1,100)<45)
		{
			if(fangju[5].have==0)
			{
				fangbag[++fangbag[0]]=5;
				fangju[5].have=1; 
				go(6,7);printf("获得战利品：钻甲！");
				if(nowpet!=-1)nowpet++;
			}
			else
			{
				baoshi+=fangju[5].much/2;
				go(6,7);printf("获得战利品：钻甲！（已转换为宝石）");
			}
		}
		if(mon[boci][n].drop==4&&getrand(1,100)<50)
		{
			if(fangju[3].have==0)
			{
				fangbag[++fangbag[0]]=3;
				fangju[3].have=1; 
				go(6,7);printf("获得战利品：钻裤！");
				if(nowpet!=-1)nowpet++;
			}
			else
			{
				baoshi+=fangju[3].much/2;
				go(6,7);printf("获得战利品：钻裤！（已转换为宝石）");
			}
		}
		if(mon[boci][n].drop==5&&getrand(1,100)<40) 
		{
			if(wuqi[1].have==0&&plzhiye==1)
			{
				wubag[++wubag[0]]=1;
				wuqi[1].have=1;
				go(6,7);printf("获得战利品：竹箭！");
				if(nowpet!=-1)nowpet++;
				if(nowfang.dun!=-1)nowfang.dun++;
				if(nowfang.jia!=-1)nowfang.jia++;
				if(nowfang.ku!=-1)nowfang.ku++;
			}
			else
			{
				baoshi+=wuqi[1].much/2;
				go(6,7);printf("获得战利品：竹箭！（已转换为宝石）");
			}
		}
		if(mon[boci][n].drop==6&&getrand(1,100)<45)
		{
			if(wuqi[2].have==0&&plzhiye==1)
			{
				wubag[++wubag[0]]=2;
				wuqi[2].have=1;
				go(6,7);printf("获得战利品：铁箭！");
				if(nowpet!=-1)nowpet++;
				if(nowfang.dun!=-1)nowfang.dun++;
				if(nowfang.jia!=-1)nowfang.jia++;
				if(nowfang.ku!=-1)nowfang.ku++;
			}
			else
			{
				baoshi+=wuqi[2].much/2;
				go(6,7);printf("获得战利品：铁箭！（已转换为宝石）");
			}
		}
		if(mon[boci][n].drop==7&&getrand(1,100)<40)
		{
			if(wuqi[3].have==0&&plzhiye==1)
			{
				wubag[++wubag[0]]=3;
				wuqi[3].have=1;
				go(6,7);printf("获得战利品：火箭！");
				if(nowpet!=-1)nowpet++;
				if(nowfang.dun!=-1)nowfang.dun++;
				if(nowfang.jia!=-1)nowfang.jia++;
				if(nowfang.ku!=-1)nowfang.ku++;				
			}
			else
			{
				baoshi+=wuqi[3].much/2;
				go(6,7);printf("获得战利品：火箭！（已转换为宝石）");
			}
		}
		Sleep(1000);
		if(n==4&&boci!=7) boci++,slept=0;
		else if(n==4&&boci==7) win();
	}
	if(shengming()<=0)
	{
		system("cls");
		system("color 0F");
		go(6,6);printf("你牺牲了。");
		Sleep(15000);
	} 
} 
void frun()
{
	zhiye[plzhiye].tili-=10;
	if(tili()<=0)
	{
		system("cls");
		system("color 0F");
		go(6,6);printf("你累死了。");
		baoshi=-999999999;	
		Sleep(10000);
	} 
}
void win()
{
	if(shengming()<=0)return; 
	boci++;
	printright();
	printmap();
	int shape[14][20]=
	{
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,1,0,0,0,3,0,0,9,8,19,0,0,20,0,0,0,30,0,0},
		{0,0,2,0,4,0,0,10,0,0,0,18,0,21,0,0,0,29,0,0},
		{0,0,0,5,0,0,0,11,0,0,0,17,0,22,0,0,0,28,0,0},
		{0,0,0,6,0,0,0,12,0,0,0,16,0,23,0,0,0,27,0,0},
		{0,0,0,7,0,0,0,0,13,14,15,0,0,0,24,25,26,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,31,0,0,0,43,0,44,45,46,0,53,0,0,0,62,0,66,0,0},
		{0,32,0,38,0,42,0,0,47,0,0,54,58,0,0,63,0,67,0,0},
		{0,33,0,37,0,41,0,0,48,0,0,55,0,59,0,64,0,68,0,0},
		{0,34,0,36,0,40,0,0,49,0,0,56,0,0,60,65,0,0,0,0},
		{0,0,35,0,39,0,0,50,51,52,0,57,0,0,0,61,0,69,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	};
	color(79);
	for(int k=1;k<=69;k++)
	for(int i=1;i<=12;i++)
	{
		for(int j=1;j<=17;j++)
		{
			if(shape[i][j]==k)
			{
				go(j,i);
				printf("■");
				Sleep(50);
			}
		}		
	}color(15);
	Sleep(1510); 
}

