import java.io.*;
import java.util.*;

class TwoSum {
    public Set<Long> d = new HashSet<Long>();
    public final int N = 1000000;
    public final String fileName = "HashInt.txt";
    public long[] a = new long[N];
    public int count = 0;

    TwoSum() throws FileNotFoundException, IOException {
        BufferedReader br = new BufferedReader(new FileReader(fileName));
        String str;
        int k = 0;

        // store all numbers in an array as well as hash them into a hash table
        while((str = br.readLine()) != null){
            a[k] = Long.parseLong(str);
            d.add(a[k]);
            k++;
        }
        br.close();
    }

    public void find(long sum){
        
        //System.out.println(sum);
        // for each element "ele" in the array
        for (int i=0; i<a.length; i++){

            // if (sum-ele) is present in the hash table, you have found a match
                long flock = sum - a[i];
            if(d.contains(flock) == true && a[i] != (flock)) {count++; break;}
        }
    }

    public static void main(String[] args) throws FileNotFoundException, IOException {
        TwoSum h = new TwoSum();
        for (long i=-1000; i<=1000; i++) 
            h.find(i);
        System.out.println(h.count);
    }
}

