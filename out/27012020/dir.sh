#!bin/zsh



for i in {0..9}
do
	cd $i
	for err in {5,10,20,50,100,200,300,400,500}
	do
		mkdir $err
	done
	cd ../
done
