exe_dir=$1
exe_name="SPSPComparison.out"
case_dir=$2

for caseNum in $(seq 1 32)
do
    echo case $caseNum
    eval $exe_dir/$exe_name $case_dir/test_case$(printf %02d $caseNum).txt
    echo 
done
