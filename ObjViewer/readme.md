# ObjViewer

- **.obj**, **.mtl** 파일을 load 하여 mesh 를 보여주는 renderer 제작
- **OpenGL** 의 기초적인 사용법
- **Rendering Pipeline** 에 대한 이해
- **obj, mtl** 파일 parsing
- 3D 그래픽에서 **MVP** 모델에 대한 이해

## Build
```
mkdir build
cd build
cmake ..
cmake --build . -j 16
cd ..
```

## run
```
./build/objviewer obj_file_path
```

## Key
front - ```W```

back - ```S```

left - ```A```

right - ```D```

up - ```SPACE```

down - ```LEFT SHIFT```

view - ```mouse move```

zoom in/out - ```mouse wheel```

zoom reset - ```mouse wheel click```

color <-> texture - ```M```

change texture - ```.```

draw face <-> draw line - ```,```

rotate clockwise by X axis - ```U```

rotate counterclockwise by X axis - ```J```

rotate clockwise by Y axis - ```I```

rotate counterclockwise by Y axis - ```K```

rotate clockwise by Z axis - ```O```

rotate counterclockwise by Z axis - ```L```