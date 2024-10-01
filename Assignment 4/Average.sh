read -p "Enter the subject name" subname
if [[ $subname=="subject_1"||$subname=="subject_2"||$subname=="subject_3" ]]; then
	awk -v sm="$subname" -f 4b3.awk Marks.dat
else
	echo "invalid input. Enter suject_1 or subject_2 or subject_3"
	exit 1
fi
#PLZ CREATE THE MARKS.dat so that it can be passed to the Average.awk script.
#Plz create the Marks.dat file according to the file delimeter as per the question.
