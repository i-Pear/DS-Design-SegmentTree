#include "SegmentPersistenceTree.h"


Segment3DPersistenceTreeNode::Segment3DPersistenceTreeNode(Segment3D segment) : Segment3DTreeNode(segment){}

Segment3DPersistenceTreeNode::Segment3DPersistenceTreeNode(Segment3DPersistenceTreeNode &b) : Segment3DTreeNode(b){}

Segment3DPersistenceTreeNode::Segment3DPersistenceTreeNode(Segment3DTreeNode &b) : Segment3DTreeNode(b){}


/* 区间修改 */

StaticsType &
Segment3DPersistenceTreeNode::__modifySegment(Segment3D segment,int diff,Segment3DPersistenceTreeNode**link){

    segment=segment.intersect(mySegment);

    if(segment.empty())return statics;

    // If passes here, it shows that modification must go through this node

    if(link){
        // shows that here's UDD node
        (*link)=new Segment3DPersistenceTreeNode(*this);
        return (*link)->__modifySegment(segment,diff,nullptr);
    }else{
        // shows that here is new node
        // so continue
    }

    if(segment==mySegment){
        cachedDiff+=diff;
        statics.sum+=diff*segment.getVolume();
        statics.min+=diff;
        statics.max+=diff;
        return statics;
    }else{
        if(ifSet){
            pushDownSet();
        }
        statics.clear();
        for(auto &i : son){
            if(i){
                auto re=((Segment3DPersistenceTreeNode*)i)->__modifySegment(segment,diff,
                                                                            ((Segment3DPersistenceTreeNode**)(&i)));
                statics.update(re);
            }
        }
        statics.add(cachedDiff,mySegment.getVolume());
        return statics;
    }

}

/* 区间赋值 */

StaticsType &Segment3DPersistenceTreeNode::__setSegment(Segment3D segment,int val,Segment3DPersistenceTreeNode**link){

    segment=segment.intersect(mySegment);

    if(segment.empty())return statics;

    // If passes here, it shows that modification must go through this node

    if(link){
        // shows that here's UDD node
        (*link)=new Segment3DPersistenceTreeNode(*this);
        return (*link)->__setSegment(segment,val,nullptr);
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
        return statics;
    }else{
        if(cachedDiff){
            pushDownDiff();
        }
        statics.clear();
        for(auto &i:son){
            if(i){
                auto re=((Segment3DPersistenceTreeNode*)i)->__setSegment(segment,val,
                                                                         ((Segment3DPersistenceTreeNode**)(&i)));
                statics.update(re);
            }
        }
        statics.add(cachedDiff,mySegment.getVolume());
        return statics;
    }
}


void Segment3DPersistenceTreeNode::modifySegment(Segment3D segment,int diff){
    __modifySegment(segment,diff,nullptr);
} // Wrapper

void Segment3DPersistenceTreeNode::setSegment(Segment3D segment,int val){
    __setSegment(segment,val,nullptr);
} // Wrapper




void Segment3DPersistenceTree::createDuplicate(){
    heads.emplace_back(heads.back());
    count++;
}


Segment3DPersistenceTree::Segment3DPersistenceTree(int xLength,int yLength,int zLength) : xLength(xLength),
                                                                                          yLength(yLength),
                                                                                          zLength(zLength){
    count=0;
    heads.emplace_back(Segment3D(0,xLength,0,yLength,0,zLength));
}

void Segment3DPersistenceTree::modifySegment(Segment3D segment,int diff){
    createDuplicate();
    heads.back().modifySegment(segment,diff);
}

void Segment3DPersistenceTree::modifyPoint(int x,int y,int z,int diff){
    modifySegment(Segment3D(x,y,z),diff);
} //Wrapper

int Segment3DPersistenceTree::querySegmentSum(Segment3D segment,int time){
    auto iter=heads.begin();
    while(time--){
        iter++;
    }
    return iter->querySegmentSum(segment);
}

int Segment3DPersistenceTree::queryPoint(int x,int y,int z,int time){
    return querySegmentSum(Segment3D(x,y,z),time);
} //Wrapper

ExtremeType Segment3DPersistenceTree::querySegmentMin(Segment3D segment,int time){
    //cout<<"DEBUG::size="<<heads.size()<<endl;
    auto iter=heads.begin();
    while(time--){
        iter++;
    }
    return iter->querySegmentMin(segment);
}

ExtremeType Segment3DPersistenceTree::querySegmentMax(Segment3D segment,int time){
    auto iter=heads.begin();
    while(time--){
        iter++;
    }
    return iter->querySegmentMax(segment);
}

void Segment3DPersistenceTree::setSegment(Segment3D segment,int val){
    createDuplicate();
    heads.back().setSegment(segment,val);
}

void Segment3DPersistenceTree::setPoint(int x,int y,int z,int val){
    setSegment(Segment3D(x,y,z),val);
} //Wrapper

void Segment3DPersistenceTree::debug_output_sum_process(Segment3D segment){
    for(int i=0;i<=count;i++){
        cout<<"Step "<<i<<" : "<<querySegmentSum(segment,i)<<endl;
    }
    cout<<endl;
}

