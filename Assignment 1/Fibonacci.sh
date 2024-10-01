read -p "Enter the number: " n
a=0
b=1
echo "Fibonacci Series up to $n terms: "
if [ $n -ge 1 ]; then
	echo -n "$a"
	echo
fi
if [ $n -ge 2 ]; then
	echo -n "$b"
	echo
fi

for (( i=3;i<=n;i++ )); 
do
	next=$((a + b))
	echo -n "$next"
	echo
	a=$b
	b=$next
done
echo
