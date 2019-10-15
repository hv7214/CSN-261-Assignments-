
import java.util.*;
import java.lang.*;
import java.io.*;

class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int[]arr;
        int n;

        System.out.println("Enter the value of n:");
        n = sc.nextInt();

        arr = new int[n];

        System.out.println("Input your array:");

        for(int i = 0; i < n; i++) {
            int x; 
            x = sc.nextInt();
            arr[i] = x;
        }

        SegmentTreeSum segtree_sum = new SegmentTreeSum(arr.length);
        // System.out.println(segtree_sum.getTreeBaseSize());
        System.out.println(segtree_sum.buildTree(arr, 0, segtree_sum.getTreeBaseSize()-1, 0));
        System.out.println(segtree_sum.update(0, 4, 4));

        
    }
}