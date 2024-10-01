FILE="personal_details"
function accept_details()
{
	echo "Enter your name"
	read name
	echo "Enter your email"
	read email
	echo "Enter your age"
	read age
	echo "ENter your password"
	read -s  passwd
	echo
	echo "$name:$email:$age:$passwd" >> "$FILE"
	echo "Details saved successfully"
	echo
}
function display_details()
{
	if [[ ! -f "$FILE" ]]; then
		echo "File does not exist"
		return
	fi
	echo "Enter your password to get your details"
	read -s password
	echo
	password=$(echo "$password" | tr -d '\n')

	while IFS=: read -r name email age stored_password
	do
	stored_password=$(echo "$stored_password" | tr -d '\n')
	if [[ "$stored_password" == "$password" ]]; then
                echo "Name: $name"
                echo "Email: $email"
                echo "Age: $age"
                echo
		return
	fi
	done < "$FILE"
        echo "Password Mismatched. Access Denied."
}
while true; do
        echo "Menu: "
        echo "1. Enter personal details: "
        echo "2. Display personal details: "
        echo "3. Exit"
        echo
        read -p "Choose an option: " choice
        echo
        case $choice in
                1)
                        accept_details
                        ;;
                2)
                        display_details
                        ;;
                3)
                        echo "Exiting..."
                        break
                        ;;
                *)
                        echo "invalid option. Please try again."
                        ;;
        esac
done


