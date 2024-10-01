#!/usr/bin/awk -f
BEGIN{FS="~"; total=0;count=0}
NR>1 && NR<7{
if(sm=="subject_1"){
total=total+$3;
}
else if(sm=="subject_2"){
total=total+$4;
}
else if(sm=="subject_3"){
total=total+$5;
}
count++;
}
END{
if(count>0)
print "the avrage marks for the entered subject is :"total/count;
else
{
print "you have done some mistake"
}
}
