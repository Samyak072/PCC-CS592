#INSERTION SORTING ALGORITHM
arr=(5 2 9 1 5 6 -5 74 61 -3)
echo "The given array is ${arr[@]}"
n=${#arr[@]}
for ((i=1;i<n;i++)); do
	key=${arr[i]}
	j=$((i-1))
	while ((j>=0 && arr[j]>key)); do
		arr[j+1]=${arr[j]}
		j=$((j-1))
	done
	arr[j+1]=$key
done
echo "Sorted Array is: ${arr[@]} "


