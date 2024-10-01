read -p "Enter the number: " n
if ! [[ "$n" =~ ^[0-9]+$ ]]; then
	echo "ERROR: Invalid Input: Enter a valid input: "
	exit 1
fi
sum=0
while [ -n "$n" ];
do
	#EXTRACT THE LAST DIGIT
	digit="${n:0:1}"
	sum=$((sum + digit))
	n="${n:1}"
done
echo "The sum of digits is $sum :"
