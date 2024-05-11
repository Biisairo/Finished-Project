# Skeleton Hierarchy 

**.asf**, **.amc** 파일을 load 하여 motion capture 데이터를 시각화 해주는 renderer 제작 \
**asf, amc** 파일 parsing \
3D 공간에서 물체들의 위치를 계산하는 **Transform Matrix** 의 이해 \
**Instancing** 을 이용한 rendering 과정 최적화

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
./build/skeleton_hierarchy
```

## Key
front - ```arrow front```

back - ```arrow back```

left - ```arrow left```

right - ```arrow right```

up - ```mouse left click```

down - ```mouse right click```

view - ```mouse move```

zoom in/out - ```mouse wheel```

zoom reset - ```mouse wheel click```

## select file

change the define in ```./includ/pch```
```
#define ASF <file in resource/skeleton>
#define amc <file in resource/motion>
``` 