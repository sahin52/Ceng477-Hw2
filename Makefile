all:
	g++ -v -pthread -O3  *.cpp -o raytracer -std=c++11 -ljpeg
run:
	./raytracer "Sample Scenes/Input Files/simple.xml"
testfile:
	cd Tests && make && ./test "../MoreScenes/scenes/earth_and_moon.xml" && cd ..
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
horse:
	./raytracer "hw2_sample_scenes/horse.xml"
simple_transform:
	make && ./raytracer "hw2_sample_scenes/simple_transform.xml"
skybox:
	make && ./raytracer "hw2_sample_scenes/skybox.xml"
earth_and_moon:
	make && ./raytracer "hw2_sample_scenes/earth_and_moon.xml"
bilinear:
	make && ./raytracer "MoreScenes/scenes/spheres_texture_bilinear.xml"
nearest:
	make && ./raytracer "MoreScenes/scenes/spheres_texture_nearest.xml"