#include "base.h"
#include "SegmentTree.h"
#include "SegmentPersistenceTree.h"


int main(){
    Segment3DPersistenceTree t(4,4,4);
    t.debug_output_sum_process(Segment3D(1,3,1,3,1,3));
    t.modifySegment(Segment3D(1,2,1,3,1,2),10);
    t.debug_output_sum_process(Segment3D(1,3,1,3,1,3));
    t.setSegment(Segment3D(1,3,1,3,1,3),50);
    t.debug_output_sum_process(Segment3D(1,3,1,3,1,3));
    t.modifySegment(Segment3D(1,2,1,3,1,2),10);
    t.debug_output_sum_process(Segment3D(1,3,1,3,1,3));
}
