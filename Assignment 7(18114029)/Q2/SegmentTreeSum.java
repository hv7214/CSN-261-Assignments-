import java.util.*;
import java.lang.*;
import java.io.*;

public class SegmentTreeSum {

    private int[] tree;
    private int size;
    private int height;

    private int sindex = 0;
    private int eindex;
    private int root = 0;
    public int arr_size;

    public SegmentTreeSum(int size) {
        arr_size = size;
        this.height = getHeight(size);
        this.size = (int)Math.pow(2, height+1) - 1;
        tree = new int[this.size];
        eindex = this.getTreeBaseSize() - 1;
    }

    public int getTreeBaseSize() {
        return (int)Math.pow(2, this.height);
    }
    
    public int getTreeSize() {
        return this.size;
    }

    private int getHeight(int size) {
        return (int)(Math.ceil(Math.log(size) / Math.log(2)));
    }

    private int buildTreeUtil(int[] arr, int l, int r, int pos) {
            if (l == r) {
                tree[pos] = (l < arr_size ? arr[l] : 0);
                return tree[pos];
            }

            int mid = (l + r) / 2;
            tree[pos] = buildTreeUtil(arr, l, mid, 2*pos+1) + buildTreeUtil(arr, mid+1, r, 2*pos+2);
            
            return tree[pos];
    }

    public String buildTree(int[] arr, int l, int r, int pos) {
        if(l < 0 || r > Math.pow(2, this.height) - 1 || pos != 0) {
            return "Build Unsuccessful";
        }

        int b = buildTreeUtil(arr, l, r, pos);
        return "Build successful";
    }

    private int getSumUtil(int lptr, int rptr, int pos, int l, int r) {

        if (lptr >= l && rptr <= r) {
            return tree[pos];
        } else if (rptr < l || lptr > r) {              //partial overlap
            return 0;
        }

        int mid = (lptr + rptr) / 2;
        return getSumUtil(lptr, mid, 2*pos+1, l, r) + getSumUtil(mid+1, rptr, 2*pos+2, l, r);
    }

    public int getSum(int l, int r) {
        if(l < 0 || r > Math.pow(2, this.height) - 1) {
            return 0;
        }
        
        return getSumUtil(this.sindex, this.eindex, 0, l, r);
    }
    
    private void updateUtil(int lptr, int rptr, int pos, int l, int r, int val) {

        if ( lptr > r || l > rptr || lptr > rptr) {              
            return;
        } 

        if (lptr == rptr) {
            tree[pos] += val;
            return;
        } 

        int mid = (lptr + rptr) / 2;
        updateUtil(lptr, mid, 2*pos+1, l, r, val);
        updateUtil(mid+1, rptr, 2*pos+2, l, r, val);

        tree[pos] = tree[2*pos+1] + tree[2*pos+2];
    }

    public String update(int l, int r, int val) {
        if(l < 0 || r > Math.pow(2, this.height) - 1) {
            return "Update unsuccessful";
        }

        updateUtil(this.sindex, this.eindex, 0, l, r, val);
        return "Update successful";
    }
}
