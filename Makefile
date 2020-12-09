all:
	g++ -v -pthread -O3  *.cpp -o raytracer -std=c++11 
run:
	./raytracer "Sample Scenes/Input Files/simple.xml"
testfile:
	cd Tests && make && ./test && cd ..
sshading:
	./raytracer "Sample Scenes/Input Files/simple_shading.xml"
bunny:
	./raytracer "Sample Scenes/Input Files/bunny.xml"
cornellbox:
	./raytracer "Sample Scenes/Input Files/cornellbox.xml"
horseandmug:
	./raytracer "Sample Scenes/Input Files/horse_and_mug.xml"
killeroo:
	./raytracer "Sample Scenes/Input Files/killeroo.xml"
mirror_spheres:
	./raytracer "Sample Scenes/Input Files/mirror_spheres.xml"
sreflectance:
	./raytracer "Sample Scenes/Input Files/simple_reflectance.xml"
onebyone:
	make all && make run && make sshading && make sreflectance && make bunny && make cornellbox && make mirror_spheres  && make killeroo && make horseandmug 