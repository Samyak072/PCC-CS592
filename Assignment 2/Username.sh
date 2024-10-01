input="$1"
pattern="^[a-zA-Z0-9_]{3,16}$"
if [[ $input =~ $pattern ]]; then
	echo "USERNAME HAS BEEN ACCEPTED: "
else
	echo "INVALID USERNAME: "
fi
