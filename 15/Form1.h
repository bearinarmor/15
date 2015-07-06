#pragma once

#include <cstdlib>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
namespace My15 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// —водка дл€ Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	private:
		int **board;
		int **lock;
		int target;
		int step;
		int flag;
		int *F;
		int *G;
		int *H;
		int *open;//открытый и закрытый список сразу 1-открытый, 2-закрытый
		int *parent;
	public:
		
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
			flag=0;
			board=(int **)malloc(4*sizeof(int*));
			for (int i=0; i<=3; i++){
				board[i] = (int*) malloc (4*sizeof(int));
			};
			lock=(int **)malloc(6*sizeof(int*));
			for (int i=0; i<=5; i++){
				lock[i] = (int*) malloc (6*sizeof(int));
			};
			for(int i=0; i<=3;i++){//обнулим
				for(int j=0; j<=3; j++){
					board[i][j]=0;
					lock[i+1][j+1]=0;
				}
			}
			for(int i=0; i<=5; i++){
				lock[i][0]=1;
				lock[i][5]=1;
				lock[0][i]=1;
				lock[5][i]=1;
			}
			F= (int*) malloc (17*sizeof(int));
			G=(int*) malloc (17*sizeof(int));
			H=(int*) malloc (17*sizeof(int));
			open=(int*) malloc (17*sizeof(int));
			parent=(int*) malloc (17*sizeof(int));
			/* initialize random seed: */
			srand (time(NULL));
			for(int i=1; i<=15; i++){//расставим числа в случайные €чейки
				int flag=1;
				while(flag==1){//пытаемс€ запихнуть число в случайную €чейку, при условии, что она свободна
					int x=rand() % 4;
					int y=rand() % 4;
					if(board[x][y]==0){
						board[x][y]=i;
						flag=0;
					};
				};
			}
			//выведем полученное поле
			if(board[0][0]!=0){this->button1->Text = board[0][0].ToString();}else{this->button1->Text =L"";};
			if(board[0][1]!=0){this->button2->Text = board[0][1].ToString();}else{this->button2->Text =L"";};
			if(board[0][2]!=0){this->button3->Text = board[0][2].ToString();}else{this->button3->Text =L"";};
			if(board[0][3]!=0){this->button4->Text = board[0][3].ToString();}else{this->button4->Text =L"";};
			if(board[1][0]!=0){this->button5->Text = board[1][0].ToString();}else{this->button5->Text =L"";};
			if(board[1][1]!=0){this->button6->Text = board[1][1].ToString();}else{this->button6->Text =L"";};
			if(board[1][2]!=0){this->button7->Text = board[1][2].ToString();}else{this->button7->Text =L"";};
			if(board[1][3]!=0){this->button8->Text = board[1][3].ToString();}else{this->button8->Text =L"";};
			if(board[2][0]!=0){this->button9->Text = board[2][0].ToString();}else{this->button9->Text =L"";};
			if(board[2][1]!=0){this->button10->Text = board[2][1].ToString();}else{this->button10->Text =L"";};
			if(board[2][2]!=0){this->button11->Text = board[2][2].ToString();}else{this->button11->Text =L"";};
			if(board[2][3]!=0){this->button12->Text = board[2][3].ToString();}else{this->button12->Text =L"";};
			if(board[3][0]!=0){this->button13->Text = board[3][0].ToString();}else{this->button13->Text =L"";};
			if(board[3][1]!=0){this->button14->Text = board[3][1].ToString();}else{this->button14->Text =L"";};
			if(board[3][2]!=0){this->button15->Text = board[3][2].ToString();}else{this->button15->Text =L"";};
			if(board[3][3]!=0){this->button16->Text = board[3][3].ToString();}else{this->button16->Text =L"";};
			
		}
		int is_spase_around(int x, int y){//возвращает 1, если пуста€ клетка слева, 2 - сверху, 3 справа, 4 снизу
			if((y>=1) && (board[x][y-1]==0)) return 1;
			if((x>=1) && (board[x-1][y]==0)) return 2;
			if((y<=2) && (board[x][y+1]==0)) return 3;
			if((x<=2) && (board[x+1][y]==0)) return 4;
			return 0;
		}
		void cell_clik(int x, int y){
			switch(x){
			case 0://row1
				switch(y){
				case 0://button1
					switch(is_spase_around(0, 0)){
						int tmp;
						case 3:
							tmp=board[0][0];
							board[0][0]=board[0][1];
							board[0][1]=tmp;
							this->button1->Text=L"";
							this->button2->Text=board[0][1].ToString();
							break;
						case 4:
							tmp=board[0][0];
							board[0][0]=board[1][0];
							board[1][0]=tmp;
							this->button1->Text=L"";
							this->button5->Text=board[1][0].ToString();
							break;
						}
					this->Invalidate();
					break;
				case 1://button2
					switch(is_spase_around(0, 1)){
						int tmp;
						case 1:
							tmp=board[0][1];
							board[0][1]=board[0][0];
							board[0][0]=tmp;
							this->button2->Text=L"";
							this->button1->Text=board[0][0].ToString();
							break;
						case 3:
							tmp=board[0][1];
							board[0][1]=board[0][2];
							board[0][2]=tmp;
							this->button2->Text=L"";
							this->button3->Text=board[0][2].ToString();
							break;
						case 4:
							tmp=board[0][1];
							board[0][1]=board[1][1];
							board[1][1]=tmp;
							this->button2->Text=L"";
							this->button6->Text=board[1][1].ToString();
							break;
					}
					this->Invalidate();
					break;
				case 2://button3
					switch(is_spase_around(0, 2)){
						int tmp;
						case 1:
							tmp=board[0][2];
							board[0][2]=board[0][1];
							board[0][1]=tmp;
							this->button3->Text=L"";
							this->button2->Text=board[0][1].ToString();
							break;
						case 3:
							tmp=board[0][2];
							board[0][2]=board[0][3];
							board[0][3]=tmp;
							this->button3->Text=L"";
							this->button4->Text=board[0][3].ToString();
							break;
						case 4:
							tmp=board[0][2];
							board[0][2]=board[1][2];
							board[1][2]=tmp;
							this->button3->Text=L"";
							this->button7->Text=board[1][2].ToString();
							break;
					}
					this->Invalidate();
					break;
				case 3://button4
					switch(is_spase_around(0, 3)){
						int tmp;
						case 1:
							tmp=board[0][3];
							board[0][3]=board[0][2];
							board[0][2]=tmp;
							this->button4->Text=L"";
							this->button3->Text=board[0][2].ToString();
							break;
						case 4:
							tmp=board[0][3];
							board[0][3]=board[1][3];
							board[1][3]=tmp;
							this->button4->Text=L"";
							this->button8->Text=board[1][3].ToString();
							break;
					}
					this->Invalidate();
					break;
				}
				break;			
			case 1://row2
				switch(y){
				case 0://button5
					switch(is_spase_around(1, 0)){
						int tmp;
						case 2:
							tmp=board[1][0];
							board[1][0]=board[0][0];
							board[0][0]=tmp;
							this->button5->Text=L"";
							this->button1->Text=board[0][0].ToString();
							break;
						case 3:
							tmp=board[1][0];
							board[1][0]=board[1][1];
							board[1][1]=tmp;
							this->button5->Text=L"";
							this->button6->Text=board[1][1].ToString();
							break;
						case 4:
							tmp=board[1][0];
							board[1][0]=board[2][0];
							board[2][0]=tmp;
							this->button5->Text=L"";
							this->button9->Text=board[2][0].ToString();
							break;
					}
					this->Invalidate();
					break;
				case 1://button6
					switch(is_spase_around(1, 1)){
						int tmp;
						case 1:
							tmp=board[1][1];
							board[1][1]=board[1][0];
							board[1][0]=tmp;
							this->button6->Text=L"";
							this->button5->Text=board[1][0].ToString();
							break;
						case 2:
							tmp=board[1][1];
							board[1][1]=board[0][1];
							board[0][1]=tmp;
							this->button6->Text=L"";
							this->button2->Text=board[0][1].ToString();
							break;
						case 3:
							tmp=board[1][1];
							board[1][1]=board[1][2];
							board[1][2]=tmp;
							this->button6->Text=L"";
							this->button7->Text=board[1][2].ToString();
							break;
						case 4:
							tmp=board[1][1];
							board[1][1]=board[2][1];
							board[2][1]=tmp;
							this->button6->Text=L"";
							this->button10->Text=board[2][1].ToString();
							break;
					}
					this->Invalidate();
					break;
				case 2://button7
					switch(is_spase_around(1, 2)){
						int tmp;
						case 1:
							tmp=board[1][2];
							board[1][2]=board[1][1];
							board[1][1]=tmp;
							this->button7->Text=L"";
							this->button6->Text=board[1][1].ToString();
							break;
						case 2:
							tmp=board[1][2];
							board[1][2]=board[0][2];
							board[0][2]=tmp;
							this->button7->Text=L"";
							this->button3->Text=board[0][2].ToString();
							break;
						case 3:
							tmp=board[1][2];
							board[1][2]=board[1][3];
							board[1][3]=tmp;
							this->button7->Text=L"";
							this->button8->Text=board[1][3].ToString();
							break;
						case 4:
							tmp=board[1][2];
							board[1][2]=board[2][2];
							board[2][2]=tmp;
							this->button7->Text=L"";
							this->button11->Text=board[2][2].ToString();
							break;
					}
					this->Invalidate();
					break;
				case 3://button8
					switch(is_spase_around(1, 3)){
						int tmp;
						case 1:
							tmp=board[1][3];
							board[1][3]=board[1][2];
							board[1][2]=tmp;
							this->button8->Text=L"";
							this->button7->Text=board[1][2].ToString();
							break;
						case 2:
							tmp=board[1][3];
							board[1][3]=board[0][3];
							board[0][3]=tmp;
							this->button8->Text=L"";
							this->button4->Text=board[0][3].ToString();
							break;
						case 4:
							tmp=board[1][3];
							board[1][3]=board[2][3];
							board[2][3]=tmp;
							this->button8->Text=L"";
							this->button12->Text=board[2][3].ToString();
							break;
					}
					this->Invalidate();
					break;
				}
				break;
			case 2://row3
				switch(y){
				case 0://button9
					switch(is_spase_around(2, 0)){
						int tmp;
						case 2:
							tmp=board[2][0];
							board[2][0]=board[1][0];
							board[1][0]=tmp;
							this->button9->Text=L"";
							this->button5->Text=board[1][0].ToString();
							break;
						case 3:
							tmp=board[2][0];
							board[2][0]=board[2][1];
							board[2][1]=tmp;
							this->button9->Text=L"";
							this->button10->Text=board[2][1].ToString();
							break;
						case 4:
							tmp=board[2][0];
							board[2][0]=board[3][0];
							board[3][0]=tmp;
							this->button9->Text=L"";
							this->button13->Text=board[3][0].ToString();
							break;
					}
					this->Invalidate();
					break;
				case 1://button10
					 switch(is_spase_around(2, 1)){
						int tmp;
						case 1:
							tmp=board[2][1];
							board[2][1]=board[2][0];
							board[2][0]=tmp;
							this->button10->Text=L"";
							this->button9->Text=board[2][0].ToString();
							break;
						case 2:
							tmp=board[2][1];
							board[2][1]=board[1][1];
							board[1][1]=tmp;
							this->button10->Text=L"";
							this->button6->Text=board[1][1].ToString();
							break;
						case 3:
							tmp=board[2][1];
							board[2][1]=board[2][2];
							board[2][2]=tmp;
							this->button10->Text=L"";
							this->button11->Text=board[2][2].ToString();
							break;
						case 4:
							tmp=board[2][1];
							board[2][1]=board[3][1];
							board[3][1]=tmp;
							this->button10->Text=L"";
							this->button14->Text=board[3][1].ToString();
							break;
					}
					this->Invalidate();
					break;
				case 2://button11
					switch(is_spase_around(2, 2)){
						int tmp;
						case 1:
							tmp=board[2][2];
							board[2][2]=board[2][1];
							board[2][1]=tmp;
							this->button11->Text=L"";
							this->button10->Text=board[2][1].ToString();
							break;
						case 2:
							tmp=board[2][2];
							board[2][2]=board[1][2];
							board[1][2]=tmp;
							this->button11->Text=L"";
							this->button7->Text=board[1][2].ToString();
							break;
						case 3:
							tmp=board[2][2];
							board[2][2]=board[2][3];
							board[2][3]=tmp;
							this->button11->Text=L"";
							this->button12->Text=board[2][3].ToString();
							break;
						case 4:
							tmp=board[2][2];
							board[2][2]=board[3][2];
							board[3][2]=tmp;
							this->button11->Text=L"";
							this->button15->Text=board[3][2].ToString();
							break;
					}
					this->Invalidate();
					break;
				case 3://button12
					switch(is_spase_around(2, 3)){
						int tmp;
						case 1:
							tmp=board[2][3];
							board[2][3]=board[2][2];
							board[2][2]=tmp;
							this->button12->Text=L"";
							this->button11->Text=board[2][2].ToString();
							break;
						case 2:
							tmp=board[2][3];
							board[2][3]=board[1][3];
							board[1][3]=tmp;
							this->button12->Text=L"";
							this->button8->Text=board[1][3].ToString();
							break;
						case 4:
							tmp=board[2][3];
							board[2][3]=board[3][3];
							board[3][3]=tmp;
							this->button12->Text=L"";
							this->button16->Text=board[3][3].ToString();
						break;
					}
					this->Invalidate();
					break;
				}
				break;
			case 3://row4
				switch(y){
				case 0://button13
					switch(is_spase_around(3, 0)){
						int tmp;
						case 2:
							tmp=board[3][0];
							board[3][0]=board[2][0];
							board[2][0]=tmp;
							this->button13->Text=L"";
							this->button9->Text=board[2][0].ToString();
							break;
						case 3:
							tmp=board[3][0];
							board[3][0]=board[3][1];
							board[3][1]=tmp;
							this->button13->Text=L"";
							this->button14->Text=board[3][1].ToString();
							break;
					}
					this->Invalidate();
					break;
				case 1://button14
					switch(is_spase_around(3, 1)){
						int tmp;
						case 1:
							tmp=board[3][1];
							board[3][1]=board[3][0];
							board[3][0]=tmp;
							this->button14->Text=L"";
							this->button13->Text=board[3][0].ToString();
							break;
						case 2:
							tmp=board[3][1];
							board[3][1]=board[2][1];
							board[2][1]=tmp;
							this->button14->Text=L"";
							this->button10->Text=board[2][1].ToString();
							break;
						case 3:
							tmp=board[3][1];
							board[3][1]=board[3][2];
							board[3][2]=tmp;
							this->button14->Text=L"";
							this->button15->Text=board[3][2].ToString();
							break;
					}
					this->Invalidate();
					break;
				case 2://button15
					switch(is_spase_around(3, 2)){
						int tmp;
						case 1:
							tmp=board[3][2];
							board[3][2]=board[3][1];
							board[3][1]=tmp;
							this->button15->Text=L"";
							this->button14->Text=board[3][1].ToString();
							break;
						case 2:
							tmp=board[3][2];
							board[3][2]=board[2][2];
							board[2][2]=tmp;
							this->button15->Text=L"";
							this->button11->Text=board[2][2].ToString();
							break;
						case 3:
							tmp=board[3][2];
							board[3][2]=board[3][3];
							board[3][3]=tmp;
							this->button15->Text=L"";
							this->button16->Text=board[3][3].ToString();
							break;
					}
					this->Invalidate();
					break;
				case 3://button16
					switch(is_spase_around(3, 3)){
						int tmp;
						case 1:
							tmp=board[3][3];
							board[3][3]=board[3][2];
							board[3][2]=tmp;
							this->button16->Text=L"";
							this->button15->Text=board[3][2].ToString();
							break;
						case 2:
							tmp=board[3][3];
							board[3][3]=board[2][3];
							board[2][3]=tmp;
							this->button16->Text=L"";
							this->button12->Text=board[2][3].ToString();
							break;
					}
					this->Invalidate();
					break;
				}
				break;
			}
			
		}
		int find_zero(){
			for(int i=0; i<=3; i++){
				for(int j=0; j<=3; j++){
					if(board[i][j]==0) return (i*4+j+1);
				}
			}
		}	
		int find_num(int x){
			for(int i=0; i<=3; i++){
				for(int j=0; j<=3; j++){
					if(board[i][j]==x) return (i*4+j+1);
				}
			}
		}
		void set_direction(){//в каком направлении двигать
			int x1=(find_zero()-1)/4;
			int x2=(target-1)/4;
			if((x1-x2)!=0){//по вертикали
				if(x1-x2>0){//вверх
					flag=0;
				}
				else{//вниз
					flag=2;
				}
			}
			else{//по горизонтали
				if((find_zero()-1)%4-(target-1)%4>0){//налево
					flag=3;
				}
				else{//направо
					flag=1;
				}
			}
			
		}
		void set_target(int start, int goal){//определим куда двигать пустую клетку
			int x1=(start-1)/4;
			int x2=(goal-1)/4;
			int flag3=0;
			if((x1-x2)!=0){//по вертикали
				if(x1-x2>0){//вверх
					if(lock[x1][(start-1)%4+1]==0){
						target=start-4;
						flag3=1;
					}
				}
				else{//вниз
					if(lock[x1+2][(start-1)%4+1]==0){
						target=start+4;
						flag3=1;
					}
				}
			}
			if(flag3==0){//по горизонтали если по вертикали не получилось
				if((start-1)%4-(goal-1)%4>0){//налево
					if(lock[x1+1][(start-1)%4]==0){
						target=start-1;
						set_direction();
					}
				}
				else{//направо
					if(lock[x1+1][(start-1)%4+2]==0){
						target=start+1;
						set_direction();
					}
				}
			}
		}
		int manhattan(int num){
			int x1=(num-1)/4;
			int y1=(num-1)%4;
			int x2=(find_zero()-1)/4;
			int y2=(find_zero()-1)%4;
			return abs(x1-x2)+abs(y1-y2);
		}
		void a_cell_check(int num, int cur){
			if(open[num]==0){
				open[num]=1;
				G[num]=G[cur]+1;
				H[num]=manhattan(num);
				F[num]=G[num]+H[num];
				parent[num]=cur;
				int g_cur=G[num];
				int h_cur=H[num];
				int f_cur=F[num];
			}
			else{
				if(open[num]==1){
					int G_tmp=G[cur]+1;
					if(G_tmp<G[num]){
						G[num]=G_tmp;
						F[num]=G[num]+H[num];
						parent[num]=cur;
				int g_cur=G[num];
				int h_cur=H[num];
				int f_cur=F[num];
					}
				}
			}
		}
		void move_zero(){
			//A*
			while(find_zero()!=target){
				for(int i=0; i<=16; i++){
					F[i]=0;
					G[i]=0;
					H[i]=0;
					if(lock[(i-1)/4+1][(i-1)%4+1]==0){
						open[i]=0;
					}
					else{
						open[i]=2;
					}
					//parent[i]=16;
				}
				//parent[16]=16;
				int cur=target;
				parent[cur]=cur;
				int flag1=0;
				while(flag1==0){				
					open[cur]=2;
					if((cur-1)==find_zero() || (cur+1)==find_zero() || (cur-4)==find_zero() || (cur+4)==find_zero()) flag1=1;
					if(cur!=1 && cur!=5 && cur!=9 && cur!=13){
						a_cell_check(cur-1, cur);
					}
					if(cur!=4 && cur!=8 && cur!=12 && cur!=16){
						a_cell_check(cur+1, cur);
					}	
					if(cur!=1 && cur!=2 && cur!=3 && cur!=4){
						a_cell_check(cur-4, cur);
					}
					if(cur!=13 && cur!=14 && cur!=15 && cur!=16){
						a_cell_check(cur+4, cur);
					}
					int f0=F[0];
					int f1=F[1];
					int f2=F[2];
					int f3=F[3];
					int f4=F[4];
					int f5=F[5];
					int f6=F[6];
					int f7=F[7];
					int f8=F[8];
					int f9=F[9];
					int f10=F[10];
					int f11=F[11];
					int f12=F[12];
					int f13=F[13];
					int f14=F[14];
					int f15=F[15];
					int f16=F[16];
					int F_tmp=99999;
					for(int i=1; i<=16; i++){
						if(open[i]==1){
							if(F[i]<=F_tmp){
								cur=i;
								F_tmp=F[i];
							}
						}
					}
				}
				while(find_zero()!=target){
					int parent0=parent[0];
					int parent1=parent[1];
					int parent2=parent[2];
					int parent3=parent[3];
					int parent4=parent[4];
					int parent5=parent[5];
					int parent6=parent[6];
					int parent7=parent[7];
					int parent8=parent[8];
					int parent9=parent[9];
					int parent10=parent[10];
					int parent11=parent[11];
					int parent12=parent[12];
					int parent13=parent[13];
					int parent14=parent[14];
					int parent15=parent[15];
					int parent16=parent[16];
					int lock1=lock[1][1];
					int lock2=lock[1][2];
					int lock3=lock[1][3];
					int lock4=lock[1][4];
					int lock5=lock[2][1];
					int lock6=lock[2][2];
					int lock7=lock[2][3];
					int lock8=lock[2][4];
					int lock9=lock[3][1];
					int lock10=lock[3][2];
					int lock11=lock[3][3];
					int lock12=lock[3][4];
					int lock13=lock[4][1];
					int lock14=lock[4][2];
					int lock15=lock[4][3];
					int lock16=lock[4][4];
					cell_clik((parent[find_zero()]-1)/4, (parent[find_zero()]-1)%4);
				}

			//тут надо написать возвращение по маршруту
			/*int j=target;
			int path[8];
			int p=0;
			path[p]=j;
			int flag2=0;
			while(flag2==0){
				j=parent[j];
				if(find_zero()==j){
					flag2=1;
				}
				p++;
				path[p]=j;
			}
			p--;
			while(p>=0){
				cell_clik((path[p]-1)/4,(path[p]-1)%4);
				p--;
			}*/
			}
			//стара€ реализаци€
			/*while(find_zero()!=target){
				int x=(find_zero()-1)/4;
				int y=(find_zero()-1)%4;
				if(((x-(target-1)/4)>0)||flag==0){ //вверх
					if(lock[x][y+1]==0){
						cell_clik(x-1,y);
						flag=0;
						continue;
					}
					else{
						flag=(flag+4+((rand()%2)-1))%4;
					}
				}
				if(((y-(target-1)%4)<0)||flag==1){//направо
					if(lock[x+1][y+2]==0){
						cell_clik(x,y+1);
						flag=1;
						continue;
					}
					else{
						flag=(flag+4+((rand()%2)-1))%4;
					}
				}
				if(((x-(target-1)/4)<0)||flag==2){ //вниз
					if(lock[x+2][y+1]==0){
						cell_clik(x+1,y);
						flag=2;
						continue;
					}
					else{
						flag=(flag+4+((rand()%2)-1))%4;
					}
				}
				if(((y-(target-1)%4)>0)||flag==3){//налево
					if(lock[x+1][y]==0){
						cell_clik(x,y-1);
						flag=3;
						continue;
					}
					else{
						flag=(flag+4+((rand()%2)-1))%4;
					}
				}
			}*/
		}

	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
			for(int i=0; i<=3; i++) free(board[i]);
			free(board);
			for(int i=0; i<=5; i++) free(lock[i]);
			free(lock);
			free(F);
			free(G);
			free(H);
			free(open);
			free(parent);
		}
	private: System::Windows::Forms::Button^  button1;
	protected: 
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::Button^  button5;
	private: System::Windows::Forms::Button^  button6;
	private: System::Windows::Forms::Button^  button7;
	private: System::Windows::Forms::Button^  button8;
	private: System::Windows::Forms::Button^  button9;
	private: System::Windows::Forms::Button^  button10;
	private: System::Windows::Forms::Button^  button11;
	private: System::Windows::Forms::Button^  button12;
	private: System::Windows::Forms::Button^  button13;
	private: System::Windows::Forms::Button^  button14;
	private: System::Windows::Forms::Button^  button15;
	private: System::Windows::Forms::Button^  button16;
	private: System::Windows::Forms::Button^  button17;

	private:
		/// <summary>
		/// “ребуетс€ переменна€ конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// ќб€зательный метод дл€ поддержки конструктора - не измен€йте
		/// содержимое данного метода при помощи редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->button7 = (gcnew System::Windows::Forms::Button());
			this->button8 = (gcnew System::Windows::Forms::Button());
			this->button9 = (gcnew System::Windows::Forms::Button());
			this->button10 = (gcnew System::Windows::Forms::Button());
			this->button11 = (gcnew System::Windows::Forms::Button());
			this->button12 = (gcnew System::Windows::Forms::Button());
			this->button13 = (gcnew System::Windows::Forms::Button());
			this->button14 = (gcnew System::Windows::Forms::Button());
			this->button15 = (gcnew System::Windows::Forms::Button());
			this->button16 = (gcnew System::Windows::Forms::Button());
			this->button17 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(13, 11);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(50, 50);
			this->button1->TabIndex = 1;
			this->button1->Text = L"1";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(70, 13);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(50, 50);
			this->button2->TabIndex = 2;
			this->button2->Text = L"2";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(127, 13);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(50, 50);
			this->button3->TabIndex = 3;
			this->button3->Text = L"3";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &Form1::button3_Click);
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(184, 13);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(50, 50);
			this->button4->TabIndex = 4;
			this->button4->Text = L"4";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &Form1::button4_Click);
			// 
			// button5
			// 
			this->button5->Location = System::Drawing::Point(13, 70);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(50, 50);
			this->button5->TabIndex = 5;
			this->button5->Text = L"5";
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Click += gcnew System::EventHandler(this, &Form1::button5_Click);
			// 
			// button6
			// 
			this->button6->Location = System::Drawing::Point(70, 70);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(50, 50);
			this->button6->TabIndex = 6;
			this->button6->Text = L"6";
			this->button6->UseVisualStyleBackColor = true;
			this->button6->Click += gcnew System::EventHandler(this, &Form1::button6_Click);
			// 
			// button7
			// 
			this->button7->Location = System::Drawing::Point(127, 70);
			this->button7->Name = L"button7";
			this->button7->Size = System::Drawing::Size(50, 50);
			this->button7->TabIndex = 7;
			this->button7->Text = L"7";
			this->button7->UseVisualStyleBackColor = true;
			this->button7->Click += gcnew System::EventHandler(this, &Form1::button7_Click);
			// 
			// button8
			// 
			this->button8->Location = System::Drawing::Point(184, 70);
			this->button8->Name = L"button8";
			this->button8->Size = System::Drawing::Size(50, 50);
			this->button8->TabIndex = 8;
			this->button8->Text = L"8";
			this->button8->UseVisualStyleBackColor = true;
			this->button8->Click += gcnew System::EventHandler(this, &Form1::button8_Click);
			// 
			// button9
			// 
			this->button9->Location = System::Drawing::Point(13, 127);
			this->button9->Name = L"button9";
			this->button9->Size = System::Drawing::Size(50, 50);
			this->button9->TabIndex = 9;
			this->button9->Text = L"9";
			this->button9->UseVisualStyleBackColor = true;
			this->button9->Click += gcnew System::EventHandler(this, &Form1::button9_Click);
			// 
			// button10
			// 
			this->button10->Location = System::Drawing::Point(70, 127);
			this->button10->Name = L"button10";
			this->button10->Size = System::Drawing::Size(50, 50);
			this->button10->TabIndex = 10;
			this->button10->Text = L"10";
			this->button10->UseVisualStyleBackColor = true;
			this->button10->Click += gcnew System::EventHandler(this, &Form1::button10_Click);
			// 
			// button11
			// 
			this->button11->Location = System::Drawing::Point(127, 127);
			this->button11->Name = L"button11";
			this->button11->Size = System::Drawing::Size(50, 50);
			this->button11->TabIndex = 11;
			this->button11->Text = L"11";
			this->button11->UseVisualStyleBackColor = true;
			this->button11->Click += gcnew System::EventHandler(this, &Form1::button11_Click);
			// 
			// button12
			// 
			this->button12->Location = System::Drawing::Point(184, 127);
			this->button12->Name = L"button12";
			this->button12->Size = System::Drawing::Size(50, 50);
			this->button12->TabIndex = 12;
			this->button12->Text = L"12";
			this->button12->UseVisualStyleBackColor = true;
			this->button12->Click += gcnew System::EventHandler(this, &Form1::button12_Click);
			// 
			// button13
			// 
			this->button13->Location = System::Drawing::Point(13, 184);
			this->button13->Name = L"button13";
			this->button13->Size = System::Drawing::Size(50, 50);
			this->button13->TabIndex = 13;
			this->button13->Text = L"13";
			this->button13->UseVisualStyleBackColor = true;
			this->button13->Click += gcnew System::EventHandler(this, &Form1::button13_Click);
			// 
			// button14
			// 
			this->button14->Location = System::Drawing::Point(70, 184);
			this->button14->Name = L"button14";
			this->button14->Size = System::Drawing::Size(50, 50);
			this->button14->TabIndex = 14;
			this->button14->Text = L"14";
			this->button14->UseVisualStyleBackColor = true;
			this->button14->Click += gcnew System::EventHandler(this, &Form1::button14_Click);
			// 
			// button15
			// 
			this->button15->Location = System::Drawing::Point(127, 184);
			this->button15->Name = L"button15";
			this->button15->Size = System::Drawing::Size(50, 50);
			this->button15->TabIndex = 15;
			this->button15->Text = L"15";
			this->button15->UseVisualStyleBackColor = true;
			this->button15->Click += gcnew System::EventHandler(this, &Form1::button15_Click);
			// 
			// button16
			// 
			this->button16->Location = System::Drawing::Point(184, 184);
			this->button16->Name = L"button16";
			this->button16->Size = System::Drawing::Size(50, 50);
			this->button16->TabIndex = 16;
			this->button16->UseVisualStyleBackColor = true;
			this->button16->Click += gcnew System::EventHandler(this, &Form1::button16_Click);
			// 
			// button17
			// 
			this->button17->Location = System::Drawing::Point(70, 254);
			this->button17->Name = L"button17";
			this->button17->Size = System::Drawing::Size(107, 50);
			this->button17->TabIndex = 0;
			this->button17->Text = L"—ледующий ход";
			this->button17->UseVisualStyleBackColor = true;
			this->button17->Click += gcnew System::EventHandler(this, &Form1::button17_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(249, 314);
			this->Controls->Add(this->button17);
			this->Controls->Add(this->button16);
			this->Controls->Add(this->button15);
			this->Controls->Add(this->button14);
			this->Controls->Add(this->button13);
			this->Controls->Add(this->button12);
			this->Controls->Add(this->button11);
			this->Controls->Add(this->button10);
			this->Controls->Add(this->button9);
			this->Controls->Add(this->button8);
			this->Controls->Add(this->button7);
			this->Controls->Add(this->button6);
			this->Controls->Add(this->button5);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Name = L"Form1";
			this->Text = L"15";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
			 cell_clik(0,0);
		 }
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
			 cell_clik(0,1);			 
		 }
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
			 cell_clik(0,2);
		 }
private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {
			 cell_clik(0,3);
		 }
private: System::Void button5_Click(System::Object^  sender, System::EventArgs^  e) {
			 cell_clik(1,0);
		 }
private: System::Void button6_Click(System::Object^  sender, System::EventArgs^  e) {
			 cell_clik(1,1);
		 }
private: System::Void button7_Click(System::Object^  sender, System::EventArgs^  e) {
			 cell_clik(1,2);
		 }
private: System::Void button8_Click(System::Object^  sender, System::EventArgs^  e) {
			 cell_clik(1,3);
		 }
private: System::Void button9_Click(System::Object^  sender, System::EventArgs^  e) {
			 cell_clik(2,0);
		 }
private: System::Void button10_Click(System::Object^  sender, System::EventArgs^  e) {
			 cell_clik(2,1);			
		 }
private: System::Void button11_Click(System::Object^  sender, System::EventArgs^  e) {
			 cell_clik(2,2);
		 }
private: System::Void button12_Click(System::Object^  sender, System::EventArgs^  e) {
			 cell_clik(2,3);
		 }
private: System::Void button13_Click(System::Object^  sender, System::EventArgs^  e) {
			 cell_clik(3,0);
		 }
private: System::Void button14_Click(System::Object^  sender, System::EventArgs^  e) {
			 cell_clik(3,1);
		 }
private: System::Void button15_Click(System::Object^  sender, System::EventArgs^  e) {
			 cell_clik(3,2);
		 }
private: System::Void button16_Click(System::Object^  sender, System::EventArgs^  e) {
			 cell_clik(3,3);
		 }
private: System::Void button17_Click(System::Object^  sender, System::EventArgs^  e) {
			//жесткий алгоритм сборки
			 while(find_num(1)!=1){//1 to 1
				set_target(find_num(1),1);
				lock[(find_num(1)-1)/4+1][(find_num(1)-1)%4+1]=1;
				move_zero();				
				lock[(find_num(1)-1)/4+1][(find_num(1)-1)%4+1]=0;
				cell_clik((find_num(1)-1)/4,(find_num(1)-1)%4);
			}
			lock[(find_num(1)-1)/4+1][(find_num(1)-1)%4+1]=1;
			while(find_num(2)!=2){//2 to 2
				set_target(find_num(2), 2);
				lock[(find_num(2)-1)/4+1][(find_num(2)-1)%4+1]=1;
				move_zero();				
				lock[(find_num(2)-1)/4+1][(find_num(2)-1)%4+1]=0;
				cell_clik((find_num(2)-1)/4,(find_num(2)-1)%4);
			}
			lock[(find_num(2)-1)/4+1][(find_num(2)-1)%4+1]=1;
			while(find_num(4)!=13){//4 to 13 чтобы не мешалась
				set_target(find_num(4), 13);
				lock[(find_num(4)-1)/4+1][(find_num(4)-1)%4+1]=1;
				move_zero();				
				lock[(find_num(4)-1)/4+1][(find_num(4)-1)%4+1]=0;
				cell_clik((find_num(4)-1)/4,(find_num(4)-1)%4);
			}
			while(find_num(3)!=4){//3 to 4
				set_target(find_num(3), 4);
				lock[(find_num(3)-1)/4+1][(find_num(3)-1)%4+1]=1;
				move_zero();				
				lock[(find_num(3)-1)/4+1][(find_num(3)-1)%4+1]=0;
				cell_clik((find_num(3)-1)/4,(find_num(3)-1)%4);
			}
			lock[(find_num(3)-1)/4+1][(find_num(3)-1)%4+1]=1;
			while(find_num(4)!=8){//4 to 8
				set_target(find_num(4), 8);
				lock[(find_num(4)-1)/4+1][(find_num(4)-1)%4+1]=1;
				move_zero();				
				lock[(find_num(4)-1)/4+1][(find_num(4)-1)%4+1]=0;
				cell_clik((find_num(4)-1)/4,(find_num(4)-1)%4);
			}
			lock[(find_num(4)-1)/4+1][(find_num(4)-1)%4+1]=1;
			set_target(find_num(3), 3);//0 to 3
			move_zero();
			cell_clik(0,3);
			cell_clik(1,3);
			lock[2][3]=1;
			lock[2][4]=0;			
			while(find_num(5)!=5){//5 to 5
				set_target(find_num(5), 5);
				lock[(find_num(5)-1)/4+1][(find_num(5)-1)%4+1]=1;
				move_zero();				
				lock[(find_num(5)-1)/4+1][(find_num(5)-1)%4+1]=0;
				cell_clik((find_num(5)-1)/4,(find_num(5)-1)%4);
			}
			lock[(find_num(5)-1)/4+1][(find_num(5)-1)%4+1]=1;						
			while(find_num(6)!=6){//6 to 6
				set_target(find_num(6), 6);
				lock[(find_num(6)-1)/4+1][(find_num(6)-1)%4+1]=1;
				move_zero();				
				lock[(find_num(6)-1)/4+1][(find_num(6)-1)%4+1]=0;
				cell_clik((find_num(6)-1)/4,(find_num(6)-1)%4);
			}
			lock[(find_num(6)-1)/4+1][(find_num(6)-1)%4+1]=1;
			while(find_num(8)!=13){//8 to 13
				set_target(find_num(8), 13);
				lock[(find_num(8)-1)/4+1][(find_num(8)-1)%4+1]=1;
				move_zero();				
				lock[(find_num(8)-1)/4+1][(find_num(8)-1)%4+1]=0;
				cell_clik((find_num(8)-1)/4,(find_num(8)-1)%4);
			}
			while(find_num(7)!=8){//7 to 8
				set_target(find_num(7), 8);
				lock[(find_num(7)-1)/4+1][(find_num(7)-1)%4+1]=1;
				move_zero();				
				lock[(find_num(7)-1)/4+1][(find_num(7)-1)%4+1]=0;
				cell_clik((find_num(7)-1)/4,(find_num(7)-1)%4);
			}
			lock[(find_num(7)-1)/4+1][(find_num(7)-1)%4+1]=1;
			while(find_num(8)!=12){//8 to 12
				set_target(find_num(8), 12);
				lock[(find_num(8)-1)/4+1][(find_num(8)-1)%4+1]=1;
				move_zero();				
				lock[(find_num(8)-1)/4+1][(find_num(8)-1)%4+1]=0;
				cell_clik((find_num(8)-1)/4,(find_num(8)-1)%4);
			}
			lock[(find_num(8)-1)/4+1][(find_num(8)-1)%4+1]=1;
			set_target(find_num(7), 7);//0 to 7
			move_zero();
			cell_clik(1,3);
			cell_clik(2,3);
			lock[1][2]=1;
			lock[2][3]=0;
			while(find_num(9)!=16){//9 to 16
				set_target(find_num(9), 16);
				lock[(find_num(9)-1)/4+1][(find_num(9)-1)%4+1]=1;
				move_zero();				
				lock[(find_num(9)-1)/4+1][(find_num(9)-1)%4+1]=0;
				cell_clik((find_num(9)-1)/4,(find_num(9)-1)%4);
			}
			while(find_num(13)!=9){//13 to 9
				set_target(find_num(13), 9);
				lock[(find_num(13)-1)/4+1][(find_num(13)-1)%4+1]=1;
				move_zero();				
				lock[(find_num(13)-1)/4+1][(find_num(13)-1)%4+1]=0;
				cell_clik((find_num(13)-1)/4,(find_num(13)-1)%4);
			}
			lock[(find_num(13)-1)/4+1][(find_num(13)-1)%4+1]=1;
			while(find_num(9)!=10){//9 to 10
				set_target(find_num(9), 10);
				lock[(find_num(9)-1)/4+1][(find_num(9)-1)%4+1]=1;
				move_zero();				
				lock[(find_num(9)-1)/4+1][(find_num(9)-1)%4+1]=0;
				cell_clik((find_num(9)-1)/4,(find_num(9)-1)%4);
			}
			lock[(find_num(9)-1)/4+1][(find_num(9)-1)%4+1]=1;
			set_target(find_num(13), 13);//0 to 13
			move_zero();
			cell_clik(2,0);
			cell_clik(2,1);
			lock[2][0]=1;
			lock[2][1]=0;			
		 }
};
}

