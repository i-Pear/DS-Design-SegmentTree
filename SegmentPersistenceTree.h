#pragma once

#include "SegmentTree.h"


class Segment3DPersistenceTreeNode : public Segment3DTreeNode{

private:

public:

    Segment3DPersistenceTreeNode(Segment3D segment) : Segment3DTreeNode(segment){}

    Segment3DPersistenceTreeNode(Segment3DPersistenceTreeNode &b) : Segment3DTreeNode(b){

    }

    Segment3DPersistenceTreeNode(Segment3DTreeNode &b) : Segment3DTreeNode(b){

    }


    /* 区间修改 */

    StaticsType &__modifySegment(Segment3D segment,int diff,Segment3DPersistenceTreeNode**link){

        segment=segment.intersect(mySegment);

        if(segment.empty())return statics;

        // If passes here, it shows that modification must go through this node

        if(link){
            // shows that here's UDD node
            (*link)=new Segment3DPersistenceTreeNode(*this);
            (*link)->__modifySegment(segment,diff,nullptr);
            return statics;
        }else{
            // shows that here is new node
            // so continue
        }

        if(segment==mySegment){
            cachedDiff+=diff;
            statics.sum+=diff;
            statics.min+=diff;
            statics.max+=diff;
            return statics;
        }else{
            statics.clear();
            for(auto &i : son){
                if(i){
                    auto re=((Segment3DPersistenceTreeNode*)i)->__modifySegment(segment,diff,((Segment3DPersistenceTreeNode**)(&i)));
                    statics.update(re);
                }
            }
            return statics;
        }

    }

    /* 区间赋值 */

    StaticsType &__setSegment(Segment3D segment,int val,Segment3DPersistenceTreeNode**link){

        segment=segment.intersect(mySegment);

        if(segment.empty())return statics;

        // If passes here, it shows that modification must go through this node

        if(link){
            // shows that here's UDD node
            (*link)=new Segment3DPersistenceTreeNode(*this);
            (*link)->__setSegment(segment,val,nullptr);
            return statics;
        }else{
            // shows that here is new node
            // so continue
        }

        if(segment==mySegment){
            cachedDiff=0;
            ifSet=true;
            cachedSet=val;
            statics.max=statics.min=val;
            statics.sum=val*mySegment.getVolume();
        }else{
            if(cachedDiff){
                pushDownDiff();
            }
            statics.clear();
            for(auto &i:son){
                if(i){
                    auto re=((Segment3DPersistenceTreeNode*)i)->__setSegment(segment,val,((Segment3DPersistenceTreeNode**)(&i)));
                    statics.update(re);
                }
            }
            return statics;
        }
    }


    void modifySegment(Segment3D segment,int diff){
        __modifySegment(segment,diff,nullptr);
    } // Wrapper

    void setSegment(Segment3D segment,int val){
        __setSegment(segment,val,nullptr);
    } // Wrapper

};


class Segment3DPersistenceTree{

protected:

    list<Segment3DPersistenceTreeNode> heads;
    int count;

    void createDuplicate(){
        heads.emplace_back(heads.back());
        count++;
    }

    int xLength;
    int yLength;
    int zLength;

public:

    Segment3DPersistenceTree(int xLength,int yLength,int zLength) : xLength(xLength),yLength(yLength),zLength(zLength){
        count=0;
        heads.emplace_back(Segment3D(0,xLength,0,yLength,0,zLength));
    }

    void modifySegment(Segment3D segment,int diff){
        createDuplicate();
        heads.back().modifySegment(segment,diff);
    }

    void modifyPoint(int x,int y,int z,int diff){
        modifySegment(Segment3D(x,y,z),diff);
    } //Wrapper

    int querySegmentSum(Segment3D segment,int time){
        auto iter=heads.begin();
        while(time--){
            iter++;
        }
        return iter->querySegmentSum(segment);
    }

    int queryPoint(int x,int y,int z,int time){
        return querySegmentSum(Segment3D(x,y,z),time);
    } //Wrapper

    ExtremeType querySegmentMin(Segment3D segment,int time){
        cout<<"DEBUG::size="<<heads.size()<<endl;
        auto iter=heads.begin();
        while(time--){
            iter++;
        }
        return iter->querySegmentMin(segment);
    }

    ExtremeType querySegmentMax(Segment3D segment,int time){
        auto iter=heads.begin();
        while(time--){
            iter++;
        }
        return iter->querySegmentMax(segment);
    }

    void setSegment(Segment3D segment,int val){
        createDuplicate();
        heads.back().setSegment(segment,val);
    }

    void setPoint(int x,int y,int z,int val){
        setSegment(Segment3D(x,y,z),val);
    } //Wrapper

    void DEBUG_Output_Sum_Process(Segment3D segment){
        for(int i=0;i<=count;i++){
            cout<<"Step "<<i<<" : "<<querySegmentSum(segment,i)<<endl;
        }
        cout<<endl;
    }

};