#!/usr/bin/awk -f
BEGIN {FS="~"; highest_1=0; highest_2=0; highest_3=0}
NR>1 && NR<6 {
score_1=$3;
score_2=$4;
score_3=$5;
if(highest_1<score_1) {
highest_1=score_1;
rec1=$1};
if(highest_2<score_2) {
highest_2=score_2;
rec2=$1};
if(highest_3<score_3) {
highest_3=score_3;
rec3=$1
}
}
END {printf"Top Scorers:\n Subject_1->%s(%d) \n Subject_2->%s(%d) \n Subject_3->%s(%d)\n",rec1,highest_1,rec2,highest_2,rec3,highest_3}
