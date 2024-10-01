while true; do
	echo "MENU:"
	echo "1. Show the permissions of a file or a directory:"
	echo "2.Show the number of files and directories under the current directory:"
	echo "3.Show the last modification time of the file in the current directory: "
	echo "4. Exit from Menu:"
	read -p "Enter your choice:" choice
	case $choice in
		1)
			read -p "Enter the name of the file:" file
			if [[ -e "$file" ]]; then
				p=$( ls -ld "$file" | cut -d ' ' -f1 | cut -c2-)
				if [ -f "$file" ]; then
					echo "IT IS AN FILE:"
					echo "$p"
				elif [ -d "$file" ]; then
					echo "It is an directory"
					echo "$p"
				fi
			else
				echo "$file does not exists:"
			fi
			;;
		2)
			files=$( ls -l | grep "^-" | wc -l )
			directories=$( ls -l | grep "^d" | wc -l )
			echo "number of files are: $files"
			echo "number of directories are: $directories"
			;;
		3)
			echo -n "Enter the filename:"
			read file
			if [ -e "$file" ]; then
				time=$(ls -ld "$file" | cut -d ' ' -f6-8)
				echo "$time: "
			else
				echo "$file does not exist: PLease run again $0 to proceed:"
			fi
			;;
		4)
			echo "EXITING...."
			break
			;;
		*)
			echo "INVALID CHOICE:"
			;;
	esac
done
