# skeleton hierarchy

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