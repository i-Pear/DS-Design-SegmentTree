#include <bits/stdc++.h>

using namespace std;


class Segment3D{
public:
    int xL,xR,yL,yR,zL,zR;

    Segment3D(int xL,int xR,int yL,int yR,int zL,int zR) :
            xL(xL),xR(xR),yL(yL),yR(yR),zL(zL),zR(zR){}

    Segment3D intersect(const Segment3D &b){
        return {max(xL,b.xL),min(xR,b.xR),
                max(yL,b.yL),min(yR,b.yR),
                max(zL,b.zL),min(xR,b.zR)};
    }

    int getArea() const{
        return (xR-xL)*(yR-yL)*(xR-xL);
    }

    bool contains(const Segment3D& b){
        return xL<=b.xL&&xR>=b.xR&&yL<=b.yL&&yR>=b.yR&&zL<=b.zL&&zR>=b.zR;
    }

};

template<typename T>
class Segment3DTreeNode{
public:
    Segment3D mySegment;
    int lazy;
    int xMid,yMid,zMid; // Midµã´¦Ëã×÷L·¶Î§
    Segment3DTreeNode*son[8];
    int sum;
    int cachedDiff;


    Segment3DTreeNode(int xL,int xR,int yL,int yR,int zL,int zR) :
            mySegment(xL,xR,yL,yR,zL,zR){
        xMid(xL+xR/2);
        yMid(yL+yR/2);
        zMid(zL+zR/2);
        son[0]=new Segment3DTreeNode(xL,xMid,yL,yMid,zL,zMid);
        //...
    }

    void modifySegment(Segment3D segment,int diff){
        if(segment==mySegment){
            lazy+=diff;
            return;
        }else{
            for(auto &i : son){
                i->modifySegment(segment.intersect(i->mySegment),diff);
            }
        }
    }

    void modifyPoint(int x,int y,int z,int diff){
        modifySegment(Segment3D(x,x,y,y,z,z),diff);
    }

    int querySegmentSum(Segment3D segment){
        if(segment==mySegment){
            return sum;
        }
        int sum=0;
        for(auto &i:son){
            sum+=i->querySegmentSum(segment.intersect(i->mySegment));
        }
        return sum;
    }

    int queryPoint(int x,int y,int z){
        return querySegmentSum(Segment3D(x,x,y,y,z,z));
    }

};

template<typename T>
class Segment3DTree{
public:
    int xLength;
    int yLength;

    Segment3DTree(int xLength,int yLength,T**source){

    }
};


int main(){
    cout<<"Hello, World!"<<endl;
    return 0;
}
