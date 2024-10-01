if [ "$#" -lt 1 ]; then
	echo "Enter atleast 2 numbers: "
	exit 1
fi
sum=0
for i in "$@"; do
	sum=$((sum + i))
done
echo "The Sum is $sum : "
