#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair

int p;   // Denotes which player - blue or red

vector<vector<int> >arena(12,vector<int>(12));

//  pos stores the current positions of amazons to easily generate moves when needed
//  Otherwise while generating moves we have to traverse the matrix to find the amazons and then check moves.
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

    // Maximising player will have positive score attached
    // Minimising player will have negative score attached

    // I am using sum of degree of freedom of each amazon

    int sum1=0;  // sum of degree of freedom for amazons of maximising player
    int sum2=0;  // sum of degree of freedom for amazons of minimising player

    // degree of freedom here means number of squares available to an amazon to move
    for(int s=0;s<=3;++s){

        int si=pos[p][s][0]; // i coordinate
        int sj=pos[p][s][1];  // j coordinate

        int di,dj;

        for(int j=0;j<8;++j){  // an amazon can move in any of the 8 directions

            int x;
            for(x=1; ;x++){

                di=si+x*dir[j][0],dj=sj+x*dir[j][1];
                if(di<0 || di>11 || dj<0 || dj>11 || arena[di][dj]!=0) break;

            }

            sum1+=x-1;

        }

    }

    for(int s=0;s<=3;++s){

        int si=pos[!p][s][0]; // i coordinate
        int sj=pos[!p][s][1];  // j coordinate

        int di,dj;

        for(int j=0;j<8;++j){

            int x;
            for(x=1; ;x++){

                di=si+x*dir[j][0],dj=sj+x*dir[j][1];
                if(di<0 || di>11 || dj<0 || dj>11 || arena[di][dj]!=0) break;

            }

            sum2+=x-1;


        }

    }

    return sum1-sum2;
}


// Time Complexity O(3*8*12*8*12)=O(27648)

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

// Time Complexity :- O(144+3*8)=O(168)

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

        if(pos[p][s][0]==si && pos[p][s][1]==sj){  // we want to move amazon s

            pos[p][s][0]=di;   // current destination will become source for furthur opertations
            pos[p][s][1]=dj;

            newArena[si][sj]=0;
            newArena[di][dj]=p+1;  // blue or red by 1 or 2

            if(newArena[ari][arj]==5){  // If arrow lands on a bomb

                newArena[ari][arj]=0;  // Clear the square where bomb resides
                int bombi,bombj;

                // Clearing the nearby 8 squares

                for(int i=0;i<8;++i){

                    if(newArena[ari+1*dir[i][0]][arj+1*dir[i][1]]==-1)
                        newArena[ari+1*dir[i][0]][arj+1*dir[i][1]]=0;
                }

            }

            else{

                newArena[ari][arj]=-1;
            }

            break;

        }


    }

    return newArena;

}

int minimax(int depth,vector<vector<int> >arena,bool isMaximisingPlayer){
    vector<vector<int> >newArena;

    if(depth==0){

        cout<<"Leaf node of minimax tree\n";
        int val=evaluateArena(arena);

        return val;
    }


    if(isMaximisingPlayer){
        cout<<"depth: "<<depth<<"\n";
        vector<move> possibleMoves=generateMoves(arena,p);
        int bestValue=-1500;
        cout<<"No of possible moves: ";
        cout<<possibleMoves.size()<<"\n";

        for(int i=0;i<possibleMoves.size();++i){

            move newMove=possibleMoves[i];
            int temp[2][4][2];  // An array that keeps copy of pos
                                // Latter used to undo
            memcpy(temp,pos,sizeof pos);
            newArena=makeMove(arena,newMove,p);
            bestValue=max(bestValue,minimax(depth-1,newArena,!isMaximisingPlayer));
            memcpy(pos,temp,sizeof temp);   // Now I am undoing my deeds

        }

      
        return bestValue;

    }
    else{
        cout<<"depth: "<<depth<<"\n";
        cout<<"Minimising player\n";
        vector<move> possibleMoves=generateMoves(arena,!p);
        int bestValue=1500;
        cout<<"No of possible moves: ";
        cout<<possibleMoves.size()<<"\n";

        for(int i=0;i<possibleMoves.size();++i){

            move newMove=possibleMoves[i];
            int temp[2][4][2];
            memcpy(temp,pos,sizeof pos);
            newArena=makeMove(arena,newMove,!p);
            bestValue=min(bestValue,minimax(depth-1,newArena,!isMaximisingPlayer));

            memcpy(pos,temp,sizeof temp);  // undoing
        }

        return bestValue;

    }

}

int main(){

    memset(pos,0,sizeof(pos));

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

    cout<<"\n";

    for(int i=0;i<12;++i){

        for(int j=0;j<12;++j){

            cout<<arena[i][j]<<" ";

        }

        cout<<"\n";

    }


    // arena gives board state and p gives turn(which player)

    vector<move> possibleMoves=generateMoves(arena,p);

    move bestMove;
    int bestValue=-1500;

    //  Player p will act as maximising player and opposite player will be minimising player

    // Now I will try out all posssible moves

    // Since returning a 2 D array is messy , I will return a 2D vector

    vector<vector<int> >newArena(12,vector<int>(12));

    // Arena does not change while trying to make possible moves
    // We do changes on a copy of arena and return a new Arena

    for(int i=0;i<possibleMoves.size();++i){

        move newMove=possibleMoves[i];
        int temp[2][4][2];  // An array that keeps copy of pos
                            // Latter used to undo
        memcpy(temp,pos,sizeof pos);
        newArena=makeMove(arena,newMove,p); // I am sending a copy of arena and returning a new 2 D vector

        int arenaValue=minimax(2,newArena,false);

      //  cout<<"Ek minimax complete\n";

        memcpy(pos,temp,sizeof temp);   // Now I am undoing my deeds

        if(arenaValue>=bestValue){

            bestValue=arenaValue;
            bestMove=newMove;
        }


    }



    cout<<(char)('A'+bestMove.si);
    cout<<(char)('A'+bestMove.sj);
    cout<<(char)('A'+bestMove.di);
    cout<<(char)('A'+bestMove.dj);
    cout<<(char)('A'+bestMove.ari);
    cout<<(char)('A'+bestMove.arj);
    cout<<"\n";


    return 0;
}
