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

    bool empty()const{
        return xL==xR||yL==yR||zL==zR;
    }

    bool operator == (const Segment3D b)const{
        return xL==b.xL&&xR==b.xR&&yL==b.yL&&yR==b.yR&&zL==b.zL&&zR==b.zR;
    }

};

class ExtremeType{
public:
    bool valid;
    int min;
    int max;

    ExtremeType(int min,int max): min(min),max(max),valid(true){}
    ExtremeType(): min(0),max(0),valid(false){}
    void update(const ExtremeType& b){
        if(!b.valid)return;
        min=std::min(min,b.min);
        max=std::max(max,b.max);
    }
};

template<typename T>
class Segment3DTreeNode{
public:
    Segment3D mySegment;
    int xMid,yMid,zMid; // Mid�㴦����L��Χ
    Segment3DTreeNode*son[8];
    int sum;
    ExtremeType extreme;
    int cachedDiff;
    bool ifSet;
    int cachedSet;
    // ����������ȼ���set>modify
    // ���ڵ����cachedDiff����cachedSetʱ����ִ��set
    // ��setʱ�ɸ���diff������diffʱ����set�����´�

    Segment3DTreeNode(int xL,int xR,int yL,int yR,int zL,int zR) :mySegment(xL,xR,yL,yR,zL,zR){
        assert(!mySegment.empty());
        if(mySegment.getArea()==1) return;

        sum=0;
        max=INT_MAX;
        min=INT_MIN;
        cachedDiff=0;
        ifSet=false;
        cachedSet=0;
        xMid=(xL+xR/2);
        yMid=(yL+yR/2);
        zMid=(zL+zR/2);

        memset(son,0,sizeof(son));
        // ���ĳά�������Сֻ��1����ϸ�ָ�ά��L~Mid���������
        if(xR-xL>1)
            son[0]=new Segment3DTreeNode(xL,xMid,yMid,yR,zMid,zR);
        son[1]=new Segment3DTreeNode(xMid,xR,yMid,yR,zMid,zR);
        if(yR-yL>1)
            son[2]=new Segment3DTreeNode(xMid,xR,yL,yMid,zMid,zR);
        if(xR-xL>1&&yR-yL>1)
            son[3]=new Segment3DTreeNode(xL,xMid,yL,yMid,zMid,zR);
        if(xR-xL>1&&zR-zL>1)
            son[4]=new Segment3DTreeNode(xL,xMid,yMid,yR,zL,zMid);
        if(zR-zL>1)
            son[5]=new Segment3DTreeNode(xMid,xR,yMid,yR,zL,zMid);
        if(yR-yL>1&&zR-zL>1)
            son[6]=new Segment3DTreeNode(xMid,xR,yL,yMid,zL,zMid);
        if(xR-xL>1&&yR-yL>1&&zR-zL>1)
            son[7]=new Segment3DTreeNode(xL,xMid,yL,yMid,zL,zMid);
    }

    explicit Segment3DTreeNode(Segment3D segment){
        Segment3DTreeNode(segment.xL,segment.xR,segment.yL,segment.yR,segment.zL,segment.zR);
    }

    ExtremeType modifySegment(Segment3D segment,int diff){
        if(segment.empty())return {};
        sum+=segment.getArea()*diff;
        if(segment==mySegment){
            cachedDiff+=diff;
            return {};
        }else{
            for(auto &i : son){
                if(i){
                    auto re=i->modifySegment(segment.intersect(i->mySegment),diff);
                    extreme.update(re);
                }
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

}
