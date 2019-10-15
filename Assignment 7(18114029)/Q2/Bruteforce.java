import java.util.*;
import java.lang.*;
import java.io.*;

public class Bruteforce{
    
    int INFI = 10000000;
    int[] arr;

    public Bruteforce(int[] arr) {
        this.arr = arr;
    }
    public int getMax( int l, int r) {
        int max = -1;
        for(int i = l; i <= r; i++) {
            max = Math.max(max, arr[i]);
        }

        return max;
    }
    
    public int getMin( int l, int r) {
        int min = INFI;
        for(int i = l; i <= r; i++) {
            min = Math.min(min, arr[i]);
        }

        return min;
    }

    public int getSum( int l, int r) {
        int sum = 0;
        for(int i = l; i <= r; i++) {
            sum += arr[i];
        }

        return sum;
    }

    public void update(int l, int r, int val) {
        for(int i = l; i <= r; i++)
            arr[i] += val;
    }
}