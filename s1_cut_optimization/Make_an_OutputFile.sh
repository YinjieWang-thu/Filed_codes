cat VarList.out | while read rows
do
	if [[ $rows =~ ---.*--- ]]
	then
		sleep 0.001
	else
		varName=$(echo $rows | awk 'BEGIN{FS="/"} {print $1}')
       	varMin=$(echo $rows | awk 'BEGIN{FS="/"} {print $2}')
    	varMax=$(echo $rows | awk 'BEGIN{FS="/"} {print $3}')
        sed -i -e '$a\'"\t\t float ${varName}; " result.txt
		
	fi
done

cat VarList.out | while read rows
do
	if [[ $rows =~ ---.*--- ]]
	then
		sleep 0.001
	else
		varName=$(echo $rows | awk 'BEGIN{FS="/"} {print $1}')
       	varMin=$(echo $rows | awk 'BEGIN{FS="/"} {print $2}')
    	varMax=$(echo $rows | awk 'BEGIN{FS="/"} {print $3}')
        sed -i -e '$a\'"\t\t &${varName}, " result.txt
		
	fi
done

cat VarList.out | while read rows
do
	if [[ $rows =~ ---.*--- ]]
	then
		sleep 0.001
	else
		varName=$(echo $rows | awk 'BEGIN{FS="/"} {print $1}')
       	varMin=$(echo $rows | awk 'BEGIN{FS="/"} {print $2}')
    	varMax=$(echo $rows | awk 'BEGIN{FS="/"} {print $3}')
        sed -i -e '$a\'"\t\t ${varName} > ${varMin} && ${varName} < ${varMax} &&" result.txt
		
	fi
done