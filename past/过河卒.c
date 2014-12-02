#include <stdio.h>  
  
long long arr[20][20];  
int cX, cY;  
  
int canGo(int x, int y) {  
    if ((x == cX && y == cY)  
        || (x == cX - 2 && y == cY - 1)  
        || (x == cX - 1 && y == cY - 2)  
        || (x == cX + 2 && y == cY + 1)  
        || (x == cX + 1 && y == cY + 2)  
        || (x == cX + 1 && y == cY - 2)  
        || (x == cX + 2 && y == cY - 1)  
        || (x == cX - 1 && y == cY + 2)  
        || (x == cX - 2 && y == cY + 1)  
        ) {  
        return 0;  
    } else {  
        return 1;  
    }  
}  
  
int main( void ) {  
    int bX, bY;  
    scanf("%d %d %d %d", &bX, &bY, &cX, &cY);  
    int i, j;  
    for (i = 0; i <= bX; i++) {  
       	if (canGo(i, 0) != 0) {
   	 		arr[i][0] = 1;   
   		} else {
			for (j = i; j <= bX; j++) {
   				arr[j][0] = 0;
   			}
   			break;
   		}
    }
    for (i = 0; i <= bY; i++) {  
       	if (canGo(0, i) != 0) {
   	 		arr[0][i] = 1;   
   		} else {
			for (j = i; j <= bY; j++) {
   				arr[0][j] = 0;
   			}
   			break;
   		}
    }
    
    for (i = 1; i <= bX; i++) {  
        for (j = 1; j <= bY; j++) {  
            if (canGo(i, j) != 0) {  
                arr[i][j] = arr[i][j - 1] + arr[i - 1][j];  
            } else {  
                arr[i][j] = 0;  
            }  
  
        }  
    }  
    printf("%I64d", arr[bX][bY]);  
  
    return 0;  
}  