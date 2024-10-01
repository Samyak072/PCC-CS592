#!/usr/bin/awk -f
BEGIN {FS="~"; highest=0};
NR>1 && NR<6 {total=$3+$4+$5; if(highest<total) {highest=total; rec=$0}};
END {print rec"|"highest}
