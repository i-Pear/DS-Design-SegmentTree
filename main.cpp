#include "base.h"
#include "SegmentTree.h"
#include "SegmentPersistenceTree.h"


int main(){ // 左闭右开
    Segment3DTree t(10,1,1);
    t.modifySegment({0,5,0,1,0,1},2);
    t.modifySegment({1,6,0,1,0,1},-1);
    cout<<t.querySegmentSum({0,10,0,1,0,1});
}
