# Psuedo for extra part 


## Approach one


```C 
    if(first run){
        for(int i = 0; i < blah; i++){
            assign(blah);
            delay(maxVal/((int)i/scaler)); // or delay(maxVal - ((int)i/scaler))
        }
    }
```


## Approach two 
```C 
    if(first run){
        for(int i = 0; i < blah; i++){
            for(int j = 0; j < blah; j++){
                assign(blah); 
                if(i == 0){
                    delay(blah); 
                }
                else if(i == 1){
                    delay(blah); 
                }
                //......
            }
        }

    }

```

