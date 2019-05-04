all:
	gcc src/main.c src/camera.c src/utils.c src/model.c src/draw.c -lSOIL -lglut32 -lopengl32 -lglu32 -lm -o grafika.exe