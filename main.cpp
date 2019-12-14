#include <bits/stdc++.h>
using namespace std;

class Segment3D{
public:
    int xL,xR,yL,yR,zL,zR;

    Segment3D(int xL,int xR,int yL,int yR,int zL,int zR):
    xL(xL),xR(xR),yL(yL),yR(yR),zL(zL),zR(zR){}
    int getXLeft(){ return xL;}
    int getXRight(){ return xR;}
    int getYLeft(){ return yL;}
    int getYRight(){ return yR;}
    int getZLeft(){ return zL;}
    int getZRight(){ return zR;}
};

template<typename T>
class SegmentTree3DNode{
public:
    int xLeft,xRight;
    int yLeft,yRight;
    int zLeft,zRight;
    int xMid,yMid,zMid;
    SegmentTree3DNode*son[8];

    SegmentTree3DNode(int xL,int xR,int yL,int yR,int zL,int zR) :
            xLeft(xL),xRight(xR),
            yLeft(yL),yRight(yR),
            zLeft(zL),zRight(zR),
            xMid(xL+xR/2),yMid(yL+yR/2),zMid(zL+zR/2){}

    update(int xL,int xR,int yL,int yR,int zL,int zR)
};

template<typename T>
class SegmentTree3D{
public:
    int xLength;
    int yLength;
    T**data;

    SegmentTree3D(int xLength,int yLength,T**source){

    }
};


int main(){
    cout<<"Hello, World!"<<std::endl;
    return 0;
}