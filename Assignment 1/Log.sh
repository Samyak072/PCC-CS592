if [ "$#" -ne 1 ]; then
	echo "$0 has more than 1 arguments: Please enter a number: "
	exit 1
fi
n=$1
ans=$(echo "scale=2; l($n)/l(10)" | bc -l ) 
echo "$ans"
