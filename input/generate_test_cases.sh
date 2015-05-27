sh_name="generate_test_cases.sh"
exe_name="spflower.out"

len=$(( ${#0} - ${#sh_name} ))
dir=`echo $0 | cut -c 1-$len`

file_dir=$1
mkdir -p $file_dir

min[0]=1
min[1]=1000
max[0]=1000
max[1]=10000

d2=5

counter=1
for n1 in 50 100
do
    for n2 in 50 100
    do
        for bound in 0 1
        do
            for is_sym in 0 1
            do
                for seed in 1 10
                do
                    file_name="test_case$(printf %02d $counter).txt"
                    eval ${dir}${exe_name} \
                            ${file_dir}/${file_name} $n1 $n2 $d2 \
                            ${min[$bound]} ${max[$bound]} ${min[$bound]} ${max[$bound]} \
                            $is_sym $seed
                    counter=$(( $counter + 1 ))
                done
            done
        done
    done
done
