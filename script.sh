#!bin/bash
curl -k -u "$USERNAME:$PASSWORD" $URL | awk '{print $9}' | sort > file_names.txt
if [[ -f "output.txt" ]]; then
    rm output.txt
fi
while IFS= read -r line; do
    ./main $line >> output.txt
done < file_names.txt


