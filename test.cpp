#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair

int p;

vector<vector<int> >arena(12,vector<int>(12));

int pos[2][4][2];  // pos[player][amazon][iorjcoordinate]
                   // 0 for i coordinate 1 for j coordinate

struct move{

  int si;   // start position(i coordinate) of amazon
  int sj;   // start position (j) of amazon
  int di;   // destination position(i) of amazon
  int dj;   // destination position(j) of amazon

  int ari;   // Destination i of arrow
  int arj;   // Destination j of arrow

};
               // first i direction then j (i,j) pairs
int dir[8][2]={-1,-1,-1,0,-1,1,0,1,1,1,1,0,1,-1,0,-1};

int evaluateArena(vector<vector<int> >arena){




}

vector<move> generateMoves(vector<vector<int> >arena,int p){

    vector<move>possibleMoves;

    move moveTemp;

    // source,destination,destination of arrow
    int si,sj,di,dj,ari,arj;

    for(int s=0;s<=3;++s){

        int si=pos[p][s][0]; // i coordinate
        int sj=pos[p][s][1];  // j coordinate

        for(int j=0;j<8;++j){  // an amazon can move in any of th
                               // 8 directions.
            for(int x=1; ;x++){

                di=si+x*dir[j][0],dj=sj+x*dir[j][1];

                if(di<0 || di>11 || dj<0 || dj>11 || arena[di][dj]!=0) break;

                for(int k=0;k<8;++k){   // an arrow can be thrown in any of the 8 directions

                    for(int y=1; ;y++){  // distance to which arrow will be thrown

                        ari=di+y*dir[k][0],arj=dj+y*dir[k][1];

                        if((ari<0 || ari>11 || arj<0 || arj>11 || (arena[ari][arj]!=0 && arena[ari][arj]!=5)) && !(ari==si && arj==sj))
                            break;

                        moveTemp.si=si;
                        moveTemp.sj=sj;
                        moveTemp.di=di;
                        moveTemp.dj=dj;
                        moveTemp.ari=ari;
                        moveTemp.arj=arj;

                        possibleMoves.pb(moveTemp);

                    }
                }

            }
        }


    }

    return possibleMoves;

}

vector<vector<int> > makeMove(vector<vector<int> >arena,move newMove,int p){

    vector<vector<int> >newArena(12,vector<int>(12));

    //  Initialize newArena with Original Arena

    for(int i=0;i<12;++i){
        for(int j=0;j<12;++j){
            newArena[i][j]=arena[i][j];
        }
    }

    int si=newMove.si;
    int sj=newMove.sj;
    int di=newMove.di;
    int dj=newMove.dj;
    int ari=newMove.ari;
    int arj=newMove.arj;

    // Lets check which amazon is being moved actually

    for(int s=0;s<=3;++s){



    }

}


int main(){

    cin>>p;  // p take as 1 or 2
    p=p-1;  // reduce p so that we can easily move between 0 and 1
    //  0  --- blue player's turn
    //  1  --- red player's turn
    /*  But in board state
        1  --  blue amazon
        2  --  red amazon
        -1 -- blocked square
        5  -- square contains a bomb
        0  -- empty square
    */

    int cnt1=0,cnt2=0;  // cnt1 for blue amazon cnt2 for red amazon

    for(int i=0;i<12;++i){
      for(int j=0;j<12;++j){
          cin>>arena[i][j];
          if(arena[i][j]==1){  // blue amazon
              pos[0][cnt1][0]=i;
              pos[0][cnt1][1]=j;
              cnt1+=1;
          }
          if(arena[i][j]==2){   // red amazon
              pos[1][cnt2][0]=i;
              pos[1][cnt2][1]=j;
              cnt2+=1;
          }
      }
    }

    // arena gives board state and p gives turn(which player)

    vector<move> possibleMoves=generateMoves(arena,p);

    move bestMove=NULL;
    int bestValue=-10000;

    //  Player p will act as maximising player and opposite player will be minimising player

    // Now I will try out all posssible moves

    // Since returning a 2 D array is messy , I will return a 2D vector

    vector<vector<int> >newArena(12,vector<int>(12));

    for(int i=0;i<possibleMoves.size();++i){

        move newMove=possibleMoves[i];
        int temp[2][4][2];  // An array will store a 2D
        memcpy(temp,pos,sizeof pos);
        newArena=makeMove(arena,newMove,p); // I am sending a copy of arena and returning a new 2 D vector


    }








    return 0;
}
