#!bin/zsh

for i in {0..99}
do
	#mkdir $i
	cd $i
	mkdir 5
	mkdir 10
	mkdir 20
	mkdir 50
	mkdir 100
	mkdir 200
	mkdir 500
	cd ../
done
