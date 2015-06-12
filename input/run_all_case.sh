exe_dir=$1
exe_name="SPSPComparison.out"
case_dir=$2
output_path="output/result.csv"

for caseNum in $(seq 1 32)
do
    echo case $caseNum
    mkdir -p output/
    echo case $caseNum >> $output_path
    eval $exe_dir/$exe_name $case_dir/test_case$(printf %02d $caseNum).txt $output_path
    echo "" >> $output_path
    echo 
done
