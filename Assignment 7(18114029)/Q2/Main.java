
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
        SegmentTreeMax segtree_max = new SegmentTreeMax(arr.length);
        SegmentTreeMin segtree_min = new SegmentTreeMin(arr.length);
        Bruteforce bf = new Bruteforce(arr);

        System.out.println(segtree_sum.buildTree(arr, 0, segtree_sum.getTreeBaseSize()-1, 0));
        System.out.println(segtree_max.buildTree(arr, 0, segtree_max.getTreeBaseSize()-1, 0));
        System.out.println(segtree_min.buildTree(arr, 0, segtree_min.getTreeBaseSize()-1, 0));

        while(true) {
            System.out.println("----------------MAIN MENU----------------");
            System.out.println("1. Minimum value");
            System.out.println("2. Maximum value");
            System.out.println("3. Sum");
            System.out.println("4. Update by adding 4 with each element");
            System.out.println("5. Exit");

            int opt = sc.nextInt();

            switch(opt) {
                case 1: {
                    long ts1, te1, ts2, te2;
                    int l, r;

                    System.out.println("Index1:");
                    l = sc.nextInt();
                    System.out.println("Index2:");
                    r = sc.nextInt();
                    
                    ts1 = System.nanoTime();
                    System.out.println(segtree_min.getMin(l, r));
                    te1 = System.nanoTime();

                    ts2 = System.nanoTime();
                    int m = bf.getMin(l, r);
                    te2 = System.nanoTime();

                    System.out.println("Segment tree time: " + (te1-ts1));
                    System.out.println("Bruteforce time: " + (te2-ts2));

                    break;
                }

                case 2: {
                    long ts1, te1, ts2, te2;
                    int l, r;

                    System.out.println("Index1:");
                    l = sc.nextInt();
                    System.out.println("Index2:");
                    r = sc.nextInt();

                    ts1 = System.nanoTime();
                    System.out.println(segtree_max.getMax(l, r));
                    te1 = System.nanoTime();
                    
                    ts2 = System.nanoTime();
                    int max = bf.getMax(l, r);
                    te2 = System.nanoTime();

                    System.out.println("Segment tree time: " + (te1-ts1));
                    System.out.println("Bruteforce time: " + (te2-ts2));

                    break;
                }
                
                case 3: {
                    long ts1, te1, ts2, te2;
                    int l, r;

                    System.out.println("Index1:");
                    l = sc.nextInt();
                    System.out.println("Index2:");
                    r = sc.nextInt();

                    ts1 = System.nanoTime();
                    System.out.println(segtree_sum.getSum(l, r));
                    te1 = System.nanoTime();
                    
                    ts2 = System.nanoTime();
                    int sum = bf.getSum(l, r);
                    te2 = System.nanoTime();

                    System.out.println("Segment tree time: " + (te1-ts1));
                    System.out.println("Bruteforce time: " + (te2-ts2));

                    break;
                }

                case 4: {
                    long ts1, te1, ts2, te2;
                    int l, r;
                    
                    System.out.println("Index1:");
                    l = sc.nextInt();
                    System.out.println("Index2:");
                    r = sc.nextInt();

                    ts1 = System.nanoTime();
                    String msg = segtree_min.update(l, r, 4);
                    te1 = System.nanoTime();

                    msg = segtree_max.update(l, r, 4);
                    msg = segtree_sum.update(l, r, 4);

                    ts2 = System.nanoTime();
                    bf.update(l, r, 4);
                    te2 = System.nanoTime();

                    System.out.println("Segment tree time: " + (te1-ts1));
                    System.out.println("Bruteforce time: " + (te2-ts2));

                    System.out.println(msg);
                    break;
                }

                case 5: {
                    System.exit(0);
                }

                default:
                    System.out.println("Wrong input! Try Again.");
            }
        }
    }
}