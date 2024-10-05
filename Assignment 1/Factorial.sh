read -p "Enter the numberto compute the factorial: " n
factorial=1
for ((i=1;i<=$n;i++))
do
	factorial=$((factorial*i))
done
echo "Factorial of $n is $factorial "
