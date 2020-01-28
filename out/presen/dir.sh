#!bin/zsh

for i in {100,200}
do
	cd $i
	for j in {1..40}
	do
		rm -rf $j
	done
	cd ..
done
